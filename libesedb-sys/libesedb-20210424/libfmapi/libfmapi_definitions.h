/*
 * The internal definitions
 *
 * Copyright (C) 2009-2018, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( LIBFMAPI_INTERNAL_DEFINITIONS_H )
#define LIBFMAPI_INTERNAL_DEFINITIONS_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBFMAPI for local use of libfmapi
 */
#if !defined( HAVE_LOCAL_LIBFMAPI )
#include <libfmapi/definitions.h>

/* The definitions in <libfmapi/definitions.h> are copied here
 * for local use of libfmapi
 */
#else
#include <byte_stream.h>

#define LIBFMAPI_VERSION					20180714

/* The libfmapi version string
 */
#define LIBFMAPI_VERSION_STRING					"20180714"

/* The endian definitions
 */
#define LIBFMAPI_ENDIAN_BIG					_BYTE_STREAM_ENDIAN_BIG
#define LIBFMAPI_ENDIAN_LITTLE					_BYTE_STREAM_ENDIAN_LITTLE

enum LIBFMAPI_ENTRY_IDENTIFIER_FLAGS
{
	LIBFMAPI_ENTRY_IDENTIFIER_FLAG_MAPI_NOTRESERVED		= 0x08,
	LIBFMAPI_ENTRY_IDENTIFIER_FLAG_MAPI_NOW			= 0x10,
	LIBFMAPI_ENTRY_IDENTIFIER_FLAG_MAPI_THISSESSION		= 0x20,
	LIBFMAPI_ENTRY_IDENTIFIER_FLAG_MAPI_NOTRECIP		= 0x40,
	LIBFMAPI_ENTRY_IDENTIFIER_FLAG_MAPI_SHORTTERM		= 0x80
};

#define LIBFMAPI_ENTRY_IDENTIFIER_FLAG_MAPI_COMPOUND		0x80

enum LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAGS
{
	LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_NO_RICH_INFO	= 0x0001,

	LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_0x1000		= 0x1000,

	LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE		= 0x8000
};

#endif /* !defined( HAVE_LOCAL_LIBFMAPI ) */

#endif /* !defined( LIBFMAPI_INTERNAL_DEFINITIONS_H ) */

