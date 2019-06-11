/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. 
 *
 *    Copyright 2019 (c) Christoph Hirzel, Indel AG
 */

#ifdef UA_ARCHITECTURE_INOS

#include <open62541/types.h>
#include "ua_inos_sys.h"

/* The current time in UTC time */
UA_DateTime UA_DateTime_now(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * UA_DATETIME_SEC) + (tv.tv_usec * UA_DATETIME_USEC) + UA_DATETIME_UNIX_EPOCH;
}

/* Offset between local time and UTC time */
UA_Int64 UA_DateTime_localTimeUtcOffset(void) {
/*    struct tm *ptm;
    struct tm gbuf;
    ptm = gmtime_r(&rawtime, &gbuf);
    // Request that mktime() looksup dst in timezone database
    ptm->tm_isdst = -1;
    gmt = mktime(ptm);

	return (UA_Int64) (difftime(rawtime, gmt) * UA_DATETIME_SEC);
	*/
	return 0;
}

/* CPU clock invariant to system time changes. Use only to measure durations,
 * not absolute time. */
UA_DateTime UA_DateTime_nowMonotonic(void) {
    uint64_t uMicroSec = GetSystemMicroSeconds_inos();
    struct timespec ts;
    ts.tv_sec = uMicroSec/1000000;
    ts.tv_nsec = (uMicroSec % 1000000)* 1000;
    return (ts.tv_sec * UA_DATETIME_SEC) + (ts.tv_nsec / 100);
}

#endif /* UA_ARCHITECTURE_FREERTOSLWIP */
