/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_var.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudloff <mrudloff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:51:10 by mrudloff          #+#    #+#             */
/*   Updated: 2023/01/28 15:56:50 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_VAR_H
# define MINISHELL_VAR_H

# include <sys/types.h>

typedef struct s_global
{
	struct s_parsing	*parse;
	struct s_function	*func;
	char				**split;
	char				*file;
	char				*line;
	int					fd1;
	int					fd2;
	int					check_execution_here;
	pid_t				pid;
}				t_global;

extern struct s_global	g_global;

typedef struct s_env
{
	char	*name;
	char	*value;
}				t_env;

typedef struct s_minishell
{
	pid_t				*pid;
	int					fd[2];
	int					fd_pipe;
	int					fd_input;
	int					fd_output;
	int					check_export;
	char				*prompt;
	struct s_list		*lst_env;
	struct s_function	*func;
	struct s_function	*start_func;

}				t_minishell;

typedef struct s_parsing
{
	int					*i;
	int					*x;
	char				*line;
	struct s_list		*lst_env;
	struct s_minishell	*mini;
}				t_parsing;

typedef struct s_function
{
	char				**cmd;
	int					check_input;
	int					check_export;
	int					fd_input;
	int					fd_output;
	int					check_execution;
	struct s_function	*next;
}				t_function;

#endif
