/*
 * Library record type test program
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "fwps_test_libcerror.h"
#include "fwps_test_libfwps.h"
#include "fwps_test_macros.h"
#include "fwps_test_memory.h"
#include "fwps_test_unused.h"

#include "../libfwps/libfwps_definitions.h"
#include "../libfwps/libfwps_record.h"

uint8_t fwps_test_record_data1[ 113 ] = {
	0x6d, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00,
	0x00, 0x53, 0x00, 0x2d, 0x00, 0x31, 0x00, 0x2d, 0x00, 0x35, 0x00, 0x2d, 0x00, 0x32, 0x00, 0x31,
	0x00, 0x2d, 0x00, 0x34, 0x00, 0x30, 0x00, 0x36, 0x00, 0x30, 0x00, 0x32, 0x00, 0x38, 0x00, 0x39,
	0x00, 0x33, 0x00, 0x32, 0x00, 0x33, 0x00, 0x2d, 0x00, 0x31, 0x00, 0x39, 0x00, 0x39, 0x00, 0x37,
	0x00, 0x30, 0x00, 0x31, 0x00, 0x30, 0x00, 0x32, 0x00, 0x32, 0x00, 0x2d, 0x00, 0x33, 0x00, 0x39,
	0x00, 0x32, 0x00, 0x34, 0x00, 0x38, 0x00, 0x30, 0x00, 0x31, 0x00, 0x36, 0x00, 0x38, 0x00, 0x31,
	0x00, 0x2d, 0x00, 0x31, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00 };

/* Record with value of type 0x101f
 */
uint8_t fwps_test_record_data2[ 281 ] = {
	0x19, 0x01, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00,
	0x00, 0x29, 0x00, 0x00, 0x00, 0x7b, 0x00, 0x46, 0x00, 0x32, 0x00, 0x39, 0x00, 0x46, 0x00, 0x38,
	0x00, 0x35, 0x00, 0x45, 0x00, 0x30, 0x00, 0x2d, 0x00, 0x34, 0x00, 0x46, 0x00, 0x46, 0x00, 0x39,
	0x00, 0x2d, 0x00, 0x31, 0x00, 0x30, 0x00, 0x36, 0x00, 0x38, 0x00, 0x2d, 0x00, 0x41, 0x00, 0x42,
	0x00, 0x39, 0x00, 0x31, 0x00, 0x2d, 0x00, 0x30, 0x00, 0x38, 0x00, 0x30, 0x00, 0x30, 0x00, 0x32,
	0x00, 0x42, 0x00, 0x32, 0x00, 0x37, 0x00, 0x42, 0x00, 0x33, 0x00, 0x44, 0x00, 0x39, 0x00, 0x7d,
	0x00, 0x2c, 0x00, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x7b, 0x00, 0x42,
	0x00, 0x37, 0x00, 0x32, 0x00, 0x35, 0x00, 0x46, 0x00, 0x31, 0x00, 0x33, 0x00, 0x30, 0x00, 0x2d,
	0x00, 0x34, 0x00, 0x37, 0x00, 0x45, 0x00, 0x46, 0x00, 0x2d, 0x00, 0x31, 0x00, 0x30, 0x00, 0x31,
	0x00, 0x41, 0x00, 0x2d, 0x00, 0x41, 0x00, 0x35, 0x00, 0x46, 0x00, 0x31, 0x00, 0x2d, 0x00, 0x30,
	0x00, 0x32, 0x00, 0x36, 0x00, 0x30, 0x00, 0x38, 0x00, 0x43, 0x00, 0x39, 0x00, 0x45, 0x00, 0x45,
	0x00, 0x42, 0x00, 0x41, 0x00, 0x43, 0x00, 0x7d, 0x00, 0x2c, 0x00, 0x31, 0x00, 0x30, 0x00, 0x00,
	0x00, 0x29, 0x00, 0x00, 0x00, 0x7b, 0x00, 0x46, 0x00, 0x32, 0x00, 0x39, 0x00, 0x46, 0x00, 0x38,
	0x00, 0x35, 0x00, 0x45, 0x00, 0x30, 0x00, 0x2d, 0x00, 0x34, 0x00, 0x46, 0x00, 0x46, 0x00, 0x39,
	0x00, 0x2d, 0x00, 0x31, 0x00, 0x30, 0x00, 0x36, 0x00, 0x38, 0x00, 0x2d, 0x00, 0x41, 0x00, 0x42,
	0x00, 0x39, 0x00, 0x31, 0x00, 0x2d, 0x00, 0x30, 0x00, 0x38, 0x00, 0x30, 0x00, 0x30, 0x00, 0x32,
	0x00, 0x42, 0x00, 0x32, 0x00, 0x37, 0x00, 0x42, 0x00, 0x33, 0x00, 0x44, 0x00, 0x39, 0x00, 0x7d,
	0x00, 0x2c, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT )

