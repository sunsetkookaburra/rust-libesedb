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
use std::marker::PhantomData;
use std::ptr::null_mut;

use crate::error::ese_result;
use crate::Value;

pub struct LongValue<'a> {
    ptr: *mut libesedb_long_value_t,
    typ: Value,
    _marker: PhantomData<&'a ()>,
}

impl LongValue<'_> {
    pub(crate) fn load<'a>(
        record_handle: *mut libesedb_record_t,
        entry: i32,
    ) -> io::Result<LongValue<'a>> {
        let mut ptr = null_mut();
        ese_result!(
            libesedb_record_get_long_value,
            record_handle,
            entry,
            &mut ptr
        )?;
        let mut typ = 0;
        ese_result!(
            libesedb_record_get_column_type,
            record_handle,
            entry,
            &mut typ
        )?;
        let typ = Value::from_discriminant(typ as _);
        Ok(LongValue::<'a> {
            ptr,
            typ,
            _marker: PhantomData,
        })
    }

    /// Gets an empty [`Value`] representing the type of the data stored in the column.
    pub fn variant(&self) -> Value {
        self.typ.clone()
    }

    pub fn vec(&self) -> io::Result<Vec<u8>> {
        let mut size = 0;
        ese_result!(libesedb_long_value_get_data_size, self.ptr, &mut size)?;
        let mut buf = Vec::with_capacity(size as _);
        ese_result!(
            libesedb_long_value_get_data,
            self.ptr,
            buf.as_mut_ptr(),
            size as _
        )?;
        unsafe { buf.set_len(size as _) };
        Ok(buf)
    }

    pub fn utf8(&self) -> io::Result<String> {
        let mut size = 0;
        ese_result!(
            libesedb_long_value_get_utf8_string_size,
            self.ptr,
            &mut size
        )?;
        let mut text = Vec::with_capacity(size as _);
        ese_result!(
            libesedb_long_value_get_utf8_string,
            self.ptr,
            text.as_mut_ptr(),
            size
        )?;
        unsafe { text.set_len(size as _) };
        text.pop(); // remove nul byte
        String::from_utf8(text).map_err(|e| io::Error::new(io::ErrorKind::Other, e))
    }

    pub fn count_segments(&self) -> io::Result<i32> {
        let mut count = 0;
        ese_result!(
            libesedb_long_value_get_number_of_data_segments,
            self.ptr,
            &mut count
        )?;
        Ok(count)
    }

    pub fn segment(&self, entry: i32) -> io::Result<Vec<u8>> {
        let mut size = 0;
        ese_result!(
            libesedb_long_value_get_data_segment_size,
            self.ptr,
            entry,
            &mut size
        )?;
        let mut buf = Vec::with_capacity(size);
        ese_result!(
            libesedb_long_value_get_data_segment,
            self.ptr,
            entry,
            buf.as_mut_ptr(),
            size
        )?;
        unsafe { buf.set_len(size) };
        Ok(buf)
    }

    pub fn iter_segments(&self) -> io::Result<impl Iterator<Item = io::Result<Vec<u8>>> + '_> {
        Ok((0..self.count_segments()?).map(|i| self.segment(i)))
    }
}

impl Drop for LongValue<'_> {
    fn drop(&mut self) {
        unsafe {
            libesedb_long_value_free(&mut self.ptr, null_mut());
        }
    }
}
