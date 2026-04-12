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

# ⚙️ Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -I$(INC_DIR)
DEBUG_FLAGS = -g

# 📦 Arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.c)

# 🎯 Nomes dos executáveis (sem caminho)
TARGETS = $(notdir $(SRCS:.c=))

# 📦 Executáveis dentro de build/
TARGET_PATHS = $(addprefix $(BUILD_DIR)/, $(TARGETS))

# 🔄 Regra padrão
all: $(TARGET_PATHS)

# 🔨 Compilar cada .c em um executável dentro de build/
$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

# ▶️ Rodar (ex: make run-ex4)
run-%: $(BUILD_DIR)/%
	./$<

# 🐞 Debug
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

# 🧹 Limpeza
clean:
	rm -rf $(BUILD_DIR)

# 🔁 Rebuild
re: clean all