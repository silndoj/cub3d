/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:02:44 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/06 19:52:03 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/cub3d.h"

int	exit_error(const char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_allocations();
	exit(EXIT_FAILURE);
}

int	errno_exit(void)
{
	printf("Error: %s\n", strerror(errno));
	return (EXIT_FAILURE);
}
