/*
 * OSS-Fuzz target for libfwps record type
 *
 * Copyright (C) 2013-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libfwps.h"
#include "libfwps_definitions.h"
#include "libfwps_record.h"

/* The maximum size of a temporary data or string buffer
 */
#define OSS_FUZZ_MAXIMUM_DATA_SIZE	( (size_t) 8 * 1024 * 1024 )

/* Retrieves an ASCII codepage based on the size of the byte stream
 * This varies the codepage used to convert ASCII formatted value data
 * including UTF-7 (65000) and UTF-8 (65001)
 */
static int ossfuzz_get_ascii_codepage(
      size_t byte_stream_size )
{
	/* The supported codepages
	 */
	static const int ascii_codepages[] = {
		LIBFWPS_CODEPAGE_WINDOWS_1252,
		LIBFWPS_CODEPAGE_WINDOWS_1251,
		LIBFWPS_CODEPAGE_WINDOWS_1250,
		LIBFWPS_CODEPAGE_WINDOWS_936,
		LIBFWPS_CODEPAGE_ISO_8859_1,
		LIBFWPS_CODEPAGE_ISO_8859_5,
		LIBFWPS_CODEPAGE_KOI8_R,
		LIBFWPS_CODEPAGE_ASCII,
		65000, /* UTF-7 */
		65001  /* UTF-8 */ };

	return( ascii_codepages[
	          byte_stream_size % ( sizeof( ascii_codepages ) / sizeof( ascii_codepages[ 0 ] ) ) ] );
}

/* Exercises the record functions of libfwps with a record
 * Note that the return values of the record functions are intentionally ignored,
 * both the regular and the error paths are of interest
 */
