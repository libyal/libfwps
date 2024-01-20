/*
 * Property identifier functions
 *
 * Copyright (C) 2013-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFWPS_PROPERTY_IDENTIFIER_H )
#define _LIBFWPS_PROPERTY_IDENTIFIER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_DEBUG_OUTPUT )

typedef struct libfwps_property_identifier libfwps_property_identifier_t;

struct libfwps_property_identifier
{
	/* The entry type
	 */
	uint32_t entry_type;

	/* The value type
	 */
	uint32_t value_type;

	/* The identifier
	 */
	const char *identifier;

	/* The description
	 */
	const char *description;
};

const char *libfwps_property_identifiers_get_identifier(
             libfwps_property_identifier_t libfwps_property_identifiers[],
             uint32_t entry_type,
             uint32_t value_type );

const char *libfwps_property_identifier_get_identifier(
             const uint8_t *format_class_identifier,
             uint32_t entry_type,
             uint32_t value_type );

const char *libfwps_property_identifiers_get_description(
             libfwps_property_identifier_t libfwps_property_identifiers[],
             uint32_t entry_type,
             uint32_t value_type );

const char *libfwps_property_identifier_get_description(
             const uint8_t *format_class_identifier,
             uint32_t entry_type,
             uint32_t value_type );

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFWPS_PROPERTY_IDENTIFIER_H ) */

