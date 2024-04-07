# update:
# [+] remove bnfc stage, and use the generated Makefile 
# as a reference to generate our own Makefile.

CC = g++ -std=c++11 -g
CCFLAGS = -W -Wall \
	-Wno-unused-parameter \
	-Wno-unused-function \
	-Wno-unneeded-internal-declaration

# run with DEBUG flag: make DEBUG=1
ifdef DEBUG
	CCFLAGS += -DDEBUG
endif

# llvm config
LLVM_CC_CONFIG = `llvm-config --cxxflags` -fexceptions
LLVM_LD_CONFIG = `llvm-config --ldflags --libs --system-libs`


BUILD_DIR := build
SRC_DIR := src
FRONT_END_DIR := $(SRC_DIR)/front_end


FRONT_END_DIR_CC_FILES := $(wildcard $(FRONT_END_DIR)/*.C)
# FRONT_END_DIR_cc_FILES will be like: 
# src/front_end/Absyn.C src/front_end/Buffer.C ...

FRONT_END_DIR_H_FILES := $(wildcard $(FRONT_END_DIR)/*.H)
# FRONT_END_DIR_H_FILES will be like:
# src/front_end/Absyn.H src/front_end/Buffer.H ...

# generate the object files under the build directory
FRONT_END_DIR_OBJS := $(patsubst $(FRONT_END_DIR)/%.C, $(BUILD_DIR)/%.o, $(FRONT_END_DIR_CC_FILES))
# FRONT_END_DIR_OBJS will be like:
# build/Absyn.o build/Buffer.o ...

UTILS_DIR := $(SRC_DIR)/utils
UTILS_DIR_H_FILES := $(wildcard $(UTILS_DIR)/*.h)
UTILS_DIR_CC_FILES := $(wildcard $(UTILS_DIR)/*.cpp)
UTILS_DIR_OBJS := $(patsubst $(UTILS_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(UTILS_DIR_CC_FILES))

HEADERS := $(FRONT_END_DIR_H_FILES) $(UTILS_DIR_H_FILES)

OBJS := $(FRONT_END_DIR_OBJS) $(UTILS_DIR_OBJS)

CC_INCLUDES := -I$(FRONT_END_DIR) -I$(UTILS_DIR)


.PHONY : clean all

all: clean jlc

clean:
	mkdir -p $(BUILD_DIR)
	rm -rf $(BUILD_DIR)/*
	rm -rf jlc



run_parser_test: TestJavalette
	./$(BUILD_DIR)/TestJavalette test/parser/test_1.jl

# special c flag for Lexer.o
$(BUILD_DIR)/Lexer.o : $(FRONT_END_DIR)/Lexer.C $(FRONT_END_DIR)/Bison.H 
	$(CC) $(CCFLAGS) -Wno-sign-conversion $(CC_INCLUDES) -c $< -o $@;

$(BUILD_DIR)/JLCLLVMGenerator.o : $(FRONT_END_DIR)/JLCLLVMGenerator.C $(FRONT_END_DIR)/JLCLLVMGenerator.H
	$(CC) $(CCFLAGS) $(CC_INCLUDES) $(LLVM_CC_CONFIG) -c $< -o $@;

# generate the object files
$(BUILD_DIR)/%.o: $(FRONT_END_DIR)/%.C $(HEADERS) 
	$(CC) $(CCFLAGS) $(CC_INCLUDES) -c $< -o $@; \
	
	
# this target is used to generate the jlc executable, 
# output to the root directory directly.
jlc: $(OBJS) $(SRC_DIR)/jlc.cpp
	@echo "Building jlc..."
	$(CC) $(CCFLAGS) $(LLVM_CC_CONFIG) \
		$(CC_INCLUDES) $(OBJS) $(SRC_DIR)/jlc.cpp $(LLVM_LD_CONFIG) -o jlc 

# remove this target, because we just need to generate it once,
# thus, we generate it manually.
# also we have to modify the generated files to make it work.
# complie .Cf files
CF_FILE=$(SRC_DIR)/Javalette.cf
generate_parser:
	bnfc -m --cpp $(CF_FILE) -o $(BUILD_DIR)
	cd $(BUILD_DIR) && make
	cd -