#include "minishell.h"

extern t_data g_d;

void    redirect(int i)
{
    int j;
    int fd;
	char **r;

    j = 1;
	r = space_split(g_d.arglist[i], '>');
    while (r[j])
	{
		fd = open(space_split(r[j], ' ')[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, 1);
		close(fd);
		j++;
	}
	if (j > 1)
		*ft_strrchr(g_d.arglist[i], '>') = '\0';
}