/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:16:26 by tndreka           #+#    #+#             */
/*   Updated: 2025/03/17 21:41:48 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int parse_cub(int ac, char *av[])
{
    if (ac != 2)
    {
        printf("Error\nWrong number of arguments\n");
        return (1);
    }
    if (check_file(av[1]) == 1)
    {
        printf("Error\nFile not found\n");
        return (1);
    }
    return (0);
}

int check_file(char *file)
{
    int fd;
    int i;

    i = ft_strlen(file);
    
    if (i < 4 || ft_strcmp(file + i - 4, ".cub") != 0)
    {
        printf("Invalide file\n File must end .cub\n");
        return (1);
    }
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        printf("Fialed to open the file\n");
        return (1);
    }
    close(fd);
    return (0);
}
