#!/usr/bin/python -u
# coding: utf-8
#-------------------------------------------------------------------------------
# Script for building open62541 library, based on 
# https://open62541.org/doc/current/building.html
#-------------------------------------------------------------------------------

import os
import sys
import shutil

#-------------------------------------------------------------------------------
# Constants
#-------------------------------------------------------------------------------

BUILD_DIR = "build"

#-------------------------------------------------------------------------------
# Functions
#-------------------------------------------------------------------------------

def build_win():
	CMAKE = "cmake"
	COMPILER = "Visual Studio 14 2015"
	MSBUILD = "C:\\Program Files (x86)\\MSBuild\\14.0\\Bin\\MSBuild.exe"	
	return os.system('cd ' + BUILD_DIR + ' && ' + CMAKE + ' -G "' + COMPILER + '" .. && "' + MSBUILD + '" open62541.sln')
# end build_win

#-------------------------------------------------------------------------------

def build_linux():
	return os.system('cd ' + BUILD_DIR + ' && cmake .. && make')
# end build_linux

#-------------------------------------------------------------------------------
# Entry point
#-------------------------------------------------------------------------------

if __name__ == "__main__":

	# clean first
	if os.path.exists(BUILD_DIR):
		shutil.rmtree(BUILD_DIR)
	# end if
	
	# create output directory
	os.mkdir(BUILD_DIR)
	
	# run os specific build
	ret = 0
	if os.name == 'nt':
		ret = build_win()
	else:
		ret = build_linux()
	# end if
	
	# Check for success
	if ret == 0:
		print("\nBuild successful")
	else:
		print("\nERROR: Build failed")
		sys.exit(ret)
	# end if
	
# end if

#-------------------------------------------------------------------------------
