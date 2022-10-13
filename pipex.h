/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:22:28 by pperol            #+#    #+#             */
/*   Updated: 2022/10/12 22:15:40 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

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


# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"

/*
** DATAS ****************
*/
typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_pipe;	

/*
** PARSING ****************
*/
int		ft_check_access(char *file_path_name);
int		ft_check_args(int ac, char **av);


/*
** PIPEX ******************
*/
char	*ft_get_cmd(char **paths, char *cmd);
void	ft_free_child(t_pipe *pipex);
void	ft_child(int child, t_pipe pipex, char **argv, char **env);
char	*ft_find_path(char **env);
void	ft_free_cmd_path(t_pipe *pipex);
void	ft_pipex(char **av, char **env);

/*
** ERRORS *****************
*/
int		ft_msg_err(char *msg);

/*
** LIBFT ******************
*/
size_t  ft_strlen(const char *s);
size_t  ft_strclen(const char *s, char c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(char const *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);

#endif
