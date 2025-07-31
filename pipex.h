/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:08:47 by hyakici           #+#    #+#             */
/*   Updated: 2025/07/31 15:13:30 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**paths;
	char	*cmd;

}			t_pipex;

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *str, int c);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		control_params(int argc, char **argv);
int			output_file_exist(char *outfile);
char		**path_find(char **envp);
char		*pars_cmd(char *argv, t_pipex stuff);
void		free_split(char **split);
void		run_command(char *arguments, t_pipex stuff);

void		start_pipex(t_pipex *pipex, int argc, char **argv, char **envp);
void		init_pipes(int pipes[2]);
void		start_fork(int pipes[2], int argc, char **argv, t_pipex pipex_info);
void		close_fds(int pipes[2], int infile, int outfile);
void		wait_for_childs(void);

#endif