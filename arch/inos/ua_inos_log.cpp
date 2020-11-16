/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. 
 *
 *    Copyright 2018 (c) Indel AG (Author: Daniel Pauli)
 */

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
//
// system
#include <inos.h>
#include <cinoseventlogger.h>
// project
#include "ua_inos_log.h"

//------------------------------------------------------------------------------
//
extern "C" {

//------------------------------------------------------------------------------
//
void UA_Log_Stdout_inos(UA_LogLevel level,
	const char* levelStr, const char* categoryStr,
	const char *msg, va_list args)
{
	// format message
	char cFmtMsg [256];
	vsnprintf(cFmtMsg, sizeof(cFmtMsg), msg, args);
	// ensure null-termination
	cFmtMsg[sizeof(cFmtMsg)-1] = 0;

	// trace according to log level
	switch (level) {
	case UA_LOGLEVEL_ERROR:
	case UA_LOGLEVEL_FATAL:
		INOS_ERROR("[UA:%s:%s] %s", categoryStr, levelStr, cFmtMsg);
		break;
	case UA_LOGLEVEL_WARNING:
		INOS_WARNING("[UA:%s:%s] %s", categoryStr, levelStr, cFmtMsg);
		break;
	case UA_LOGLEVEL_INFO:
		INOS_MESSAGE("[UA:%s:%s] %s", categoryStr, levelStr, cFmtMsg);
		break;
	case UA_LOGLEVEL_DEBUG:
	case UA_LOGLEVEL_TRACE:
		INOS_VERBOSE("[UA:%s:%s] %s", categoryStr, levelStr, cFmtMsg);
		break;
	default:
		// trace error for unknown log levels to ensure visibility
		INOS_ERROR("[UA:%s:%s???] %s", categoryStr, levelStr, cFmtMsg);
		break;
	}

}

//------------------------------------------------------------------------------
//
} // end extern "c"

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
