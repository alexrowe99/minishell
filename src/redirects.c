/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:51:02 by nspeedy           #+#    #+#             */
/*   Updated: 2022/06/20 12:59:23 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_pipe(t_data *d, int i)
{
	int	j;
	int	fd;

	d->redirect = ft_split(d->arglist[i], '<');
	j = 0;
	while (d->redirect[j])
		j++;
	if (j == 2)
	{
		fd = open(d->redirect[1], O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
}

void	op_cl(t_data *d, int old_p[], int new_p[], int i)
{
	if (i != 0)
	{
		close(old_p[1]);
		dup2(old_p[0], 0);
		close(old_p[0]);
	}
	else
		redir_pipe(d, i);
	if (i != d->cmd_amt - 1)
	{
		close(new_p[0]);
		dup2(new_p[1], 1);
		close(new_p[1]);
	}
}
