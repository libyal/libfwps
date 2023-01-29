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
		if( ( *internal_record )->value_data != NULL )
		{
			memory_free(
			 ( *internal_record )->value_data );
		}
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

	if( internal_record->value_data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid record - value data already set.",
		 function );

		return( -1 );
	}
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
	if( ( byte_stream_size < 13 )
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

	if( ( internal_record->size < 13 )
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
		 "%s: record data:\n",
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
		if( ( name_size > byte_stream_size )
		 || ( byte_stream_offset > ( byte_stream_size - name_size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid name size value out of bounds.",
			 function );

			goto on_error;
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
			if( value_string_size > (size_t) ( SSIZE_MAX / sizeof( system_character_t ) ) )
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
	if( byte_stream_offset > ( byte_stream_size - 4 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid byte stream size value too small.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 &( byte_stream[ byte_stream_offset ] ),
	 internal_record->value_type );

	byte_stream_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: value type\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_record->value_type );
	}
#endif
	switch( internal_record->value_type )
	{
		case LIBFWPS_VALUE_TYPE_BOOLEAN:
		case LIBFWPS_VALUE_TYPE_INTEGER_8BIT_SIGNED:
		case LIBFWPS_VALUE_TYPE_INTEGER_8BIT_UNSIGNED:
			internal_record->value_data_size = 1;
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_16BIT_SIGNED:
		case LIBFWPS_VALUE_TYPE_INTEGER_16BIT_UNSIGNED:
			internal_record->value_data_size = 2;
			break;

		case LIBFWPS_VALUE_TYPE_FLOAT_32BIT:
		case LIBFWPS_VALUE_TYPE_INTEGER_32BIT_SIGNED:
		case LIBFWPS_VALUE_TYPE_INTEGER_32BIT_UNSIGNED:
			internal_record->value_data_size = 4;
			break;

		case LIBFWPS_VALUE_TYPE_CURRENCY:
		case LIBFWPS_VALUE_TYPE_DOUBLE_64BIT:
		case LIBFWPS_VALUE_TYPE_FILETIME:
		case LIBFWPS_VALUE_TYPE_INTEGER_64BIT_SIGNED:
		case LIBFWPS_VALUE_TYPE_INTEGER_64BIT_UNSIGNED:
			internal_record->value_data_size = 8;
			break;

		case LIBFWPS_VALUE_TYPE_FIXED_POINT_128BIT:
		case LIBFWPS_VALUE_TYPE_GUID:
			internal_record->value_data_size = 16;
			break;

		case LIBFWPS_VALUE_TYPE_BINARY_STRING:
		case LIBFWPS_VALUE_TYPE_STRING_ASCII:
		case LIBFWPS_VALUE_TYPE_STRING_UNICODE:
			internal_record->value_data_size = 0;
			break;

		default:
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: invalid record entry - unsupported value type.",
			 function );

			goto on_error;
	}
	if( internal_record->value_data_size == 0 )
	{
		if( byte_stream_offset > ( byte_stream_size - 4 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: invalid byte stream size value too small.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 &( byte_stream[ byte_stream_offset ] ),
		 internal_record->value_data_size );

		byte_stream_offset += 4;

		if( internal_record->value_type == LIBFWPS_VALUE_TYPE_STRING_UNICODE )
		{
			internal_record->value_data_size *= 2;
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: value data size\t\t: %" PRIu32 "\n",
		 function,
		 internal_record->value_data_size );
	}
#endif
	if( internal_record->value_data_size > 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: value data:\n",
			 function );
			libcnotify_print_data(
			 &( byte_stream[ byte_stream_offset ] ),
			 internal_record->value_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		if( internal_record->value_data_size > MEMORY_MAXIMUM_ALLOCATION_SIZE )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid value data size value exceeds maximum.",
			 function );

			goto on_error;
		}
		internal_record->value_data = (uint8_t *) memory_allocate(
		                                           sizeof( uint8_t ) * internal_record->value_data_size );

		if( internal_record->value_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create value data.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     internal_record->value_data,
		     &( byte_stream[ byte_stream_offset ] ),
		     internal_record->value_data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy value data.",
			 function );

			goto on_error;
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( byte_stream_offset < internal_record->size )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( byte_stream[ byte_stream_offset ] ),
			 internal_record->size - byte_stream_offset,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
	}
#endif
	internal_record->ascii_codepage = ascii_codepage;

	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
#endif
	if( internal_record->value_data != NULL )
	{
		memory_free(
		 internal_record->value_data );

		internal_record->value_data = NULL;
	}
	internal_record->value_data_size = 0;

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

/* Retrieves the value type
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_value_type(
     libfwps_record_t *record,
     uint32_t *value_type,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_value_type";

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

	if( value_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value type.",
		 function );

		return( -1 );
	}
	*value_type = internal_record->value_type;

	return( 1 );
}

/* Retrieves the data as a boolean value
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_boolean(
     libfwps_record_t *record,
     uint8_t *value_boolean,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_boolean";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( internal_record->value_type != LIBFWPS_VALUE_TYPE_BOOLEAN )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data_size != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( value_boolean == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value boolean.",
		 function );

		return( -1 );
	}
	*value_boolean = internal_record->value_data[ 0 ];

	return( 1 );
}

/* Retrieves the data as a 8-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_8bit_integer(
     libfwps_record_t *record,
     uint8_t *value_8bit,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_8bit_integer";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( ( internal_record->value_type != LIBFWPS_VALUE_TYPE_INTEGER_8BIT_SIGNED )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_INTEGER_8BIT_UNSIGNED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data_size != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( value_8bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 8-bit.",
		 function );

		return( -1 );
	}
	*value_8bit = internal_record->value_data[ 0 ];

	return( 1 );
}

/* Retrieves the data as a 16-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_16bit_integer(
     libfwps_record_t *record,
     uint16_t *value_16bit,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_16bit_integer";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( ( internal_record->value_type != LIBFWPS_VALUE_TYPE_INTEGER_16BIT_SIGNED )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_INTEGER_16BIT_UNSIGNED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data_size != 2 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( value_16bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 16-bit.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 internal_record->value_data,
	 *value_16bit );

	return( 1 );
}

/* Retrieves the data as a 32-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_32bit_integer(
     libfwps_record_t *record,
     uint32_t *value_32bit,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_32bit_integer";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( ( internal_record->value_type != LIBFWPS_VALUE_TYPE_INTEGER_32BIT_SIGNED )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_INTEGER_32BIT_UNSIGNED )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_ERROR ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data_size != 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( value_32bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 32-bit.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 internal_record->value_data,
	 *value_32bit );

	return( 1 );
}

/* Retrieves the data as a 64-bit integer value
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_64bit_integer(
     libfwps_record_t *record,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_64bit_integer";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( ( internal_record->value_type != LIBFWPS_VALUE_TYPE_INTEGER_64BIT_SIGNED )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_INTEGER_64BIT_UNSIGNED )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_CURRENCY ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data_size != 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint64_little_endian(
	 internal_record->value_data,
	 *value_64bit );

	return( 1 );
}

/* Retrieves the data as a 64-bit FILETIME value
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_filetime(
     libfwps_record_t *record,
     uint64_t *filetime,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_filetime";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( internal_record->value_type != LIBFWPS_VALUE_TYPE_FILETIME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data_size != 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint64_little_endian(
	 internal_record->value_data,
	 *filetime );

	return( 1 );
}

/* Retrieves the floating point value
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_floating_point(
     libfwps_record_t *record,
     double *value_floating_point,
     libcerror_error_t **error )
{
	byte_stream_float32_t value_float;
	byte_stream_float64_t value_double;

	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_floating_point";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( ( internal_record->value_type != LIBFWPS_VALUE_TYPE_FLOAT_32BIT )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_DOUBLE_64BIT ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( value_floating_point == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value floating point.",
		 function );

		return( -1 );
	}
	/* The value data size of a floating point value is 4 or 8
	 */
	if( ( internal_record->value_data_size != 4 )
	 && ( internal_record->value_data_size != 8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data_size == 4 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 internal_record->value_data,
		 value_float.integer );

		*value_floating_point = (double) value_float.floating_point;
	}
	else if( internal_record->value_data_size == 8 )
	{
		byte_stream_copy_to_uint64_little_endian(
		 internal_record->value_data,
		 value_double.integer );

		*value_floating_point = value_double.floating_point;
	}
	return( 1 );
}

