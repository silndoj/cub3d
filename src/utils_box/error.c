/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silndoj <silndoj@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 00:02:44 by silndoj           #+#    #+#             */
/*   Updated: 2025/04/30 02:38:41 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/cub3d.h"

int	errno_exit(void)
{
	printf("Error: %s\n", strerror(errno));
	return (EXIT_FAILURE);
}
