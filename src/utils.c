#include "minishell.h"

int	strarrlen(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*newstr(char *s, int l)
{
	char *rv;

	rv = emalloc(l+1);
	rv[l] = '\0';
	strncpy(rv, s, l);
	return rv;
}

void	*emalloc(size_t n)
{
	void *rv;

	if ( (rv = malloc(n)) == NULL )
		fatal("out of memory","",1);
	return rv;
}

void	*erealloc(void *p, size_t n)
{
	void *rv;

	if ( (rv = realloc(p,n)) == NULL )
		fatal("realloc() failed","",1);
	return rv;
}

void	init_struct(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
}