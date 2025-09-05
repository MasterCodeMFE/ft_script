# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manufern <manufern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 20:45:56 by manufern          #+#    #+#              #
#    Updated: 2025/09/02 12:51:00 by manufern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
SRCS                    = ft_atoi.c \
                      ft_bzero.c \
                      ft_calloc.c \
                      ft_isalnum.c \
                      ft_itoa.c \
                      ft_isalpha.c \
                      ft_isascii.c \
                      ft_isdigit.c \
                      ft_isprint.c \
                      ft_memchr.c \
                      ft_memcmp.c \
                      ft_memcpy.c \
                      ft_memmove.c \
                      ft_memset.c \
                      ft_split.c \
                      ft_strchr.c \
                      ft_strdup.c \
                      ft_striteri.c \
                      ft_strlcat.c \
                      ft_strlcpy.c \
                      ft_strlen.c \
                      ft_strncmp.c \
                      ft_strnstr.c \
                      ft_strrchr.c \
                      ft_strjoin.c \
                      ft_strtrim.c \
                      ft_strmapi.c \
                      ft_substr.c \
                      ft_tolower.c \
                      ft_toupper.c \
                      ft_putchar_fd.c \
                      ft_putstr_fd.c \
                      ft_putendl_fd.c \
                      ft_putnbr_fd.c \
                      ft_strcmp.c
BNS_SRCS                = ft_lstnew_bonus.c \
						  ft_lstadd_front_bonus.c \
						  ft_lstsize_bonus.c \
						  ft_lstlast_bonus.c \
						  ft_lstadd_back_bonus.c \
						  ft_lstdelone_bonus.c \
						  ft_lstclear_bonus.c \
						  ft_lstmap_bonus.c \
						  ft_lstiter_bonus.c
                          

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJS_DIR), $(BNS_SRCS:.c=.o))
RM = rm -f

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus