/*
 * Windows Serialized Property Record functions
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

	/* The entry name
	 */
	uint8_t *entry_name;

	/* The entry name size
	 */
	uint32_t entry_name_size;

	/* The entry type
	 */
	uint32_t entry_type;

	/* The value name
	 */
	uint8_t *value_name;

	/* The value name size
	 */
	uint32_t value_name_size;

	/* The value type
	 */
	uint32_t value_type;

	/* The value data
	 */
	uint8_t *value_data;

	/* The value data size
	 */
	size_t value_data_size;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;
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
int libfwps_record_get_utf8_entry_name_size(
     libfwps_record_t *record,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_utf8_entry_name(
     libfwps_record_t *record,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_utf16_entry_name_size(
     libfwps_record_t *record,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_utf16_entry_name(
     libfwps_record_t *record,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_entry_type(
     libfwps_record_t *record,
     uint32_t *entry_type,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_utf8_value_name_size(
     libfwps_record_t *record,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_utf8_value_name(
     libfwps_record_t *record,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_utf16_value_name_size(
     libfwps_record_t *record,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_utf16_value_name(
     libfwps_record_t *record,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_value_type(
     libfwps_record_t *record,
     uint32_t *value_type,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_size(
     libfwps_record_t *record,
     size_t *data_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data(
     libfwps_record_t *record,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_boolean(
     libfwps_record_t *record,
     uint8_t *value_boolean,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_8bit_integer(
     libfwps_record_t *record,
     uint8_t *value_8bit,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_16bit_integer(
     libfwps_record_t *record,
     uint16_t *value_16bit,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_32bit_integer(
     libfwps_record_t *record,
     uint32_t *value_32bit,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_64bit_integer(
     libfwps_record_t *record,
     uint64_t *value_64bit,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_filetime(
     libfwps_record_t *record,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_floating_point(
     libfwps_record_t *record,
     double *value_floating_point,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf8_string_size(
     libfwps_record_t *record,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf8_string(
     libfwps_record_t *record,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf16_string_size(
     libfwps_record_t *record,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf16_string(
     libfwps_record_t *record,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf8_path_string_size(
     libfwps_record_t *record,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf8_path_string(
     libfwps_record_t *record,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf16_path_string_size(
     libfwps_record_t *record,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf16_path_string(
     libfwps_record_t *record,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBFWPS_EXTERN \
int libfwps_record_get_data_as_guid(
     libfwps_record_t *record,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWPS_RECORD_H ) */

