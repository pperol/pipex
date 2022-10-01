/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:22:28 by pperol            #+#    #+#             */
/*   Updated: 2022/10/01 17:10:04 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* write, read, close, access, pipe, dup, execve */
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

/*
** DATAS ****************
*/
typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
}	t_pipe;	

/*
** PARSING ****************
*/
int			ft_parsing(char **arg);

/*
** LIBFT ****************
*/
size_t  ft_strlen(const char *s);
size_t  ft_strclen(const char *s, char c);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(char const *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
