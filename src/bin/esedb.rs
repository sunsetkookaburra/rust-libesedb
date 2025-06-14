use anyhow;
use clap::Parser;
use libesedb::{EseDb, Value};
use rusqlite::{params_from_iter, Connection};
use std::{collections::HashMap, path::PathBuf};

#[derive(Parser)]
enum Cli {
    Info {
        /// Path to ESE database file (.edb)
        file: PathBuf,
    },
    Export {
        /// Path to ESE database file (.edb)
        source: PathBuf,
        /// Path for SQLite database file (.db)
        target: PathBuf,
    },
}

fn value_to_sql(value: &Value) -> &dyn rusqlite::ToSql {
    match value {
        Value::Null(_) => &rusqlite::types::Null,
        Value::Bool(x) => x,
        Value::U8(x) => x,
        Value::I16(x) => x,
        Value::I32(x) => x,
        Value::Currency(x) => x,
        Value::F32(x) => x,
        Value::F64(x) => x,
        Value::DateTime(x) => x,
        Value::Binary(x) => x,
        Value::Text(x) => x,
        Value::LargeBinary(x) => x,
        Value::LargeText(x) => x,
        Value::SuperLarge(x) => x,
        Value::U32(x) => x,
        Value::I64(x) => x,
        Value::Guid(x) => x,
        Value::U16(x) => x,
        Value::Long => &rusqlite::types::Null,
        Value::Multi => &rusqlite::types::Null,
    }
}

fn main() -> anyhow::Result<()> {
    match Cli::parse() {
        Cli::Info { ref file } => {
            let db = EseDb::open(file)?;
            for t_i in 0..db.count_tables()? {
                let table = db.table(t_i)?;
                println!("[{t_i}] {}", table.name()?);

                for c_i in 0..table.count_columns()? {
                    let column = table.column(c_i)?;
                    println!(
                        "  [{t_i}.{c_i}] {}: {:?}",
                        column.name()?,
                        column.variant()?
                    );
                }
            }
        }
        Cli::Export {
            ref source,
            ref target,
        } => {
            let db = EseDb::open(source)?;
            let mut conn = Connection::open(target)?;
            conn.pragma_update(None, "journal_mode", "OFF")?;

            for table in db.iter_tables()? {
                let table = table?;
                let table_name = table.name()?;

                println!("Exporting table: {}", table_name);

                let tx = conn.transaction()?;

                tx.execute_batch(
                    &format!(
                        "DROP TABLE IF EXISTS {table_name}; CREATE TABLE {table_name} ({})",
                        table.iter_columns()?.map(|col| anyhow::Ok(col?.name()?)).collect::<Result<Vec<_>, _>>()?.join(",")
                    )
                )?;

                let mut insert_query = tx.prepare(&format!(
                    "INSERT INTO {table_name} VALUES ({})",
                    ["?"].repeat(table.count_columns()? as _).join(","),
                ))?;

                for rec in table.iter_records()? {
                    let rec = rec?;

                    let mut rec_params = vec![];
                    let values = rec.iter_values()?.collect::<Result<Vec<_>, _>>()?;
                    for val in &values {
                        rec_params.push(value_to_sql(val));
                    }
                    insert_query.execute(&*rec_params)?;
                }
                drop(insert_query);
                tx.commit()?;
            }
        }
    }

    Ok(())
}
