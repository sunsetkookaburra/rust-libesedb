use cc::Build;
use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader, Write};
use std::path::PathBuf;
use walkdir::WalkDir;

fn main() {
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-env-changed=LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES");

    // We manually generate bindings, so there is no need to recompile the
    // vendored C source on docs.rs
    if env::var("DOCS_RS").is_ok() {
        println!("cargo:warning=docs.rs build, skipping C source build because of manual bindings.");
        return;
    }

    let mut c = Build::new();

    let mut page_tree_orig =
        BufReader::new(File::open("libesedb-20210424/libesedb/libesedb_page_tree.c").unwrap())
            .lines();
    let page_tree = PathBuf::from(env::var("OUT_DIR").unwrap()).join("libesedb_page_tree.c");
    let mut page_tree_new = File::create(&page_tree).unwrap();

    let max_leaf_pages = env::var("LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES")
        .unwrap_or(String::from("32 * 1024"));
    println!("cargo:warning=LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES set to ({max_leaf_pages})");

    while let Some(line) = page_tree_orig.next() {
        let line = line.unwrap();
        writeln!(page_tree_new, "{line}").unwrap();
        if line.starts_with("#include \"esedb_page_values.h\"") {
            writeln!(page_tree_new).unwrap();
            writeln!(page_tree_new, "#undef LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES").unwrap();
            writeln!(page_tree_new, "#define LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES   ({max_leaf_pages})").unwrap();
        }
    }
    drop(page_tree_new);

    c.include("libesedb-20210424/include");
    c.include("libesedb-20210424/common");
    c.include("libesedb-20210424/libbfio");
    c.include("libesedb-20210424/libcdata");
    c.include("libesedb-20210424/libcerror");
    c.include("libesedb-20210424/libcfile");
    c.include("libesedb-20210424/libclocale");
    c.include("libesedb-20210424/libcnotify");
    c.include("libesedb-20210424/libcpath");
    c.include("libesedb-20210424/libcsplit");
    c.include("libesedb-20210424/libcthreads");
    c.include("libesedb-20210424/libesedb");
    c.include("libesedb-20210424/libfcache");
    c.include("libesedb-20210424/libfdata");
    c.include("libesedb-20210424/libfdatetime");
    c.include("libesedb-20210424/libfguid");
    c.include("libesedb-20210424/libfmapi");
    c.include("libesedb-20210424/libfvalue");
    c.include("libesedb-20210424/libfwnt");
    c.include("libesedb-20210424/libmapidb");
    c.include("libesedb-20210424/libuna");

    for ent in WalkDir::new("libesedb-20210424") {
        let ent = ent.unwrap();
        if ent.file_type().is_file() {
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
                    c.file(&page_tree);
                } else if parent_name.starts_with("lib") {
                    c.file(ent.path());
                }
            }
        }
    }

    if cfg!(target_family = "unix") {
        c.define("HAVE_CONFIG_H", None);
        c.define("LOCALEDIR", "\"/usr/share/locale\"");
    } else if cfg!(target_family = "windows") {
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
    }

    c.compile("esedb");
}
