/*
 * Python bindings module for libfwps (pyfwps)
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfwps.h"
#include "pyfwps_error.h"
#include "pyfwps_libcerror.h"
#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"
#include "pyfwps_record.h"
#include "pyfwps_records.h"
#include "pyfwps_set.h"
#include "pyfwps_sets.h"
#include "pyfwps_storage.h"
#include "pyfwps_store.h"
#include "pyfwps_unused.h"

/* The pyfwps module methods
 */
PyMethodDef pyfwps_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pyfwps_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pyfwps/libfwps version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_get_version(
           PyObject *self PYFWPS_ATTRIBUTE_UNUSED,
           PyObject *arguments PYFWPS_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYFWPS_UNREFERENCED_PARAMETER( self )
	PYFWPS_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libfwps_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

#if PY_MAJOR_VERSION >= 3

/* The pyfwps module definition
 */
PyModuleDef pyfwps_module_definition = {
	PyModuleDef_HEAD_INIT,

	/* m_name */
	"pyfwps",
	/* m_doc */
	"Python libfwps module (pyfwps).",
	/* m_size */
	-1,
	/* m_methods */
	pyfwps_module_methods,
	/* m_reload */
	NULL,
	/* m_traverse */
	NULL,
	/* m_clear */
	NULL,
	/* m_free */
	NULL,
};

#endif /* PY_MAJOR_VERSION >= 3 */

/* Initializes the pyfwps module
 */
#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pyfwps(
                void )
#else
PyMODINIT_FUNC initpyfwps(
                void )
#endif
{
	PyObject *module           = NULL;
	PyGILState_STATE gil_state = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libfwps_notify_set_stream(
	 stderr,
	 NULL );
	libfwps_notify_set_verbose(
	 1 );
#endif

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(
	          &pyfwps_module_definition );
#else
	module = Py_InitModule3(
	          "pyfwps",
	          pyfwps_module_methods,
	          "Python libfwps module (pyfwps)." );
#endif
	if( module == NULL )
	{
#if PY_MAJOR_VERSION >= 3
		return( NULL );
#else
		return;
#endif
	}
#if PY_VERSION_HEX < 0x03070000
	PyEval_InitThreads();
#endif
	gil_state = PyGILState_Ensure();

	/* Setup the record type object
	 */
	pyfwps_record_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwps_record_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwps_record_type_object );

	PyModule_AddObject(
	 module,
	 "record",
	 (PyObject *) &pyfwps_record_type_object );

	/* Setup the records type object
	 */
	pyfwps_records_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwps_records_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwps_records_type_object );

	PyModule_AddObject(
	 module,
	 "records",
	 (PyObject *) &pyfwps_records_type_object );

	/* Setup the set type object
	 */
	pyfwps_set_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwps_set_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwps_set_type_object );

	PyModule_AddObject(
	 module,
	 "set",
	 (PyObject *) &pyfwps_set_type_object );

	/* Setup the sets type object
	 */
	pyfwps_sets_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwps_sets_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwps_sets_type_object );

	PyModule_AddObject(
	 module,
	 "sets",
	 (PyObject *) &pyfwps_sets_type_object );

	/* Setup the storage type object
	 */
	pyfwps_storage_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwps_storage_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwps_storage_type_object );

	PyModule_AddObject(
	 module,
	 "storage",
	 (PyObject *) &pyfwps_storage_type_object );

	/* Setup the store type object
	 */
	pyfwps_store_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwps_store_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwps_store_type_object );

	PyModule_AddObject(
	 module,
	 "store",
	 (PyObject *) &pyfwps_store_type_object );

	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( module );
#else
	return;
#endif

on_error:
	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( NULL );
#else
	return;
#endif
}

