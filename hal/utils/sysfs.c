/*****************************************************************************
* | File        :   luckfox_sysfs.c
* | Author      :   luckfox team
* | Function    :   sysfs
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2023-08-01
* | Info        :   Basic version
*
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "log.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sysfs.h"

static int _write_sysfs_int(const char *filename, const char *basedir, int val,
            bool verify)
{
    int ret = 0;
    FILE *sysfsfp;
    int test;
    char *temp = (char *)malloc(strlen(basedir) + strlen(filename) + 2);
    if (!temp)
        return -ENOMEM;

    ret = sprintf(temp, "%s/%s", basedir, filename);
    if (ret < 0)
        goto error_free;

    sysfsfp = fopen(temp, "w");
    if (!sysfsfp) {
        ret = -errno;
        log_debug("failed to open %s", temp);
        goto error_free;
    }

    ret = fprintf(sysfsfp, "%d", val);
    if (ret < 0) {
        if (fclose(sysfsfp))
            log_debug("Failed to close dir: %s", strerror(errno));

        goto error_free;
    }

    ret = 0;

    if (fclose(sysfsfp)) {
        ret = -errno;
        goto error_free;
    }

    if (verify) {
        sysfsfp = fopen(temp, "r");
        if (!sysfsfp) {
            ret = -errno;
            log_debug("failed to open %s", temp);
            goto error_free;
        }

        if (fscanf(sysfsfp, "%d", &test) != 1) {
            ret = errno ? -errno : -ENODATA;
            if (fclose(sysfsfp))
                log_debug("Failed to close dir: %s", strerror(errno));

            goto error_free;
        }

        if (fclose(sysfsfp)) {
            ret = -errno;
            goto error_free;
        }

        if (test != val) {
            log_debug("Possible failure in int write %d to %s/%s",
                val, basedir, filename);
            ret = -1;
        }
    }

error_free:
    free(temp);
    return ret;
}

int write_sysfs_int(const char *filename, const char *basedir, int val)
{
	return _write_sysfs_int(filename, basedir, val, false);
}

int write_sysfs_int_and_verify(const char *filename, const char *basedir,
            int val)
{
	return _write_sysfs_int(filename, basedir, val, true);
}

static int _write_sysfs_string(const char *filename, const char *basedir,
            const char *val, bool verify)
{
    int ret = 0;
    FILE  *sysfsfp;
    char *temp = (char *)malloc(strlen(basedir) + strlen(filename) + 2);

    if (!temp) {
        log_debug("Memory allocation failed");
        return -ENOMEM;
    }

    ret = sprintf(temp, "%s/%s", basedir, filename);
    if (ret < 0)
        goto error_free;

    sysfsfp = fopen(temp, "w");
    if (!sysfsfp) {
        ret = -errno;
        log_debug("Could not open %s", temp);
        goto error_free;
    }

    ret = fprintf(sysfsfp, "%s", val);
    if (ret < 0) {
        if (fclose(sysfsfp))
            log_debug("Failed to close dir: %s", strerror(errno));

        goto error_free;
    }

    if (fclose(sysfsfp)) {
        ret = -errno;
        goto error_free;
    }

    if (verify) {
        sysfsfp = fopen(temp, "r");
        if (!sysfsfp) {
            ret = -errno;
            log_debug("Could not open file to verify");
            goto error_free;
        }

        if (fscanf(sysfsfp, "%s", temp) != 1) {
            ret = errno ? -errno : -ENODATA;
            if (fclose(sysfsfp))
                log_debug("Failed to close dir: %s", strerror(errno));

            goto error_free;
        }

        if (fclose(sysfsfp)) {
            ret = -errno;
            goto error_free;
        }

        if (strcmp(temp, val) != 0) {
            log_debug("Possible failure in string write of %s "
                "Should be %s written to %s/%s", temp, val,
                basedir, filename);
            ret = -1;
        }
    }

error_free:
    free(temp);

    return ret;
}

int write_sysfs_string_and_verify(const char *filename, const char *basedir,
            const char *val)
{
    return _write_sysfs_string(filename, basedir, val, true);
}

int write_sysfs_string(const char *filename, const char *basedir,
        const char *val)
{
    return _write_sysfs_string(filename, basedir, val, false);
}

int read_sysfs_posint(const char *filename, const char *basedir)
{
    int ret;
    FILE  *sysfsfp;
    char *temp = (char *)malloc(strlen(basedir) + strlen(filename) + 2);

    if (!temp) {
        log_debug("Memory allocation failed");
        return -ENOMEM;
    }

    ret = sprintf(temp, "%s/%s", basedir, filename);
    if (ret < 0)
        goto error_free;

    sysfsfp = fopen(temp, "r");
    if (!sysfsfp) {
        ret = -errno;
        goto error_free;
    }

    errno = 0;
    if (fscanf(sysfsfp, "%d\n", &ret) != 1) {
        ret = errno ? -errno : -ENODATA;
        if (fclose(sysfsfp))
            log_debug("Failed to close dir: %s", strerror(errno));

        goto error_free;
    }

    if (fclose(sysfsfp))
        ret = -errno;

error_free:
    free(temp);

    return ret;
}

int read_sysfs_float(const char *filename, const char *basedir, float *val)
{
    int ret = 0;
    FILE  *sysfsfp;
    char *temp = (char *)malloc(strlen(basedir) + strlen(filename) + 2);

    if (!temp) {
        log_debug("Memory allocation failed");
        return -ENOMEM;
    }

    ret = sprintf(temp, "%s/%s", basedir, filename);
    if (ret < 0)
        goto error_free;

    sysfsfp = fopen(temp, "r");
    if (!sysfsfp) {
        ret = -errno;
        goto error_free;
    }

    errno = 0;
    if (fscanf(sysfsfp, "%f\n", val) != 1) {
        ret = errno ? -errno : -ENODATA;
        if (fclose(sysfsfp))
            log_debug("Failed to close dir: %s", strerror(errno));

        goto error_free;
    }

    if (fclose(sysfsfp))
        ret = -errno;

error_free:
    free(temp);

    return ret;
}

int read_sysfs_string(const char *filename, const char *basedir, char *str)
{
    int ret = 0;
    FILE  *sysfsfp;
    char *temp = (char *)malloc(strlen(basedir) + strlen(filename) + 2);

    if (!temp) {
        log_debug("Memory allocation failed");
        return -ENOMEM;
    }

    ret = sprintf(temp, "%s/%s", basedir, filename);
    if (ret < 0)
        goto error_free;

    sysfsfp = fopen(temp, "r");
    if (!sysfsfp) {
        ret = -errno;
        goto error_free;
    }

    errno = 0;
    if (fscanf(sysfsfp, "%s\n", str) != 1) {
        ret = errno ? -errno : -ENODATA;
        if (fclose(sysfsfp))
            log_debug("Failed to close dir: %s", strerror(errno));

        goto error_free;
    }

    if (fclose(sysfsfp))
        ret = -errno;

error_free:
    free(temp);

    return ret;
}
