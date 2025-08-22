SRC_DIR = ./src
INC_DIR = ./inc
OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(pathsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

-include $(pathsubst %.o,%.d,$(OBJ_FILES))

all: $(OBJ_FILES)
	@echo Enlazado $@
	@gcc $(OBJ_FILES) -o $(OUT_DIR)/app.elf

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compilando $@
	@mkdir -p $(OBJ_DIR)
	@gcc -o $@ -c $< -I $(INC_DIR) -MMD -Wall -Wextra -Werror -pedantic

clean:
	@rm -r $(OUT_DIR)
