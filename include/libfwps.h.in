/*
 * Library to access the Windows Property Store format
 *
 * Copyright (C) 2013-2022, Joachim Metz <joachim.metz@gmail.com>
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
 * Storage functions
 * ------------------------------------------------------------------------- */

/* Creates a storage
 * Make sure the value storage is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_storage_initialize(
     libfwps_storage_t **storage,
     libfwps_error_t **error );

/* Frees a storage
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_storage_free(
     libfwps_storage_t **storage,
     libfwps_error_t **error );

/* Copies a serialized property storage from a byte stream
 * Returns 1 if successful or -1 on error
 */
LIBFWPS_EXTERN \
int libfwps_storage_copy_from_byte_stream(
     libfwps_storage_t *storage,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libfwps_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWPS_H ) */

