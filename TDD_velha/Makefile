# Compilador e flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O0 -g --coverage
LDFLAGS := --coverage
INCLUDES := -Iinclude -Itests/third_party

# Ferramentas
CPPLINT ?= cpplint

# Estrutura de build
BUILD := build
TARGET := $(BUILD)/unit_tests   # <— evita conflito com a pasta build/tests

# Fontes
SRCS := src/velha.cpp tests/catch_main.cpp tests/testa_velha.cpp
OBJS := $(SRCS:%.cpp=$(BUILD)/%.o)

.PHONY: all test lint static valgrind coverage clean

all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

# Compila .cpp gerando .o espelhado em build/
$(BUILD)/%.o: %.cpp | $(BUILD)/src $(BUILD)/tests $(BUILD)/tests/third_party
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Cria as subpastas necessárias
$(BUILD) $(BUILD)/src $(BUILD)/tests $(BUILD)/tests/third_party:
	mkdir -p $@

test: all
	./$(TARGET)

# Lint: exclui tests/third_party usando find
LINT_FILES := $(shell find include src tests -type f \( -name '*.cpp' -o -name '*.hpp' \) ! -path 'tests/third_party/*')
lint:
	$(CPPLINT) $(LINT_FILES)

static:
	cppcheck --enable=warning --std=c++17 --inline-suppr --suppress=missingIncludeSystem \
	 --exclude=$(BUILD) --exclude=tests/third_party .

valgrind: all
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

coverage: test
	gcov -b src/velha.cpp tests/testa_velha.cpp

clean:
	rm -rf $(BUILD) *.gcov *.gcda *.gcno
