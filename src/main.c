/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2025/03/20 18:03:28 by silndoj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

#define BPP sizeof(int32_t)

int run_game(t_game *game)
{
//    mlx_set_setting(MLX_MAXIMIZED, true);
    game->mlx = mlx_init(800, 800, "cub3d", true);
    if (!game->mlx)
    {
        fprintf(stderr, "Error: mlx_init failed\n");
        exit(EXIT_FAILURE);
    }

    mlx_image_t* img = mlx_new_image(game->mlx, 800, 800); // Proper width and height
    if (!img)
    {
        fprintf(stderr, "Error: mlx_new_image failed\n");
        exit(EXIT_FAILURE);
    }

    memset(img->pixels, 255, img->width * img->height * BPP);

    mlx_image_to_window(game->mlx, img, 0, 0);
    //draw map
    simple_map(img);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);

    return (EXIT_SUCCESS);
}

void simple_map(mlx_image_t* img)
{
    char **map;

    map = ft_malloc(sizeof(char *) * 11);
    map[0] = ft_strdup("1111111111");
    map[1] = ft_strdup("1000000001");
    map[2] = ft_strdup("1000000001");
    map[3] = ft_strdup("1000000001");
    map[4] = ft_strdup("1000101001");
    map[5] = ft_strdup("1000000001");
    map[6] = ft_strdup("1000000001");
    map[7] = ft_strdup("1000000001");
    map[8] = ft_strdup("1000000001");
    map[9] = ft_strdup("1111111111");
    map[10] = 0;

    int x;
    int y;
    int sq_size_x;
    int sq_size_y;

    y = 0;
    sq_size_x = 800  / 10; // width of the window divided by number of colums
    sq_size_y =  800 / 10;  // window height  devided by  number of rows
    while (map[y])
    {
        x = 0;
        while(map[y][x])
        {
            for (int i =0; i < sq_size_x; i++)
                for(int j = 0; j <sq_size_y; j++)
                {
                    if(map[y][x] == '1')
                        mlx_put_pixel(img, x * sq_size_x + i, y * sq_size_y + j, 0x000000FF);
                    else
                    {
                        mlx_put_pixel(img, x * sq_size_x + i, y * sq_size_y + j, 0xFF0000FF);
                        for( int k = 0; k < sq_size_x; k++)
                        {
                            mlx_put_pixel(img, x * sq_size_x + k, y *  sq_size_y,  0xFFFFFFFF);
                        }
                        for(int k = 0; k < sq_size_x; k++)
                        {
                            mlx_put_pixel(img, x * sq_size_x + k, y *  sq_size_y + sq_size_x - 1,  0xFFFFFFFF);
                        }
                        for( int k = 0; k < sq_size_x; k++)
                        {
                            mlx_put_pixel(img, x * sq_size_x, y *  sq_size_y + k,  0xFFFFFFFF);
                        }
                        for( int k = 0; k < sq_size_x; k++)
                        {
                            mlx_put_pixel(img, x * sq_size_x  + sq_size_y  - 1, y *  sq_size_y + k,  0xFFFFFFFF);
                        }
                    }

                }
            x++;
        }
        y++;
    }
}

int main(int ac, char *av[])
{
    t_game game;

    if (map_build(ac, av, &game.parser))
        return (free_allocations(),1);
    run_game(&game);
    return (free_allocations(),0);
}

