# rust-libesedb

[![Repository](https://img.shields.io/static/v1?label=GitHub&message=Repository&color=9f7be1&logo=github)](https://github.com/sunsetkookaburra/rust-libesedb)
[![Crate Page](https://img.shields.io/crates/v/libesedb?logo=rust)](https://crates.io/crates/libesedb)
[![Documentation](https://img.shields.io/docsrs/libesedb?logo=rust)](https://docs.rs/libesedb)
[![License](https://img.shields.io/crates/l/libesedb)](https://github.com/sunsetkookaburra/rust-libesedb/blob/main/COPYING.LESSER)

Safe Rust bindings to [`libyal/libesedb`](https://github.com/libyal/libesedb) (via [`libesedb-sys`](https://github.com/sunsetkookaburra/rust-libesedb/tree/main/libesedb-sys)).

```rust
use libesedb::EseDb;

fn main() {
    let filename = std::env::args()
        .nth(1)
        .unwrap_or("Catalog1.edb".to_string());
    let db = EseDb::open(filename).unwrap();
    println!("Db load finished!");
    let string = db.table_by_name("string").unwrap();
    for rec in string.iter_records().unwrap() {
        let rec = rec.unwrap();
        let vals = rec.iter_values().unwrap().map(|v| v.unwrap_or_default().to_string()).collect::<Vec<_>>();
        println!("{}", vals.join("\t"));
    }
}
```

## Test Data

* <https://github.com/janstarke/ntdsextract2/blob/10-include-deleted-entries-in-timeline/tests/data/ntds_plain.dit>

## Future Changes

* `v0.3.0`
    * Remove `close()` methods in favour of `drop!()`
    * Lazy-load `Value`s (store some sort of record reference, similar to current LongValue and MultiValue internally)
    * `Value`s come in either `FlatValue`, `LongValue`, `MultiValue` variants, with a defined `ValueType`

## License and Acknowledgement

This project is made available under the [LGPL-3.0-or-later](./COPYING.LESSER).

The `time` crate (used in FILETIME/OLETIME conversions) is available under the [MIT License](https://github.com/time-rs/time/blob/main/LICENSE-MIT).

The core functionality that this library binds to is the hard work of [`Joachim Metz (~joachimmetz)`](https://github.com/joachimmetz).
