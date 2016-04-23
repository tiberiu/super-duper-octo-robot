SRC_DIR:=./source
BINARIES_SRC_DIR=./source/main
TEST_SRC_DIR:=./tests
BUILD_DIR:=./build
INCLUDES_DIR:=./include
BIN_DIR:=./bin
BIN_TESTS_DIR:=./bin/tests

CXX:=g++
CXXFLAGS:=-I$(INCLUDES_DIR)
LDFLAGS:=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo 

SOURCES:=$(shell find $(SRC_DIR) -name *.cpp)
TESTS_SRC:=$(shell find $(TEST_SRC_DIR) -name *.cpp)

BINARIES_SRC:=$(filter $(BINARIES_SRC_DIR)/%, $(SOURCES))
OBJECTS_SRC:=$(filter-out $(BINARIES_SRC_DIR)/%, $(SOURCES))
HEADERS:=$(shell find $(INCLUDES_DIR) -name *.h)

OBJECTS:=$(patsubst $(SRC_DIR)/%.obj, $(BUILD_DIR)/%.obj, $(OBJECTS_SRC:%.cpp=%.obj))
BINARIES:=$(patsubst $(BINARIES_SRC_DIR)/%.app, $(BIN_DIR)/%.app, $(BINARIES_SRC:%.cpp=%.app))
TESTS_BIN=$(patsubst $(TEST_SRC_DIR)/%.app, $(BIN_TESTS_DIR)/%.app, $(TESTS_SRC:%.cpp=%.app))


all: $(OBJECTS) $(BINARIES) $(TESTS_BIN)

.PHONY: tests
tests: $(OBJECTS) $(TESTS_BIN)

$(BUILD_DIR)/%.obj: source/%.cpp $(HEADERS)
	@echo "Compiling $(notdir $<)"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_TESTS_DIR)/%.app:./tests/%.cpp $(OBJECTS) $(HEADERS)
	@echo "Creating $(notdir $@)"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $< -o $@

$(BIN_DIR)/%.app:./source/main/%.cpp $(OBJECTS) $(HEADERS)
	@echo "Creating $(notdir $@)"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $< -o $@

clean:
	@rm -rf ./build
	@rm -rf ./bin
	@mkdir -p build
	@mkdir -p bin
