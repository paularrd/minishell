# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 10:47:02 by fle-tolg          #+#    #+#              #
#    Updated: 2023/01/29 13:56:56 by mrudloff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#PROJECT
NAME	=	minishell

#COMMAND
CC		=	@clang
CFLAGS	=	-g -Wall -Wextra -Werror
IFLAGS	=	-Iinc
MK		=	@mkdir -p
RM		=	@rm -f
HARDRM	=	@rm -rf
CLEAR	=	@clear
FILE	=	$(shell ls -l src/**/* | grep -F .c | wc -l)
CMP		=	1

# COLOR #
GREEN	=	\033[38;5;76m
RED		=	\033[38;5;124m
YELLOW	=	\033[38;5;226m
ORANGE	=	\033[38;5;202m
PURPLE	=	\033[38;5;213m
LBLUE	=	\033[38;5;51m
BLUE	=	\033[38;5;117m
INDI	=	\033[38;5;99m
RESET	=	\033[00m

SKULL0	=	@printf "\n$(RED)██████████████████████████"
SKULL1	=	printf "██████▀▀▀░░░░░░░▀▀▀███████"
SKULL2	=	printf "███▀░░░░░░░░░░░░░░░░░▀████"
SKULL3	=	printf "██│░░░░░░░░░░░░░░░░░░░│███"
SKULL4	=	printf "█▌│░░░░░░░░░░░░░░░░░░░│▐██"
SKULL5	=	printf "█░└┐░░░░░░░░░░░░░░░░░┌┘░██"
SKULL6	=	printf "█░░└┐░░░░░░░░░░░░░░░┌┘░░██"
SKULL7	=	printf "█░░┌┘▄▄▄▄▄░░░░░▄▄▄▄▄└┐░░██"
SKULL8	=	printf "█▌░│██████▌░░░▐██████│░▐██"
SKULL9	=	printf "██░│▐███▀▀░░▄░░▀▀███▌│░███"
SKULL10	=	printf "█▀─┘░░░░░░░▐█▌░░░░░░░└─▀██"
SKULL11	=	printf "█▄░░░▄▄▄▓░░▀█▀░░▓▄▄▄░░░▄██"
SKULL12	=	printf "███▄─┘██▌░░░░░░░▐██└─▄████"
SKULL13	=	printf "████░░▐█─┬┬┬┬┬┬┬─█▌░░█████"
SKULL14	=	printf "███▌░░░▀┬┼┼┼┼┼┼┼┬▀░░░▐████"
SKULL15	=	printf "████▄░░░└┴┴┴┴┴┴┴┘░░░▄█████"
SKULL16	=	printf "██████▄░░░░░░░░░░░▄███████"
SKULL17	=	printf "█████████▄▄▄▄▄▄▄██████████"
P1	=	printf "───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n"
P2	=	printf "─██████████████─██████████████─██████──██████─██████████████─██████████─██████████████─██████──██████─██████████████─██████─────────██████─────────\n"
P3	=	printf "─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░██──██░░██─██░░░░░░░░░░██─██░░░░░░██─██░░░░░░░░░░██─██░░██──██░░██─██░░░░░░░░░░██─██░░██─────────██░░██─────────\n"
P4	=	printf "─██░░██████████─██░░██████░░██─██░░██──██░░██─██░░██████████─████░░████─██░░██████████─██░░██──██░░██─██░░██████████─██░░██─────────██░░██─────────\n"
P5	=	printf "─██░░██─────────██░░██──██░░██─██░░██──██░░██─██░░██───────────██░░██───██░░██─────────██░░██──██░░██─██░░██─────────██░░██─────────██░░██─────────\n"
P6	=	printf "─██░░██████████─██░░██████░░██─██░░██──██░░██─██░░██───────────██░░██───██░░██████████─██░░██████░░██─██░░██████████─██░░██─────────██░░██─────────\n"
P7	=	printf "─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░██──██░░██─██░░██───────────██░░██───██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░██─────────██░░██─────────\n"
P8	=	printf "─██████████░░██─██░░██████░░██─██░░██──██░░██─██░░██───────────██░░██───██████████░░██─██░░██████░░██─██░░██████████─██░░██─────────██░░██─────────\n"
P9	=	printf "─────────██░░██─██░░██──██░░██─██░░██──██░░██─██░░██───────────██░░██───────────██░░██─██░░██──██░░██─██░░██─────────██░░██─────────██░░██─────────\n"
Q1	=	printf "─██████████░░██─██░░██──██░░██─██░░██████░░██─██░░██████████─████░░████─██████████░░██─██░░██──██░░██─██░░██████████─██░░██████████─██░░██████████─\n"
Q2	=	printf "─██░░░░░░░░░░██─██░░██──██░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░██─██░░░░░░░░░░██─██░░██──██░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░██─\n"
Q3	=	printf "─██████████████─██████──██████─██████████████─██████████████─██████████─██████████████─██████──██████─██████████████─██████████████─██████████████─\n"
Q4	=	printf "───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n"
Q5	=	printf "███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████\n"
Q6	=	printf "██ ▄▄▀█ ██ ████ ▄▄▄█ ▄▄█ ███▄██ █ ███ ▄▄▀█ ▄▄▀█ ▄▀████ ▄▀▄ █ ▄▄▀█▄ ▄█ █████▄██ ▄▄██████████████████████████████████████████████████████████████████\n"
Q7	=	printf "██ ▄▄▀█ ▀▀ ████ ▄▄██ ▄▄█ ███ ▄█▀▄▀███ ▀▀ █ ██ █ █ ████ █ █ █ ▀▀ ██ ██ ▄▄ ██ ▄█▄▄▀██████████████████████████████████████████████████████████████████\n"
Q8	=	printf "██ ▀▀ █▀▀▀▄████ ████▄▄▄█▄▄█▄▄▄█▄█▄███▄██▄█▄██▄█▄▄█████ ███ █▄██▄██▄██▄██▄█▄▄▄█▄▄▄██████████████████████████████████████████████████████████████████\n"
Q9	=	printf "███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████$(RESET)\n"

HELL	=	$(SKULL0);$(P1);$(SKULL1);$(P2);$(SKULL2);$(P3);$(SKULL3);$(P4);$(SKULL4);$(P5);$(SKULL5);$(P6);$(SKULL6);$(P7);$(SKULL7);$(P8);$(SKULL8);$(P9);$(SKULL9);$(Q1);$(SKULL10);$(Q2);$(SKULL11);$(Q3);$(SKULL12);$(Q4);$(SKULL13);$(Q5);$(SKULL14);$(Q6);$(SKULL15);$(Q7);$(SKULL16);$(Q8);$(SKULL17);$(Q9);

#LIBFT
LIBFT_NAME	=	./libft/libft.a
LIBFT_DIR	=	./libft/ --no-print-directory

#SOURCES
SRC_BUILTINS	:=	builtins/cd/cd.c\
					builtins/echo/echo.c\
					builtins/env/env.c\
					builtins/env/env_utils.c\
					builtins/env/env_create.c\
					builtins/exit/exit.c\
					builtins/export/export.c\
					builtins/pwd/pwd.c\
					builtins/unset/unset.c\
					builtins/unset/unset_utils.c\

SRC_PARSING		:=	parsing/del_cmd.c\
					parsing/ft_split_pipe.c\
					parsing/ft_split_pipe_utils.c\
					parsing/get_next_arg.c\
					parsing/parsing.c\
					parsing/parsing_cmd.c\
					parsing/parsing_error.c\
					parsing/test_redirect.c\
					parsing/redirect_heredoc.c\
					parsing/redirection.c\
					parsing/utils_get_next_arg.c\
					parsing/utils_parsing.c\
					parsing/utils_pipe.c\
					parsing/utils_redirection_2.c\
					parsing/utils_redirection.c\
					parsing/utils_heredoc.c

SRC_UTILS		:=	main.c\
					utils/utils_cmd.c\
					utils/utils_free.c\
					utils/utils_prompt.c

SRC_SIGNAL		:=	signal/signal.c

SRC_EXECUTION	:= 	execution/execution.c\
					execution/execution_2.c\
					execution/execution_utils.c\
					execution/execution_builtins.c

SRCS			=	$(SRC_BUILTINS) $(SRC_PARSING) $(SRC_UTILS) $(SRC_SIGNAL) $(SRC_EXECUTION)

#OBJECTS
OBJS		=	$(addprefix objs/, $(SRCS:%.c=%.o))
OBJS_DIR	=	objs

all : $(LIBFT_NAME) $(NAME)

$(OBJS_DIR)/%.o: src/%.c
	$(MK) $(@D)
	@printf "\r$(LBLUE)[$(RESET)+$(LBLUE)] $(RESET)Compiling $(GREEN)$<$(BLUE) [$(RESET)$(CMP)$(BLUE)/$(RESET)$(FILE)$(BLUE)]$(RESET)         \r"
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LIBFT_NAME) -o $(NAME) -lreadline
	$(CLEAR)
	$(HELL)

clean :
	@make clean -C $(LIBFT_DIR)
	$(HARDRM) $(OBJS_DIR)

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re : fclean all

.PHONY :
	all clean fclean re
