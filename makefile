cc := g++
cflags := -std=c++11 -Wall -static-libgcc -mwindows
ldlibs :=

program_lib_prefix := D:/Library/msys64/mingw64
program_include_dirs := $(program_lib_prefix)/include/SDL2
program_libraries_dirs := $(program_lib_prefix)/lib
cflags += $(foreach include, $(program_include_dirs), -I$(include))
ldlibs += -L$(program_libraries_dirs)
ldlibs += -lmingw32
ldlibs += -lfreetype
ldlibs += -lSDL2_ttf
ldlibs += -lSDL2main
ldlibs += -lSDL2

source_dir := source
build_dir := build
release_dir := release
log_dir := log

srcs := $(wildcard $(addprefix $(source_dir)/, *.cpp))
srcs_notdir = $(notdir $(srcs))
objs := $(addprefix $(build_dir)/, $(srcs_notdir:.cpp=.o))
target := $(release_dir)/MiGong.exe

.PHONY: all clean

all: $(release_dir) $(build_dir) $(log_dir) $(target)

$(target): $(objs)
	$(cc) $^ $(ldlibs) -o $@ $(cflags)

$(build_dir)/%.o: $(source_dir)/%.cpp
	$(cc) -c $< -o $@ $(cflags)

$(build_dir):
	mkdir -p $@

$(release_dir):
	mkdir -p $@

$(log_dir):
	mkdir -p $@

clean:
	rm -rf $(build_dir)

nothing:
	echo $$PATH