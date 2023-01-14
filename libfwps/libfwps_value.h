/*
 * Windows Serialized Property Value functions
 *
 * Copyright (C) 2013-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFWPS_INTERNAL_VALUE_H )
#define _LIBFWPS_INTERNAL_VALUE_H

#include <common.h>
#include <types.h>

#include "libfwps_extern.h"
#include "libfwps_libcerror.h"
#include "libfwps_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwps_internal_value libfwps_internal_value_t;

struct libfwps_internal_value
{
	/* The type
	 */
	uint8_t type;

	/* The size
	 */
	uint32_t size;
};

int libfwps_value_initialize(
     libfwps_value_t **value,
     uint8_t value_type,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_value_free(
     libfwps_value_t **value,
     libcerror_error_t **error );

int libfwps_internal_value_free(
     libfwps_internal_value_t **internal_value,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_value_copy_from_byte_stream(
     libfwps_value_t *value,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWPS_INTERNAL_VALUE_H ) */

