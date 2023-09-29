/*
 * Entry identifier (ENTRYID) functions
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

#if !defined( _LIBFMAPI_ENTRY_IDENTIFIER_H )
#define _LIBFMAPI_ENTRY_IDENTIFIER_H

#include <common.h>
#include <types.h>

#include "libfmapi_extern.h"
#include "libfmapi_libcerror.h"
#include "libfmapi_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfmapi_internal_entry_identifier libfmapi_internal_entry_identifier_t;

struct libfmapi_internal_entry_identifier
{
	/* The flags
	 */
	uint8_t flags[ 4 ];

	/* The service provider identifier
	 */
	uint8_t service_provider_identifier[ 16 ];
};

LIBFMAPI_EXTERN \
int libfmapi_entry_identifier_initialize(
     libfmapi_entry_identifier_t **entry_identifier,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_entry_identifier_free(
     libfmapi_entry_identifier_t **entry_identifier,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_entry_identifier_copy_from_byte_stream(
     libfmapi_entry_identifier_t *entry_identifier,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_entry_identifier_get_service_provider_identifier(
     libfmapi_entry_identifier_t *entry_identifier,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFMAPI_ENTRY_IDENTIFIER_H ) */

