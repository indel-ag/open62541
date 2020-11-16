/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. 
 *
 *    Copyright 2018 (c) Indel AG (Author: Daniel Pauli)
 */
 
#ifndef INOS_OS_OPEN62541_INOS_INOS_LOG_H_
#define INOS_OS_OPEN62541_INOS_INOS_LOG_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
//
// system

// project
#include <open62541/plugin/log.h> // UA_LogLevel

//------------------------------------------------------------------------------
//
#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------
//

void UA_Log_Stdout_inos(UA_LogLevel level,
		const char* levelStr, const char* categoryStr,
		const char *msg, va_list args);

//------------------------------------------------------------------------------
//
#ifdef __cplusplus
}
#endif
//------------------------------------------------------------------------------
//

#endif /* INOS_OS_OPEN62541_INOS_INOS_LOG_H_ */
//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
