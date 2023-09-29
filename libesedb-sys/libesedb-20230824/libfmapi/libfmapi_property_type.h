/*
 * Property type functions
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

#if !defined( _LIBFMAPI_PROPERTY_TYPE_H )
#define _LIBFMAPI_PROPERTY_TYPE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_DEBUG_OUTPUT )

typedef struct libfmapi_property_type libfmapi_property_type_t;

struct libfmapi_property_type
{
	/* The entry type
	 */
	uint32_t entry_type;

	/* The value type
	 */
	uint32_t value_type;

	/* The identifier
	 */
	const char *identifier;

	/* The description
	 */
	const char *description;
};

typedef struct libfmapi_named_property_type libfmapi_named_property_type_t;

struct libfmapi_named_property_type
{
	/* The name size
	 */
	size_t name_size;

	/* The name
	 */
	const char *name;

	/* The value type
	 */
	uint32_t value_type;

	/* The identifier
	 */
	const char *identifier;

	/* The description
	 */
	const char *description;
};

const char *libfmapi_property_types_get_identifier(
             libfmapi_property_type_t libfmapi_property_types[],
             uint32_t entry_type,
             uint32_t value_type );

const char *libfmapi_property_type_get_identifier(
             uint8_t *class_identifier,
             uint32_t entry_type,
             uint32_t value_type );

const char *libfmapi_property_types_get_description(
             libfmapi_property_type_t libfmapi_property_types[],
             uint32_t entry_type,
             uint32_t value_type );

const char *libfmapi_property_type_get_description(
             uint8_t *class_identifier,
             uint32_t entry_type,
             uint32_t value_type );

const char *libfmapi_named_property_types_get_identifier(
             libfmapi_named_property_type_t libfmapi_named_property_types[],
             const char *name,
             size_t name_size,
             uint32_t value_type );

const char *libfmapi_named_property_type_get_identifier(
             uint8_t *class_identifier,
             const char *name,
             size_t name_size,
             uint32_t value_type );

const char *libfmapi_named_property_types_get_description(
             libfmapi_named_property_type_t libfmapi_named_property_types[],
             const char *name,
             size_t name_size,
             uint32_t value_type );

const char *libfmapi_named_property_type_get_description(
             uint8_t *class_identifier,
             const char *name,
             size_t name_size,
             uint32_t value_type );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFMAPI_PROPERTY_TYPE_H ) */

