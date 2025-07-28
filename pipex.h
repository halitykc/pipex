

#ifndef PIPEX_H
#define PIPEX_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_pipex
{
    int infile;
    int outfile;
}              t_pipex;



char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);

void    control_params(int argc, char **argv);

void    start_pipex(t_pipex *pipex, int argc, char **argv);
void    init_pipes(int pipes[][2], int argc);
void    start_fork(int pipes[][2], int argc, char **argv, t_pipex pipex_info);
void    close_fds(int argc, int pipes[][2], int infile, int outfile);
void    wait_for_childs(int argc);


#endif