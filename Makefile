# update:
# [+] remove bnfc stage, and use the generated Makefile 
# as a reference to generate our own Makefile.

CC = gcc -g
CCFLAGS = --ansi -W -Wall -Wsign-conversion \
	-Wno-unused-parameter \
	-Wno-unused-function \
	-Wno-unneeded-internal-declaration \
	${CC_OPTS}

FLEX = flex
FLEX_OPTS = -Pjavalette_

BISON = bison
BISON_OPTS = -t -pjavalette_

BUILD_DIR := build
SRC_DIR := src
FRONT_END_DIR := $(SRC_DIR)/front_end


FRONT_END_DIR_CC_FILES := $(wildcard $(FRONT_END_DIR)/*.c)
# FRONT_END_DIR_cc_FILES will be like: 
# src/front_end/Absyn.c src/front_end/Buffer.c ...

FRONT_END_DIR_H_FILES := $(wildcard $(FRONT_END_DIR)/*.h)
# FRONT_END_DIR_H_FILES will be like:
# src/front_end/Absyn.h src/front_end/Buffer.h ...

# generate the object files under the build directory
FRONT_END_DIR_OBJS := $(patsubst $(FRONT_END_DIR)/%.c, $(BUILD_DIR)/%.o, $(FRONT_END_DIR_CC_FILES))
# FRONT_END_DIR_OBJS will be like:
# build/Absyn.o build/Buffer.o ...

OBJS := $(FRONT_END_DIR_OBJS)

.PHONY : clean all

clean:
	mkdir -p $(BUILD_DIR)
	rm -rf $(BUILD_DIR)/*

all: TestJavalette

run_parser_test: TestJavalette
	./$(BUILD_DIR)/TestJavalette test/parser/test_1.jl

# generate the object files
$(BUILD_DIR)/%.o: $(FRONT_END_DIR)/%.c $(FRONT_END_DIR_H_FILES)
# special c flag for Lexer.o
	if [ $* = "Lexer" ]; then \
		$(CC) $(CCFLAGS) -Wno-sign-conversion -c $< -o $@; \
	else \
		$(CC) $(CCFLAGS) -c $< -o $@; \
	fi

# test .o files
# test: $(OBJS)
# 	@echo $(OBJS)

TestJavalette: $(OBJS)
	@echo "Linking TestJavalette..."
	$(CC) $(OBJS) -o $(BUILD_DIR)/TestJavalette


# remove this target, because we just need to generate it once,
# thus, we generate it manually.
# also we have to modify the generated files to make it work.
# complie .cf files
# CF_FILE := $(wildcard $(SRC_DIR)/Javalette.cf)
# all:
# 	bnfc -m --c $(CF_FILE) -o $(BUILD_DIR)
# 	cd $(BUILD_DIR) && make
# 	cd -