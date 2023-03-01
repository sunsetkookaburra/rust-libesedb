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
use crate::iter::LoadEntry;
use crate::value::ColumnVariant;

/// Instance of a ESE database column in a currently open [`Table`].
pub struct Column<'a> {
    ptr: *mut libesedb_column_t,
    _marker: PhantomData<&'a ()>,
}

impl Column<'_> {
    /// Gets the name of the column.
    pub fn name(&self) -> io::Result<String> {
        with_error(|err| unsafe {
            let mut size = 0;
            (libesedb_column_get_utf8_name_size(self.ptr, &mut size, err) == 1).then(||())?;
            let mut name = vec![0; size as _];
            (libesedb_column_get_utf8_name(self.ptr, name.as_mut_ptr(), size, err) == 1).then(||())?;
            name.pop(); // remove null byte
            Some(name)
        }).and_then(|name| {
            String::from_utf8(name).map_err(|e| io::Error::new(io::ErrorKind::Other, e))
        })
    }

    /// Gets the entry id of the column.
    pub fn id(&self) -> io::Result<u32> {
        with_error(|err| unsafe {
            let mut id = 0;
            (libesedb_column_get_identifier(self.ptr, &mut id, err) == 1)
            .then(|| id)
        })
    }

    /// Gets the type of the data stored in the column.
    pub fn variant(&self) -> io::Result<ColumnVariant> {
        with_error(|err| unsafe {
            let mut typ = 0;
            (libesedb_column_get_type(self.ptr, &mut typ, err) == 1).then(||())?;
            Some(typ.into())
        })
    }

    /// When done reading, call this to free resources the column is using in memory.
    pub fn close(self) {}
}

impl Drop for Column<'_> {
    fn drop(&mut self) {
        unsafe {
            libesedb_column_free(&mut self.ptr, null_mut());
        }
    }
}

impl LoadEntry for Column<'_> {
    type Handle = libesedb_column_t;

    fn load(handle: *mut Self::Handle, entry: i32) -> io::Result<Self> {
        with_error(|err| unsafe {
            let mut ptr = null_mut();
            (libesedb_table_get_column(handle as _, entry, &mut ptr, 0, err) == 1)
            .then(|| Self { ptr, _marker: PhantomData })
        })
    }
}
