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
use std::time::{SystemTime, UNIX_EPOCH, Duration};

use crate::error::with_error;
use crate::iter::LoadEntry;

macro_rules! column_variants {
    (
        $(
            $(#[$attr:ident $($args:tt)*])*
            $i:ident $(($p:pat_param, $t:ty))? = $e:ident
        ),*$(,)?
    ) => {
        #[derive(Debug)]
        pub enum ColumnVariant {
            $(
                $(#[$attr $($args)*])*
                $i = $e as _
            ),*
        }

        impl From<i32> for ColumnVariant {
            fn from(x: i32) -> Self {
                match x {
                    $( $e => Self::$i, )*
                    _ => Self::Null
                }
            }
        }

        impl From<&Value> for ColumnVariant {
            fn from(value: &Value) -> Self {
                match value {
                    $( Value::$i$(($p))? => Self::$i, )*
                }
            }
        }

        #[derive(Debug)]
        pub enum Value {
            $(
                $(#[$attr $($args)*])*
                $i$(($t))?
            ),*
        }
    }
}

column_variants!{
    Null = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_NULL,
    Bool(_, bool) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_BOOLEAN,
    U8(_, u8) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_8BIT_UNSIGNED,
    I16(_, i16) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_16BIT_SIGNED,
    I32(_, i32) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_INTEGER_32BIT_SIGNED,
    Currency(_, i64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_CURRENCY,
    F32(_, f32) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_FLOAT_32BIT,
    F64(_, f64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_DOUBLE_64BIT,
    /// Decimal number of days since 1900.\
    /// See: <https://docs.microsoft.com/en-us/windows/win32/extensible-storage-engine/jet-coltyp>
    DateTime(_, f64) = LIBESEDB_COLUMN_TYPES_LIBESEDB_COLUMN_TYPE_DATE_TIME,
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
}

impl Value {
    pub fn time(&self) -> Option<SystemTime> {
        if let Self::DateTime(value) = self {
            Some(UNIX_EPOCH - Duration::from_secs(60 * 60 * 24 * 25567) + Duration::from_secs_f64((60 * 60 * 24) as f64 * value))
        } else {
            None
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
            Value::Binary(b)
            | Value::LargeBinary(b)
            | Value::SuperLarge(b) => {
                b.iter().map(|x| format!("{x:02x}")).collect::<Vec<_>>().join(" ")
            },
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
            },
            Value::U16(x) => x.to_string(),
        }
    }
}

impl LoadEntry for Value {
    type Handle = libesedb_record_t;

    fn load(handle: *mut Self::Handle, entry: i32) -> io::Result<Value> {
        with_error(|err| unsafe {
            let mut column_type = 0;
            (libesedb_record_get_column_type(handle, entry, &mut column_type, err) == 1).then(||())?;
            Some(match column_type {
                0 => Self::Null,
                1 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_boolean(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::Bool(value != 0),
                        _ => return None,
                    }
                },
                2 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_8bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::U8(value),
                        _ => return None,
                    }
                },
                3 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_16bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::I16(value as i16),
                        _ => return None,
                    }
                },
                4 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_32bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::I32(value as i32),
                        _ => return None,
                    }
                },
                5 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_64bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::Currency(value as i64),
                        _ => return None,
                    }
                },
                6 => {
                    let mut value = 0.0;
                    let result = libesedb_record_get_value_floating_point_32bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::F32(value),
                        _ => return None,
                    }
                },
                7 => {
                    let mut value = 0.0;
                    let result = libesedb_record_get_value_floating_point_64bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::F64(value),
                        _ => return None,
                    }
                },
                8 => {
                    let mut value = 0.0;
                    let result = libesedb_record_get_value_floating_point_64bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::DateTime(value),
                        _ => return None,
                    }
                },
                c @ (9 | 11) => {
                    let mut size = 0;
                    let result = libesedb_record_get_value_binary_data_size(handle, entry, &mut size, err);
                    match result {
                        0 => Self::Null,
                        1 => {
                            let mut data = vec![0; size as _];
                            let result = libesedb_record_get_value_binary_data(handle, entry, data.as_mut_ptr(), size, err);
                            match result {
                                0 => Self::Null,
                                1 => match c {
                                    9 => Self::Binary(data),
                                    11 => Self::LargeBinary(data),
                                    _ => unreachable!(),
                                },
                                _ => return None,
                            }
                        },
                        _ => return None,
                    }
                },
                c @ (10 | 12) => {
                    let mut size = 0;
                    let result = libesedb_record_get_value_utf8_string_size(handle, entry, &mut size, err);
                    match result {
                        0 => Self::Null,
                        1 => {
                            let mut data = vec![0; size as _];
                            let result = libesedb_record_get_value_utf8_string(handle, entry, data.as_mut_ptr(), size, err);
                            match result {
                                0 => Self::Null,
                                1 => {
                                    data.pop(); // remove null byte
                                    let text = String::from_utf8_lossy(&data).into();
                                    match c {
                                        10 => Self::Text(text),
                                        12 => Self::LargeText(text),
                                        _ => unreachable!(),
                                    }
                                },
                                _ => return None,
                            }
                        },
                        _ => return None,
                    }
                },
                c @ (13 | 16) => {
                    let mut size = 0;
                    let result = libesedb_record_get_value_data_size(handle, entry, &mut size, err);
                    match result {
                        1 => {
                            let mut data = vec![0; size as _];
                            let result = libesedb_record_get_value_data(handle, entry, data.as_mut_ptr(), size, err);
                            match result {
                                1 => match c {
                                    13 => Self::SuperLarge(data),
                                    16 => Self::Guid(data),
                                    _ => unreachable!(),
                                },
                                _ => return None,
                            }
                        },
                        _ => return None,
                    }
                },
                14 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_32bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::U32(value),
                        _ => return None,
                    }
                },
                15 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_64bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::I64(value as i64),
                        _ => return None,
                    }
                },
                17 => {
                    let mut value = 0;
                    let result = libesedb_record_get_value_16bit(handle, entry, &mut value, err);
                    match result {
                        0 => Self::Null,
                        1 => Self::U16(value),
                        _ => return None,
                    }
                },
                _ => unreachable!(),
            })
        })
    }
}
