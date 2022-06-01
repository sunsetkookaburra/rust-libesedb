/*
 * Floating point value (IEEE 754) functions
 *
 * Copyright (C) 2010-2020, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#include "libfvalue_definitions.h"
#include "libfvalue_floating_point.h"
#include "libfvalue_libcerror.h"

/* Creates a floating point
 * Make sure the value floating_point is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_initialize(
     libfvalue_floating_point_t **floating_point,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_initialize";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( *floating_point != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid floating point value already set.",
		 function );

		return( -1 );
	}
	*floating_point = memory_allocate_structure(
	            libfvalue_floating_point_t );

	if( *floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create floating point.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *floating_point,
	     0,
	     sizeof( libfvalue_floating_point_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear floating point.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *floating_point != NULL )
	{
		memory_free(
		 *floating_point );

		*floating_point = NULL;
	}
	return( -1 );
}

/* Frees a floating point
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_free(
     libfvalue_floating_point_t **floating_point,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_free";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( *floating_point != NULL )
	{
		memory_free(
		 *floating_point );

		*floating_point = NULL;
	}
	return( 1 );
}

/* Clones a floating point
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_clone(
     libfvalue_floating_point_t **destination_floating_point,
     libfvalue_floating_point_t *source_floating_point,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_clone";

	if( destination_floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination floating point.",
		 function );

		return( -1 );
	}
	if( *destination_floating_point != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: destination floating point already set.",
		 function );

		return( -1 );
	}
	if( source_floating_point == NULL )
	{
		*destination_floating_point = NULL;

		return( 1 );
	}
	*destination_floating_point = memory_allocate_structure(
	                               libfvalue_floating_point_t );

	if( *destination_floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination floating point.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     *destination_floating_point,
	     source_floating_point,
	     sizeof( libfvalue_floating_point_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy floating point.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *destination_floating_point != NULL )
	{
		memory_free(
		 *destination_floating_point );

		*destination_floating_point = NULL;
	}
	return( -1 );
}

/* Copies the floating point from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_from_byte_stream(
     libfvalue_floating_point_t *floating_point,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int encoding,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_copy_from_byte_stream";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
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
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( encoding != LIBFVALUE_ENDIAN_BIG )
	 && ( encoding != LIBFVALUE_ENDIAN_LITTLE )
	 && ( encoding != LIBFVALUE_ENDIAN_NATIVE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported encoding.",
		 function );

		return( -1 );
	}
	switch( byte_stream_size )
	{
		case 4:
			if( encoding == LIBFVALUE_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint32_big_endian(
				 byte_stream,
				 floating_point->value );
			}
			else if( encoding == LIBFVALUE_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint32_little_endian(
				 byte_stream,
				 floating_point->value );
			}
			else
			{
				floating_point->value = (uint64_t) *( (uint32_t *) byte_stream );
			}
			break;

		case 8:
			if( encoding == LIBFVALUE_ENDIAN_BIG )
			{
				byte_stream_copy_to_uint64_big_endian(
				 byte_stream,
				 floating_point->value );
			}
			else if( encoding == LIBFVALUE_ENDIAN_LITTLE )
			{
				byte_stream_copy_to_uint64_little_endian(
				 byte_stream,
				 floating_point->value );
			}
			else
			{
				floating_point->value = (uint64_t) *( (uint64_t *) byte_stream );
			}
			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported byte stream size: %" PRIzd ".",
			 function,
			 byte_stream_size );

			return( -1 );
	}
	floating_point->value_size = byte_stream_size * 8;

	return( 1 );
}

/* Copies the floating point from an integer value
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_from_integer(
     libfvalue_floating_point_t *floating_point,
     uint64_t integer_value,
     size_t integer_value_size,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_float64;

	static char *function = "libfvalue_floating_point_copy_from_integer";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( ( integer_value_size != 32 )
	 && ( integer_value_size != 64 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported integer value size.",
		 function );

		return( -1 );
	}
	value_float64.floating_point = (double) integer_value;
	floating_point->value        = value_float64.integer;
	floating_point->value_size   = 64;

	return( 1 );
}

/* Copies the floating point to an integer value
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_to_integer(
     libfvalue_floating_point_t *floating_point,
     uint64_t *integer_value,
     size_t *integer_value_size,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_float64;

	static char *function = "libfvalue_floating_point_copy_to_integer";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( integer_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid integer value.",
		 function );

		return( -1 );
	}
	if( integer_value_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid integer value size.",
		 function );

		return( -1 );
	}
	value_float64.integer = floating_point->value;
	*integer_value        = (uint64_t) value_float64.floating_point;
	*integer_value_size   = 64;

	return( 1 );
}

/* Copies the floating point from a floating point value
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_from_floating_point(
     libfvalue_floating_point_t *floating_point,
     double floating_point_value,
     size_t floating_point_value_size,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_float64;

	static char *function = "libfvalue_floating_point_copy_from_floating_point";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( ( floating_point_value_size != 32 )
	 && ( floating_point_value_size != 64 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported floating point value size.",
		 function );

		return( -1 );
	}
	value_float64.floating_point = floating_point_value;
	floating_point->value        = value_float64.integer;
	floating_point->value_size   = 64;

	return( 1 );
}

/* Copies the floating point to a floating point value
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_to_floating_point(
     libfvalue_floating_point_t *floating_point,
     double *floating_point_value,
     size_t *floating_point_value_size,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_float64;

	static char *function = "libfvalue_floating_point_copy_to_floating_point";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( floating_point_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point value.",
		 function );

		return( -1 );
	}
	if( floating_point_value_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point value size.",
		 function );

		return( -1 );
	}
	value_float64.integer      = floating_point->value;
	*floating_point_value      = (double) value_float64.floating_point;
	*floating_point_value_size = 64;

	return( 1 );
}

/* Retrieves the size of a string of the floating point
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_get_string_size(
     libfvalue_floating_point_t *floating_point,
     size_t *string_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_get_string_size";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( libfvalue_string_size_from_floating_point(
	     string_size,
	     floating_point->value,
	     floating_point->value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to determine size of string of %" PRIzd "-bit floating point.",
		 function,
		 floating_point->value_size );

		return( -1 );
	}
	return( 1 );
}

/* Copies the floating point from an UTF-8 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_from_utf8_string_with_index(
     libfvalue_floating_point_t *floating_point,
     uint8_t *utf8_string,
     size_t utf8_string_length,
     size_t *utf8_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_copy_from_utf8_string_with_index";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( libfvalue_utf8_string_with_index_copy_to_floating_point(
	     utf8_string,
	     utf8_string_length,
	     utf8_string_index,
	     &( floating_point->value ),
	     floating_point->value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy %" PRIzd "-bit floating point from UTF-8 string.",
		 function,
		 floating_point->value_size );

		return( -1 );
	}
	return( 1 );
}

/* Copies the floating point to an UTF-8 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_to_utf8_string_with_index(
     libfvalue_floating_point_t *floating_point,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_copy_to_utf8_string_with_index";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( libfvalue_utf8_string_with_index_copy_from_floating_point(
	     utf8_string,
	     utf8_string_size,
	     utf8_string_index,
	     floating_point->value,
	     floating_point->value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy %" PRIzd "-bit floating point to UTF-8 string.",
		 function,
		 floating_point->value_size );

		return( -1 );
	}
	return( 1 );
}

/* Copies the floating point from an UTF-16 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_from_utf16_string_with_index(
     libfvalue_floating_point_t *floating_point,
     uint16_t *utf16_string,
     size_t utf16_string_length,
     size_t *utf16_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_copy_from_utf16_string_with_index";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( libfvalue_utf16_string_with_index_copy_to_floating_point(
	     utf16_string,
	     utf16_string_length,
	     utf16_string_index,
	     &( floating_point->value ),
	     floating_point->value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy %" PRIzd "-bit floating point from UTF-16 string.",
		 function,
		 floating_point->value_size );

		return( -1 );
	}
	return( 1 );
}

/* Copies the floating point to an UTF-16 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_to_utf16_string_with_index(
     libfvalue_floating_point_t *floating_point,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_copy_to_utf16_string_with_index";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( libfvalue_utf16_string_with_index_copy_from_floating_point(
	     utf16_string,
	     utf16_string_size,
	     utf16_string_index,
	     floating_point->value,
	     floating_point->value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy %" PRIzd "-bit floating point to UTF-16 string.",
		 function,
		 floating_point->value_size );

		return( -1 );
	}
	return( 1 );
}

/* Copies the floating point from an UTF-32 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_from_utf32_string_with_index(
     libfvalue_floating_point_t *floating_point,
     uint32_t *utf32_string,
     size_t utf32_string_length,
     size_t *utf32_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_copy_from_utf32_string_with_index";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( libfvalue_utf32_string_with_index_copy_to_floating_point(
	     utf32_string,
	     utf32_string_length,
	     utf32_string_index,
	     &( floating_point->value ),
	     floating_point->value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy %" PRIzd "-bit floating point from UTF-32 string.",
		 function,
		 floating_point->value_size );

		return( -1 );
	}
	return( 1 );
}

/* Copies the floating point to an UTF-32 encoded string
 * Returns 1 if successful or -1 on error
 */
