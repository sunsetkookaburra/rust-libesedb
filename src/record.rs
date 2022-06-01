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

pub struct Record<'a> {
    ptr: *mut libesedb_record_t,
    _marker: PhantomData<&'a ()>,
}

impl Record<'_> {
    pub fn value(&self, entry: i32) -> io::Result<Value> {
        Value::load(self.ptr, entry)
    }

    pub fn count_values(&self) -> io::Result<i32> {
        with_error(|err| unsafe {
            let mut n = 0;
            (libesedb_record_get_number_of_values(self.ptr, &mut n, err) == 1)
            .then(|| n)
        })
    }

    pub fn iter_values(&self) -> io::Result<IterEntries<'_, Value>> {
        Ok(IterEntries::new(self.ptr, self.count_values()?))
    }

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

    fn load(handle: *mut Self::Handle, entry: i32) -> io::Result<Self> {
        with_error(|err| unsafe {
            let mut ptr = null_mut();
            (libesedb_table_get_record(handle, entry, &mut ptr, err) == 1)
            .then(|| Self { ptr, _marker: PhantomData })
        })
    }
}
