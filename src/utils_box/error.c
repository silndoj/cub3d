/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka < tndreka@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:02:44 by silndoj           #+#    #+#             */
/*   Updated: 2025/05/06 16:42:48 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/cub3d.h"

int	exit_error(const char *msg)
{
	printf("Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

int	errno_exit(void)
{
	printf("Error: %s\n", strerror(errno));
	return (EXIT_FAILURE);
}
