/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:02:44 by silndoj           #+#    #+#             */
/*   Updated: 2025/04/30 17:03:57 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/cub3d.h"
#include <unistd.h>

void	errno_exit(void)
{
	write(STDERR_FILENO, "Error: ", 7);
	perror(strerror(errno));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	errno_error_mlx(void)
{
	write(STDERR_FILENO, "Error: ", 7);
	perror(mlx_strerror(mlx_errno));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
