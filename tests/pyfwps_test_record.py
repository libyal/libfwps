#!/usr/bin/env python
#
# Python-bindings record type test script
#
# Copyright (C) 2013-2024, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import sys
import unittest

import pyfwps


class RecordTypeTests(unittest.TestCase):
  """Tests the record type."""

  _TEST_DATA = bytes(bytearray([
      0x89, 0x00, 0x00, 0x00, 0x31, 0x53, 0x50, 0x53, 0xe2, 0x8a, 0x58, 0x46,
      0xbc, 0x4c, 0x38, 0x43, 0xbb, 0xfc, 0x13, 0x93, 0x26, 0x98, 0x6d, 0xce,
      0x6d, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00,
      0x00, 0x2e, 0x00, 0x00, 0x00, 0x53, 0x00, 0x2d, 0x00, 0x31, 0x00, 0x2d,
      0x00, 0x35, 0x00, 0x2d, 0x00, 0x32, 0x00, 0x31, 0x00, 0x2d, 0x00, 0x34,
      0x00, 0x30, 0x00, 0x36, 0x00, 0x30, 0x00, 0x32, 0x00, 0x38, 0x00, 0x39,
      0x00, 0x33, 0x00, 0x32, 0x00, 0x33, 0x00, 0x2d, 0x00, 0x31, 0x00, 0x39,
      0x00, 0x39, 0x00, 0x37, 0x00, 0x30, 0x00, 0x31, 0x00, 0x30, 0x00, 0x32,
      0x00, 0x32, 0x00, 0x2d, 0x00, 0x33, 0x00, 0x39, 0x00, 0x32, 0x00, 0x34,
      0x00, 0x38, 0x00, 0x30, 0x00, 0x31, 0x00, 0x36, 0x00, 0x38, 0x00, 0x31,
      0x00, 0x2d, 0x00, 0x31, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]))

  def test_get_entry_name(self):
    """Tests the get_entry_name function and entry_name property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)

    entry_name = fwps_record.get_entry_name()
    self.assertIsNone(entry_name)

    self.assertIsNone(fwps_record.entry_name)

  def test_get_entry_type(self):
    """Tests the get_entry_type function and entry_type property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)

    entry_type = fwps_record.get_entry_type()
    self.assertEqual(entry_type, 4)

    self.assertEqual(fwps_record.entry_type, 4)

  def test_get_value_name(self):
    """Tests the get_value_name function and value_name property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)

    value_name = fwps_record.get_value_name()
    self.assertIsNone(value_name)

    self.assertIsNone(fwps_record.value_name)

  def test_get_value_type(self):
    """Tests the get_value_type function and value_type property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)

    value_type = fwps_record.get_value_type()
    self.assertEqual(value_type, 0x001f)

    self.assertEqual(fwps_record.value_type, 0x001f)

  def test_get_data(self):
    """Tests the get_data function and data property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)

    data = fwps_record.get_data()
    self.assertIsNotNone(data)

    self.assertIsNotNone(fwps_record.data)

  def test_get_data_as_boolean(self):
    """Tests the get_data_as_boolean function and data_as_boolean property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)

    with self.assertRaises(IOError):
      fwps_record.get_data_as_boolean()

    with self.assertRaises(IOError):
      fwps_record.data_as_boolean

  def test_get_data_as_integer(self):
    """Tests the get_data_as_integer function and data_as_integer property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)

    with self.assertRaises(IOError):
      fwps_record.get_data_as_integer()

    with self.assertRaises(IOError):
      fwps_record.data_as_integer

  def test_get_data_as_floating_point(self):
    """Tests the get_data_as_floating_point function and data_as_floating_point property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)

    with self.assertRaises(IOError):
      fwps_record.get_data_as_floating_point()

    with self.assertRaises(IOError):
      fwps_record.data_as_floating_point

  def test_get_data_as_string(self):
    """Tests the get_data_as_string function and data_as_string property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)

    data_as_string = fwps_record.get_data_as_string()
    self.assertIsNotNone(data_as_string)

    self.assertIsNotNone(fwps_record.data_as_string)


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  unittest.main(argv=unknown_options, verbosity=2)
