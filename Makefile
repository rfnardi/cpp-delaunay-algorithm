OUT = conversor-stl
CFLAGS := $(CFLAGS)
CPP_FILES := $(CPP_FILES) main.cpp
# $(CC) -g -save-temps $(CFLAGS) source.c
compile_conversor:
	g++ $(CPP_FILES) -o $(OUT) $(CFLAGS)