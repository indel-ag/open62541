/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 *    Copyright 2019 (c) Christoph Hirzel, Indel AG
 */

#ifdef UA_ARCHITECTURE_INOS

#ifndef PLUGINS_ARCH_INOS_UA_ARCHITECTURE_H_
#define PLUGINS_ARCH_INOS_UA_ARCHITECTURE_H_

#undef UA_ENABLE_DISCOVERY_SEMAPHORE
//#define UA_ENABLE_DISCOVERY_MULTICAST


#define UA_free free
#define UA_malloc malloc
#define UA_calloc calloc
#define UA_realloc realloc
#define UA_snprintf snprintf
#define UA_sleep_ms(X) sleep_ms_inos(X)
#define UA_gethostname gethostname_inos
#define UA_getaddrinfo getaddrinfo_inos
#define UA_LOG_SOCKET_ERRNO_WRAP(LOG) { \
    char *errno_str = ""; \
    LOG; \
}

#include "ua_lwip.h"
#include <open62541/architecture_functions.h>
#include "ua_inos_sys.h"

//! TODO discovery semaphore currently not supported under INOS,
//! as it requires some file system API (access())
#endif /* PLUGINS_ARCH_INOS_UA_ARCHITECTURE_H_ */


#if UA_MULTITHREADING >= 100
#define UA_LOCK_TYPE_NAME               inos_mutex_t
#define UA_LOCK_TYPE(mutexName)         inos_mutex_t mutexName;
#define UA_LOCK_INIT(mutexName)         inos_mutex_init(&mutexName);
#define UA_LOCK_DESTROY(mutexName)      inos_mutex_destroy(&mutexName);
#define UA_LOCK(mutexName)              inos_mutex_lock(&mutexName);
#define UA_UNLOCK(mutexName)            inos_mutex_unlock(&mutexName);
#define UA_LOCK_ASSERT(mutexName, num)  //UA_assert(mutexName##Counter == num);
#else
#define UA_LOCK_TYPE_NAME
#define UA_LOCK_TYPE(mutexName)
#define UA_LOCK_INIT(mutexName)
#define UA_LOCK_DESTROY(mutexName)
#define UA_LOCK(mutexName)
#define UA_UNLOCK(mutexName)
#define UA_LOCK_ASSERT(mutexName, num)
#endif

#define UA_strncasecmp strncasecmp

#ifndef IN6_IS_ADDR_UNSPECIFIED
# define IN6_IS_ADDR_UNSPECIFIED(a) \
        (((const uint32_t *) (a))[0] == 0                                      \
         && ((const uint32_t *) (a))[1] == 0                                      \
         && ((const uint32_t *) (a))[2] == 0                                      \
         && ((const uint32_t *) (a))[3] == 0)
#endif


#endif /* UA_ARCHITECTURE_INOS */
