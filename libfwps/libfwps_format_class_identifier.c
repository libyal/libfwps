/*
 * Formal class identifier functions
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libfwps_format_class_identifier.h"
#include "libfwps_libcerror.h"

uint8_t libfwps_format_class_identifier_document_summary_information[ 16 ] = {
	0x02, 0xd5, 0xcd, 0xd5, 0x9c, 0x2e, 0x1b, 0x10, 0x93, 0x97, 0x08, 0x00, 0x2b, 0x2c, 0xf9, 0xae };

uint8_t libfwps_format_class_identifier_summary_information[ 16 ] = {
	0xe0, 0x85, 0x9f, 0xf2, 0xf9, 0x4f, 0x68, 0x10, 0xab, 0x91, 0x08, 0x00, 0x2b, 0x27, 0xb3, 0xd9 };

uint8_t libfwps_format_class_identifier_user_defined[ 16 ] = {
	0x05, 0xd5, 0xcd, 0xd5, 0x9c, 0x2e, 0x1b, 0x10, 0x93, 0x97, 0x08, 0x00, 0x2b, 0x2c, 0xf9, 0xae };

uint8_t libfwps_format_class_identifier_unknown[ 16 ] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

/* The format class identifiers
 */
libfwps_format_class_identifier_definition_t libfwps_format_class_identifier_definitions[ ] = {
	{ libfwps_format_class_identifier_document_summary_information,	"FMTID_DocumentSummaryInformation",	"Document summary information" },
	{ libfwps_format_class_identifier_summary_information,		"FMTID_SummaryInformation",		"Summary information" },
	{ libfwps_format_class_identifier_user_defined,			"FMTID_UserDefinedProperties",		"User defined" },

	{ libfwps_format_class_identifier_unknown,			"Unknown",				"Unknown" } };

/* Retrieves a string containing the identifier of the folder identifier
 */
const char *libfwps_format_class_identifier_get_identifier(
             const uint8_t *format_class_identifier )
{
	int iterator = 0;

	if( format_class_identifier == NULL )
	{
		return( "Invalid format class identifier" );
	}
	while( memory_compare(
	        ( libfwps_format_class_identifier_definitions[ iterator ] ).class_identifier,
	        libfwps_format_class_identifier_unknown,
	        16 ) != 0 )
	{
		if( memory_compare(
		     ( libfwps_format_class_identifier_definitions[ iterator ] ).class_identifier,
		     format_class_identifier,
		     16 ) == 0 )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfwps_format_class_identifier_definitions[ iterator ] ).identifier );
}

/* Retrieves a string containing the description of the folder identifier
 */
const char *libfwps_format_class_identifier_get_description(
             const uint8_t *format_class_identifier )
{
	int iterator = 0;

	if( format_class_identifier == NULL )
	{
		return( "Invalid format class identifier" );
	}
	while( memory_compare(
	        ( libfwps_format_class_identifier_definitions[ iterator ] ).class_identifier,
	        libfwps_format_class_identifier_unknown,
	        16 ) != 0 )
	{
		if( memory_compare(
		     ( libfwps_format_class_identifier_definitions[ iterator ] ).class_identifier,
		     format_class_identifier,
		     16 ) == 0 )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfwps_format_class_identifier_definitions[ iterator ] ).description );
}

