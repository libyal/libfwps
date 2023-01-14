/*
 * Python object wrapper of libfwps_storage_t
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

#if !defined( _PYFWPS_STORAGE_H )
#define _PYFWPS_STORAGE_H

#include <common.h>
#include <types.h>

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

int pyfwps_storage_init(
     pyfwps_storage_t *pyfwps_storage );

void pyfwps_storage_free(
      pyfwps_storage_t *pyfwps_storage );

PyObject *pyfwps_storage_copy_from_byte_stream(
           pyfwps_storage_t *pyfwps_storage,
           PyObject *arguments,
           PyObject *keywords );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYFWPS_STORAGE_H ) */

