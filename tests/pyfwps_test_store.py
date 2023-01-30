#!/usr/bin/env python
#
# Python-bindings store type test script
#
# Copyright (C) 2013-2023, Joachim Metz <joachim.metz@gmail.com>
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


class StoreTypeTests(unittest.TestCase):
  """Tests the store type."""

  def test_get_number_of_sets(self):
    """Tests the get_number_of_sets function and number_of_sets property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    fwps_store = pyfwps.store()

    fwps_store.open(test_source)

    number_of_sets = fwps_store.get_number_of_sets()
    self.assertIsNotNone(number_of_sets)

    self.assertIsNotNone(fwps_store.number_of_sets)

    fwps_store.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="The path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