static void ossfuzz_fuzz_record(
      libfwps_record_t *record )
{
	uint8_t *value_data     = NULL;
	uint8_t *utf8_string    = NULL;
	uint8_t guid_data[ 16 ] = { 0 };
	uint8_t value_boolean   = 0;
	uint8_t value_8bit      = 0;
	uint16_t *utf16_string  = NULL;
	uint16_t value_16bit    = 0;
	uint32_t entry_type     = 0;
	uint32_t value_32bit    = 0;
	uint32_t value_type     = 0;
	uint64_t filetime       = 0;
	uint64_t floatingtime   = 0;
	uint64_t value_64bit    = 0;
	double value_double     = 0.;
	size_t data_size        = 0;
	size_t utf8_string_size = 0;
	size_t utf16_string_size = 0;

	if( record == NULL )
	{
		return;
	}
	libfwps_record_get_entry_type(
	 record,
	 &entry_type,
	 NULL );
	libfwps_record_get_value_type(
	 record,
	 &value_type,
	 NULL );

	if( libfwps_record_get_utf8_entry_name_size(
	     record,
	     &utf8_string_size,
	     NULL ) == 1
	 && utf8_string_size > 0
	 && utf8_string_size <= OSS_FUZZ_MAXIMUM_DATA_SIZE )
	{
		utf8_string = (uint8_t *) malloc( utf8_string_size );

		if( utf8_string != NULL )
		{
			libfwps_record_get_utf8_entry_name(
			 record,
			 utf8_string,
			 utf8_string_size,
			 NULL );
		}
	}
	if( utf8_string != NULL )
	{
		free( utf8_string );
	}
	if( libfwps_record_get_utf16_entry_name_size(
	     record,
	     &utf16_string_size,
	     NULL ) == 1
	 && utf16_string_size > 0
	 && ( utf16_string_size * sizeof( uint16_t ) ) <= OSS_FUZZ_MAXIMUM_DATA_SIZE )
	{
		utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

		if( utf16_string != NULL )
		{
			libfwps_record_get_utf16_entry_name(
			 record,
			 utf16_string,
			 utf16_string_size,
			 NULL );
		}
	}
	if( utf16_string != NULL )
	{
		free( utf16_string );
	}

	if( libfwps_record_get_utf8_value_name_size(
	     record,
	     &utf8_string_size,
	     NULL ) == 1
	 && utf8_string_size > 0
	 && utf8_string_size <= OSS_FUZZ_MAXIMUM_DATA_SIZE )
	{
		utf8_string = (uint8_t *) malloc( utf8_string_size );

		if( utf8_string != NULL )
		{
			libfwps_record_get_utf8_value_name(
			 record,
			 utf8_string,
			 utf8_string_size,
			 NULL );
		}
	}
	if( utf8_string != NULL )
	{
		free( utf8_string );
	}
	if( libfwps_record_get_utf16_value_name_size(
	     record,
	     &utf16_string_size,
	     NULL ) == 1
	 && utf16_string_size > 0
	 && ( utf16_string_size * sizeof( uint16_t ) ) <= OSS_FUZZ_MAXIMUM_DATA_SIZE )
	{
		utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

		if( utf16_string != NULL )
		{
			libfwps_record_get_utf16_value_name(
			 record,
			 utf16_string,
			 utf16_string_size,
			 NULL );
		}
	}
	if( utf16_string != NULL )
	{
		free( utf16_string );
	}

	if( libfwps_record_get_data_size(
	     record,
	     &data_size,
	     NULL ) == 1
	 && data_size > 0
	 && data_size <= OSS_FUZZ_MAXIMUM_DATA_SIZE )
	{
		value_data = (uint8_t *) malloc( data_size );

		if( value_data != NULL )
		{
			libfwps_record_get_data(
			 record,
			 value_data,
			 data_size,
			 NULL );
		}
	}
	if( value_data != NULL )
	{
		free( value_data );
	}

	libfwps_record_get_data_as_boolean(
	 record,
	 &value_boolean,
	 NULL );
	libfwps_record_get_data_as_8bit_integer(
	 record,
	 &value_8bit,
	 NULL );
	libfwps_record_get_data_as_16bit_integer(
	 record,
	 &value_16bit,
	 NULL );
	libfwps_record_get_data_as_32bit_integer(
	 record,
	 &value_32bit,
	 NULL );
	libfwps_record_get_data_as_64bit_integer(
	 record,
	 &value_64bit,
	 NULL );
	libfwps_record_get_data_as_floatingtime(
	 record,
	 &floatingtime,
	 NULL );
	libfwps_record_get_data_as_filetime(
	 record,
	 &filetime,
	 NULL );
	libfwps_record_get_data_as_floating_point(
	 record,
	 &value_double,
	 NULL );

	if( libfwps_record_get_data_as_utf8_string_size(
	     record,
	     &utf8_string_size,
	     NULL ) == 1
	 && utf8_string_size > 0
	 && utf8_string_size <= OSS_FUZZ_MAXIMUM_DATA_SIZE )
	{
		utf8_string = (uint8_t *) malloc( utf8_string_size );

		if( utf8_string != NULL )
		{
			libfwps_record_get_data_as_utf8_string(
			 record,
			 utf8_string,
			 utf8_string_size,
			 NULL );
		}
	}
	if( utf8_string != NULL )
	{
		free( utf8_string );
	}
	if( libfwps_record_get_data_as_utf16_string_size(
	     record,
	     &utf16_string_size,
	     NULL ) == 1
	 && utf16_string_size > 0
	 && ( utf16_string_size * sizeof( uint16_t ) ) <= OSS_FUZZ_MAXIMUM_DATA_SIZE )
	{
		utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

		if( utf16_string != NULL )
		{
			libfwps_record_get_data_as_utf16_string(
			 record,
			 utf16_string,
			 utf16_string_size,
			 NULL );
		}
	}
	if( utf16_string != NULL )
	{
		free( utf16_string );
	}
	if( libfwps_record_get_data_as_utf8_path_string_size(
	     record,
	     &utf8_string_size,
	     NULL ) == 1
	 && utf8_string_size > 0
	 && utf8_string_size <= OSS_FUZZ_MAXIMUM_DATA_SIZE )
	{
		utf8_string = (uint8_t *) malloc( utf8_string_size );

		if( utf8_string != NULL )
		{
			libfwps_record_get_data_as_utf8_path_string(
			 record,
			 utf8_string,
			 utf8_string_size,
			 NULL );
		}
	}
	if( utf8_string != NULL )
	{
		free( utf8_string );
	}
	if( libfwps_record_get_data_as_utf16_path_string_size(
	     record,
	     &utf16_string_size,
	     NULL ) == 1
	 && utf16_string_size > 0
	 && ( utf16_string_size * sizeof( uint16_t ) ) <= OSS_FUZZ_MAXIMUM_DATA_SIZE )
	{
		utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

		if( utf16_string != NULL )
		{
			libfwps_record_get_data_as_utf16_path_string(
			 record,
			 utf16_string,
			 utf16_string_size,
			 NULL );
		}
	}
	if( utf16_string != NULL )
	{
		free( utf16_string );
	}

	libfwps_record_get_data_as_guid(
	 record,
	 guid_data,
	 16,
	 NULL );
}

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	libfwps_record_t *record    = NULL;
	uint8_t record_type         = 0;

	if( size == 0 )
	{
		return( 0 );
	}
	/* The least significant bit of the first byte of the byte stream is used
	 * to select the record type so that both the named and the numeric
	 * record types are exercised
	 */
	if( ( data[ 0 ] & 0x01 ) == 0 )
	{
		record_type = LIBFWPS_RECORD_TYPE_NAMED;
	}
	else
	{
		record_type = LIBFWPS_RECORD_TYPE_NUMERIC;
	}
	if( libfwps_record_initialize(
	     &record,
	     record_type,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	libfwps_record_copy_from_byte_stream(
	 record,
	 data,
	 size,
	 ossfuzz_get_ascii_codepage( size ),
	 NULL );
	ossfuzz_fuzz_record(
	 record );

	libfwps_internal_record_free(
	 (libfwps_internal_record_t **) &record,
	 NULL );

	return( 0 );
}

} /* extern "C" */
