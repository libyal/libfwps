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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libfwps_format_class_identifier.h"
#include "libfwps_property_identifier.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* The document summary information property identifiers
 * Format class identifier: d5cdd502-2e9c-101b-9397-08002b2cf9ae
 */
libfwps_property_identifier_t libfwps_document_summary_information_properties[ ] = {
	{ 0x0001, 0x0002, "PIDDSI_CODEPAGE",		"Codepage" },
	{ 0x0002, 0x001e, "PIDDSI_CATEGORY",		"Category" },
	{ 0x0003, 0x001e, "PIDDSI_PRESFORMAT",		"Presentation format" },
	{ 0x0004, 0x0003, "PIDDSI_BYTECOUNT",		"Number of bytes" },
	{ 0x0005, 0x0003, "PIDDSI_LINECOUNT",		"Number of lines" },
	{ 0x0006, 0x0003, "PIDDSI_PARCOUNT",		"Number of paragraphs" },
	{ 0x0007, 0x0003, "PIDDSI_SLIDECOUNT",		"Number of slides" },
	{ 0x0008, 0x0003, "PIDDSI_NOTECOUNT",		"Number of notes" },
	{ 0x0009, 0x0003, "PIDDSI_HIDDENCOUNT",		"Number of hidden slides" },
	{ 0x000a, 0x0003, "PIDDSI_MMCLIPCOUNT",		"Number of multimedia clips" },
	{ 0x000b, 0x000b, "PIDDSI_SCALE",		"Scale crop" },
	{ 0x000c, 0x100c, "PIDDSI_HEADINGPAIR",		"Heading pair" },
	{ 0x000d, 0x101e, "PIDDSI_DOCPARTS",		"Document parts" },
	{ 0x000e, 0x001e, "PIDDSI_MANAGER",		"Manager" },
	{ 0x000f, 0x001e, "PIDDSI_COMPANY",		"Company" },
	{ 0x0010, 0x000b, "PIDDSI_LINKSDIRTY",		"Links dirty" },
	{ 0x0011, 0x0003, "PIDDSI_CCHWITHSPACES",	"Number of characters with white-space" },

	{ 0x0013, 0x000b, "PIDDSI_SHAREDDOC",		"Shared document" },

	{ 0x0016, 0x000b, "PIDDSI_HYPERLINKSCHANGED",	"Hyper links changed" },
	{ 0x0017, 0x0003, "PIDDSI_VERSION",		"Creating application version" },
	{ 0x0018, 0x0041, "PIDDSI_DIGSIG",		"Digital signature" },

	{ 0x001a, 0x001e, "PIDDSI_CONTENTTYPE",		"Content type" },
	{ 0x001b, 0x001e, "PIDDSI_CONTENTSTATUS",	"Content status" },
	{ 0x001c, 0x001e, "PIDDSI_LANGUAGE",		"Language" },
	{ 0x001d, 0x001e, "PIDDSI_DOCVERSION",		"Document version" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The summary information property identifiers
 * Format class identifier: f29f85e0-4ff9-1068-ab91-08002b27b3d9
 */
libfwps_property_identifier_t libfwps_summary_information_properties[ ] = {
	{ 0x0001, 0x0002, "PIDSI_CODEPAGE",	"Codepage" },
	{ 0x0002, 0x001e, "PIDSI_TITLE",	"Title" },
	{ 0x0003, 0x001e, "PIDSI_SUBJECT",	"Subject" },
	{ 0x0004, 0x001e, "PIDSI_AUTHOR",	"Author" },
	{ 0x0005, 0x001e, "PIDSI_KEYWORDS",	"Keywords" },
	{ 0x0006, 0x001e, "PIDSI_COMMENTS ",	"Comments" },
	{ 0x0007, 0x001e, "PIDSI_TEMPLATE",	"Template" },
	{ 0x0008, 0x001e, "PIDSI_LASTAUTHOR",	"Last saved by" },
	{ 0x0009, 0x001e, "PIDSI_REVNUMBER",	"Revision number" },
	{ 0x000a, 0x0040, "PIDSI_EDITTIME",	"Total editing time" },
	{ 0x000b, 0x0040, "PIDSI_LASTPRINTED",	"Last printed date and time" },
	{ 0x000c, 0x0040, "PIDSI_CREATE_DTM",	"Creation date and time" },
	{ 0x000d, 0x0040, "PIDSI_LASTSAVE_DTM",	"Last saved date and time" },
	{ 0x000e, 0x0003, "PIDSI_PAGECOUNT", 	"Number of pages" },
	{ 0x000f, 0x0003, "PIDSI_WORDCOUNT", 	"Number of words" },
	{ 0x0010, 0x0003, "PIDSI_CHARCOUNT", 	"Number of characters" },
	{ 0x0011, 0x0047, "PIDSI_THUMBNAIL",	"Thumbnail" },
	{ 0x0012, 0x001e, "PIDSI_APPNAME", 	"Creating application name" },
	{ 0x0013, 0x0003, "PIDSI_SECURITY",	"Security" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* Retrieves a string containing the property identifier
 */
const char *libfwps_property_identifiers_get_identifier(
             libfwps_property_identifier_t libfwps_property_identifiers[],
             uint32_t entry_type,
             uint32_t value_type )
{
	int iterator = 0;

	if( value_type == 0x001f )
	{
		value_type = 0x001e;
	}
	else if( value_type == 0x101f )
	{
		value_type = 0x101e;
	}
	while( ( libfwps_property_identifiers[ iterator ] ).entry_type != (uint32_t) -1 )
	{
		if( ( ( libfwps_property_identifiers[ iterator ] ).entry_type == entry_type )
		 && ( ( libfwps_property_identifiers[ iterator ] ).value_type == value_type ) )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfwps_property_identifiers[ iterator ] ).identifier );
}

/* Retrieves a string containing the property identifier
 */
const char *libfwps_property_identifier_get_identifier(
	     const uint8_t *format_class_identifier,
	     uint32_t entry_type,
	     uint32_t value_type )
{
	if( format_class_identifier != NULL )
	{
		if( memory_compare(
		     format_class_identifier,
		     libfwps_format_class_identifier_document_summary_information,
		     16 ) == 0 )
		{
			return( libfwps_property_identifiers_get_identifier(
				 libfwps_document_summary_information_properties,
				 entry_type,
				 value_type ) );
		}
		else if( memory_compare(
			  format_class_identifier,
		          libfwps_format_class_identifier_summary_information,
			  16 ) == 0 )
		{
			return( libfwps_property_identifiers_get_identifier(
				 libfwps_summary_information_properties,
				 entry_type,
				 value_type ) );
		}
	}
	return( "_UNKNOWN_" );
}

/* Retrieves a string containing the property identifier description
 */
const char *libfwps_property_identifiers_get_description(
             libfwps_property_identifier_t libfwps_property_identifiers[],
             uint32_t entry_type,
             uint32_t value_type )
{
	int iterator = 0;

	if( value_type == 0x001f )
	{
		value_type = 0x001e;
	}
	else if( value_type == 0x101f )
	{
		value_type = 0x101e;
	}
	while( ( libfwps_property_identifiers[ iterator ] ).entry_type != (uint32_t) -1 )
	{
		if( ( ( libfwps_property_identifiers[ iterator ] ).entry_type == entry_type )
		 && ( ( libfwps_property_identifiers[ iterator ] ).value_type == value_type ) )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfwps_property_identifiers[ iterator ] ).description );
}

/* Retrieves a string containing the property identifier description
 */
const char *libfwps_property_identifier_get_description(
             const uint8_t *format_class_identifier,
             uint32_t entry_type,
             uint32_t value_type )
{
	if( format_class_identifier != NULL )
	{
		if( memory_compare(
		     format_class_identifier,
		     libfwps_format_class_identifier_document_summary_information,
		     16 ) == 0 )
		{
			return( libfwps_property_identifiers_get_description(
				 libfwps_document_summary_information_properties,
				 entry_type,
				 value_type ) );
		}
		else if( memory_compare(
			  format_class_identifier,
		          libfwps_format_class_identifier_summary_information,
			  16 ) == 0 )
		{
			return( libfwps_property_identifiers_get_description(
				 libfwps_summary_information_properties,
				 entry_type,
				 value_type ) );
		}
	}
	return( "Unknown" );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

