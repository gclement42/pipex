/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:08:43 by gclement          #+#    #+#             */
/*   Updated: 2023/01/24 14:44:15 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char	*argv[], char *envp[])
{
	char	**cmd;
	char	**argxec;
	pid_t	c_pid;
	char	**all_path;

	(void) argc;
	all_path = create_array_path(envp);
	cmd = ft_split(argv[2], ' ');
	argxec = set_argxec(cmd, argv[1]);
	c_pid = fork();
	if (c_pid == -1)
		exit(EXIT_FAILURE);
	call_cmd(c_pid, argxec, cmd);
	exit (EXIT_SUCCESS);
}
