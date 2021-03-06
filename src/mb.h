#ifndef MB_H
#define MB_H

#include <stdbool.h>		/* bool, true, false */
#include <stdio.h>		/* FILE */

#include "../nginx/http_parser.h"	/* http_parser */

#define PGNAME		"mb"
#define WATCHDOG_MS	100

#define MB_MAX_CLIENTS	50000	/* maximum number of clients per connections */
#define MB_CFG_COOKIES	0	/* default usage of cookies */
#define MB_CFG_DURATION	5	/* default duration [s] */
#define MB_CFG_THREADS	1	/* default number of threads */
#define MB_FD_START	128	/* usually start with fd 5, but give us some more room */
#define MB_TLS_VERSION 0	/* SSL version: auto(0), see cfg.ssl_version */

/* Statistics */
typedef struct statistics {
  uint64_t start;		/* time [us] since the Epoch the test started */
  uint64_t err_conn;		/* number of connection-related errors during the test run */
  uint64_t err_status;		/* number of HTTP status errors during the test run */
  uint64_t err_parser;		/* number of HTTP errors caused by parsing HTTP responses */
  FILE *fd;			/* file descriptor of a file to write statistics to */
} statistics;

/* Client options */
typedef struct config {
  bool cookies;			/* use session cookies */
  uint64_t duration;		/* duration of the test run [s] */
  char *file_req;		/* input file with individual requests */
  char *file_resp;		/* JMeter-style output file with individual response statistics */
  uint64_t ramp_up;		/* thread ramp-up time [s] */
  int ssl_version;		/* SSL version: auto(0), SSLv3(1) - TLS1.2(4) */
  uint64_t threads;		/* number of threads */

  bool ssl;			/* seen https protocol during parsing file with requests => initialize ssl */
} config;

/* Module variables */
extern config cfg;
extern statistics stats;
extern http_parser_settings parser_settings;

/* Module functions */
extern uint64_t time_us();

#endif /* MB_H */
