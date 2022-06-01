/*
 * Database functions
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

#if !defined( _LIBMAPIDB_INTERNAL_DATABASE_H )
#define _LIBMAPIDB_INTERNAL_DATABASE_H

#include <common.h>
#include <types.h>

#include "libmapidb_extern.h"
#include "libmapidb_libcerror.h"
#include "libmapidb_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libmapidb_internal_database libmapidb_internal_database_t;

struct libmapidb_internal_database
{
	/* Dummy
	 */
	int dummy;
};

LIBMAPIDB_EXTERN \
int libmapidb_database_initialize(
     libmapidb_database_t **database,
     libcerror_error_t **error );

LIBMAPIDB_EXTERN \
int libmapidb_database_free(
     libmapidb_database_t **database,
     libcerror_error_t **error );

LIBMAPIDB_EXTERN \
int libmapidb_database_get_root_folder(
     libmapidb_database_t *database,
     libmapidb_folder_t **root_folder,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBMAPIDB_INTERNAL_DATABASE_H ) */

