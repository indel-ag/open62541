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
#define UA_LOG_SOCKET_ERRNO_WRAP(LOG) { \
    char *errno_str = ""; \
    LOG; \
}

#include "ua_lwip.h"
#include <open62541/architecture_functions.h>
//#include "ua_inos_sys.h"

//! TODO discovery semaphore currently not supported under INOS,
//! as it requires some file system API (access())
#endif /* PLUGINS_ARCH_INOS_UA_ARCHITECTURE_H_ */

#endif /* UA_ARCHITECTURE_INOS */
