# libesedb-sys

[![Repository](https://img.shields.io/static/v1?label=GitHub&message=Repository&color=9f7be1&logo=github)](https://github.com/sunsetkookaburra/rust-libesedb)
[![Upstream](https://img.shields.io/static/v1?label=GitHub&message=Upstream&color=9f7be1&logo=github)](https://github.com/libyal/libesedb)
[![Crate Page](https://img.shields.io/crates/v/libesedb-sys?logo=rust)](https://crates.io/crates/libesedb-sys)
[![Documentation](https://img.shields.io/docsrs/libesedb-sys?logo=rust)](https://docs.rs/libesedb-sys)
[![License](https://img.shields.io/crates/l/libesedb-sys)](https://github.com/sunsetkookaburra/rust-libesedb/blob/main/COPYING.LESSER)

Rust `-sys` bindings to [`libyal/libesedb`](https://github.com/libyal/libesedb).


## Building

Ensure that all git submodules are initialised after which `cargo build` can be used to compile this library.

### Updating

Updating submodules can be achieved by executing the following within the desired submodule `git fetch; git checkout $(git tag -l --sort=-taggerdate | tail -1)`.
Or all submodules can be updated via `./update.sh`.

When updating `libesedb` the changes must be reflected in `Cargo.toml`, `build.rs` and `lib.rs`.

## Authors

```
libesedb
Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>

libesedb-sys
Copyright (C) 2022-2025, Oliver Lenehan ~sunsetkookaburra
```


## License

* [`libyal/libesedb`](https://github.com/libyal/libesedb) is the hard work of [`Joachim Metz (~joachimmetz)`](https://github.com/joachimmetz), provided under [LGPL-3.0-or-later](./COPYING.LESSER). A distribution version of the library is bundled here.
* This `-sys` binding is also provided under [LGPL-3.0-or-later](./COPYING.LESSER).
