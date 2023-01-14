/*
 * Format class identifier functions
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

#if !defined( _LIBFWPS_FORMAT_CLASS_IDENTIFIER_H )
#define _LIBFWPS_FORMAT_CLASS_IDENTIFIER_H

#include <common.h>
#include <types.h>

#include "libfwps_extern.h"
#include "libfwps_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

/* The CLSID is stored as a little endian GUID
 */
typedef struct libfwps_format_class_identifier_definition libfwps_format_class_identifier_definition_t;

struct libfwps_format_class_identifier_definition
{
	/* The class identifier
	 */
	uint8_t *class_identifier;

	/* The identifier
	 */
	const char *identifier;

	/* The description
	 */
	const char *description;
};

extern uint8_t libfwps_format_class_identifier_document_summary_information[ 16 ];
extern uint8_t libfwps_format_class_identifier_summary_information[ 16 ];

LIBFWPS_EXTERN \
const char *libfwps_format_class_identifier_get_identifier(
             const uint8_t *format_class_identifier );

LIBFWPS_EXTERN \
const char *libfwps_format_class_identifier_get_description(
             const uint8_t *format_class_identifier );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWPS_FORMAT_CLASS_IDENTIFIER_H ) */

