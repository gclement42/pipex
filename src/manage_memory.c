/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:46:10 by gclement          #+#    #+#             */
/*   Updated: 2023/01/26 18:47:31 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	*free_2d_array(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

void exit_wrong_cmd(char **cmd)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
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