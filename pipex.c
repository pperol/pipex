/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pperol <pperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:22:10 by pperol            #+#    #+#             */
/*   Updated: 2022/10/12 10:18:20 by pperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// man : access()  checks  whether the calling process can access the file path‐
// name.  If pathname is a symbolic link, it is dereferenced.

int	ft_check_access(char *file_path_name)
{
	if (access(file_path_name, F_OK) == 0)
		return (1);
	else
		return (0);
}

int	ft_check_args(int ac, char *av[])
{
	t_pipex	pipex;

	if (ac != 5 || ft_check_access(av[1]))
	{
		ft_putstr_fd("Usage:\n./pipex file1 cmd1 cmd2 file2\n", 2);
		return (ft_msg_err(ERR_INPUT));
	}
	pipex.infile = open(av[1], O_RDONLY);
	//if (pipex.infile < 0)
		// ft_msg_exit(ERR_INFILE);
		// ft_msg_errno_exit();
	// cf. int creat(const char *pathname, mode_t mode);
	// eg. man open : A call to creat() is equivalent to calling open() with flags
    // equal to O_CREAT|O_WRONLY|O_TRUNC.
	pipex.outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.infile < 0 || pipex.outfile < 0)
		//ft_msg_exit(ERR_OUTFILE);
		//ft_msg_errno_exit();
		return (EXIT_FAILURE);
	// On success, open(), and creat() return the new file
    // descriptor (a nonnegative integer).  On error, -1 is returned and
    // errno is set to indicate the error.
		

}

char	**ft_get_path(char **env)
{
	int		i;
	int		j;
	char	**path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)	
		{
			path = ft_split((env[i] + 5), ':');
			if (path == NULL)
				return (NULL);
			j = 0;
			while (path[j])
			{
				if (path[i][ft_strlen(path[j]) - 1] != '/')
					path[i] = ft_strjoin(path[j], "/");
				j++;
			}	
			break ;
		}
		i++;
	}
	return (path);
}

char	*ft_get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char **argv, char **env)
{
	int	i;

	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(av[2], ' ');
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	execve(pipex.cmd, pipex.cmd_args, env);
	if (!pipex.cmd)
	{
		i = 0;
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
		free(pipex->cmd);
		ft_strerror_exit(ERR_CMD);
	}
}

void	second_child(t_pipex pipex, char **av, char **env)
{
	int	i;

	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		i = 0;
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
		free(pipex->cmd);
		ft_strerror_exit(ERR_CMD);
	}
	execve(pipex.cmd, pipex.cmd_args, env);
}

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	ft_free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
}

void	ft_pipex(int ac, char **av, char **env)
{
	t_pipex	pipex;

	pipex.paths = ft_find_path(env);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, av, env);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, av, env);
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	ft_free_parent(&pipex);
}


int	main(int ac, char **av, char **env)
{
	ft_check_args(ac, av);
	ft_pipex(infile, outfile, av, env);
	return (0);
}
