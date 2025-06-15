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
use patch_apply::{apply, Patch};
use std::env;
use std::fs;
use std::io;
use std::path::{Path, PathBuf};
use walkdir::WalkDir;

const VERSION: &str = "20230824";

fn apply_changes<P: AsRef<Path>, S: AsRef<str>>(root: P, patch_text: S) -> io::Result<()> {
    let root = root.as_ref();
    match Patch::from_multiple(patch_text.as_ref()) {
        Ok(patches) => {
            for patch in patches {
                let old_file_path = root.join(&*patch.old.path);
                let old_file_text = fs::read_to_string(&old_file_path)?;
                fs::remove_file(&old_file_path)?;
                let new_file_path = root.join(&*patch.new.path);
                let new_file_text = apply(old_file_text, patch);
                fs::write(&new_file_path, new_file_text)?;
            }
            Ok(())
        },
        Err(err) => {
            Err(io::Error::other(format!("{err}")))
        },
    }
}

fn main() {
    println!("cargo::rerun-if-changed=build.rs");
    println!("cargo::rerun-if-env-changed=LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES");

    // docs.rs will attempt to compile, to allow for build scripts that generate
    //   bindings on the fly.
    // We manually generate bindings, so there is no need to recompile the
    //   vendored C source for docs.rs
    if env::var("DOCS_RS").is_ok() {
        println!(
            "cargo::warning=docs.rs build, skipping C source build because of manual bindings."
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

    let out_dir = PathBuf::from(env::var("OUT_DIR").unwrap());
    println!("cargo::warning=Using OUT_DIR: {out_dir:?}");

    // Copy source to OUT_DIR, so we can make changes without affecting the
    //   local cache of the bundled source tree (reproducibility).
    for ent in WalkDir::new(format!("libesedb-{VERSION}")) {
        let ent = ent.unwrap();
        if ent.file_type().is_dir() {
            fs::create_dir_all(out_dir.join(ent.path())).unwrap();
        } else if ent.file_type().is_file() {
            fs::copy(ent.path(), out_dir.join(ent.path())).unwrap();
        }
    }

    let src_dir = out_dir.join(format!("libesedb-{VERSION}"));

    // Apply our downstream patches.
    for ent in WalkDir::new("patches") {
        let ent = ent.unwrap();
        if !ent.file_type().is_file() { continue; }
        let name = ent.file_name().to_str().unwrap();
        if !name.ends_with(".patch") { continue; }

        println!("cargo::warning=Applying {:?}", ent.path());
        let patch_file_text = fs::read_to_string(ent.path()).unwrap();
        apply_changes(&src_dir, patch_file_text).unwrap();
    }

    let max_leaf_pages = env::var("LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES")
        .unwrap_or(String::from("(INT_MAX - 1)"));
    println!("cargo::warning=LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES set to `{max_leaf_pages}`");
    c.define("BUILD_RS_LIBESEDB_LEAF_PAGES", &*max_leaf_pages);

    // Add all *relevant* source .c files (lib*/*.c),
    // basically to exclude esedbtools, tests and Python bindings.
    for ent in WalkDir::new(&src_dir) {
        let ent = ent.unwrap();
        if !ent.file_type().is_file() { continue; }
        let name = ent.file_name().to_str().unwrap();
        if !name.ends_with(".c") { continue; }

        let parent_name = ent.path().parent()
            .and_then(|p| p.file_name())
            .and_then(|n| n.to_str()).unwrap();
        if parent_name.starts_with("lib") {
            c.file(ent.path());
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

    if cfg!(windows) {
        println!("cargo::warning=Applying Windows config...");
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
    } else if cfg!(unix) {
        println!("cargo::warning=Applying Unix config...");
        c.define("HAVE_CONFIG_H", None);
        c.define("LOCALEDIR", "\"/usr/share/locale\"");
        apply_changes(&src_dir, "\
            --- common/config.h\n\
            +++ common/config.h\n\
            @@ -29,1 +29,1 @@\n\
            -#define HAVE_CYGWIN_FS_H 1\n\
            +#undef HAVE_CYGWIN_FS_H\n\
        ").unwrap();

        if cfg!(target_os = "macos") {
            println!("cargo::warning=Applying additional MacOS config...");
            apply_changes(&src_dir, "\
                --- common/config.h\n\
                +++ common/config.h\n\
                @@ -227,1 +227,1 @@\n\
                -#define HAVE_LIBINTL_H 1\n\
                +#undef HAVE_LIBINTL_H\n\
                @@ -347,1 +347,1 @@\n\
                -#define HAVE_POSIX_FADVISE 1\n\
                +#undef HAVE_POSIX_FADVISE\n\
            ").unwrap();
        }

        eprintln!("{}", fs::read_to_string(src_dir.join("common/config.h")).unwrap());
    }

    println!("cargo::warning=Compiling (CC)...");
    c.compile("esedb");
}
