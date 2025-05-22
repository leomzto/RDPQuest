# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -Iheaders

# Nome do executável
TARGET = game/rpg.exe

# Diretórios
SRC_DIR = source
OBJ_DIR = obj
HEADERS_DIR = headers

# Arquivos fonte
SRC = $(wildcard $(SRC_DIR)/*.c)

# Arquivos objeto
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Dependências de cabeçalhos
DEPS = $(wildcard $(HEADERS_DIR)/*.h)

# Regra padrão
all: $(TARGET)

# Linkagem do executável
$(TARGET): $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@

# Compilação dos objetos com dependências de cabeçalhos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Inclui as dependências geradas automaticamente
-include $(OBJ:.o=.d)

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean