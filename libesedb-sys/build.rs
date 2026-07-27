/*
 * Rust build script for bindings to libesedb
 *
 * Copyright (C) 2022-2023, Oliver Lenehan ~sunsetkookaburra
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

use std::env;
use std::fs;
use std::path::{Path, PathBuf};

use cc::Build;

const VERSION: &str = "20260704";

const LIBYALS: [&str; 18] = [
    "libbfio",
    "libcdata",
    "libcerror",
    "libcfile",
    "libclocale",
    "libcnotify",
    "libcpath",
    "libcsplit",
    "libcthreads",
    "libfcache",
    "libfdata",
    "libfdatetime",
    "libfguid",
    "libfmapi",
    "libfvalue",
    "libfwnt",
    "libmapidb",
    "libuna",
];

fn main() {
    println!("cargo::rerun-if-changed=libesedb/common");
    println!("cargo::rerun-if-changed=libesedb/include");
    println!("cargo::rerun-if-changed=libesedb/libesedb");

    let target = env::var("TARGET").unwrap();

    let mut cfg = Build::new();
    let dst = PathBuf::from(env::var_os("OUT_DIR").unwrap());
    let common = dst.join("common");
    fs::create_dir_all(&common).unwrap();
    let include = dst.join("include");
    fs::create_dir_all(&include).unwrap();
    let libesedb = dst.join("libesedb");
    fs::create_dir_all(&libesedb).unwrap();

    cp_r("libesedb/common", &common);
    cfg.include(&common);
    cp_r("libesedb/include", &include);
    cfg.include(&include);
    cp_r("libesedb/libesedb", &libesedb);

    for libyal in &LIBYALS {
        let lib = libesedb.join(libyal);
        fs::create_dir_all(&lib).unwrap();
        cp_r(format!("{}/{}", libyal, libyal), &lib);
        cfg.include(&lib);
        cfg.define(&format!("HAVE_LOCAL_{}", libyal.to_uppercase()), "1");
        println!("cargo::rerun-if-changed={}/{}", libyal, libyal);
    }

    // Set all the autoconf string substitutions.
    let package = format!("libesedb {}", VERSION);
    let ac_config = vec![
        ["HAVE_INTTYPES_H", "0"],
        ["HAVE_LIBBFIO", "0"],
        ["HAVE_MULTI_THREAD_SUPPORT", "0"],
        ["HAVE_OFF64_T", "0"],
        ["HAVE_SIZE32_T", "0"],
        ["HAVE_SIZE64_T", "0"],
        ["HAVE_SSIZE32_T", "0"],
        ["HAVE_SSIZE64_T", "0"],
        ["HAVE_STDINT_H", "0"],
        ["HAVE_SYS_TYPES_H", "0"],
        ["HAVE_WCHAR_H", "0"],
        ["HAVE_WIDE_CHARACTER_TYPE", "0"],
        ["PACKAGE", "libesedb"],
        ["PACKAGE_BUGREPORT", "joachim.metz@gmail.com"],
        ["PACKAGE_NAME", "libesedb"],
        ["PACKAGE_STRING", &package],
        ["PACKAGE_TARNAME", "libesedb"],
        ["PACKAGE_URL", ""],
        ["PACKAGE_VERSION", VERSION],
    ];

    // Add all the `c` files while also converting `in` files.
    configure_files(&mut cfg, &dst, &ac_config);

    eprintln!("{}", target);
    if target.contains("windows") {
        cfg.define("WINAPI", "1");
    } else {
        cfg.define("HAVE_CHDIR", "1");
        cfg.define("HAVE_CLOSE", "1");
        cfg.define("HAVE_ERRNO_H", "1");
        cfg.define("HAVE_FCLOSE", "1");
        cfg.define("HAVE_FCNTL_H", "1");
        cfg.define("HAVE_FOPEN", "1");
        cfg.define("HAVE_FREAD", "1");
        cfg.define("HAVE_FREE", "1");
        cfg.define("HAVE_FSTAT", "1");
        cfg.define("HAVE_FTRUNCATE", "1");
        cfg.define("HAVE_FWRITE", "1");
        cfg.define("HAVE_GETCWD", "1");
        cfg.define("HAVE_INTTYPES_H", "1");
        cfg.define("HAVE_LIMITS_H", "1");
        cfg.define("HAVE_LOCALE_H", "1");
        cfg.define("HAVE_LSEEK", "1");
        cfg.define("HAVE_MALLOC", "1");
        cfg.define("HAVE_MEMCHR", "1");
        cfg.define("HAVE_MEMCMP", "1");
        cfg.define("HAVE_MEMCPY", "1");
        cfg.define("HAVE_MEMSET", "1");
        cfg.define("HAVE_MKDIR", "1");
        cfg.define("HAVE_MULTI_THREAD_SUPPORT", "1");
        cfg.define("HAVE_OPEN", "1");
        cfg.define("HAVE_PTHREAD_H", "1");
        cfg.define("HAVE_READ", "1");
        cfg.define("HAVE_REALLOC", "1");
        cfg.define("HAVE_STAT", "1");
        cfg.define("HAVE_STDARG_H", "1");
        cfg.define("HAVE_STDINT_H", "1");
        cfg.define("HAVE_STDLIB_H", "1");
        cfg.define("HAVE_STRERROR_R", "1");
        cfg.define("HAVE_STRING_H", "1");
        cfg.define("HAVE_STRLEN", "1");
        cfg.define("HAVE_STRNCASECMP", "1");
        cfg.define("HAVE_SYS_STAT_H", "1");
        cfg.define("HAVE_SYS_TYPES_H", "1");
        cfg.define("HAVE_UNISTD_H", "1");
        cfg.define("HAVE_UNLINK", "1");
        cfg.define("HAVE_VSNPRINTF", "1");
        cfg.define("HAVE_WRITE", "1");
    }

    let mut bind = bindgen::Builder::default()
        .allowlist_file(".*libesedb.*")
        // NOTE: Enums are typed in `lib.rs` to handle signed issue!
        .blocklist_type("LIBESEDB_CODEPAGES")
        .blocklist_type("LIBESEDB_.*_DOMAINS")
        .blocklist_type("LIBESEDB_.*_ERROR")
        .blocklist_type("LIBESEDB_.*_FLAGS")
        .blocklist_type("LIBESEDB_.*_TYPES")
        .clang_arg("-DHAVE_STDINT_H")
        .clang_arg("-DHAVE_SYS_TYPES_H")
        .clang_arg(&format!("-I{}", include.display()))
        .header("wrapper.h");

    if target.contains("apple") {
        bind = bind.clang_arg("-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include");
    }

    let bindings = bind.generate().unwrap();
    bindings.write_to_file(dst.join("bindings.rs")).unwrap();

    cfg.compile("esedb");

    println!("cargo:root={}", dst.display());
}

fn add_file(cfg: &mut Build, path: &Path) {
    if let Some(extension) = path.extension() {
        if extension == "c" {
            cfg.file(&path);
        }
    }
}

fn configure_files(cfg: &mut Build, path: &Path, defaults: &Vec<[&str; 2]>) {
    for e in path.read_dir().unwrap() {
        let e = e.unwrap();
        let path = e.path();
        if e.file_type().unwrap().is_dir() {
            configure_files(cfg, &path, &defaults);
        } else {
            if let Some(extension) = path.extension() {
                if extension == "in" {
                    let mut contents = fs::read_to_string(&path).unwrap();
                    for [k, v] in defaults {
                        contents = contents.replace(&format!("@{}@", k), v);
                    }
                    let stem = path.file_stem().unwrap();
                    let out = path.with_file_name(stem);
                    fs::write(&out, contents).unwrap();
                    add_file(cfg, &out);
                }
                add_file(cfg, &path);
            }
        }
    }
}

fn cp_r(from: impl AsRef<Path>, to: impl AsRef<Path>) {
    for e in from.as_ref().read_dir().unwrap() {
        let e = e.unwrap();
        let from = e.path();
        let to = to.as_ref().join(e.file_name());
        if e.file_type().unwrap().is_dir() {
            fs::create_dir_all(&to).unwrap();
            cp_r(&from, &to);
        } else {
            fs::copy(&from, &to).unwrap();
        }
    }
}
