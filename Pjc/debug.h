#ifndef DEBUG_H
#define DEBUG_H

#include <errno.h>
#include <string.h>
#include <stdio.h>

#define get_errno() ((errno == 0) ? "" : strerror(errno) )

#define log_error(format, ...) fprintf(stderr, "[ERROR] (%s:%d:%s) errno: %s, "\
                               format "\n", __FILE__, __LINE__, __FUNCTION__,\
                               get_errno(), ##__VA_ARGS__ )

#define log(format, ...) fprintf(stderr, "[LOG] (%s:%d:%s) " format "\n", __FILE__, __LINE__,\
                                __FUNCTION__, ##__VA_ARGS__)

#define check_mem(test) if (!(test)) { log_error("%s", "Out of memory"); goto error; }

#endif