/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:37:55 by pperol            #+#    #+#             */
/*   Updated: 2022/11/24 17:28:02 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* write, read, close, access, pipe, fork, dup, execve */
# include <unistd.h>
# include <sys/uio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* fork, pid_t */
# include <sys/types.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/* perror*/
# include <stdio.h>

# define ERR_INPUT "Invalid number of arguments.\n"
//# define ERR_ACCESS "No such file or directory\n"
//# define ERR_CMD "Invalid command\n"
# define ERR_CMD "Error: command not found"
# define ERR "Error: "

/*
** DATAS ****************
*/
typedef struct s_pipe
{
	int		infile;
	int		outfile;
	char	**path;
	int		pipefd[2];
}	t_pipe;	

/*
** PIPEX ******************
*/
void	ft_print_error();
char	*ft_find_path(char **env);
char	*ft_get_cmd(char **paths, char *cmd);
void	ft_free_child(char **args, char *cmd);
void	ft_child(size_t child, t_pipe *pipex, char **argv, char **env);
void	ft_free_cmd_path(t_pipe *pipex);
void	ft_pipex(t_pipe *pipex, char **av, char **env);

/*
** LIBFT ******************
*/
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);

#endif
