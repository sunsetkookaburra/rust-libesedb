//! # rust-libesedb - Safe Rust API to libesedb
//!
//! # Example
//!
//! ```no_run
//! use libesedb::EseDb;
//!
//! fn main() {
//!     let filename = std::env::args()
//!         .nth(1)
//!         .unwrap_or("Catalog1.edb".to_string());
//!     let db = EseDb::open(filename).unwrap();
//!     println!("Db load finished!");
//!     let string = db.table_by_name("string").unwrap();
//!     for rec in string.iter_records().unwrap() {
//!         let rec = rec.unwrap();
//!         let vals = rec.iter_values().unwrap().map(|v| v.unwrap_or_default().to_string()).collect::<Vec<_>>();
//!         println!("{}", vals.join("\t"));
//!     }
//! }
//! ```

mod error;
mod db;
mod iter;
mod table;
mod column;
mod record;
mod value;

pub use db::*;
pub use table::*;
