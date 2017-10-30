CC      := gcc
CFLAGS    := -g -Wall
CFLAGS  += -std=gnu99
# Compile the test file, ignore the main function of sample.c, the sample.c code with the CPPUTEST macro
CXXFLAGS  += -D CPPUTEST
# CPPUTest is C++Write, so using g++ To compile the test file
CPP     := g++
CPPFLAGS  := -g -Wall
CPPFLAGS  += -I$(CPPUTEST_HOME)/include

# Flags included for both cpp and c compilation
CXXFLAGS  += -I include/
LDFLAGS := -L$(CPPUTEST_HOME)/lib -lCppUTest

SRC_DIR := src/

OBJ_DIR := objs/
SRC_FILES := $(wildcard $(SRC_DIR)*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))

OBJTST_DIR := objs/tests/
TST_FILES := $(wildcard tests/*.c)
TST_OBJ_FILES := $(patsubst tests/%.c, $(OBJTST_DIR)%.o,$(TST_FILES))


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJTST_DIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<


# Additional compiled test program
test: $(OBJ_FILES) $(TST_OBJ_FILES)
	$(CPP) -o $(OBJ_DIR)$@ $^ $(LDFLAGS)
	$(OBJ_DIR)$@


objs/tests/%.o: tests/%.c
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<


all: test


.PHONY: clean
clean:
	@echo "clean..."
	rm -rf $(OBJ_DIR)
	rm *.bmp
