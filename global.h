#ifndef GLOBAL_H
#define GLOBAL_H

#include "filelogger.h"
#include "httpsessionstore.h"
#include "staticfilecontroller.h"

using namespace stefanfrings;

/** Storage for session cookies */
extern HttpSessionStore *sessionStore;

/** Controller for static files */
extern StaticFileController *staticFileController;

/** Redirects log messages to a file */
extern FileLogger *logger;

extern const char *getKapokVersion();

#endif // GLOBAL_H
