/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:02:44 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/09 03:09:09 by silndoj          ###   ########.fr       */
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
