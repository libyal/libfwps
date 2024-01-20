/*
 * Windows Serialized Property Sheet functions
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
#include <byte_stream.h>
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include "libfwps_definitions.h"
#include "libfwps_libcerror.h"
#include "libfwps_libcnotify.h"
#include "libfwps_record.h"
#include "libfwps_libfguid.h"
#include "libfwps_set.h"
#include "libfwps_types.h"

const char *libfwps_serialized_property_set_signature = "1SPS";

uint8_t libfwps_format_class_identifier_named_properties[ 16 ] = {
	0x05, 0xd5, 0xcd, 0xd5, 0x9c, 0x2e, 0x1b, 0x10, 0x93, 0x97, 0x08, 0x00, 0x2b, 0x2c, 0xf9, 0xae };

uint8_t libfwps_format_class_identifier_unknown1[ 16 ] = {
	0x30, 0xf1, 0x25, 0xb7, 0xef, 0x47, 0x1a, 0x10, 0xa5, 0xf1, 0x02, 0x60, 0x8c, 0x9e, 0xeb, 0xac };

/* Creates a set
 * Make sure the value set is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwps_set_initialize(
     libfwps_set_t **set,
     libcerror_error_t **error )
{
	libfwps_internal_set_t *internal_set = NULL;
	static char *function                = "libfwps_set_initialize";

	if( set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid set.",
		 function );

		return( -1 );
	}
	if( *set != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid set value already set.",
		 function );

		return( -1 );
	}
	internal_set = memory_allocate_structure(
	                libfwps_internal_set_t );

	if( internal_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create set.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_set,
	     0,
	     sizeof( libfwps_internal_set_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear set.",
		 function );

		memory_free(
		 internal_set );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_set->records_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create records array.",
		 function );

		goto on_error;
	}
	*set = (libfwps_set_t *) internal_set;

	return( 1 );

on_error:
	if( internal_set != NULL )
	{
		memory_free(
		 internal_set );
	}
	return( -1 );
}

/* Frees a set
 * Returns 1 if successful or -1 on error
 */
int libfwps_set_free(
     libfwps_set_t **set,
     libcerror_error_t **error )
{
	libfwps_internal_set_t *internal_set = NULL;
	static char *function                = "libfwps_set_free";
	int result                           = 1;

	if( set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid set.",
		 function );

		return( -1 );
	}
	if( *set != NULL )
	{
		internal_set = (libfwps_internal_set_t *) *set;

		if( internal_set->is_managed == 0 )
		{
			if( libfwps_internal_set_free(
			     &internal_set,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free set.",
				 function );

				result = -1;
			}
		}
		*set = NULL;
	}
	return( result );
}

/* Frees a set
 * Returns 1 if successful or -1 on error
 */
int libfwps_internal_set_free(
     libfwps_internal_set_t **internal_set,
     libcerror_error_t **error )
{
	static char *function = "libfwps_internal_set_free";
	int result            = 1;

	if( internal_set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid set.",
		 function );

		return( -1 );
	}
	if( *internal_set != NULL )
	{
		if( libcdata_array_free(
		     &( ( *internal_set )->records_array ),
		     (int(*)(intptr_t **, libcerror_error_t **)) &libfwps_internal_record_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free records array.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_set );

		*internal_set = NULL;
	}
	return( result );
}