/* Tests the libfwps_record_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwps_test_record_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwps_record_t *record        = NULL;
	int result                      = 0;

#if defined( HAVE_FWPS_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwps_record_initialize(
	          &record,
	          LIBFWPS_RECORD_TYPE_NUMERIC,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwps_internal_record_free(
	          (libfwps_internal_record_t **) &record,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwps_record_initialize(
	          NULL,
	          LIBFWPS_RECORD_TYPE_NUMERIC,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	record = (libfwps_record_t *) 0x12345678UL;

	result = libfwps_record_initialize(
	          &record,
	          LIBFWPS_RECORD_TYPE_NUMERIC,
	          &error );

	record = NULL;

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FWPS_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libfwps_record_initialize with malloc failing
		 */
		fwps_test_malloc_attempts_before_fail = test_number;

		result = libfwps_record_initialize(
		          &record,
		          LIBFWPS_RECORD_TYPE_NUMERIC,
		          &error );

		if( fwps_test_malloc_attempts_before_fail != -1 )
		{
			fwps_test_malloc_attempts_before_fail = -1;

			if( record != NULL )
			{
				libfwps_internal_record_free(
				 (libfwps_internal_record_t **) &record,
				 NULL );
			}
		}
		else
		{
			FWPS_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FWPS_TEST_ASSERT_IS_NULL(
			 "record",
			 record );

			FWPS_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libfwps_record_initialize with memset failing
		 */
		fwps_test_memset_attempts_before_fail = test_number;

		result = libfwps_record_initialize(
		          &record,
		          LIBFWPS_RECORD_TYPE_NUMERIC,
		          &error );

		if( fwps_test_memset_attempts_before_fail != -1 )
		{
			fwps_test_memset_attempts_before_fail = -1;

			if( record != NULL )
			{
				libfwps_internal_record_free(
				 (libfwps_internal_record_t **) &record,
				 NULL );
			}
		}
		else
		{
			FWPS_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FWPS_TEST_ASSERT_IS_NULL(
			 "record",
			 record );

			FWPS_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FWPS_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( record != NULL )
	{
		libfwps_internal_record_free(
		 (libfwps_internal_record_t **) &record,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

/* Tests the libfwps_record_free function
 * Returns 1 if successful or 0 if not
 */
int fwps_test_record_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwps_record_free(
	          NULL,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT )

/* Tests the libfwps_record_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int fwps_test_record_copy_from_byte_stream(
     void )
{
	libcerror_error_t *error = NULL;
	libfwps_record_t *record = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfwps_record_initialize(
	          &record,
	          LIBFWPS_RECORD_TYPE_NUMERIC,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwps_record_copy_from_byte_stream(
	          record,
	          fwps_test_record_data1,
	          113,
	          LIBFWPS_CODEPAGE_WINDOWS_1252,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwps_internal_record_free(
	          (libfwps_internal_record_t **) &record,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwps_record_initialize(
	          &record,
	          LIBFWPS_RECORD_TYPE_NUMERIC,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwps_record_copy_from_byte_stream(
	          record,
	          fwps_test_record_data2,
	          281,
	          LIBFWPS_CODEPAGE_WINDOWS_1252,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libfwps_internal_record_free(
	          (libfwps_internal_record_t **) &record,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libfwps_record_initialize(
	          &record,
	          LIBFWPS_RECORD_TYPE_NUMERIC,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwps_record_copy_from_byte_stream(
	          NULL,
	          fwps_test_record_data1,
	          113,
	          LIBFWPS_CODEPAGE_WINDOWS_1252,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwps_record_copy_from_byte_stream(
	          record,
	          NULL,
	          113,
	          LIBFWPS_CODEPAGE_WINDOWS_1252,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwps_record_copy_from_byte_stream(
	          record,
	          fwps_test_record_data1,
	          (size_t) SSIZE_MAX + 1,
	          LIBFWPS_CODEPAGE_WINDOWS_1252,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwps_record_copy_from_byte_stream(
	          record,
	          fwps_test_record_data1,
	          0,
	          LIBFWPS_CODEPAGE_WINDOWS_1252,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* TODO: test with invalid codepage */

	/* Clean up
	 */
	result = libfwps_internal_record_free(
	          (libfwps_internal_record_t **) &record,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( record != NULL )
	{
		libfwps_internal_record_free(
		 (libfwps_internal_record_t **) &record,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

/* Tests the libfwps_record_get_value_type function
 * Returns 1 if successful or 0 if not
 */
int fwps_test_record_get_value_type(
     libfwps_record_t *record )
{
	libcerror_error_t *error = NULL;
	uint32_t value_type      = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libfwps_record_get_value_type(
	          record,
	          &value_type,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_EQUAL_UINT32(
	 "value_type",
	 value_type,
	 (uint32_t) 0x0000001fUL );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwps_record_get_value_type(
	          NULL,
	          &value_type,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libfwps_record_get_value_type(
	          record,
	          NULL,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FWPS_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FWPS_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FWPS_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FWPS_TEST_ATTRIBUTE_UNUSED )
#endif
{
#if defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT )
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	libcerror_error_t *error = NULL;
	libfwps_record_t *record = NULL;
	int result               = 0;
#endif
#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

	FWPS_TEST_UNREFERENCED_PARAMETER( argc )
	FWPS_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT )

	FWPS_TEST_RUN(
	 "libfwps_record_initialize",
	 fwps_test_record_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

	FWPS_TEST_RUN(
	 "libfwps_record_free",
	 fwps_test_record_free );

#if defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT )

	FWPS_TEST_RUN(
	 "libfwps_record_copy_from_byte_stream",
	 fwps_test_record_copy_from_byte_stream );

#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

#if defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT )
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize record for tests
	 */
	result = libfwps_record_initialize(
	          &record,
	          LIBFWPS_RECORD_TYPE_NUMERIC,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwps_record_copy_from_byte_stream(
	          record,
	          fwps_test_record_data1,
	          113,
	          LIBFWPS_CODEPAGE_WINDOWS_1252,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* TODO: add tests for libfwps_record_get_utf8_entry_name_size */
	/* TODO: add tests for libfwps_record_get_utf8_entry_name */
	/* TODO: add tests for libfwps_record_get_utf16_entry_name_size */
	/* TODO: add tests for libfwps_record_get_utf16_entry_name */
	/* TODO: add tests for libfwps_record_get_entry_type */
	/* TODO: add tests for libfwps_record_get_utf8_value_name_size */
	/* TODO: add tests for libfwps_record_get_utf8_value_name */
	/* TODO: add tests for libfwps_record_get_utf16_value_name_size */
	/* TODO: add tests for libfwps_record_get_utf16_value_name */

	FWPS_TEST_RUN_WITH_ARGS(
	 "libfwps_record_get_value_type",
	 fwps_test_record_get_value_type,
	 record );

	/* TODO: add tests for libfwps_record_get_data_size */
	/* TODO: add tests for libfwps_record_get_data */
	/* TODO: add tests for libfwps_record_get_data_as_boolean */
	/* TODO: add tests for libfwps_record_get_data_as_8bit_integer */
	/* TODO: add tests for libfwps_record_get_data_as_16bit_integer */
	/* TODO: add tests for libfwps_record_get_data_as_32bit_integer */
	/* TODO: add tests for libfwps_record_get_data_as_64bit_integer */
	/* TODO: add tests for libfwps_record_get_data_as_filetime */
	/* TODO: add tests for libfwps_record_get_data_as_floating_point */
	/* TODO: add tests for libfwps_record_get_data_as_utf8_string_size */
	/* TODO: add tests for libfwps_record_get_data_as_utf8_string */
	/* TODO: add tests for libfwps_record_get_data_as_utf16_string_size */
	/* TODO: add tests for libfwps_record_get_data_as_utf16_string */
	/* TODO: add tests for libfwps_record_get_data_as_utf8_path_string_size */
	/* TODO: add tests for libfwps_record_get_data_as_utf8_path_string */
	/* TODO: add tests for libfwps_record_get_data_as_utf16_path_string_size */
	/* TODO: add tests for libfwps_record_get_data_as_utf16_path_string */
	/* TODO: add tests for libfwps_record_get_data_as_guid */

	/* Clean up
	 */
	result = libfwps_internal_record_free(
	          (libfwps_internal_record_t **) &record,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
#if defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT )
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( record != NULL )
	{
		libfwps_internal_record_free(
		 (libfwps_internal_record_t **) &record,
		 NULL );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

	return( EXIT_FAILURE );
}

