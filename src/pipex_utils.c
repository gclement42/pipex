/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:04:34 by gclement          #+#    #+#             */
/*   Updated: 2023/02/13 14:03:54 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	**set_argxec(char **cmd)
{
	char	**argxec;
	int		x;

	x = 0;
	while (cmd[x])
		x++;
	argxec = malloc((x + 1) * sizeof(char *));
	if (!argxec)
		return (NULL);
	x = 0;
	while (cmd[x])
	{
		argxec[x] = ft_strdup(cmd[x]);
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
			free_in_execmd(all_path, cmd, argxec);
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (!path)
			free_in_execmd(all_path, cmd, argxec);
		if (access(path, X_OK) == 0)
		{
			free_2d_array(all_path);
			execve(path, argxec, NULL);
		}
		free(path);
	}
	free_in_execmd(all_path, cmd, argxec);
	ft_putstr_fd("command not found\n", 2);
	exit (EXIT_SUCCESS);
}

static	void	exe_cmd(char *arg, char **all_path)
{
	char	**cmd;
	char	**argxec;

	cmd = ft_split(arg, ' ');
	if (!cmd)
	{
		free_2d_array(all_path);
		exit (EXIT_FAILURE);
	}
	if (ft_strnstr(cmd[0], "./", 2) != 0)
		exit_wrong_cmd(cmd, all_path);
	argxec = set_argxec(cmd);
	if (!argxec)
	{
		free_2d_array(cmd);
		free_and_exit(all_path);
	}
	call_cmd(argxec, cmd, all_path);
}

void	set_scnd_cmd(int fd[2], char **argv, char **all_path)
{
	int		out_fd;
	int		fd_pipe2[2];

	close(fd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (dup(fd[0]) == -1)
		exit (EXIT_FAILURE);
	out_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (open(argv[1], O_RDONLY) == -1)
	{
		close (out_fd);
		if (pipe(fd_pipe2) == -1)
			free_and_exit(all_path);
		close (fd_pipe2[0]);
		if (dup(fd_pipe2[1]) == -1)
			free_and_exit(all_path);
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
	if (dup2(in_fd, STDIN_FILENO) == -1)
		free_and_exit(all_path);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		free_and_exit(all_path);
	exe_cmd(argv[2], all_path);
}
