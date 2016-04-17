$(SOURCES)

CXX:=g++
CXXFLAGS:=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -I.
TEST_DIR:=./tests
SOURCES_DIR:=./source

TESTS_SRC:=$(shell find $(TEST_DIR) -name *.cpp)
TESTS_BIN=$(TESTS_SRC:%.cpp=%.app)

SOURCES:=$(shell find $(SOURCES_DIR) -name *.cpp)
OBJECTS:=$(SOURCES:%.cpp=%.obj)
HEADERS:=$(shell find $(SOURCES_DIR) -name *.h)

.PHONY: tests
tests: $(OBJECTS) $(TESTS_BIN)

%.obj:%.cpp
	$(CXX) -I. -c $< -o $@

%.app:%.cpp $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $< -o $@
