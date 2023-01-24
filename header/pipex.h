/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:21:51 by gclement          #+#    #+#             */
/*   Updated: 2023/01/24 14:44:17 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../Libft/libft.h"

char	**set_argxec(char **cmd, char *filename);
void	call_cmd(pid_t c_pid, char **argxec, char **cmd);
char	**create_array_path(char *envp[]);

void	*free_2d_array(char **ptr);

#endif
