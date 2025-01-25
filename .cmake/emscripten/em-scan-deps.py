#!/usr/bin/env python3
# Copyright 2024 The Emscripten Authors.  All rights reserved.
# Emscripten is available under two separate licenses, the MIT license and the
# University of Illinois/NCSA Open Source License.  Both these licenses can be
# found in the LICENSE file.

"""emscan-deps - clang-scan-deps helper script

This script acts as a frontend replacement for clang-scan-deps.
"""
import sys
import os
from os.path import join
sys.path.insert(0, os.environ["EM_ROOT"])
from tools import shared, cache

CLANG_SCAN_DEPS = shared.build_llvm_tool_path(shared.exe_suffix('clang-scan-deps'))

# allow overriding the clang-scan-deps executable (for Nix)
if "EM_SCAN_DEPS_EXE" in os.environ:
   CLANG_SCAN_DEPS = os.environ["EM_SCAN_DEPS_EXE"]

args = sys.argv[1:]
# remove all -s... arguments from scan-deps because they're not needed
args = [x for x in args if not x.startswith("-s")]

# TODO for some reason CMake(?) refuses to add the -std flag for the web configuration so we must force it :/
args.append("-std=c++26")

args.append('--sysroot=' + cache.get_sysroot(absolute=True))
shared.exec_process([CLANG_SCAN_DEPS] + args)
