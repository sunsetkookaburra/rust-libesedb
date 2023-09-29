/*
 * Debug functions
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfmapi_class_identifier.h"
#include "libfmapi_codepage.h"
#include "libfmapi_definitions.h"
#include "libfmapi_debug.h"
#include "libfmapi_entry_identifier.h"
#include "libfmapi_libcerror.h"
#include "libfmapi_libcnotify.h"
#include "libfmapi_libfdatetime.h"
#include "libfmapi_libfguid.h"
#include "libfmapi_libfwnt.h"
#include "libfmapi_libuna.h"
#include "libfmapi_lzfu.h"
#include "libfmapi_one_off_entry_identifier.h"
#include "libfmapi_service_provider_identifier.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Function to determine if there are zero bytes in a string
 * Trailing zero bytes not included
 * Returns 1 if the buffer contains zero bytes, 0 if not or -1 on error
 */
int libfmapi_debug_string_contains_zero_bytes(
     uint8_t *buffer,
     size_t buffer_size,
     libcerror_error_t **error )
{
	static char *function   = "libfmapi_debug_string_contains_zero_bytes";
	size_t buffer_iterator  = 0;
	uint8_t zero_byte_found = 0;

	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	for( buffer_iterator = 0;
	     buffer_iterator < buffer_size;
	     buffer_iterator++ )
	{
		if( zero_byte_found == 0 )
		{
			if( buffer[ buffer_iterator ] == 0 )
			{
				zero_byte_found = 1;
			}
		}
		else
		{
			if( buffer[ buffer_iterator ] != 0 )
			{
				return( 1 );
			}
		}
	}
	return( 0 );
}

/* Prints the entry identifier
 * Returns 1 if successful or -1 on error
 */
int libfmapi_debug_print_entry_identifier(
     uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfmapi_internal_entry_identifier_t *entry_identifier = NULL;
	static char *function                                  = "libfmapi_debug_print_entry_identifier";
	uint32_t value_32bit                                   = 0;

	uint8_t *service_provider_identifier                   = NULL;

	if( libfmapi_entry_identifier_initialize(
	     (libfmapi_entry_identifier_t **) &entry_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create entry identifier.",
		 function );

		goto on_error;
	}
	if( libfmapi_entry_identifier_copy_from_byte_stream(
	     (libfmapi_entry_identifier_t *) entry_identifier,
	     value_data,
	     value_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set entry identifier.",
		 function );

		goto on_error;
	}
	service_provider_identifier = &( value_data[ 4 ] );

	value_data      += 20;
	value_data_size -= 20;

	libcnotify_printf(
	 "Entry identifier:\n" );

	libcnotify_printf(
	 "Object identifier data:\n" );

	if( memory_compare(
	     service_provider_identifier,
	     &libfmapi_service_provider_identifier_one_off_entry_identifier,
	     16 ) == 0 )
	{
		if( libfmapi_debug_print_one_off_entry_identifier(
		     value_data,
		     value_data_size,
		     ascii_codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print one-off entry identifier.",
			 function );

			goto on_error;
		}
	}
	else if( memory_compare(
	          service_provider_identifier,
	          &libfmapi_service_provider_identifier_x500_address,
	          16 ) == 0 )
	{
		libcnotify_print_data(
		 value_data,
		 value_data_size,
		 0 );
	}
	else if( value_data_size == 4 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 value_data,
		 value_32bit );

		libcnotify_printf(
		 "Descriptor identifier\t\t: %" PRIu32 "\n",
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
	else
	{
		libcnotify_print_data(
		 value_data,
		 value_data_size,
		 0 );
	}
	if( libfmapi_entry_identifier_free(
	     (libfmapi_entry_identifier_t **) &entry_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free entry identifier.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( entry_identifier != NULL )
	{
		libfmapi_entry_identifier_free(
		 (libfmapi_entry_identifier_t **) &entry_identifier,
		 NULL );
	}
	return( -1 );
}

/* Prints the one-off entry identifier
 * Returns 1 if successful or -1 on error
 */
int libfmapi_debug_print_one_off_entry_identifier(
     uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfmapi_one_off_entry_identifier_t *one_off_entry_identifier = NULL;
	system_character_t *value_string                              = NULL;
	static char *function                                         = "libfmapi_debug_print_one_off_entry_identifier";
	size_t value_string_size                                      = 0;
	int result                                                    = 0;

	if( libfmapi_one_off_entry_identifier_initialize(
	     &one_off_entry_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create one-off entry identifier.",
		 function );

		goto on_error;
	}
	if( libfmapi_one_off_entry_identifier_copy_from_byte_stream(
	     one_off_entry_identifier,
	     value_data,
	     value_data_size,
	     ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy one-off entry identifier from byte stream.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "One-off entry identifier:\n" );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfmapi_one_off_entry_identifier_get_utf16_display_name_size(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  &value_string_size,
		  error );
#else
	result = libfmapi_one_off_entry_identifier_get_utf8_display_name_size(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  &value_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine value string size.",
		 function );

		goto on_error;
	}
	value_string = system_string_allocate(
	                value_string_size );

	if( value_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create value string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfmapi_one_off_entry_identifier_get_utf16_display_name(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  (uint16_t *) value_string,
		  value_string_size,
		  error );
#else
	result = libfmapi_one_off_entry_identifier_get_utf8_display_name(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  (uint8_t *) value_string,
		  value_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "Display name\t\t\t: %" PRIs_SYSTEM "\n",
	 value_string );

	memory_free(
	 value_string );

	value_string = NULL;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfmapi_one_off_entry_identifier_get_utf16_address_type_size(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  &value_string_size,
		  error );
#else
	result = libfmapi_one_off_entry_identifier_get_utf8_address_type_size(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  &value_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine value string size.",
		 function );

		goto on_error;
	}
	value_string = system_string_allocate(
	                value_string_size );

	if( value_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create value string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfmapi_one_off_entry_identifier_get_utf16_address_type(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  (uint16_t *) value_string,
		  value_string_size,
		  error );
#else
	result = libfmapi_one_off_entry_identifier_get_utf8_address_type(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  (uint8_t *) value_string,
		  value_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "Address type\t\t\t: %" PRIs_SYSTEM "\n",
	 value_string );

	memory_free(
	 value_string );

	value_string = NULL;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfmapi_one_off_entry_identifier_get_utf16_email_address_size(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  &value_string_size,
		  error );
#else
	result = libfmapi_one_off_entry_identifier_get_utf8_email_address_size(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  &value_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine value string size.",
		 function );

		goto on_error;
	}
	value_string = system_string_allocate(
	                value_string_size );

	if( value_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create value string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfmapi_one_off_entry_identifier_get_utf16_email_address(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  (uint16_t *) value_string,
		  value_string_size,
		  error );
#else
	result = libfmapi_one_off_entry_identifier_get_utf8_email_address(
		  (libfmapi_one_off_entry_identifier_t *) one_off_entry_identifier,
		  (uint8_t *) value_string,
		  value_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "Email address\t\t\t: %" PRIs_SYSTEM "\n",
	 value_string );

	memory_free(
	 value_string );

	value_string = NULL;

	libcnotify_printf(
	 "\n" );

	if( libfmapi_one_off_entry_identifier_free(
	     &one_off_entry_identifier,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free one-off entry identifier.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	if( one_off_entry_identifier != NULL )
	{
		libfmapi_one_off_entry_identifier_free(
		 &one_off_entry_identifier,
		 NULL );
	}
	return( -1 );
}

/* Prints the persist data block
 * Returns 1 if successful or -1 on error
 */
int libfmapi_debug_print_persist_data_block(
     uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	static char *function       = "libfmapi_debug_print_persist_data_block";
	uint16_t block_type         = 0;
	uint16_t elements_data_size = 0;

	if( value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value data.",
		 function );

		return( -1 );
	}
/* TODO sanity check of value_data_size */
	libcnotify_printf(
	 "Persist data block:\n" );

	byte_stream_copy_to_uint16_little_endian(
	 value_data,
	 block_type );
/* TODO print block type decription */
	libcnotify_printf(
	 "\tType:\t\t\t\t0x%04" PRIx16 "\n",
	 block_type );

	value_data      += 2;
	value_data_size -= 2;

	byte_stream_copy_to_uint16_little_endian(
	 value_data,
	 elements_data_size );
	libcnotify_printf(
	 "\tSize:\t\t\t\t%" PRIu16 "\n",
	 elements_data_size );

	value_data      += 2;
	value_data_size -= 2;

/* TODO sanity check of elements_data_size */

/* TODO print persist data elements
	while( elements_data_size > 0 )
	{
	}
*/
	libcnotify_print_data(
	 value_data,
	 elements_data_size,
	 0 );

	value_data      += elements_data_size;
	value_data_size -= elements_data_size;

	if( value_data_size > 0 )
	{
		libcnotify_printf(
		 "Trailing data:\n" );
		libcnotify_print_data(
		 value_data,
		 value_data_size,
		 0 );
	}
	return( 1 );
}

/* Prints the MAPI value
 * Returns 1 if successful or -1 on error
 */
int libfmapi_debug_print_value(
     uint32_t entry_type,
     uint32_t value_type,
     uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	system_character_t filetime_string[ 32 ];
	system_character_t guid_string[ 48 ];

	libfdatetime_filetime_t *filetime = NULL;
	libfguid_identifier_t *guid       = NULL;
	system_character_t *value_string  = NULL;
	static char *function             = "libfmapi_debug_print_value";
	size_t value_string_size          = 0;
	double value_double               = 0.0;
	float value_float                 = 0.0;
	uint64_t value_64bit              = 0;
	uint32_t value_32bit              = 0;
	uint8_t is_ascii_string           = 0;
	int result                        = 0;

	switch( value_type )
	{
		case 0x0003:
			if( value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
				 "%s: invalid value data.",
				 function );

				return( -1 );
			}
			if( libfmapi_debug_print_integer_32bit_value(
			     entry_type,
			     value_type,
			     value_data,
			     value_data_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print 32-bit integer MAPI value.",
				 function );

				return( -1 );
			}
			break;

		case 0x0004:
			if( value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
				 "%s: invalid value data.",
				 function );

				return( -1 );
			}
			byte_stream_copy_to_uint32_little_endian(
			 value_data,
			 value_32bit );

			if( memory_copy(
			     &value_float,
			     &value_32bit,
			     sizeof( uint32_t ) ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to convert 32-bit value into float.",
				 function );

				return( -1 );
			}
			libcnotify_printf(
			 "Floating point single precision value\t: %f\n\n",
			 value_float );

			break;

		case 0x0005:
			if( value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
				 "%s: invalid value data.",
				 function );

				return( -1 );
			}
			byte_stream_copy_to_uint64_little_endian(
			 value_data,
			 value_64bit );

			if( memory_copy(
			     &value_double,
			     &value_64bit,
			     sizeof( uint64_t ) ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to convert 64-bit value into double.",
				 function );

				return( -1 );
			}
			libcnotify_printf(
			 "Floating point double precision value\t: %f\n\n",
			 value_double );

			break;

		case 0x000b:
			if( value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
				 "%s: invalid value data.",
				 function );

				return( -1 );
			}
			libcnotify_printf(
			 "Boolean\t: " );

			if( value_data[ 0 ] == 0 )
			{
				libcnotify_printf(
				 "false" );
			}
			else
			{
				libcnotify_printf(
				 "true" );
			}
			libcnotify_printf(
			 "\n\n" );

			break;

		case 0x000d:
			if( value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
				 "%s: invalid value data.",
				 function );

				return( -1 );
			}
			if( value_data_size == 8 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 value_data,
				 value_32bit );

				value_data      += 4;
				value_data_size -= 4;

				libcnotify_printf(
				 "local descriptor identifier\t: %" PRIu32 "\n",
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 value_data,
				 value_32bit );

				value_data      += 4;
				value_data_size -= 4;

				libcnotify_printf(
				 "unknown\t\t\t\t: %" PRIu32 "\n",
				 value_32bit );

				libcnotify_printf(
				 "\n" );
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x0014:
			if( value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
				 "%s: invalid value data.",
				 function );

				return( -1 );
			}
			byte_stream_copy_to_uint64_little_endian(
			 value_data,
			 value_64bit );

			libcnotify_printf(
			 "integer 64-bit signed\t: %" PRId64 " (0x%" PRIx64 ")\n\n",
			 (int64_t) value_64bit,
			 value_64bit );

			break;

		case 0x0040:
			if( value_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
				 "%s: invalid value data.",
				 function );

				return( -1 );
			}
			if( libfdatetime_filetime_initialize(
			     &filetime,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create filetime.",
				 function );

				return( -1 );
			}
			if( libfdatetime_filetime_copy_from_byte_stream(
			     filetime,
			     value_data,
			     value_data_size,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy byte stream to filetime.",
				 function );

				libfdatetime_filetime_free(
				 &filetime,
				 NULL );

				return( -1 );
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libfdatetime_filetime_copy_to_utf16_string(
			          filetime,
			          (uint16_t *) filetime_string,
			          32,
			          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			          error );
#else
			result = libfdatetime_filetime_copy_to_utf8_string(
			          filetime,
			          (uint8_t *) filetime_string,
			          32,
			          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			          error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy filetime to string.",
				 function );

				libfdatetime_filetime_free(
				 &filetime,
				 NULL );

				return( -1 );
			}
			if( libfdatetime_filetime_free(
			     &filetime,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free filetime.",
				 function );

				return( -1 );
			}
			libcnotify_printf(
			 "Filetime\t: %" PRIs_SYSTEM " UTC\n\n",
			 filetime_string );

			break;

		case 0x0048:
			if( value_data == NULL )
			{
				libcnotify_printf(
				 "GUID\t: <NULL>\n\n" );
			}
			else  if( value_data_size == 16 )
			{
				if( libfguid_identifier_initialize(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create GUID.",
					 function );

					return( -1 );
				}
				if( libfguid_identifier_copy_from_byte_stream(
				     guid,
				     value_data,
				     value_data_size,
				     LIBFGUID_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to GUID.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				value_data      += 16;
				value_data_size -= 16;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfguid_identifier_copy_to_utf16_string(
					  guid,
					  (uint16_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#else
				result = libfguid_identifier_copy_to_utf8_string(
					  guid,
					  (uint8_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy GUID to string.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				if( libfguid_identifier_free(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free GUID.",
					 function );

					return( -1 );
				}
				libcnotify_printf(
				 "GUID\t: %" PRIs_SYSTEM "\n\n",
				 guid_string );
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x001e:
			if( value_data == NULL )
			{
				libcnotify_printf(
				 "ASCII string\t: <NULL>\n\n" );
			}
			else
			{
				is_ascii_string = 1;

				/* Codepage 1200 represents Unicode
				 * If the codepage is 1200 find out if the string is encoded in UTF-8 or UTF-16 little-endian
				 */
				if( ascii_codepage == 1200 )
				{
					result = libfmapi_debug_string_contains_zero_bytes(
						  value_data,
						  value_data_size,
						  error );

					if( result == -1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to determine if value type contains zero bytes.",
						 function );

						return( -1 );
					}
					else if( result != 0 )
					{
						is_ascii_string = 0;
					}
				}
				/* String is in UTF-16 little-endian
				 */
				if( is_ascii_string == 0 )
				{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_utf16_stream(
					          value_data,
					          value_data_size,
					          LIBUNA_ENDIAN_LITTLE,
					          &value_string_size,
					          error );
#else
					result = libuna_utf8_string_size_from_utf16_stream(
					          value_data,
					          value_data_size,
					          LIBUNA_ENDIAN_LITTLE,
					          &value_string_size,
					          error );
#endif
				}
				/* Codepage 65000 represents UTF-7
				 */
				else if( ascii_codepage == 65000 )
				{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_utf7_stream(
					          value_data,
					          value_data_size,
					          &value_string_size,
					          error );
#else
					result = libuna_utf8_string_size_from_utf7_stream(
					          value_data,
					          value_data_size,
					          &value_string_size,
					          error );
#endif
				}
				/* Codepage 1200 or 65001 represents UTF-8
				 */
				else if( ( ascii_codepage == 1200 )
				      || ( ascii_codepage == 65001 ) )
				{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_utf8_stream(
					          value_data,
					          value_data_size,
					          &value_string_size,
					          error );
#else
					result = libuna_utf8_string_size_from_utf8_stream(
					          value_data,
					          value_data_size,
					          &value_string_size,
					          error );
#endif
				}
				else
				{
					/* TODO currently libuna uses the same numeric values for the codepages as libfmapi
					 * add a mapping function if this implementation changes
					 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_byte_stream(
					          value_data,
					          value_data_size,
					          ascii_codepage,
					          &value_string_size,
					          error );
#else
					result = libuna_utf8_string_size_from_byte_stream(
					          value_data,
					          value_data_size,
					          ascii_codepage,
					          &value_string_size,
					          error );
#endif
				}
				/* TODO error tollerance required ? */
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to determine value string size.",
					 function );

					return( -1 );
				}
				value_string = system_string_allocate(
				                value_string_size );

				if( value_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create value string.",
					 function );

					return( -1 );
				}
				/* String is in UTF-16 little-endian
				 */
				if( is_ascii_string == 0 )
				{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_utf16_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  value_data,
						  value_data_size,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#else
					result = libuna_utf8_string_copy_from_utf16_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  value_data,
						  value_data_size,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#endif
				}
				/* Codepage 65000 represents UTF-7
				 */
				else if( ascii_codepage == 65000 )
				{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_utf7_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  value_data,
						  value_data_size,
						  error );
#else
					result = libuna_utf8_string_copy_from_utf7_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  value_data,
						  value_data_size,
						  error );
#endif
				}
				/* Codepage 1200 or 65001 represents UTF-8
				 */
				else if( ( ascii_codepage == 1200 )
				      || ( ascii_codepage == 65001 ) )
				{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_utf8_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  value_data,
						  value_data_size,
						  error );
#else
					result = libuna_utf8_string_copy_from_utf8_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  value_data,
						  value_data_size,
						  error );
#endif
				}
				else
				{
					/* TODO currently libuna uses the same numeric values for the codepages as libfmapi
					 * add a mapping function if this implementation changes
					 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_byte_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  value_data,
						  value_data_size,
						  (int) ascii_codepage,
						  error );
#else
					result = libuna_utf8_string_copy_from_byte_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  value_data,
						  value_data_size,
						  (int) ascii_codepage,
						  error );
#endif
				}
				/* TODO error tollerance required ? */
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set value string.",
					 function );

					memory_free(
					 value_string );

					return( -1 );
				}
				libcnotify_printf(
				 "ASCII string\t: %" PRIs_SYSTEM "\n\n",
				 value_string );

				memory_free(
				 value_string );
			}
			break;

		case 0x001f:
			if( value_data == NULL )
			{
				libcnotify_printf(
				 "Unicode string\t: <NULL>\n\n" );
			}
			else
			{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libuna_utf16_string_size_from_utf16_stream(
					  value_data,
					  value_data_size,
					  LIBUNA_ENDIAN_LITTLE,
					  &value_string_size,
					  error );
#else
				result = libuna_utf8_string_size_from_utf16_stream(
					  value_data,
					  value_data_size,
					  LIBUNA_ENDIAN_LITTLE,
					  &value_string_size,
					  error );
#endif

				/* TODO error tollerance required ? */
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to determine value string size.",
					 function );

					return( -1 );
				}
				value_string = system_string_allocate(
				                value_string_size );

				if( value_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create value string.",
					 function );

					return( -1 );
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libuna_utf16_string_copy_from_utf16_stream(
				          (libuna_utf16_character_t *) value_string,
				          value_string_size,
				          value_data,
				          value_data_size,
					  LIBUNA_ENDIAN_LITTLE,
				          error );
