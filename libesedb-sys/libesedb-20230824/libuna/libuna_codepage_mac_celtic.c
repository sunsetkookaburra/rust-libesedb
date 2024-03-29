/*
 * MacCeltic codepage functions
 *
 * Copyright (C) 2008-2023, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#include "libuna_codepage_mac_celtic.h"
#include "libuna_libcerror.h"
#include "libuna_types.h"

/* Extended ASCII to Unicode character lookup table for the MacCeltic codepage
 * Unknown are filled with the Unicode replacement character 0xfffd
 */
const uint16_t libuna_codepage_mac_celtic_byte_stream_to_unicode_base_0x80[ 128 ] = {
	0x00c4, 0x00c5, 0x00c7, 0x00c9, 0x00d1, 0x00d6, 0x00dc, 0x00e1,
	0x00e0, 0x00e2, 0x00e4, 0x00e3, 0x00e5, 0x00e7, 0x00e9, 0x00e8,
	0x00ea, 0x00eb, 0x00ed, 0x00ec, 0x00ee, 0x00ef, 0x00f1, 0x00f3,
	0x00f2, 0x00f4, 0x00f6, 0x00f5, 0x00fa, 0x00f9, 0x00fb, 0x00fc,
	0x2020, 0x00b0, 0x00a2, 0x00a3, 0x00a7, 0x2022, 0x00b6, 0x00df,
	0x00ae, 0x00a9, 0x2122, 0x00b4, 0x00a8, 0x2260, 0x00c6, 0x00d8,
	0x221e, 0x00b1, 0x2264, 0x2265, 0x00a5, 0x00b5, 0x2202, 0x2211,
	0x220f, 0x03c0, 0x222b, 0x00aa, 0x00ba, 0x03a9, 0x00e6, 0x00f8,
	0x00bf, 0x00a1, 0x00ac, 0x221a, 0x0192, 0x2248, 0x2206, 0x00ab,
	0x00bb, 0x2026, 0x00a0, 0x00c0, 0x00c3, 0x00d5, 0x0152, 0x0153,
	0x2013, 0x2014, 0x201c, 0x201d, 0x2018, 0x2019, 0x00f7, 0x25ca,
	0x00ff, 0x0178, 0x2044, 0x20ac, 0x2039, 0x203a, 0x0176, 0x0177,
	0x2021, 0x00b7, 0x1ef2, 0x1ef3, 0x2030, 0x00c2, 0x00ca, 0x00c1,
	0x00cb, 0x00c8, 0x00cd, 0x00ce, 0x00cf, 0x00cc, 0x00d3, 0x00d4,
	0x2663, 0x00d2, 0x00da, 0x00db, 0x00d9, 0x0131, 0x00dd, 0x00fd,
	0x0174, 0x0175, 0x1e84, 0x1e85, 0x1e80, 0x1e81, 0x1e82, 0x1e83
};

/* Unicode to ASCII character lookup tables for the MacCeltic codepage
 * Unknown are filled with the ASCII replacement character 0x1a
 */
const uint8_t libuna_codepage_mac_celtic_unicode_to_byte_stream_base_0x00a0[ 96 ] = {
	0xca, 0xc1, 0xa2, 0xa3, 0x1a, 0xb4, 0x1a, 0xa4,
	0xac, 0xa9, 0xbb, 0xc7, 0xc2, 0x1a, 0xa8, 0x1a,
	0xa1, 0xb1, 0x1a, 0x1a, 0xab, 0xb5, 0xa6, 0xe1,
	0x1a, 0x1a, 0xbc, 0xc8, 0x1a, 0x1a, 0x1a, 0xc0,
	0xcb, 0xe7, 0xe5, 0xcc, 0x80, 0x81, 0xae, 0x82,
	0xe9, 0x83, 0xe6, 0xe8, 0xed, 0xea, 0xeb, 0xec,
	0x1a, 0x84, 0xf1, 0xee, 0xef, 0xcd, 0x85, 0x1a,
	0xaf, 0xf4, 0xf2, 0xf3, 0x86, 0xf6, 0x1a, 0xa7,
	0x88, 0x87, 0x89, 0x8b, 0x8a, 0x8c, 0xbe, 0x8d,
	0x8f, 0x8e, 0x90, 0x91, 0x93, 0x92, 0x94, 0x95,
	0x1a, 0x96, 0x98, 0x97, 0x99, 0x9b, 0x9a, 0xd6,
	0xbf, 0x9d, 0x9c, 0x9e, 0x9f, 0xf7, 0x1a, 0xd8
};

const uint8_t libuna_codepage_mac_celtic_unicode_to_byte_stream_base_0x2010[ 56 ] = {
	0x1a, 0x1a, 0x1a, 0xd0, 0xd1, 0x1a, 0x1a, 0x1a,
	0xd4, 0xd5, 0x1a, 0x1a, 0xd2, 0xd3, 0x1a, 0x1a,
	0xa0, 0xe0, 0xa5, 0x1a, 0x1a, 0x1a, 0xc9, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0xe4, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0xdc, 0xdd, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0xda, 0x1a, 0x1a, 0x1a
};

