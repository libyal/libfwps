/*
 * Library storage type testing program
 *
 * Copyright (C) 2013-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
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

/* Tests the libfwps_storage_initialize function
 * Returns 1 if successful or 0 if not
 */
int fwps_test_storage_initialize(
     void )
{
	libcerror_error_t *error   = NULL;
	libfwps_storage_t *storage = NULL;
	int result                 = 0;

	/* Test libfwps_storage_initialize
	 */
	result = libfwps_storage_initialize(
	          &storage,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FWPS_TEST_ASSERT_IS_NOT_NULL(
         "storage",
         storage );

        FWPS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libfwps_storage_free(
	          &storage,
	          &error );

	FWPS_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        FWPS_TEST_ASSERT_IS_NULL(
         "storage",
         storage );

        FWPS_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libfwps_storage_initialize(
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

	storage = (libfwps_storage_t *) 0x12345678UL;

	result = libfwps_storage_initialize(
	          &storage,
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

	storage = NULL;

#if defined( HAVE_FWPS_TEST_MEMORY )

	/* Test libfwps_storage_initialize with malloc failing
	 */
	fwps_test_malloc_attempts_before_fail = 0;

	result = libfwps_storage_initialize(
	          &storage,
	          &error );

	if( fwps_test_malloc_attempts_before_fail != -1 )
	{
		fwps_test_malloc_attempts_before_fail = -1;

		if( storage != NULL )
		{
			libfwps_storage_free(
			 &storage,
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
		 "storage",
		 storage );

		FWPS_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libfwps_storage_initialize with memset failing
	 */
	fwps_test_memset_attempts_before_fail = 0;

	result = libfwps_storage_initialize(
	          &storage,
	          &error );

	if( fwps_test_memset_attempts_before_fail != -1 )
	{
		fwps_test_memset_attempts_before_fail = -1;

		if( storage != NULL )
		{
			libfwps_storage_free(
			 &storage,
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
		 "storage",
		 storage );

		FWPS_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_FWPS_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( storage != NULL )
	{
		libfwps_storage_free(
		 &storage,
		 NULL );
	}
	return( 0 );
}

/* Tests the libfwps_storage_free function
 * Returns 1 if successful or 0 if not
 */
int fwps_test_storage_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libfwps_storage_free(
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
	FWPS_TEST_UNREFERENCED_PARAMETER( argc )
	FWPS_TEST_UNREFERENCED_PARAMETER( argv )

	FWPS_TEST_RUN(
	 "libfwps_storage_initialize",
	 fwps_test_storage_initialize );

	FWPS_TEST_RUN(
	 "libfwps_storage_free",
	 fwps_test_storage_free );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

