#!/usr/bin/env python
#
# Python-bindings set type test script
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
import sys
import unittest

import pyfwps


class SetTypeTests(unittest.TestCase):
  """Tests the set type."""

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

  def test_get_number_of_records(self):
    """Tests the get_number_of_records function and number_of_records property."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    number_of_records = fwps_set.get_number_of_records()
    self.assertEqual(number_of_records, 1)

    self.assertEqual(fwps_set.number_of_records, 1)

  def test_get_record(self):
    """Tests the get_record function."""
    fwps_set = pyfwps.set()

    fwps_set.copy_from_byte_stream(self._TEST_DATA)

    fwps_record = fwps_set.get_record(0)
    self.assertIsNotNone(fwps_record)


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  unittest.main(argv=unknown_options, verbosity=2)
