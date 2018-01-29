/*
 * Windows Serialized Property Value functions
 *
 * Copyright (C) 2013-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libfwps_definitions.h"
#include "libfwps_libcerror.h"
#include "libfwps_libcnotify.h"
#include "libfwps_libfole.h"
#include "libfwps_libuna.h"
#include "libfwps_types.h"
#include "libfwps_value.h"

/* Creates a value
 * Make sure the value value is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwps_value_initialize(
     libfwps_value_t **value,
     uint8_t value_type,
     libcerror_error_t **error )
{
	libfwps_internal_value_t *internal_value = NULL;
	static char *function                    = "libfwps_value_initialize";

	if( value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	if( *value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid value value already set.",
		 function );

		return( -1 );
	}
	if( ( value_type != LIBFWPS_VALUE_TYPE_NAMED )
	 && ( value_type != LIBFWPS_VALUE_TYPE_NUMERIC ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value type.",
		 function );

		return( -1 );
	}
	internal_value = memory_allocate_structure(
	                  libfwps_internal_value_t );

	if( internal_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create value.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_value,
	     0,
	     sizeof( libfwps_internal_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear value.",
		 function );

		goto on_error;
	}
	internal_value->type = value_type;

	*value = (libfwps_value_t *) internal_value;

	return( 1 );

on_error:
	if( internal_value != NULL )
	{
		memory_free(
		 internal_value );
	}
	return( -1 );
}

/* Frees a value
 * Returns 1 if successful or -1 on error
 */
int libfwps_value_free(
     libfwps_value_t **value,
     libcerror_error_t **error )
{
	static char *function = "libfwps_value_free";

	if( value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	if( *value != NULL )
	{
		*value = NULL;
	}
	return( 1 );
}

/* Frees a value
 * Returns 1 if successful or -1 on error
 */
int libfwps_internal_value_free(
     libfwps_internal_value_t **internal_value,
     libcerror_error_t **error )
{
	static char *function = "libfwps_internal_value_free";

	if( internal_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal value.",
		 function );

		return( -1 );
	}
	if( *internal_value != NULL )
	{
		memory_free(
		 *internal_value );

		*internal_value = NULL;
	}
	return( 1 );
}

/* Copies a serialized property value from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libfwps_value_copy_from_byte_stream(
     libfwps_value_t *value,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfwps_internal_value_t *internal_value = NULL;
	static char *function                    = "libfwps_value_copy_from_byte_stream";
	size_t byte_stream_offset                = 0;
	uint32_t name_size                       = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t *value_string         = NULL;
	size_t value_string_size                 = 0;
	uint32_t value_32bit                     = 0;
	int result                               = 0;
#endif

	if( value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	internal_value = (libfwps_internal_value_t *) value;

	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: byte stream size exceeds maximum.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 byte_stream,
	 internal_value->size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: property value data:\n",
		 function );
		libcnotify_print_data(
		 byte_stream,
		 internal_value->size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_value->size );
	}
#endif
	if( internal_value->size == 0 )
	{
		return( 1 );
	}
	if( ( internal_value->size < 4 )
	 && ( (size_t) internal_value->size > byte_stream_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid property value size value out of bounds.",
		 function );

		goto on_error;
	}
	byte_stream_offset += 4;

	if( internal_value->type == LIBFWPS_VALUE_TYPE_NAMED )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( byte_stream[ byte_stream_offset ] ),
		 name_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: name size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 name_size );
		}
#endif
	}
	else if( internal_value->type == LIBFWPS_VALUE_TYPE_NUMERIC )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 &( byte_stream[ byte_stream_offset ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: identifier\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );
		}
#endif
	}
	byte_stream_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%" PRIx8 "\n",
		 function,
		 byte_stream[ byte_stream_offset ] );
	}
#endif
	byte_stream_offset += 1;

	if( internal_value->type == LIBFWPS_VALUE_TYPE_NAMED )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  &( byte_stream[ byte_stream_offset ] ),
				  name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  &( byte_stream[ byte_stream_offset ] ),
				  name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine size of URI string.",
				 function );

				goto on_error;
			}
			if( ( value_string_size > (size_t) SSIZE_MAX )
			 || ( ( sizeof( system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid URI string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = system_string_allocate(
					value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create URI string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_utf16_stream(
				  (libuna_utf16_character_t *) value_string,
				  value_string_size,
				  &( byte_stream[ byte_stream_offset ] ),
				  name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  &( byte_stream[ byte_stream_offset ] ),
				  name_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set URI string.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: name\t\t\t\t: %" PRIs_SYSTEM "\n",
			 function,
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#endif
		byte_stream_offset += name_size;
	}

/* TODO read value */
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: value data:\n",
		 function );
		libcnotify_print_data(
		 &( byte_stream[ byte_stream_offset ] ),
		 internal_value->size - byte_stream_offset,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif

/* TODO print trailing data */

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
#endif
	return( -1 );
}

