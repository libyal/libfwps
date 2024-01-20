/*
 * Windows Serialized Property Set functions
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

#if !defined( _LIBFWPS_SET_H )
#define _LIBFWPS_SET_H

#include <common.h>
#include <types.h>

#include "libfwps_extern.h"
#include "libfwps_libcdata.h"
#include "libfwps_libcerror.h"
#include "libfwps_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwps_internal_set libfwps_internal_set_t;

struct libfwps_internal_set
{
	/* The size
	 */
	uint32_t size;

	/* The identifier
	 */
	uint8_t identifier[ 16 ];

	/* The records array
	 */
	libcdata_array_t *records_array;

	/* Value to indicate if the set is managed by a store
	 */
	uint8_t is_managed;
};

LIBFWPS_EXTERN \
int libfwps_set_initialize(
     libfwps_set_t **set,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_set_free(
     libfwps_set_t **set,
     libcerror_error_t **error );

int libfwps_internal_set_free(
     libfwps_internal_set_t **internal_set,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_set_copy_from_byte_stream(
     libfwps_set_t *set,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_set_get_identifier(
     libfwps_set_t *set,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_set_get_number_of_records(
     libfwps_set_t *set,
     int *number_of_records,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_set_get_record_by_index(
     libfwps_set_t *set,
     int record_index,
     libfwps_record_t **record,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWPS_SET_H ) */

