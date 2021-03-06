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

use std::{io, marker::PhantomData};

pub trait LoadEntry: Sized {
    type Handle;
    fn load(handle: *mut Self::Handle, entry: i32) -> io::Result<Self>;
}

pub struct IterEntries<'a, T: LoadEntry> {
    handle: *mut T::Handle,
    pos: i32,
    max: i32,
    _marker: PhantomData<&'a T>,
}

impl<T: LoadEntry> IterEntries<'_, T> {
    pub fn new(handle: *mut T::Handle, max: i32) -> Self {
        Self { handle, pos: 0, max, _marker: PhantomData }
    }
}

impl<T: LoadEntry> Iterator for IterEntries<'_, T> {
    type Item = io::Result<T>;

    fn next(&mut self) -> Option<Self::Item> {
        if self.pos < self.max {
            let val = T::load(self.handle, self.pos);
            self.pos += 1;
            Some(val)
        } else {
            None
        }
    }
}
