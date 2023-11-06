#ifndef CONFIG_UTILS_H
#define CONFIG_UTILS_H

#include <cJSON.h>

double cjson_value_analysis_double(cJSON *params,const char *str);
int cjson_value_analysis_int(cJSON *params, const char *str);
char *cjson_value_analysis_string(cJSON *params, const char *str);

#endif
