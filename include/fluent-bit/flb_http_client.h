/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Fluent Bit
 *  ==========
 *  Copyright (C) 2015-2016 Treasure Data Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef FLB_HTTP_CLIENT_H
#define FLB_HTTP_CLIENT_H

#include <fluent-bit/flb_io.h>

/* Buffer size */
#define FLB_HTTP_BUF_SIZE 2048

/* HTTP Methods */
#define FLB_HTTP_GET         0
#define FLB_HTTP_POST        1
#define FLB_HTTP_HEAD        2

struct flb_http_response {
    int status;
    int content_length;
    char  data[1024 * 4];   /* 4 KB */
    size_t data_len;
};

/* Set a request type */
struct flb_http_client {
    /* Upstream context */
    struct flb_io_upstream *u;

    /* Request data */
    int method;
    int header_len;
    int header_size;
    char *header_buf;

    int body_len;
    char *body_buf;

    /* Response */
    struct flb_http_response resp;
};

struct flb_http_client *flb_http_client(struct flb_io_upstream *u,
                                        int method, char *uri,
                                        char *body, size_t body_len);
int flb_http_add_header(struct flb_http_client *c,
                        char *key, size_t key_len,
                        char *val, size_t val_len);
int flb_http_do(struct flb_http_client *c, size_t *bytes);
void flb_http_client_destroy(struct flb_http_client *c);

#endif
