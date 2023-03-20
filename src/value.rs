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
use std::time::SystemTime;

use crate::datatype::{FileTime, OleTime};
use crate::error::with_error;
use crate::iter::LoadEntry;

macro_rules! column_variants {
    (
        $(
            $(#[$attr:ident $($args:tt)*])*
            $name:ident ($(@$l:lifetime)? $t:ty) = $e:ident
        ),*$(,)?
        ;
        $(
            $($from:ident),+ => $intofn:ident $into:ty
        ),*$(,)?
        ;
        $(
            $($fromref:ident),+ => $reffn:ident $intoref:ty
        ),*$(,)?
    ) => {
        #[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
        #[repr(i32)]
        pub enum ColumnVariant {
            $(
                $(#[$attr $($args)*])*
                $name = $e
            ),*
        }

        impl From<i32> for ColumnVariant {
            fn from(x: i32) -> Self {
                match x {
                    $( $e => Self::$name, )*
                    _ => panic!("Unknown column type {x}")
                }
            }
        }

        impl From<u32> for ColumnVariant {
            fn from(x: u32) -> Self {
                (x as i32).into()
            }
        }

        impl From<&Value> for ColumnVariant {
            fn from(value: &Value) -> Self {
                match value {
                    $( Value::$name(_) => Self::$name, )*
                }
            }
        }

        #[derive(Debug, PartialEq, PartialOrd)]
        #[repr(i32)]
        pub enum Value {
            $(
                $(#[$attr $($args)*])*
                $name($t) = $e
            ),*
        }

        impl Value {
            $(
            pub fn $intofn(&self) -> Option<$into> {
                match self {
                    $(Self::$from(x) => (*x).try_into().ok()),+,
                    _ => None,
                }
            }
            )*

            $(
            pub fn $reffn(&self) -> Option<&$intoref> {
                match self {
                    $(Self::$fromref(x) => Some(x)),+,
                    _ => None,
                }
            }
            )*
        }

        $(
        impl PartialEq<$into> for Value {
            fn eq(&self, rhs: &$into) -> bool {
                self.$intofn() == Some(*rhs)
            }
        }
        impl PartialEq<Value> for $into {
            fn eq(&self, rhs: &Value) -> bool {
                rhs == self
            }
        }
        )*

        $(
        impl PartialEq<$intoref> for Value {
            fn eq(&self, rhs: &$intoref) -> bool {
                self.$reffn() == Some(rhs)
            }
        }
        impl PartialEq<Value> for $intoref {
            fn eq(&self, rhs: &Value) -> bool {
                rhs == self
            }
        }
        )*

        impl PartialEq<SystemTime> for Value {
            fn eq(&self, rhs: &SystemTime) -> bool {
                self.to_filetime() == Some((*rhs).into())
            }
        }
        impl PartialEq<Value> for SystemTime {
            fn eq(&self, rhs: &Value) -> bool {
                rhs == self
            }
        }
        impl PartialOrd<SystemTime> for Value {
            fn partial_cmp(&self, other: &SystemTime) -> Option<std::cmp::Ordering> {
                self.to_filetime().and_then(|t| t.partial_cmp(other))
            }
        }
        impl PartialOrd<Value> for SystemTime {
            fn partial_cmp(&self, other: &Value) -> Option<std::cmp::Ordering> {
                other.partial_cmp(self)
            }
        }
    }
}

column_variants! {
    Null(()) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_NULL,
    Bool(bool) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_BOOLEAN,
    U8(u8) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_8BIT_UNSIGNED,
    I16(i16) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_16BIT_SIGNED,
    I32(i32) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_32BIT_SIGNED,
    Currency(i64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_CURRENCY,
    F32(f32) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_FLOAT_32BIT,
    F64(f64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_DOUBLE_64BIT,
    /// FILETIME format: little-endian 64bit 100-nanosecond intervals since 1 jan 1601 UTC
    DateTime(u64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_DATE_TIME,
    Binary(Vec<u8>) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_BINARY_DATA,
    Text(String) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_TEXT,
    LargeBinary(Vec<u8>) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_LARGE_BINARY_DATA,
    LargeText(String) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_LARGE_TEXT,
    SuperLarge(Vec<u8>) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_SUPER_LARGE_VALUE,
    U32(u32) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_32BIT_UNSIGNED,
    I64(i64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_64BIT_SIGNED,
    /// 16 byte value
    Guid(Vec<u8>) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_GUID,
    U16(u16) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_16BIT_UNSIGNED,
    ; // Primitive casts
    Bool => to_bool bool,
    U8, U16, U32, I16, I32, I64, Currency => to_u8 u8,
    U8, U16, U32, I16, I32, I64, Currency => to_u16 u16,
    U8, U16, U32, I16, I32, I64, Currency => to_u32 u32,
    U8, U16, U32, I16, I32, I64, Currency, DateTime => to_u64 u64,
    U8, U16, U32, I16, I32, I64, Currency => to_i16 i16,
    U8, U16, U32, I16, I32, I64, Currency => to_i32 i32,
    U8, U16, U32, I16, I32, I64, Currency => to_i64 i64,
    U8, U16, I16, F32 => to_f32 f32,
    U8, U16, U32, I16, I32, F32, F64 => to_f64 f64,
    ; // References to inside
    Binary, LargeBinary, SuperLarge, Guid => as_bytes [u8],
    Text, LargeText => as_str str,
}

impl Value {
    pub fn to_filetime(&self) -> Option<FileTime> {
        match self {
            Self::DateTime(x) => Some(FileTime::from_100ns(*x)),
            _ => None
        }
    }

    pub fn to_oletime(&self) -> Option<OleTime> {
        match self {
            Self::DateTime(x) => Some(OleTime::from_days(f64::from_bits(*x))),
            _ => None
        }
    }

    pub fn variant(&self) -> ColumnVariant {
        self.into()
    }
}

impl Default for Value {
    fn default() -> Self {
        Self::Null(())
    }
}

impl ToString for Value {
    fn to_string(&self) -> String {
        match self {
            Value::Null(()) => String::from("NULL"),
            Value::Bool(x) => x.to_string(),
            Value::U8(x) => x.to_string(),
            Value::I16(x) => x.to_string(),
            Value::I32(x) => x.to_string(),
            Value::Currency(x) => x.to_string(),
            Value::F32(x) => x.to_string(),
            Value::F64(x) => x.to_string(),
            Value::DateTime(x) => x.to_string(),
            Value::Binary(b) | Value::LargeBinary(b) | Value::SuperLarge(b) => b
                .iter()
                .map(|x| format!("{x:02x}"))
                .collect::<Vec<_>>()
                .join(" "),
            Value::Text(x) => x.to_string(),
            Value::LargeText(x) => x.to_string(),
            Value::U32(x) => x.to_string(),
            Value::I64(x) => x.to_string(),
            Value::Guid(b) => {
                format!(
                    "{:02x}{:02x}{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}",
                    b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7],
                    b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15],
                )
            }
            Value::U16(x) => x.to_string(),
        }
    }
}

impl LoadEntry for Value {
    type Handle = libesedb_record_t;

    unsafe fn load(handle: *mut Self::Handle, entry: i32) -> io::Result<Value> {
        with_error(|err| unsafe {
            let mut raw_column_type = 0;
            // Short circuit return if result != 1
            (libesedb_record_get_column_type(handle, entry, &mut raw_column_type, err) == 1)
                .then(|| ())?;
            let column_type: ColumnVariant = raw_column_type.into();
            Some(match column_type {
                ColumnVariant::Null => Self::Null(()),
                ColumnVariant::Bool => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_boolean(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null(()),
                        1 => Self::Bool(value != 0),
                        _ => return None,
                    }
                }
                ColumnVariant::U8 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_8bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null(()),
                        1 => Self::U8(value),
                        _ => return None,
                    }
                }
                ColumnVariant::I16 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_16bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null(()),
                        1 => Self::I16(value as i16),
                        _ => return None,
                    }
                }
                ColumnVariant::I32 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_32bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null(()),
                        1 => Self::I32(value as i32),
                        _ => return None,
                    }
                }
                ColumnVariant::Currency => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_64bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null(()),
                        1 => Self::Currency(value as i64),
                        _ => return None,
                    }
                }
                ColumnVariant::F32 => {
                    let mut value = 0.0;
                    let result = libesedb_record_get_value_floating_point_32bit(
                        handle, entry, &mut value, err,
                    );
                    match result {
                        0 => Self::Null(()),
                        1 => Self::F32(value),
                        _ => return None,
                    }
                }
                ColumnVariant::F64 => {
                    let mut value = 0.0;
                    let result = libesedb_record_get_value_floating_point_64bit(
                        handle, entry, &mut value, err,
                    );
                    match result {
                        0 => Self::Null(()),
                        1 => Self::F64(value),
                        _ => return None,
                    }
                }
                ColumnVariant::DateTime => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_filetime(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null(()),
                        1 => Self::DateTime(value),
                        _ => return None,
                    }
                }
                c @ (ColumnVariant::Binary | ColumnVariant::LargeBinary) => {
                    let mut size = 0;
                    let result =
                        libesedb_record_get_value_binary_data_size(handle, entry, &mut size, err);
                    match result {
                        0 => Self::Null(()),
                        1 => {
                            let mut data = vec![0; size as _];
                            let result = libesedb_record_get_value_binary_data(
                                handle,
                                entry,
                                data.as_mut_ptr(),
                                size,
                                err,
                            );
                            match result {
                                0 => Self::Null(()),
                                1 => match c {
                                    ColumnVariant::Binary => Self::Binary(data),
                                    ColumnVariant::LargeBinary => Self::LargeBinary(data),
                                    _ => unreachable!(),
                                },
                                _ => return None,
                            }
                        }
                        _ => return None,
                    }
                }
                c @ (ColumnVariant::Text | ColumnVariant::LargeText) => {
                    let mut size = 0;
                    let result =
                        libesedb_record_get_value_utf8_string_size(handle, entry, &mut size, err);
                    match result {
                        0 => Self::Null(()),
                        1 => {
                            let mut data = vec![0; size as _];
                            let result = libesedb_record_get_value_utf8_string(
                                handle,
                                entry,
                                data.as_mut_ptr(),
                                size,
                                err,
                            );
                            match result {
                                0 => Self::Null(()),
                                1 => {
                                    data.pop(); // remove null byte
                                    let text = String::from_utf8_lossy(&data).into();
                                    match c {
                                        ColumnVariant::Text => Self::Text(text),
                                        ColumnVariant::LargeText => Self::LargeText(text),
                                        _ => unreachable!(),
                                    }
                                }
                                _ => return None,
                            }
                        }
                        _ => return None,
                    }
                }
                c @ (ColumnVariant::SuperLarge | ColumnVariant::Guid) => {
                    let mut size = 0;
                    let result = libesedb_record_get_value_data_size(handle, entry, &mut size, err);
                    match result {
                        1 => {
                            let mut data = vec![0; size as _];
                            let result = libesedb_record_get_value_data(
                                handle,
                                entry,
                                data.as_mut_ptr(),
                                size,
                                err,
                            );
                            match result {
                                1 => match c {
                                    ColumnVariant::SuperLarge => Self::SuperLarge(data),
                                    ColumnVariant::Guid => Self::Guid(data),
                                    _ => unreachable!(),
                                },
                                _ => return None,
                            }
                        }
                        _ => return None,
                    }
                }
                ColumnVariant::U32 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_32bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null(()),
                        1 => Self::U32(value),
                        _ => return None,
                    }
                }
                ColumnVariant::I64 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_64bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null(()),
                        1 => Self::I64(value as i64),
                        _ => return None,
                    }
                }
                ColumnVariant::U16 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_16bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null(()),
                        1 => Self::U16(value),
                        _ => return None,
                    }
                }
            })
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::time::SystemTime;

    #[test]
    fn value_compare() {
        let date = SystemTime::UNIX_EPOCH;
        assert_eq!(date, Value::DateTime(116444736000000000).to_filetime().unwrap());
        assert_eq!(Value::DateTime(116444736000000000).to_filetime().unwrap(), date);
        assert_eq!(42, Value::U8(42));
        assert_eq!(Value::U8(42), 42u8);
    }
}
