/*
 * A safe Rust API to libesedb
 *
 * Copyright (C) 2022-2024, Oliver Lenehan ~sunsetkookaburra
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

use libesedb_sys::*;
use std::io;

fn error_string(error: *mut libesedb_error_t) -> String {
    let mut buf = vec![0u8; 4096];
    let n = unsafe { libesedb_error_sprint(error, buf.as_mut_ptr() as _, buf.len() as _) };
    if n == -1 {
        return String::from("Error retrieving error string");
    }
    buf.truncate(buf.iter().position(|&x| x == 0).unwrap_or(n as usize - 1));
    String::from_utf8(buf).unwrap_or(String::from("Error text contained invalid UTF-8"))
}

fn error_backtrace_string(error: *mut libesedb_error_t) -> String {
    let mut buf = vec![0u8; 4096];
    let n =
        unsafe { libesedb_error_backtrace_sprint(error, buf.as_mut_ptr() as _, buf.len() as _) };
    if n == -1 {
        return String::from("Error retrieving error backtrace string");
    }
    buf.truncate(buf.iter().position(|&x| x == 0).unwrap_or(n as usize - 1));
    String::from_utf8(buf).unwrap_or(String::from("Error backtrace text contained invalid UTF-8"))
}

pub(crate) fn ese_error(error: *mut *mut libesedb_error_t) -> io::Error {
    let err = io::Error::new(
        io::ErrorKind::Other,
        // error_string(unsafe { *error })
        format!(
            "c-libesedb: {}\n{}",
            error_string(unsafe { *error }),
            error_backtrace_string(unsafe { *error })
        ),
    );
    unsafe {
        libesedb_error_free(error);
    }
    err
}

macro_rules! ese_result {
    ($fn_name:ident, $($args:expr),*) => ({
        let mut error: *mut libesedb_error_t = ::std::ptr::null_mut();
        let result = unsafe { $fn_name($($args),*, &mut error) };
        if -1 == result {
            Err(if error.is_null() {
                io::Error::new(io::ErrorKind::Other, format!("rust-libesedb: Unexpected error when calling C function '{}'", stringify!($fn_name)))
            } else {
                $crate::error::ese_error(&mut error)
            })
        } else {
            Ok(result)
        }
    });
}

pub(crate) use ese_result;
