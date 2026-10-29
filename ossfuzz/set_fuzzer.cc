/*
 * OSS-Fuzz target for libfwps set type
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

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libfwps.h"

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

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	libfwps_record_t *record              = NULL;
	libfwps_set_t *set                    = NULL;
	uint8_t guid_data[ 16 ]               = { 0 };
	int number_of_records                 = 0;
	int record_index                      = 0;

	if( libfwps_set_initialize(
	     &set,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	libfwps_set_copy_from_byte_stream(
	 set,
	 data,
	 size,
	 ossfuzz_get_ascii_codepage( size ),
	 NULL );

	if( libfwps_set_get_number_of_records(
	     set,
	     &number_of_records,
	     NULL ) == 1 )
	{
		for( record_index = 0;
		     record_index < number_of_records;
		     record_index++ )
		{
			record = NULL;

			if( libfwps_set_get_record_by_index(
			     set,
			     record_index,
			     &record,
			     NULL ) != 1
			 || record == NULL )
			{
				continue;
			}
			libfwps_record_free(
			 &record,
			 NULL );
		}
	}
	libfwps_set_get_identifier(
	 set,
	 guid_data,
	 16,
	 NULL );
	libfwps_format_class_identifier_get_identifier(
	 guid_data );
	libfwps_format_class_identifier_get_description(
	 guid_data );

	libfwps_set_free(
	 &set,
	 NULL );

	return( 0 );
}

} /* extern "C" */
