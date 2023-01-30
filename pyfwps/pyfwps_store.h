/*
 * Python object wrapper of libfwps_store_t
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

#if !defined( _PYFWPS_STORE_H )
#define _PYFWPS_STORE_H

#include <common.h>
#include <types.h>

#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwps_store pyfwps_store_t;

struct pyfwps_store
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwps store
	 */
	libfwps_store_t *store;
};

extern PyMethodDef pyfwps_store_object_methods[];
extern PyTypeObject pyfwps_store_type_object;

int pyfwps_store_init(
     pyfwps_store_t *pyfwps_store );

void pyfwps_store_free(
      pyfwps_store_t *pyfwps_store );

PyObject *pyfwps_store_copy_from_byte_stream(
           pyfwps_store_t *pyfwps_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfwps_store_get_number_of_sets(
           pyfwps_store_t *pyfwps_store,
           PyObject *arguments );

PyObject *pyfwps_store_get_set_by_index(
           PyObject *pyfwps_store,
           int set_index );

PyObject *pyfwps_store_get_set(
           pyfwps_store_t *pyfwps_store,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfwps_store_get_sets(
           pyfwps_store_t *pyfwps_store,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWPS_STORE_H ) */

