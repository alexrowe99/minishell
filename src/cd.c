/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:26:22 by alex              #+#    #+#             */
/*   Updated: 2022/07/13 16:48:22 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_d;

int	cd(void)
{
	char	c[256];
	int		i;

	if (ft_strncmp(g_d.command_args[0], "cd", 2) == 0)
	{
		chdir(g_d.command_args[1]);
		getcwd(c, sizeof(c));
		printf("%s\n", c);
		return (0);
	}
	return (1);
}