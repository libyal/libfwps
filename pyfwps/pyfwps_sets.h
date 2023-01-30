/*
 * Python object definition of the sequence and iterator object of sets
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

#if !defined( _PYFWPS_SETS_H )
#define _PYFWPS_SETS_H

#include <common.h>
#include <types.h>

#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwps_sets pyfwps_sets_t;

struct pyfwps_sets
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyfwps_sets_type_object;

PyObject *pyfwps_sets_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyfwps_sets_init(
     pyfwps_sets_t *sequence_object );

void pyfwps_sets_free(
      pyfwps_sets_t *sequence_object );

Py_ssize_t pyfwps_sets_len(
            pyfwps_sets_t *sequence_object );

PyObject *pyfwps_sets_getitem(
           pyfwps_sets_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyfwps_sets_iter(
           pyfwps_sets_t *sequence_object );

PyObject *pyfwps_sets_iternext(
           pyfwps_sets_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWPS_SETS_H ) */