/* Copies a serialized property set from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libfwps_set_copy_from_byte_stream(
     libfwps_set_t *set,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfwps_internal_set_t *internal_set = NULL;
	libfwps_record_t *property_record    = NULL;
	static char *function                = "libfwps_set_copy_from_byte_stream";
	size_t byte_stream_offset            = 0;
	uint32_t record_data_size            = 0;
	uint8_t property_record_type         = 0;
	int entry_index                      = 0;
	int record_index                     = 0;

#if defined( HAVE_DEBUG_OUTPUT )
        system_character_t guid_string[ 48 ];

        libfguid_identifier_t *guid          = NULL;
	int result                           = 0;
#endif

	if( set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid set.",
		 function );

		return( -1 );
	}
	internal_set = (libfwps_internal_set_t *) set;

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
	if( ( byte_stream_size < 24 )
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: property set data:\n",
		 function );
		libcnotify_print_data(
		 byte_stream,
		 24,
		 0 );
	}
#endif
	if( memory_compare(
	     &( byte_stream[ byte_stream_offset + 4 ] ),
	     libfwps_serialized_property_set_signature,
	     4 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 byte_stream,
	 internal_set->size );

	if( memory_copy(
	     internal_set->identifier,
	     &( byte_stream[ byte_stream_offset + 8 ] ),
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: size\t\t\t\t\t: %" PRIu16 "\n",
		 function,
		 internal_set->size );

		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c\n",
		 function,
		 byte_stream[ byte_stream_offset + 4 ],
		 byte_stream[ byte_stream_offset + 5 ],
		 byte_stream[ byte_stream_offset + 6 ],
		 byte_stream[ byte_stream_offset + 7 ] );

		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create GUID.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     internal_set->identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_UPPER_CASE | LIBFGUID_STRING_FORMAT_FLAG_USE_SURROUNDING_BRACES,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: format class identifier\t\t: %" PRIs_SYSTEM "\n",
		 function,
		 guid_string );

		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free GUID.",
			 function );

			goto on_error;
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( ( internal_set->size < 24 )
	 || ( (size_t) internal_set->size > byte_stream_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid property set size value out of bounds.",
		 function );

		goto on_error;
	}
	byte_stream_offset += 24;

	if( memory_compare(
	     internal_set->identifier,
	     libfwps_format_class_identifier_named_properties,
	     16 ) == 0 )
	{
		property_record_type = LIBFWPS_RECORD_TYPE_NAMED;
	}
	else
	{
		property_record_type = LIBFWPS_RECORD_TYPE_NUMERIC;
	}
	while( byte_stream_offset < byte_stream_size )
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
		 record_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: record: %d data size\t\t\t: %" PRIu32 "\n",
			 function,
			 record_index,
			 record_data_size );
		}
#endif
		if( record_data_size == 0 )
		{
			break;
		}
		if( ( record_data_size > byte_stream_size )
		 || ( byte_stream_offset > ( byte_stream_size - record_data_size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid record: %d data size value out of bounds.",
			 function,
			 record_index );

			goto on_error;
		}
		if( libfwps_record_initialize(
		     &property_record,
		     property_record_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create property record: %d.",
			 function,
			 record_index );

			goto on_error;
		}
		if( libfwps_record_copy_from_byte_stream(
		     property_record,
		     &( byte_stream[ byte_stream_offset ] ),
		     record_data_size,
		     ascii_codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy property record: %d from byte stream.",
			 function,
			 record_index );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     internal_set->records_array,
		     &entry_index,
		     (intptr_t *) property_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to append record: %d to array.",
			 function,
			 record_index );

			goto on_error;
		}
		property_record = NULL;

		byte_stream_offset += record_data_size;

		record_index++;
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
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
#endif
	if( property_record != NULL )
	{
		libfwps_internal_record_free(
		 (libfwps_internal_record_t **) &property_record,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the identifier
 * The identifier is a little-endian GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libfwps_set_get_identifier(
     libfwps_set_t *set,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libfwps_internal_set_t *internal_set = NULL;
	static char *function                = "libfwps_set_get_identifier";

	if( set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid set.",
		 function );

		return( -1 );
	}
	internal_set = (libfwps_internal_set_t *) set;

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
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     internal_set->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of records
 * Returns 1 if successful or -1 on error
 */
int libfwps_set_get_number_of_records(
     libfwps_set_t *set,
     int *number_of_records,
     libcerror_error_t **error )
{
	libfwps_internal_set_t *internal_set = NULL;
	static char *function                = "libfwps_set_get_number_of_records";

	if( set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid set.",
		 function );

		return( -1 );
	}
	internal_set = (libfwps_internal_set_t *) set;

	if( libcdata_array_get_number_of_entries(
	     internal_set->records_array,
	     number_of_records,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of records.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific record
 * Returns 1 if successful or -1 on error
 */
int libfwps_set_get_record_by_index(
     libfwps_set_t *set,
     int record_index,
     libfwps_record_t **record,
     libcerror_error_t **error )
{
	libfwps_internal_set_t *internal_set = NULL;
	static char *function                = "libfwps_set_get_record_by_index";

	if( set == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid set.",
		 function );

		return( -1 );
	}
	internal_set = (libfwps_internal_set_t *) set;

	if( libcdata_array_get_entry_by_index(
	     internal_set->records_array,
	     record_index,
	     (intptr_t **) record,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve record: %d.",
		 function,
		 record_index );

		return( -1 );
	}
	return( 1 );
}

