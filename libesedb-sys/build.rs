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
            writeln!(
                page_tree_new,
                r#"
                    #undef LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES
                    #define LIBESEDB_MAXIMUM_NUMBER_OF_LEAF_PAGES   ({max_leaf_pages})
                "#
            )
            .unwrap();
        }
    }
    drop(page_tree_new);

    c.file(&page_tree);
    c.include("libesedb-20210424/include");
    c.include("libesedb-20210424/common");

    for ent in WalkDir::new("libesedb-20210424") {
        let ent = ent.unwrap();
        let typ = ent.file_type();
        let name = ent.file_name().to_str().unwrap();
        if typ.is_file() {
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
                    continue;
                } else if parent_name.starts_with("lib") {
                    c.file(ent.path());
                }
            }
        } else if typ.is_dir() {
            let full_path = ent.path().to_str().unwrap();

            // `include/libesedb` contains a features.h, which conflicts with
            // `/usr/include/features.h`. The same applies to `types.h`
            if full_path.ends_with("include/libesedb") {
                continue;
            }

            // do not include msvscpp headers on non-Windows OSes
            if ! cfg!(target_os="windows") {
                if full_path.contains("msvscpp") {
                    continue;
                }
            }

            if name.starts_with("lib") {
                
                c.include(ent.path());
            }
        }
    }

    if cfg!(target_os="linux") {
        c.define("ENABLE_NLS", "1");
        c.define("HAVE_BINDTEXTDOMAIN", "1");
        c.define("HAVE_CHDIR", "1");
        c.define("HAVE_CLOCK_GETTIME", "1");
        c.define("HAVE_CLOSE", "1");
        c.define("HAVE_DCGETTEXT", "1");
        c.define("HAVE_DECL_MEMRCHR", "0");
        c.define("HAVE_DECL_STRERROR_R", "1");
        c.define("HAVE_DLFCN_H", "1");
        c.define("HAVE_ERRNO_H", "1");
        c.define("HAVE_FCLOSE", "1");
        c.define("HAVE_FCNTL_H", "1");
        c.define("HAVE_FEOF", "1");
        c.define("HAVE_FGETS", "1");
        c.define("HAVE_FMEMOPEN", "1");
        c.define("HAVE_FOPEN", "1");
        c.define("HAVE_FREAD", "1");
        c.define("HAVE_FREE", "1");
        c.define("HAVE_FSEEKO", "1");
        c.define("HAVE_FSEEKO64", "1");
        c.define("HAVE_FSTAT", "1");
        c.define("HAVE_FTRUNCATE", "1");
        c.define("HAVE_FWRITE", "1");
        c.define("HAVE_GETCWD", "1");
        c.define("HAVE_GETENV", "1");
        c.define("HAVE_GETOPT", "1");
        c.define("HAVE_GETTEXT", "1");
        c.define("HAVE_GNU_DL_DLSYM", "1");
        c.define("HAVE_INTTYPES_H", "1");
        c.define("HAVE_IOCTL", "1");
        c.define("HAVE_LANGINFO_CODESET", "1");
        c.define("HAVE_LANGINFO_H", "1");
        c.define("HAVE_LIBDL", "1");
        c.define("HAVE_LIBINTL_H", "1");
        c.define("HAVE_LIMITS_H", "1");
        c.define("HAVE_LINUX_FS_H", "1");
        c.define("HAVE_LOCALECONV", "1");
        c.define("HAVE_LOCALE_H", "1");
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
        c.define("HAVE_LSEEK", "1");
        c.define("HAVE_MALLOC", "1");
        c.define("HAVE_MEMCHR", "1");
        c.define("HAVE_MEMCMP", "1");
        c.define("HAVE_MEMCPY", "1");
        c.define("HAVE_MEMORY_H", "1");
        c.define("HAVE_MEMRCHR", "1");
        c.define("HAVE_MEMSET", "1");
        c.define("HAVE_MKDIR", "1");
        c.define("HAVE_MKDIR_MODE", "1");
        c.define("HAVE_MKSTEMP", "1");
        c.define("HAVE_MULTI_THREAD_SUPPORT", "1");
        c.define("HAVE_NL_LANGINFO", "1");
        c.define("HAVE_OPEN", "1");
        c.define("HAVE_POSIX_FADVISE", "1");
        c.define("HAVE_PRINTF_JD", "1");
        c.define("HAVE_PRINTF_ZD", "1");
        c.define("HAVE_PTHREAD", "1");
        c.define("HAVE_PTHREAD_H", "1");
        c.define("HAVE_READ", "1");
        c.define("HAVE_REALLOC", "1");
        c.define("HAVE_SETENV", "1");
        c.define("HAVE_SETLOCALE", "1");
        c.define("HAVE_SETVBUF", "1");
        c.define("HAVE_SIGNAL_H", "1");
        c.define("HAVE_SNPRINTF", "1");
        c.define("HAVE_SSCANF", "1");
        c.define("HAVE_STAT", "1");
        c.define("HAVE_STDARG_H", "1");
        c.define("HAVE_STDINT_H", "1");
        c.define("HAVE_STDIO_H", "1");
        c.define("HAVE_STDLIB_H", "1");
        c.define("HAVE_STRCASECMP", "1");
        c.define("HAVE_STRCHR", "1");
        c.define("HAVE_STRERROR_R", "1");
        c.define("HAVE_STRINGS_H", "1");
        c.define("HAVE_STRING_H", "1");
        c.define("HAVE_STRLEN", "1");
        c.define("HAVE_STRNCASECMP", "1");
        c.define("HAVE_STRNCMP", "1");
        c.define("HAVE_STRNCPY", "1");
        c.define("HAVE_STRRCHR", "1");
        c.define("HAVE_STRSTR", "1");
        c.define("HAVE_SYS_IOCTL_H", "1");
        c.define("HAVE_SYS_SIGNAL_H", "1");
        c.define("HAVE_SYS_STAT_H", "1");
        c.define("HAVE_SYS_TYPES_H", "1");
        c.define("HAVE_TIME", "1");
        c.define("HAVE_TZSET", "1");
        c.define("HAVE_UNISTD_H", "1");
        c.define("HAVE_UNLINK", "1");
        c.define("HAVE_VFPRINTF", "1");
        c.define("HAVE_VSNPRINTF", "1");
        c.define("HAVE_WCHAR_H", "1");
        c.define("HAVE_WCTYPE_H", "1");
        c.define("HAVE_WRITE", "1");
        c.define("LT_OBJDIR", ".libs/");
        c.define("PACKAGE", "libesedb");
        c.define("PACKAGE_BUGREPORT", "joachim.metz@gmail.com");
        c.define("PACKAGE_NAME", "libesedb");
        c.define("PACKAGE_STRING", "libesedb 20210424");
        c.define("PACKAGE_TARNAME", "libesedb");
        c.define("PACKAGE_URL", "");
        c.define("PACKAGE_VERSION", "20210424");
        c.define("SIZEOF_INT", "4");
        c.define("SIZEOF_LONG", "8");
        c.define("SIZEOF_OFF_T", "8");
        c.define("SIZEOF_SIZE_T", "8");
        c.define("SIZEOF_WCHAR_T", "4");
        c.define("STDC_HEADERS", "1");
        c.define("TIME_WITH_SYS_TIME", "1");
        c.define("VERSION", "20210424");
        c.define("LOCALEDIR", "\"/usr/share/locale\"");
    }

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

    c.compile("esedb");
}

