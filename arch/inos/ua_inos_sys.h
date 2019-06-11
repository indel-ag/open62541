/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. 
 *
 *    Copyright 2018 (c) Indel AG (Author: Daniel Pauli)
 */
 
#ifndef INOS_OS_OPEN62541_INOS_INOS_SYS_H_
#define INOS_OS_OPEN62541_INOS_INOS_SYS_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
//
// system
#include <stdint.h> // uint64_t
#include <stddef.h> // size_t
#include <lwip/sockets.h>

// project
#include <open62541/plugin/log_stdout.h> // UA_LogLevel

//------------------------------------------------------------------------------
//
#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------
//

uint64_t GetSystemMicroSeconds_inos();

int gethostname_inos(char* name, size_t len);

const char *gai_strerror_inos(int errcode);

void sleep_ms_inos(int aiMs);

int getnameinfo_inos(const struct sockaddr_storage* addr,
		char* host, socklen_t hostlen);

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

#endif /* INOS_OS_OPEN62541_INOS_INOS_SYS_H_ */
//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
