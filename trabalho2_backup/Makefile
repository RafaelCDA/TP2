# Compilador
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
COVFLAGS = -ftest-coverage -fprofile-arcs

# Diretórios
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Arquivos
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Alvos
TARGET_TEST = test_backup

# Alvo principal
all: $(TARGET_TEST)

# Compilar testes
$(TARGET_TEST): $(OBJ_FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(COVFLAGS) -o $@ $(TEST_FILES) $(OBJ_FILES)

# Compilar objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criar diretório build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Executar testes
test: $(TARGET_TEST)
	./$(TARGET_TEST) --success

# Cobertura
coverage: test
	gcov -r $(SRC_FILES)

# Verificação de estilo Google (AGORA FUNCIONA!)
lint:
	cpplint --filter=-whitespace,-readability,-build/include_order,-build/include_subdir,-runtime/references $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h $(TEST_DIR)/*.cpp

# Verificação estática
check:
	cppcheck --enable=warning,performance $(SRC_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET_TEST) *.gcov *.gcda *.gcno

.PHONY: all test coverage lint check clean