int libfvalue_floating_point_copy_to_utf32_string_with_index(
     libfvalue_floating_point_t *floating_point,
     uint32_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf32_string_index,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function = "libfvalue_floating_point_copy_to_utf32_string_with_index";

	if( floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point.",
		 function );

		return( -1 );
	}
	if( libfvalue_utf32_string_with_index_copy_from_floating_point(
	     utf32_string,
	     utf32_string_size,
	     utf32_string_index,
	     floating_point->value,
	     floating_point->value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy %" PRIzd "-bit floating point to UTF-32 string.",
		 function,
		 floating_point->value_size );

		return( -1 );
	}
	return( 1 );
}

/* Determines the size of a string of a floating point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_string_size_from_floating_point(
     size_t *string_size,
     uint64_t floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function       = "libfvalue_string_size_from_floating_point";
	size_t safe_string_size     = 0;
	uint32_t string_format_type = 0;
	uint32_t supported_flags    = 0;
	uint8_t is_indeterminate    = 0;
	uint8_t is_infinite         = 0;
	uint8_t is_not_a_number     = 0;
	uint8_t is_signed           = 0;
	int8_t bit_shift            = 0;

	if( string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string size.",
		 function );

		return( -1 );
	}
	if( ( floating_point_value_size != 32 )
	 && ( floating_point_value_size != 64 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported floating point value size.",
		 function );

		return( -1 );
	}
	supported_flags = 0x000000ffUL;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_format_type = string_format_flags & 0x000000ffUL;

	if( ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_DECIMAL )
	 && ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format type.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		safe_string_size = ( floating_point_value_size >> 2 ) + 3;
	}
	else
	{
		bit_shift = (uint8_t) ( floating_point_value_size - 1 );
		is_signed = (uint8_t) ( floating_point_value >> bit_shift );

		if( is_signed != 0 )
		{
			floating_point_value &= ~( (uint64_t) 1 << bit_shift );
		}
		switch( floating_point_value_size )
		{
			case 32:
				if( floating_point_value == 0x7f800000UL )
				{
					is_infinite = 1;
				}
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7fc00000UL ) )
				{
					is_indeterminate = 1;
				}
				else if( ( floating_point_value >= 0x7f800001UL )
				      && ( floating_point_value <= 0x7fffffffUL ) )
				{
					is_not_a_number = 1;
				}
				break;

			case 64:
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				if( floating_point_value == 0x7ff0000000000000UL )
#else
				if( floating_point_value == 0x7ff0000000000000ULL )
#endif
				{
					is_infinite = 1;
				}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7ff8000000000000UL ) )
#else
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7ff8000000000000ULL ) )
#endif
				{
					is_indeterminate = 1;
				}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				else if( ( floating_point_value >= 0x7ff0000000000001UL )
				      && ( floating_point_value <= 0x7fffffffffffffffUL ) )
#else
				else if( ( floating_point_value >= 0x7ff0000000000001ULL )
				      && ( floating_point_value <= 0x7fffffffffffffffULL ) )
#endif
				{
					is_not_a_number = 1;
				}
				break;
		}
		if( is_indeterminate != 0 )
		{
			/* "Ind\x00" */
			safe_string_size = 4;
		}
		else if( is_infinite != 0 )
		{
			/* "Inf\x00" */
			safe_string_size = 4;
		}
		else if( is_not_a_number != 0 )
		{
			/* "Nan\x00" */
			safe_string_size = 4;
		}
		else
		{
			/* "[-]0.000000e[+-]000\x00" */
			if( is_signed != 0 )
			{
				safe_string_size = 15;
			}
			else
			{
				safe_string_size = 14;
			}
		}
	}
	*string_size = safe_string_size;

	return( 1 );
}

