
#include "pipex.h"

char	**path_find(char **envp)
{
	char **paths;

	while (*envp)
	{
		if (!strncmp(*envp, "PATH", 4))
		{
			*envp = strchr(*envp, '=');
			(*envp)++;
			paths = ft_split(*envp, ':');
			return (paths);
		}
		envp++;
	}
	return (NULL);
}


char	*pars_cmd(char *argv, t_pipex stuff) // bura kontorl edilecek
{
	char **split;
	char *cmd_path;
	char *temp;
	int i;

	split = ft_split(argv, ' ');
	if (!split || !*split)
		return (NULL);

    if (strchr(split[0], '/'))          // NOT YOUR FUNCTİON
    {
        if (access(split[0], F_OK | X_OK) == 0)
        {
            cmd_path = ft_strdup(split[0]);
            free_split(split);
            return (cmd_path);
        }
        
    }
    
	i = -1;
	while (stuff.paths[++i])
	{
		temp = ft_strjoin(stuff.paths[i], "/");
		cmd_path = ft_strjoin(temp, split[0]);
		free(temp);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_split(split);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_split(split);
	return (NULL);
}

void	run_command(char *arguments, t_pipex stuff)
{
	char	**args;

	args = ft_split(arguments, ' ');
    if (!args || !*args)
	{
		perror("ft_split failed or args empty");
		exit(EXIT_FAILURE);
	}
	if (execve(stuff.cmd, args, NULL) == -1)
    {
        perror("execve failed");
        free_split(args);
        exit(EXIT_FAILURE);
    }
}