/*
 * Copyright (c) 2017  Martin Lund
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holders nor contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MSG_HEADER_SIZE 16
#define MSG_HEADER_PROLOGUE 0x4853 // "HS"

// Control codes
#define CC_PREFER_OVERLAP     1
#define CC_PREFER_SYNC        0
#define CC_RMT_DELIVERED      1
#define CC_RMT_NOT_DELIVERED  0
#define CC_REQUEST 1
#define CC_RELEASE 0
#define CC_REQUEST_RSP_FAIL    0
#define CC_REQUEST_RSP_SUCCESS 1
#define CC_REQUEST_RSP_ERROR   3
#define CC_RELEASE_RSP_SUCCESS_EXCLUSIVE 1
#define CC_RELEASE_RSP_SUCCESS_SHARED    2
#define CC_RELEASE_RSP_SUCCESS_ERROR     3
#define CC_INFO_RSP_NO_EXCLUSIVE_LOCK 0
#define CC_INFO_RSP_EXCLUSIVE_LOCK    1
#define CC_DISABLE_REMOTE                        0
#define CC_ENABLE_REMOTE                         1
#define CC_DISABLE_REMOTE_GO_LOCAL               2
#define CC_ENABLE_REMOTE_GO_REMOTE               3
#define CC_ENABLE_REMOTE_LOCK_LOCAL              4
#define CC_ENABLE_REMOTE_GO_REMOTE_LOCAL_LOCKOUT 5
#define CC_GO_LOCAL_NO_REN_OR_LOCKOUT_CHANGE     6


typedef struct __attribute__((__packed__))
{
    uint16_t prologue;
    uint8_t type;
    uint8_t control_code;
    uint32_t parameter;
    uint64_t payload_length;
} msg_header_t;

typedef enum
{
    Initialize,
    InitializeResponse,
    FatalError,
    Error,
    AsyncLock,
    AsyncLockResponse,
    Data,
    DataEnd,
    DeviceClearComplete,
    DeviceClearAcknowledge,
    AsyncRemoteLocalControl,
    AsyncRemoteLocalResponse,
    Trigger,
    Interrupted,
    AsyncInterrupted,
    AsyncMaximumMessageSize,
    AsyncMaximumMessageSizeResponse,
    AsyncInitialize,
    AsyncInitializeResponse,
    AsyncDeviceClear,
    AsyncServiceRequest,
    AsyncStatusQuery,
    AsyncStatusResponse,
    AsyncDeviceClearAcknowledge,
    AsyncLockInfo,
    AsyncLockInfoResponse
} msg_type_t;

typedef enum
{
    FATAL_ERROR_UNIDENTIFIED,
    FATAL_ERROR_POORLY_FORMED_MESSAGE_HEADER,
    FATAL_ERROR_CONNECTION_NOT_READY,
    FATAL_ERROR_INVALID_INIT_SEQUENCE,
    FATAL_ERROR_TOO_MANY_CLIENTS
} fatal_error_code_t;

typedef enum
{
    ERROR_UNIDENTIFIED,
    ERROR_UNRECOGNIZED_MESSAGE_TYPE,
    ERROR_UNRECOGNIZED_CONTROL_CODE,
    ERROR_UNRECOGNIZED_VENDOR_DEFINED_MESSAGE,
    ERROR_MESSAGE_TOO_LARGE
} error_code_t;

int msg_header_verify(msg_header_t *header);
int msg_create(
        void **message,
        msg_type_t type,
        uint8_t control_code,
        uint32_t parameter,
        uint64_t payload_length,
        void *payload);
void msg_destroy(void *message);

#endif
