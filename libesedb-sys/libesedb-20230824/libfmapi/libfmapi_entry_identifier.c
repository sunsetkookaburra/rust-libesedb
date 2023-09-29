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

#include <common.h>
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include "libfmapi_definitions.h"
#include "libfmapi_entry_identifier.h"
#include "libfmapi_libcerror.h"
#include "libfmapi_libcnotify.h"
#include "libfmapi_libfguid.h"
#include "libfmapi_service_provider_identifier.h"

/* Creates an entry identifier
 * Make sure the value entry_identifier is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfmapi_entry_identifier_initialize(
     libfmapi_entry_identifier_t **entry_identifier,
     libcerror_error_t **error )
{
	libfmapi_internal_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                           = "libfmapi_entry_identifier_initialize";

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
	                             libfmapi_internal_entry_identifier_t );

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
	     sizeof( libfmapi_internal_entry_identifier_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear entry identifier.",
		 function );

		goto on_error;
	}
	*entry_identifier = (libfmapi_entry_identifier_t *) internal_entry_identifier;

	return( 1 );

on_error:
	if( internal_entry_identifier != NULL )
	{
		memory_free(
		 internal_entry_identifier );
	}
	return( -1 );
}

/* Frees an entry identifier
 * Returns 1 if successful or -1 on error
 */
int libfmapi_entry_identifier_free(
     libfmapi_entry_identifier_t **entry_identifier,
     libcerror_error_t **error )
{
	libfmapi_internal_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                           = "libfmapi_entry_identifier_free";

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
		internal_entry_identifier = (libfmapi_internal_entry_identifier_t *) *entry_identifier;
		*entry_identifier         = NULL;

		memory_free(
		 internal_entry_identifier );
	}
	return( 1 );
}

/* Converts a byte stream into an entry identifier
 * Returns 1 if successful or -1 on error
 */
int libfmapi_entry_identifier_copy_from_byte_stream(
     libfmapi_entry_identifier_t *entry_identifier,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     libcerror_error_t **error )
{
	libfmapi_internal_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                           = "libfmapi_entry_identifier_copy_from_byte_stream";

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid                                     = NULL;
	int result                                                      = 0;
#endif

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
	internal_entry_identifier = (libfmapi_internal_entry_identifier_t *) entry_identifier;

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
	if( ( byte_stream_size < 20 )
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
		 "%s: entry identifier data:\n",
		 function );
		libcnotify_print_data(
		 byte_stream,
		 20,
		 0 );
	}
#endif
	if( memory_copy(
	     internal_entry_identifier->flags,
	     &( byte_stream[ 0 ] ),
	     4 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy flags.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     internal_entry_identifier->service_provider_identifier,
	     &( byte_stream[ 4 ] ),
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy service provider identifier.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create service provider identifier.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: flags\t\t\t\t: 0x%02" PRIx8 ", 0x%02" PRIx8 ", 0x%02" PRIx8 ", 0x%02" PRIx8 "\n",
		 function,
		 internal_entry_identifier->flags[ 0 ],
		 internal_entry_identifier->flags[ 1 ],
		 internal_entry_identifier->flags[ 2 ],
		 internal_entry_identifier->flags[ 3 ] );

		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     internal_entry_identifier->service_provider_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy service provider identifier from byte stream.",
			 function );

			goto on_error;
		}
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

			goto on_error;
		}
		libcnotify_printf(
		 "%s: service provider identifier\t: %" PRIs_SYSTEM " (%s)\n",
		 function,
		 guid_string,
		 libfmapi_service_provider_identifier_get_name(
		  internal_entry_identifier->service_provider_identifier ) );
	
		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free service provider identifier.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
#endif
	return( -1 );
}

/* Retrieves the service provider identifier
 * Returns 1 if successful or -1 on error
 */
int libfmapi_entry_identifier_get_service_provider_identifier(
     libfmapi_entry_identifier_t *entry_identifier,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libfmapi_internal_entry_identifier_t *internal_entry_identifier = NULL;
	static char *function                                           = "libfmapi_entry_identifier_get_service_provider_identifier";

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
	internal_entry_identifier = (libfmapi_internal_entry_identifier_t *) entry_identifier;

	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: GUID data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID data size value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     internal_entry_identifier->service_provider_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy service provider identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

