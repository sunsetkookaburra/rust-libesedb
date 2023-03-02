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

use std::time::SystemTime;
use time::{ext::NumericalDuration, macros::datetime, Duration, OffsetDateTime, UtcOffset};

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
/// Time represented as 100 nanosecond intervals since 1601 Jan 01, 0000 UTC
pub struct FileTime(u64);

impl FileTime {
    pub const EPOCH: OffsetDateTime = datetime!(1601-01-01 00:00:00 +0);

    pub fn from_100ns(x: u64) -> Self {
        Self(x)
    }

    pub fn to_time(&self) -> OffsetDateTime {
        (*self).into()
    }

    pub fn to_system(&self) -> SystemTime {
        (*self).into()
    }
}

impl From<FileTime> for OffsetDateTime {
    fn from(value: FileTime) -> Self {
        FileTime::EPOCH.saturating_add(Duration::new(
            (value.0 / 10000000) as _,
            (value.0 % 10000000) as _,
        ))
    }
}

impl From<FileTime> for SystemTime {
    fn from(value: FileTime) -> Self {
        OffsetDateTime::from(value).into()
    }
}

impl From<OffsetDateTime> for FileTime {
    fn from(value: OffsetDateTime) -> Self {
        Self(
            ((value - Self::EPOCH).whole_nanoseconds() / 100)
                .max(0)
                .min(u64::MAX as _) as _,
        )
    }
}

impl From<SystemTime> for FileTime {
    fn from(value: SystemTime) -> Self {
        Self::from(OffsetDateTime::from(value))
    }
}

impl PartialEq<SystemTime> for FileTime {
    fn eq(&self, other: &SystemTime) -> bool {
        &self.to_system() == other
    }
}

impl PartialEq<FileTime> for SystemTime {
    fn eq(&self, other: &FileTime) -> bool {
        other == self
    }
}

#[derive(Debug, Clone, Copy, PartialEq, PartialOrd)]
/// Time represented as fractional/decimal days since 1900 Jan 01, 0000 UTC
pub struct OleTime(f64);

impl OleTime {
    pub const EPOCH: OffsetDateTime = datetime!(1899-12-30 00:00:00).assume_offset(UtcOffset::UTC);

    pub fn from_days(days: f64) -> Self {
        Self(days)
    }

    pub fn to_time(&self) -> OffsetDateTime {
        (*self).into()
    }

    pub fn to_system(&self) -> SystemTime {
        (*self).into()
    }
}

impl From<OleTime> for OffsetDateTime {
    fn from(value: OleTime) -> Self {
        OleTime::EPOCH.saturating_add(value.0.days())
    }
}

impl From<OleTime> for SystemTime {
    fn from(value: OleTime) -> Self {
        OffsetDateTime::from(value).into()
    }
}

impl From<OffsetDateTime> for OleTime {
    fn from(value: OffsetDateTime) -> Self {
        let diff = value - Self::EPOCH;
        Self(diff.whole_days() as f64 + diff.as_seconds_f64() % (60.0 * 60.0 * 24.0))
    }
}

impl From<SystemTime> for OleTime {
    fn from(value: SystemTime) -> Self {
        Self::from(OffsetDateTime::from(value))
    }
}

impl PartialEq<SystemTime> for OleTime {
    fn eq(&self, other: &SystemTime) -> bool {
        println!("selfie {:?} self {:?} other {:?}", self, self.to_system(), other);
        &self.to_system() == other
    }
}

impl PartialEq<OleTime> for SystemTime {
    fn eq(&self, other: &OleTime) -> bool {
        other == self
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn filetime_from_systemtime() {
        assert_eq!(
            FileTime::from(OffsetDateTime::UNIX_EPOCH),
            SystemTime::UNIX_EPOCH
        );
        assert_eq!(
            SystemTime::UNIX_EPOCH,
            FileTime::from(OffsetDateTime::UNIX_EPOCH)
        );
    }

    #[test]
    fn filetime_value() {
        assert_eq!(
            FileTime::from_100ns(116444736000000000),
            SystemTime::UNIX_EPOCH
        );
    }

    #[test]
    fn oletime_from_systemtime() {
        assert_eq!(
            OleTime::from(OffsetDateTime::UNIX_EPOCH),
            SystemTime::UNIX_EPOCH
        );
        assert_eq!(
            SystemTime::UNIX_EPOCH,
            OleTime::from(OffsetDateTime::UNIX_EPOCH)
        );
    }

    #[test]
    fn oletime_value() {
        assert_eq!(
            OleTime::from_days(25569.0),
            SystemTime::UNIX_EPOCH
        );
    }
}
