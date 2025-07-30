/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:06:06 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/29 15:46:54 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **res, int i)
{
	while (--i >= 0)
		free(res[i]);
	free(res);
}

int	main(int argc, char *argv[], char **envp)
{
	int		pipe[2];
	t_pipex	pipe_infos;

	if (argc == 5)
	{
		control_params(argc, argv);
		start_pipex(&pipe_infos, argc, argv, envp);
		init_pipes(pipe);
		start_fork(pipe, argc, argv, pipe_infos);
		close_fds(pipe, pipe_infos.infile, pipe_infos.outfile);
		wait_for_childs();
		free_split(pipe_infos.paths);
		return (0);
	}
	else
	{
		write(1,"Thats how yu use it ./pipex file1 \"cmd\" \"cmd2\" file2\n",54);
	}
	
}
