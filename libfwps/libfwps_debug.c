/*
 * Debug functions
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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfwps_debug.h"
#include "libfwps_libcerror.h"
#include "libfwps_libcnotify.h"
#include "libfwps_libuna.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints an UTF-16 string value
 * Returns 1 if successful or -1 on error
 */
int libfwps_debug_print_utf16_string_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	system_character_t *string = NULL;
	static char *function      = "libfwps_debug_print_utf16_string_value";
	size_t string_size         = 0;
	int result                 = 0;

	if( ( byte_stream == NULL )
	 || ( byte_stream_size == 0 ) )
	{
		libcnotify_printf(
		 "%s: %s:\n",
		 function_name,
		 value_name );

		return( 1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_size_from_utf16_stream(
	          byte_stream,
	          byte_stream_size,
	          byte_order,
	          &string_size,
	          error );
#else
	result = libuna_utf8_string_size_from_utf16_stream(
	          byte_stream,
	          byte_stream_size,
	          byte_order,
	          &string_size,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of string.",
		 function );

		goto on_error;
	}
	if( string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s:",
	 function_name,
	 value_name );

	if( string_size > 0 )
	{
		string = system_string_allocate(
		          string_size );

		if( string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libuna_utf16_string_copy_from_utf16_stream(
		          (libuna_utf16_character_t *) string,
		          string_size,
		          byte_stream,
		          byte_stream_size,
		          byte_order,
		          error );
#else
		result = libuna_utf8_string_copy_from_utf16_stream(
		          (libuna_utf8_character_t *) string,
		          string_size,
		          byte_stream,
		          byte_stream_size,
		          byte_order,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 " %s",
		 string );

		memory_free(
		 string );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );

on_error:
	if( string != NULL )
	{
		memory_free(
		 string );
	}
	return( -1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

