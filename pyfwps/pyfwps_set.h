/*
 * Python object wrapper of libfwps_set_t
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

#if !defined( _PYFWPS_SET_H )
#define _PYFWPS_SET_H

#include <common.h>
#include <types.h>

#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwps_set pyfwps_set_t;

struct pyfwps_set
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwps set
	 */
	libfwps_set_t *set;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwps_set_object_methods[];
extern PyTypeObject pyfwps_set_type_object;

PyObject *pyfwps_set_new(
           libfwps_set_t *set,
           PyObject *parent_object );

int pyfwps_set_init(
     pyfwps_set_t *pyfwps_set );

void pyfwps_set_free(
      pyfwps_set_t *pyfwps_set );

PyObject *pyfwps_set_copy_from_byte_stream(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfwps_set_get_identifier(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments );

PyObject *pyfwps_set_get_number_of_records(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments );

PyObject *pyfwps_set_get_record_by_index(
           PyObject *pyfwps_set,
           int record_index );

PyObject *pyfwps_set_get_record(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyfwps_set_get_records(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWPS_SET_H ) */

