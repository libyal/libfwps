/*
 * Windows Serialized Property Record functions
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

#if !defined( _LIBFWPS_RECORD_H )
#define _LIBFWPS_RECORD_H

#include <common.h>
#include <types.h>

#include "libfwps_extern.h"
#include "libfwps_libcerror.h"
#include "libfwps_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfwps_internal_record libfwps_internal_record_t;

struct libfwps_internal_record
{
	/* The type
	 */
	uint8_t type;

	/* The size
	 */
	uint32_t size;

	/* The entry type
	 */
	uint32_t entry_type;

	/* The value type
	 */
	uint32_t value_type;
};

int libfwps_record_initialize(
     libfwps_record_t **record,
     uint8_t record_type,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_free(
     libfwps_record_t **record,
     libcerror_error_t **error );

int libfwps_internal_record_free(
     libfwps_internal_record_t **internal_record,
     libcerror_error_t **error );

int libfwps_record_copy_from_byte_stream(
     libfwps_record_t *record,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_identifier(
     libfwps_record_t *record,
     uint32_t *identifier,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWPS_RECORD_H ) */