/* Copies an UTF-8 encoded string from a floating point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_utf8_string_copy_from_floating_point(
     uint8_t *utf8_string,
     size_t utf8_string_size,
     uint64_t floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function    = "libfvalue_utf8_string_copy_from_floating_point";
	size_t utf8_string_index = 0;

	if( libfvalue_utf8_string_with_index_copy_from_floating_point(
	     utf8_string,
	     utf8_string_size,
	     &utf8_string_index,
	     floating_point_value,
	     floating_point_value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy floating point value to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-8 encoded string of from floating_point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_utf8_string_with_index_copy_from_floating_point(
     uint8_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf8_string_index,
     uint64_t floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	byte_stream_float32_t value_float32;
	byte_stream_float64_t value_float64;

	static char *function         = "libfvalue_utf8_string_with_index_copy_from_floating_point";
	size_t safe_utf8_string_index = 0;
	uint64_t divider              = 0;
	uint64_t value_fraction       = 0;
	uint32_t string_format_type   = 0;
	uint32_t supported_flags      = 0;
	int16_t exponent10            = 0;
	int16_t exponent2             = 0;
	uint8_t byte_value            = 0;
	uint8_t digit_index           = 0;
	uint8_t exponent_sign         = 0;
	uint8_t is_indeterminate      = 0;
	uint8_t is_infinite           = 0;
	uint8_t is_not_a_number       = 0;
	uint8_t is_signed             = 0;
	uint8_t number_of_characters  = 0;
	int8_t bit_shift              = 0;
	double exponent_value         = 0.0;
	double value_float            = 0.0;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	if( *utf8_string_index >= utf8_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-8 string index value out of bounds.",
		 function );

		return( -1 );
	}
	safe_utf8_string_index = *utf8_string_index;

	if( ( floating_point_value_size != 32 )
	 && ( floating_point_value_size != 64 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported floating point value size.",
		 function );

		return( -1 );
	}
	supported_flags = 0x000000ffUL;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_format_type = string_format_flags & 0x000000ffUL;

	if( ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_DECIMAL )
	 && ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format type.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		number_of_characters = (uint8_t) ( floating_point_value_size >> 2 ) + 3;
	}
	else
	{
		bit_shift = (uint8_t) ( floating_point_value_size - 1 );
		is_signed = (uint8_t) ( floating_point_value >> bit_shift );

		if( is_signed != 0 )
		{
			floating_point_value &= ~( (uint64_t) 1 << bit_shift );
		}
		switch( floating_point_value_size )
		{
			case 32:
				if( floating_point_value == 0x7f800000UL )
				{
					is_infinite = 1;
				}
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7fc00000UL ) )
				{
					is_indeterminate = 1;
				}
				else if( ( floating_point_value >= 0x7f800001UL )
				      && ( floating_point_value <= 0x7fffffffUL ) )
				{
					is_not_a_number = 1;
				}
				else if( floating_point_value != 0 )
				{
					value_float32.integer = (uint32_t) floating_point_value;
					value_float           = (double) value_float32.floating_point;

					exponent2 = (int16_t) ( floating_point_value >> 23 );

					if( exponent2 == 0 )
					{
						exponent2 = -126;
					}
					else
					{
						exponent2 -= 127;
					}
				}
				break;

			case 64:
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				if( floating_point_value == 0x7ff0000000000000UL )
#else
				if( floating_point_value == 0x7ff0000000000000ULL )
#endif
				{
					is_infinite = 1;
				}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7ff8000000000000UL ) )
#else
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7ff8000000000000ULL ) )
#endif
				{
					is_indeterminate = 1;
				}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				else if( ( floating_point_value >= 0x7ff0000000000001UL )
				      && ( floating_point_value <= 0x7fffffffffffffffUL ) )
#else
				else if( ( floating_point_value >= 0x7ff0000000000001ULL )
				      && ( floating_point_value <= 0x7fffffffffffffffULL ) )
#endif
				{
					is_not_a_number = 1;
				}
				else if( floating_point_value != 0 )
				{
					value_float64.integer = (uint64_t) floating_point_value;
					value_float           = (double) value_float64.floating_point;

					exponent2 = (int16_t) ( floating_point_value >> 52 );

					if( exponent2 == 0 )
					{
						exponent2 = -1023;
					}
					else
					{
						exponent2 -= 1023;
					}
				}
				break;
		}
		if( is_indeterminate != 0 )
		{
			/* "Ind\x00" */
			number_of_characters = 4;
		}
		else if( is_infinite != 0 )
		{
			/* "Inf\x00" */
			number_of_characters = 4;
		}
		else if( is_not_a_number != 0 )
		{
			/* "Nan\x00" */
			number_of_characters = 4;
		}
		else
		{
			/* "[-]0.000000e[+-]000\x00" */
			if( is_signed != 0 )
			{
				number_of_characters = 15;
			}
			else
			{
				number_of_characters = 14;
			}
		}
	}
	if( ( number_of_characters > utf8_string_size )
	 || ( safe_utf8_string_index > ( utf8_string_size - number_of_characters ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string size too small.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0';
		utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'x';

		bit_shift = (uint8_t) ( floating_point_value_size - 4 );

		do
		{
			byte_value = (uint8_t) ( ( floating_point_value >> bit_shift ) & 0x0f );

			if( byte_value <= 9 )
			{
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + byte_value;
			}
			else
			{
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'a' + byte_value - 10;
			}
			bit_shift -= 4;
		}
		while( bit_shift >= 0 );
	}
	else
	{
		if( is_indeterminate != 0 )
		{
			/* "Ind\x00" */
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'I';
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'n';
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'd';
		}
		else if( is_infinite != 0 )
		{
			/* "Inf\x00" */
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'I';
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'n';
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'f';
		}
		else if( is_not_a_number != 0 )
		{
			/* "Nan\x00" */
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'N';
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'a';
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'N';
		}
		else
		{
			/* "[-]0.000000e[+-]000\x00" */
			if( is_signed != 0 )
			{
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '-';
			}
			if( exponent2 < 0 )
			{
				exponent_sign = (uint8_t) '-';
				exponent2    *= -1;
			}
			else
			{
				exponent_sign = (uint8_t) '+';
			}
			exponent_value = 1.0;
			exponent10     = 0;

			while( exponent2 > 0 )
			{
				exponent_value *= 2;
				exponent2--;

				if( exponent_value >= 10.0 )
				{
					exponent_value /= 10.0;
					exponent10++;

					if( exponent_sign == (uint8_t) '-' )
					{
						value_float *= 10.0;
					}
					else
					{
						value_float /= 10.0;
					}
				}
			}
			if( value_float != 0.0 )
			{
				while( ( value_float < 1.0 )
				    || ( value_float >= 10.0 ) )
				{
					exponent10++;

					if( exponent_sign == (uint8_t) '-' )
					{
						value_float *= 10;
					}
					else
					{
						value_float /= 10;
					}
				}
			}
			for( digit_index = 0;
			     digit_index < 7;
			     digit_index++ )
			{
				value_fraction *= 10;
				value_fraction += (uint8_t) value_float;

				value_float -= (uint8_t) value_float;
				value_float *= 10.0;
			}
			if( value_float >= 5.0 )
			{
				value_fraction += 1;
			}
			divider = 1000000;

			for( digit_index = 0;
			     digit_index < 7;
			     digit_index++ )
			{
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( value_fraction / divider );

				if( digit_index == 0 )
				{
					utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '.';
				}
				value_fraction %= divider;
				divider        /= 10;
			}
			utf8_string[ safe_utf8_string_index++ ] = (uint8_t) 'e';
			utf8_string[ safe_utf8_string_index++ ] = exponent_sign;

			divider = 100;

			for( digit_index = 0;
			     digit_index < 3;
			     digit_index++ )
			{
				utf8_string[ safe_utf8_string_index++ ] = (uint8_t) '0' + (uint8_t) ( exponent10 / divider );

				exponent10 %= divider;
				divider    /= 10;
			}
		}
	}
	utf8_string[ safe_utf8_string_index++ ] = 0;

	*utf8_string_index = safe_utf8_string_index;

	return( 1 );
}

/* Copies an UTF-8 encoded string to a floating point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_utf8_string_with_index_copy_to_floating_point(
     uint8_t *utf8_string,
     size_t utf8_string_length,
     size_t *utf8_string_index,
     uint64_t *floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_float64;

	static char *function         = "libfvalue_utf8_string_with_index_copy_to_floating_point";
	size_t fraction_index         = 0;
	size_t maximum_string_index   = 0;
	size_t safe_utf8_string_index = 0;
	uint64_t divider              = 0;
	uint64_t value_64bit          = 0;
	uint32_t string_format_type   = 0;
	uint32_t supported_flags      = 0;
	uint8_t byte_value            = 0;
	uint8_t character_value       = 0;
	int8_t bit_shift              = 0;
	int8_t sign                   = 1;
	double value_fraction         = 0.0;

	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string index.",
		 function );

		return( -1 );
	}
	if( *utf8_string_index >= utf8_string_length )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-8 string index value out of bounds.",
		 function );

		return( -1 );
	}
	safe_utf8_string_index = *utf8_string_index;

	if( floating_point_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point value.",
		 function );

		return( -1 );
	}
	if( ( floating_point_value_size != 32 )
	 && ( floating_point_value_size != 64 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported floating point value size.",
		 function );

		return( -1 );
	}
	supported_flags = 0x000000ffUL;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_format_type = string_format_flags & 0x000000ffUL;

	if( ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_DECIMAL )
	 && ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format type.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		maximum_string_index = (size_t) ( floating_point_value_size >> 2 ) + 3;
	}
	else
	{
		/* The string is at least a single digit with an end of string character
		 */
		maximum_string_index = 2;

		bit_shift = (uint8_t) ( floating_point_value_size - 1 );

		divider = 1;

		value_64bit = ~( ( ~( (uint64_t) 1 << bit_shift ) >> bit_shift ) << bit_shift );

		while( ( value_64bit / divider ) >= 10 )
		{
			divider *= 10;

			maximum_string_index += 1;
		}
	}
	maximum_string_index += safe_utf8_string_index;

	if( maximum_string_index > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid maximum string index value exceeds maximum.",
		 function );

		return( -1 );
	}
	value_64bit = 0;

	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		character_value = utf8_string[ safe_utf8_string_index++ ];

		if(character_value != (uint8_t) '0' )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: 0x%02" PRIx8 " at index: %d.",
			 function,
			 character_value,
			 safe_utf8_string_index );

			return( -1 );
		}
		character_value = utf8_string[ safe_utf8_string_index++ ];

		if( character_value != (uint8_t) 'x' )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: 0x%02" PRIx8 " at index: %d.",
			 function,
			 character_value,
			 safe_utf8_string_index );

			return( -1 );
		}
		while( safe_utf8_string_index < utf8_string_length )
		{
			character_value = utf8_string[ safe_utf8_string_index ];

			if( character_value == 0 )
			{
				break;
			}
			if( safe_utf8_string_index > (size_t) maximum_string_index )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
				 "%s: string too large.",
				 function );

				return( -1 );
			}
			value_64bit <<= 4;

			if( ( character_value >= (uint8_t) '0' )
			 && ( character_value <= (uint8_t) '9' ) )
			{
				byte_value = (uint8_t) ( character_value - (uint8_t) '0' );
			}
			else if( ( character_value >= (uint8_t) 'A' )
			      && ( character_value <= (uint8_t) 'F' ) )
			{
				byte_value = (uint8_t) ( character_value - (uint8_t) 'A' + 10 );
			}
			else if( ( character_value >= (uint8_t) 'a' )
			      && ( character_value <= (uint8_t) 'f' ) )
			{
				byte_value = (uint8_t) ( character_value - (uint8_t) 'a' + 10 );
			}
			else
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported character value: 0x%02" PRIx8 " at index: %d.",
				 function,
				 character_value,
				 safe_utf8_string_index );

				return( -1 );
			}
			value_64bit += byte_value;

			safe_utf8_string_index++;
		}
	}
	else
	{
		value_float64.floating_point = 0.0;

		character_value = utf8_string[ safe_utf8_string_index ];

		/* In the maximum possible string one character is substituted for the sign
		 */
		if( character_value == (uint8_t) '-' )
		{
			safe_utf8_string_index++;

			sign = -1;
		}
		else if( character_value == (uint8_t) '+' )
		{
			safe_utf8_string_index++;
		}
		while( safe_utf8_string_index < utf8_string_length )
		{
			character_value = utf8_string[ safe_utf8_string_index ];

			if( character_value == 0 )
			{
				break;
			}
			if( safe_utf8_string_index > (size_t) maximum_string_index )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
				 "%s: string too large.",
				 function );

				return( -1 );
			}
			if( character_value == (uint8_t) '.' )
			{
				break;
			}
			if( ( character_value < (uint8_t) '0' )
			 || ( character_value > (uint8_t) '9' ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported character value: 0x%02" PRIx8 " at index: %d.",
				 function,
				 character_value,
				 safe_utf8_string_index );

				return( -1 );
			}
			value_float64.floating_point *= 10;
			value_float64.floating_point += character_value - (uint8_t) '0';

			safe_utf8_string_index++;
		}
		fraction_index = safe_utf8_string_index;

		safe_utf8_string_index++;
		utf8_string_length--;

		if( utf8_string_length > (size_t) maximum_string_index )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
			 "%s: string too large.",
			 function );

			return( -1 );
		}
		while( fraction_index < utf8_string_length )
		{
			character_value = utf8_string[ utf8_string_length ];

			if( character_value == 0 )
			{
				break;
			}
			if( ( character_value < (uint8_t) '0' )
			 || ( character_value > (uint8_t) '9' ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported character value: 0x%02" PRIx8 " at index: %d.",
				 function,
				 character_value,
				 utf8_string_length );

				return( -1 );
			}
			value_fraction /= 10;
			value_fraction += character_value - (uint8_t) '0';

			safe_utf8_string_index++;
			utf8_string_length--;
		}
		if( value_fraction != 0.0 )
		{
			value_float64.floating_point += value_fraction / 10;
		}
		if( sign == -1 )
		{
			value_float64.floating_point *= 1.0;
		}
		value_64bit = value_float64.integer;
	}
	*utf8_string_index    = safe_utf8_string_index;
	*floating_point_value = value_64bit;

	return( 1 );
}

