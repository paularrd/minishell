# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 11:57:23 by fle-tolg          #+#    #+#              #
#    Updated: 2023/01/23 14:50:06 by mrudloff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#PROJECT
NAME	=	libft.a
CC		=	@clang
AR		=	@ar rcs
CFLAGS	=	-Wall -Werror -Wextra -g
RM		=	@rm -f
CLEAR	=	@clear
FILE	=	$(shell ls -l ./* | grep -F .c | wc -l)
CMP		=	1

# COLOR #
GREEN	=	\033[38;5;76m
RED		=	\033[38;5;160m
YELLOW	=	\033[38;5;226m
ORANGE	=	\033[38;5;202m
PURPLE	=	\033[38;5;213m
LBLUE	=	\033[38;5;51m
BLUE	=	\033[38;5;117m
INDI	=	\033[38;5;99m
RESET	=	\033[00m

RNBW	= @printf "                                                 \r$(RED)Lib$(ORANGE)ft$(YELLOW) is$(GREEN) re$(LBLUE)ady $(INDI)to $(PURPLE)use$(RESET)\n"

#FILE
SRC_CHAR	:=	char/ft_isalnum.c char/ft_isalpha.c char/ft_isascii.c char/ft_isdigit.c char/ft_isprint.c char/ft_tolower.c char/ft_toupper.c char/ft_isspace.c
SRC_GNL		:=	gnl/get_next_line.c gnl/get_next_line_zero.c
SRC_LST		:=	lst/db_lstadd_back.c lst/db_lstdelone.c lst/db_lstnew.c lst/ft_lstadd_front.c lst/ft_lstiter.c lst/ft_lstnew.c lst/db_lstadd_front.c lst/db_lstfirst.c lst/db_lstsize.c lst/ft_lstclear.c lst/ft_lstlast.c lst/ft_lstsize.c lst/db_lstclear.c lst/db_lstlast.c lst/ft_lstadd_back.c lst/ft_lstdelone.c lst/ft_lstmap.c
SRC_MEM		:=	mem/ft_bzero.c mem/ft_calloc.c mem/ft_memchr.c mem/ft_memcmp.c mem/ft_memcpy.c mem/ft_memmove.c mem/ft_memset.c
SRC_PRINTF	:=	print/ft_fprintf.c print/ft_printf.c print/ft_putchar_fd.c print/ft_putnbr_base_fd.c print/ft_putstr_fd.c print/ft_fprintf_utils.c print/ft_printf_utils.c print/ft_putendl_fd.c print/ft_putnbr_fd.c
SRC_STR		:=	str/ft_atoi.c str/ft_split_utils.c str/ft_strcmp.c str/ft_strjoin.c str/ft_strlen.c str/ft_strnstr.c str/ft_substr.c str/ft_itoa.c str/ft_strchr.c str/ft_strdup.c str/ft_strlcat.c str/ft_strmapi.c str/ft_strrchr.c str/ft_split.c str/ft_strchr_char.c str/ft_striteri.c str/ft_strlcpy.c str/ft_strncmp.c str/ft_strtrim.c str/ft_strcat.c str/ft_strndup.c str/ft_atoll.c str/ft_strdup_split.c

SRC			=	$(SRC_CHAR) $(SRC_GNL) $(SRC_LST) $(SRC_MEM) $(SRC_PRINTF) $(SRC_STR)

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o: %.c
	@printf "\r$(LBLUE)[$(RESET)+$(LBLUE)] $(RESET)Compiling $(GREEN)$<$(BLUE)[$(RESET)$(CMP)$(BLUE)/$(RESET)$(FILE)$(BLUE)]$(RESET)                     \r"
	$(CC) $(CFLAGS) -c $< -o $@
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)
	$(RNBW)

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.SILENT:
	all
.PHONY :
	all clean fclean re
