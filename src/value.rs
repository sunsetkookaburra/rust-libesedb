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
use std::error::Error;
use std::fmt::Display;
use std::io;

use crate::datatype::{FileTime, OleTime};
use crate::error::with_error;
use crate::iter::LoadEntry;

#[derive(Debug)]
pub struct ValueTryFromError(String, String);

impl Display for ValueTryFromError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "libesedb::Value cannot convert {} into {}", self.0, self.1)
    }
}

impl Error for ValueTryFromError {}

macro_rules! column_variants {
    (
        $(
            $(#[$attr:ident $($args:tt)*])*
            $name:ident $(($p:pat_param, $t:ty))? = $e:ident
        ),*$(,)?
        ;
        $(
            $($from:ident),+ => $into:ty
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
                    $( Value::$name$(($p))? => Self::$name, )*
                }
            }
        }

        #[derive(Debug, PartialEq, PartialOrd)]
        #[repr(i32)]
        pub enum Value {
            $(
                $(#[$attr $($args)*])*
                $name$(($t))? = $e
            ),*
        }

        $(
        impl TryFrom<Value> for $into {
            type Error = ValueTryFromError;

            fn try_from(value: Value) -> Result<Self, Self::Error> {
                match value {
                    $(Value::$from(x) => Ok(x.try_into().map_err(|e| ValueTryFromError(format!("one of {} ({e})", stringify!($from)), stringify!($into).into()))?),)+
                    _ => Err(ValueTryFromError(format!("{value:?}"), stringify!($into).into()))
                }
            }
        }

        impl<'a> TryFrom<&'a Value> for &'a $into {
            type Error = ValueTryFromError;

            fn try_from(value: &'a Value) -> Result<Self, Self::Error> {
                match value {
                    $(Value::$from(ref x) => Ok(x.try_into().map_err(|e| ValueTryFromError(format!("one of {} ({e})", stringify!($from,+)), stringify!($into).into()))?),)+
                    _ => Err(ValueTryFromError(format!("{value:?}"), stringify!($into).into()))
                }
            }
        }

        impl PartialEq<$into> for Value {
            fn eq(&self, other: &$into) -> bool {
                // println!("{}", );
                self.try_into().ok() == Some(other)
            }
        }

        impl PartialEq<Value> for $into {
            fn eq(&self, other: &Value) -> bool {
                other == self
            }
        }
        )*
    }
}

impl<'a> TryFrom<&'a Value> for u16 {
    type Error = ValueTryFromError;

    fn try_from(value: &'a Value) -> Result<Self, Self::Error> {
        match value {
            Value::U8(x) => Ok((*x).into()),
            _ => Ok(12)
        }
    }
}

column_variants! {
    Null = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_NULL,
    Bool(_, bool) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_BOOLEAN,
    U8(_, u8) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_8BIT_UNSIGNED,
    I16(_, i16) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_16BIT_SIGNED,
    I32(_, i32) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_32BIT_SIGNED,
    Currency(_, i64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_CURRENCY,
    F32(_, f32) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_FLOAT_32BIT,
    F64(_, f64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_DOUBLE_64BIT,
    /// FILETIME format: little-endian 64bit 100-nanosecond intervals since 1 jan 1601 UTC
    DateTime(_, u64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_DATE_TIME,
    Binary(_, Vec<u8>) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_BINARY_DATA,
    Text(_, String) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_TEXT,
    LargeBinary(_, Vec<u8>) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_LARGE_BINARY_DATA,
    LargeText(_, String) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_LARGE_TEXT,
    SuperLarge(_, Vec<u8>) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_SUPER_LARGE_VALUE,
    U32(_, u32) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_32BIT_UNSIGNED,
    I64(_, i64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_64BIT_SIGNED,
    /// 16 byte value
    Guid(_, Vec<u8>) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_GUID,
    U16(_, u16) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_16BIT_UNSIGNED,
    ;
    Bool => bool,
    U8 => u8,
    // U16 => u16,
    U32 => u32,
    I16 => i16,
    I32 => i32,
    I64, Currency => i64,
    F32 => f32,
    F64 => f64,
    Binary, LargeBinary, SuperLarge, Guid => Vec<u8>,
    Text, LargeText => String,
    DateTime => u64,
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
        Self::Null
    }
}

impl ToString for Value {
    fn to_string(&self) -> String {
        match self {
            Value::Null => String::new(),
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

    fn load(handle: *mut Self::Handle, entry: i32) -> io::Result<Value> {
        with_error(|err| unsafe {
            let mut raw_column_type = 0;
            // Short circuit return if result != 1
            (libesedb_record_get_column_type(handle, entry, &mut raw_column_type, err) == 1)
                .then(|| ())?;
            let column_type: ColumnVariant = raw_column_type.into();
            Some(match column_type {
                ColumnVariant::Null => Self::Null,
                ColumnVariant::Bool => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_boolean(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::Bool(value != 0),
                        _ => return None,
                    }
                }
                ColumnVariant::U8 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_8bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::U8(value),
                        _ => return None,
                    }
                }
                ColumnVariant::I16 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_16bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::I16(value as i16),
                        _ => return None,
                    }
                }
                ColumnVariant::I32 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_32bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::I32(value as i32),
                        _ => return None,
                    }
                }
                ColumnVariant::Currency => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_64bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
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
                        0 => Self::Null,
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
                        0 => Self::Null,
                        1 => Self::F64(value),
                        _ => return None,
                    }
                }
                ColumnVariant::DateTime => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_filetime(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::DateTime(value),
                        _ => return None,
                    }
                }
                c @ (ColumnVariant::Binary | ColumnVariant::LargeBinary) => {
                    let mut size = 0;
                    let result =
                        libesedb_record_get_value_binary_data_size(handle, entry, &mut size, err);
                    match result {
                        0 => Self::Null,
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
                                0 => Self::Null,
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
                        0 => Self::Null,
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
                                0 => Self::Null,
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
                        0 => Self::Null,
                        1 => Self::U32(value),
                        _ => return None,
                    }
                }
                ColumnVariant::I64 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_64bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::I64(value as i64),
                        _ => return None,
                    }
                }
                ColumnVariant::U16 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_16bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
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
