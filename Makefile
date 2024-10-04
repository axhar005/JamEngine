#--- APPLICATION NAME ---#
NAME = JamEngine

#--- COMPILER AND OPTIONS ---#
CXX = g++
CC = gcc
CFLAGS = -Wall -std=c++11 -O2 -g
CFLAGS += -MMD -MP
SRC_DIR = src

#--- OS DETECTION ---#
ifeq ($(OS),Windows_NT)
    # Configuration for Windows (assuming MinGW)
    UNAME_S = Windows
else
    UNAME_S := $(shell uname -s)
endif

#--- RAYLIB CONFIGURATION ---#
RAYLIB_DIR = lib/raylib
RAYLIB_BUILD_DIR = $(RAYLIB_DIR)/build
RAYLIB_REPO_URL = https://github.com/raysan5/raylib.git

# Check if raylib is installed on the system
ifeq ($(UNAME_S),Linux)
    RAYLIB_SYSTEM_LIB := /usr/local/lib/libraylib.a
    RAYLIB_SYSTEM_INCLUDE := /usr/local/include/raylib.h
else ifeq ($(UNAME_S),Darwin)
    RAYLIB_SYSTEM_LIB := /usr/local/lib/libraylib.a
    RAYLIB_SYSTEM_INCLUDE := /usr/local/include/raylib.h
else ifeq ($(UNAME_S),Windows)
    RAYLIB_SYSTEM_LIB := C:/raylib/lib/libraylib.a
    RAYLIB_SYSTEM_INCLUDE := C:/raylib/include/raylib.h
endif

# Determine whether to use system-installed raylib or build local
ifeq ($(wildcard $(RAYLIB_SYSTEM_LIB)),)
    # raylib not found on the system, use local version
    USE_LOCAL_RAYLIB = true
else
    USE_LOCAL_RAYLIB = false
endif

USE_LOCAL_RAYLIB = true

# Include paths
CFLAGS += -Iinclude

ifeq ($(USE_LOCAL_RAYLIB),true)
    CFLAGS += -I$(RAYLIB_DIR)/src -I$(RAYLIB_DIR)/src/external
    LDFLAGS += -L$(RAYLIB_BUILD_DIR) -lraylib
else
    CFLAGS += -I$(dir $(RAYLIB_SYSTEM_INCLUDE))
    LDFLAGS += -L$(dir $(RAYLIB_SYSTEM_LIB)) -lraylib
endif

# Add OS-specific linker flags
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lGL -lm -lpthread -ldl -lrt -lX11
else ifeq ($(UNAME_S),Darwin)
    LDFLAGS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
else ifeq ($(UNAME_S),Windows)
    LDFLAGS += -lopengl32 -lgdi32 -lwinmm
endif

#--- SOURCE FILES AND OBJECTS ---#
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_DIR = object
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

#--- RULES ---#
all: $(NAME)

$(NAME): $(OBJ) $(RAYLIB_BUILD_DIR)/libraylib.a
	$(CXX) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@

# Build raylib if using local version
$(RAYLIB_BUILD_DIR)/libraylib.a:
	@if [ "$(USE_LOCAL_RAYLIB)" = "true" ]; then \
		if [ ! -d "$(RAYLIB_DIR)" ]; then \
			echo "Raylib not found on the system. Cloning Raylib..."; \
			git clone --depth=1 $(RAYLIB_REPO_URL) $(RAYLIB_DIR); \
		fi; \
		echo "Building local Raylib..."; \
		mkdir -p $(RAYLIB_BUILD_DIR); \
		cd $(RAYLIB_BUILD_DIR) && cmake .. && $(MAKE); \
	else \
		echo "Using system-installed Raylib."; \
	fi

run:
	./$(NAME)

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
	@if [ "$(USE_LOCAL_RAYLIB)" = "true" ]; then \
		$(MAKE) -C $(RAYLIB_BUILD_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME)
	@if [ "$(USE_LOCAL_RAYLIB)" = "true" ]; then \
		rm -rf $(RAYLIB_BUILD_DIR); \
	fi

rclean: fclean
	rm -rf $(RAYLIB_DIR);

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
