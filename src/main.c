/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:08:43 by gclement          #+#    #+#             */
/*   Updated: 2023/01/25 08:52:53 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char	*argv[], char *envp[])
{
	char	**cmd;
	char	**argxec;
	char	**all_path;

	(void) argc;
	all_path = create_array_path(envp);
	cmd = ft_split(argv[2], ' ');
	argxec = set_argxec(cmd, argv[1]);
	call_cmd(argxec, cmd, all_path);
	cmd = ft_split(argv[3], ' ');
	argxec = set_argxec(cmd, argv[5]);
	call_cmd(argxec, cmd, all_path);
	free_2d_array(all_path);
	exit (EXIT_SUCCESS);
}
