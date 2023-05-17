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
#include <sockets.h>
#include <cinosmalloc.h>
// project
#include "ua_inos_sys.h"


//------------------------------------------------------------------------------
// variables
//------------------------------------------------------------------------------
//
#ifdef INOS_OPCUA_OMM
//! allocator used for malloc() and friends
CINOSMalloc gUaMemory("open62541");
#endif


//------------------------------------------------------------------------------
// start functions
//------------------------------------------------------------------------------
//
StartFunction(_INI_0100_ua_inos_sys) {
	InitializeUaMemory();
}


//------------------------------------------------------------------------------
// functions
//------------------------------------------------------------------------------
//
void InitializeUaMemory()
{
#ifdef INOS_OPCUA_OMM
	// critical section
	static CINOSMutex s_Mutex;
	CINOSLock lock(s_Mutex);

	if (gUaMemory.GetNumPools() > 0) {
		// already done
		return;
	}

	// try to load pools from config
	if (gUaMemory.LoadFromTable("open62541") == 0) {
		/*
		 * no config found -> use default
		 *
		 * The following configuration was picked based on observing the memory usage
		 * while repeatedly executing the OPC UA unit tests.
		 */
		gUaMemory.AddPool(      4,  1024);
		gUaMemory.AddPool(      8,  1024);
		gUaMemory.AddPool(     16,  1024);
		gUaMemory.AddPool(     64,  1024);
		gUaMemory.AddPool(    128,   256);
		gUaMemory.AddPool(    256,   256);
		gUaMemory.AddPool(   1024,   256);  //   1 KB
		gUaMemory.AddPool(  65536,    16);  //  64 KB
		gUaMemory.AddPool( 131072,    16);  // 128 KB
		gUaMemory.AddPool( 262144,    16);  // 256 KB
	} // end if

#endif
}

//------------------------------------------------------------------------------
//
extern "C" {

//------------------------------------------------------------------------------
//
void* inos_malloc(size_t size)
{
#ifdef INOS_OPCUA_OMM
	return gUaMemory.Malloc(size);
#else
	return malloc(size);
#endif
}

//------------------------------------------------------------------------------
//
void* inos_calloc(size_t num, size_t size)
{
#ifdef INOS_OPCUA_OMM
	return gUaMemory.Calloc(num, size);
#else
	return calloc(num, size);
#endif
}

//------------------------------------------------------------------------------
//
void* inos_realloc(void* ptr, size_t size)
{
#ifdef INOS_OPCUA_OMM
	return gUaMemory.Realloc(ptr, size);
#else
	return realloc(ptr, size);
#endif
}

//------------------------------------------------------------------------------
//
void inos_free(void* ptr)
{
#ifdef INOS_OPCUA_OMM
	gUaMemory.Free(ptr);
#else
	free(ptr);
#endif
}

//------------------------------------------------------------------------------
//
uint64_t GetSystemMicroSeconds_inos() {
	return GetSystemMicroSeconds();
}

//------------------------------------------------------------------------------
//
void inos_mutex_init(inos_mutex_t* mutex)
{
	mutex->pMutex = new CINOSMutex();
}

//------------------------------------------------------------------------------
//
void inos_mutex_destroy(inos_mutex_t* mutex)
{
	delete (CINOSMutex*)mutex->pMutex;
	mutex->pMutex = nullptr;
}

//------------------------------------------------------------------------------
//
void inos_mutex_lock(inos_mutex_t* mutex)
{
	ASSERT_ALWAYS(mutex->pMutex);
	((CINOSMutex*)mutex->pMutex)->Request();
}

//------------------------------------------------------------------------------
//
void inos_mutex_unlock(inos_mutex_t* mutex)
{
	ASSERT_ALWAYS(mutex->pMutex);
	((CINOSMutex*)mutex->pMutex)->Release();
}

//------------------------------------------------------------------------------
//
int gethostname_inos(char* name, size_t len)
{
	int ret = 0;
	const char* apCustomHostname = INOSGetSystemString("OPCUA", "CustomHostname");
	if (!apCustomHostname) {
		// default case: return our MDNS hostname
		ret = snprintf(name, len, "%s.local", TARGET.GetHostname());
	} else {
		// return custom hostname
		// we do this here because of deprecation of UA_ServerConfig_setCustomHostname
		// see also ServerNetworkLayerTCP_start
		ret = snprintf(name, len, "%s", apCustomHostname);
	}
    if (ret>=0 && ret<(int)len) {
    	// success
    	return 0;
    }
    // failed
	return -1;
}

//------------------------------------------------------------------------------
//
const char *gai_strerror_inos(int errcode)
{
	static char cError [256];
	// TODO use actual error descriptions
	snprintf(cError, sizeof(cError), "Network error %d", errcode);
	return cError;
}

//------------------------------------------------------------------------------
//
void sleep_ms_inos(int aiMs)
{
	Sleep(aiMs);
}

//------------------------------------------------------------------------------
//
int getnameinfo_inos(const struct sockaddr_storage* addr,
		char* host, socklen_t hostlen)
{
    char cIpAddr [64];
    int port = 0;

	if (addr->ss_family == AF_INET) {
		// IPv4
	    struct sockaddr_in *s = (struct sockaddr_in *)addr;
	    ipaddr_ntoa_r((ip_addr_t*)&s->sin_addr, cIpAddr, sizeof(cIpAddr));
	    port = ntohs(s->sin_port);
	    if ((socklen_t)snprintf(host, hostlen, "%s:%u", cIpAddr, port) >= hostlen) {
	    	// buffer too small
	    	return -1;
	    }
	    // success
	    return 0;
#if LWIP_IPV6
	} else if (addr->ss_family == AF_INET6) {
		// IPv6
	    struct sockaddr_in6 *s = (struct sockaddr_in6 *)addr;
	    ip6addr_ntoa_r((ip6_addr_t*)&s->sin6_addr, cIpAddr, sizeof(cIpAddr));
	    port = ntohs(s->sin6_port);
	    // success
	    if ((socklen_t)snprintf(host, hostlen, "[%s]:%u", cIpAddr, port) >= hostlen) { ;
			// buffer too small
			return -1;
		}
	    // success
	    return 0;
#endif // LWIP_IPV6
	} else {
		// unsupported protocol
		return -1;
	}
}


//------------------------------------------------------------------------------
//
int getaddrinfo_inos(const char *nodename, const char *servname,
                 const struct addrinfo *hints, struct addrinfo **res)
{
	// is it our MDNS hostname?
	if (nodename) {
		char cMdnsHostname [64];
		snprintf(cMdnsHostname, sizeof(cMdnsHostname), "%s.local", TARGET.GetHostname());
		if (strncmp(nodename, cMdnsHostname, sizeof(cMdnsHostname)) == 0) {
			// yes -> LWIP does not know it, treat it as IPv4 wildcard
			// this is the "OPC UA server" use case
			nodename = "0.0.0.0";
		}
	}
	// pass to LWIP
	return getaddrinfo(nodename, servname, hints, res);
}

//------------------------------------------------------------------------------
//
} // end extern "c"

//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
