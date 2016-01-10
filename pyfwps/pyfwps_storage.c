/*
 * Python object definition of the libfwps storage
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
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include "pyfwps_error.h"
#include "pyfwps_libcerror.h"
#include "pyfwps_libcstring.h"
#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"
#include "pyfwps_storage.h"
#include "pyfwps_unused.h"

PyMethodDef pyfwps_storage_object_methods[] = {

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwps_storage_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwps_storage_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwps.storage",
	/* tp_basicsize */
	sizeof( pyfwps_storage_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwps_storage_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyfwps storage object (wraps libfwps_storage_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyfwps_storage_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwps_storage_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyfwps_storage_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new pyfwps storage object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_storage_new(
           void )
{
	static char *function            = "pyfwps_storage_new";
	pyfwps_storage_t *pyfwps_storage = NULL;

	pyfwps_storage = PyObject_New(
	                  struct pyfwps_storage,
	                  &pyfwps_storage_type_object );

	if( pyfwps_storage == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize storage.",
		 function );

		goto on_error;
	}
	if( pyfwps_storage_init(
	     pyfwps_storage ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize storage.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pyfwps_storage );

on_error:
	if( pyfwps_storage != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwps_storage );
	}
	return( NULL );
}

/* Intializes a storage object
 * Returns 0 if successful or -1 on error
 */
int pyfwps_storage_init(
     pyfwps_storage_t *pyfwps_storage )
{
	static char *function    = "pyfwps_storage_init";
	libcerror_error_t *error = NULL;

	if( pyfwps_storage == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid storage.",
		 function );

		return( -1 );
	}
	pyfwps_storage->storage = NULL;

	if( libfwps_storage_initialize(
	     &( pyfwps_storage->storage ),
	     &error ) != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize storage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a storage object
 */
void pyfwps_storage_free(
      pyfwps_storage_t *pyfwps_storage )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyfwps_storage_free";
	int result                  = 0;

	if( pyfwps_storage == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid storage.",
		 function );

		return;
	}
	if( pyfwps_storage->storage == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid storage - missing libfwps storage.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwps_storage );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_storage_free(
	          &( pyfwps_storage->storage ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free storage.",
		 function );

		libcerror_error_free(
		 &error );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwps_storage );
}

