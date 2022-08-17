/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:45:14 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/28 22:28:17 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef struct s_data
{
	char	*cmdline;
	char	**arglist;
	char	**command_args;
	char	**redirect;
	char	**quotes;
	char	*prompt;
	int		cmd_amt;
	int		pid;
	int		statval;
	char	**env;
}	t_data;

typedef struct s_split
{
	int		i;
	int		j;
	int		k;
	bool	inquote;
	char	c;
}	t_split;

typedef struct s_dollar
{
	int		find;
	int		found;
	int		i;
	int		n;
	char	*env_arg;
	char	*str;
	char	*tmp;
	char	*prev;
	int		envi;
}	t_dollar;

typedef struct s_env
{
	char			**n_env;
}	t_env;

typedef struct s_qbool
{
	bool	inq;
	bool	indq;
}	t_qbool;

extern char	**environ;
char		*find_path(char *cmd[]);
char		*check_access(char **paths, char *cmd[]);
int			strarrlen(char **arr);
void		free_strarray(char **arr);
void		exsit(char *cmdline, char **arglist);
void		redir_pipe(int i);
void		op_cl(int old_p[], int new_p[], int i);
int			bad_pipe(int new_p[], int i);
int			child_process(int old_p[], int new_p[], int i, int j);
void		parent_process(int old_p[], int new_p[], int i);
int			manage(int old_p[], int new_p[]);
int			redirect(int i);
void		siggles(void);
char		*dollar_bils(char *n_args);
char		*inside(char *n_args, t_dollar *d);
void		check_quotes(t_split *sp, const char *s, int i);
char		**space_split(const char *s, char delim);
char		*replace(char *n_args, t_dollar *d);
t_dollar	*find(char *n_args, t_dollar *d);
void		rm_quote(char *str);
void		exportal(char **cmargs);
char		**env_keys(void);
bool		check_key(char *cmargs);
int			env_size(char **environ);
char		**ft_fill_envs(void);
void		print_envs(void);
void		add_var(char **cmargs);
void		ch_var(char **cmargs);
void		rm_var(char **cmargs);
void		run_ex_un_env(char **cmargs);
bool		check_key_un(char *cmargs);
int			cd(void);
bool		is_builtin(void);
void		q_check(t_split *s, const char *src, int track);

#endif