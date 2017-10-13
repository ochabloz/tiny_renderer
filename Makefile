CC      := gcc
CFLAGS    := -g -Wall
CFLAGS  += -std=gnu99
# Compile the test file, ignore the main function of sample.c, the sample.c code with the CPPUTEST macro
CXXFLAGS  += -D CPPUTEST
# CPPUTest is C++Write, so using g++ To compile the test file
CPP     := g++
CPPFLAGS  := -g -Wall
CPPFLAGS  += -I$(CPPUTEST_HOME)/include
CXXFLAGS  += -I include/

LDFLAGS := -L$(CPPUTEST_HOME)/lib -lCppUTest

SRC_DIR := src/
OBJ_DIR := objs/
OBJTST_DIR := objs/tests/
SRC_FILES := $(wildcard $(SRC_DIR)*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))


TST_FILES := $(wildcard tests/*.c)
TST_OBJ_FILES := $(patsubst tests/%.c, $(OBJTST_DIR)%.o,$(TST_FILES))


ALL_TESTS := run_all.c

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJTST_DIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<


# Additional compiled test program
test: $(OBJ_FILES) $(TST_OBJ_FILES)
	$(CPP) -o $(OBJ_DIR)$@ $^ $(LDFLAGS)


objs/tests/%.o: tests/%.c
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<



run: test
	$(OBJ_DIR)$<
.PHONY: clean
clean:
	@echo "clean..."
	rm -rf $(OBJ_DIR)
