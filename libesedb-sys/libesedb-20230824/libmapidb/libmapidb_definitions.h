/*
 * The internal definitions
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( LIBMAPIDB_INTERNAL_DEFINITIONS_H )
#define LIBMAPIDB_INTERNAL_DEFINITIONS_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBMAPIDB for local use of libmapidb
 */
#if !defined( HAVE_LOCAL_LIBMAPIDB )
#include <libmapidb/definitions.h>

/* The definitions in <libmapidb/definitions.h> are copied here
 * for local use of libmapidb
 */
#else
#include <byte_stream.h>

#define LIBMAPIDB_VERSION				20170304

/* The libmapidb version string
 */
#define LIBMAPIDB_VERSION_STRING			"20170304"

/* The endian definitions
 */
#define LIBMAPIDB_ENDIAN_BIG				_BYTE_STREAM_ENDIAN_BIG
#define LIBMAPIDB_ENDIAN_LITTLE				_BYTE_STREAM_ENDIAN_LITTLE

#endif /* !defined( HAVE_LOCAL_LIBMAPIDB ) */

#endif

