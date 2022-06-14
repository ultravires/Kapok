#include "global.h"

HttpSessionStore     *sessionStore;
StaticFileController *staticFileController;
FileLogger           *logger;
Config               *config;

const char *getKapokVersion() { return "0.0.1"; }
