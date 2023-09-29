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

#if !defined( _LIBFMAPI_CLASS_IDENTIFIER_H )
#define _LIBFMAPI_CLASS_IDENTIFIER_H

#include <common.h>
#include <types.h>

#include "libfmapi_definitions.h"
#include "libfmapi_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_DEBUG_OUTPUT )

/* The CLSID is stored as a little endian GUID
 */
typedef struct libfmapi_class_identifier_definition libfmapi_class_identifier_definition_t;

struct libfmapi_class_identifier_definition
{
	/* The class identifier
	 */
	uint8_t *identifier;

	/* The class name
	 */
	const char *name;
};

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_mapi[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_public_strings[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_internet_headers[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_appointment[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_task[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_address[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_common[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_journal[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_sticky_note[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_sharing[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_rss_feed[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_unified_messaging[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_calendar[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_air_sync[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_attachment[ 16 ];

LIBFMAPI_EXTERN_VARIABLE \
uint8_t libfmapi_class_identifier_unknown[ 16 ];

#if defined( HAVE_DEBUG_OUTPUT )

const char *libfmapi_class_identifier_get_name(
             uint8_t *class_identifier );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFMAPI_CLASS_IDENTIFIER_H ) */

