/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspeedy <nspeedy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:50:56 by nspeedy           #+#    #+#             */
/*   Updated: 2022/06/20 13:44:38 by nspeedy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strarray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	exsit(char *cmdline, char **arglist)
{
	int	exit_code;

	if (ft_strncmp("exit", cmdline, 4) == 0)
	{
		if (ft_strncmp("exit", cmdline, ft_strlen(cmdline)) == 0)
			exit(0);
		arglist = ft_split(cmdline, ' ');
		exit_code = ft_atoi(arglist[1]);
		exit(exit_code);
	}
}
