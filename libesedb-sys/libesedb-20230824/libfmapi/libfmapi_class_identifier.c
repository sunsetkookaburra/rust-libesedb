/*
 * Class identifier (CLSID) functions
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfmapi_class_identifier.h"
#include "libfmapi_definitions.h"

uint8_t libfmapi_class_identifier_mapi[ 16 ] = \
	{ 0x28, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_public_strings[ 16 ] = \
	{ 0x29, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_internet_headers[ 16 ] = \
	{ 0x86, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_appointment[ 16 ] = \
	{ 0x02, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_task[ 16 ] = \
	{ 0x03, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_address[ 16 ] = \
	{ 0x04, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_common[ 16 ] = \
	{ 0x08, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_journal[ 16 ] = \
	{ 0x0a, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_sticky_note[ 16 ] = \
	{ 0x0e, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_sharing[ 16 ] = \
	{ 0x40, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_rss_feed[ 16 ] = \
	{ 0x41, 0x20, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

uint8_t libfmapi_class_identifier_unified_messaging[ 16 ] = \
	{ 0x8e, 0x85, 0x42, 0x44, 0xe3, 0xa9, 0x80, 0x4e, 0xb9, 0x00, 0x31, 0x7a, 0x21, 0x0c, 0xc1, 0x5b };

uint8_t libfmapi_class_identifier_calendar[ 16 ] = \
	{ 0x90, 0xda, 0xd8, 0x6e, 0x0b, 0x45, 0x1b, 0x10, 0x98, 0xda, 0x00, 0xaa, 0x00, 0x3f, 0x13, 0x05 };

uint8_t libfmapi_class_identifier_air_sync[ 16 ] = \
	{ 0x49, 0x55, 0x03, 0x71, 0x39, 0x07, 0xcb, 0x4d, 0x91, 0x63, 0x00, 0xf0, 0x58, 0x0d, 0xbb, 0xdf };

uint8_t libfmapi_class_identifier_attachment[ 16 ] = \
	{ 0x7f, 0x7f, 0x35, 0x96, 0xe1, 0x59, 0xd0, 0x47, 0x99, 0xa7, 0x46, 0x51, 0x5c, 0x18, 0x3b, 0x54 };

uint8_t libfmapi_class_identifier_unknown[ 16 ] = \
	{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

#if defined( HAVE_DEBUG_OUTPUT )

/* The class identifiers
 */
libfmapi_class_identifier_definition_t libfmapi_class_identifier_definitions[ ] = {
	{ libfmapi_class_identifier_mapi,		"MAPI" },
	{ libfmapi_class_identifier_public_strings,	"Public strings" },
	{ libfmapi_class_identifier_internet_headers,	"Internet headers" },

	{ libfmapi_class_identifier_appointment,	"Appointment" },
	{ libfmapi_class_identifier_task,		"Task" },
	{ libfmapi_class_identifier_address,		"Address" },
	{ libfmapi_class_identifier_common,		"Common" },
	{ libfmapi_class_identifier_journal,		"Journal" },
	{ libfmapi_class_identifier_sticky_note,	"Sticky note" },
	{ libfmapi_class_identifier_sharing,		"Sharing" },
	{ libfmapi_class_identifier_rss_feed,		"RSS feed" },

	{ libfmapi_class_identifier_unified_messaging,	"Unified messaging" },
	{ libfmapi_class_identifier_calendar,		"Calendar" },
	{ libfmapi_class_identifier_air_sync,		"Air sync" },

	{ libfmapi_class_identifier_unknown,		"Unknown" } };

/* Retrieves a string containing the name of the class identifier
 */
const char *libfmapi_class_identifier_get_name(
             uint8_t *class_identifier )
{
	int iterator = 0;

	if( class_identifier == NULL )
	{
		return( "Invalid class identifier" );
	}
	while( memory_compare(
	        ( libfmapi_class_identifier_definitions[ iterator ] ).identifier,
	        libfmapi_class_identifier_unknown,
	        16 ) != 0 )
	{
		if( memory_compare(
		     ( libfmapi_class_identifier_definitions[ iterator ] ).identifier,
		     class_identifier,
		     16 ) == 0 )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfmapi_class_identifier_definitions[ iterator ] ).name );
}

#endif

