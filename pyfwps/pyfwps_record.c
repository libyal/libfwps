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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwps_error.h"
#include "pyfwps_guid.h"
#include "pyfwps_integer.h"
#include "pyfwps_libcerror.h"
#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"
#include "pyfwps_record.h"
#include "pyfwps_unused.h"

PyMethodDef pyfwps_record_object_methods[] = {

	{ "get_entry_type",
	  (PyCFunction) pyfwps_record_get_entry_type,
	  METH_NOARGS,
	  "get_entry_type() -> Integer or None\n"
	  "\n"
	  "Retrieves the entry type." },

	{ "get_value_type",
	  (PyCFunction) pyfwps_record_get_value_type,
	  METH_NOARGS,
	  "get_value_type() -> Integer\n"
	  "\n"
	  "Retrieves the value type." },

	{ "get_data_as_boolean",
	  (PyCFunction) pyfwps_record_get_data_as_boolean,
	  METH_NOARGS,
	  "get_data_as_boolean() -> Integer\n"
	  "\n"
	  "Retrieves the data as a boolean." },

	{ "get_data_as_integer",
	  (PyCFunction) pyfwps_record_get_data_as_integer,
	  METH_NOARGS,
	  "get_data_as_integer() -> Integer\n"
	  "\n"
	  "Retrieves the data as an integer." },

	{ "get_data_as_floating_point",
	  (PyCFunction) pyfwps_record_get_data_as_floating_point,
	  METH_NOARGS,
	  "get_data_as_floating_point() -> Float\n"
	  "\n"
	  "Retrieves the data as a floating point." },

	{ "get_data_as_string",
	  (PyCFunction) pyfwps_record_get_data_as_string,
	  METH_NOARGS,
	  "get_data_as_string() -> Unicode string\n"
	  "\n"
	  "Retrieves the data as a string." },

	{ "get_data_as_guid",
	  (PyCFunction) pyfwps_record_get_data_as_guid,
	  METH_NOARGS,
	  "get_data_as_guid() -> Unicode string\n"
	  "\n"
	  "Retrieves the data as a GUID value." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwps_record_object_get_set_definitions[] = {

	{ "entry_type",
	  (getter) pyfwps_record_get_entry_type,
	  (setter) 0,
	  "The entry type.",
	  NULL },

	{ "value_type",
	  (getter) pyfwps_record_get_value_type,
	  (setter) 0,
	  "The value type.",
	  NULL },

	{ "data_as_boolean",
	  (getter) pyfwps_record_get_data_as_boolean,
	  (setter) 0,
	  "The data as a boolean.",
	  NULL },

	{ "data_as_integer",
	  (getter) pyfwps_record_get_data_as_integer,
	  (setter) 0,
	  "The data as an integer.",
	  NULL },

	{ "data_as_floating_point",
	  (getter) pyfwps_record_get_data_as_floating_point,
	  (setter) 0,
	  "The data as a floating point.",
	  NULL },

	{ "data_as_string",
	  (getter) pyfwps_record_get_data_as_string,
	  (setter) 0,
	  "The data as a string.",
	  NULL },

	{ "data_as_guid",
	  (getter) pyfwps_record_get_data_as_guid,
	  (setter) 0,
	  "The data as a GUID value.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwps_record_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfwps.record",
	/* tp_basicsize */
	sizeof( pyfwps_record_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwps_record_free,
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
	"pyfwps record object (wraps libfwps_record_t)",
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
	pyfwps_record_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwps_record_object_get_set_definitions,
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
	(initproc) pyfwps_record_init,
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

/* Creates a new record object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_record_new(
           libfwps_record_t *record,
           PyObject *parent_object )
{
	pyfwps_record_t *pyfwps_record = NULL;
	static char *function          = "pyfwps_record_new";

	if( record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyfwps_record = PyObject_New(
	                 struct pyfwps_record,
	                 &pyfwps_record_type_object );

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize record.",
		 function );

		goto on_error;
	}
	pyfwps_record->record        = record;
	pyfwps_record->parent_object = parent_object;

	if( pyfwps_record->parent_object != NULL )
	{
		Py_IncRef(
		 pyfwps_record->parent_object );
	}
	return( (PyObject *) pyfwps_record );

on_error:
	if( pyfwps_record != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwps_record );
	}
	return( NULL );
}

/* Initializes a record object
 * Returns 0 if successful or -1 on error
 */
int pyfwps_record_init(
     pyfwps_record_t *pyfwps_record )
{
	static char *function = "pyfwps_record_init";

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return( -1 );
	}
	/* Make sure libfwps record is set to NULL
	 */
	pyfwps_record->record = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of record not supported.",
	 function );

	return( -1 );
}

/* Frees a record object
 */
void pyfwps_record_free(
      pyfwps_record_t *pyfwps_record )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwps_record_free";
	int result                  = 0;

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfwps_record );

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
	if( pyfwps_record->record != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libfwps_record_free(
		          &( pyfwps_record->record ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyfwps_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libfwps record.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyfwps_record->parent_object != NULL )
	{
		Py_DecRef(
		 pyfwps_record->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfwps_record );
}

/* Retrieves the entry type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_record_get_entry_type(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwps_record_get_entry_type";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_record_get_entry_type(
	          pyfwps_record->record,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve entry type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the value type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_record_get_value_type(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwps_record_get_value_type";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_record_get_value_type(
	          pyfwps_record->record,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the data as a boolean value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_record_get_data_as_boolean(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwps_record_get_data_as_boolean";
	uint8_t value_boolean    = 0;
	int result               = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_record_get_data_as_boolean(
	          pyfwps_record->record,
	          &value_boolean,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve boolean value.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( value_boolean != 0x00 )
	{
		Py_IncRef(
		 Py_True );

		return( Py_True );
	}
	Py_IncRef(
	 Py_False );

	return( Py_False );
}

/* Retrieves the data as an integer value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_record_get_data_as_integer(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwps_record_get_data_as_integer";
	uint64_t value_64bit     = 0;
	uint32_t value_32bit     = 0;
	uint32_t value_type      = 0;
	uint16_t value_16bit     = 0;
	uint8_t value_8bit       = 0;
	int result               = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_record_get_value_type(
	          pyfwps_record->record,
	          &value_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve value type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( value_type )
	{
		case LIBFWPS_VALUE_TYPE_INTEGER_8BIT_SIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libfwps_record_get_data_as_8bit_integer(
			          pyfwps_record->record,
			          &value_8bit,
			          &error );

			Py_END_ALLOW_THREADS

#if PY_MAJOR_VERSION >= 3
			integer_object = PyLong_FromLong(
			                  (long) ( (int8_t) value_8bit ) );
#else
			integer_object = PyInt_FromLong(
			                  (long) ( (int8_t) value_8bit ) );
#endif
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_8BIT_UNSIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libfwps_record_get_data_as_8bit_integer(
			          pyfwps_record->record,
			          &value_8bit,
			          &error );

			Py_END_ALLOW_THREADS

			integer_object = PyLong_FromUnsignedLong(
			                  (unsigned long) value_8bit );
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_16BIT_SIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libfwps_record_get_data_as_16bit_integer(
			          pyfwps_record->record,
			          &value_16bit,
			          &error );

			Py_END_ALLOW_THREADS

#if PY_MAJOR_VERSION >= 3
			integer_object = PyLong_FromLong(
			                  (long) ( (int16_t) value_16bit ) );
#else
			integer_object = PyInt_FromLong(
			                  (long) ( (int16_t) value_16bit ) );
#endif
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_16BIT_UNSIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libfwps_record_get_data_as_16bit_integer(
			          pyfwps_record->record,
			          &value_16bit,
			          &error );

			Py_END_ALLOW_THREADS

			integer_object = PyLong_FromUnsignedLong(
			                  (unsigned long) value_16bit );
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_32BIT_SIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libfwps_record_get_data_as_32bit_integer(
			          pyfwps_record->record,
			          &value_32bit,
			          &error );

			Py_END_ALLOW_THREADS

#if PY_MAJOR_VERSION >= 3
			integer_object = PyLong_FromLong(
			                  (long) ( (int32_t) value_32bit ) );
#else
			integer_object = PyInt_FromLong(
			                  (long) ( (int32_t) value_32bit ) );
#endif
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_32BIT_UNSIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libfwps_record_get_data_as_32bit_integer(
			          pyfwps_record->record,
			          &value_32bit,
			          &error );

			Py_END_ALLOW_THREADS

			integer_object = PyLong_FromUnsignedLong(
			                  (unsigned long) value_32bit );
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_64BIT_SIGNED:
			Py_BEGIN_ALLOW_THREADS

			result = libfwps_record_get_data_as_64bit_integer(
			          pyfwps_record->record,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			integer_object = pyfwps_integer_signed_new_from_64bit(
			                  (int64_t) value_64bit );

			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_64BIT_UNSIGNED:
		case LIBFWPS_VALUE_TYPE_FILETIME:
			Py_BEGIN_ALLOW_THREADS

			result = libfwps_record_get_data_as_filetime(
			          pyfwps_record->record,
			          &value_64bit,
			          &error );

			Py_END_ALLOW_THREADS

			integer_object = pyfwps_integer_unsigned_new_from_64bit(
			                  value_64bit );
			break;

		default:
			PyErr_Format(
			 PyExc_IOError,
			 "%s: value is not an integer type.",
			 function );

			return( NULL );
	}
	if( result == -1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve integer value.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( integer_object );
}

/* Retrieves the data as an floating-point value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_record_get_data_as_floating_point(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	PyObject *float_object      = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyfwps_record_get_data_as_floating_point";
	double floating_point_value = 0;
	int result                  = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_record_get_data_as_floating_point(
	          pyfwps_record->record,
	          &floating_point_value,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data as floating-point value.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	float_object = PyFloat_FromDouble(
	                floating_point_value );

	return( float_object );
}

/* Retrieves the data as a string
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_record_get_data_as_string(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pyfwps_value_get_data_as_string";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_record_get_data_as_utf8_string_size(
	          pyfwps_record->record,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of data as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (char *) PyMem_Malloc(
	                        sizeof( char ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_record_get_data_as_utf8_string(
	          pyfwps_record->record,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data as UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string.
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

/* Retrieves the data as a GUID value
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_record_get_data_as_guid(
           pyfwps_record_t *pyfwps_record,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwps_record_get_data_as_guid";
	int result               = 0;

	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	if( pyfwps_record == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid record.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwps_record_get_data_as_guid(
	          pyfwps_record->record,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwps_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data as a GUID value.",
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

