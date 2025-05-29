# Configurações para WSL/Linux
CC := gcc
CFLAGS := -Iheaders -Wall -Wextra -g -D_LINUX -fno-stack-protector
LDFLAGS := -no-pie
TARGET := ./prompt_rogue

# Configurações para Windows (cross compile)
WIN_CC := x86_64-w64-mingw32-gcc
WIN_CFLAGS := -Iheaders -Wall -Wextra -g -D_WINDOWS
WIN_TARGET := ./prompt_rogue.exe

# Diretórios
SRC_DIR := source
BUILD_DIR := build
HEADER_DIR := headers

# Lista de fontes
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Regra principal Linux
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p saves

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

# Regra para Windows
windows: $(BUILD_DIR) $(WIN_TARGET)

$(WIN_TARGET):
	$(WIN_CC) $(WIN_CFLAGS) $(SRCS) -o $@

clean:
	rm -rf $(BUILD_DIR) saves $(WIN_TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run windows
