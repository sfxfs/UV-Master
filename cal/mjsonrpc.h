/*
    MIT License

    Copyright (c) 2024 Xiao

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef MJSONRPC_H
#define MJSONRPC_H

#include "cJSON.h"

#define JRPC_PARSE_ERROR        -32700
#define JRPC_INVALID_REQUEST    -32600
#define JRPC_METHOD_NOT_FOUND   -32601
#define JRPC_INVALID_PARAMS     -32603
#define JRPC_INTERNAL_ERROR     -32693

// -32000 to -32099 Reserved for implementation-defined server-errors.

enum mjrpc_error_return
{
    MJRPC_OK,
    MJRPC_ERROR_MEM_ALLOC_FAILED,
    MJRPC_ERROR_NOT_FOUND,
    MJRPC_ERROR_EMPTY_REQUST,
    MJRPC_ERROR_PARSE_FAILED,
};

typedef struct
{
    void *data;
    int error_code;
    char *error_message;
} mjrpc_ctx_t;

typedef cJSON *(*mjrpc_function)(mjrpc_ctx_t *context,
                                 cJSON *params,
                                 cJSON *id);

struct mjrpc_cb_info
{
    char *name;
    mjrpc_function function;
    void *data;
};

typedef struct rpc_handle
{
    int info_count;
    struct mjrpc_cb_info *infos;
} mjrpc_handle_t;

/**
 * @brief Used to add the callback function
 * @param handle Operation handle
 * @param function_pointer Function to be called
 * @param name Method name
 * @param data Data passed to the function when called
 * @return Returns the mjrpc error code
 */
int mjrpc_add_method(mjrpc_handle_t *handle, mjrpc_function function_pointer, char *name, void *data);

/**
 * @brief Used to delete the callback function
 * @param handle Operation handle
 * @param name Method name
 * @return Returns the mjrpc error code
 */
int mjrpc_del_method(mjrpc_handle_t *handle, char *name);

/**
 * @brief Function for processing RPC request strings
 * @param handle Operation handle
 * @param json_request Request string
 * @param json_return_ptr Pointer to receive the response string
 * @return Returns the mjrpc error code
 */
int mjrpc_process(mjrpc_handle_t *handle, const char *json_reqeust, char **json_return_ptr);

#endif