#else
				result = libuna_utf8_string_copy_from_utf16_stream(
				          (libuna_utf8_character_t *) value_string,
				          value_string_size,
				          value_data,
				          value_data_size,
					  LIBUNA_ENDIAN_LITTLE,
				          error );
#endif

				/* TODO error tollerance required ? */
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set value string.",
					 function );

					memory_free(
					 value_string );

					return( -1 );
				}
				libcnotify_printf(
				 "Unicode string\t: %" PRIs_SYSTEM "\n\n",
				 value_string );

				memory_free(
				 value_string );
			}
			break;

		case 0x0102:
			if( value_data == NULL )
			{
				libcnotify_printf(
				 "Binary data\t: <NULL>\n\n" );
			}
			else if( libfmapi_debug_print_binary_data_value(
			          entry_type,
			          value_type,
			          value_data,
			          value_data_size,
			          ascii_codepage,
			          error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print binary data MAPI value.",
				 function );

				return( -1 );
			}
			break;

		case 0x1002:
		case 0x1003:
		case 0x1014:
		case 0x1040:
		case 0x1048:
			if( libfmapi_debug_print_array_multi_value(
			     entry_type,
			     value_type,
			     value_data,
			     value_data_size,
			     ascii_codepage,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print MAPI array multi value.",
				 function );

				return( -1 );
			}
			break;

		case 0x101e:
		case 0x101f:
		case 0x1102:
			if( libfmapi_debug_print_element_multi_value(
			     entry_type,
			     value_type,
			     value_data,
			     value_data_size,
			     ascii_codepage,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print MAPI element multi value.",
				 function );

				return( -1 );
			}
			break;

		default:
			libcnotify_print_data(
			 value_data,
			 value_data_size,
			 0 );

			break;
	};
	return( 1 );
}

/* Prints the 32-bit signed integer MAPI value
 * Returns 1 if successful or -1 on error
 */
