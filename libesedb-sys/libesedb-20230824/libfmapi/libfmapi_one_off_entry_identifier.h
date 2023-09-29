/*
 * One-off entry identifier functions
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

#if !defined( _LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_H )
#define _LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_H

#include <common.h>
#include <types.h>

#include "libfmapi_extern.h"
#include "libfmapi_libcerror.h"
#include "libfmapi_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfmapi_internal_one_off_entry_identifier libfmapi_internal_one_off_entry_identifier_t;

struct libfmapi_internal_one_off_entry_identifier
{
	/* The format version
	 */
	uint16_t format_version;

	/* The flags
	 */
	uint16_t flags;

	/* The display name
	 */
	uint8_t *display_name;

	/* The display name size
	 */
	size_t display_name_size;

	/* The address type
	 */
	uint8_t *address_type;

	/* The address type size
	 */
	size_t address_type_size;

	/* The email address
	 */
	uint8_t *email_address;

	/* The email address size
	 */
	size_t email_address_size;

	/* The ASCII codepage
	 */
	int ascii_codepage;
};

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_initialize(
     libfmapi_one_off_entry_identifier_t **entry_identifier,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_free(
     libfmapi_one_off_entry_identifier_t **entry_identifier,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_copy_from_byte_stream(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_version(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *format_version,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_flags(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *flags,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf8_display_name_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf8_display_name(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf16_display_name_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf16_display_name(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf8_address_type_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf8_address_type(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf16_address_type_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf16_address_type(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf8_email_address_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf8_email_address(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf16_email_address_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFMAPI_EXTERN \
int libfmapi_one_off_entry_identifier_get_utf16_email_address(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_H ) */

