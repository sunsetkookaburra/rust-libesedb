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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libmapidb_database.h"
#include "libmapidb_definitions.h"
#include "libmapidb_libcerror.h"
#include "libmapidb_types.h"

/* Creates a database
 * Make sure the value database is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libmapidb_database_initialize(
     libmapidb_database_t **database,
     libcerror_error_t **error )
{
	libmapidb_internal_database_t *internal_database = NULL;
	static char *function                            = "libmapidb_database_initialize";

	if( database == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid database.",
		 function );

		return( -1 );
	}
	if( *database != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid database value already set.",
		 function );

		return( -1 );
	}
	internal_database = memory_allocate_structure(
	                     libmapidb_internal_database_t );

	if( internal_database == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create database.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_database,
	     0,
	     sizeof( libmapidb_internal_database_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear database.",
		 function );

		goto on_error;
	}
	*database = (libmapidb_database_t *) internal_database;

	return( 1 );

on_error:
	if( internal_database != NULL )
	{
		memory_free(
		 internal_database );
	}
	return( -1 );
}

/* Frees a database
 * Returns 1 if successful or -1 on error
 */
int libmapidb_database_free(
     libmapidb_database_t **database,
     libcerror_error_t **error )
{
	libmapidb_internal_database_t *internal_database = NULL;
	static char *function                            = "libmapidb_database_free";

	if( database == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid database.",
		 function );

		return( -1 );
	}
	if( *database != NULL )
	{
		internal_database = (libmapidb_internal_database_t *) *database;
		*database         = NULL;

		memory_free(
		 internal_database );
	}
	return( 1 );
}

