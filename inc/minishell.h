/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:49:46 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/29 10:29:03 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_var.h"
# include  "../libft/includes/libft.h"
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>

/* ========================================================================== */
/* ================================BUILTINS================================== */
/* ========================================================================== */

/* **********************************CD************************************** */
void		cmd_cd(char **args, t_list **env);

/* **********************************ECHO************************************ */
void		cmd_echo(char **args);

/* **********************************ENV************************************* */
void		dup_env(char **env, t_list **lst_env);
void		cmd_env(t_list **env);
void		modify_env(t_env *new, t_list **env);
void		*get_env(char *str, t_list **env);
t_env		*create_new_env(char *str);
char		**ft_lsttotab_str(t_list *lst);
int			is_valid_name(char *str);

/* **********************************EXIT************************************ */
void		run_exit(char **args, t_minishell **minishell);

/* **********************************EXPORT********************************** */
void		cmd_export(char **args, t_list **lst_env, int fd);
void		add_export(t_list **env, char *var);

/* **********************************PWD************************************* */
void		cmd_pwd(void);

/* **********************************UNSET*********************************** */
void		cmd_unset(char **args, t_list **env);
void		check_unset_arg(char **args);

/* ========================================================================== */
/* ================================EXECUTION================================= */
/* ========================================================================== */

/* ********************************EXECUTION********************************* */
void		loop_function(t_minishell **minishell, char **env, int i);
void		execution(t_minishell **minishell, char **env);
int			check_export(t_minishell **minishell);
void		execution_2(t_minishell **minishell, char **env, int i);

/* ***************************EXECUTION - BUILTINS*************************** */
void		execve_builtins_no_fork(t_minishell **minishell, char **cmd);
void		execve_builtins(t_minishell **minishell, char **cmd);
void		do_builtins(t_minishell **minishell);
void		do_builtins_pipe(t_minishell **minishell);

/* ****************************EXECUTION - UTILS***************************** */
pid_t		*get_tab_pid(t_function *func);
void		wait_fork_2(t_minishell **minishell, int i);
int			is_builtins(char *cmd);
int			is_builtins_no_fork(char *cmd);
int			print_error_code(char *cmd);

/* ========================================================================== */
/* ================================PARSING=================================== */
/* ========================================================================== */

/* ********************************DEL_CMD*********************************** */
void		get_n_char_3(char *line, int *i, int *y);
char		*del_cmd(char *line);

/* ******************************SPLIT-PIPE********************************** */
char		**ft_split_pipe(char *str);
void		init_int(int *i, int *z, int *y);
int			next_char(char *line, char c, int *x);
int			next_char_no_x(char *line, char c);
int			ft_is_in_quote(int y, char *s);

/* *****************************GET_NEXT_ARG********************************* */
void		get_size_next_arg_env(int *i, int *y,
				char *line, t_parsing **parse);
void		simple_add_get_next_arg(int *i, int *x, char *line, char *cmd);
void		initialize_integer_get_next_arg(int *i, int *x, t_parsing **parse);
char		*get_next_arg(char *line, t_parsing **parse);

/* *******************************PARSING************************************ */
t_function	*parsing(char *line, t_minishell **minishell);
int			ft_is_char_env(char c);
int			test_arg(char *line);
int			test_redirect(char *line);
int			next_quote(char *line, int i);
int			test_simple_quote(char *line);
int			test_double_quote(char *line);
int			ft_is_in_quote(int y, char *s);
int			next_char_no_x(char *line, char c);
int			get_size_next_arg_no_env(char *line);
int			next_char(char *line, char c, int *x);
int			test_prev(char *line, int i, int size);
int			get_n_char(char *line, t_parsing **parse);
void		get_n_char_2(char *line, int *i, int *y, t_parsing **parse);
t_parsing	*initialise_parse_struct(t_minishell **minishell);
char		**parse_cmd(char *line, t_minishell **minishell, t_function *func);
void		reduce_test_quote(int *i, int *counter, char *line, char c);
int			test_double_quote(char *line);
int			test_simple_quote(char *line);
int			ft_test_arg(char *line);
char		**create_blank_tab(void);

/* *******************************REDIRECT*********************************** */
char		*get_redir_heredoc(char *line, t_parsing **parse, char **split);
char		*del_redirection(int size, int s, char *line, t_parsing **parse);
char		*get_redirection(char *line, t_parsing **parse, t_function **func);

/* *******************************UTILS_ARG********************************** */
int			ft_is_char_env(char c);
void		get_next_arg_simple_env(char *line, char *cmd, t_parsing **parse);
void		get_next_arg_3(char *line, int *i, int *x, char *cmd);
void		get_next_arg_2(char *line, char *cmd, t_parsing **parse);

/* *****************************UTILS_PARSING******************************** */
char		*get_name_env(char *line_env);
char		*get_value_env(char *str, t_parsing **parse);
char		*trim_and_free(char *line, char *delim);

/* *******************************UTILS_PIPE********************************* */
int			test_pipe(char *line);
int			next_char_fill(char *line, char c, int *x, char *s);

/* ***************************UTILS_REDIRECTION****************************** */
int			ft_test_next(char *line, int i, int *test);
void		get_n_char_2_no_env(char *line, int *i, int *y);
void		get_next_arg_2_no_env(char *line, int *i, int *x, char *cmd);
int			get_size_next_arg_no_env(char *line);
char		*get_next_arg_no_env(char *line);
char		*redirect_two(char *line, t_parsing **parse,
				int *i, t_function **func);
int			size_new_line(int i, int start, char *line, t_parsing **parse);
int			test_prev(char *line, int i, int size);
int			next_quote(char *line, int i);
int			redir(char c);
void		get_global(t_parsing **parse, char *delim, char **split, int fd[2]);
char		*del_redirection_heredoc(int size, int x, char *line,
				t_parsing **parse);

/* ========================================================================== */
/* ================================SIGNAL==================================== */
/* ========================================================================== */
void		handle_child(int signum);
void		handle_signal(int signum);

/* ========================================================================== */
/* ================================UTILS===================================== */
/* ========================================================================== */
/* ******************************UTILS_CMD*********************************** */
int			get_code_error(int info, int new_error_code);
char		*get_cmd_lst_env(t_minishell **minishell, char *cmd, t_list *lst);
char		*get_cmd(char *cmd, char **path);
void		initialize_minishell(char **env, t_minishell **pipex);

/* ******************************UTILS_FREE********************************** */
void		close_all_fd(t_function *func);
void		free_lst_env(t_list *lst_env);
void		free_func(t_function *func);
void		free_all(t_minishell **minishell);

/* *****************************UTILS_PROMPT********************************* */
char		*get_prompt(void);
int			get_size(char *pwd);
void		check_dir(t_minishell **minishell, char *cmd);
char		*get_pwd(void);

#endif
