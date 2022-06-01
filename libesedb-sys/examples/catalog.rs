/*
Adapted from:
https://github.com/libyal/libesedb/wiki/C-development
*/

use std::env;
use std::ffi::CString;
use std::process::exit;
use std::ptr::null_mut;

use libesedb_sys::*;

fn main() {
    const LIBESEDB_OPEN_READ: LIBESEDB_ACCESS_FLAGS =
        LIBESEDB_ACCESS_FLAGS_LIBESEDB_ACCESS_FLAG_READ;

    unsafe {
        let mut error: *mut libesedb_error_t = null_mut();
        let mut file: *mut libesedb_file_t = null_mut();

        if libesedb_file_initialize(&mut file, &mut error) != 1 {
            eprintln!("Unable to initialize file.");
            libesedb_error_free(&mut error);
            exit(1);
        }

        let filename = CString::new(env::args().nth(1).unwrap_or("Windows.edb".to_string())).unwrap();

        if libesedb_file_open(file, filename.as_ptr() as _, LIBESEDB_OPEN_READ, &mut error) != 1 {
            eprintln!("Unable to open file.");
            libesedb_file_free(&mut file, null_mut());
            libesedb_error_free(&mut error);
            exit(1);
        }

        let mut number_of_tables = 0;

        if libesedb_file_get_number_of_tables(file, &mut number_of_tables, &mut error) != 1 {
            eprintln!("Unable to retrieve number of tables.");
            libesedb_error_free(&mut error);
        }

        println!("There are {number_of_tables} tables.");

        let mut table: *mut libesedb_table_t = null_mut();

        if libesedb_file_get_table(file, 0, &mut table, &mut error) != 1 {
            eprintln!("Unable to retrieve table: 0");
            libesedb_error_free(&mut error);
        }

        let mut table_name_size = 0;

        if libesedb_table_get_utf8_name_size(table, &mut table_name_size, &mut error) != 1 {
            eprintln!("Unable to get table name size.");
            libesedb_error_free(&mut error);
        }

        println!("The table name (including null byte) takes up {table_name_size} bytes.");

        let mut table_name = vec![0; table_name_size.try_into().unwrap()];
        if libesedb_table_get_utf8_name(table, table_name.as_mut_ptr(), table_name.len().try_into().unwrap(), &mut error) != 1 {
            eprintln!("Unable to get table name.");
            libesedb_error_free(&mut error);
        }

        println!("Table Name: {}", CString::from_vec_with_nul(table_name).unwrap().to_str().unwrap());

        if libesedb_file_close(file, &mut error) != 0 {
            eprintln!("Unable to close file.");
            libesedb_file_free(&mut file, null_mut());
            libesedb_error_free(&mut error);
            exit(1);
        }
    }
}
