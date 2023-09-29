/*
 * X.400 object identifier (MAPIOID) functions
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
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

#if !defined( _LIBFMAPI_X400_OBJECT_IDENTIFIER_H )
#define _LIBFMAPI_X400_OBJECT_IDENTIFIER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* A runtime version of the X.400 object identifier (MAPIOID)
 */
typedef struct libfmapi_x400_object_identifier libfmapi_x400_object_identifier_t;

struct libfmapi_x400_object_identifier
{
	/* The MAPI prefix
	 * Consists of 7 bytes
	 * Contains 0x2a 0x86 0x48 0x86 0xf7 0x14 0x03
	 *
	 */
	uint8_t prefix[ 7 ];

	/* The object identifier type
	 * 0x0a => tag
	 * 0x0b => encodign
	 */
	uint8_t type;

	/* The object identifier data
	 * Variable of size
	 * Known tags (0x0a)
	 * 0x01           => TNEF
	 * 0x03           => OLE
	 * 0x03 0x01      => OLE1
	 * 0x03 0x01 0x01 => OLE1 storage
	 * 0x03 0x02      => OLE2
	 * 0x03 0x02 0x01 => OLE2 storage
	 * 0x04           => Unknown
	 * Known encodings (0x0b)
	 * 0x01           => MacBinary
	 * 0x04           => Mime Tag
	 */
	uint8_t *data;
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFMAPI_X400_OBJECT_IDENTIFIER_H ) */