/* Copies an Unicode character from a MacCeltic encoded byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_codepage_mac_celtic_copy_from_byte_stream(
     libuna_unicode_character_t *unicode_character,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     libcerror_error_t **error )
{
	static char *function                             = "libuna_codepage_mac_celtic_copy_from_byte_stream";
	libuna_unicode_character_t safe_unicode_character = 0xfffd;
	size_t safe_byte_stream_index                     = 0;
	uint8_t byte_stream_character                     = 0;

	if( unicode_character == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid Unicode character.",
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
	if( byte_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream index.",
		 function );

		return( -1 );
	}
	safe_byte_stream_index = *byte_stream_index;

	if( safe_byte_stream_index >= byte_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	byte_stream_character = byte_stream[ safe_byte_stream_index++ ];

	if( byte_stream_character < 0x80 )
	{
		safe_unicode_character = byte_stream_character;
	}
	else
	{
		byte_stream_character -= 0x80;

		safe_unicode_character = libuna_codepage_mac_celtic_byte_stream_to_unicode_base_0x80[ byte_stream_character ];
	}
	*unicode_character = safe_unicode_character;
	*byte_stream_index = safe_byte_stream_index;

	return( 1 );
}

/* Copies an Unicode character to a MacCeltic encoded byte stream
 * Returns 1 if successful or -1 on error
 */
int libuna_codepage_mac_celtic_copy_to_byte_stream(
     libuna_unicode_character_t unicode_character,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     size_t *byte_stream_index,
     libcerror_error_t **error )
{
	static char *function         = "libuna_codepage_mac_celtic_copy_to_byte_stream";
	size_t safe_byte_stream_index = 0;
	uint16_t byte_stream_value    = 0x001a;

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
	if( byte_stream_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream index.",
		 function );

		return( -1 );
	}
	safe_byte_stream_index = *byte_stream_index;

	if( safe_byte_stream_index >= byte_stream_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	if( unicode_character < 0x0080 )
	{
		byte_stream_value = (uint16_t) unicode_character;
	}
	else if( ( unicode_character >= 0x00a0 )
	      && ( unicode_character < 0x0100 ) )
	{
		unicode_character -= 0x00a0;

		byte_stream_value = libuna_codepage_mac_celtic_unicode_to_byte_stream_base_0x00a0[ unicode_character ];
	}
	else if( ( unicode_character >= 0x2010 )
	      && ( unicode_character < 0x2048 ) )
	{
		unicode_character -= 0x2010;

		byte_stream_value = libuna_codepage_mac_celtic_unicode_to_byte_stream_base_0x2010[ unicode_character ];
	}
	else switch( unicode_character )
	{
		case 0x0131:
			byte_stream_value = 0xf5;
			break;

		case 0x0152:
			byte_stream_value = 0xce;
			break;

		case 0x0153:
			byte_stream_value = 0xcf;
			break;

		case 0x0174:
			byte_stream_value = 0xf8;
			break;

		case 0x0175:
			byte_stream_value = 0xf9;
			break;

		case 0x0176:
			byte_stream_value = 0xde;
			break;

		case 0x0177:
			byte_stream_value = 0xdf;
			break;

		case 0x0178:
			byte_stream_value = 0xd9;
			break;

		case 0x0192:
			byte_stream_value = 0xc4;
			break;

		case 0x03a9:
			byte_stream_value = 0xbd;
			break;

		case 0x03c0:
			byte_stream_value = 0xb9;
			break;

		case 0x1e80:
			byte_stream_value = 0xfc;
			break;

		case 0x1e81:
			byte_stream_value = 0xfd;
			break;

		case 0x1e82:
			byte_stream_value = 0xfe;
			break;

		case 0x1e83:
			byte_stream_value = 0xff;
			break;

		case 0x1e84:
			byte_stream_value = 0xfa;
			break;

		case 0x1e85:
			byte_stream_value = 0xfb;
			break;

		case 0x1ef2:
			byte_stream_value = 0xe2;
			break;

		case 0x1ef3:
			byte_stream_value = 0xe3;
			break;

		case 0x20ac:
			byte_stream_value = 0xdb;
			break;

		case 0x2122:
			byte_stream_value = 0xaa;
			break;

		case 0x2202:
			byte_stream_value = 0xb6;
			break;

		case 0x2206:
			byte_stream_value = 0xc6;
			break;

		case 0x220f:
			byte_stream_value = 0xb8;
			break;

		case 0x2211:
			byte_stream_value = 0xb7;
			break;

		case 0x221a:
			byte_stream_value = 0xc3;
			break;

		case 0x221e:
			byte_stream_value = 0xb0;
			break;

		case 0x222b:
			byte_stream_value = 0xba;
			break;

		case 0x2248:
			byte_stream_value = 0xc5;
			break;

		case 0x2260:
			byte_stream_value = 0xad;
			break;

		case 0x2264:
			byte_stream_value = 0xb2;
			break;

		case 0x2265:
			byte_stream_value = 0xb3;
			break;

		case 0x25ca:
			byte_stream_value = 0xd7;
			break;

		case 0x2663:
			byte_stream_value = 0xf0;
			break;

		default:
			byte_stream_value = 0x1a;
			break;
	}
	byte_stream[ safe_byte_stream_index++ ] = (uint8_t) ( byte_stream_value & 0x00ff );

	*byte_stream_index = safe_byte_stream_index;

	return( 1 );
}

