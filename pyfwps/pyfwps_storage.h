/*
 * Python object definition of the libfwps storage
 *
 * Copyright (C) 2014-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _PYFWPS_STORAGE_H )
#define _PYFWPS_STORAGE_H

#include <common.h>
#include <types.h>

#include "pyfwps_libcerror.h"
#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyfwps_storage pyfwps_storage_t;

struct pyfwps_storage
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libfwps storage
	 */
	libfwps_storage_t *storage;
};

extern PyMethodDef pyfwps_storage_object_methods[];
extern PyTypeObject pyfwps_storage_type_object;

PyObject *pyfwps_storage_new(
           void );

int pyfwps_storage_init(
     pyfwps_storage_t *pyfwps_storage );

void pyfwps_storage_free(
      pyfwps_storage_t *pyfwps_storage );

#if defined( __cplusplus )
}
#endif

#endif

