/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:04:34 by gclement          #+#    #+#             */
/*   Updated: 2023/01/27 10:28:54 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <stdio.h>

char	**set_argxec(char **cmd)
{
	char	**argxec;
	int		x;

	x = 0;
	while (cmd[x])
		x++;
	argxec = malloc((x + 2) * sizeof(char *));
	if (!argxec)
		exit (EXIT_FAILURE);
	x = 0;
	while (cmd[x])
	{
		argxec[x] = cmd[x];
		x++;
	}
	argxec[x] = NULL;
	return (argxec);
}

void	call_cmd(char **argxec, char **cmd, char **all_path)
{
	char	*path;
	char	*tmp;
	int		x;

	x = -1;
	while (all_path[++x])
	{
		tmp = ft_strjoin(all_path[x], "/");
		if (!tmp)
			exit (EXIT_FAILURE);
		path = ft_strjoin(tmp, cmd[0]);
		if (!path)
			exit (EXIT_FAILURE);
		if (access(path, X_OK) == 0)
		{
			free (all_path);
			free (tmp);
			execve(path, argxec, NULL);
		}
		free(path);
		free(tmp);
	}
	free_2d_array(argxec);
	ft_putstr_fd("command not found\n", 2);
	exit (EXIT_SUCCESS);
}

static void exe_cmd(char *arg, char **all_path)
{
	char	**cmd;
	char	**argxec;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		exit (EXIT_FAILURE);
	argxec = set_argxec(cmd);
	if (ft_strnstr(cmd[0], "./", 2) != 0)
		exit_wrong_cmd(cmd);
	call_cmd(argxec, cmd, all_path);
}


void	set_scnd_cmd(int fd[2], char **argv, char **all_path)
{
	int		out_fd;
	int		fd_pipe2[2];

	wait(NULL);
	close(fd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (dup(fd[0]) == -1)
		exit (EXIT_FAILURE);
	out_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup(out_fd);
	if (open(argv[1], O_RDONLY) == -1)
	{
		close (out_fd);
		pipe(fd_pipe2);
		close (fd_pipe2[0]);
		dup(fd_pipe2[1]);
	}
	exe_cmd(argv[3], all_path);
}

void	set_frst_cmd(int fd[2], char **argv, char **all_path)
{
	int		in_fd;

	in_fd = open(argv[1], O_RDONLY);
	if (in_fd == -1)
		exit(0);
	close(fd[0]);
	dup2(in_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	exe_cmd(argv[2], all_path);
	
}
