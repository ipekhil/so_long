#include "so_long.h"
#include <stdio.h>
void    render(t_game *game)
{
    int row;
    int col;

    row = -1;
    while (game -> map[++row])
    {
        col = -1;
        while (game -> map[row][++col])
        {
            if (game -> map[row][col] == '1')
                mlx_put_image_to_window(game -> mlx, game -> win, game -> textures.wall, col * 64, row * 64);
            else if (game -> map[row][col] == 'P')
                mlx_put_image_to_window(game -> mlx, game -> win, game -> textures.player, col * 64, row * 64);
            else if (game -> map[row][col] == 'E')
                mlx_put_image_to_window(game -> mlx, game -> win, game -> textures.exit, col * 64, row * 64);
            else if (game -> map[row][col] == 'C')
                mlx_put_image_to_window(game -> mlx, game -> win, game -> textures.collect, col * 64, row * 64);
            else
                mlx_put_image_to_window(game -> mlx, game -> win, game -> textures.floor, col * 64, row * 64);
        }
    }
}

