#!/usr/bin/python -u
# coding: utf-8
#-------------------------------------------------------------------------------
# Script for configuring open62541 library and generating code.
#-------------------------------------------------------------------------------

import os
import sys
import shutil
import subprocess

#-------------------------------------------------------------------------------
# Constants
#-------------------------------------------------------------------------------

BUILD_DIR = "build"
ARCHITECTURE = sys.argv[1] if len(sys.argv) > 1 else None

OPTIONS = [
	'UA_ENABLE_PUBSUB',
	'UA_ENABLE_SUBSCRIPTION_EVENTS',
]

#-------------------------------------------------------------------------------
# Functions
#-------------------------------------------------------------------------------

def build_win():
	CMAKE = "cmake"
	COMPILER = "Visual Studio 14 2015"
	MSBUILD = "C:\\Program Files (x86)\\MSBuild\\14.0\\Bin\\MSBuild.exe"
	
	# projects required for code generation
	PROJECTS = [
		'open62541-generator-ids-ns0.vcxproj',
		'open62541-generator-namespace.vcxproj',
		'open62541-generator-statuscode.vcxproj',
		'open62541-generator-transport.vcxproj',
		'open62541-generator-types.vcxproj',
	]
			
	# call cmake
	subprocess.check_call([CMAKE, '-DUA_ARCHITECTURE:STRING=' + ARCHITECTURE, '-G', COMPILER, '..'] + ['-D%s=on' % option for option in OPTIONS], cwd=BUILD_DIR)
	# build projects
	for project in PROJECTS:
		subprocess.check_call([MSBUILD, project], cwd=BUILD_DIR)
	# done
	return 0
	#return os.system('cd ' + BUILD_DIR + ' && ' + CMAKE + ' -DUA_ARCHITECTURE:STRING=' + ARCHITECTURE + ' -G "' + COMPILER + '" .. && "' + MSBUILD + '" open62541-generator-ids-ns0.vcxproj open62541-generator-namespace.vcxproj')
# end build_win

#-------------------------------------------------------------------------------

def build_linux():
	print("TODO implement")
	#return os.system('cd ' + BUILD_DIR + ' && cmake .. && make')
	return 1
# end build_linux

#-------------------------------------------------------------------------------
# Entry point
#-------------------------------------------------------------------------------

if __name__ == "__main__":

	# check if architecture specified
	if not ARCHITECTURE:
		print("Please specify architecture as first parameter, e.g. win32 or inos")
		sys.exit(1);
	# end if

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
		print("\nPrebuild successful")
	else:
		print("\nERROR: Prebuild failed")
		sys.exit(ret)
	# end if
	
# end if

#-------------------------------------------------------------------------------