/* Copies an UTF-16 encoded string of a floating point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_utf16_string_copy_from_floating_point(
     uint16_t *utf16_string,
     size_t utf16_string_size,
     uint64_t floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function     = "libfvalue_utf16_string_copy_from_floating_point";
	size_t utf16_string_index = 0;

	if( libfvalue_utf16_string_with_index_copy_from_floating_point(
	     utf16_string,
	     utf16_string_size,
	     &utf16_string_index,
	     floating_point_value,
	     floating_point_value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy floating point value to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-16 encoded string of from floating_point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_utf16_string_with_index_copy_from_floating_point(
     uint16_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_string_index,
     uint64_t floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	byte_stream_float32_t value_float32;
	byte_stream_float64_t value_float64;

	static char *function          = "libfvalue_utf16_string_with_index_copy_from_floating_point";
	size_t safe_utf16_string_index = 0;
	uint64_t divider               = 0;
	uint64_t value_fraction        = 0;
	uint32_t string_format_type    = 0;
	uint32_t supported_flags       = 0;
	int16_t exponent10             = 0;
	int16_t exponent2              = 0;
	uint8_t byte_value             = 0;
	uint8_t digit_index            = 0;
	uint8_t exponent_sign          = 0;
	uint8_t is_indeterminate       = 0;
	uint8_t is_infinite            = 0;
	uint8_t is_not_a_number        = 0;
	uint8_t is_signed              = 0;
	uint8_t number_of_characters   = 0;
	int8_t bit_shift               = 0;
	double exponent_value          = 0.0;
	double value_float             = 0.0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( *utf16_string_index >= utf16_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-16 string index value out of bounds.",
		 function );

		return( -1 );
	}
	safe_utf16_string_index = *utf16_string_index;

	if( ( floating_point_value_size != 32 )
	 && ( floating_point_value_size != 64 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported floating point value size.",
		 function );

		return( -1 );
	}
	supported_flags = 0x000000ffUL;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_format_type = string_format_flags & 0x000000ffUL;

	if( ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_DECIMAL )
	 && ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format type.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		number_of_characters = (uint16_t) ( floating_point_value_size >> 2 ) + 3;
	}
	else
	{
		bit_shift = (uint16_t) ( floating_point_value_size - 1 );
		is_signed = (uint16_t) ( floating_point_value >> bit_shift );

		if( is_signed != 0 )
		{
			floating_point_value &= ~( (uint64_t) 1 << bit_shift );
		}
		switch( floating_point_value_size )
		{
			case 32:
				if( floating_point_value == 0x7f800000UL )
				{
					is_infinite = 1;
				}
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7fc00000UL ) )
				{
					is_indeterminate = 1;
				}
				else if( ( floating_point_value >= 0x7f800001UL )
				      && ( floating_point_value <= 0x7fffffffUL ) )
				{
					is_not_a_number = 1;
				}
				else if( floating_point_value != 0 )
				{
					value_float32.integer = (uint32_t) floating_point_value;
					value_float           = (double) value_float32.floating_point;

					exponent2 = (int16_t) ( floating_point_value >> 23 );

					if( exponent2 == 0 )
					{
						exponent2 = -126;
					}
					else
					{
						exponent2 -= 127;
					}
				}
				break;

			case 64:
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				if( floating_point_value == 0x7ff0000000000000UL )
#else
				if( floating_point_value == 0x7ff0000000000000ULL )
#endif
				{
					is_infinite = 1;
				}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7ff8000000000000UL ) )
#else
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7ff8000000000000ULL ) )
#endif
				{
					is_indeterminate = 1;
				}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				else if( ( floating_point_value >= 0x7ff0000000000001UL )
				      && ( floating_point_value <= 0x7fffffffffffffffUL ) )
#else
				else if( ( floating_point_value >= 0x7ff0000000000001ULL )
				      && ( floating_point_value <= 0x7fffffffffffffffULL ) )
#endif
				{
					is_not_a_number = 1;
				}
				else if( floating_point_value != 0 )
				{
					value_float64.integer = (uint64_t) floating_point_value;
					value_float           = (double) value_float64.floating_point;

					exponent2 = (int16_t) ( floating_point_value >> 52 );

					if( exponent2 == 0 )
					{
						exponent2 = -1023;
					}
					else
					{
						exponent2 -= 1023;
					}
				}
				break;
		}
		if( is_indeterminate != 0 )
		{
			/* "Ind\x00" */
			number_of_characters = 4;
		}
		else if( is_infinite != 0 )
		{
			/* "Inf\x00" */
			number_of_characters = 4;
		}
		else if( is_not_a_number != 0 )
		{
			/* "Nan\x00" */
			number_of_characters = 4;
		}
		else
		{
			/* "[-]0.000000e[+-]000\x00" */
			if( is_signed != 0 )
			{
				number_of_characters = 15;
			}
			else
			{
				number_of_characters = 14;
			}
		}
	}
	if( ( number_of_characters > utf16_string_size )
	 || ( safe_utf16_string_index > ( utf16_string_size - number_of_characters ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-16 string size too small.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0';
		utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'x';

		bit_shift = (uint16_t) ( floating_point_value_size - 4 );

		do
		{
			byte_value = (uint16_t) ( ( floating_point_value >> bit_shift ) & 0x0f );

			if( byte_value <= 9 )
			{
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + byte_value;
			}
			else
			{
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'a' + byte_value - 10;
			}
			bit_shift -= 4;
		}
		while( bit_shift >= 0 );
	}
	else
	{
		if( is_indeterminate != 0 )
		{
			/* "Ind\x00" */
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'I';
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'n';
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'd';
		}
		else if( is_infinite != 0 )
		{
			/* "Inf\x00" */
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'I';
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'n';
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'f';
		}
		else if( is_not_a_number != 0 )
		{
			/* "Nan\x00" */
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'N';
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'a';
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'N';
		}
		else
		{
			/* "[-]0.000000e[+-]000\x00" */
			if( is_signed != 0 )
			{
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '-';
			}
			if( exponent2 < 0 )
			{
				exponent_sign = (uint16_t) '-';
				exponent2    *= -1;
			}
			else
			{
				exponent_sign = (uint16_t) '+';
			}
			exponent_value = 1.0;
			exponent10     = 0;

			while( exponent2 > 0 )
			{
				exponent_value *= 2;
				exponent2--;

				if( exponent_value >= 10.0 )
				{
					exponent_value /= 10.0;
					exponent10++;

					if( exponent_sign == (uint16_t) '-' )
					{
						value_float *= 10.0;
					}
					else
					{
						value_float /= 10.0;
					}
				}
			}
			if( value_float != 0.0 )
			{
				while( ( value_float < 1.0 )
				    || ( value_float >= 10.0 ) )
				{
					exponent10++;

					if( exponent_sign == (uint16_t) '-' )
					{
						value_float *= 10;
					}
					else
					{
						value_float /= 10;
					}
				}
			}
			for( digit_index = 0;
			     digit_index < 7;
			     digit_index++ )
			{
				value_fraction *= 10;
				value_fraction += (uint16_t) value_float;

				value_float -= (uint16_t) value_float;
				value_float *= 10.0;
			}
			if( value_float >= 5.0 )
			{
				value_fraction += 1;
			}
			divider = 1000000;

			for( digit_index = 0;
			     digit_index < 7;
			     digit_index++ )
			{
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( value_fraction / divider );

				if( digit_index == 0 )
				{
					utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '.';
				}
				value_fraction %= divider;
				divider        /= 10;
			}
			utf16_string[ safe_utf16_string_index++ ] = (uint16_t) 'e';
			utf16_string[ safe_utf16_string_index++ ] = exponent_sign;

			divider = 100;

			for( digit_index = 0;
			     digit_index < 3;
			     digit_index++ )
			{
				utf16_string[ safe_utf16_string_index++ ] = (uint16_t) '0' + (uint16_t) ( exponent10 / divider );

				exponent10 %= divider;
				divider    /= 10;
			}
		}
	}
	utf16_string[ safe_utf16_string_index++ ] = 0;

	*utf16_string_index = safe_utf16_string_index;

	return( 1 );
}

/* Copies an UTF-16 encoded string to a floating point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_utf16_string_with_index_copy_to_floating_point(
     uint16_t *utf16_string,
     size_t utf16_string_length,
     size_t *utf16_string_index,
     uint64_t *floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_float64;

	static char *function          = "libfvalue_utf16_string_with_index_copy_to_floating_point";
	size_t fraction_index          = 0;
	size_t maximum_string_index    = 0;
	size_t safe_utf16_string_index = 0;
	uint64_t divider               = 0;
	uint64_t value_64bit           = 0;
	uint32_t string_format_type    = 0;
	uint32_t supported_flags       = 0;
	uint8_t byte_value             = 0;
	uint8_t character_value        = 0;
	int8_t bit_shift               = 0;
	int8_t sign                    = 1;
	double value_fraction          = 0.0;

	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf16_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string index.",
		 function );

		return( -1 );
	}
	if( *utf16_string_index >= utf16_string_length )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-16 string index value out of bounds.",
		 function );

		return( -1 );
	}
	safe_utf16_string_index = *utf16_string_index;

	if( floating_point_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point value.",
		 function );

		return( -1 );
	}
	if( ( floating_point_value_size != 32 )
	 && ( floating_point_value_size != 64 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported floating point value size.",
		 function );

		return( -1 );
	}
	supported_flags = 0x000000ffUL;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_format_type = string_format_flags & 0x000000ffUL;

	if( ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_DECIMAL )
	 && ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format type.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		maximum_string_index = (size_t) ( floating_point_value_size >> 2 ) + 3;
	}
	else
	{
		/* The string is at least a single digit with an end of string character
		 */
		maximum_string_index = 2;

		bit_shift = (uint8_t) ( floating_point_value_size - 1 );

		divider = 1;

		value_64bit = ~( ( ~( (uint64_t) 1 << bit_shift ) >> bit_shift ) << bit_shift );

		while( ( value_64bit / divider ) >= 10 )
		{
			divider *= 10;

			maximum_string_index += 1;
		}
	}
	maximum_string_index += safe_utf16_string_index;

	if( maximum_string_index > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid maximum string index value exceeds maximum.",
		 function );

		return( -1 );
	}
	value_64bit = 0;

	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		character_value = utf16_string[ safe_utf16_string_index++ ];

		if(character_value != (uint16_t) '0' )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: 0x%02" PRIx16 " at index: %d.",
			 function,
			 character_value,
			 safe_utf16_string_index );

			return( -1 );
		}
		character_value = utf16_string[ safe_utf16_string_index++ ];

		if( character_value != (uint16_t) 'x' )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: 0x%02" PRIx16 " at index: %d.",
			 function,
			 character_value,
			 safe_utf16_string_index );

			return( -1 );
		}
		while( safe_utf16_string_index < utf16_string_length )
		{
			character_value = utf16_string[ safe_utf16_string_index ];

			if( character_value == 0 )
			{
				break;
			}
			if( safe_utf16_string_index > (size_t) maximum_string_index )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
				 "%s: string too large.",
				 function );

				return( -1 );
			}
			value_64bit <<= 4;

			if( ( character_value >= (uint16_t) '0' )
			 && ( character_value <= (uint16_t) '9' ) )
			{
				byte_value = (uint8_t) ( character_value - (uint16_t) '0' );
			}
			else if( ( character_value >= (uint16_t) 'A' )
			      && ( character_value <= (uint16_t) 'F' ) )
			{
				byte_value = (uint8_t) ( character_value - (uint16_t) 'A' + 10 );
			}
			else if( ( character_value >= (uint16_t) 'a' )
			      && ( character_value <= (uint16_t) 'f' ) )
			{
				byte_value = (uint8_t) ( character_value - (uint16_t) 'a' + 10 );
			}
			else
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported character value: 0x04%" PRIx16 " at index: %d.",
				 function,
				 character_value,
				 safe_utf16_string_index );

				return( -1 );
			}
			value_64bit += byte_value;

			safe_utf16_string_index++;
		}
	}
	else
	{
		value_float64.floating_point = 0.0;

		character_value = utf16_string[ safe_utf16_string_index ];

		/* In the maximum possible string one character is substituted for the sign
		 */
		if( character_value == (uint16_t) '-' )
		{
			safe_utf16_string_index++;

			sign = -1;
		}
		else if( character_value == (uint16_t) '+' )
		{
			safe_utf16_string_index++;
		}
		while( safe_utf16_string_index < utf16_string_length )
		{
			character_value = utf16_string[ safe_utf16_string_index ];

			if( character_value == 0 )
			{
				break;
			}
			if( safe_utf16_string_index > (size_t) maximum_string_index )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
				 "%s: string too large.",
				 function );

				return( -1 );
			}
			if( character_value == (uint16_t) '.' )
			{
				break;
			}
			if( ( character_value < (uint16_t) '0' )
			 || ( character_value > (uint16_t) '9' ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported character value: 0x%02" PRIx16 " at index: %d.",
				 function,
				 character_value,
				 safe_utf16_string_index );

				return( -1 );
			}
			value_float64.floating_point *= 10;
			value_float64.floating_point += character_value - (uint16_t) '0';

			safe_utf16_string_index++;
		}
		fraction_index = safe_utf16_string_index;

		safe_utf16_string_index++;
		utf16_string_length--;

		if( utf16_string_length > (size_t) maximum_string_index )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
			 "%s: string too large.",
			 function );

			return( -1 );
		}
		while( fraction_index < utf16_string_length )
		{
			character_value = utf16_string[ utf16_string_length ];

			if( character_value == 0 )
			{
				break;
			}
			if( ( character_value < (uint16_t) '0' )
			 || ( character_value > (uint16_t) '9' ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported character value: 0x%02" PRIx16 " at index: %d.",
				 function,
				 character_value,
				 utf16_string_length );

				return( -1 );
			}
			value_fraction /= 10;
			value_fraction += character_value - (uint16_t) '0';

			safe_utf16_string_index++;
			utf16_string_length--;
		}
		if( value_fraction != 0.0 )
		{
			value_float64.floating_point += value_fraction / 10;
		}
		if( sign == -1 )
		{
			value_float64.floating_point *= 1.0;
		}
		value_64bit = value_float64.integer;
	}
	*utf16_string_index   = safe_utf16_string_index;
	*floating_point_value = value_64bit;

	return( 1 );
}

