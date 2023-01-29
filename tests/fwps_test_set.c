/*
 * Library set type test program
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

uint8_t fwps_test_set_data1[ 141 ] = {
	0x89, 0x00, 0x00, 0x00, 0x31, 0x53, 0x50, 0x53, 0xe2, 0x8a, 0x58, 0x46, 0xbc, 0x4c, 0x38, 0x43,
	0xbb, 0xfc, 0x13, 0x93, 0x26, 0x98, 0x6d, 0xce, 0x6d, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x00, 0x1f, 0x00, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x53, 0x00, 0x2d, 0x00, 0x31, 0x00, 0x2d,
	0x00, 0x35, 0x00, 0x2d, 0x00, 0x32, 0x00, 0x31, 0x00, 0x2d, 0x00, 0x34, 0x00, 0x30, 0x00, 0x36,
	0x00, 0x30, 0x00, 0x32, 0x00, 0x38, 0x00, 0x39, 0x00, 0x33, 0x00, 0x32, 0x00, 0x33, 0x00, 0x2d,
	0x00, 0x31, 0x00, 0x39, 0x00, 0x39, 0x00, 0x37, 0x00, 0x30, 0x00, 0x31, 0x00, 0x30, 0x00, 0x32,
	0x00, 0x32, 0x00, 0x2d, 0x00, 0x33, 0x00, 0x39, 0x00, 0x32, 0x00, 0x34, 0x00, 0x38, 0x00, 0x30,
	0x00, 0x31, 0x00, 0x36, 0x00, 0x38, 0x00, 0x31, 0x00, 0x2d, 0x00, 0x31, 0x00, 0x30, 0x00, 0x30,
	0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* Tests the libfwps_set_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwps_test_set_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libfwps_set_t *set              = NULL;
	int result                      = 0;

#if defined( HAVE_FWPS_TEST_MEMORY )
	int number_of_malloc_fail_tests = 2;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libfwps_set_initialize(
	          &set,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "set",
	 set );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfwps_set_free(
	          &set,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "set",
	 set );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwps_set_initialize(
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

	set = (libfwps_set_t *) 0x12345678UL;

	result = libfwps_set_initialize(
	          &set,
	          &error );

	set = NULL;

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
		/* Test libfwps_set_initialize with malloc failing
		 */
		fwps_test_malloc_attempts_before_fail = test_number;

		result = libfwps_set_initialize(
		          &set,
		          &error );

		if( fwps_test_malloc_attempts_before_fail != -1 )
		{
			fwps_test_malloc_attempts_before_fail = -1;

			if( set != NULL )
			{
				libfwps_set_free(
				 &set,
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
			 "set",
			 set );

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
		/* Test libfwps_set_initialize with memset failing
		 */
		fwps_test_memset_attempts_before_fail = test_number;

		result = libfwps_set_initialize(
		          &set,
		          &error );

		if( fwps_test_memset_attempts_before_fail != -1 )
		{
			fwps_test_memset_attempts_before_fail = -1;

			if( set != NULL )
			{
				libfwps_set_free(
				 &set,
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
			 "set",
			 set );

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
	if( set != NULL )
	{
		libfwps_set_free(
		 &set,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwps_set_free function
 * Returns 1 if successful or 0 if not
 */
int fwps_test_set_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwps_set_free(
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

/* Tests the libfwps_set_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int fwps_test_set_copy_from_byte_stream(
     void )
{
	libcerror_error_t *error = NULL;
	libfwps_set_t *set       = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libfwps_set_initialize(
	          &set,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NOT_NULL(
	 "set",
	 set );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libfwps_set_copy_from_byte_stream(
	          set,
	          fwps_test_set_data1,
	          141,
	          LIBFWPS_CODEPAGE_WINDOWS_1252,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libfwps_set_copy_from_byte_stream(
	          NULL,
	          fwps_test_set_data1,
	          141,
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

	result = libfwps_set_copy_from_byte_stream(
	          set,
	          NULL,
	          141,
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

	result = libfwps_set_copy_from_byte_stream(
	          set,
	          fwps_test_set_data1,
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

	result = libfwps_set_copy_from_byte_stream(
	          set,
	          fwps_test_set_data1,
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
	result = libfwps_set_free(
	          &set,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FWPS_TEST_ASSERT_IS_NULL(
	 "set",
	 set );

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
	if( set != NULL )
	{
		libfwps_set_free(
		 &set,
		 NULL );
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
	FWPS_TEST_UNREFERENCED_PARAMETER( argc )
	FWPS_TEST_UNREFERENCED_PARAMETER( argv )

	FWPS_TEST_RUN(
	 "libfwps_set_initialize",
	 fwps_test_set_initialize );

	FWPS_TEST_RUN(
	 "libfwps_set_free",
	 fwps_test_set_free );

	FWPS_TEST_RUN(
	 "libfwps_set_copy_from_byte_stream",
	 fwps_test_set_copy_from_byte_stream );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

