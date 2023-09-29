//! # libesedb-sys
//!
//! [![Repository](https://img.shields.io/static/v1?label=GitHub&message=Repository&color=9f7be1&logo=github)](https://github.com/sunsetkookaburra/rust-libesedb)
//! [![Upstream](https://img.shields.io/static/v1?label=GitHub&message=Upstream&color=9f7be1&logo=github)](https://github.com/libyal/libesedb)
//! [![Crate Page](https://img.shields.io/crates/v/libesedb-sys?logo=rust)](https://crates.io/crates/libesedb-sys)
//! [![Documentation](https://img.shields.io/docsrs/libesedb-sys?logo=rust)](https://docs.rs/libesedb-sys)
//! [![License](https://img.shields.io/crates/l/libesedb-sys)](https://github.com/sunsetkookaburra/rust-libesedb/blob/main/COPYING.LESSER)
//!
//! Rust `-sys` bindings to [`libyal/libesedb`](https://github.com/libyal/libesedb).
//!
//! ## Building
//!
//! * Have a compiler installed (if you're using Rust, you have one).
//! * (Optionally) LLVM for `bindgen` to regenerate the bindings.
//! * Should use `cargo build -vv` for very verbose output to verify `cc` compiling.
//!
//! ## Rebuilding Bindings
//!
//! ```
//! bindgen libesedb-20230824/include/libesedb.h -o src/bindings.rs -- -Ilibesedb-20210424/include -fparse-all-comments
//! ```
//!
//! ## Configuring Max Leaf-Pages
//!
//! Note: the original value of `16 * 1024` has been increased to `32 * 1024` in order for a FileHistory `Catalog*.edb` of at least 330MB to load.
//!
//! Via the command-line:
//!
//! ```
//! LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES="32 * 1024" cargo build -vv
//! ```
//!
//! In your Cargo.toml:
//!
//! ```
//! [env]
//! LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES = "32 * 1024"
//! ```
//!
//! ## Updating Bundled libesedb
//!
//! * Download/Clone head of the `main` branch
//!   * `git clone --branch main --depth 1 https://github.com/libyal/libesedb`
//!   * <https://github.com/libyal/libesedb/archive/refs/heads/main.zip>
//! * Follow Build Instructions <https://github.com/libyal/libesedb/wiki/Building>
//!   * Run the following
//!     * `./synclibs.sh`
//!     * `./autogen.sh`
//!     * `./configure`
//!     * `make dist`
//!   * Output should include a `.tar.gz` containing the source distribution version
//!   * Note: I used Cygwin on Windows, you will need the packages mentioned here: <https://github.com/libyal/libesedb/wiki/Building#cygwin>
//!
//!
//! ## Authors
//!
//! ```
//! libesedb
//! Copyright (C) 2009-2021, Joachim Metz <joachim.metz@gmail.com>
//!
//! libesedb-sys
//! Copyright (C) 2022-2023, Oliver Lenehan ~sunsetkookaburra
//! ```
//!
//! ## License
//!
//! * [`libyal/libesedb`](https://github.com/libyal/libesedb) is the hard work of [`Joachim Metz (~joachimmetz)`](https://github.com/joachimmetz), available under the [LGPL-3.0-or-later](./COPYING.LESSER). A distribution version of the library is bundled here.
//! * This `-sys` binding is also made available under the [LGPL-3.0-or-later](./COPYING.LESSER).

#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(deref_nullptr)]

include!("bindings.rs");
