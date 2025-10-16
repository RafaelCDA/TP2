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
GDB_DIR = gdb_scripts

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

$(GDB_DIR):
	mkdir -p $(GDB_DIR)

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

# ========== GDB COMMANDS ==========

# Debug interativo simples
gdb: $(TARGET_TEST)
	gdb ./$(TARGET_TEST)

# Debug de um teste específico
gdb-test: $(TARGET_TEST)
	gdb -ex "run --success" ./$(TARGET_TEST)

# Debug da coluna específica que criamos
gdb-coluna-hd-inexistente: $(TARGET_TEST)
	gdb -ex "break 'Coluna: Erro quando arquivo não existe no HD'" \
	    -ex "run" \
	    ./$(TARGET_TEST)

# Debug com breakpoints nas funções principais
gdb-backup-functions: $(TARGET_TEST)
	gdb -ex "break SistemaBackup::executarBackup" \
	    -ex "break SistemaBackup::arquivoExisteHD" \
	    -ex "break SistemaBackup::compararDatas" \
	    -ex "run --success" \
	    ./$(TARGET_TEST)

# Debug passo a passo de um teste específico
gdb-step: $(TARGET_TEST)
	gdb -ex "break main" \
	    -ex "run" \
	    -ex "step" \
	    ./$(TARGET_TEST)

# Criar script de debug automático
gdb-script: | $(GDB_DIR)
	@echo "Criando script de debug automático..."
	@echo "# Script de debug automático para sistema de backup" > $(GDB_DIR)/auto_debug.gdb
	@echo "break SistemaBackup::executarBackup" >> $(GDB_DIR)/auto_debug.gdb
	@echo "commands" >> $(GDB_DIR)/auto_debug.gdb
	@echo "  print dispositivo" >> $(GDB_DIR)/auto_debug.gdb
	@echo "  print arquivos" >> $(GDB_DIR)/auto_debug.gdb
	@echo "  continue" >> $(GDB_DIR)/auto_debug.gdb
	@echo "end" >> $(GDB_DIR)/auto_debug.gdb
	@echo "" >> $(GDB_DIR)/auto_debug.gdb
	@echo "break SistemaBackup::arquivoExisteHD" >> $(GDB_DIR)/auto_debug.gdb
	@echo "commands" >> $(GDB_DIR)/auto_debug.gdb
	@echo "  print nomeArquivo" >> $(GDB_DIR)/auto_debug.gdb
	@echo "  continue" >> $(GDB_DIR)/auto_debug.gdb
	@echo "end" >> $(GDB_DIR)/auto_debug.gdb
	@echo "" >> $(GDB_DIR)/auto_debug.gdb
	@echo "run --success" >> $(GDB_DIR)/auto_debug.gdb
	@echo "Script criado em $(GDB_DIR)/auto_debug.gdb"

# Executar com script automático
gdb-auto: gdb-script $(TARGET_TEST)
	gdb -x $(GDB_DIR)/auto_debug.gdb ./$(TARGET_TEST)

# Analisar core dump (se ocorrer)
gdb-core: $(TARGET_TEST)
	@if [ -f core ]; then \
	    gdb ./$(TARGET_TEST) core; \
	else \
	    echo "Nenhum core dump encontrado. Execute 'make test' primeiro."; \
	fi

# Debug com valgrind (combina duas ferramentas)
gdb-valgrind: $(TARGET_TEST)
	valgrind --vgdb=yes --vgdb-error=0 ./$(TARGET_TEST) --success

# ========== FIM GDB COMMANDS ==========

# Limpeza TOTAL (exceto documentação)
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(REPORT_DIR) $(GDB_DIR) *.gcov *.gcda *.gcno core

# Limpeza completa (incluindo documentação)
distclean: clean
	rm -rf $(DOC_DIR)/html $(DOC_DIR)/latex

# Mostrar estrutura de diretórios
tree:
	@echo "Estrutura do projeto:"
	@tree -I '.git|*.gcov|*.gcda|*.gcno' || find . -type d | head -20

# Ajuda do GDB
help-gdb:
	@echo "=== COMANDOS GDB DISPONÍVEIS ==="
	@echo "make gdb                    - Debug interativo simples"
	@echo "make gdb-test               - Debug executando todos os testes"
	@echo "make gdb-coluna-hd-inexistente - Debug do teste específico da coluna"
	@echo "make gdb-backup-functions   - Debug com breakpoints nas funções principais"
	@echo "make gdb-auto               - Debug com script automático"
	@echo "make gdb-script             - Apenas criar o script de debug"
	@echo "make gdb-core               - Analisar core dump (se existir)"

.PHONY: all test coverage lint check clean distclean tree doc \
        gdb gdb-test gdb-coluna-hd-inexistente gdb-backup-functions \
        gdb-step gdb-script gdb-auto gdb-core gdb-valgrind help-gdb

# Verificar se todas as ferramentas estão instaladas
check-tools:
	@echo "=== VERIFICANDO FERRAMENTAS ==="
	@which g++ || echo "❌ g++ não instalado"
	@which gdb || echo "❌ gdb não instalado"
	@which cpplint || echo "⚠️  cpplint não instalado"
	@which cppcheck || echo "⚠️  cppcheck não instalado"
	@which doxygen || echo "⚠️  doxygen não instalado"
	@which valgrind || echo "⚠️  valgrind não instalado"
	@which gcov || echo "⚠️  gcov não instalado"
	@echo "=== VERIFICAÇÃO CONCLUÍDA ==="