# libesedb-sys

Rust `-sys` bindings to [`libyal/libesedb`](https://github.com/libyal/libesedb).

## Building

* Have a compiler installed (if you're using Rust, you have one).
* (Optionally) LLVM for `bindgen` to regenerate the bindings.
* Should use `cargo build -vv` for very verbose output to verify `cc` compiling.

## Rebuilding Bindings

```
bindgen libesedb-20210424/include/libesedb.h -o src/bindings.rs -- -Ilibesedb-20210424/include -fparse-all-comments
```

## Configuring Max Leaf-Pages

Note: the original value of `16 * 1024` has been increased to `32 * 1024` in order for a FileHistory `Catalog*.edb` of at least 330MB to load.

Via the command-line:

```
LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES="32 * 1024" cargo build -vv
```

In your Cargo.toml:

```
[env]
LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES = "32 * 1024"
```

## Authors

```
libesedb
Copyright (C) 2009-2021, Joachim Metz <joachim.metz@gmail.com>

libesedb-sys
Copyright (C) 2022-2023, Oliver Lenehan ~sunsetkookaburra
```

## License

* [`libyal/libesedb`](https://github.com/libyal/libesedb) is the hard work of [`Joachim Metz (~joachimmetz)`](https://github.com/joachimmetz), available under the [LGPL-3.0-or-later](./COPYING.LESSER). A distribution version of the library is bundled here.
* This `-sys` binding is also made available under the [LGPL-3.0-or-later](./COPYING.LESSER).
