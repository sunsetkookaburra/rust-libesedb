//! # rust-libesedb
//!
//! [![Repository](https://img.shields.io/static/v1?label=GitHub&message=Repository&color=9f7be1&logo=github)](https://github.com/sunsetkookaburra/rust-libesedb)
//! [![Crate Page](https://img.shields.io/crates/v/libesedb?logo=rust)](https://crates.io/crates/libesedb)
//! [![Documentation](https://img.shields.io/docsrs/libesedb?logo=rust)](https://docs.rs/libesedb)
//! [![License](https://img.shields.io/crates/l/libesedb)](https://github.com/sunsetkookaburra/rust-libesedb/blob/main/COPYING.LESSER)
//!
//! Safe Rust bindings to [`libyal/libesedb`](https://github.com/libyal/libesedb) (via [`libesedb-sys`](https://docs.rs/libesedb-sys)).
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
//!
//! ## License and Acknowledgement
//!
//! This project is made available under the [LGPL-3.0-or-later](./COPYING.LESSER).
//!
//! The core functionality that this library binds to is the hard work of [`Joachim Metz (~joachimmetz)`](https://github.com/joachimmetz).


mod error;
mod db;
mod iter;
mod table;
mod column;
mod record;
mod value;

pub use db::*;
pub use iter::*;
pub use table::*;
pub use column::*;
pub use record::*;
pub use value::*;
