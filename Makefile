# Compilador
CC = cc

# Flags de compilación
CFLAGS = -Wall -Wextra -Werror

# Nombre del ejecutable
NAME = ft_script

# Directorio libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Directorios fuentes y objetos
SRCS_DIR = src
OBJS_DIR = objs

# Fuentes listadas uno a uno con ruta
SRCS = src/main.c \
       src/ft_script.c \
       src/parse_argument.c \
	   src/print_info.c \
	   src/create_process.c \
	   src/process_inout_output.c \
	   src/print_version_help.c \
	   src/signals.c

# Objetos (se guardan en objs/, sin subdirectorios)
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# ------------------------------------------------------
# Reglas
# ------------------------------------------------------

all: $(LIBFT) $(NAME)

# Crear carpeta de objetos si no existe
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

# Regla para compilar .c en objs/*.o
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar ejecutable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Compilar libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Limpiar objetos y libft
clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

# Limpiar todo (objetos, ejecutable y libft)
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Reconstruir todo desde cero
re: fclean all

.PHONY: all clean fclean re
