# Compilador
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
COVFLAGS = -ftest-coverage -fprofile-arcs

# Diretórios
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin
REPORT_DIR = reports
DOC_DIR = docs

# Arquivos
SRC_FILES = $(SRC_DIR)/backup.cpp
TEST_FILE = $(TEST_DIR)/testa_backup.cpp
OBJ_FILES = $(BUILD_DIR)/backup.o

# Alvos
TARGET_TEST = $(BIN_DIR)/test_backup

# Alvo principal
all: $(TARGET_TEST)

# Compilar testes
$(TARGET_TEST): $(OBJ_FILES) $(TEST_FILE) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(COVFLAGS) -o $@ $(TEST_FILE) $(OBJ_FILES)

# Compilar objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criar diretórios necessários
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

# Executar testes
test: $(TARGET_TEST)
	./$(TARGET_TEST) --success

# Cobertura com relatórios em pasta separada
coverage: $(TARGET_TEST) | $(REPORT_DIR)
	./$(TARGET_TEST) --success
	gcov -r $(SRC_FILES)
	mv *.gcov $(REPORT_DIR)/

# Verificação de estilo
lint:
	cpplint --filter=-whitespace,-readability,-build/include_order,-build/include_subdir,-runtime/references $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h $(TEST_DIR)/*.cpp

# Verificação estática com relatório
check: | $(REPORT_DIR)
	cppcheck --enable=warning,performance --output-file=$(REPORT_DIR)/cppcheck_report.txt $(SRC_DIR)

# Documentação
doc:
	doxygen Doxyfile

# Abrir documentação
view-doc: doc
	xdg-open docs/html/index.html 2>/dev/null || \
	echo "Abra manualmente: docs/html/index.html"

# Limpeza TOTAL (exceto documentação)
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(REPORT_DIR) *.gcov *.gcda *.gcno

# Limpeza completa (incluindo documentação)
distclean: clean
	rm -rf $(DOC_DIR)/html $(DOC_DIR)/latex

# Mostrar estrutura de diretórios
tree:
	@echo "Estrutura do projeto:"
	@tree -I '.git|*.gcov|*.gcda|*.gcno' || find . -type d | head -20

.PHONY: all test coverage lint check clean distclean tree doc
