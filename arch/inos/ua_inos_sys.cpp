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
#include "ua_inos_sys.h"

//------------------------------------------------------------------------------
//
extern "C" {

//------------------------------------------------------------------------------
//
uint64_t GetSystemMicroSeconds_inos() {
	return GetSystemMicroSeconds();
}

//------------------------------------------------------------------------------
//
int gethostname_inos(char* name, size_t len)
{
	strncpy(name, TARGET.GetIPAddressStr(), len);
	return 0;
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
