/*
 * OSS-Fuzz target for libfwps store type
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
	libfwps_set_t *set                    = NULL;
	libfwps_store_t *store                = NULL;
	uint8_t guid_data[ 16 ]               = { 0 };
	int number_of_sets                    = 0;
	int set_index                         = 0;

	if( libfwps_store_initialize(
	     &store,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	libfwps_store_copy_from_byte_stream(
	 store,
	 data,
	 size,
	 ossfuzz_get_ascii_codepage( size ),
	 NULL );

	if( libfwps_store_get_number_of_sets(
	     store,
	     &number_of_sets,
	     NULL ) == 1 )
	{
		for( set_index = 0;
		     set_index < number_of_sets;
		     set_index++ )
		{
			set = NULL;

			if( libfwps_store_get_set_by_index(
			     store,
			     set_index,
			     &set,
			     NULL ) != 1
			 || set == NULL )
			{
				continue;
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
		}
	}
	libfwps_store_free(
	 &store,
	 NULL );

	return( 0 );
}

} /* extern "C" */
