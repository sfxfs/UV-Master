#ifndef _RPC_CJSON_H_
#define _RPC_CJSON_H_

#include "cJSON.h"

#define JRPC_VERSION "2.0"

#define JRPC_PARSE_ERROR 		-32700
#define JRPC_INVALID_REQUEST 	-32600
#define JRPC_METHOD_NOT_FOUND 	-32601
#define JRPC_INVALID_PARAMS 	-32603
#define JRPC_INTERNAL_ERROR 	-32693

typedef struct {
	void *data;
	int error_code;
	char * error_message;
} jrpc_context;

typedef cJSON* (*jrpc_function)(jrpc_context *context, cJSON *params, cJSON* id);

struct jrpc_procedure {
	char * name;
	jrpc_function function;
	void *data;
};

typedef struct str_free
{
	char **str_array;
	int total;
	int cur;
} str_free_t;

typedef struct rpc_handle
{
    int procedure_count;
	struct jrpc_procedure *procedures;
	int debug_level;
	str_free_t message;
} rpc_handle_t;

int	  rpc_add_method (rpc_handle_t *handle, jrpc_function function_pointer, char *name, void * data);
int   rpc_del_method (rpc_handle_t *handle, char *name);
char* rpc_process 	 (rpc_handle_t *handle, const char *json_req, size_t req_len);

#endif
