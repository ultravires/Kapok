#ifndef GLOBAL_H
#define GLOBAL_H

#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "filelogger.h"

using namespace stefanfrings;

/** Storage for session cookies */
extern HttpSessionStore* sessionStore;

/** Controller for static files */
extern StaticFileController* staticFileController;

/** Redirects log messages to a file */
extern FileLogger* logger;

#endif // GLOBAL_H
