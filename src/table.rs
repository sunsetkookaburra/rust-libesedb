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
use std::io;
use std::marker::PhantomData;
use std::ptr::null_mut;

use crate::column::Column;
use crate::error::with_error;
use crate::iter::{IterEntries, LoadEntry};
use crate::record::Record;

/// Instance of a ESE database table in a currently open [`crate::EseDb`].
pub struct Table<'a> {
    ptr: *mut libesedb_table_t,
    _marker: PhantomData<&'a ()>,
}

impl Table<'_> {
    pub(crate) fn from_name(handle: *mut libesedb_file_t, name: &str) -> io::Result<Self> {
        with_error(|err| unsafe {
            let mut ptr = null_mut();
            (libesedb_file_get_table_by_utf8_name(handle, name.as_ptr(), name.len() as _, &mut ptr, err) == 1).then_some(..)?;
            Some(Self { ptr, _marker: PhantomData })
        })
    }

    /// Gets the name of the table.
    pub fn name(&self) -> io::Result<String> {
        with_error(|err| unsafe {
            let mut size = 0;
            (libesedb_table_get_utf8_name_size(self.ptr, &mut size, err) == 1).then_some(..)?;
            let mut name = vec![0; size as _];
            (libesedb_table_get_utf8_name(self.ptr, name.as_mut_ptr(), size, err) == 1).then_some(..)?;
            name.pop(); // remove null byte
            Some(name)
        }).and_then(|name| {
            String::from_utf8(name).map_err(|e| io::Error::new(io::ErrorKind::Other, e))
        })
    }

    /// Total number of columns in table.
    pub fn count_columns(&self) -> io::Result<i32> {
        with_error(|err| unsafe {
            let mut n = 0;
            (libesedb_table_get_number_of_columns(self.ptr, &mut n, 0, err) == 1).then_some(n)
        })
    }

    /// Total number of records (rows) in table.
    pub fn count_records(&self) -> io::Result<i32> {
        with_error(|err| unsafe {
            let mut n = 0;
            (libesedb_table_get_number_of_records(self.ptr, &mut n, err) == 1).then_some(n)
        })
    }

    /// Load a specific column by entry number.
    /// Returned [`Column`] is bound to the lifetime of the database table.
    pub fn column(&self, entry: i32) -> io::Result<Column> {
        unsafe {
            Column::load(self.ptr, entry)
        }
    }

    /// Load a specific record (row) by entry number.
    /// Returned [`Record`] is bound to the lifetime of the database table.
    pub fn record(&self, entry: i32) -> io::Result<Record> {
        unsafe {
            Record::load(self.ptr, entry)
        }
    }

    /// Create an iterator over all the columns in the table.
    /// The [`IterEntries`] iterator and the returned [`Column`]s
    /// are bound to the lifetime of the database table.
    ///
    /// ```no_run
    /// # use libesedb::EseDb;
    /// # use std::io;
    /// # fn main() -> io::Result<()> {
    /// #     let db = EseDb::open("Catalog1.edb")?;
    /// #     let table = db.table(0)?;
    /// #
    /// for column in table.iter_columns()? {
    ///     println!("{}", column?.name()?);
    /// }
    /// #
    /// #     Ok(())
    /// # }
    /// ```
    pub fn iter_columns(&self) -> io::Result<IterEntries<'_, Column>> {
        Ok(IterEntries::new(self.ptr, self.count_columns()?))
    }

    /// Create an iterator over all the records (rows) in the table.
    /// The [`IterEntries`] iterator and the returned [`Record`]s
    /// are bound to the lifetime of the database table.
    ///
    /// ```no_run
    /// # use libesedb::EseDb;
    /// # use std::io;
    /// # fn main() -> io::Result<()> {
    /// #     let db = EseDb::open("Catalog1.edb")?;
    /// #     let table = db.table(0)?;
    /// #
    /// for record in table.iter_records()? {
    ///     let record = record?;
    ///     for value in record.iter_values()? {
    ///         println!("{:?}", value?);
    ///     }
    /// }
    /// #
    /// #     Ok(())
    /// # }
    /// ```
    pub fn iter_records(&self) -> io::Result<IterEntries<'_, Record>> {
        Ok(IterEntries::new(self.ptr, self.count_records()?))
    }

    /// When done reading, call this to free resources the table is using in memory.
    pub fn close(self) {}
}

impl Drop for Table<'_> {
    fn drop(&mut self) {
        unsafe {
            libesedb_table_free(&mut self.ptr, null_mut());
        }
    }
}

impl LoadEntry for Table<'_> {
    type Handle = libesedb_file_t;

    unsafe fn load(handle: *mut Self::Handle, entry: i32) -> io::Result<Self> {
        with_error(|err| {
            let mut ptr = null_mut();
            (unsafe { libesedb_file_get_table(handle, entry, &mut ptr, err) } == 1)
            .then_some(Self { ptr, _marker: PhantomData })
        })
    }
}
