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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwps_error.h"
#include "pyfwps_guid.h"
#include "pyfwps_libcerror.h"
#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"
#include "pyfwps_record.h"
#include "pyfwps_records.h"
#include "pyfwps_set.h"
#include "pyfwps_unused.h"

PyMethodDef pyfwps_set_object_methods[] = {

	{ "copy_from_byte_stream",
	  (PyCFunction) pyfwps_set_copy_from_byte_stream,
	  METH_VARARGS | METH_KEYWORDS,
	  "copy_from_byte_stream(byte_stream)\n"
	  "\n"
	  "Copies the set from the byte stream." },

	{ "get_identifier",
	  (PyCFunction) pyfwps_set_get_identifier,
	  METH_NOARGS,
	  "get_identifier() -> Unicode string\n"
	  "\n"
	  "Retrieves the identifier." },

	{ "get_number_of_records",
	  (PyCFunction) pyfwps_set_get_number_of_records,
	  METH_NOARGS,
	  "get_number_of_records() -> Integer\n"
	  "\n"
	  "Retrieves the number of records." },

	{ "get_record",
	  (PyCFunction) pyfwps_set_get_record,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_record(record_index) -> Object\n"
	  "\n"
	  "Retrieves the record specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwps_set_object_get_set_definitions[] = {

	{ "identifier",
	  (getter) pyfwps_set_get_identifier,
	  (setter) 0,
	  "The identifier.",
	  NULL },

	{ "number_of_records",
	  (getter) pyfwps_set_get_number_of_records,
	  (setter) 0,
	  "The number of records.",
	  NULL },

	{ "records",
	  (getter) pyfwps_set_get_records,
	  (setter) 0,
	  "The records.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwps_set_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwps.set",
	/* tp_basicsize */
	sizeof( pyfwps_set_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwps_set_free,
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
	"pyfwps set object (wraps libfwps_set_t)",
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
	pyfwps_set_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwps_set_object_get_set_definitions,
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
	(initproc) pyfwps_set_init,
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

/* Creates a new set object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_set_new(
           libfwps_set_t *set,
           PyObject *parent_object )
{
	pyfwps_set_t *pyfwps_set = NULL;
	static char *function    = "pyfwps_set_new";

	if( set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid set.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyfwps_set = PyObject_New(
	              struct pyfwps_set,
	              &pyfwps_set_type_object );

	if( pyfwps_set == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize set.",
		 function );

		goto on_error;
	}
	pyfwps_set->set           = set;
	pyfwps_set->parent_object = parent_object;

	if( pyfwps_set->parent_object != NULL )
	{
		Py_IncRef(
		 pyfwps_set->parent_object );
	}
	return( (PyObject *) pyfwps_set );

on_error:
	if( pyfwps_set != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwps_set );
	}
	return( NULL );
}

/* Initializes a set object
 * Returns 0 if successful or -1 on error
 */
int pyfwps_set_init(
     pyfwps_set_t *pyfwps_set )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwps_set_init";

	if( pyfwps_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid set.",
		 function );

		return( -1 );
	}
	/* Make sure libfwps set is set to NULL
	 */
	pyfwps_set->set = NULL;

	if( libfwps_set_initialize(
	     &( pyfwps_set->set ),
	     &error ) != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize set.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a set object
 */
void pyfwps_set_free(
      pyfwps_set_t *pyfwps_set )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwps_set_free";
	int result                  = 0;

	if( pyfwps_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid set.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwps_set );

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
	if( pyfwps_set->set != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libfwps_set_free(
		          &( pyfwps_set->set ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfwps_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libfwps set.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyfwps_set->parent_object != NULL )
	{
		Py_DecRef(
		 pyfwps_set->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwps_set );
}

/* Copies the set from a byte stream
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_set_copy_from_byte_stream(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *bytes_object      = NULL;
	libcerror_error_t *error    = NULL;
	const char *byte_stream     = NULL;
	static char *function       = "pyfwps_set_copy_from_byte_stream";
	static char *keyword_list[] = { "byte_stream", NULL };
	Py_ssize_t byte_stream_size = 0;
	int result                  = 0;

	if( pyfwps_set == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid set.",
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

	result = libfwps_set_copy_from_byte_stream(
	          pyfwps_set->set,
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
		 "%s: unable to copy set from byte stream.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_set_get_identifier(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwps_set_get_identifier";
	int result               = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid set.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_set_get_identifier(
	          pyfwps_set->set,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	string_object = pyfwps_string_new_from_guid(
	                 guid_data,
	                 16 );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert GUID into Unicode object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Retrieves the number of records
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_set_get_number_of_records(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwps_set_get_number_of_records";
	int number_of_records    = 0;
	int result               = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid set.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_set_get_number_of_records(
	          pyfwps_set->set,
	          &number_of_records,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of records.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_records );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_records );
#endif
	return( integer_object );
}

/* Retrieves a specific record by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_set_get_record_by_index(
           PyObject *pyfwps_set,
           int record_index )
{
	PyObject *record_object  = NULL;
	libcerror_error_t *error = NULL;
	libfwps_record_t *record = NULL;
	static char *function    = "pyfwps_set_get_record_by_index";
	int result               = 0;

	if( pyfwps_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid set.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_set_get_record_by_index(
	          ( (pyfwps_set_t *) pyfwps_set )->set,
	          record_index,
	          &record,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve record: %d.",
		 function,
		 record_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	record_object = pyfwps_record_new(
	                 record,
	                 pyfwps_set );

	if( record_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create record object.",
		 function );

		goto on_error;
	}
	return( record_object );

on_error:
	if( record != NULL )
	{
		libfwps_record_free(
		 &record,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific record
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_set_get_record(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *record_object     = NULL;
	static char *keyword_list[] = { "record_index", NULL };
	int record_index            = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &record_index ) == 0 )
	{
		return( NULL );
	}
	record_object = pyfwps_set_get_record_by_index(
	                 (PyObject *) pyfwps_set,
	                 record_index );

	return( record_object );
}

/* Retrieves a sequence and iterator object for the records
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_set_get_records(
           pyfwps_set_t *pyfwps_set,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyfwps_set_get_records";
	int number_of_records     = 0;
	int result                = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_set == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid set.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_set_get_number_of_records(
	          pyfwps_set->set,
	          &number_of_records,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of records.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyfwps_records_new(
	                   (PyObject *) pyfwps_set,
	                   &pyfwps_set_get_record_by_index,
	                   number_of_records );

	if( sequence_object == NULL )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

