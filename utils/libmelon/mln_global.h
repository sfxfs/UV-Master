
/*
 * Copyright (C) Niklaus F.Schen.
 */

#ifndef __MLN_GLOBAL_H
#define __MLN_GLOBAL_H
#include <stdio.h>
#include "mln_types.h"

#ifndef __MLN_GLOBAL
#define EXTERN extern
#else
#define EXTERN
#endif

EXTERN void *global_unused_var;

#endif

