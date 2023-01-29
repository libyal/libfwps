/*
 * Windows Serialized Property Storage functions
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
#include <system_string.h>
#include <types.h>

#include "libfwps_definitions.h"
#include "libfwps_libcerror.h"
#include "libfwps_libcnotify.h"
#include "libfwps_libfguid.h"
#include "libfwps_record.h"
#include "libfwps_storage.h"
#include "libfwps_types.h"

const char *libfwps_serialized_property_storage_signature = "1SPS";

uint8_t libfwps_storage_format_class_identifier_named_properties[ 16 ] = {
	0x05, 0xd5, 0xcd, 0xd5, 0x9c, 0x2e, 0x1b, 0x10, 0x93, 0x97, 0x08, 0x00, 0x2b, 0x2c, 0xf9, 0xae };

uint8_t libfwps_storage_format_class_identifier_unknown1[ 16 ] = {
	0x30, 0xf1, 0x25, 0xb7, 0xef, 0x47, 0x1a, 0x10, 0xa5, 0xf1, 0x02, 0x60, 0x8c, 0x9e, 0xeb, 0xac };

/* Creates a storage
 * Make sure the value storage is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwps_storage_initialize(
     libfwps_storage_t **storage,
     libcerror_error_t **error )
{
	libfwps_internal_storage_t *internal_storage = NULL;
	static char *function                        = "libfwps_storage_initialize";

	if( storage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid storage.",
		 function );

		return( -1 );
	}
	if( *storage != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid storage value already set.",
		 function );

		return( -1 );
	}
	internal_storage = memory_allocate_structure(
	                    libfwps_internal_storage_t );

	if( internal_storage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create storage.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_storage,
	     0,
	     sizeof( libfwps_internal_storage_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear storage.",
		 function );

		goto on_error;
	}
	*storage = (libfwps_storage_t *) internal_storage;

	return( 1 );

on_error:
	if( internal_storage != NULL )
	{
		memory_free(
		 internal_storage );
	}
	return( -1 );
}

/* Frees a storage
 * Returns 1 if successful or -1 on error
 */
int libfwps_storage_free(
     libfwps_storage_t **storage,
     libcerror_error_t **error )
{
	libfwps_internal_storage_t *internal_storage = NULL;
	static char *function                        = "libfwps_storage_free";

	if( storage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid storage.",
		 function );

		return( -1 );
	}
	if( *storage != NULL )
	{
		internal_storage = (libfwps_internal_storage_t *) *storage;
		*storage         = NULL;

		memory_free(
		 internal_storage );
	}
	return( 1 );
}

/* Copies a serialized property storage from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libfwps_storage_copy_from_byte_stream(
     libfwps_storage_t *storage,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfwps_internal_storage_t *internal_storage = NULL;
	libfwps_record_t *property_record            = NULL;
	static char *function                        = "libfwps_storage_copy_from_byte_stream";
	size_t byte_stream_offset                    = 0;
	uint32_t property_record_size                = 0;
	uint8_t property_record_type                 = 0;

#if defined( HAVE_DEBUG_OUTPUT )
        system_character_t guid_string[ 48 ];

        libfguid_identifier_t *guid                  = NULL;
	int result                                   = 0;
#endif

	if( storage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid storage.",
		 function );

		return( -1 );
	}
	internal_storage = (libfwps_internal_storage_t *) storage;

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
	if( ( byte_stream_size < 4 )
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
	 internal_storage->size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: size\t\t\t\t: %" PRIu16 "\n",
		 function,
		 internal_storage->size );
	}
#endif
	if( internal_storage->size == 0 )
	{
		return( 1 );
	}
	if( ( internal_storage->size < 4 )
	 || ( (size_t) internal_storage->size > byte_stream_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid property storage size value out of bounds.",
		 function );

		goto on_error;
	}
	byte_stream_offset += 4;

	if( ( internal_storage->size - byte_stream_offset ) < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid byte stream size value to small.",
		 function );

		goto on_error;
	}
	if( memory_compare(
	     &( byte_stream[ byte_stream_offset ] ),
	     libfwps_serialized_property_storage_signature,
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: %c%c%c%c\n",
		 function,
		 byte_stream[ byte_stream_offset ],
		 byte_stream[ byte_stream_offset + 1 ],
		 byte_stream[ byte_stream_offset + 2 ],
		 byte_stream[ byte_stream_offset + 3 ] );
	}
#endif
	byte_stream_offset += 4;

	if( ( internal_storage->size - byte_stream_offset ) < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid byte stream size value to small.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
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
		     &( byte_stream[ byte_stream_offset ] ),
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

	if( memory_compare(
	     &( byte_stream[ byte_stream_offset ] ),
	     libfwps_storage_format_class_identifier_named_properties,
	     16 ) == 0 )
	{
		property_record_type = LIBFWPS_RECORD_TYPE_NAMED;
	}
	else
	{
		property_record_type = LIBFWPS_RECORD_TYPE_NUMERIC;
	}
	byte_stream_offset += 16;

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
		 property_record_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: record data size\t\t\t: %" PRIu32 "\n",
			 function,
			 property_record_size );
		}
#endif
		if( property_record_size == 0 )
		{
			break;
		}
		if( ( property_record_size > byte_stream_size )
		 || ( byte_stream_offset > ( byte_stream_size - property_record_size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid value data size value out of bounds.",
			 function );

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
			 "%s: unable to create property record.",
			 function );

			goto on_error;
		}
		if( libfwps_record_copy_from_byte_stream(
		     property_record,
		     &( byte_stream[ byte_stream_offset ] ),
		     byte_stream_size - byte_stream_offset,
		     ascii_codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to property record.",
			 function );

			goto on_error;
		}
/* TODO store value array if size != 0 */
		if( libfwps_internal_record_free(
		     (libfwps_internal_record_t **) &property_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free property record.",
			 function );

			goto on_error;
		}
		if( property_record_size == 0 )
		{
			break;
		}
		byte_stream_offset += property_record_size;
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