/* Copies an UTF-32 encoded string of a floating point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_utf32_string_copy_from_floating_point(
     uint32_t *utf32_string,
     size_t utf32_string_size,
     uint64_t floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	static char *function     = "libfvalue_utf32_string_copy_from_floating_point";
	size_t utf32_string_index = 0;

	if( libfvalue_utf32_string_with_index_copy_from_floating_point(
	     utf32_string,
	     utf32_string_size,
	     &utf32_string_index,
	     floating_point_value,
	     floating_point_value_size,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy floating point value to UTF-32 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Copies an UTF-32 encoded string of from floating_point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_utf32_string_with_index_copy_from_floating_point(
     uint32_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf32_string_index,
     uint64_t floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	byte_stream_float32_t value_float32;
	byte_stream_float64_t value_float64;

	static char *function          = "libfvalue_utf32_string_with_index_copy_from_floating_point";
	size_t safe_utf32_string_index = 0;
	uint64_t divider               = 0;
	uint64_t value_fraction        = 0;
	uint32_t string_format_type    = 0;
	uint32_t supported_flags       = 0;
	int16_t exponent10             = 0;
	int16_t exponent2              = 0;
	uint8_t byte_value             = 0;
	uint8_t digit_index            = 0;
	uint8_t exponent_sign          = 0;
	uint8_t is_indeterminate       = 0;
	uint8_t is_infinite            = 0;
	uint8_t is_not_a_number        = 0;
	uint8_t is_signed              = 0;
	uint8_t number_of_characters   = 0;
	int8_t bit_shift               = 0;
	double exponent_value          = 0.0;
	double value_float             = 0.0;

	if( utf32_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string index.",
		 function );

		return( -1 );
	}
	if( *utf32_string_index >= utf32_string_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-32 string index value out of bounds.",
		 function );

		return( -1 );
	}
	safe_utf32_string_index = *utf32_string_index;

	if( ( floating_point_value_size != 32 )
	 && ( floating_point_value_size != 64 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported floating point value size.",
		 function );

		return( -1 );
	}
	supported_flags = 0x000000ffUL;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_format_type = string_format_flags & 0x000000ffUL;

	if( ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_DECIMAL )
	 && ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format type.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		number_of_characters = (uint32_t) ( floating_point_value_size >> 2 ) + 3;
	}
	else
	{
		bit_shift = (uint32_t) ( floating_point_value_size - 1 );
		is_signed = (uint32_t) ( floating_point_value >> bit_shift );

		if( is_signed != 0 )
		{
			floating_point_value &= ~( (uint64_t) 1 << bit_shift );
		}
		switch( floating_point_value_size )
		{
			case 32:
				if( floating_point_value == 0x7f800000UL )
				{
					is_infinite = 1;
				}
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7fc00000UL ) )
				{
					is_indeterminate = 1;
				}
				else if( ( floating_point_value >= 0x7f800001UL )
				      && ( floating_point_value <= 0x7fffffffUL ) )
				{
					is_not_a_number = 1;
				}
				else if( floating_point_value != 0 )
				{
					value_float32.integer = (uint32_t) floating_point_value;
					value_float           = (double) value_float32.floating_point;

					exponent2 = (int16_t) ( floating_point_value >> 23 );

					if( exponent2 == 0 )
					{
						exponent2 = -126;
					}
					else
					{
						exponent2 -= 127;
					}
				}
				break;

			case 64:
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				if( floating_point_value == 0x7ff0000000000000UL )
#else
				if( floating_point_value == 0x7ff0000000000000ULL )
#endif
				{
					is_infinite = 1;
				}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7ff8000000000000UL ) )
#else
				else if( ( is_signed != 0 )
				      && ( floating_point_value == 0x7ff8000000000000ULL ) )
#endif
				{
					is_indeterminate = 1;
				}
#if defined( __BORLANDC__ ) && ( __BORLANDC__ < 0x0560 )
				else if( ( floating_point_value >= 0x7ff0000000000001UL )
				      && ( floating_point_value <= 0x7fffffffffffffffUL ) )
#else
				else if( ( floating_point_value >= 0x7ff0000000000001ULL )
				      && ( floating_point_value <= 0x7fffffffffffffffULL ) )
#endif
				{
					is_not_a_number = 1;
				}
				else if( floating_point_value != 0 )
				{
					value_float64.integer = (uint64_t) floating_point_value;
					value_float           = (double) value_float64.floating_point;

					exponent2 = (int16_t) ( floating_point_value >> 52 );

					if( exponent2 == 0 )
					{
						exponent2 = -1023;
					}
					else
					{
						exponent2 -= 1023;
					}
				}
				break;
		}
		if( is_indeterminate != 0 )
		{
			/* "Ind\x00" */
			number_of_characters = 4;
		}
		else if( is_infinite != 0 )
		{
			/* "Inf\x00" */
			number_of_characters = 4;
		}
		else if( is_not_a_number != 0 )
		{
			/* "Nan\x00" */
			number_of_characters = 4;
		}
		else
		{
			/* "[-]0.000000e[+-]000\x00" */
			if( is_signed != 0 )
			{
				number_of_characters = 15;
			}
			else
			{
				number_of_characters = 14;
			}
		}
	}
	if( ( number_of_characters > utf32_string_size )
	 || ( safe_utf32_string_index > ( utf32_string_size - number_of_characters ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-32 string size too small.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		utf32_string[ safe_utf32_string_index++ ] = (uint32_t) '0';
		utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'x';

		bit_shift = (uint32_t) ( floating_point_value_size - 4 );

		do
		{
			byte_value = (uint32_t) ( ( floating_point_value >> bit_shift ) & 0x0f );

			if( byte_value <= 9 )
			{
				utf32_string[ safe_utf32_string_index++ ] = (uint32_t) '0' + byte_value;
			}
			else
			{
				utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'a' + byte_value - 10;
			}
			bit_shift -= 4;
		}
		while( bit_shift >= 0 );
	}
	else
	{
		if( is_indeterminate != 0 )
		{
			/* "Ind\x00" */
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'I';
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'n';
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'd';
		}
		else if( is_infinite != 0 )
		{
			/* "Inf\x00" */
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'I';
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'n';
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'f';
		}
		else if( is_not_a_number != 0 )
		{
			/* "Nan\x00" */
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'N';
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'a';
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'N';
		}
		else
		{
			/* "[-]0.000000e[+-]000\x00" */
			if( is_signed != 0 )
			{
				utf32_string[ safe_utf32_string_index++ ] = (uint32_t) '-';
			}
			if( exponent2 < 0 )
			{
				exponent_sign = (uint32_t) '-';
				exponent2    *= -1;
			}
			else
			{
				exponent_sign = (uint32_t) '+';
			}
			exponent_value = 1.0;
			exponent10     = 0;

			while( exponent2 > 0 )
			{
				exponent_value *= 2;
				exponent2--;

				if( exponent_value >= 10.0 )
				{
					exponent_value /= 10.0;
					exponent10++;

					if( exponent_sign == (uint32_t) '-' )
					{
						value_float *= 10.0;
					}
					else
					{
						value_float /= 10.0;
					}
				}
			}
			if( value_float != 0.0 )
			{
				while( ( value_float < 1.0 )
				    || ( value_float >= 10.0 ) )
				{
					exponent10++;

					if( exponent_sign == (uint32_t) '-' )
					{
						value_float *= 10;
					}
					else
					{
						value_float /= 10;
					}
				}
			}
			for( digit_index = 0;
			     digit_index < 7;
			     digit_index++ )
			{
				value_fraction *= 10;
				value_fraction += (uint32_t) value_float;

				value_float -= (uint32_t) value_float;
				value_float *= 10.0;
			}
			if( value_float >= 5.0 )
			{
				value_fraction += 1;
			}
			divider = 1000000;

			for( digit_index = 0;
			     digit_index < 7;
			     digit_index++ )
			{
				utf32_string[ safe_utf32_string_index++ ] = (uint32_t) '0' + (uint32_t) ( value_fraction / divider );

				if( digit_index == 0 )
				{
					utf32_string[ safe_utf32_string_index++ ] = (uint32_t) '.';
				}
				value_fraction %= divider;
				divider        /= 10;
			}
			utf32_string[ safe_utf32_string_index++ ] = (uint32_t) 'e';
			utf32_string[ safe_utf32_string_index++ ] = exponent_sign;

			divider = 100;

			for( digit_index = 0;
			     digit_index < 3;
			     digit_index++ )
			{
				utf32_string[ safe_utf32_string_index++ ] = (uint32_t) '0' + (uint32_t) ( exponent10 / divider );

				exponent10 %= divider;
				divider    /= 10;
			}
		}
	}
	utf32_string[ safe_utf32_string_index++ ] = 0;

	*utf32_string_index = safe_utf32_string_index;

	return( 1 );
}

/* Copies an UTF-32 encoded string to a floating point value
 * The floating_point value size is in bits
 * Returns 1 if successful or -1 on error
 */
int libfvalue_utf32_string_with_index_copy_to_floating_point(
     uint32_t *utf32_string,
     size_t utf32_string_length,
     size_t *utf32_string_index,
     uint64_t *floating_point_value,
     size_t floating_point_value_size,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	byte_stream_float64_t value_float64;

	static char *function          = "libfvalue_utf32_string_with_index_copy_to_floating_point";
	size_t fraction_index          = 0;
	size_t maximum_string_index    = 0;
	size_t safe_utf32_string_index = 0;
	uint64_t divider               = 0;
	uint64_t value_64bit           = 0;
	uint32_t string_format_type    = 0;
	uint32_t supported_flags       = 0;
	uint8_t byte_value             = 0;
	uint8_t character_value        = 0;
	int8_t bit_shift               = 0;
	int8_t sign                    = 1;
	double value_fraction          = 0.0;

	if( utf32_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string.",
		 function );

		return( -1 );
	}
	if( utf32_string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf32_string_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-32 string index.",
		 function );

		return( -1 );
	}
	if( *utf32_string_index >= utf32_string_length )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-32 string index value out of bounds.",
		 function );

		return( -1 );
	}
	safe_utf32_string_index = *utf32_string_index;

	if( floating_point_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid floating point value.",
		 function );

		return( -1 );
	}
	if( ( floating_point_value_size != 32 )
	 && ( floating_point_value_size != 64 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported floating point value size.",
		 function );

		return( -1 );
	}
	supported_flags = 0x000000ffUL;

	if( ( string_format_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format flags: 0x%08" PRIx32 ".",
		 function,
		 string_format_flags );

		return( -1 );
	}
	string_format_type = string_format_flags & 0x000000ffUL;

	if( ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_DECIMAL )
	 && ( string_format_type != LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported string format type.",
		 function );

		return( -1 );
	}
	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		maximum_string_index = (size_t) ( floating_point_value_size >> 2 ) + 3;
	}
	else
	{
		/* The string is at least a single digit with an end of string character
		 */
		maximum_string_index = 2;

		bit_shift = (uint8_t) ( floating_point_value_size - 1 );

		divider = 1;

		value_64bit = ~( ( ~( (uint64_t) 1 << bit_shift ) >> bit_shift ) << bit_shift );

		while( ( value_64bit / divider ) >= 10 )
		{
			divider *= 10;

			maximum_string_index += 1;
		}
	}
	maximum_string_index += safe_utf32_string_index;

	if( maximum_string_index > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid maximum string index value exceeds maximum.",
		 function );

		return( -1 );
	}
	value_64bit = 0;

	if( string_format_type == LIBFVALUE_FLOATING_POINT_FORMAT_TYPE_HEXADECIMAL )
	{
		character_value = utf32_string[ safe_utf32_string_index++ ];

		if(character_value != (uint32_t) '0' )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: 0x%02" PRIx32 " at index: %d.",
			 function,
			 character_value,
			 safe_utf32_string_index );

			return( -1 );
		}
		character_value = utf32_string[ safe_utf32_string_index++ ];

		if( character_value != (uint32_t) 'x' )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: 0x%02" PRIx32 " at index: %d.",
			 function,
			 character_value,
			 safe_utf32_string_index );

			return( -1 );
		}
		while( safe_utf32_string_index < utf32_string_length )
		{
			character_value = utf32_string[ safe_utf32_string_index ];

			if( character_value == 0 )
			{
				break;
			}
			if( safe_utf32_string_index > (size_t) maximum_string_index )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
				 "%s: string too large.",
				 function );

				return( -1 );
			}
			value_64bit <<= 4;

			if( ( character_value >= (uint32_t) '0' )
			 && ( character_value <= (uint32_t) '9' ) )
			{
				byte_value = (uint8_t) ( character_value - (uint32_t) '0' );
			}
			else if( ( character_value >= (uint32_t) 'A' )
			      && ( character_value <= (uint32_t) 'F' ) )
			{
				byte_value = (uint8_t) ( character_value - (uint32_t) 'A' + 10 );
			}
			else if( ( character_value >= (uint32_t) 'a' )
			      && ( character_value <= (uint32_t) 'f' ) )
			{
				byte_value = (uint8_t) ( character_value - (uint32_t) 'a' + 10 );
			}
			else
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported character value: 0x08%" PRIx32 " at index: %d.",
				 function,
				 character_value,
				 safe_utf32_string_index );

				return( -1 );
			}
			value_64bit += byte_value;

			safe_utf32_string_index++;
		}
	}
	else
	{
		value_float64.floating_point = 0.0;

		character_value = utf32_string[ safe_utf32_string_index ];

		/* In the maximum possible string one character is substituted for the sign
		 */
		if( character_value == (uint32_t) '-' )
		{
			safe_utf32_string_index++;

			sign = -1;
		}
		else if( character_value == (uint32_t) '+' )
		{
			safe_utf32_string_index++;
		}
		while( safe_utf32_string_index < utf32_string_length )
		{
			character_value = utf32_string[ safe_utf32_string_index ];

			if( character_value == 0 )
			{
				break;
			}
			if( safe_utf32_string_index > (size_t) maximum_string_index )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
				 "%s: string too large.",
				 function );

				return( -1 );
			}
			if( character_value == (uint32_t) '.' )
			{
				break;
			}
			if( ( character_value < (uint32_t) '0' )
			 || ( character_value > (uint32_t) '9' ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported character value: 0x%02" PRIx32 " at index: %d.",
				 function,
				 character_value,
				 safe_utf32_string_index );

				return( -1 );
			}
			value_float64.floating_point *= 10;
			value_float64.floating_point += character_value - (uint32_t) '0';

			safe_utf32_string_index++;
		}
		fraction_index = safe_utf32_string_index;

		safe_utf32_string_index++;
		utf32_string_length--;

		if( utf32_string_length > (size_t) maximum_string_index )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
			 "%s: string too large.",
			 function );

			return( -1 );
		}
		while( fraction_index < utf32_string_length )
		{
			character_value = utf32_string[ utf32_string_length ];

			if( character_value == 0 )
			{
				break;
			}
			if( ( character_value < (uint32_t) '0' )
			 || ( character_value > (uint32_t) '9' ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported character value: 0x%02" PRIx32 " at index: %d.",
				 function,
				 character_value,
				 utf32_string_length );

				return( -1 );
			}
			value_fraction /= 10;
			value_fraction += character_value - (uint32_t) '0';

			safe_utf32_string_index++;
			utf32_string_length--;
		}
		if( value_fraction != 0.0 )
		{
			value_float64.floating_point += value_fraction / 10;
		}
		if( sign == -1 )
		{
			value_float64.floating_point *= 1.0;
		}
		value_64bit = value_float64.integer;
	}
	*utf32_string_index   = safe_utf32_string_index;
	*floating_point_value = value_64bit;

	return( 1 );
}

