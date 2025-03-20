/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2025/03/19 23:47:42 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

#define BPP sizeof(int32_t)

int run_game(t_game *game)
{
    game->mlx = mlx_init(512, 512, "cub3d", true);
    if (!game->mlx)
    {
        fprintf(stderr, "Error: mlx_init failed\n");
        exit(EXIT_FAILURE);
    }

    mlx_image_t* img = mlx_new_image(game->mlx, 512, 512); // Proper width and height
    if (!img)
    {
        fprintf(stderr, "Error: mlx_new_image failed\n");
        exit(EXIT_FAILURE);
    }

    memset(img->pixels, 255, img->width * img->height * BPP);

    mlx_image_to_window(game->mlx, img, 128, 128);

    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);

    return (EXIT_SUCCESS);
}

int main(int ac, char *av[])
{
    t_game game;

    if (parse_cub(ac, av, &game.parser)) 
    {
        free_allocations(); // Assuming this function exists and works
        return 1;
    }
    
    run_game(&game);

    free_allocations(); // Free any allocated memory
    return 0;
}