int libfmapi_debug_print_integer_32bit_value(
     uint32_t entry_type,
     uint32_t value_type,
     uint8_t *value_data,
     size_t value_data_size,
     libcerror_error_t **error )
{
	static char *function = "libfmapi_debug_print_integer_32bit_value";
	uint32_t value_32bit  = 0;

	if( value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value data.",
		 function );

		return( -1 );
	}
	if( value_type != 0x0003 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value type.",
		 function );

		return( -1 );
	}
	if( value_data_size != 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 value_data,
	 value_32bit );

	switch( entry_type )
	{
		case 0x0001:
			libcnotify_printf(
			 "Acknowledgment mode\t: " );

			switch( value_32bit )
			{
				case 0:
					libcnotify_printf(
					 "Manual" );

					break;

				case 1:
					libcnotify_printf(
					 "Automatic" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x0017:
			libcnotify_printf(
			 "Importance\t: " );

			switch( value_32bit )
			{
				case 0:
					libcnotify_printf(
					 "Low (IMPORTANCE_LOW)" );

					break;

				case 1:
					libcnotify_printf(
					 "Normal (IMPORTANCE_NORMAL)" );

					break;

				case 2:
					libcnotify_printf(
					 "High (IMPORTANCE_HIGH)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x0026:
			libcnotify_printf(
			 "Priority\t: " );

			switch( value_32bit )
			{
				case (uint32_t) -1:
					libcnotify_printf(
					 "Non urgent (PRIO_NONURGENT)" );

					break;

				case 0:
					libcnotify_printf(
					 "Normal (PRIO_NORMAL)" );

					break;

				case 1:
					libcnotify_printf(
					 "Urgent (PRIO_URGENT)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRId32 "",
					 (int32_t) value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x002e:
		case 0x0036:
			libcnotify_printf(
			 "Sensitivity\t: " );

			switch( value_32bit )
			{
				case 0:
					libcnotify_printf(
					 "None (SENSITIVITY_NONE)" );

					break;

				case 1:
					libcnotify_printf(
					 "Personal (SENSITIVITY_PERSONAL)" );

					break;

				case 2:
					libcnotify_printf(
					 "Private (SENSITIVITY_PRIVATE)" );

					break;

				case 3:
					libcnotify_printf(
					 "Company confidential (SENSITIVITY_COMPANY_CONFIDENTIAL)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x0c15:
			libcnotify_printf(
			 "Recipient type\t: " );

			switch( value_32bit & 0x0fffffff )
			{
				case 0:
					libcnotify_printf(
					 "Originator (MAPI_ORIG)" );

					break;

				case 1:
					libcnotify_printf(
					 "To (MAPI_TO)" );

					break;

				case 2:
					libcnotify_printf(
					 "CC (MAPI_CC)" );

					break;

				case 3:
					libcnotify_printf(
					 "BCC (MAPI_BCC)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			if( ( value_32bit & 0x10000000L ) != 0 )
			{
				libcnotify_printf(
				 "\tResend (MAPI_P1)\n" );
			}
			if( ( value_32bit & 0x80000000L ) != 0 )
			{
				libcnotify_printf(
				 "\tAlready processed (MAPI_SUBMITTED)\n" );
			}
			break;

		case 0x0e07:
			libcnotify_printf(
			 "Message flags\t: 0x%08" PRIx32 "\n",
			 value_32bit );

			if( ( value_32bit & 0x000000001 ) != 0 )
			{
				libcnotify_printf(
				 "\tRead (MSGFLAG_READ)\n" );
			}
			if( ( value_32bit & 0x000000002 ) != 0 )
			{
				libcnotify_printf(
				 "\tUnmodified (MSGFLAG_UNMODIFIED)\n" );
			}
			if( ( value_32bit & 0x000000004 ) != 0 )
			{
				libcnotify_printf(
				 "\tSubmit (MSGFLAG_SUBMIT)\n" );
			}
			if( ( value_32bit & 0x000000008 ) != 0 )
			{
				libcnotify_printf(
				 "\tUnsent (MSGFLAG_UNSENT)\n" );
			}
			if( ( value_32bit & 0x000000010 ) != 0 )
			{
				libcnotify_printf(
				 "\tHas attachment(s) (MSGFLAG_HASATTACH)\n" );
			}
			if( ( value_32bit & 0x000000020 ) != 0 )
			{
				libcnotify_printf(
				 "\tFrom me (MSGFLAG_FROMME)\n" );
			}
			if( ( value_32bit & 0x000000040 ) != 0 )
			{
				libcnotify_printf(
				 "\tAssociated (MSGFLAG_ASSOCIATED)\n" );
			}
			if( ( value_32bit & 0x000000080 ) != 0 )
			{
				libcnotify_printf(
				 "\tResend (MSGFLAG_RESEND)\n" );
			}
			if( ( value_32bit & 0x000000100 ) != 0 )
			{
				libcnotify_printf(
				 "\tRead notification pending (MSGFLAG_RN_PENDING)\n" );
			}
			if( ( value_32bit & 0x000000200 ) != 0 )
			{
				libcnotify_printf(
				 "\tNon-Read notification pending (MSGFLAG_NRN_PENDING)\n" );
			}

			if( ( value_32bit & 0x000001000 ) != 0 )
			{
				libcnotify_printf(
				 "\tOrigin X.400 (MSGFLAG_ORIGIN_X400)\n" );
			}
			if( ( value_32bit & 0x000002000 ) != 0 )
			{
				libcnotify_printf(
				 "\tOrigin Internet (MSGFLAG_ORIGIN_INTERNET)\n" );
			}

			if( ( value_32bit & 0x000008000 ) != 0 )
			{
				libcnotify_printf(
				 "\tOrigin external (MSGFLAG_ORIGIN_MISC_EXT)\n" );
			}
			break;

		case 0x0e14:
			libcnotify_printf(
			 "Message submit flags\t: 0x%08" PRIx32 "\n",
			 value_32bit );

			if( ( value_32bit & 0x000000001 ) != 0 )
			{
				libcnotify_printf(
				 "\tLocked by MAPI spooler (SUBMITFLAG_LOCKED)\n" );
			}
			if( ( value_32bit & 0x000000002 ) != 0 )
			{
				libcnotify_printf(
				 "\tPreprocessing needed (SUBMITFLAG_PREPROCESS)\n" );
			}
			break;

		case 0x0e17:
			libcnotify_printf(
			 "Message status flags\t: 0x%08" PRIx32 "\n",
			 value_32bit );

			if( ( value_32bit & 0x000000001 ) != 0 )
			{
				libcnotify_printf(
				 "\tHighlighted (MSGSTATUS_HIGHLIGHTED)\n" );
			}
			if( ( value_32bit & 0x000000002 ) != 0 )
			{
				libcnotify_printf(
				 "\tTagged (MSGSTATUS_TAGGED)\n" );
			}
			if( ( value_32bit & 0x000000004 ) != 0 )
			{
				libcnotify_printf(
				 "\tHidden (MSGSTATUS_HIDDEN)\n" );
			}
			if( ( value_32bit & 0x000000008 ) != 0 )
			{
				libcnotify_printf(
				 "\tMarked for deletion (MSGSTATUS_DELMARKED)\n" );
			}

			if( ( value_32bit & 0x000000100 ) != 0 )
			{
				libcnotify_printf(
				 "\tDraft (MSGSTATUS_DRAFT)\n" );
			}
			if( ( value_32bit & 0x000000200 ) != 0 )
			{
				libcnotify_printf(
				 "\tHas been answered (MSGSTATUS_ANSWERED)\n" );
			}

			if( ( value_32bit & 0x000001000 ) != 0 )
			{
				libcnotify_printf(
				 "\tMarked for download from server (MSGSTATUS_REMOTE_DOWNLOAD)\n" );
			}
			if( ( value_32bit & 0x000002000 ) != 0 )
			{
				libcnotify_printf(
				 "\tMarked for deletion on server (MSGSTATUS_REMOTE_DELETE)\n" );
			}
			break;

		case 0x0ff4:
			libcnotify_printf(
			 "Access flags\t: 0x%08" PRIx32 "\n",
			 value_32bit );

			if( ( value_32bit & 0x000000001 ) != 0 )
			{
				libcnotify_printf(
				 "\tWrite (MAPI_ACCESS_MODIFY)\n" );
			}
			if( ( value_32bit & 0x000000002 ) != 0 )
			{
				libcnotify_printf(
				 "\tRead (MAPI_ACCESS_READ)\n" );
			}
			if( ( value_32bit & 0x000000004 ) != 0 )
			{
				libcnotify_printf(
				 "\tDeletion (MAPI_ACCESS_DELETE)\n" );
			}
			if( ( value_32bit & 0x000000008 ) != 0 )
			{
				libcnotify_printf(
				 "\tCreate folder (MAPI_ACCESS_CREATE_HIERARCHY)\n" );
			}
			if( ( value_32bit & 0x000000010 ) != 0 )
			{
				libcnotify_printf(
				 "\tCreate message (MAPI_ACCESS_CREATE_CONTENTS)\n" );
			}
			if( ( value_32bit & 0x000000020 ) != 0 )
			{
				libcnotify_printf(
				 "\tCreate associated item (MAPI_ACCESS_CREATE_ASSOCIATED)\n" );
			}
			break;

		case 0x0ffe:
			libcnotify_printf(
			 "Object type\t: " );

			switch( value_32bit )
			{
				case 1:
					libcnotify_printf(
					 "Message store (MAPI_STORE)" );

					break;

				case 2:
					libcnotify_printf(
					 "Address book (MAPI_ADDRBOOK)" );

					break;

				case 3:
					libcnotify_printf(
					 "Folder (MAPI_FOLDER)" );

					break;

				case 4:
					libcnotify_printf(
					 "Address book container (MAPI_ABCONT)" );

					break;

				case 5:
					libcnotify_printf(
					 "Message (MAPI_MESSAGE)" );

					break;

				case 6:
					libcnotify_printf(
					 "Recipient (MAPI_MAILUSER)" );

					break;

				case 7:
					libcnotify_printf(
					 "Attachment (MAPI_ATTACH)" );

					break;

				case 8:
					libcnotify_printf(
					 "Distribution list (MAPI_DISTLIST)" );

					break;

				case 9:
					libcnotify_printf(
					 "Profile section (MAPI_PROFSECT)" );

					break;

				case 10:
					libcnotify_printf(
					 "Status object (MAPI_STATUS)" );

					break;

				case 11:
					libcnotify_printf(
					 "Session (MAPI_SESSION)" );

					break;

				case 12:
					libcnotify_printf(
					 "Form information (MAPI_FORMINFO)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x1080:
			libcnotify_printf(
			 "Icon index\t: " );

			switch( value_32bit )
			{
				case 0x00000001:
					libcnotify_printf(
					 "Post" );

					break;

				case 0x00000003:
					libcnotify_printf(
					 "Other" );

					break;

				case 0x00000100:
					libcnotify_printf(
					 "Read mail" );

					break;

				case 0x00000101:
					libcnotify_printf(
					 "Unread mail" );

					break;

				case 0x00000102:
					libcnotify_printf(
					 "Submitted mail" );

					break;

				case 0x00000103:
					libcnotify_printf(
					 "Unsent mail" );

					break;

				case 0x00000104:
					libcnotify_printf(
					 "Receipt mail" );

					break;

				case 0x00000105:
					libcnotify_printf(
					 "Replied mail" );

					break;

				case 0x00000106:
					libcnotify_printf(
					 "Forwarded mail" );

					break;

				case 0x00000107:
					libcnotify_printf(
					 "Remote mail" );

					break;

				case 0x00000108:
					libcnotify_printf(
					 "Delivery mail" );

					break;

				case 0x00000109:
					libcnotify_printf(
					 "Read mail" );

					break;

				case 0x0000010a:
					libcnotify_printf(
					 "Nondelivery mail" );

					break;

				case 0x0000010b:
					libcnotify_printf(
					 "Nonread mail" );

					break;

				case 0x0000010c:
					libcnotify_printf(
					 "Recall_S mail" );

					break;

				case 0x0000010d:
					libcnotify_printf(
					 "Recall_F mail" );

					break;

				case 0x0000010e:
					libcnotify_printf(
					 "Tracking mail" );

					break;

				case 0x0000011b:
					libcnotify_printf(
					 "Out of office mail" );

					break;

				case 0x0000011c:
					libcnotify_printf(
					 "Recall mail" );

					break;

				case 0x00000130:
					libcnotify_printf(
					 "Tracked mail" );

					break;

				case 0x00000200:
					libcnotify_printf(
					 "Contact" );

					break;

				case 0x00000202:
					libcnotify_printf(
					 "Distribution list" );

					break;

				case 0x00000300:
					libcnotify_printf(
					 "Sticky note blue" );

					break;

				case 0x00000301:
					libcnotify_printf(
					 "Sticky note green" );

					break;

				case 0x00000302:
					libcnotify_printf(
					 "Sticky note pink" );

					break;

				case 0x00000303:
					libcnotify_printf(
					 "Sticky note yellow" );

					break;

				case 0x00000304:
					libcnotify_printf(
					 "Sticky note white" );

					break;

				case 0x00000400:
					libcnotify_printf(
					 "Single instance appointment" );

					break;

				case 0x00000401:
					libcnotify_printf(
					 "Recurring appointment" );

					break;

				case 0x00000402:
					libcnotify_printf(
					 "Single instance meeting" );

					break;

				case 0x00000403:
					libcnotify_printf(
					 "Recurring meeting" );

					break;

				case 0x00000404:
					libcnotify_printf(
					 "Meeting request" );

					break;

				case 0x00000405:
					libcnotify_printf(
					 "Accept" );

					break;

				case 0x00000406:
					libcnotify_printf(
					 "Decline" );

					break;

				case 0x00000407:
					libcnotify_printf(
					 "Tentativly" );

					break;

				case 0x00000408:
					libcnotify_printf(
					 "Cancellation" );

					break;

				case 0x00000409:
					libcnotify_printf(
					 "Informational update" );

					break;

				case 0x00000500:
					libcnotify_printf(
					 "Task/task" );

					break;

				case 0x00000501:
					libcnotify_printf(
					 "Unassigned recurring task" );

					break;

				case 0x00000502:
					libcnotify_printf(
					 "Assignee's task" );

					break;

				case 0x00000503:
					libcnotify_printf(
					 "Assigner's task" );

					break;

				case 0x00000504:
					libcnotify_printf(
					 "Task request" );

					break;

				case 0x00000505:
					libcnotify_printf(
					 "Task acceptance" );

					break;

				case 0x00000506:
					libcnotify_printf(
					 "Task rejection" );

					break;

				case 0x00000601:
					libcnotify_printf(
					 "Journal conversation" );

					break;

				case 0x00000602:
					libcnotify_printf(
					 "Journal e-mail message" );

					break;

				case 0x00000603:
					libcnotify_printf(
					 "Journal meeting request" );

					break;

				case 0x00000604:
					libcnotify_printf(
					 "Journal meeting response" );

					break;

				case 0x00000606:
					libcnotify_printf(
					 "Journal task request" );

					break;

				case 0x00000607:
					libcnotify_printf(
					 "Journal task response" );

					break;

				case 0x00000608:
					libcnotify_printf(
					 "Journal note" );

					break;

				case 0x00000609:
					libcnotify_printf(
					 "Journal fax" );

					break;

				case 0x0000060a:
					libcnotify_printf(
					 "Journal phone call" );

					break;

				case 0x0000060c:
					libcnotify_printf(
					 "Journal letter" );

					break;

				case 0x0000060d:
					libcnotify_printf(
					 "Journal Microsoft Office Word" );

					break;

				case 0x0000060e:
					libcnotify_printf(
					 "Journal Microsoft Office Excel" );

					break;

				case 0x0000060f:
					libcnotify_printf(
					 "Journal Microsoft Office PowerPoint" );

					break;

				case 0x00000610:
					libcnotify_printf(
					 "Journal Microsoft Office Access" );

					break;

				case 0x00000612:
					libcnotify_printf(
					 "Journal document" );

					break;

				case 0x00000613:
					libcnotify_printf(
					 "Journal meeting" );

					break;

				case 0x00000614:
					libcnotify_printf(
					 "Journal meeting cancellation" );

					break;

				case 0x00000615:
					libcnotify_printf(
					 "Journal remote session" );

					break;

				case 0xffffffff:
					libcnotify_printf(
					 "New mail" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x3009:
			/* TODO determine difference between message service and service provider, but how ?
			 */
			libcnotify_printf(
			 "Resource flags\t: 0x%08" PRIx32 "\n",
			 value_32bit );

			if( ( value_32bit & 0x000000001 ) != 0 )
			{
				libcnotify_printf(
				 "\t(SERVICE_DEFAULT_STORE or STATUS_DEFAULT_OUTBOUND)\n" );
			}
			if( ( value_32bit & 0x000000002 ) != 0 )
			{
				libcnotify_printf(
				 "\t(SERVICE_SINGLE_COPY or STATUS_DEFAULT_STORE)\n" );
			}
			if( ( value_32bit & 0x000000004 ) != 0 )
			{
				libcnotify_printf(
				 "\t(SERVICE_CREATE_WITH_STORE or STATUS_PRIMARY_IDENTITY)\n" );
			}
			if( ( value_32bit & 0x000000008 ) != 0 )
			{
				libcnotify_printf(
				 "\t(SERVICE_PRIMARY_IDENTITY or STATUS_SIMPLE_STORE)\n" );
			}
			if( ( value_32bit & 0x000000010 ) != 0 )
			{
				libcnotify_printf(
				 "\t(_UNKNOWN_ or STATUS_XP_PREFER_LAST)\n" );
			}
			if( ( value_32bit & 0x000000020 ) != 0 )
			{
				libcnotify_printf(
				 "\t(SERVICE_NO_PRIMARY_IDENTITY or STATUS_NO_PRIMARY_IDENTITY)\n" );
			}
			if( ( value_32bit & 0x000000040 ) != 0 )
			{
				libcnotify_printf(
				 "\t(_UNKNOWN_ or STATUS_NO_DEFAULT_STORE)\n" );
			}
			if( ( value_32bit & 0x000000080 ) != 0 )
			{
				libcnotify_printf(
				 "\t(_UNKNOWN_ or STATUS_TEMP_SECTION)\n" );
			}
			if( ( value_32bit & 0x000000100 ) != 0 )
			{
				libcnotify_printf(
				 "\t(_UNKNOWN_ or STATUS_OWN_STORE)\n" );
			}
			if( ( value_32bit & 0x000000200 ) != 0 )
			{
				libcnotify_printf(
				 "\t(_UNKNOWN_ or HOOK_INBOUND)\n" );
			}
			if( ( value_32bit & 0x000000400 ) != 0 )
			{
				libcnotify_printf(
				 "\t(_UNKNOWN_ or HOOK_OUTBOUND)\n" );
			}
			if( ( value_32bit & 0x000000800 ) != 0 )
			{
				libcnotify_printf(
				 "\t(_UNKNOWN_ or STATUS_NEED_IPM_TREE)\n" );
			}
			if( ( value_32bit & 0x000001000 ) != 0 )
			{
				libcnotify_printf(
				 "\t(_UNKNOWN_ or STATUS_PRIMARY_STORE)\n" );
			}
			if( ( value_32bit & 0x000002000 ) != 0 )
			{
				libcnotify_printf(
				 "\t(_UNKNOWN_ or STATUS_SECONDARY_STORE)\n" );
			}
			break;

		case 0x340d:
		case 0x6611:
			libcnotify_printf(
			 "Message store characteristics flags\t: 0x%08" PRIx32 "\n",
			 value_32bit );

			if( ( value_32bit & 0x000000001 ) != 0 )
			{
				libcnotify_printf(
				 "\tEntry identifiers are unique, not reused (STORE_ENTRYID_UNIQUE)\n" );
			}
			if( ( value_32bit & 0x000000002 ) != 0 )
			{
				libcnotify_printf(
				 "\tRead-only (STORE_READONLY)\n" );
			}
			if( ( value_32bit & 0x000000004 ) != 0 )
			{
				libcnotify_printf(
				 "\tSearch-result folders support (STORE_SEARCH_OK)\n" );
			}
			if( ( value_32bit & 0x000000008 ) != 0 )
			{
				libcnotify_printf(
				 "\tMessage modification support (STORE_MODIFY_OK)\n" );
			}
			if( ( value_32bit & 0x000000010 ) != 0 )
			{
				libcnotify_printf(
				 "\tMessage creation support (STORE_CREATE_OK)\n" );
			}
			if( ( value_32bit & 0x000000020 ) != 0 )
			{
				libcnotify_printf(
				 "\tAttachment support (STORE_ATTACH_OK)\n" );
			}
			if( ( value_32bit & 0x000000040 ) != 0 )
			{
				libcnotify_printf(
				 "\tOLE attachment support (STORE_OLE_OK)\n" );
			}
			if( ( value_32bit & 0x000000080 ) != 0 )
			{
				libcnotify_printf(
				 "\tMessage submission marking support (STORE_SUBMIT_OK)\n" );
			}
			if( ( value_32bit & 0x000000100 ) != 0 )
			{
				libcnotify_printf(
				 "\tNotification support (STORE_NOTIFY_OK)\n" );
			}
			if( ( value_32bit & 0x000000200 ) != 0 )
			{
				libcnotify_printf(
				 "\tMulti-value property support (STORE_MV_PROPS_OK)\n" );
			}
			if( ( value_32bit & 0x000000400 ) != 0 )
			{
				libcnotify_printf(
				 "\tCategorized view support (STORE_CATEGORIZE_OK)\n" );
			}
			if( ( value_32bit & 0x000000800 ) != 0 )
			{
				libcnotify_printf(
				 "\tCompressed RTF message support (STORE_RTF_OK)\n" );
			}
			if( ( value_32bit & 0x000001000 ) != 0 )
			{
				libcnotify_printf(
				 "\tRestriction support (STORE_RESTRICTION_OK)\n" );
			}
			if( ( value_32bit & 0x000002000 ) != 0 )
			{
				libcnotify_printf(
				 "\tSorting view support (STORE_SORT_OK)\n" );
			}
			if( ( value_32bit & 0x000004000 ) != 0 )
			{
				libcnotify_printf(
				 "\tFolders are public, multi-user accessible (STORE_PUBLIC_FOLDERS)\n" );
			}
			if( ( value_32bit & 0x000008000 ) != 0 )
			{
				libcnotify_printf(
				 "\tUncompressed RTF message support (STORE_UNCOMPRESSED_RTF)\n" );
			}
			if( ( value_32bit & 0x000010000 ) != 0 )
			{
				libcnotify_printf(
				 "\tHTML message support (STORE_HTML_OK)\n" );
			}
			if( ( value_32bit & 0x000020000 ) != 0 )
			{
				libcnotify_printf(
				 "\t8-bit extended ASCII string support (STORE_ANSI_OK)\n" );
			}
			if( ( value_32bit & 0x000040000 ) != 0 )
			{
				libcnotify_printf(
				 "\tUTF-16 little-endian string support (STORE_UNICODE_OK)\n" );
			}
			if( ( value_32bit & 0x000080000 ) != 0 )
			{
				libcnotify_printf(
				 "\tReserved (STORE_LOCALSTORE)\n" );
			}

			if( ( value_32bit & 0x000200000 ) != 0 )
			{
				libcnotify_printf(
				 "\tItem processing support (STORE_ITEMPROC)\n" );
			}

			if( ( value_32bit & 0x000800000 ) != 0 )
			{
				libcnotify_printf(
				 "\tChange push support, no index crawling (STORE_PUSHER_OK)\n" );
			}
			break;

		case 0x35df:
			libcnotify_printf(
			 "Valid folder mask\t: 0x%08" PRIx32 "\n",
			 value_32bit );

			if( ( value_32bit & 0x000000001 ) != 0 )
			{
				libcnotify_printf(
				 "\tSubtree (FOLDER_IPM_SUBTREE_VALID)\n" );
			}
			if( ( value_32bit & 0x000000002 ) != 0 )
			{
				libcnotify_printf(
				 "\tInbox (FOLDER_IPM_INBOX_VALID)\n" );
			}
			if( ( value_32bit & 0x000000004 ) != 0 )
			{
				libcnotify_printf(
				 "\tOutbox (FOLDER_IPM_OUTBOX_VALID)\n" );
			}
			if( ( value_32bit & 0x000000008 ) != 0 )
			{
				libcnotify_printf(
				 "\tDeleted Items (FOLDER_IPM_WASTEBOX_VALID)\n" );
			}
			if( ( value_32bit & 0x000000010 ) != 0 )
			{
				libcnotify_printf(
				 "\tSent Items (FOLDER_IPM_SENTMAIL_VALID)\n" );
			}
			if( ( value_32bit & 0x000000020 ) != 0 )
			{
				libcnotify_printf(
				 "\tViews (FOLDER_VIEWS_VALID)\n" );
			}
			if( ( value_32bit & 0x000000040 ) != 0 )
			{
				libcnotify_printf(
				 "\tCommon views (FOLDER_COMMON_VIEWS_VALID)\n" );
			}
			if( ( value_32bit & 0x000000080 ) != 0 )
			{
				libcnotify_printf(
				 "\tFinder (FOLDER_FINDER_VALID)\n" );
			}
			break;

		case 0x3600:
			libcnotify_printf(
			 "Containter flags\t: 0x%08" PRIx32 "\n",
			 value_32bit );

			if( ( value_32bit & 0x000000001 ) != 0 )
			{
				libcnotify_printf(
				 "\tCan have recipients (AB_RECIPIENTS)\n" );
			}
			if( ( value_32bit & 0x000000002 ) != 0 )
			{
				libcnotify_printf(
				 "\tCan have sub containers (AB_SUBCONTAINERS)\n" );
			}
			if( ( value_32bit & 0x000000004 ) != 0 )
			{
				libcnotify_printf(
				 "\tCan be modified (AB_MODIFIABLE)\n" );
			}
			if( ( value_32bit & 0x000000008 ) != 0 )
			{
				libcnotify_printf(
				 "\tCannot be modified (AB_UNMODIFIABLE)\n" );
			}
			if( ( value_32bit & 0x000000010 ) != 0 )
			{
				libcnotify_printf(
				 "\tRequest restriction (AB_FIND_ON_OPEN)\n" );
			}
			if( ( value_32bit & 0x000000020 ) != 0 )
			{
				libcnotify_printf(
				 "\tIs default (AB_NOT_DEFAULT)\n" );
			}
			break;

		case 0x3601:
			libcnotify_printf(
			 "Folder type\t: " );

			switch( value_32bit )
			{
				case 0:
					libcnotify_printf(
					 "Root (FOLDER_ROOT)" );

					break;

				case 1:
					libcnotify_printf(
					 "Generic (FOLDER_GENERIC)" );

					break;

				case 2:
					libcnotify_printf(
					 "Search (FOLDER_SEARCH)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x3705:
			libcnotify_printf(
			 "Attachment method\t: " );

			switch( value_32bit )
			{
				case 0:
					libcnotify_printf(
					 "None (NO_ATTACHMENT)" );

					break;

				case 1:
					libcnotify_printf(
					 "By value (ATTACH_BY_VALUE)" );

					break;

				case 2:
					libcnotify_printf(
					 "By reference (ATTACH_BY_REFERENCE)" );

					break;

				case 3:
					libcnotify_printf(
					 "By reference resolve (ATTACH_BY_REF_RESOLVE)" );

					break;

				case 4:
					libcnotify_printf(
					 "By reference only (ATTACH_BY_REF_ONLY)" );

					break;

				case 5:
					libcnotify_printf(
					 "Embedded message (ATTACH_EMBEDDED_MSG)" );

					break;

				case 6:
					libcnotify_printf(
					 "OLE (ATTACH_OLE)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x3a4d:
			libcnotify_printf(
			 "Gender\t: " );

			switch( value_32bit )
			{
				case 0:
					libcnotify_printf(
					 "Unspecified (genderUnspecified)" );

					break;

				case 1:
					libcnotify_printf(
					 "Female (genderFemale)" );

					break;

				case 2:
					libcnotify_printf(
					 "Male (genderMale)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x3fde:
		case 0x3ffd:
			libcnotify_printf(
			 "Codepage\t: %s (%s)\n",
			 libfmapi_codepage_get_description(
			  value_32bit ),
			 libfmapi_codepage_get_identifier(
			  value_32bit ) );

			break;

		case 0x5909:
			libcnotify_printf(
			 "Message editor format\t: " );

			switch( value_32bit )
			{
				case 0:
					libcnotify_printf(
					 "Unknown editor (EDITOR_FORMAT_DONTKNOW)" );

					break;

				case 1:
					libcnotify_printf(
					 "Plain text editor (EDITOR_FORMAT_PLAINTEXT)" );

					break;

				case 2:
					libcnotify_printf(
					 "HTML editor (EDITOR_FORMAT_HTML)" );

					break;

				case 3:
					libcnotify_printf(
					 "Rich text (RTF) editor (EDITOR_FORMAT_RTF)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		case 0x6623:
			libcnotify_printf(
			 "RPC over HTTP (ROH) flags\t: 0x%08" PRIx32 "\n",
			 value_32bit );

			if( ( value_32bit & 0x000000001 ) != 0 )
			{
				libcnotify_printf(
				 "\tUse RPC over HTTP (ROHFLAGS_USE_ROH)\n" );
			}
			if( ( value_32bit & 0x000000002 ) != 0 )
			{
				libcnotify_printf(
				 "\tOnly use SSL (ROHFLAGS_SSL_ONLY)\n" );
			}
			if( ( value_32bit & 0x000000004 ) != 0 )
			{
				libcnotify_printf(
				 "\tUse SSL mutual authentication (ROHFLAGS_MUTUAL_AUTH)\n" );
			}
			if( ( value_32bit & 0x000000008 ) != 0 )
			{
				libcnotify_printf(
				 "\tOn fast networks use HTTP first (ROHFLAGS_HTTP_FIRST_ON_FAST)\n" );
			}

			if( ( value_32bit & 0x000000020 ) != 0 )
			{
				libcnotify_printf(
				 "\tOn slow networks use HTTP first (ROHFLAGS_HTTP_FIRST_ON_SLOW)\n" );
			}
			break;

		case 0x6627:
			libcnotify_printf(
			 "RPC over HTTP (ROH) authentication scheme\t: " );

			switch( value_32bit )
			{
				case 0:
					libcnotify_printf(
					 "Basic authentication (ROHAUTH_BASIC)" );

					break;

				case 1:
					libcnotify_printf(
					 "NTLM authentication (ROHAUTH_NTLM)" );

					break;

				default:
					libcnotify_printf(
					 "%" PRIu32 "",
					 value_32bit );

					break;
			}
			libcnotify_printf(
			 "\n" );

			break;

		/* TODO Appointment color 0x00008214 */
		/* TODO Appointment response status 0x00008218 */

		default:
			libcnotify_printf(
			 "Integer 32-bit signed\t: %" PRId32 "\n",
			 (int32_t) value_32bit );

			break;
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

/* Prints the binary data MAPI value
 * Returns 1 if successful or -1 on error
 */
int libfmapi_debug_print_binary_data_value(
     uint32_t entry_type,
     uint32_t value_type,
     uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	uint8_t filetime_buffer[ 8 ];

	system_character_t filetime_string[ 32 ];
	system_character_t guid_string[ 48 ];
	system_character_t sid_string[ 128 ];

	libfdatetime_filetime_t *delta_filetime = NULL;
	libfdatetime_filetime_t *filetime       = NULL;
	libfguid_identifier_t *guid             = NULL;
	libfwnt_security_identifier_t *sid      = NULL;
	system_character_t *value_string        = NULL;
	uint8_t *rtf_value_string               = NULL;
	uint8_t *value_data_pointer             = NULL;
	static char *function                   = "libfmapi_debug_print_binary_data_value";
	size_t rtf_value_string_size            = 0;
	size_t sid_string_size                  = 0;
	size_t value_data_iterator              = 0;
	size_t value_string_size                = 0;
	uint64_t value_64bit                    = 0;
	uint32_t entries_size                   = 0;
	uint32_t number_of_values               = 0;
	uint32_t value_32bit                    = 0;
	uint32_t value_iterator                 = 0;
	uint16_t value_16bit                    = 0;
	uint8_t data_size                       = 0;
	int list_iterator                       = 0;
	int result                              = 0;

	if( value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value data.",
		 function );

		return( -1 );
	}
	if( value_type != 0x0102 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value type.",
		 function );

		return( -1 );
	}
	if( value_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: value data size exceeds maximum.",
		 function );

		return( -1 );
	}
	switch( entry_type )
	{
		case 0x000b:
		case 0x0025:
		case 0x0e30:
		case 0x0ff9:
		case 0x300b:
		case 0x683f:
		case 0x6842:
			if( value_data == NULL )
			{
				libcnotify_printf(
				 "GUID\t: <NULL>\n\n" );
			}
			else  if( value_data_size == 16 )
			{
				if( libfguid_identifier_initialize(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create GUID.",
					 function );

					return( -1 );
				}
				if( libfguid_identifier_copy_from_byte_stream(
				     guid,
				     value_data,
				     value_data_size,
				     LIBFGUID_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to GUID.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				value_data      += 16;
				value_data_size -= 16;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfguid_identifier_copy_to_utf16_string(
					  guid,
					  (uint16_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#else
				result = libfguid_identifier_copy_to_utf8_string(
					  guid,
					  (uint8_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy GUID to string.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				if( libfguid_identifier_free(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free GUID.",
					 function );

					return( -1 );
				}
				libcnotify_printf(
				 "GUID\t: %" PRIs_SYSTEM "\n\n",
				 guid_string );
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x003b:
		case 0x0051:
		case 0x0052:
		case 0x0c1d:
			libcnotify_printf(
			 "ASCII string\t: " );

			for( value_data_iterator = 0;
			     value_data_iterator < value_data_size;
			     value_data_iterator++ )
			{
				if( value_data[ value_data_iterator ] != 0 )
				{
					libcnotify_printf(
					 "%c",
					 (char) value_data[ value_data_iterator ] );
				}
			}
			libcnotify_printf(
			 "\n" );
			libcnotify_printf(
			 "\n" );

			break;

		case 0x003f:
		case 0x0041:
		case 0x0043:
		case 0x0045:
		case 0x0046:
		case 0x004c:
		case 0x0c19:
		case 0x0e34:
		case 0x0e0a:
		case 0x0fff:
		case 0x3ff9:
		case 0x3ffb:
		case 0x3416:
		case 0x35e0:
		case 0x35e2:
		case 0x35e3:
		case 0x35e4:
		case 0x35e5:
		case 0x35e6:
		case 0x35e7:
		case 0x36d0:
		case 0x36d1:
		case 0x36d2:
		case 0x36d3:
		case 0x36d4:
		case 0x36d5:
		case 0x36d6:
		case 0x36d7:
		case 0x3ff0:
		case 0x5ff7:
		case 0x7c07:
		case 0x8081:
		case 0x8085:
		case 0x8091:
		case 0x8095:
		case 0x80a1:
		case 0x80a5:
		case 0x80b5:
		case 0x80c5:
		case 0x80d5:
		/* 0x1102 */
		case 0x1098:
		case 0x36d8:
		case 0x36e4:
		case 0x8054:
		case 0x8055:
			if( value_data_size >= 20 )
			{
				if( libfmapi_debug_print_entry_identifier(
				     value_data,
				     value_data_size,
				     ascii_codepage,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print entry identifier.",
					 function );

					return( -1 );
				}
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x004f:
			if( value_data_size >= 8 )
			{
				value_data_pointer = value_data;

				byte_stream_copy_to_uint32_little_endian(
				 value_data_pointer,
				 number_of_values );

				value_data_pointer += 4;

				byte_stream_copy_to_uint32_little_endian(
				 value_data_pointer,
				 entries_size );

				value_data_pointer += 4;

				if( entries_size < ( value_data_size - 8 ) )
				{
					value_data_size -= 8;

					libcnotify_printf(
					 "Number of entries\t: %" PRIu32 "\n",
					 number_of_values );

					libcnotify_printf(
					 "Size of entries\t\t: %" PRIu32 "\n",
					 entries_size );

					for( value_iterator = 0;
					     value_iterator < number_of_values;
					     value_iterator++ )
					{
						byte_stream_copy_to_uint32_little_endian(
						 value_data_pointer,
						 value_32bit );

						value_data_pointer += 4;
						value_data_size    -= 4;
						entries_size       -= 4;

						if( ( value_32bit > entries_size )
						 || ( value_32bit > value_data_size ) )
						{
							libcnotify_printf(
							 "Entry: %02" PRIu32 " size\t\t: %" PRIu32 " <OUT OF BOUNDS>\n",
							 value_iterator,
							 value_32bit );

							break;
						}
						libcnotify_printf(
						 "Entry: %02" PRIu32 " size\t\t: %" PRIu32 "\n",
						 value_iterator,
						 value_32bit );

						libcnotify_printf(
						 "Entry: %02" PRIu32 " data:\n",
						 value_iterator );
						libcnotify_print_data(
						 value_data_pointer,
						 value_32bit,
						 0 );

						value_data_pointer += value_32bit;
						value_data_size    -= value_32bit;
						entries_size       -= value_32bit;
					}
					if( value_data_size > 0 )
					{
						libcnotify_printf(
						 "trailing data:\n" );
						libcnotify_print_data(
						 value_data_pointer,
						 value_data_size,
						 0 );
					}
				}
				else
				{
					libcnotify_print_data(
					 value_data,
					 value_data_size,
					 0 );
				}
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x0071:
			if( value_data_size >= 22 )
			{
				/* According to MSDN the first byte is reserved
				 * and should always be 0x01 however it makes
				 * more sense that it's the most significant
				 * part of the current system filetime data
				 */
				if( value_data[ 0 ] == 0x01 )
				{
					if( libfdatetime_filetime_initialize(
					     &filetime,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create filetime.",
						 function );

						return( -1 );
					}
					if( libfdatetime_filetime_initialize(
					     &delta_filetime,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create delta filetime.",
						 function );

						libfdatetime_filetime_free(
						 &filetime,
						 NULL );

						return( -1 );
					}
					libcnotify_printf(
					 "Header block:\n" );

					/* The current system file data is in big-endian
					 */
					filetime_buffer[ 0 ] = 0;
					filetime_buffer[ 1 ] = 0;
					filetime_buffer[ 2 ] = value_data[ 5 ];
					filetime_buffer[ 3 ] = value_data[ 4 ];
					filetime_buffer[ 4 ] = value_data[ 3 ];
					filetime_buffer[ 5 ] = value_data[ 2 ];
					filetime_buffer[ 6 ] = value_data[ 1 ];
					filetime_buffer[ 7 ] = value_data[ 0 ];

					if( libfdatetime_filetime_copy_from_byte_stream(
					     filetime,
					     filetime_buffer,
					     8,
					     LIBFDATETIME_ENDIAN_LITTLE,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy byte stream to filetime.",
						 function );

						libfdatetime_filetime_free(
						 &delta_filetime,
						 NULL );
						libfdatetime_filetime_free(
						 &filetime,
						 NULL );

						return( -1 );
					}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libfdatetime_filetime_copy_to_utf16_string(
						  filetime,
						  (uint16_t *) filetime_string,
						  32,
					          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
						  error );
#else
					result = libfdatetime_filetime_copy_to_utf8_string(
						  filetime,
						  (uint8_t *) filetime_string,
						  32,
					          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
						  error );
#endif
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy filetime to string.",
						 function );

						libfdatetime_filetime_free(
						 &delta_filetime,
						 NULL );
						libfdatetime_filetime_free(
						 &filetime,
						 NULL );

						return( -1 );
					}
					libcnotify_printf(
					 "\tFiletime\t: %" PRIs_SYSTEM " UTC\n",
					 filetime_string );

					if( libfguid_identifier_initialize(
					     &guid,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
						 "%s: unable to create GUID.",
						 function );

						libfdatetime_filetime_free(
						 &delta_filetime,
						 NULL );
						libfdatetime_filetime_free(
						 &filetime,
						 NULL );

						return( -1 );
					}
					/* Currently it is assumed that the GUID is in big-endian
					 */
					if( libfguid_identifier_copy_from_byte_stream(
					     guid,
					     &( value_data[ 6 ] ),
					     16,
					     LIBFGUID_ENDIAN_BIG,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy byte stream to GUID.",
						 function );

						libfguid_identifier_free(
						 &guid,
						 NULL );
						libfdatetime_filetime_free(
						 &delta_filetime,
						 NULL );
						libfdatetime_filetime_free(
						 &filetime,
						 NULL );

						return( -1 );
					}
/* TODO
					value_data      += 16;
					value_data_size -= 16;
*/

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libfguid_identifier_copy_to_utf16_string(
						  guid,
						  (uint16_t *) guid_string,
						  48,
						  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
						  error );
#else
					result = libfguid_identifier_copy_to_utf8_string(
						  guid,
						  (uint8_t *) guid_string,
						  48,
						  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
						  error );
#endif
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy GUID to string.",
						 function );

						libfguid_identifier_free(
						 &guid,
						 NULL );
						libfdatetime_filetime_free(
						 &delta_filetime,
						 NULL );
						libfdatetime_filetime_free(
						 &filetime,
						 NULL );

						return( -1 );
					}
					if( libfguid_identifier_free(
					     &guid,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free GUID.",
						 function );

						libfdatetime_filetime_free(
						 &delta_filetime,
						 NULL );
						libfdatetime_filetime_free(
						 &filetime,
						 NULL );

						return( -1 );
					}
					libcnotify_printf(
					 "\tGUID\t\t: %" PRIs_SYSTEM "\n",
					 guid_string );

					list_iterator = 1;

					for( value_data_iterator = 22;
					     value_data_iterator < value_data_size;
					     value_data_iterator += 5 )
					{
						libcnotify_printf(
						 "Child block: %d\n",
						 list_iterator );

						value_data_pointer = &( value_data[ value_data_iterator ] );

						libcnotify_print_data(
						 value_data_pointer,
						 5,
						 0 );

						/* Use a 64-bit value to be able to shift the bits in the right position
						 * current system time delta is in big-endian
						 */
						byte_stream_copy_to_uint32_big_endian(
						 value_data_pointer,
						 value_64bit );

						/* Make sure only 31-bits are set and the rest is cleared
						 */
						value_64bit &= 0x07fffffffUL;

						/* Check if the highest bit is set
						 */
						if( ( value_data[ value_data_iterator ] & 0x80 ) == 0 )
						{
							/* Discard the highest 15-bits and the lowest 18-bits
							 */
							value_64bit <<= 18;
						}
						else
						{
							/* Discard the highest 10-bits and the lowest 23-bits
							 */
							value_64bit <<= 23;
						}
						if( libfdatetime_filetime_copy_from_64bit(
						     delta_filetime,
						     value_64bit,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
							 "%s: unable to copy delta filetime from 64-bit value.",
							 function );

							libfdatetime_filetime_free(
							 &delta_filetime,
							 NULL );
							libfdatetime_filetime_free(
							 &filetime,
							 NULL );

							return( -1 );
						}
						/* The next child block uses the previous filetime as its base
						 * not the filetime in the header block as MSDN states
						 * so the filetime is updated
						 */
						if( libfdatetime_filetime_add(
						     filetime,
						     delta_filetime,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
							 "%s: unable to create filetime.",
							 function );

							libfdatetime_filetime_free(
							 &delta_filetime,
							 NULL );
							libfdatetime_filetime_free(
							 &filetime,
							 NULL );

							return( -1 );
						}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
						result = libfdatetime_filetime_copy_to_utf16_string(
							  filetime,
							  (uint16_t *) filetime_string,
							  32,
						          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
							  error );
#else
						result = libfdatetime_filetime_copy_to_utf8_string(
							  filetime,
							  (uint8_t *) filetime_string,
							  32,
						          LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
							  error );
#endif
						if( result != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
							 "%s: unable to copy filetime to string.",
							 function );

							libfdatetime_filetime_free(
							 &delta_filetime,
							 NULL );
							libfdatetime_filetime_free(
							 &filetime,
							 NULL );

							return( -1 );
						}
						libcnotify_printf(
						 "\tFiletime\t: %" PRIs_SYSTEM " UTC\n",
						 filetime_string );

						libcnotify_printf(
						 "\tRandom number\t: %" PRIu8 "\n",
						 ( value_data[ value_data_iterator + 4 ] & 0xf0 ) >> 4 );
						libcnotify_printf(
						 "\tSequence count\t: %" PRIu8 "\n",
						 value_data[ value_data_iterator + 4 ] & 0x0f );

						list_iterator++;
					}
					libcnotify_printf(
					 "\n" );

					if( value_data_iterator < value_data_size )
					{
						libcnotify_print_data(
						 &( value_data[ value_data_iterator ] ),
						 value_data_size - value_data_iterator,
						 0 );
					}
					if( libfdatetime_filetime_free(
					     &delta_filetime,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free delta filetime.",
						 function );

						libfdatetime_filetime_free(
						 &filetime,
						 NULL );

						return( -1 );
					}
					if( libfdatetime_filetime_free(
					     &filetime,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free filetime.",
						 function );

						return( -1 );
					}
				}
				else
				{
					libcnotify_print_data(
					 value_data,
					 value_data_size,
					 0 );
				}
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x0e27:
		case 0x3d21:
			if( value_data_size >= 100 )
			{
				if( libfwnt_security_identifier_initialize(
				     &sid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create SID.",
					 function );

					return( -1 );
				}
				libcnotify_printf(
				 "Unknown1:\n" );
				libcnotify_print_data(
				 value_data,
				 8,
				 0 );

				libcnotify_printf(
				 "Security descriptor:\n" );
				libcnotify_printf(
				 "\tRevision number:\t\t%" PRIu8 "\n",
				 value_data[ 8 ] );
				libcnotify_printf(
				 "\tPadding:\t\t\t0x%02" PRIx8 "\n",
				 value_data[ 9 ] );

				value_data_pointer = &( value_data[ 10 ] );

				byte_stream_copy_to_uint16_little_endian(
				 value_data_pointer,
				 value_16bit );

				libcnotify_printf(
				 "\tControl flags:\t\t\t0x%04" PRIx16 "\n",
				 value_16bit );

				value_data_pointer = &( value_data[ 12 ] );

				byte_stream_copy_to_uint32_little_endian(
				 value_data_pointer,
				 value_32bit );

				libcnotify_printf(
				 "\tOwner SID reference:\t\t%" PRIu32 "\n",
				 value_32bit );

				value_data_iterator = value_32bit + 8;

				if( ( value_data_iterator > 0 )
				 && ( value_data_iterator < value_data_size ) )
				{
					if( libfwnt_security_identifier_copy_from_byte_stream(
					     sid,
					     &( value_data[ value_data_iterator ] ),
					     value_data_size - value_data_iterator,
					     LIBFWNT_ENDIAN_LITTLE,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy byte stream to SID.",
						 function );

						libfwnt_security_identifier_free(
						 &sid,
						 NULL );

						return( -1 );
					}
					result = libfwnt_security_identifier_get_string_size(
						  sid,
						  &sid_string_size,
						  0,
						  error );

					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve SID string size.",
						 function );

						libfwnt_security_identifier_free(
						 &sid,
						 NULL );

						return( -1 );
					}
					/* It is assumed that the SID string cannot be larger than 127 characters
					 * otherwise using dynamic allocation is more appropriate
					 */
					if( sid_string_size > 128 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: SID string size value exceeds maximum.",
						 function );

						libfwnt_security_identifier_free(
						 &sid,
						 NULL );

						return( -1 );
					}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libfwnt_security_identifier_copy_to_utf16_string(
						  sid,
						  (uint16_t *) sid_string,
						  128,
						  0,
						  error );
#else
					result = libfwnt_security_identifier_copy_to_utf8_string(
						  sid,
						  (uint8_t *) sid_string,
						  128,
						  0,
						  error );
#endif
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy SID to string.",
						 function );

						libfwnt_security_identifier_free(
						 &sid,
						 NULL );

						return( -1 );
					}
					libcnotify_printf(
					 "\t\tOwner SID:\t\t%" PRIs_SYSTEM "\n",
					 sid_string );
				}
				value_data_pointer = &( value_data[ 16 ] );

				byte_stream_copy_to_uint32_little_endian(
				 value_data_pointer,
				 value_32bit );

				libcnotify_printf(
				 "\tGroup SID reference:\t\t%" PRIu32 "\n",
				 value_32bit );

				value_data_iterator = value_32bit + 8;

				if( ( value_data_iterator > 0 )
				 && ( value_data_iterator < value_data_size ) )
				{
					if( libfwnt_security_identifier_copy_from_byte_stream(
					     sid,
					     &( value_data[ value_data_iterator ] ),
					     value_data_size - value_data_iterator,
					     LIBFWNT_ENDIAN_LITTLE,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy byte stream to SID.",
						 function );

						libfwnt_security_identifier_free(
						 &sid,
						 NULL );

						return( -1 );
					}
					result = libfwnt_security_identifier_get_string_size(
						  sid,
						  &sid_string_size,
						  0,
						  error );

					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve SID string size.",
						 function );

						libfwnt_security_identifier_free(
						 &sid,
						 NULL );

						return( -1 );
					}
					/* It is assumed that the SID string cannot be larger than 127 characters
					 * otherwise using dynamic allocation is more appropriate
					 */
					if( sid_string_size > 128 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: SID string size value exceeds maximum.",
						 function );

						libfwnt_security_identifier_free(
						 &sid,
						 NULL );

						return( -1 );
					}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result = libfwnt_security_identifier_copy_to_utf16_string(
						  sid,
						  (uint16_t *) sid_string,
						  128,
						  0,
						  error );
#else
					result = libfwnt_security_identifier_copy_to_utf8_string(
						  sid,
						  (uint8_t *) sid_string,
						  128,
						  0,
						  error );
#endif
					if( result != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unable to copy SID to string.",
						 function );

						libfwnt_security_identifier_free(
						 &sid,
						 NULL );

						return( -1 );
					}
					libcnotify_printf(
					 "\t\tGroup SID:\t\t%" PRIs_SYSTEM "\n",
					 sid_string );
				}
				value_data_pointer = &( value_data[ 20 ] );

				byte_stream_copy_to_uint32_little_endian(
				 value_data_pointer,
				 value_32bit );

				libcnotify_printf(
				 "\tDACL reference:\t\t\t%" PRIu32 "\n",
				 value_32bit );

				value_data_pointer = &( value_data[ 24 ] );

				byte_stream_copy_to_uint32_little_endian(
				 value_data_pointer,
				 value_32bit );

				libcnotify_printf(
				 "\tSACL reference:\t\t\t%" PRIu32 "\n",
				 value_32bit );

				value_data_iterator = value_32bit + 8;

				if( ( value_data_iterator > 0 )
				 && ( value_data_iterator < value_data_size ) )
				{
					libcnotify_printf(
					 "\t\tAccess control list (ACL):\n" );
					libcnotify_printf(
					 "\t\tRevision number:\t%" PRIu8 "\n",
					 value_data[ value_data_iterator ] );
					libcnotify_printf(
					 "\t\tPadding1:\t\t%" PRIu8 "\n",
					 value_data[ value_data_iterator + 1 ] );

					value_data_pointer = &( value_data[ value_data_iterator + 2 ] );

					byte_stream_copy_to_uint16_little_endian(
					 value_data_pointer,
					 value_16bit );

					libcnotify_printf(
					 "\t\tSize:\t\t\t%" PRIu16 "\n",
					 value_16bit );

					value_data_pointer = &( value_data[ value_data_iterator + 4 ] );

					byte_stream_copy_to_uint16_little_endian(
					 value_data_pointer,
					 value_16bit );

					libcnotify_printf(
					 "\t\tCount:\t\t\t%" PRIu16 "\n",
					 value_16bit );

					number_of_values = (uint32_t) value_16bit;

					value_data_pointer = &( value_data[ value_data_iterator + 6 ] );

					byte_stream_copy_to_uint16_little_endian(
					 value_data_pointer,
					 value_16bit );

					libcnotify_printf(
					 "\t\tPadding2:\t\t0x%04" PRIx16 "\n",
					 value_16bit );

					value_data_iterator += 8;

					for( value_iterator = 0;
					     value_iterator < number_of_values;
					     value_iterator++ )
					{
						libcnotify_printf(
						 "\t\tAccess control entry (ACE):\n" );
						libcnotify_printf(
						 "\t\tType:\t\t\t%" PRIu8 "\n",
						 value_data[ value_data_iterator ] );
						libcnotify_printf(
						 "\t\tFlags:\t\t\t%" PRIu8 "\n",
						 value_data[ value_data_iterator + 1 ] );

						value_data_pointer = &( value_data[ value_data_iterator + 2 ] );

						byte_stream_copy_to_uint16_little_endian(
						 value_data_pointer,
						 value_16bit );

						libcnotify_printf(
						 "\t\tSize:\t\t\t%" PRIu16 "\n",
						 value_16bit );

						libcnotify_printf(
						 "\t\tACE data:\n" );

						if( ( value_data[ value_data_iterator ] <= 0x03 )
						 || ( value_data[ value_data_iterator ] == 0x09 )
						 || ( value_data[ value_data_iterator ] == 0x0a )
						 || ( value_data[ value_data_iterator ] == 0x0d )
						 || ( value_data[ value_data_iterator ] == 0x0e )
						 || ( value_data[ value_data_iterator ] == 0x11 ) )
						{
							value_data_pointer = &( value_data[ value_data_iterator + 4 ] );

							byte_stream_copy_to_uint16_little_endian(
							 value_data_pointer,
							 value_32bit );

							libcnotify_printf(
							 "\t\tAccess rights flags:\t0x%08" PRIx32 "\n",
							 value_32bit );

							if( libfwnt_security_identifier_copy_from_byte_stream(
							     sid,
							     &( value_data[ value_data_iterator + 8 ] ),
							     value_data_size - value_data_iterator,
							     LIBFWNT_ENDIAN_LITTLE,
							     error ) != 1 )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_RUNTIME,
								 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
								 "%s: unable to copy byte stream to SID.",
								 function );

								libfwnt_security_identifier_free(
								 &sid,
								 NULL );

								return( -1 );
							}
							result = libfwnt_security_identifier_get_string_size(
								  sid,
								  &sid_string_size,
								  0,
								  error );

							if( result != 1 )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_RUNTIME,
								 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
								 "%s: unable to retrieve SID string size.",
								 function );

								libfwnt_security_identifier_free(
								 &sid,
								 NULL );

								return( -1 );
							}
							/* It is assumed that the SID string cannot be larger than 127 characters
							 * otherwise using dynamic allocation is more appropriate
							 */
							if( sid_string_size > 128 )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_RUNTIME,
								 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
								 "%s: SID string size value exceeds maximum.",
								 function );

								libfwnt_security_identifier_free(
								 &sid,
								 NULL );

								return( -1 );
							}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
							result = libfwnt_security_identifier_copy_to_utf16_string(
								  sid,
								  (uint16_t *) sid_string,
								  128,
								  0,
								  error );
#else
							result = libfwnt_security_identifier_copy_to_utf8_string(
								  sid,
								  (uint8_t *) sid_string,
								  128,
								  0,
								  error );
#endif
							if( result != 1 )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_RUNTIME,
								 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
								 "%s: unable to copy SID to string.",
								 function );

								libfwnt_security_identifier_free(
								 &sid,
								 NULL );

								return( -1 );
							}
							libcnotify_printf(
							 "\t\tSID:\t\t\t%" PRIs_SYSTEM "\n",
							 sid_string );

							libcnotify_printf(
							 "\n" );
						}
						else
						{
							libcnotify_print_data(
							 &( value_data[ value_32bit + 4 ] ),
							 value_16bit - 4,
							 0 );
						}
					}
				}
				libcnotify_printf(
				 "\n" );

				if( libfwnt_security_identifier_free(
				     &sid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free SID.",
					 function );

					return( -1 );
				}
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x0e58:
		case 0x0e59:
			if( libfwnt_security_identifier_initialize(
			     &sid,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create SID.",
				 function );

				return( -1 );
			}
			if( libfwnt_security_identifier_copy_from_byte_stream(
			     sid,
			     value_data,
			     value_data_size,
			     LIBFWNT_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy byte stream to SID.",
				 function );

				libfwnt_security_identifier_free(
				 &sid,
				 NULL );

				return( -1 );
			}
			result = libfwnt_security_identifier_get_string_size(
				  sid,
				  &sid_string_size,
				  0,
				  error );

			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve SID string size.",
				 function );

				libfwnt_security_identifier_free(
				 &sid,
				 NULL );

				return( -1 );
			}
			/* It is assumed that the SID string cannot be larger than 127 characters
			 * otherwise using dynamic allocation is more appropriate
			 */
			if( sid_string_size > 128 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: SID string size value exceeds maximum.",
				 function );

				libfwnt_security_identifier_free(
				 &sid,
				 NULL );

				return( -1 );
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libfwnt_security_identifier_copy_to_utf16_string(
				  sid,
				  (uint16_t *) sid_string,
				  128,
				  0,
				  error );
#else
			result = libfwnt_security_identifier_copy_to_utf8_string(
				  sid,
				  (uint8_t *) sid_string,
				  128,
				  0,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy SID to string.",
				 function );

				libfwnt_security_identifier_free(
				 &sid,
				 NULL );

				return( -1 );
			}
			libcnotify_printf(
			 "SID:\t%" PRIs_SYSTEM "\n",
			 sid_string );
			libcnotify_printf(
			 "\n" );

			if( libfwnt_security_identifier_free(
			     &sid,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free SID.",
				 function );

				return( -1 );
			}
			break;

		case 0x1009:
			if( ( value_data_size >= 16 )
			 && ( value_data[  8 ] == (uint8_t) 'L' )
			 && ( value_data[  9 ] == (uint8_t) 'Z' )
			 && ( value_data[ 10 ] == (uint8_t) 'F' )
			 && ( value_data[ 11 ] == (uint8_t) 'u' ) )
			{
				value_data_pointer = &( value_data[ 4 ] );

				byte_stream_copy_to_uint32_little_endian(
				 value_data_pointer,
				 rtf_value_string_size );

				rtf_value_string_size += 2;

				rtf_value_string = (uint8_t *) memory_allocate(
						                sizeof( uint8_t ) * rtf_value_string_size );

				if( rtf_value_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable create rtf value string.",
					 function );

					return( -1 );
				}
				if( libfmapi_lzfu_decompress(
				     value_data,
				     value_data_size,
				     (uint8_t *) rtf_value_string,
				     &rtf_value_string_size,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_COMPRESSION,
					 LIBCERROR_COMPRESSION_ERROR_DECOMPRESS_FAILED,
					 "%s: unable to decompress LZFu compressed RTF data.",
					 function );

					memory_free(
					 rtf_value_string );

					return( -1 );
				}
				libcnotify_printf(
				 "uncompressed RTF data\t: " );

				for( value_data_iterator = 0;
				     value_data_iterator < rtf_value_string_size;
				     value_data_iterator++ )
				{
					libcnotify_printf(
					 "%c",
					 rtf_value_string[ value_data_iterator ] );
				}
				libcnotify_printf(
				 "\n\n" );

				memory_free(
				 rtf_value_string );

				rtf_value_string = NULL;
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x1013:
			if( value_data == NULL )
			{
				libcnotify_printf(
				 "ASCII string\t: <NULL>\n\n" );
			}
			else
			{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libuna_utf16_string_size_from_byte_stream(
					  value_data,
					  value_data_size,
					  LIBUNA_CODEPAGE_ASCII,
					  &value_string_size,
					  error );
#else
				result = libuna_utf8_string_size_from_byte_stream(
					  value_data,
					  value_data_size,
					  LIBUNA_CODEPAGE_ASCII,
					  &value_string_size,
					  error );
#endif
				/* TODO error tollerance required ? */
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to determine value string size.",
					 function );

					return( -1 );
				}
				value_string = system_string_allocate(
				                value_string_size );

				if( value_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create value string.",
					 function );

					return( -1 );
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libuna_utf16_string_copy_from_byte_stream(
				          (libuna_utf16_character_t *) value_string,
				          value_string_size,
				          value_data,
				          value_data_size,
				          LIBUNA_CODEPAGE_ASCII,
				          error );
#else
				result = libuna_utf8_string_copy_from_byte_stream(
				          (libuna_utf8_character_t *) value_string,
				          value_string_size,
				          value_data,
				          value_data_size,
				          LIBUNA_CODEPAGE_ASCII,
				          error );
#endif

				/* TODO error tollerance required ? */
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set value string.",
					 function );

					memory_free(
					 value_string );

					return( -1 );
				}
				libcnotify_printf(
				 "ASCII string\t: %" PRIs_SYSTEM "\n\n",
				 value_string );

				memory_free(
				 value_string );
			}
			break;

		case 0x300c:
		case 0x3615:
			if( value_data == NULL )
			{
				libcnotify_printf(
				 "MAPI UID\t: <NULL>\n\n" );
			}
			else  if( value_data_size == 16 )
			{
				if( libfguid_identifier_initialize(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create GUID.",
					 function );

					return( -1 );
				}
				if( libfguid_identifier_copy_from_byte_stream(
				     guid,
				     value_data,
				     value_data_size,
				     LIBFGUID_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to GUID.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				value_data      += 16;
				value_data_size -= 16;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfguid_identifier_copy_to_utf16_string(
					  guid,
					  (uint16_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#else
				result = libfguid_identifier_copy_to_utf8_string(
					  guid,
					  (uint8_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy GUID to string.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				if( libfguid_identifier_free(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free GUID.",
					 function );

					return( -1 );
				}
				libcnotify_printf(
				 "MAPI UID\t: %" PRIs_SYSTEM "\n\n",
				 guid_string );
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x36d9:
			if( value_data_size >= 4 )
			{
				if( libfmapi_debug_print_persist_data_block(
				     value_data,
				     value_data_size,
				     ascii_codepage,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
					 "%s: unable to print persist data block.",
					 function );

					return( -1 );
				}
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x3702:
		case 0x370a:
			if( value_data_size >= 9 )
			{
				value_data_iterator = 9;

				/* Check if the object identifier has the MAPI prefix
				 */
				if( ( value_data[ 0 ] == 0x2a )
				 && ( value_data[ 1 ] == 0x86 )
				 && ( value_data[ 2 ] == 0x48 )
				 && ( value_data[ 3 ] == 0x86 )
				 && ( value_data[ 4 ] == 0xf7 )
				 && ( value_data[ 5 ] == 0x14 )
				 && ( value_data[ 6 ] == 0x03 ) )
				{
					libcnotify_printf(
					 "MAPI X.400 object identifier\t:" );

					if( value_data[ 7 ] == 0x0a )
					{
						libcnotify_printf(
						 "tag (0x%02" PRIx8 ")",
						 value_data[ 7 ] );

						if( value_data[ 8 ] == 0x01 )
						{
							libcnotify_printf(
							 " TNEF (0x%02" PRIx8")",
							 value_data[ 8 ] );
						}
						else if( value_data[ 8 ] == 0x03 )
						{
							if( value_data_size >= 11 )
							{
								value_data_iterator = 11;

								if( ( value_data[ 9 ] == 0x01 )
								 && ( value_data[ 10 ] == 0x01 ) )
								{
									libcnotify_printf(
									 " OLE1 storage (0x%02" PRIx8 " 0x%02" PRIx8 " 0x%02" PRIx8 ")",
									 value_data[ 8 ],
									 value_data[ 9 ],
									 value_data[ 10 ] );
								}
								else if( ( value_data[ 9 ] == 0x02 )
								      && ( value_data[ 10 ] == 0x01 ) )
								{
									libcnotify_printf(
									 " OLE2 storage (0x%02" PRIx8 " 0x%02" PRIx8 " 0x%02" PRIx8 ")",
									 value_data[ 8 ],
									 value_data[ 9 ],
									 value_data[ 10 ] );
								}
								else
								{
									libcnotify_printf(
									 " OLE unknown (0x%02" PRIx8 " 0x%02" PRIx8 " 0x%02" PRIx8 ")",
									 value_data[ 8 ],
									 value_data[ 9 ],
									 value_data[ 10 ] );
								}
							}
							else if( value_data_size >= 10 )
							{
								value_data_iterator = 10;

								if( value_data[ 9 ] == 0x01 )
								{
									libcnotify_printf(
									 " OLE1 (0x%02" PRIx8 " 0x%02" PRIx8 ")",
									 value_data[ 8 ],
									 value_data[ 9 ] );
								}
								else if( value_data[ 9 ] == 0x02 )
								{
									libcnotify_printf(
									 " OLE2 (0x%02" PRIx8 " 0x%02" PRIx8 ")",
									 value_data[ 8 ],
									 value_data[ 9 ] );
								}
								else
								{
									libcnotify_printf(
									 " OLE unknown (0x%02" PRIx8 " 0x%02" PRIx8 ")",
									 value_data[ 8 ],
									 value_data[ 9 ] );
								}
							}
							else
							{
								libcnotify_printf(
								 " OLE (0x%02" PRIx8 ")",
								 value_data[ 8 ] );
							}
						}
						else if( value_data[ 8 ] == 0x04 )
						{
							libcnotify_printf(
							 " MIME (0x%02" PRIx8 ")",
							 value_data[ 8 ] );
						}
						else
						{
							libcnotify_printf(
							 " unknown (0x%02" PRIx8 ")",
							 value_data[ 8 ] );
						}
					}
					else if( value_data[ 7 ] == 0x0b )
					{
						libcnotify_printf(
						 " encoding (0x%02" PRIx8 ")",
						 value_data[ 7 ] );

						if( value_data[ 8 ] == 0x01 )
						{
							libcnotify_printf(
							 " MacBinary (0x%02" PRIx8 ")",
							 value_data[ 8 ] );
						}
						else
						{
							libcnotify_printf(
							 " unknown (0x%02" PRIx8 ")",
							 value_data[ 8 ] );
						}
					}
					else
					{
						libcnotify_printf(
						 " unknown (0x%02" PRIx8 ")",
						 value_data[ 7 ] );
					}
					libcnotify_printf(
					 "\n" );

					if( value_data_iterator < value_data_size )
					{
						libcnotify_print_data(
						 &( value_data[ value_data_iterator ] ),
						 value_data_size - value_data_iterator,
						 0 );
					}
					else
					{
						libcnotify_printf(
						 "\n" );
					}
				}
				else
				{
					libcnotify_print_data(
					 value_data,
					 value_data_size,
					 0 );
				}
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x65e2:
			if( value_data_size > 16 )
			{
				if( libfguid_identifier_initialize(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create GUID.",
					 function );

					return( -1 );
				}
				if( libfguid_identifier_copy_from_byte_stream(
				     guid,
				     value_data,
				     16,
				     LIBFGUID_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to GUID.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				value_data      += 16;
				value_data_size -= 16;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfguid_identifier_copy_to_utf16_string(
					  guid,
					  (uint16_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#else
				result = libfguid_identifier_copy_to_utf8_string(
					  guid,
					  (uint8_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy GUID to string.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				if( libfguid_identifier_free(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free GUID.",
					 function );

					return( -1 );
				}
				libcnotify_printf(
				 "GUID\t\t: %" PRIs_SYSTEM "\n",
				 guid_string );

				libcnotify_printf(
				 "Unknown1:\n" );
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x65e3:
			if( value_data_size > 1 )
			{
/* TODO */
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );

				if( libfguid_identifier_initialize(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create GUID.",
					 function );

					return( -1 );
				}
				while( value_data_size > 0 )
				{
					data_size = *value_data;

					value_data      += 1;
					value_data_size -= 1;

					if( data_size < value_data_size )
					{
						libcnotify_printf(
						 "Size\t\t: 0x%02x\n",
						 data_size );
					}
					else
					{
						libcnotify_printf(
						 "Size\t\t: 0x%02x <OUT OF BOUNDS>\n",
						 data_size );

						break;
					}
					if( data_size >= 16 )
					{
						if( libfguid_identifier_copy_from_byte_stream(
						     guid,
						     value_data,
						     value_data_size,
						     LIBFGUID_ENDIAN_LITTLE,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
							 "%s: unable to copy byte stream to GUID.",
							 function );

							libfguid_identifier_free(
							 &guid,
							 NULL );

							return( -1 );
						}
						value_data      += 16;
						value_data_size -= 16;
						data_size       -= 16;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
						result = libfguid_identifier_copy_to_utf16_string(
							  guid,
							  (uint16_t *) guid_string,
							  48,
							  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
							  error );
#else
						result = libfguid_identifier_copy_to_utf8_string(
							  guid,
							  (uint8_t *) guid_string,
							  48,
							  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
							  error );
#endif
						if( result != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
							 "%s: unable to copy GUID to string.",
							 function );

							libfguid_identifier_free(
							 &guid,
							 NULL );

							return( -1 );
						}
						libcnotify_printf(
						 "GUID\t\t: %" PRIs_SYSTEM "\n",
						 guid_string );
					}
					libcnotify_printf(
					 "Unknown:\n" );
					libcnotify_print_data(
					 value_data,
					 data_size,
					 0 );

					value_data      += data_size;
					value_data_size -= data_size;
				}
				if( libfguid_identifier_free(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free GUID.",
					 function );

					return( -1 );
				}
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x683c:
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_byte_stream(
			          value_data,
			          value_data_size,
			          ascii_codepage,
			          &value_string_size,
			          error );
#else
			result = libuna_utf8_string_size_from_byte_stream(
			          value_data,
			          value_data_size,
			          ascii_codepage,
			          &value_string_size,
			          error );
#endif

			/* TODO error tollerance required ? */
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine value string size.",
				 function );

				return( -1 );
			}
			value_string = system_string_allocate(
			                value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create value string.",
				 function );

				return( -1 );
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_byte_stream(
			          (libuna_utf16_character_t *) value_string,
			          value_string_size,
			          value_data,
			          value_data_size,
			          ascii_codepage,
			          error );
#else
			result = libuna_utf8_string_copy_from_byte_stream(
			          (libuna_utf8_character_t *) value_string,
			          value_string_size,
			          value_data,
			          value_data_size,
			          ascii_codepage,
			          error );
#endif

			/* TODO error tollerance required ? */
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set value string.",
				 function );

				memory_free(
				 value_string );

				return( -1 );
			}
			libcnotify_printf(
			 "ASCII string\t: %" PRIs_SYSTEM "\n",
			 value_string );

			memory_free(
			 value_string );

			libcnotify_printf(
			 "\n" );

			break;

		case 0x7c04:
			if( value_data_size == 20 )
			{
				if( libfguid_identifier_initialize(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create GUID.",
					 function );

					return( -1 );
				}
				if( libfguid_identifier_copy_from_byte_stream(
				     guid,
				     value_data,
				     value_data_size,
				     LIBFGUID_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to GUID.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				value_data      += 16;
				value_data_size -= 16;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfguid_identifier_copy_to_utf16_string(
					  guid,
					  (uint16_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#else
				result = libfguid_identifier_copy_to_utf8_string(
					  guid,
					  (uint8_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy GUID to string.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				if( libfguid_identifier_free(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free GUID.",
					 function );

					return( -1 );
				}
				libcnotify_printf(
				 "GUID\t: %" PRIs_SYSTEM "\n",
				 guid_string );

				libcnotify_printf(
				 "Unknown1:\n" );
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );

				libcnotify_printf(
				 "\n" );
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		case 0x859c:
			if( value_data_size >= 46 )
			{
				if( libfguid_identifier_initialize(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create GUID.",
					 function );

					return( -1 );
				}

				libcnotify_printf(
				 "Unknown1:\n" );
				libcnotify_print_data(
				 value_data,
				 4,
				 0 );

				value_data      += 4;
				value_data_size -= 4;

				if( libfguid_identifier_copy_from_byte_stream(
				     guid,
				     value_data,
				     value_data_size,
				     LIBFGUID_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to GUID.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				value_data      += 16;
				value_data_size -= 16;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfguid_identifier_copy_to_utf16_string(
					  guid,
					  (uint16_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#else
				result = libfguid_identifier_copy_to_utf8_string(
					  guid,
					  (uint8_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy GUID to string.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				libcnotify_printf(
				 "GUID\t\t: %" PRIs_SYSTEM "\n",
				 guid_string );

				libcnotify_printf(
				 "Unknown2:\n" );
				libcnotify_print_data(
				 value_data,
				 2,
				 0 );

				value_data      += 2;
				value_data_size -= 2;

				if( libfguid_identifier_copy_from_byte_stream(
				     guid,
				     value_data,
				     value_data_size,
				     LIBFGUID_ENDIAN_LITTLE,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy byte stream to GUID.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				value_data      += 16;
				value_data_size -= 16;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfguid_identifier_copy_to_utf16_string(
					  guid,
					  (uint16_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#else
				result = libfguid_identifier_copy_to_utf8_string(
					  guid,
					  (uint8_t *) guid_string,
					  48,
					  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to copy GUID to string.",
					 function );

					libfguid_identifier_free(
					 &guid,
					 NULL );

					return( -1 );
				}
				libcnotify_printf(
				 "GUID\t\t: %" PRIs_SYSTEM "\n",
				 guid_string );

				libcnotify_printf(
				 "Unknown3:\n" );
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );

				libcnotify_printf(
				 "\n" );

				if( libfguid_identifier_free(
				     &guid,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free GUID.",
					 function );

					return( -1 );
				}
			}
			else
			{
				libcnotify_print_data(
				 value_data,
				 value_data_size,
				 0 );
			}
			break;

		default:
			libcnotify_print_data(
			 value_data,
			 value_data_size,
			 0 );

			break;
	}
	return( 1 );
}

/* Prints the MAPI array multi value
 * Returns 1 if successful or -1 on error
 */
int libfmapi_debug_print_array_multi_value(
     uint32_t entry_type,
     uint32_t value_type,
     uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	static char *function     = "libfmapi_debug_print_array_multi_value";
	size_t value_size         = 0;
	uint32_t number_of_values = 0;
	uint32_t value_iterator   = 0;
	uint32_t value_offset     = 0;

	if( ( value_type != 0x1002 )
	 && ( value_type != 0x1003 )
	 && ( value_type != 0x1014 )
	 && ( value_type != 0x1040 )
	 && ( value_type != 0x1048 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value type.",
		 function );

		return( -1 );
	}
	if( value_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: value data size exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value_data == NULL )
	{
		switch( value_type )
		{
			case 0x1002:
				libcnotify_printf(
				 "Integer 16-bit signed multi value\t: <NULL>\n\n" );
				break;

			case 0x1003:
				libcnotify_printf(
				 "Integer 32-bit signed multi value\t: <NULL>\n\n" );
				break;

			case 0x1014:
				libcnotify_printf(
				 "Integer 64-bit signed multi value\t: <NULL>\n\n" );
				break;

			case 0x1040:
				libcnotify_printf(
				 "Filetime multi value\t: <NULL>\n\n" );
				break;

			case 0x1048:
				libcnotify_printf(
				 "GUID multi value\t: <NULL>\n\n" );
				break;
		}
	}
	else
	{
		switch( value_type )
		{
			case 0x1002:
				value_size = 2;
				break;

			case 0x1003:
				value_size = 4;
				break;

			case 0x1014:
			case 0x1040:
				value_size = 8;
				break;

			case 0x1048:
				value_size = 16;
				break;
		}
		if( value_size != 0 )
		{
			if( ( value_data_size % value_size ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: value data size: %" PRIzd " not a multitude of value size: %" PRIzd ".",
				 function,
				 value_data_size,
				 value_size );

				 return( -1 );
			}
			number_of_values = value_data_size / value_size;
		}
		libcnotify_printf(
		 "Number of entries\t\t: %" PRIu32 "\n",
		 number_of_values );

		for( value_iterator = 0;
		     value_iterator < number_of_values;
		     value_iterator++ )
		{
			libcnotify_printf(
			 "Entry: %02" PRIu32 " identifier offset\t: %" PRIu32 "\n",
			 value_iterator,
			 value_offset );

			if( libfmapi_debug_print_value(
			     entry_type,
			     value_type & 0x0fff,
			     &( value_data[ value_offset ] ),
			     value_size,
			     ascii_codepage,
			     error ) != 1 )
			{
				if( ( error != NULL )
				 && ( *error != NULL ) )
				{
					libcnotify_print_error_backtrace(
					 *error );
				}
				libcerror_error_free(
				 error );

				libcnotify_print_data(
				 &( value_data[ value_offset ] ),
			 	 value_size,
				 0 );
			}
			value_offset += value_size;
		}
	}
	return( 1 );
}

/* Prints the MAPI element multi value
 * The type of multi value is used by ASCII and Unicode string and binary data values
 * Returns 1 if successful or -1 on error
 */
int libfmapi_debug_print_element_multi_value(
     uint32_t entry_type,
     uint32_t value_type,
     uint8_t *value_data,
     size_t value_data_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	uint8_t *value_data_pointer = NULL;
	static char *function       = "libfmapi_debug_print_element_multi_value";
	uint32_t number_of_values   = 0;
	uint32_t value_32bit        = 0;
	uint32_t last_value_32bit   = 0;
	uint32_t value_iterator     = 0;
	int unsupported_data        = 0;

	if( ( value_type != 0x101e )
	 && ( value_type != 0x101f )
	 && ( value_type != 0x1102 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value type.",
		 function );

		return( -1 );
	}
	if( value_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: value data size exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value_data == NULL )
	{
		switch( value_type )
		{
			case 0x101e:
				libcnotify_printf(
				 "ASCII string multi value\t: <NULL>\n\n" );
				break;

			case 0x101f:
				libcnotify_printf(
				 "Unicode string multi value\t: <NULL>\n\n" );
				break;

			case 0x1102:
				libcnotify_printf(
				 "Binary data multi value\t: <NULL>\n\n" );
				break;

		}
	}
	else
	{
		value_data_pointer = value_data;

		byte_stream_copy_to_uint32_little_endian(
		 value_data_pointer,
		 number_of_values );

		value_data_pointer += 4;

		/* Read the first identifier offset
		 */
		byte_stream_copy_to_uint32_little_endian(
		 value_data_pointer,
		 last_value_32bit );

		value_data_pointer += 4;

		/* Check if number of values makes sense
		 */
		if( number_of_values >= value_data_size )
		{
			unsupported_data = 1;
		}
		/* Check if first idendifier offset makes sense
		 */
		else if( last_value_32bit >= value_data_size )
		{
			unsupported_data = 1;
		}
		else
		{
			libcnotify_printf(
			 "Number of values\t\t: %" PRIu32 "\n",
			 number_of_values );

			for( value_iterator = 1;
			     value_iterator < number_of_values;
			     value_iterator++ )
			{
				/* Read the next identifier offset
				 */
				byte_stream_copy_to_uint32_little_endian(
				 value_data_pointer,
				 value_32bit );

				value_data_pointer += 4;

				libcnotify_printf(
				 "Value: %02" PRIu32 " identifier offset\t: %" PRIu32 "\n",
				 value_iterator - 1,
				 last_value_32bit );

				if( last_value_32bit < value_32bit )
				{
					if( libfmapi_debug_print_value(
					     entry_type,
					     value_type & 0x0fff,
					     &( value_data[ last_value_32bit ] ),
					     value_32bit - last_value_32bit,
					     ascii_codepage,
					     error ) != 1 )
					{
						if( ( error != NULL )
						 && ( *error != NULL ) )
						{
							libcnotify_print_error_backtrace(
							 *error );
						}
						libcerror_error_free(
						 error );

						libcnotify_print_data(
						 &( value_data[ last_value_32bit ] ),
						 value_32bit - last_value_32bit,
						 0 );
					}
				}
				else
				{
					libcnotify_printf(
					 "<NULL>\n\n" );
				}
				last_value_32bit = value_32bit;
			}
			libcnotify_printf(
			 "Value: %02" PRIu32 " identifier offset\t: %" PRIu32 "\n",
			 value_iterator - 1,
			 last_value_32bit );

			/* A multi value can contain a single value
			 */
			if( ( last_value_32bit < value_32bit )
			 || ( number_of_values == 1 ) )
			{
				if( libfmapi_debug_print_value(
				     entry_type,
				     value_type & 0x0fff,
				     &( value_data[ last_value_32bit ] ),
				     value_data_size - last_value_32bit,
				     ascii_codepage,
				     error ) != 1 )
				{
					if( ( error != NULL )
					 && ( *error != NULL ) )
					{
						libcnotify_print_error_backtrace(
						 *error );
					}
					libcerror_error_free(
					 error );

					libcnotify_print_data(
					 &( value_data[ last_value_32bit ] ),
					 value_data_size - last_value_32bit,
					 0 );
				}
			}
			else
			{
				libcnotify_printf(
				 "<NULL>\n\n" );
			}
		}
	}
	if( unsupported_data != 0 )
	{
		libcnotify_print_data(
		 value_data,
	 	 value_data_size,
		 0 );
	}
	return( 1 );
}

#endif

