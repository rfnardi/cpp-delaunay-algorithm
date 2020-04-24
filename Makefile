OUT = conversor-stl
CFLAGS := $(CFLAGS)
CPP_FILES := $(CPP_FILES) conversor_stl.cpp
compile_conversor:
	g++ $(CPP_FILES) -o $(OUT) $(CFLAGS)