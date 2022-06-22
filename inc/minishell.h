/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:45:14 by nspeedy           #+#    #+#             */
/*   Updated: 2022/06/20 15:02:42 by nspeedy          ###   ########.fr       */
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

typedef struct s_data
{
	char	*cmdline;
	char	**arglist;
	char	**command_args;
	char	**redirect;
	char	**quotes;
	char	*command;
	char	*prompt;
	int		cmd_amt;
	int		pid;
}	t_data;

extern char	**environ;
char	*find_path(char *cmd[]);
char	*check_access(char **paths, char *cmd[]);
int		strarrlen(char **arr);
void	free_strarray(char **arr);
void	exsit(char *cmdline, char **arglist);
void	redir_pipe(int i);
void	op_cl(int old_p[], int new_p[], int i);
int		bad_pipe(int new_p[], int i);
void	child_process(int old_p[], int new_p[], int i);
void	parent_process(int old_p[], int new_p[], int i);
int		manage(int old_p[], int new_p[]);
void    redirect(void);
void	siggles(void);
void    singles(void);
void    first_wrdq(void);
#endif