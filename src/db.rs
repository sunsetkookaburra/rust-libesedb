/*
 * A safe Rust API to libesedb
 *
 * Copyright (C) 2022, Oliver Lenehan ~sunsetkookaburra
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
use std::ffi::CString;
use std::io;
use std::path::Path;
use std::ptr::null_mut;

use crate::error::with_error;
use crate::Table;
use crate::iter::{IterEntries, LoadEntry};

const LIBESEDB_OPEN_READ: LIBESEDB_ACCESS_FLAGS = LIBESEDB_ACCESS_FLAGS_LIBESEDB_ACCESS_FLAG_READ;

/// A loaded instance of an ESE database.
pub struct EseDb {
    ptr: *mut libesedb_file_t,
}

impl EseDb {
    /// Opens an existing ESE database file.
    ///
    /// ```no_run
    /// use libesedb::EseDb;
    /// use std::io;
    ///
    /// fn main() -> io::Result<()> {
    ///     let db = EseDb::open("Catalog1.edb")?;
    ///     // ...
    ///     Ok(())
    /// }
    /// ```
    pub fn open<P: AsRef<Path>>(filename: P) -> io::Result<Self> {
        let filename = CString::new(&*filename.as_ref().to_string_lossy())?;
        with_error(|err| unsafe {
            let mut ptr = null_mut();
            (libesedb_file_initialize(&mut ptr, err) == 1).then(||())?;
            if libesedb_file_open(ptr, filename.as_ptr(), LIBESEDB_OPEN_READ, err) != 1 {
                libesedb_file_free(&mut ptr, null_mut());
                return None
            }
            Some(Self { ptr })
        })
    }

    /// Return underlying pointer for use with `libesedb-sys`.
    pub fn as_mut_ptr(&mut self) -> *mut libesedb_table_t {
        self.ptr
    }

    /// Load a specific table by entry number.
    /// Returned [`Table`] is bound to the lifetime of the database.
    pub fn table<'a>(&'a self, entry: i32) -> io::Result<Table<'a>> {
        unsafe {
            Table::load(self.ptr, entry)
        }
    }

    /// Load a specific table by name.
    /// Returned [`Table`] is bound to the lifetime of the database.
    pub fn table_by_name<'a>(&'a self, name: &str) -> io::Result<Table<'a>> {
        Table::from_name(self.ptr, name)
    }

    /// Total number of tables in ESE database.
    pub fn count_tables(&self) -> io::Result<i32> {
        with_error(|err| unsafe {
            let mut n = 0;
            (libesedb_file_get_number_of_tables(self.ptr, &mut n, err) == 1)
            .then(|| n)
        })
    }

    /// Create an iterator over all the tables in the database.
    /// The [`IterEntries`] iterator and the returned [`Table`]s
    /// are bound to the lifetime of the database.
    ///
    /// ```no_run
    /// # use libesedb::EseDb;
    /// # use std::io;
    /// # fn main() -> io::Result<()> {
    /// #     let db = EseDb::open("Catalog1.edb")?;
    /// #
    /// for table in db.iter_tables()? {
    ///     let table = table?;
    ///     println!("{}", table.name()?);
    /// }
    /// #
    /// #     Ok(())
    /// # }
    /// ```
    pub fn iter_tables<'a>(&'a self) -> io::Result<IterEntries<'a, Table<'a>>> {
        Ok(IterEntries::new(self.ptr, self.count_tables()?))
    }
}

impl Drop for EseDb {
    fn drop(&mut self) {
        unsafe {
            libesedb_file_free(&mut self.ptr, null_mut());
        }
    }
}
