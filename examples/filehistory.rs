use std::{
    collections::{HashMap, HashSet},
    path::{Path, PathBuf},
    time::SystemTime,
};

use anyhow::anyhow;
use clap::{builder::Str, Parser, Subcommand};
use humansize::{format_size, DECIMAL};
use input_macro::input;
use libesedb::{EseDb, Value, };
use time::{OffsetDateTime, UtcDateTime, UtcOffset};

#[derive(Parser)]
struct Args {
    #[command(subcommand)]
    command: Command,
}

#[derive(Subcommand)]
enum Command {
    Info {
        /// For example, `E:\FileHistory\User\DESKTOP-XXXXXX\Configuration\Catalog1.edb`
        catalog: String,
    },
    List {
        /// For example, `E:\FileHistory\User\DESKTOP-XXXXXX\Configuration\Catalog1.edb`
        catalog: String,
    },
    // Copy {
    //   #[arg(name = "Catalog.edb")]
    //   catalog: String,
    // },
}

fn open_filehistory<P: AsRef<Path>>(filename: P) -> anyhow::Result<EseDb> {
    let db = EseDb::open(filename)?;
    let mut tables = HashSet::new();
    for table in db.iter_tables()? {
        tables.insert(table?.name()?);
    }
    if !tables.is_superset(&HashSet::from([
        String::from("backupset"),
        String::from("file"),
        String::from("global"),
        String::from("library"),
        String::from("namespace"),
        String::from("string"),
    ])) {
        Err(anyhow!("Not a valid FileHistory catalog"))
    } else {
        Ok(db)
    }
}

fn systemtime_to_localtime(time: SystemTime) -> OffsetDateTime {
    let mut time = OffsetDateTime::from(time);
    if let Ok(offset) = UtcOffset::current_local_offset() {
        time = time.to_offset(offset);
    }
    time
}

fn rfc3339(time: OffsetDateTime) -> anyhow::Result<String> {
    Ok(time.format(&time::format_description::well_known::Rfc3339)?)
}

fn main() -> anyhow::Result<()> {
    let args = Args::parse();
    match args.command {
        Command::Info { catalog } => {
            let db = open_filehistory(&catalog)?;
            let fh_global = {
                let table = db.table_by_name("global")?;
                let cols = table
                    .iter_columns()?
                    .enumerate()
                    .map(|(i, col)| anyhow::Ok((col?.name()?, i)))
                    .collect::<Result<HashMap<_, _>, _>>()?;
                let key_col = *cols.get("key").ok_or(anyhow!("No 'key' column"))? as _;
                let value_col = *cols.get("value").ok_or(anyhow!("No 'value' column"))? as _;
                let kv = table
                    .iter_records()?
                    .map(|rec| {
                        rec.and_then(|rec| {
                            std::result::Result::Ok((
                                rec.value(key_col)?.as_str().unwrap().to_string(),
                                rec.value(value_col)?,
                            ))
                        })
                    })
                    .collect::<Result<HashMap<_, _>, _>>()?;
                kv
            };
            let fh_file = {
                let table = db.table_by_name("file")?;
                let cols = table
                    .iter_columns()?
                    .enumerate()
                    .map(|(i, col)| anyhow::Ok((col?.name()?, i)))
                    .collect::<Result<HashMap<_, _>, _>>()?;
            };
            println!("File History Information");
            println!(
                "  First Backup: {}",
                fh_global
                    .get("FirstBackupTime")
                    .and_then(|x| Some(u64::from_le_bytes(x.as_bytes()?.try_into().ok()?)))
                    .map(libesedb::systemtime_from_filetime)
                    .map(systemtime_to_localtime)
                    .map(rfc3339)
                    .transpose()?
                    .unwrap_or("N/A".into())
            );
            println!(
                "  Last Backup:  {}",
                fh_global
                    .get("LastBackupTime")
                    .and_then(|x| Some(u64::from_le_bytes(x.as_bytes()?.try_into().ok()?)))
                    .map(libesedb::systemtime_from_filetime)
                    .map(systemtime_to_localtime)
                    .map(rfc3339)
                    .transpose()?
                    .unwrap_or("N/A".into())
            );
            let files_fp = fh_global
                .get("FullyProtectedFileRecords")
                .and_then(|x| Some(u32::from_le_bytes(x.as_bytes()?.try_into().ok()?)))
                .unwrap_or(0);
            let files_pp = fh_global
                .get("PartiallyProtectedFileRecords")
                .and_then(|x| Some(u32::from_le_bytes(x.as_bytes()?.try_into().ok()?)))
                .unwrap_or(0);
            let files_up = fh_global
                .get("UnprotectedFileRecords")
                .and_then(|x| Some(u32::from_le_bytes(x.as_bytes()?.try_into().ok()?)))
                .unwrap_or(0);
            println!("  Total Files:  {}", files_fp + files_pp + files_up);
            let files_size = fh_global
                .get("TotalBytesOnDefaultTarget")
                .and_then(|x| Some(u64::from_le_bytes(x.as_bytes()?.try_into().ok()?)))
                .unwrap_or(0);
            println!("  Total Size:   {}", format_size(files_size, humansize::DECIMAL));
            let fh_path = Path::new(&catalog).canonicalize()?;
            if let Some(parent) = fh_path.parent() {
                if parent.file_name().unwrap().to_string_lossy() == "Configuration" {
                    let machine_name_path = parent.parent().unwrap();
                    let machine_name = machine_name_path.file_name().unwrap().to_string_lossy();
                    let user_name = machine_name_path.parent().unwrap().file_name().unwrap().to_string_lossy();
                    println!("  Machine:      {}", machine_name);
                    println!("  User:         {}", user_name);
                }
            }
        }
        Command::List { catalog } => {}
    }
    // let db: std::result::Result<EseDb, std::io::Error> =
    // EseDb::open(filename)
    // check for `strings` and for `file`
    Ok(())
}
