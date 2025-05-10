/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:02:44 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/10 07:14:29 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <unistd.h>

int	exit_error(const char *msg)
{
	ft_putstr_fd("Error \n", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_allocations();
	exit(EXIT_FAILURE);
}

void	errno_exit(void)
{
	if (write(STDERR_FILENO, "Error: ", 7) < 0)
		return ;
	perror(strerror(errno));
	if (write(STDERR_FILENO, "\n", 1) < 0)
		return ;
	exit(EXIT_FAILURE);
}

void	errno_error_mlx(void)
{
	if (write(STDERR_FILENO, "Error: ", 7) < 0)
		return ;
	perror(mlx_strerror(mlx_errno));
	if (write(STDERR_FILENO, "\n", 1) < 0)
		return ;
	exit(EXIT_FAILURE);
}

void	close_hook(t_game *game)
{
	mlx_terminate(game->mlx);
	free_allocations();
	exit(0);
}
