/*
 * Value type functions
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
#include <types.h>

#include "libfmapi_value_type.h"

#if defined( HAVE_DEBUG_OUTPUT )

libfmapi_value_type_t libfmapi_value_types[ ] = {
	{ 0x0000, "PtypUnspecified",		"Unspecified" },
	{ 0x0001, "PtypNull",			"NULL" },
	{ 0x0002, "PtypInteger16",		"Integer 16-bit signed" },
	{ 0x0003, "PtypInteger32",		"Integer 32-bit signed" },
	{ 0x0004, "PtypFloating32",		"Floating point single precision (32-bit)" },
	{ 0x0005, "PtypFloating64",		"Floating point double precision (64-bit)" },
	{ 0x0006, "PtypCurrency",		"Currency (64-bit)" },
	{ 0x0007, "PtypFloatingTime",		"Floating time (64-bit)" },
	{ 0x000a, "PtypErrorCode",		"Error value (32-bit)" },
	{ 0x000b, "PtypBoolean",		"Boolean" },
	{ 0x000d, "PtypObject",			"Embedded object" },
	{ 0x0014, "PtypInteger64",		"Integer 64-bit signed" },
	{ 0x001e, "PtypString8",		"Extended ASCII string" },
	{ 0x001f, "PtypString",			"UTF-16 Unicode string" },
	{ 0x0040, "PtypTime",			"Windows Filetime (64-bit)" },
	{ 0x0048, "PtypGuid",			"GUID (128-bit)" },
	{ 0x00fb, "PtypServerId",		"Server identifier" },
	{ 0x00fd, "PtypRestriction",		"Restriction" },
	{ 0x00fe, "PtypRuleAction",		"Rule actions" },
	{ 0x0102, "PtypBinary",			"Binary data" },

	{ 0x1002, "PtypMultipleInteger16",	"Array of Integer 16-bit signed values" },
	{ 0x1003, "PtypMultipleInteger32",	"Array of Integer 32-bit signed values" },
	{ 0x1004, "PtypMultipleFloating32",	"Array of Floating point single precision (32-bit) values" },
	{ 0x1005, "PtypMultipleFloating64",	"Array of Floating point double precision (64-bit) values" },
	{ 0x1006, "PtypMultipleCurrency",	"Array of Currency (64-bit) values" },
	{ 0x1007, "PtypMultipleFloatingTime",	"Array of Floating time (64-bit) values" },
	{ 0x1014, "PtypMultipleInteger64",	"Array of Integer 64-bit signed values" },
	{ 0x101e, "PtypMultipleString8",	"Array of Extended ASCII string values" },
	{ 0x101f, "PtypMultipleString",		"Array of UTF-16 Unicode string values" },
	{ 0x1040, "PtypMultipleTime",		"Array of Windows Filetime (64-bit) values" },
	{ 0x1048, "PtypMultipleGuid",		"Array of GUID (128-bit) values" },
	{ 0x1102, "PtypMultipleBinary",		"Array of Binary data values" },

	{ (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* Retrieves a string containing the value type identifier
 */
const char *libfmapi_value_type_get_identifier(
             uint32_t value_type )
{
	int iterator = 0;

	while( ( libfmapi_value_types[ iterator ] ).value_type != (uint32_t) -1 )
	{
		if( ( libfmapi_value_types[ iterator ] ).value_type == value_type )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfmapi_value_types[ iterator ] ).identifier );
}

/* Retrieves a string containing the value type description
 */
const char *libfmapi_value_type_get_description(
             uint32_t value_type )
{
	int iterator = 0;

	while( ( libfmapi_value_types[ iterator ] ).value_type != (uint32_t) -1 )
	{
		if( ( libfmapi_value_types[ iterator ] ).value_type == value_type )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfmapi_value_types[ iterator ] ).description );
}

#endif

