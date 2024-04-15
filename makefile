# Directorios de trabajo
SRC_DIR := ./src
OUT_DIR := ./build
OBJ_DIR := $(OUT_DIR)/obj

# Archivos de fuente y objeto
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# La meta por defecto que se ejecuta cuando se llama a make sin argumentos
.DEFAULT_GOAL := all

# Incluye archivos de dependencia
-include $(patsubst %.o,%.d,$(OBJ_FILES))

# Regla principal para construir el proyecto
all: $(OBJ_FILES)
	@echo Enlazando $@
	@gcc $(OBJ_FILES) -o  $(OUT_DIR)/app.elf

# Regla para compilar archivos fuente a objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compilando $<
	@mkdir -p $(OBJ_DIR)
	@gcc -o $@ -c $< -I$(SRC_DIR) -MMD -DUSE_STATIC_MEM -DMAX_GPIO_INSTANCES=7

# Regla para limpiar el proyecto (eliminar archivos generados)
clean:
	@rm -r $(OUT_DIR)

# Regla para generar la documentación con Doxygen
doc:
	@mkdir -p $(OUT_DIR)
	@doxygen doxyfile
