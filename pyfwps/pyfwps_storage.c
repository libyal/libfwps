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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwps_error.h"
#include "pyfwps_libcerror.h"
#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"
#include "pyfwps_storage.h"
#include "pyfwps_unused.h"

PyMethodDef pyfwps_storage_object_methods[] = {

	{ "copy_from_byte_stream",
	  (PyCFunction) pyfwps_storage_copy_from_byte_stream,
	  METH_VARARGS | METH_KEYWORDS,
	  "copy_from_byte_stream(byte_stream)\n"
	  "\n"
	  "Copies the storage from the byte stream." },

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

/* Initializes a storage object
 * Returns 0 if successful or -1 on error
 */
int pyfwps_storage_init(
     pyfwps_storage_t *pyfwps_storage )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwps_storage_init";

	if( pyfwps_storage == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid storage.",
		 function );

		return( -1 );
	}
	/* Make sure libfwps storage is set to NULL
	 */
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
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwps_storage_free";
	int result                  = 0;

	if( pyfwps_storage == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid storage.",
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
	if( pyfwps_storage->storage != NULL )
	{
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
			 "%s: unable to free libfwps storage.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pyfwps_storage );
}

/* Copies the storage from a byte stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_storage_copy_from_byte_stream(
           pyfwps_storage_t *pyfwps_storage,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *bytes_object      = NULL;
	libcerror_error_t *error    = NULL;
	const char *byte_stream     = NULL;
	static char *function       = "pyfwps_storage_copy_from_byte_stream";
	static char *keyword_list[] = { "byte_stream", NULL };
	Py_ssize_t byte_stream_size = 0;
	int result                  = 0;

	if( pyfwps_storage == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid storage.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O",
	     keyword_list,
	     &bytes_object ) == 0 )
	{
		return( NULL );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          bytes_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          bytes_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyfwps_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if object is of type bytes.",
		 function );

		return( NULL );
	}
	else if( result == 0 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported bytes object type",
		 function );

		return( NULL );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	byte_stream = PyBytes_AsString(
	               bytes_object );

	byte_stream_size = PyBytes_Size(
	                    bytes_object );
#else
	byte_stream = PyString_AsString(
	               bytes_object );

	byte_stream_size = PyString_Size(
	                    bytes_object );
#endif
	if( ( byte_stream_size < 0 )
	 || ( byte_stream_size > (Py_ssize_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid byte stream size value out of bounds.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_storage_copy_from_byte_stream(
	          pyfwps_storage->storage,
	          (uint8_t *) byte_stream,
	          (size_t) byte_stream_size,
	          LIBFWPS_ENDIAN_LITTLE,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to copy storage from byte stream.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

