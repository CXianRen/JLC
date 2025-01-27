# update:
# [+] remove bnfc stage, and use the generated Makefile 
# as a reference to generate our own Makefile.

CC = g++ -std=c++11 -g
CCFLAGS = -W -Wall \
	-Wno-unused-parameter \
	-Wno-unused-function 

# run with DEBUG flag: make DEBUG=1
ifdef DEBUG
	CCFLAGS += -DDEBUG
endif

BUILD_DIR := build
SRC_DIR := src

PARSER_DIR := parser
TYPECHECKER_DIR := typechecker
LLVM_DIR := llvm
COMMON_DIR := common
TEST_DIR := test

# for test docker, due to the dependenced libraries are not installed correctly.
LIBS_DIR := libs
LD_FLAGS = -L$(BUILD_DIR)/$(LIBS_DIR)


PARSER_DIR_H_FILES := $(wildcard $(SRC_DIR)/$(PARSER_DIR)/*.H)
PARSER_DIR_CC_FILES := $(wildcard $(SRC_DIR)/$(PARSER_DIR)/*.C)
PARSER_DIR_OBJS := $(patsubst $(SRC_DIR)/$(PARSER_DIR)/%.C, $(BUILD_DIR)/$(PARSER_DIR)/%.o, $(PARSER_DIR_CC_FILES))

TYPECHECKER_DIR_H_FILES := $(wildcard $(SRC_DIR)/$(TYPECHECKER_DIR)/*.h)
TYPECHECKER_DIR_CC_FILES := $(wildcard $(SRC_DIR)/$(TYPECHECKER_DIR)/*.cpp)
TYPECHECKER_DIR_OBJS := $(patsubst $(SRC_DIR)/$(TYPECHECKER_DIR)/%.cpp, $(BUILD_DIR)/$(TYPECHECKER_DIR)/%.o, $(TYPECHECKER_DIR_CC_FILES))

LLVM_DIR_H_FILES := $(wildcard $(SRC_DIR)/$(LLVM_DIR)/*.h)
LLVM_DIR_CC_FILES := $(wildcard $(SRC_DIR)/$(LLVM_DIR)/*.cpp)
LLVM_DIR_OBJS := $(patsubst $(SRC_DIR)/$(LLVM_DIR)/%.cpp, $(BUILD_DIR)/$(LLVM_DIR)/%.o, $(LLVM_DIR_CC_FILES))

COMMON_DIR_H_FILES := $(wildcard $(SRC_DIR)/$(COMMON_DIR)/*.h)
COMMON_DIR_CC_FILES := $(wildcard $(SRC_DIR)/$(COMMON_DIR)/*.cpp)
COMMON_DIR_OBJS := $(patsubst $(SRC_DIR)/$(COMMON_DIR)/%.cpp, $(BUILD_DIR)/$(COMMON_DIR)/%.o, $(COMMON_DIR_CC_FILES))

$(info "PARSER_DIR_OBJS:"$(PARSER_DIR_OBJS))
$(info "TYPECHECKER_DIR_OBJS:"$(TYPECHECKER_DIR_OBJS))
$(info "LLVM_DIR_OBJS:"$(LLVM_DIR_OBJS))
$(info "COMMON_DIR_OBJS:"$(COMMON_DIR_OBJS))

HEADERS := $(PARSER_DIR_H_FILES) \
		   $(TYPECHECKER_DIR_H_FILES) \
		   $(LLVM_DIR_H_FILES) \
		   $(COMMON_DIR_H_FILES)

OBJS := $(PARSER_DIR_OBJS) \
		$(TYPECHECKER_DIR_OBJS) \
		$(LLVM_DIR_OBJS) \
		$(COMMON_DIR_OBJS)

CC_INCLUDES := -I$(SRC_DIR) \
			   -I$(SRC_DIR)/$(PARSER_DIR) \
			   -I$(SRC_DIR)/$(TYPECHECKER_DIR) \
			   -I$(SRC_DIR)/$(LLVM_DIR) \
			   -I$(SRC_DIR)/$(COMMON_DIR)

.PHONY : clean all

all: clean jlc

clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf jlc
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/$(PARSER_DIR)
	mkdir -p $(BUILD_DIR)/$(TYPECHECKER_DIR)
	mkdir -p $(BUILD_DIR)/$(LLVM_DIR)
	mkdir -p $(BUILD_DIR)/$(COMMON_DIR)
	mkdir -p $(BUILD_DIR)/$(TEST_DIR)

# generate the object files
$(BUILD_DIR)/$(COMMON_DIR)/%.o: $(SRC_DIR)/$(COMMON_DIR)/%.cpp $(HEADERS) 
	$(CC) $(CCFLAGS) $(CC_INCLUDES) -c $< -o $@;

$(BUILD_DIR)/$(PARSER_DIR)/%.o: $(SRC_DIR)/$(PARSER_DIR)/%.C $(HEADERS)
	$(CC) $(CCFLAGS) $(CC_INCLUDES) -c $< -o $@;

# special c flag for Lexer.o
$(BUILD_DIR)/$(PARSER_DIR)/Lexer.o : $(SRC_DIR)/$(PARSER_DIR)/Lexer.C $(SRC_DIR)/$(PARSER_DIR)/Bison.H 
	$(CC) $(CCFLAGS) -Wno-sign-conversion $(CC_INCLUDES) -c $< -o $@;

$(BUILD_DIR)/$(TYPECHECKER_DIR)/%.o: $(SRC_DIR)/$(TYPECHECKER_DIR)/%.cpp $(HEADERS)
	$(CC) $(CCFLAGS) $(CC_INCLUDES) -c $< -o $@;

$(BUILD_DIR)/$(LLVM_DIR)/%.o: $(SRC_DIR)/$(LLVM_DIR)/%.cpp $(HEADERS)
	$(CC) $(CCFLAGS) $(CC_INCLUDES) $(LLVM_CC_CONFIG) -c $< -o $@;
	

# this target is used to generate the jlc executable, 
# output to the root directory directly.
jlc: $(OBJS) $(SRC_DIR)/jlc.cpp
	@echo "Building jlc..."
	$(CC) $(CCFLAGS) $(LLVM_CC_CONFIG) \
		$(CC_INCLUDES) $(OBJS) $(SRC_DIR)/jlc.cpp $(LD_FLAGS) $(LLVM_LD_CONFIG)  -o jlc 

# test target
TEST_TARGETS := $(patsubst $(SRC_DIR)/$(TEST_DIR)/%.cpp, $(BUILD_DIR)/$(TEST_DIR)/%, $(wildcard $(SRC_DIR)/$(TEST_DIR)/*.cpp))
$(info "TEST_TARGETS:"$(TEST_TARGETS))

$(BUILD_DIR)/$(TEST_DIR)/%: $(SRC_DIR)/$(TEST_DIR)/%.cpp $(OBJS) 
	@echo "Building test: $@..."
	$(CC) $(CCFLAGS) $(CC_INCLUDES) $(OBJS) $(LD_FLAGS) $< -o $@

test: $(TEST_TARGETS)
	@echo "All tests are built."

# remove this target, because we just need to generate it once,
# thus, we generate it manually.
# also we have to modify the generated files to make it work.
# complie .Cf files
FLEX = flex
FLEX_OPTS = -Pjavalette_
BISON = bison
BISON_OPTS = -t -pjavalette_

CF_FILE=$(SRC_DIR)/Javalette.cf
gen:
	@echo "clean the parser directory..."
	rm -rf $(SRC_DIR)/$(PARSER_DIR)/*
	@echo "Generating parser..."
	bnfc -m --cpp $(CF_FILE) -o $(SRC_DIR)/$(PARSER_DIR)
	@echo "Generating parser done."

	@echo "generate the Lexer.C and Parser.C files..."
	cd $(SRC_DIR)/$(PARSER_DIR) && \
	${FLEX} ${FLEX_OPTS} -oLexer.C Javalette.l && \
	${BISON} ${BISON_OPTS} Javalette.y \
		-o Parser.C
	# remove the Test.C file
	rm -f $(SRC_DIR)/$(PARSER_DIR)/Test.C