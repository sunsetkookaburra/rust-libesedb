/*
 * The internal extern definition
 *
 * Copyright (C) 2010-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFCACHE_INTERNAL_EXTERN_H )
#define _LIBFCACHE_INTERNAL_EXTERN_H

#include <common.h>

/* Define HAVE_LOCAL_LIBFCACHE for local use of libfcache
 */
#if !defined( HAVE_LOCAL_LIBFCACHE )

#include <libfcache/extern.h>

#if defined( __CYGWIN__ ) || defined( __MINGW32__ )
#define LIBFCACHE_EXTERN_VARIABLE	extern
#else
#define LIBFCACHE_EXTERN_VARIABLE	LIBFCACHE_EXTERN
#endif

#else
#define LIBFCACHE_EXTERN		/* extern */
#define LIBFCACHE_EXTERN_VARIABLE	extern

#endif /* !defined( HAVE_LOCAL_LIBFCACHE ) */

#endif /* !defined( _LIBFCACHE_INTERNAL_EXTERN_H ) */

