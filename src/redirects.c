#include "minishell.h"

void	handle_redirect(char *cmd)
{
	char **redirect_in;
	char **redirect_out;
	int rinlen;
	int routlen;

	redirect_in = ft_split(cmd, '<');
	redirect_out = ft_split(cmd, '>');
	rinlen = strarrlen(redirect_in);
	routlen = strarrlen(redirect_out);

	if (rinlen == 1 && routlen == 1)
		return;
}

void	redir_pipe(t_data *d, int i)
{
	int j;

	d->redirect = ft_split(d->arglist[i], '<');
	j = 0;
	while (d->redirect[j])
		j++;
	if (j == 2) 
	{
		int fd = open(d->redirect[1], O_RDONLY);
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