/*
 * Python object wrapper of libfwps_record_t
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

#if !defined( _PYFWPS_RECORD_H )
#define _PYFWPS_RECORD_H

#include <common.h>
#include <types.h>

#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwps_record pyfwps_record_t;

struct pyfwps_record
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwps record
	 */
	libfwps_record_t *record;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyfwps_record_object_methods[];
extern PyTypeObject pyfwps_record_type_object;

PyObject *pyfwps_record_new(
           libfwps_record_t *record,
           PyObject *parent_object );

int pyfwps_record_init(
     pyfwps_record_t *pyfwps_record );

void pyfwps_record_free(
      pyfwps_record_t *pyfwps_record );

PyObject *pyfwps_record_get_entry_type(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments );

PyObject *pyfwps_record_get_value_type(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments );

PyObject *pyfwps_record_get_data_as_boolean(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments );

PyObject *pyfwps_record_get_data_as_integer(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments );

PyObject *pyfwps_record_get_data_as_floating_point(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments );

PyObject *pyfwps_record_get_data_as_string(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments );

PyObject *pyfwps_record_get_data_as_guid(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWPS_RECORD_H ) */

