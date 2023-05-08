/*
 * A safe Rust API to libesedb
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

use libesedb_sys::*;
use std::io;
use std::marker::PhantomData;
use std::ptr::null_mut;

use crate::error::ese_assert_cfn;
use crate::Value;

/// Instance of a ESE database column in a currently open [`crate::Table`].
pub struct Column<'a> {
    ptr: *mut libesedb_column_t,
    _marker: PhantomData<&'a ()>,
}

impl Column<'_> {
    /// Gets the name of the column.
    pub fn name(&self) -> io::Result<String> {
        let mut size = 0;
        ese_assert_cfn(
            |err| unsafe { libesedb_column_get_utf8_name_size(self.ptr, &mut size, err) == 1 },
            format_args!("libesedb_column_get_utf8_name_size"),
        )?;
        let mut name = Vec::with_capacity(size as _);
        ese_assert_cfn(
            |err| unsafe {
                libesedb_column_get_utf8_name(self.ptr, name.as_mut_ptr(), size, err) == 1
            },
            format_args!("libesedb_column_get_utf8_name"),
        )?;
        name.pop();
        String::from_utf8(name).map_err(|e| io::Error::new(io::ErrorKind::Other, e))
    }

    /// Gets the entry id of the column.
    pub fn id(&self) -> io::Result<u32> {
        let mut id = 0;
        ese_assert_cfn(
            |err| unsafe { libesedb_column_get_identifier(self.ptr, &mut id, err) == 1 },
            format_args!("libesedb_column_get_identifier"),
        )?;
        Ok(id)
    }

    /// Gets an empty [`Value`] representing the type of the data stored in the column.
    pub fn variant(&self) -> io::Result<Value> {
        let mut typ = 0;
        ese_assert_cfn(
            |err| unsafe { libesedb_column_get_type(self.ptr, &mut typ, err) == 1 },
            format_args!("libesedb_column_get_type"),
        )?;
        Ok(Value::from_discriminant(typ as _))
    }

    /// When done reading, call this to free resources the column is using in memory.
    pub fn close(self) {}

    pub(crate) fn load<'a>(
        table_handle: *mut libesedb_table_t,
        entry: i32,
    ) -> io::Result<Column<'a>> {
        let mut ptr = null_mut();
        ese_assert_cfn(
            |err| unsafe { libesedb_table_get_column(table_handle, entry, &mut ptr, 0, err) == 1 },
            format_args!("libesedb_table_get_column"),
        )?;
        Ok(Column::<'a> {
            ptr,
            _marker: PhantomData,
        })
    }
}

impl Drop for Column<'_> {
    fn drop(&mut self) {
        // Safety:
        //   libesedb_column.c::libesedb_column_free only fails if &mut self.ptr is null,
        //   but this can never hold since it references valid memory
        unsafe {
            libesedb_column_free(&mut self.ptr, null_mut());
        }
    }
}
