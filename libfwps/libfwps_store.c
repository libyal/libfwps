/*
 * Windows Serialized Property Store functions
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
#include <types.h>

#include "libfwps_libcdata.h"
#include "libfwps_libcerror.h"
#include "libfwps_libcnotify.h"
#include "libfwps_set.h"
#include "libfwps_store.h"
#include "libfwps_types.h"

/* Creates a store
 * Make sure the value store is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libfwps_store_initialize(
     libfwps_store_t **store,
     libcerror_error_t **error )
{
	libfwps_internal_store_t *internal_store = NULL;
	static char *function                    = "libfwps_store_initialize";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	if( *store != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid store value already set.",
		 function );

		return( -1 );
	}
	internal_store = memory_allocate_structure(
	                  libfwps_internal_store_t );

	if( internal_store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create store.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_store,
	     0,
	     sizeof( libfwps_internal_store_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear store.",
		 function );

		memory_free(
		 internal_store );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_store->sets_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sets array.",
		 function );

		goto on_error;
	}
	*store = (libfwps_store_t *) internal_store;

	return( 1 );

on_error:
	if( internal_store != NULL )
	{
		memory_free(
		 internal_store );
	}
	return( -1 );
}

/* Frees a store
 * Returns 1 if successful or -1 on error
 */
int libfwps_store_free(
     libfwps_store_t **store,
     libcerror_error_t **error )
{
	libfwps_internal_store_t *internal_store = NULL;
	static char *function                    = "libfwps_store_free";
	int result                               = 1;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	if( *store != NULL )
	{
		internal_store = (libfwps_internal_store_t *) *store;
		*store         = NULL;

		if( libcdata_array_free(
		     &( internal_store->sets_array ),
		     (int(*)(intptr_t **, libcerror_error_t **)) &libfwps_internal_set_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free sets array.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_store );
	}
	return( result );
}

/* Copies a store from a byte stream
 * Returns 1 if successful or -1 on error
 */
int libfwps_store_copy_from_byte_stream(
     libfwps_store_t *store,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libfwps_internal_store_t *internal_store = NULL;
	libfwps_set_t *set                       = NULL;
	static char *function                    = "libfwps_store_copy_from_byte_stream";
	size_t byte_stream_offset                = 0;
	uint32_t set_data_size                   = 0;
	int entry_index                          = 0;
	int set_index                            = 0;

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfwps_internal_store_t *) store;

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
		 set_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: set: %d data size\t\t\t: %" PRIu32 "\n",
			 function,
			 set_index,
			 set_data_size );
		}
#endif
		if( set_data_size == 0 )
		{
			break;
		}
		if( ( set_data_size > byte_stream_size )
		 || ( byte_stream_offset > ( byte_stream_size - set_data_size ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid set: %d data size value out of bounds.",
			 function,
			 set_index );

			goto on_error;
		}
		if( libfwps_set_initialize(
		     &set,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create set: %d.",
			 function,
			 set_index );

			goto on_error;
		}
		( (libfwps_internal_set_t *) set )->is_managed = 1;

		if( libfwps_set_copy_from_byte_stream(
		     set,
		     &( byte_stream[ byte_stream_offset ] ),
		     (size_t) set_data_size,
		     ascii_codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy set: %d from byte stream.",
			 function,
			 set_index );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     internal_store->sets_array,
		     &entry_index,
		     (intptr_t *) set,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to append set: %d to array.",
			 function,
			 set_index );

			goto on_error;
		}
		set = NULL;

		byte_stream_offset += set_data_size;

		set_index++;
	}
	return( 1 );

on_error:
	if( set != NULL )
	{
		libfwps_internal_set_free(
		 (libfwps_internal_set_t **) &set,
		 NULL );
	}
	libcdata_array_empty(
	 internal_store->sets_array,
	 (int(*)(intptr_t **, libcerror_error_t **)) &libfwps_internal_set_free,
	 NULL );

	return( -1 );
}

/* Retrieves the number of sets
 * Returns 1 if successful or -1 on error
 */
int libfwps_store_get_number_of_sets(
     libfwps_store_t *store,
     int *number_of_sets,
     libcerror_error_t **error )
{
	libfwps_internal_store_t *internal_store = NULL;
	static char *function                    = "libfwps_store_get_number_of_sets";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfwps_internal_store_t *) store;

	if( libcdata_array_get_number_of_entries(
	     internal_store->sets_array,
	     number_of_sets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sets.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific set
 * Returns 1 if successful or -1 on error
 */
int libfwps_store_get_set_by_index(
     libfwps_store_t *store,
     int set_index,
     libfwps_set_t **set,
     libcerror_error_t **error )
{
	libfwps_internal_store_t *internal_store = NULL;
	static char *function                    = "libfwps_store_get_set_by_index";

	if( store == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid store.",
		 function );

		return( -1 );
	}
	internal_store = (libfwps_internal_store_t *) store;

	if( libcdata_array_get_entry_by_index(
	     internal_store->sets_array,
	     set_index,
	     (intptr_t **) set,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve set: %d.",
		 function,
		 set_index );

		return( -1 );
	}
	return( 1 );
}

