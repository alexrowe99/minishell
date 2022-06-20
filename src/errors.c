#include "minishell.h"

void	fatal(char *s1, char *s2, int n)
{
	fprintf(stderr, "Error: %s,%s\n", s1, s2);
	exit(n);
}

void	free_strarray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	freelist(char **list)
{
	char	**cp;
	
	cp = list;
	while(*cp)
		free(*cp++);
	free(list);
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