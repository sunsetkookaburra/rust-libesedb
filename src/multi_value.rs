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

pub struct MultiValue<'a> {
    ptr: *mut libesedb_multi_value_t,
    typ: Value,
    _marker: PhantomData<&'a ()>,
}

impl MultiValue<'_> {
    pub(crate) fn load<'a>(
        record_handle: *mut libesedb_record_t,
        entry: i32,
    ) -> io::Result<MultiValue<'a>> {
        let mut ptr = null_mut();
        ese_result!(
            libesedb_record_get_multi_value,
            record_handle,
            entry,
            &mut ptr
        )?;
        let mut typ = 0;
        ese_result!(libesedb_multi_value_get_column_type, ptr, &mut typ)?;
        let typ = Value::from_discriminant(typ as _);
        Ok(MultiValue::<'a> {
            ptr,
            typ,
            _marker: PhantomData,
        })
    }

    /// Gets an empty [`Value`] representing the type of the data stored in the column.
    pub fn variant(&self) -> Value {
        self.typ.clone()
    }

    pub fn count_values(&self) -> io::Result<i32> {
        let mut count = 0;
        ese_result!(
            libesedb_multi_value_get_number_of_values,
            self.ptr,
            &mut count
        )?;
        Ok(count)
    }

    pub fn iter_values(&self) -> io::Result<impl Iterator<Item = io::Result<Value>> + '_> {
        Ok((0..self.count_values()?).map(|i| self.value(i)))
    }

    pub fn value(&self, entry: i32) -> io::Result<Value> {
        Ok(match self.typ {
            Value::Null(_) => Value::Null(()),
            Value::Bool(_) => {
                let mut value = 0;
                ese_result!(
                    libesedb_multi_value_get_value_8bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::Bool(value != 0)
            }
            Value::U8(_) => {
                let mut value = 0;
                ese_result!(
                    libesedb_multi_value_get_value_8bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::U8(value)
            }
            Value::I16(_) => {
                let mut value = 0;
                ese_result!(
                    libesedb_multi_value_get_value_16bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::I16(value as _)
            }
            Value::I32(_) => {
                let mut value = 0;
                ese_result!(
                    libesedb_multi_value_get_value_32bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::I32(value as _)
            }
            Value::Currency(_) => {
                let mut value = 0;
                ese_result!(
                    libesedb_multi_value_get_value_64bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::Currency(value as _)
            }
            Value::F32(_) => {
                let mut value = 0.0;
                ese_result!(
                    libesedb_multi_value_get_value_floating_point_32bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::F32(value)
            }
            Value::F64(_) => {
                let mut value = 0.0;
                ese_result!(
                    libesedb_multi_value_get_value_floating_point_64bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::F64(value)
            }
            Value::DateTime(_) => {
                let mut value = 0;
                ese_result!(
                    libesedb_multi_value_get_value_filetime,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::DateTime(value)
            }
            Value::Binary(_) => {
                let mut size = 0;
                ese_result!(
                    libesedb_multi_value_get_value_binary_data_size,
                    self.ptr,
                    entry,
                    &mut size
                )?;
                let mut buf = vec![0; size as _];
                ese_result!(
                    libesedb_multi_value_get_value_binary_data,
                    self.ptr,
                    entry,
                    buf.as_mut_ptr(),
                    size
                )?;
                Value::Binary(buf)
            }
            Value::Text(_) => {
                let mut size = 0;
                ese_result!(
                    libesedb_multi_value_get_value_utf8_string_size,
                    self.ptr,
                    entry,
                    &mut size
                )?;
                let mut buf = vec![0; size as _];
                ese_result!(
                    libesedb_multi_value_get_value_utf8_string,
                    self.ptr,
                    entry,
                    buf.as_mut_ptr(),
                    size
                )?;
                buf.pop(); // remove nul byte
                Value::Text(
                    String::from_utf8(buf).map_err(|e| io::Error::new(io::ErrorKind::Other, e))?,
                )
            }
            Value::LargeBinary(_) => {
                let mut size = 0;
                ese_result!(
                    libesedb_multi_value_get_value_binary_data_size,
                    self.ptr,
                    entry,
                    &mut size
                )?;
                let mut buf = vec![0; size as _];
                ese_result!(
                    libesedb_multi_value_get_value_binary_data,
                    self.ptr,
                    entry,
                    buf.as_mut_ptr(),
                    size
                )?;
                Value::LargeBinary(buf)
            }
            Value::LargeText(_) => {
                let mut size = 0;
                ese_result!(
                    libesedb_multi_value_get_value_utf8_string_size,
                    self.ptr,
                    entry,
                    &mut size
                )?;
                let mut buf = vec![0; size as _];
                ese_result!(
                    libesedb_multi_value_get_value_utf8_string,
                    self.ptr,
                    entry,
                    buf.as_mut_ptr(),
                    size
                )?;
                buf.pop(); // remove nul byte
                Value::LargeText(
                    String::from_utf8(buf).map_err(|e| io::Error::new(io::ErrorKind::Other, e))?,
                )
            }
            Value::SuperLarge(_) => {
                let mut size = 0;
                ese_result!(
                    libesedb_multi_value_get_value_data_size,
                    self.ptr,
                    entry,
                    &mut size
                )?;
                let mut buf = vec![0; size as _];
                ese_result!(
                    libesedb_multi_value_get_value_data,
                    self.ptr,
                    entry,
                    buf.as_mut_ptr(),
                    size
                )?;
                Value::SuperLarge(buf)
            }
            Value::U32(_) => {
                let mut value = 0;
                ese_result!(
                    libesedb_multi_value_get_value_32bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::I32(value as _)
            }
            Value::I64(_) => {
                let mut value = 0;
                ese_result!(
                    libesedb_multi_value_get_value_64bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::Currency(value as _)
            }
            Value::Guid(_) => {
                let mut size = 0;
                ese_result!(
                    libesedb_multi_value_get_value_data_size,
                    self.ptr,
                    entry,
                    &mut size
                )?;
                let mut buf = vec![0; size as _];
                ese_result!(
                    libesedb_multi_value_get_value_data,
                    self.ptr,
                    entry,
                    buf.as_mut_ptr(),
                    size
                )?;
                Value::Guid(buf)
            }
            Value::U16(_) => {
                let mut value = 0;
                ese_result!(
                    libesedb_multi_value_get_value_16bit,
                    self.ptr,
                    entry,
                    &mut value
                )?;
                Value::U16(value)
            }
            Value::Long => unreachable!(),
            Value::Multi => unreachable!(),
        })
    }
}

impl Drop for MultiValue<'_> {
    fn drop(&mut self) {
        unsafe {
            libesedb_multi_value_free(&mut self.ptr, null_mut());
        }
    }
}
