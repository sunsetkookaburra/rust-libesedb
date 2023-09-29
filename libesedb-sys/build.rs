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

use cc::Build;
use std::env;
use std::fs::{copy, create_dir_all, File};
use std::io::{BufRead, BufReader, Write};
use std::path::PathBuf;
use std::process::Command;
use walkdir::WalkDir;

const VERSION: &str = "20230824";

fn main() {
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-env-changed=LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES");

    // docs.rs will attempt to compile, to allow for build scripts that generate
    //   bindings on the fly.
    // We manually generate bindings, so there is no need to recompile the
    //   vendored C source for docs.rs
    if env::var("DOCS_RS").is_ok() {
        println!(
            "cargo:warning=docs.rs build, skipping C source build because of manual bindings."
        );
        return;
    }

    // There are a couple different approaches to building '*-sys' crates.
    // This site provides a great overview and initial starting point:
    //   https://kornel.ski/rust-sys-crate
    // The build script here takes a weird combo hybrid approach that
    //   hopefully works well all-round.
    // On Windows:
    //   * Compile with `cc` crate
    // On Unices:
    //   * Run configure script
    //   * Compile with `cc` crate
    let mut c = Build::new();

    // Copy source to OUT_DIR, so we can make changes without affecting the
    //   bundled source tree (allow for reproducibility).
    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());
    let src_dir = out_dir.join(format!("libesedb-{VERSION}"));

    for ent in WalkDir::new(format!("libesedb-{VERSION}")) {
        let ent = ent.unwrap();
        if ent.file_type().is_dir() {
            // println!("{:?}", out_dir.join(ent.path()));
            create_dir_all(out_dir.join(ent.path())).unwrap();
        } else if ent.file_type().is_file() {
            copy(ent.path(), out_dir.join(ent.path())).unwrap();
            let name = ent.file_name().to_str().unwrap();
            if name.ends_with(".c") {
                let parent_name = ent
                    .path()
                    .parent()
                    .unwrap()
                    .file_name()
                    .unwrap()
                    .to_str()
                    .unwrap();
                if name == "libesedb_page_tree.c" {
                    let max_leaf_pages = env::var("LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES")
                        .unwrap_or(String::from("32 * 1024"));
                    println!("cargo:warning=LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES set to ({max_leaf_pages})");
                    let mut page_tree = File::create(out_dir.join(ent.path())).unwrap();
                    for line in BufReader::new(File::open(ent.path()).unwrap()).lines() {
                        let line = line.unwrap();
                        writeln!(page_tree, "{line}").unwrap();
                        if line.starts_with("#include \"esedb_page_values.h\"") {
                            writeln!(page_tree).unwrap();
                            writeln!(page_tree, "#undef LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES")
                                .unwrap();
                            writeln!(page_tree, "#define LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES   ({max_leaf_pages})").unwrap();
                        }
                    }
                    c.file(ent.path());
                } else if parent_name.starts_with("lib") {
                    c.file(ent.path());
                }
            }
        }
    }

    c.include(src_dir.join("include"));
    c.include(src_dir.join("common"));
    c.include(src_dir.join("libbfio"));
    c.include(src_dir.join("libcdata"));
    c.include(src_dir.join("libcerror"));
    c.include(src_dir.join("libcfile"));
    c.include(src_dir.join("libclocale"));
    c.include(src_dir.join("libcnotify"));
    c.include(src_dir.join("libcpath"));
    c.include(src_dir.join("libcsplit"));
    c.include(src_dir.join("libcthreads"));
    c.include(src_dir.join("libesedb"));
    c.include(src_dir.join("libfcache"));
    c.include(src_dir.join("libfdata"));
    c.include(src_dir.join("libfdatetime"));
    c.include(src_dir.join("libfguid"));
    c.include(src_dir.join("libfmapi"));
    c.include(src_dir.join("libfvalue"));
    c.include(src_dir.join("libfwnt"));
    c.include(src_dir.join("libmapidb"));
    c.include(src_dir.join("libuna"));

    if env::var("CARGO_CFG_TARGET_FAMILY").unwrap() == "windows" {
        c.define("HAVE_LOCAL_LIBBFIO", "1");
        c.define("HAVE_LOCAL_LIBCDATA", "1");
        c.define("HAVE_LOCAL_LIBCERROR", "1");
        c.define("HAVE_LOCAL_LIBCFILE", "1");
        c.define("HAVE_LOCAL_LIBCLOCALE", "1");
        c.define("HAVE_LOCAL_LIBCNOTIFY", "1");
        c.define("HAVE_LOCAL_LIBCPATH", "1");
        c.define("HAVE_LOCAL_LIBCSPLIT", "1");
        c.define("HAVE_LOCAL_LIBCTHREADS", "1");
        c.define("HAVE_LOCAL_LIBFCACHE", "1");
        c.define("HAVE_LOCAL_LIBFDATA", "1");
        c.define("HAVE_LOCAL_LIBFDATETIME", "1");
        c.define("HAVE_LOCAL_LIBFGUID", "1");
        c.define("HAVE_LOCAL_LIBFMAPI", "1");
        c.define("HAVE_LOCAL_LIBFVALUE", "1");
        c.define("HAVE_LOCAL_LIBFWNT", "1");
        c.define("HAVE_LOCAL_LIBMAPIDB", "1");
        c.define("HAVE_LOCAL_LIBUNA", "1");
    } else if env::var("CARGO_CFG_TARGET_FAMILY").unwrap() == "unix" {
        c.define("HAVE_CONFIG_H", None);
        c.define("LOCALEDIR", "\"/usr/share/locale\"");

        Command::new("chmod")
            .arg("+x")
            .arg(src_dir.join("configure"))
            .status()
            .unwrap();
        // Run configure on Unices (they have shell)
        Command::new(src_dir.join("configure"))
            .current_dir(src_dir)
            .env("CC", c.get_compiler().cc_env())
            .env("CFLAGS", c.get_compiler().cflags_env())
            .status()
            .unwrap();
    }

    c.compile("esedb");
}