/* Retrieves the size of the data formatted as an UTF-8 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_utf8_string_size(
     libfwps_record_t *record,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_utf8_string_size";
	uint8_t is_ascii_string                    = 0;
	int result                                 = 0;

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( ( internal_record->value_type != LIBFWPS_VALUE_TYPE_STRING_ASCII )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_record->value_data == NULL )
	 || ( internal_record->value_data_size == 0 ) )
	{
		*utf8_string_size = 0;

		return( 1 );
	}
	if( internal_record->value_type == LIBFWPS_VALUE_TYPE_STRING_ASCII )
	{
		is_ascii_string = 1;
	}
	/* String is in UTF-16 little-endian
	 */
	if( is_ascii_string == 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
		          internal_record->value_data,
		          internal_record->value_data_size,
		          LIBUNA_ENDIAN_LITTLE,
		          utf8_string_size,
		          error );
	}
	/* Codepage 65000 represents UTF-7
	 */
	else if( internal_record->ascii_codepage == 65000 )
	{
		result = libuna_utf8_string_size_from_utf7_stream(
			  internal_record->value_data,
			  internal_record->value_data_size,
			  utf8_string_size,
			  error );
	}
	/* Codepage 65001 represents UTF-8
	 */
	else if( internal_record->ascii_codepage == 65001 )
	{
		result = libuna_utf8_string_size_from_utf8_stream(
			  internal_record->value_data,
			  internal_record->value_data_size,
			  utf8_string_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  internal_record->value_data,
			  internal_record->value_data_size,
			  internal_record->ascii_codepage,
			  utf8_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of value data as UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data formatted as an UTF-8 string
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_utf8_string(
     libfwps_record_t *record,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_utf8_string";
	uint8_t is_ascii_string                    = 0;
	int result                                 = 0;

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( ( internal_record->value_type != LIBFWPS_VALUE_TYPE_STRING_ASCII )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( ( utf8_string_size == 0 )
	 || ( utf8_string_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-8 string size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( internal_record->value_data == NULL )
	 || ( internal_record->value_data_size == 0 ) )
	{
		utf8_string[ 0 ] = 0;

		return( 1 );
	}
	if( internal_record->value_type == LIBFWPS_VALUE_TYPE_STRING_ASCII )
	{
		is_ascii_string = 1;
	}
	/* String is in UTF-16 little-endian
	 */
	if( is_ascii_string == 0 )
	{
		result = libuna_utf8_string_copy_from_utf16_stream(
		          utf8_string,
		          utf8_string_size,
		          internal_record->value_data,
		          internal_record->value_data_size,
		          LIBUNA_ENDIAN_LITTLE,
		          error );
	}
	/* Codepage 65000 represents UTF-7
	 */
	else if( internal_record->ascii_codepage == 65000 )
	{
		result = libuna_utf8_string_copy_from_utf7_stream(
		          utf8_string,
		          utf8_string_size,
		          internal_record->value_data,
		          internal_record->value_data_size,
		          error );
	}
	/* Codepage 65001 represents UTF-8
	 */
	else if( internal_record->ascii_codepage == 65001 )
	{
		result = libuna_utf8_string_copy_from_utf8_stream(
		          utf8_string,
		          utf8_string_size,
		          internal_record->value_data,
		          internal_record->value_data_size,
		          error );
	}
	else
	{
		result = libuna_utf8_string_copy_from_byte_stream(
		          utf8_string,
		          utf8_string_size,
		          internal_record->value_data,
		          internal_record->value_data_size,
		          internal_record->ascii_codepage,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the data formatted as an UTF-16 string
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_utf16_string_size(
     libfwps_record_t *record,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_utf16_string_size";
	uint8_t is_ascii_string                    = 0;
	int result                                 = 0;

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( ( internal_record->value_type != LIBFWPS_VALUE_TYPE_STRING_ASCII )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( ( internal_record->value_data == NULL )
	 || ( internal_record->value_data_size == 0 ) )
	{
		*utf16_string_size = 0;

		return( 1 );
	}
	if( internal_record->value_type == LIBFWPS_VALUE_TYPE_STRING_ASCII )
	{
		is_ascii_string = 1;
	}
	/* String is in UTF-16 little-endian
	 */
	if( is_ascii_string == 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
		          internal_record->value_data,
		          internal_record->value_data_size,
		          LIBUNA_ENDIAN_LITTLE,
		          utf16_string_size,
		          error );
	}
	/* Codepage 65000 represents UTF-7
	 */
	else if( internal_record->ascii_codepage == 65000 )
	{
		result = libuna_utf16_string_size_from_utf7_stream(
			  internal_record->value_data,
			  internal_record->value_data_size,
			  utf16_string_size,
			  error );
	}
	/* Codepage 65001 represents UTF-8
	 */
	else if( internal_record->ascii_codepage == 65001 )
	{
		result = libuna_utf16_string_size_from_utf8_stream(
			  internal_record->value_data,
			  internal_record->value_data_size,
			  utf16_string_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  internal_record->value_data,
			  internal_record->value_data_size,
			  internal_record->ascii_codepage,
			  utf16_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of value data as UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data formatted as an UTF-16 string
 * The function uses a codepage if necessary, it uses the codepage set for the library
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_utf16_string(
     libfwps_record_t *record,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_utf16_string";
	uint8_t is_ascii_string                    = 0;
	int result                                 = 0;

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( ( internal_record->value_type != LIBFWPS_VALUE_TYPE_STRING_ASCII )
	 && ( internal_record->value_type != LIBFWPS_VALUE_TYPE_STRING_UNICODE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( ( utf16_string_size == 0 )
	 || ( utf16_string_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-16 string size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( internal_record->value_data == NULL )
	 || ( internal_record->value_data_size == 0 ) )
	{
		utf16_string[ 0 ] = 0;

		return( 1 );
	}
	if( internal_record->value_type == LIBFWPS_VALUE_TYPE_STRING_ASCII )
	{
		is_ascii_string = 1;
	}
	/* String is in UTF-16 little-endian
	 */
	if( is_ascii_string == 0 )
	{
		result = libuna_utf16_string_copy_from_utf16_stream(
		          utf16_string,
		          utf16_string_size,
		          internal_record->value_data,
		          internal_record->value_data_size,
		          LIBUNA_ENDIAN_LITTLE,
		          error );
	}
	/* Codepage 65000 represents UTF-7
	 */
	else if( internal_record->ascii_codepage == 65000 )
	{
		result = libuna_utf16_string_copy_from_utf7_stream(
		          utf16_string,
		          utf16_string_size,
		          internal_record->value_data,
		          internal_record->value_data_size,
		          error );
	}
	/* Codepage 65001 represents UTF-8
	 */
	else if( internal_record->ascii_codepage == 65001 )
	{
		result = libuna_utf16_string_copy_from_utf8_stream(
		          utf16_string,
		          utf16_string_size,
		          internal_record->value_data,
		          internal_record->value_data_size,
		          error );
	}
	else
	{
		result = libuna_utf16_string_copy_from_byte_stream(
		          utf16_string,
		          utf16_string_size,
		          internal_record->value_data,
		          internal_record->value_data_size,
		          internal_record->ascii_codepage,
		          error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy value data to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data as a GUID value
 * Returns 1 if successful or -1 on error
 */
int libfwps_record_get_data_as_guid(
     libfwps_record_t *record,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libfwps_internal_record_t *internal_record = NULL;
	static char *function                      = "libfwps_record_get_data_as_guid";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record entry.",
		 function );

		return( -1 );
	}
	internal_record = (libfwps_internal_record_t *) record;

	if( internal_record->value_type != LIBFWPS_VALUE_TYPE_GUID )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid record entry - unsupported value type.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid record entry - missing value data.",
		 function );

		return( -1 );
	}
	if( internal_record->value_data_size != 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported value data size.",
		 function );

		return( -1 );
	}
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: GUID data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID data size value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     internal_record->value_data,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy value data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

