/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:56:33 by nspeedy           #+#    #+#             */
/*   Updated: 2022/07/08 14:33:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_d;

int	bad_pipe(int new_p[], int i)
{
	if (i != g_d.cmd_amt - 1)
	{
		if (pipe(new_p) == -1)
		{
			printf("bad pipe\n");
			return (1);
		}
	}
	g_d.pid = fork();
	if (g_d.pid < 0)
	{
		printf("bad fork\n");
		return (1);
	}
	return (0);
}

void	child_process(int old_p[], int new_p[], int i)
{
	if (g_d.pid == 0)
	{
		op_cl(old_p, new_p, i);
		g_d.command_args = space_split(dollar_bils(g_d.arglist[i]));
		redirect();
		if (access(g_d.command_args[0], X_OK) != 0)
			g_d.command = find_path(g_d.command_args);
		else
			g_d.command = g_d.command_args[0];
		execve(g_d.command, g_d.command_args, environ);
		perror("execve");
	}
}

void	parent_process(int old_p[], int new_p[], int i)
{
	if (g_d.pid > 0)
	{	
		if (i != 0)
		{
			close(old_p[0]);
			close(old_p[1]);
		}
		if (i != g_d.cmd_amt - 1)
		{
			old_p[0] = new_p[0];
			old_p[1] = new_p[1];
		}
		waitpid(g_d.pid, &g_d.statval, 0);
	}
}

void	op_cl(int old_p[], int new_p[], int i)
{
	if (i != 0)
	{
		close(old_p[1]);
		dup2(old_p[0], 0);
		close(old_p[0]);
	}
	if (i != g_d.cmd_amt - 1)
	{
		close(new_p[0]);
		dup2(new_p[1], 1);
		close(new_p[1]);
	}
}

int	manage(int old_p[], int new_p[])
{
	int	i;

	i = 0;
	g_d.cmd_amt = 0;
	while (g_d.arglist[i])
	{
		g_d.cmd_amt++;
		i++;
	}
	
	i = 0;
	while (i < g_d.cmd_amt)
	{
		if (bad_pipe(new_p, i) == 1)
			return (1);
		child_process(old_p, new_p, i);
		parent_process(old_p, new_p, i);
		i++;
	}
	return (0);
}
