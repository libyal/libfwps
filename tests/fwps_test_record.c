/*
 * Library record type test program
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

#include "../libfwps/libfwps_definitions.h"
#include "../libfwps/libfwps_record.h"

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

#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

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

#if defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT )

	FWPS_TEST_RUN(
	 "libfwps_record_initialize",
	 fwps_test_record_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

	FWPS_TEST_RUN(
	 "libfwps_record_free",
	 fwps_test_record_free );

#if defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT )

	/* TODO: add tests for libfwps_record_copy_from_byte_stream */

#endif /* defined( __GNUC__ ) && !defined( LIBFWPS_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

