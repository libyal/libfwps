/*
 * Python bindings module for libfwps (pyfwps)
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
#include <types.h>

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include "pyfwps.h"
#include "pyfwps_error.h"
#include "pyfwps_libcerror.h"
#include "pyfwps_libcstring.h"
#include "pyfwps_libfwps.h"
#include "pyfwps_python.h"
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
	{ NULL,
	  NULL,
	  0,
	  NULL}
};

/* Retrieves the pyfwps/libfwps version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwps_get_version(
           PyObject *self PYFWSI_ATTRIBUTE_UNUSED,
           PyObject *arguments PYFWSI_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYFWSI_UNREFERENCED_PARAMETER( self )
	PYFWSI_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libfwps_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = libcstring_narrow_string_length(
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

/* Declarations for DLL import/export
 */
#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif

/* Initializes the pyfwps module
 */
PyMODINIT_FUNC initpyfwps(
                void )
{
	PyObject *module                 = NULL;
#ifdef TODO
	PyTypeObject *volume_type_object = NULL;
#endif
	PyGILState_STATE gil_state       = 0;

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
	module = Py_InitModule3(
	          "pyfwps",
	          pyfwps_module_methods,
	          "Python libfwps module (pyfwps)." );

	PyEval_InitThreads();

	gil_state = PyGILState_Ensure();

#ifdef TODO
	/* Setup the volume type object
	 */
	pyfwps_volume_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwps_volume_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwps_volume_type_object );

	volume_type_object = &pyfwps_volume_type_object;

	PyModule_AddObject(
	 module,
	 "volume",
	 (PyObject *) volume_type_object );
#endif

on_error:
	PyGILState_Release(
	 gil_state );
}

