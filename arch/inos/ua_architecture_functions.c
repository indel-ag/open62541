/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information.
 *
 *    Copyright 2019 (c) Christoph Hirzel, Indel AG
 */

#ifdef UA_ARCHITECTURE_INOS

#include <open62541/types.h>

unsigned int UA_socket_set_blocking(UA_SOCKET sockfd){
  int on = 0;
  if(lwip_ioctl(sockfd, FIONBIO, &on) < 0)
    return UA_STATUSCODE_BADINTERNALERROR;
  return UA_STATUSCODE_GOOD;
}

unsigned int UA_socket_set_nonblocking(UA_SOCKET sockfd){
  int on = 1;
  if(lwip_ioctl(sockfd, FIONBIO, &on) < 0)
    return UA_STATUSCODE_BADINTERNALERROR;
  return UA_STATUSCODE_GOOD;
}

void UA_initialize_architecture_network(void){
  return;
}

void UA_deinitialize_architecture_network(void){
  return;
}

#endif /* UA_ARCHITECTURE_INOS */
