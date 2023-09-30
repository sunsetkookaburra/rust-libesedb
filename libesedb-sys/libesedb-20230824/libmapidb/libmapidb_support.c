/*
 * Support functions
 *
 * Copyright (C) 2011-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#include <stdio.h>

#include "libmapidb_definitions.h"
#include "libmapidb_libcerror.h"
#include "libmapidb_support.h"

#if !defined( HAVE_LOCAL_LIBMAPIDB )

/* Returns the library version as a string
 */
const char *libmapidb_get_version(
             void )
{
	return( (const char *) LIBMAPIDB_VERSION_STRING );
}

#endif

