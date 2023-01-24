/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:04:34 by gclement          #+#    #+#             */
/*   Updated: 2023/01/24 14:44:28 by gclement         ###   ########.fr       */
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

void	call_cmd(pid_t c_pid, char **argxec, char **cmd)
{
	char	*dest;
	char	*path;
	int		fd[2];

	if (pipe(fd) == -1)
		exit (0);
	if (c_pid == 0)
	{
		dest = ft_strdup("/usr/bin/");
		path = ft_strjoin(dest, cmd[0]);
		execve(path, argxec, NULL);
	}
	else
	{
		dest = ft_strdup("/bin/");
		path = ft_strjoin(dest, cmd[0]);
		execve(path, argxec, NULL);
	}
	free (dest);
	free (path);
	//free_2d_array(argxec);
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
