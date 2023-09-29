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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libfmapi_definitions.h"
#include "libfmapi_libcerror.h"
#include "libfmapi_libcnotify.h"
#include "libfmapi_libuna.h"
#include "libfmapi_one_off_entry_identifier.h"

/* Creates an one-off entry identifier
 * Make sure the value entry_identifier is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_initialize(
     libfmapi_one_off_entry_identifier_t **entry_identifier,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_initialize";

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	if( *entry_identifier != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid entry identifier value already set.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = memory_allocate_structure(
	                             libfmapi_internal_one_off_entry_identifier_t );

	if( internal_entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create entry identifier.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_entry_identifier,
	     0,
	     sizeof( libfmapi_internal_one_off_entry_identifier_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear entry identifier.",
		 function );

		goto on_error;
	}
	*entry_identifier = (libfmapi_one_off_entry_identifier_t *) internal_entry_identifier;

	return( 1 );

on_error:
	if( internal_entry_identifier != NULL )
	{
		memory_free(
		 internal_entry_identifier );
	}
	return( -1 );
}

/* Frees an one-off entry identifier
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_free(
     libfmapi_one_off_entry_identifier_t **entry_identifier,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_free";

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	if( *entry_identifier != NULL )
	{
		internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) *entry_identifier;
		*entry_identifier         = NULL;

		if( internal_entry_identifier->display_name != NULL )
		{
			memory_free(
			 internal_entry_identifier->display_name );
		}
		if( internal_entry_identifier->address_type != NULL )
		{
			memory_free(
			 internal_entry_identifier->address_type );
		}
		if( internal_entry_identifier->email_address != NULL )
		{
			memory_free(
			 internal_entry_identifier->email_address );
		}
		memory_free(
		 internal_entry_identifier );
	}
	return( 1 );
}

/* Converts a byte stream into an one-off entry identifier
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_copy_from_byte_stream(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_copy_from_byte_stream";
	size_t byte_stream_offset                                               = 0;
	size_t string_size                                                      = 0;
	uint16_t flags                                                          = 0;
	uint16_t format_version                                                 = 0;
	uint16_t supported_flags                                                = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( internal_entry_identifier->email_address != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid entry identifier - email address value already set.",
		 function );

		return( -1 );
	}
	if( internal_entry_identifier->address_type != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid entry identifier - address type value already set.",
		 function );

		return( -1 );
	}
	if( internal_entry_identifier->display_name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid entry identifier - display value value already set.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( ( byte_stream_size < 4 )
	 || ( byte_stream_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid byte stream size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: one-off entry identifier header data:\n",
		 function );
		libcnotify_print_data(
		 byte_stream,
		 4,
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 &( byte_stream[ 0 ] ),
	 format_version );

	byte_stream_copy_to_uint16_little_endian(
	 &( byte_stream[ 2 ] ),
	 flags );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: format version\t: %" PRIu16 "\n",
		 function,
		 format_version );

		libcnotify_printf(
		 "%s: flags\t\t: 0x%04" PRIx16 "\n",
		 function,
		 flags );
	}
#endif
	byte_stream_offset += 4;

	if( format_version != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version: %" PRIu16 ".",
		 function,
		 format_version );

		goto on_error;
	}
	supported_flags = LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_NO_RICH_INFO
	                | LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_0x1000
	                | LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE;

	if( ( flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%04" PRIx16 ".",
		 function,
		 flags );

		goto on_error;
	}
	internal_entry_identifier->format_version = format_version;
	internal_entry_identifier->flags          = flags;
	internal_entry_identifier->ascii_codepage = ascii_codepage;

	string_size = byte_stream_offset;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		while( string_size < ( byte_stream_size - 3 ) )
		{
			if( ( byte_stream[ string_size ] == 0 )
			 && ( byte_stream[ string_size + 1 ] == 0 ) )
			{
				break;
			}
			string_size += 2;
		}
		if( ( string_size >= ( byte_stream_size - 1 ) )
		 || ( byte_stream[ string_size ] != 0 )
		 || ( byte_stream[ string_size + 1 ] != 0 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported display name value in byte stream.",
			 function );

			goto on_error;
		}
		string_size += 2;
	}
	else
	{
		while( string_size < ( byte_stream_size - 1 ) )
		{
			if( byte_stream[ string_size ] == 0 )
			{
				break;
			}
			string_size += 1;
		}
		if( ( string_size >= byte_stream_size )
		 || ( byte_stream[ string_size ] != 0 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported display name value in byte stream.",
			 function );

			return( -1 );
		}
		string_size += 1;
	}
	string_size -= byte_stream_offset;

	if( ( string_size == 0 )
	 || ( string_size > MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid display name size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: display name data:\n",
		 function );
		libcnotify_print_data(
		 &( byte_stream[ byte_stream_offset ] ),
		 string_size,
		 0 );
	}
#endif
	internal_entry_identifier->display_name = (uint8_t *) memory_allocate(
	                                                       sizeof( uint8_t ) * string_size );

	if( internal_entry_identifier->display_name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create display name.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     internal_entry_identifier->display_name,
	     &( byte_stream[ byte_stream_offset ] ),
	     string_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy display name.",
		 function );

		goto on_error;
	}
	internal_entry_identifier->display_name_size = string_size;

	byte_stream_offset += string_size;

	string_size = byte_stream_offset;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		while( string_size < ( byte_stream_size - 3 ) )
		{
			if( ( byte_stream[ string_size ] == 0 )
			 && ( byte_stream[ string_size + 1 ] == 0 ) )
			{
				break;
			}
			string_size += 2;
		}
		if( ( string_size >= ( byte_stream_size - 1 ) )
		 || ( byte_stream[ string_size ] != 0 )
		 || ( byte_stream[ string_size + 1 ] != 0 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported address type value in byte stream.",
			 function );

			goto on_error;
		}
		string_size += 2;
	}
	else
	{
		while( string_size < ( byte_stream_size - 1 ) )
		{
			if( byte_stream[ string_size ] == 0 )
			{
				break;
			}
			string_size += 1;
		}
		if( ( string_size >= byte_stream_size )
		 || ( byte_stream[ string_size ] != 0 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported address type value in byte stream.",
			 function );

			goto on_error;
		}
		string_size += 1;
	}
	string_size -= byte_stream_offset;

	if( ( string_size == 0 )
	 || ( string_size > MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid address type size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: address type data:\n",
		 function );
		libcnotify_print_data(
		 &( byte_stream[ byte_stream_offset ] ),
		 string_size,
		 0 );
	}
#endif
	internal_entry_identifier->address_type = (uint8_t *) memory_allocate(
	                                                       sizeof( uint8_t ) * string_size );

	if( internal_entry_identifier->address_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create address type.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     internal_entry_identifier->address_type,
	     &( byte_stream[ byte_stream_offset ] ),
	     string_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy address type.",
		 function );

		goto on_error;
	}
	internal_entry_identifier->address_type_size = string_size;

	byte_stream_offset += string_size;

	string_size = byte_stream_offset;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		while( string_size < ( byte_stream_size - 3 ) )
		{
			if( ( byte_stream[ string_size ] == 0 )
			 && ( byte_stream[ string_size + 1 ] == 0 ) )
			{
				break;
			}
			string_size += 2;
		}
		if( ( string_size >= ( byte_stream_size - 1 ) )
		 || ( byte_stream[ string_size ] != 0 )
		 || ( byte_stream[ string_size + 1 ] != 0 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported email address value in byte stream.",
			 function );

			goto on_error;
		}
		string_size += 2;
	}
	else
	{
		while( string_size < ( byte_stream_size - 1 ) )
		{
			if( byte_stream[ string_size ] == 0 )
			{
				break;
			}
			string_size += 1;
		}
		if( ( string_size >= byte_stream_size )
		 || ( byte_stream[ string_size ] != 0 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported email address value in byte stream.",
			 function );

			goto on_error;
		}
		string_size += 1;
	}
	string_size -= byte_stream_offset;

	if( ( string_size == 0 )
	 || ( string_size > MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid email address size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: email address data:\n",
		 function );
		libcnotify_print_data(
		 &( byte_stream[ byte_stream_offset ] ),
		 string_size,
		 0 );
	}
#endif
	internal_entry_identifier->email_address = (uint8_t *) memory_allocate(
	                                                        sizeof( uint8_t ) * string_size );

	if( internal_entry_identifier->email_address == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create email address.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     internal_entry_identifier->email_address,
	     &( byte_stream[ byte_stream_offset ] ),
	     string_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy email address.",
		 function );

		goto on_error;
	}
	internal_entry_identifier->email_address_size = string_size;

	byte_stream_offset += string_size;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( byte_stream_offset < byte_stream_size )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( byte_stream[ byte_stream_offset ] ),
			 byte_stream_size - byte_stream_offset,
			 0 );
		}
	}
#endif
	return( 1 );

on_error:
	if( internal_entry_identifier->email_address != NULL )
	{
		memory_free(
		 internal_entry_identifier->email_address );

		internal_entry_identifier->email_address = NULL;
	}
	if( internal_entry_identifier->address_type != NULL )
	{
		memory_free(
		 internal_entry_identifier->address_type );

		internal_entry_identifier->address_type = NULL;
	}
	if( internal_entry_identifier->display_name != NULL )
	{
		memory_free(
		 internal_entry_identifier->display_name );

		internal_entry_identifier->display_name = NULL;
	}
	return( -1 );
}

/* Retrieves the format version
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_version(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *format_version,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_version";

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( format_version == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid format version.",
		 function );

		return( -1 );
	}
	*format_version = internal_entry_identifier->format_version;

	return( 1 );
}

/* Retrieves the flags
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_flags(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *flags,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_flags";

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid flags.",
		 function );

		return( -1 );
	}
	*flags = internal_entry_identifier->flags;

	return( 1 );
}

/* Retrieves the UTF-8 string size of the one-off entry identifier display name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf8_display_name_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf8_display_name_size";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
			  internal_entry_identifier->display_name,
			  internal_entry_identifier->display_name_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf8_string_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  internal_entry_identifier->display_name,
			  internal_entry_identifier->display_name_size,
			  internal_entry_identifier->ascii_codepage,
			  utf8_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 string of the one-off entry identifier display name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf8_display_name(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf8_display_name";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_copy_from_utf16_stream(
			  utf8_string,
			  utf8_string_size,
			  internal_entry_identifier->display_name,
			  internal_entry_identifier->display_name_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf8_string_copy_from_byte_stream(
			  utf8_string,
			  utf8_string_size,
			  internal_entry_identifier->display_name,
			  internal_entry_identifier->display_name_size,
			  internal_entry_identifier->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 string size of the one-off entry identifier display name
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf16_display_name_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf16_display_name_size";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
			  internal_entry_identifier->display_name,
			  internal_entry_identifier->display_name_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf16_string_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  internal_entry_identifier->display_name,
			  internal_entry_identifier->display_name_size,
			  internal_entry_identifier->ascii_codepage,
			  utf16_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 string of the one-off entry identifier display name
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf16_display_name(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf16_display_name";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  internal_entry_identifier->display_name,
			  internal_entry_identifier->display_name_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf16_string_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  internal_entry_identifier->display_name,
			  internal_entry_identifier->display_name_size,
			  internal_entry_identifier->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 string size of the one-off entry identifier address type
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf8_address_type_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf8_address_type_size";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
			  internal_entry_identifier->address_type,
			  internal_entry_identifier->address_type_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf8_string_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  internal_entry_identifier->address_type,
			  internal_entry_identifier->address_type_size,
			  internal_entry_identifier->ascii_codepage,
			  utf8_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 string of the one-off entry identifier address type
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf8_address_type(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf8_address_type";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_copy_from_utf16_stream(
			  utf8_string,
			  utf8_string_size,
			  internal_entry_identifier->address_type,
			  internal_entry_identifier->address_type_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf8_string_copy_from_byte_stream(
			  utf8_string,
			  utf8_string_size,
			  internal_entry_identifier->address_type,
			  internal_entry_identifier->address_type_size,
			  internal_entry_identifier->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 string size of the one-off entry identifier address type
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf16_address_type_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf16_address_type_size";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
			  internal_entry_identifier->address_type,
			  internal_entry_identifier->address_type_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf16_string_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  internal_entry_identifier->address_type,
			  internal_entry_identifier->address_type_size,
			  internal_entry_identifier->ascii_codepage,
			  utf16_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 string of the one-off entry identifier address type
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf16_address_type(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf16_address_type";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  internal_entry_identifier->address_type,
			  internal_entry_identifier->address_type_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf16_string_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  internal_entry_identifier->address_type,
			  internal_entry_identifier->address_type_size,
			  internal_entry_identifier->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 string size of the one-off entry identifier email address
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf8_email_address_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf8_email_address_size";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
			  internal_entry_identifier->email_address,
			  internal_entry_identifier->email_address_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf8_string_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  internal_entry_identifier->email_address,
			  internal_entry_identifier->email_address_size,
			  internal_entry_identifier->ascii_codepage,
			  utf8_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 string of the one-off entry identifier email address
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf8_email_address(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf8_email_address";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_copy_from_utf16_stream(
			  utf8_string,
			  utf8_string_size,
			  internal_entry_identifier->email_address,
			  internal_entry_identifier->email_address_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf8_string_copy_from_byte_stream(
			  utf8_string,
			  utf8_string_size,
			  internal_entry_identifier->email_address,
			  internal_entry_identifier->email_address_size,
			  internal_entry_identifier->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 string size of the one-off entry identifier email address
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf16_email_address_size(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf16_email_address_size";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
			  internal_entry_identifier->email_address,
			  internal_entry_identifier->email_address_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf16_string_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  internal_entry_identifier->email_address,
			  internal_entry_identifier->email_address_size,
			  internal_entry_identifier->ascii_codepage,
			  utf16_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 string of the one-off entry identifier email address
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfmapi_one_off_entry_identifier_get_utf16_email_address(
     libfmapi_one_off_entry_identifier_t *entry_identifier,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfmapi_internal_one_off_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                                   = "libfmapi_one_off_entry_identifier_get_utf16_email_address";
	int result                                                              = 0;

	if( entry_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry identifier.",
		 function );

		return( -1 );
	}
	internal_entry_identifier = (libfmapi_internal_one_off_entry_identifier_t *) entry_identifier;

	if( ( internal_entry_identifier->flags & LIBFMAPI_ONE_OFF_ENTRY_IDENTIFIER_FLAG_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  internal_entry_identifier->email_address,
			  internal_entry_identifier->email_address_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf16_string_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  internal_entry_identifier->email_address,
			  internal_entry_identifier->email_address_size,
			  internal_entry_identifier->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

