#include "sysBootup.h"

#include <aurora/aurora.h>
#include <aurora/event.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static AuroraInfo initInfo;

static void log_callback(AuroraLogLevel level, const char* module, const char* message, unsigned int len)
{
	const char* levelStr;
	FILE* out = stdout;

	switch (level) {
		case LOG_DEBUG:
			levelStr = "DEBUG";
			break;
		case LOG_INFO:
			levelStr = "INFO";
			break;
		case LOG_WARNING:
			levelStr = "WARNING";
			break;
		case LOG_ERROR:
			levelStr = "ERROR";
			out = stderr;
			break;
		case LOG_FATAL:
			levelStr = "FATAL";
			out = stderr;
			break;
	}

	fprintf(out, "[%s: %s;%s]\n", levelStr, module, message);

	if (level == LOG_FATAL) {
		fflush(out);
		abort();
	}
}

int main(int argc, char* argv[])
{
	const AuroraConfig config = {
		.appName = "Sprout",
		.logCallback = &log_callback,
	};
	initInfo = aurora_initialize(argc, argv, &config);

	if (!aurora_dvd_open("pikmin.us.rev1.iso")) {
		return 1;
	}

    game_main();

	aurora_dvd_close();
	aurora_shutdown();

    return 0;
}
