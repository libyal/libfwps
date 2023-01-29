/*
 * Library to access the Windows Property Store format
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

#if !defined( _LIBFWPS_H )
#define _LIBFWPS_H

#include <libfwps/codepage.h>
#include <libfwps/definitions.h>
#include <libfwps/error.h>
#include <libfwps/extern.h>
#include <libfwps/features.h>
#include <libfwps/types.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBFWPS_EXTERN \
const char *libfwps_get_version(
             void );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBFWPS_EXTERN \
void libfwps_error_free(
      libfwps_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_error_fprint(
     libfwps_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_error_sprint(
     libfwps_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_error_backtrace_fprint(
     libfwps_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the amount of printed characters if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_error_backtrace_sprint(
     libfwps_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Format class identifier functions
 * ------------------------------------------------------------------------- */

/* Retrieves a string containing the identifier of the folder identifier
 */
LIBFWPS_EXTERN \
const char *libfwps_format_class_identifier_get_identifier(
             const uint8_t *format_class_identifier );

/* Retrieves a string containing the description of the folder identifier
 */
LIBFWPS_EXTERN \
const char *libfwps_format_class_identifier_get_description(
             const uint8_t *format_class_identifier );

/* -------------------------------------------------------------------------
 * Record functions
 * ------------------------------------------------------------------------- */

/* Frees a record
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_free(
     libfwps_record_t **record,
     libfwps_error_t **error );

/* Retrieves the entry type
 * Returns 1 if successful, 0 if not available or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_entry_type(
     libfwps_record_t *record,
     uint32_t *entry_type,
     libfwps_error_t **error );

/* Retrieves the value type
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_value_type(
     libfwps_record_t *record,
     uint32_t *value_type,
     libfwps_error_t **error );

/* Retrieves the data as a boolean value
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_boolean(
     libfwps_record_t *record,
     uint8_t *value_boolean,
     libfwps_error_t **error );

/* Retrieves the data as a 8-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_8bit_integer(
     libfwps_record_t *record,
     uint8_t *value_8bit,
     libfwps_error_t **error );

/* Retrieves the data as a 16-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_16bit_integer(
     libfwps_record_t *record,
     uint16_t *value_16bit,
     libfwps_error_t **error );

/* Retrieves the data as a 32-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_32bit_integer(
     libfwps_record_t *record,
     uint32_t *value_32bit,
     libfwps_error_t **error );

/* Retrieves the data as a 64-bit integer value
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_64bit_integer(
     libfwps_record_t *record,
     uint64_t *value_64bit,
     libfwps_error_t **error );

/* Retrieves the data as a 64-bit FILETIME value
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_filetime(
     libfwps_record_t *record,
     uint64_t *filetime,
     libfwps_error_t **error );

/* Retrieves the floating point value
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_floating_point(
     libfwps_record_t *record,
     double *value_floating_point,
     libfwps_error_t **error );

/* Retrieves the size of the data formatted as an UTF-8 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf8_string_size(
     libfwps_record_t *record,
     size_t *utf8_string_size,
     libfwps_error_t **error );

/* Retrieves the data formatted as an UTF-8 string
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf8_string(
     libfwps_record_t *record,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libfwps_error_t **error );

/* Retrieves the size of the data formatted as an UTF-16 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf16_string_size(
     libfwps_record_t *record,
     size_t *utf16_string_size,
     libfwps_error_t **error );

/* Retrieves the data formatted as an UTF-16 string
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_utf16_string(
     libfwps_record_t *record,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libfwps_error_t **error );

/* Retrieves the data as a GUID value
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_record_get_data_as_guid(
     libfwps_record_t *record,
     uint8_t *guid_data,
     size_t guid_data_size,
     libfwps_error_t **error );

/* -------------------------------------------------------------------------
 * Set functions
 * ------------------------------------------------------------------------- */

/* Creates a set
 * Make sure the value set is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_set_initialize(
     libfwps_set_t **set,
     libfwps_error_t **error );

/* Frees a set
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_set_free(
     libfwps_set_t **set,
     libfwps_error_t **error );

/* Copies a set from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_set_copy_from_byte_stream(
     libfwps_set_t *set,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libfwps_error_t **error );

/* Retrieves the identifier
 * The identifier is a little-endian GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_set_get_identifier(
     libfwps_set_t *set,
     uint8_t *guid_data,
     size_t guid_data_size,
     libfwps_error_t **error );

/* Retrieves the number of records
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_set_get_number_of_records(
     libfwps_set_t *set,
     int *number_of_records,
     libfwps_error_t **error );

/* Retrieves a specific record
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_set_get_record_by_index(
     libfwps_set_t *set,
     int record_index,
     libfwps_record_t **record,
     libfwps_error_t **error );

/* -------------------------------------------------------------------------
 * Storage functions
 * ------------------------------------------------------------------------- */

/* Creates a storage
 * Make sure the value storage is referencing, is set to NULL
 *
 * This function is deprecated use libfwps_set_initialize instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_DEPRECATED \
LIBFWPS_EXTERN \
int libfwps_storage_initialize(
     libfwps_storage_t **storage,
     libfwps_error_t **error );

/* Frees a storage
 *
 * This function is deprecated use libfwps_set_free instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_DEPRECATED \
LIBFWPS_EXTERN \
int libfwps_storage_free(
     libfwps_storage_t **storage,
     libfwps_error_t **error );

/* Copies a serialized property storage from a byte stream
 *
 * This function is deprecated use libfwps_set_copy_from_byte_stream instead
 *
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_DEPRECATED \
LIBFWPS_EXTERN \
int libfwps_storage_copy_from_byte_stream(
     libfwps_storage_t *storage,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libfwps_error_t **error );

/* -------------------------------------------------------------------------
 * Store functions
 * ------------------------------------------------------------------------- */

/* Creates a store
 * Make sure the value store is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_store_initialize(
     libfwps_store_t **store,
     libfwps_error_t **error );

/* Frees a store
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_store_free(
     libfwps_store_t **store,
     libfwps_error_t **error );

/* Copies a store from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_store_copy_from_byte_stream(
     libfwps_store_t *store,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libfwps_error_t **error );

/* Retrieves the number of sets
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_store_get_number_of_sets(
     libfwps_store_t *store,
     int *number_of_sets,
     libfwps_error_t **error );

/* Retrieves a specific set
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_store_get_set_by_index(
     libfwps_store_t *store,
     int set_index,
     libfwps_set_t **set,
     libfwps_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWPS_H ) */

