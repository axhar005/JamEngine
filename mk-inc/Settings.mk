
# Defines executable file name
PROJECT_NAME	= TestGame

# Build mode for project: DEBUG or RELEASE
BUILD_MODE		= DEBUG

# Define all source files required
INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj

# Defines the path for raylib, if different than /usr/local
# comment out if uneeded
CUSTOM_RALIB_PATH = ~/.brew

# Defines compiler flags:
#  -O0									defines optimization level (no optimization, better for debugging)
#  -O1									defines optimization level
#  -g										include debug information on compilation
#  -s										strip unnecesiary data from build -> do not use in debug builds
#  -Wall								turns on most, but not all, compiler warnings
#  -std=c99							defines C language mode (standard C from 1999 revision)
#  -std=gnu99						defines C language mode (GNU C from 1999 revision)
#  -Wno-missing-braces	ignore invalid warning (GCC bug 53119)
#  -D_DEFAULT_SOURCE		use with -std=c99 on Linux and PLATFORM_WEB, required for timespec
CFLAGS += -Wall -Werror -Wextra -Wshadow -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces