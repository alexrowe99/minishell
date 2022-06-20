#include "minishell.h"

char	*check_access(char **paths, char *cmd[])
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(path, X_OK) == 0)
		{
			free_strarray(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_strarray(paths);
	return (NULL);
}

char	*find_path(char *cmd[])
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	
	while (environ[i])
	{
		if (ft_strncmp("PATH=", environ[i], 5) == 0)
		{
			paths = ft_split(environ[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (check_access(paths, cmd));
}