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
#include "libfwps_record.h"
#include "libfwps_types.h"

/* Creates a record
 * Make sure the record value is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_initialize(
     libfwps_record_t **record,
     uint8_t record_type,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_initialize";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record.",
		 function );

		return( -1 );
	}
	if( *record != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid record value already set.",
		 function );

		return( -1 );
	}
	if( ( record_type != LIBFWPS_RECORD_TYPE_NAMED )
	 && ( record_type != LIBFWPS_RECORD_TYPE_NUMERIC ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported record type.",
		 function );

		return( -1 );
	}
	internal_record = memory_allocate_structure(
	                   libfwps_internal_record_t );

	if( internal_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create record.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_record,
	     0,
	     sizeof( libfwps_internal_record_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear record.",
		 function );

		goto on_error;
	}
	internal_record->type = record_type;

	*record = (libfwps_record_t *) internal_record;

	return( 1 );

on_error:
	if( internal_record != NULL )
	{
		memory_free(
		 internal_record );
	}
	return( -1 );
}

/* Frees a record
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_free(
     libfwps_record_t **record,
     libcerror_error_t **error )
{
	static char *function = "libfwps_record_free";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record.",
		 function );

		return( -1 );
	}
	if( *record != NULL )
	{
		*record = NULL;
	}
	return( 1 );
}

/* Frees a record
 * Returns 1 if successful or -1 on error
 */
int libfwps_internal_record_free(
     libfwps_internal_record_t **internal_record,
     libcerror_error_t **error )
{
	static char *function = "libfwps_internal_record_free";

	if( internal_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal record.",
		 function );

		return( -1 );
	}
	if( *internal_record != NULL )
	{
		memory_free(
		 *internal_record );

		*internal_record = NULL;
	}
	return( 1 );
}

/* Copies a record from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_copy_from_byte_stream(
     libfwps_record_t *record,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_copy_from_byte_stream";
	size_t byte_stream_offset                  = 0;
	uint32_t name_size                         = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	system_character_t *value_string           = NULL;
	size_t value_string_size                   = 0;
	int result                                 = 0;
#endif

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

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
	if( ( byte_stream_size < 9 )
	 || ( byte_stream_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid byte stream size value out of bounds.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 byte_stream,
	 internal_record->size );

	if( ( internal_record->size < 9 )
	 || ( (size_t) internal_record->size > byte_stream_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid record - size value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: property record data:\n",
		 function );
		libcnotify_print_data(
		 byte_stream,
		 internal_record->size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( internal_record->type == LIBFWPS_RECORD_TYPE_NAMED )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( byte_stream[ byte_stream_offset + 4 ] ),
		 name_size );
	}
	else if( internal_record->type == LIBFWPS_RECORD_TYPE_NUMERIC )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( byte_stream[ byte_stream_offset + 4 ] ),
		 internal_record->entry_type );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_record->size );

		if( internal_record->type == LIBFWPS_RECORD_TYPE_NAMED )
		{
			libcnotify_printf(
			 "%s: name size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 name_size );
		}
		else
		{
			libcnotify_printf(
			 "%s: entry type\t\t\t: %" PRIu32 "\n",
			 function,
			 internal_record->entry_type );
		}
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 byte_stream[ byte_stream_offset + 8 ] );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_offset += 9;

	if( internal_record->type == LIBFWPS_RECORD_TYPE_NAMED )
	{
		if( ( name_size > internal_record->size )
		 || ( byte_stream_offset > ( internal_record->size - name_size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid name size value out of bounds.",
			 function );

			return( -1 );
		}
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
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		byte_stream_offset += name_size;
	}
	if( byte_stream_offset < internal_record->size )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value data:\n",
			 function );
			libcnotify_print_data(
			 &( byte_stream[ byte_stream_offset ] ),
			 internal_record->size - byte_stream_offset,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		/* TODO read value */
	}

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

/* Retrieves the entry type
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libfwps_record_get_entry_type(
     libfwps_record_t *record,
     uint32_t *entry_type,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_entry_type";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( entry_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry type.",
		 function );

		return( -1 );
	}
	if( internal_record->type == LIBFWPS_RECORD_TYPE_NAMED )
	{
		return( 0 );
	}
	*entry_type = internal_record->entry_type;

	return( 1 );
}

