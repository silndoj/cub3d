/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:16:26 by tndreka           #+#    #+#             */
/*   Updated: 2025/03/17 22:06:28 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include <stdio.h>

int parse_cub(int ac, char *av[])
{
    if (ac != 2)
    {
        printf("Error: Wrong number of arguments\n");
        return (1);
    }
    return (check_map(av[1]));
}

int check_map(char *file)
{
    int fd;
    int i;

    i = ft_strlen(file);
    
    if (i < 4 || ft_strcmp(file + i - 4, ".cub") != 0)
    {
        printf("Error: Run ./cub3d map_name.cub\n");
        return (1);
    }
    fd = open(file, O_RDONLY);
    if (fd == -1)
	{
		printf("Error: File not found\n");
        return (1);
	}
    close(fd);
    return (0);
}
