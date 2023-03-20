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

use crate::error::with_error;
use crate::iter::{LoadEntry, IterEntries};
use crate::value::Value;

/// Instance of a ESE database record in a currently open [`crate::Table`].
pub struct Record<'a> {
    ptr: *mut libesedb_record_t,
    _marker: PhantomData<&'a ()>,
}

impl Record<'_> {
    /// Load a specific column/field value by entry number.
    /// Returned [`Value`] is bound to the lifetime of the database record.
    pub fn value(&self, entry: i32) -> io::Result<Value> {
        unsafe {
            Value::load(self.ptr, entry)
        }
    }

    /// Returns number of values (columns/fields) in the record.
    pub fn count_values(&self) -> io::Result<i32> {
        with_error(|err| unsafe {
            let mut n = 0;
            (libesedb_record_get_number_of_values(self.ptr, &mut n, err) == 1)
            .then(|| n)
        })
    }

    /// Create an iterator over all the (column/field) values in the table record.
    /// The [`IterEntries`] iterator and the returned [`Value`]s
    /// are bound to the lifetime of the database record.
    ///
    /// ```no_run
    /// # use libesedb::EseDb;
    /// # use std::io;
    /// # fn main() -> io::Result<()> {
    /// #     let db = EseDb::open("Catalog1.edb")?;
    /// #     let table = db.table(0)?;
    /// #     let record = table.record(0)?;
    /// #
    /// for value in record.iter_values()? {
    ///     println!("{:?}", value?);
    /// }
    /// #
    /// #     Ok(())
    /// # }
    /// ```
    pub fn iter_values(&self) -> io::Result<IterEntries<'_, Value>> {
        Ok(IterEntries::new(self.ptr, self.count_values()?))
    }

    /// When done reading, call this to free resources the record is using in memory.
    pub fn close(self) {}
}

impl Drop for Record<'_> {
    fn drop(&mut self) {
        unsafe {
            libesedb_record_free(&mut self.ptr, null_mut());
        }
    }
}

impl LoadEntry for Record<'_> {
    type Handle = libesedb_table_t;

    unsafe fn load(handle: *mut Self::Handle, entry: i32) -> io::Result<Self> {
        with_error(|err| unsafe {
            let mut ptr = null_mut();
            (libesedb_table_get_record(handle, entry, &mut ptr, err) == 1)
            .then(|| Self { ptr, _marker: PhantomData })
        })
    }
}
