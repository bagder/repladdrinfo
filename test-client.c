/***************************************************************************
 *
 * Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "replace.h"

static int lookup(const char *host, bool replace)
{
  struct addrinfo hints, *res, *result;
  int errcode;
  char addrstr[100];
  void *ptr;
  int (*getaddr)(const char *node,
                 const char *service,
                 const struct addrinfo *hints,
                 struct addrinfo **res);
  void (*freeaddr)(struct addrinfo *res);

  /* setup the correct functions to use */
  getaddr = replace ? r_getaddrinfo : getaddrinfo;
  freeaddr = replace ? r_freeaddrinfo : freeaddrinfo;

  memset(&hints, 0, sizeof (hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags |= AI_CANONNAME;

  errcode = getaddr(host, NULL, &hints, &result);
  if(errcode) {
    perror ("getaddrinfo");
    return -1;
  }

  res = result;

  printf("Host: %s%s\n", host, replace ? " [REPLACED]" : "");
  while(res) {
    switch(res->ai_family) {
    case AF_INET:
      ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
      break;
    case AF_INET6:
      ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
      break;
    }
    inet_ntop(res->ai_family, ptr, addrstr, sizeof(addrstr));
    printf("IPv%d: %s (%s)\n",
           res->ai_family == PF_INET6 ? 6 : 4,
           addrstr, res->ai_canonname ? res->ai_canonname : "");
    res = res->ai_next;
  }

  freeaddr(result);

  return 0;
}

int main(void)
{
  lookup("curl.se", false);
  lookup("curl.se", true);
  return 0;
}
