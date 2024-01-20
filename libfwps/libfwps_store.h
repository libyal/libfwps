/*
 * Windows Serialized Property Store functions
 *
 * Copyright (C) 2013-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFWPS_STORE_H )
#define _LIBFWPS_STORE_H

#include <common.h>
#include <types.h>

#include "libfwps_extern.h"
#include "libfwps_libcdata.h"
#include "libfwps_libcerror.h"
#include "libfwps_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwps_internal_store libfwps_internal_store_t;

struct libfwps_internal_store
{
	/* The size
	 */
	uint32_t size;

	/* The sets array
	 */
	libcdata_array_t *sets_array;
};

LIBFWPS_EXTERN \
int libfwps_store_initialize(
     libfwps_store_t **store,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_store_free(
     libfwps_store_t **store,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_store_copy_from_byte_stream(
     libfwps_store_t *store,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_store_get_number_of_sets(
     libfwps_store_t *store,
     int *number_of_sets,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_store_get_set_by_index(
     libfwps_store_t *store,
     int set_index,
     libfwps_set_t **set,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWPS_STORE_H ) */

