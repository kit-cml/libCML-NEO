# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC_DYNAMIC := libcml.so
TARGET_EXEC_STATIC := libcml.a

BUILD_DIR := ./build
SRC_DIRS := ./src

# CXX to set the compiler
CXX := g++

# CC to set the compiler
CC := gcc


# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Flags for C++
CXXFLAGS := -fPIC -fpermissive -std=c++11 -I/opt/prog/sundials/sundials-5.7.0/include
#CXXFLAGS := -fPIC -fpermissive

# Flags for C
CFLAGS := -fPIC

# Flags for binary
LDFLAGS := -L/usr/local/lib ./libs/libsundials_cvode.a ./libs/libsundials_nvecserial.a

# Static libs build
LIB_BUILD_STATIC := gcc-ar -rcs

# Dynamic libs build
#LIB_BUILD_DYNAMIC := $(CXX) -shared $(LDFLAGS)

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC_STATIC): $(OBJS)
	$(LIB_BUILD_STATIC) $@ $(OBJS)
  

#$(BUILD_DIR)/$(TARGET_EXEC_DYNAMIC): $(OBJS)
#  $(LIB_BUILD_DYNAMIC) $(OBJS) -o $@


# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR) 

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
