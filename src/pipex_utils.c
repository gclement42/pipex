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

char	**create_array_path(char *envp[])
{
	int		i;
	char	**all_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	all_path = ft_split(ft_strchr(envp[i], '='), ':');
	if (!all_path)
		exit (EXIT_FAILURE);
	return (all_path);
}

void	execute_scnd_cmd(int fd[2], char **argv, char **all_path)
{
	char	**cmd;
	char	**argxec;
	int		out_fd;

	wait(NULL);
	close(fd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (dup(fd[0]) == -1)
		exit (EXIT_FAILURE);
	out_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	cmd = ft_split(argv[3], ' ');
	if (!cmd)
		exit (EXIT_FAILURE);
	argxec = set_argxec(cmd);
	call_cmd(argxec, cmd, all_path);
	exit(0);
}

void	execute_frst_cmd(int fd[2], char **argv, char **all_path)
{
	char	**cmd;
	char	**argxec;
	int		in_fd;

	in_fd = open(argv[1], O_RDONLY);
	if (in_fd == -1)
		exit(0);
	close(fd[0]);
	dup2(in_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	cmd = ft_split(argv[2], ' ');
	if (!cmd)
		exit (EXIT_FAILURE);
	argxec = set_argxec(cmd);
	call_cmd(argxec, cmd, all_path);
	exit (0);
}
