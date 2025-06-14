use anyhow;
use clap::Parser;
use libesedb::EseDb;
use std::path::PathBuf;

#[derive(Parser)]
struct Cli {
    /// Path to ESE database file (.edb)
    file: PathBuf,
}

fn main() -> anyhow::Result<()> {
    let args = Cli::parse();
    let db = EseDb::open(&args.file)?;

    println!("Database Overview ({:?})", &args.file);
    for table in db.iter_tables()? {
        let table = table?;
        println!("{}", table.name()?);

        for column in table.iter_columns()? {
            let column = column?;
            println!("  {}: {:?}", column.name()?, column.variant()?);
        }
    }

    Ok(())
}
