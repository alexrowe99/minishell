/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:56:33 by nspeedy           #+#    #+#             */
/*   Updated: 2022/06/20 13:42:35 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bad_pipe(t_data *d, int new_p[], int i)
{
	if (i != d->cmd_amt - 1)
	{
		if (pipe(new_p) == -1)
		{
			printf("bad pipe\n");
			return (1);
		}
	}
	d->pid = fork();
	if (d->pid < 0)
	{
		printf("bad fork\n");
		return (1);
	}
	return (0);
}

void	child_process(t_data *d, int old_p[], int new_p[], int i)
{
	if (d->pid == 0)
	{
		op_cl(d, old_p, new_p, i);
		d->command_args = ft_split(d->arglist[i], ' ');
		if (access(d->command_args[0], X_OK) != 0)
			d->command = find_path(d->command_args);
		else
			d->command = d->command_args[0];
		execve(d->command, d->command_args, environ);
		perror("execve");
	}
}

void	parent_process(t_data *d, int old_p[], int new_p[], int i)
{
	if (d->pid > 0)
	{	
		if (i != 0)
		{
			close(old_p[0]);
			close(old_p[1]);
		}
		if (i != d->cmd_amt - 1)
		{
			old_p[0] = new_p[0];
			old_p[1] = new_p[1];
		}
		wait(NULL);
	}
}

int	manage(t_data *d, int old_p[], int new_p[])
{
	int	i;

	i = 0;
	d->cmd_amt = 0;
	while (d->arglist[i])
	{
		d->cmd_amt++;
		i++;
	}
	i = 0;
	while (i < d->cmd_amt)
	{
		if (bad_pipe(d, new_p, i) == 1)
			return (1);
		child_process(d, old_p, new_p, i);
		parent_process(d, old_p, new_p, i);
		i++;
	}
	return (0);
}
