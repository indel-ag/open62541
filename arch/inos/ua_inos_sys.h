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


//------------------------------------------------------------------------------
//
#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// types
//-----------------------------------------------------------------------------
//
typedef struct inos_mutex {
	//! opaque pointer to a CINOSMutex
	void* pMutex;
} inos_mutex_t;

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------
//

//! timing related
uint64_t GetSystemMicroSeconds_inos();
void sleep_ms_inos(int aiMs);

//! locking related
void inos_mutex_init(inos_mutex_t* mutex);
void inos_mutex_destroy(inos_mutex_t* mutex);
void inos_mutex_lock(inos_mutex_t* mutex);
void inos_mutex_unlock(inos_mutex_t* mutex);

//! network related
int gethostname_inos(char* name, size_t len);
const char *gai_strerror_inos(int errcode);
int getnameinfo_inos(const struct sockaddr_storage* addr,
	char* host, socklen_t hostlen);
int getaddrinfo_inos(const char *nodename, const char *servname,
	const struct addrinfo *hints, struct addrinfo **res);

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
