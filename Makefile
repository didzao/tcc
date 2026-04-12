# Makefile simples
# all:
# 	gcc *.c -o main

# run:
# 	./main

# ----------

# 📁 Diretórios
SRC_DIR = src
BUILD_DIR = build
INC_DIR = include
TEST_DIR = tests
UNITY_DIR = $(TEST_DIR)/unity

# ⚙️ Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -I$(INC_DIR)
LDFLAGS = -lm
DEBUG_FLAGS = -g

# 📦 Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# 🎯 Nomes dos executáveis (sem caminho)
TARGETS = $(notdir $(SRCS:.c=))

# 📦 Executáveis dentro de build/
TARGET_PATHS = $(addprefix $(BUILD_DIR)/, $(TARGETS))

# 🔄 Regra padrão
all: $(TARGET_PATHS)

# 🧪 Testes
test:
	$(CC) $(CFLAGS) -DTEST \
	$(filter-out $(SRC_DIR)/main.c, $(SRC_DIR)/*.c) \
	$(TEST_DIR)/test_*.c \
	$(UNITY_DIR)/unity.c \
	-o test_runner $(LDFLAGS)
	./test_runner

# 🔨 Compilar cada .c em um executável (básico/individual)
$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# ▶️ Rodar Dinamicamente (ex: make run-main ARGS="ieee_utils.c")
# Esta regra recompila o alvo incluindo as dependências passadas em ARGS
run-%:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/$*.c $(addprefix $(SRC_DIR)/, $(ARGS)) -o $(BUILD_DIR)/$* $(LDFLAGS)
	@echo "--- Executando $(BUILD_DIR)/$* ---"
	./$(BUILD_DIR)/$*

# 🐞 Debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

# 🧹 Limpeza
clean:
	rm -rf $(BUILD_DIR)
	rm -f test_runner

# 🔁 Rebuild
re: clean all