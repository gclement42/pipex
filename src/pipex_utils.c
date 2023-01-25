/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:04:34 by gclement          #+#    #+#             */
/*   Updated: 2023/01/25 13:41:50 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	**set_argxec(char **cmd, char *filename)
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
	argxec[x] = filename;
	x++;
	argxec[x] = NULL;
	return (argxec);
}

char	**set_argxec_child(char **cmd)
{
	char	**argxec;
	int		x;

	x = 0;
	while (cmd[x])
		x++;
	argxec = malloc((x + 1) * sizeof(char *));
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

	x = 0;
	while (all_path[x])
	{
		tmp = ft_strjoin(all_path[x], "/");
		path = ft_strjoin(tmp, cmd[0]);
		if (execve(path, argxec, NULL) != -1)
			break ;
		free (path);
		free (tmp);
		x++;
	}
	free (path);
	free (tmp);
	free_2d_array(argxec);
}

char	**create_array_path(char *envp[])
{
	int		i;
	char	**all_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	all_path = ft_split(ft_strchr(envp[i], '='), ':');
	return (all_path);
}

void	child(int fd[2], char **argv, char **all_path)
{
	char	**cmd;
	char	**argxec;
	int		out;

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(fd[1]);
	dup(fd[0]);
	out = open(argv[4], O_WRONLY | O_RDONLY);
	cmd = ft_split(argv[3], ' ');
	argxec = set_argxec_child(cmd);
	call_cmd(argxec, cmd, all_path);
    close(fd[0]);
}
