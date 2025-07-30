/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:09:21 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/29 17:59:34 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	init_pipes(int pipes[2])
{
	if (pipe(pipes) == -1)
	{
		perror("Pipe Failed\n");
		exit(EXIT_FAILURE);
	}
}

void	close_fds(int pipes[2], int infile, int outfile)
{
	close(pipes[0]);
	close(pipes[1]);
	close(outfile);
	close(infile);
}

void	wait_for_childs(void)
{
	wait(NULL);
}


void	start_fork(int pipes[2], int argc, char **argv, t_pipex pipex_info)
{
	int	i;

	i = -1;
	while (++i < argc - 3)
	{
		if (fork() == 0)
		{
			if (i == 0)
				dup2(pipex_info.infile, STDIN_FILENO);
			else
				dup2(pipes[0], STDIN_FILENO);
			if (i == argc - 4)
				dup2(pipex_info.outfile, STDOUT_FILENO);
			else
				dup2(pipes[1], STDOUT_FILENO);
			close_fds(pipes, pipex_info.infile, pipex_info.outfile);
			pipex_info.cmd = pars_cmd(argv[i + 2], pipex_info);
			run_command(argv[i + 2], pipex_info);
		}
	}
}

void	start_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDWR, 0644);
	if (!output_file_exist(argv[argc - 1]))
	{
		pipex->outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	else
		pipex->outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	pipex->paths = path_find(envp);
}


/*			CONTROL			*/


void	check_if_validfile(char *file)
{
	if (access(file, F_OK) != 0)
	{
		write(1, " ==> File Doesnt Exist!\n", 24);
		exit(EXIT_FAILURE);
	}
	if (access(file, R_OK | W_OK) != 0)
	{
		write(1, " ==> Check File Permisions!\n", 28);
		exit(EXIT_FAILURE);
	}
}

int	output_file_exist(char *outfile)
{
	if (access(outfile, F_OK) != 0)
	{
		return (1);
	}
	else
		return (0);
}

void	control_params(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc - 1)
	{
		if (i == 1)
			check_if_validfile(argv[i]);
	}
	if (i == argc - 1 && !output_file_exist(argv[argc - 1]))
	{
		check_if_validfile(argv[i]);
	}
}
