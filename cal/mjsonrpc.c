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

#include <stdlib.h>
#include <string.h>

#include "mjsonrpc.h"

#define JRPC_VERSION "2.0"

int mjrpc_add_method(mjrpc_handle_t *handle, mjrpc_function function_pointer, char *name, void *data)
{
    int i = handle->info_count++;
    if (!handle->infos)
        handle->infos = malloc(sizeof(struct mjrpc_cb_info));
    else
    {
        struct mjrpc_cb_info *ptr = realloc(handle->infos,
                                            sizeof(struct mjrpc_cb_info) * handle->info_count);
        if (!ptr)
            return MJRPC_ERROR_MEM_ALLOC_FAILED;
        handle->infos = ptr;
    }
    if ((handle->infos[i].name = strdup(name)) == NULL)
        return MJRPC_ERROR_MEM_ALLOC_FAILED;
    handle->infos[i].function = function_pointer;
    handle->infos[i].data = data;
    return MJRPC_OK;
}

static void cb_info_destroy(struct mjrpc_cb_info *info)
{
    if (info->name)
    {
        free(info->name);
        info->name = NULL;
    }
    if (info->data)
    {
        free(info->data);
        info->data = NULL;
    }
}

int mjrpc_del_method(mjrpc_handle_t *handle, char *name)
{
    int i;
    int found = 0;
    if (handle->infos)
    {
        for (i = 0; i < handle->info_count; i++)
        {
            if (found)
                handle->infos[i - 1] = handle->infos[i];
            else if (!strcmp(name, handle->infos[i].name))
            {
                found = 1;
                cb_info_destroy(&(handle->infos[i]));
            }
        }
        if (found)
        {
            handle->info_count--;
            if (handle->info_count)
            {
                struct mjrpc_cb_info *ptr = realloc(handle->infos,
                                                    sizeof(struct mjrpc_cb_info) * handle->info_count);
                if (!ptr)
                    return MJRPC_ERROR_MEM_ALLOC_FAILED;
                handle->infos = ptr;
            }
            else
                handle->infos = NULL;
        }
    }
    else
        return MJRPC_ERROR_NOT_FOUND;
    return MJRPC_OK;
}

static cJSON *rpc_err(mjrpc_handle_t *handle, int code, char *message, cJSON *id)
{
    cJSON *result_root = cJSON_CreateObject();
    cJSON *error_root = cJSON_CreateObject();
    if (result_root == NULL || error_root == NULL)
        return NULL;

    cJSON_AddNumberToObject(error_root, "code", code);
    if (message)
    {
        cJSON_AddStringToObject(error_root, "message", message);
        free(message);
    }

    cJSON_AddStringToObject(result_root, "jsonrpc", JRPC_VERSION);

    cJSON_AddItemToObject(result_root, "error", error_root);

    if (id)
        cJSON_AddItemToObject(result_root, "id", id);
    else
        cJSON_AddItemToObject(result_root, "id", cJSON_CreateNull());

    return result_root;
}

static cJSON *rpc_ok(cJSON *result, cJSON *id)
{
    cJSON *result_root = cJSON_CreateObject();

    cJSON_AddStringToObject(result_root, "jsonrpc", JRPC_VERSION);

    cJSON_AddItemToObject(result_root, "result", result);

    if (id)
        cJSON_AddItemToObject(result_root, "id", id);
    else
        cJSON_AddItemToObject(result_root, "id", cJSON_CreateNull());

    return result_root;
}

static cJSON *invoke_procedure(mjrpc_handle_t *handle, char *name, cJSON *params, cJSON *id)
{
    cJSON *returned = NULL;
    int procedure_found = 0;
    mjrpc_ctx_t ctx;
    ctx.error_code = 0;
    ctx.error_message = NULL;
    int i = handle->info_count;
    while (i--)
    {
        if (!strcmp(handle->infos[i].name, name))
        {
            procedure_found = 1;
            ctx.data = handle->infos[i].data;
            returned = handle->infos[i].function(&ctx, params, id);
            break;
        }
    }
    if (!procedure_found)
        return rpc_err(handle, JRPC_METHOD_NOT_FOUND, strdup("Method not found."), id);
    else
    {
        if (ctx.error_code)
            return rpc_err(handle, ctx.error_code, ctx.error_message, id);
        else
            return rpc_ok(returned, id);
    }
}

static cJSON *rpc_invoke_method(mjrpc_handle_t *handle, cJSON *request)
{
    cJSON *method, *params, *id;

    if (strcmp("2.0", cJSON_GetObjectItem(request, "jsonrpc")->valuestring) != 0)
        return rpc_err(handle, JRPC_INVALID_REQUEST, strdup("Valid request received: JSONRPC version error."), NULL);

    method = cJSON_GetObjectItem(request, "method");
    if (method != NULL && method->type == cJSON_String)
    {
        params = cJSON_GetObjectItem(request, "params");

        id = cJSON_GetObjectItem(request, "id");
        if (id->type == cJSON_NULL || id->type == cJSON_String || id->type == cJSON_Int)
        {
            // We have to copy ID because using it on the reply and deleting the response Object will also delete ID
            cJSON *id_copy = NULL;
            if (id != NULL)
                id_copy =
                    (id->type == cJSON_String) ? cJSON_CreateString(
                                                     id->valuestring)
                                               : cJSON_CreateNumber(id->valueint);
            return invoke_procedure(handle, method->valuestring, params, id_copy);
        }
        return rpc_err(handle, JRPC_INVALID_REQUEST, strdup("Valid request received: No 'id' member or wrong type"), NULL);
    }
    return rpc_err(handle, JRPC_INVALID_REQUEST, strdup("Valid request received: No 'method' member or wrong type"), NULL);
}

static cJSON *rpc_invoke_method_array(mjrpc_handle_t *handle, cJSON *request)
{
    int array_size = cJSON_GetArraySize(request);
    if (array_size <= 0)
        return rpc_err(handle, JRPC_INVALID_REQUEST, strdup("Valid request received: Empty JSON array."), NULL);

    cJSON *return_json_array = cJSON_CreateArray();
    for (int i = 0; i < array_size; i++)
        cJSON_AddItemToArray(return_json_array, rpc_invoke_method(handle, cJSON_GetArrayItem(request, i)));

    return return_json_array;
}

int mjrpc_process(mjrpc_handle_t *handle, const char *json_reqeust, char **json_return_ptr)
{
    if (json_reqeust == NULL)
        return MJRPC_ERROR_EMPTY_REQUST;

    cJSON *request = cJSON_Parse(json_reqeust);
    if (request == NULL)
    {
        *json_return_ptr = cJSON_PrintUnformatted(rpc_err(handle, JRPC_PARSE_ERROR, strdup("Parse error: Not in JSON format."), NULL));
        return MJRPC_ERROR_PARSE_FAILED;
    }

    cJSON *cjson_return = NULL;
    if (request->type == cJSON_Array)
    {
        cjson_return = rpc_invoke_method_array(handle, request);
    }
    else if (request->type == cJSON_Object)
    {
        cjson_return = rpc_invoke_method(handle, request);
    }
    else
    {
        cjson_return = rpc_err(handle, JRPC_INVALID_REQUEST, strdup("Valid request received: Not a JSON object or array."), NULL);
    }

    *json_return_ptr = cJSON_PrintUnformatted(cjson_return);
    cJSON_Delete(cjson_return);
    cJSON_Delete(request);

    return MJRPC_OK;
}
