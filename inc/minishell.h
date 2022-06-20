/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:45:14 by nspeedy           #+#    #+#             */
/*   Updated: 2022/06/20 12:13:02 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "smsh.h"
#include "minishell.h"

typedef struct	s_data
{
	char	*cmdline;
	char	**arglist;
	char	**command_args;
	char	**redirect;
	char	*command;
	char	*prompt;
	
	int		cmd_amt;
	int		pid;
}	t_data;


extern char **environ;

char	*find_path(char *cmd[]);
char	*check_access(char **paths, char *cmd[]);
int		strarrlen(char **arr);
char	*newstr(char *s, int l);
void	*emalloc(size_t n);
void	*erealloc(void *p, size_t n);
void	fatal(char *s1, char *s2, int n);
void	free_strarray(char **arr);
void	freelist(char **list);
void	handle_redirect(char *cmd);
void	exsit(char *cmdline, char **arglist);
void	init_struct(t_data *data);
void	redir_pipe(t_data *d, int i);
void	op_cl(t_data *d, int old_p[], int new_p[], int i);

#endif