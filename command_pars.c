/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:04:38 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/31 14:46:52 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_find(char **envp)
{
	char	**paths;

	while (*envp)
	{
		if (!strncmp(*envp, "PATH=", 5))
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

static int	contains_path(char **split, char **cmd)
{
	if (ft_strchr(split[0], '/'))
	{
		if (access(split[0], F_OK | X_OK) == 0)
		{
			*cmd = ft_strdup(split[0]);
			free_split(split);
			return (1);
		}
		else
		{
			free_split(split);
			*cmd = NULL;
			return (2);
		}
	}
	return (0);
}

static void	join_cmd(char *path, char *split, char **cmd_path)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	*cmd_path = ft_strjoin(tmp, split);
	free(tmp);
}

char	*pars_cmd(char *argv, t_pipex stuff)
{
	char	**split;
	char	*cmd_path;
	int		i;

	split = ft_split(argv, ' ');
	if (!split || !*split)
		return (NULL);
	if (contains_path(split, &cmd_path))
		return (cmd_path);
	i = -1;
	while (stuff.paths[++i])
	{
		join_cmd(stuff.paths[i], split[0], &cmd_path);
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
		perror("ft_split failed");
		exit(EXIT_FAILURE);
	}
	if (stuff.cmd == NULL || execve(stuff.cmd, args, NULL) == -1)
	{
		perror(args[0]);
		free_split(args);
		free_split(stuff.paths);
		free(stuff.cmd);
		exit(EXIT_FAILURE);
	}
}
