/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:25:55 by hiipek            #+#    #+#             */
/*   Updated: 2025/04/08 11:20:32 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_textures(t_game *game)
{
	int	img_width;
	int	img_height;

	game -> textures.floor = mlx_xpm_file_to_image(game -> mlx,
			"textures/floor.xpm", &img_width, &img_height);
	game -> textures.player = mlx_xpm_file_to_image(game -> mlx,
			"textures/player.xpm", &img_width, &img_height);
	game -> textures.exit = mlx_xpm_file_to_image(game -> mlx,
			"textures/exit6.xpm", &img_width, &img_height);
	game -> textures.wall = mlx_xpm_file_to_image(game -> mlx,
			"textures/wall5.xpm", &img_width, &img_height);
	game -> textures.collect = mlx_xpm_file_to_image(game -> mlx,
			"textures/collectible2.xpm", &img_width, &img_height);
}

static void	put_image(t_game	*game, void *img, int col, int row)
{
	mlx_put_image_to_window(game -> mlx, game -> win, img, col * 64, row * 64);
}

void	render(t_game	*game)
{
	int	row;
	int	col;

	row = -1;
	while (game -> map[++row])
	{
		col = -1;
		while (game -> map[row][++col])
		{
			if (game -> map[row][col] == '1')
				put_image(game, game -> textures.wall, col, row);
			else if (game -> map[row][col] == 'P')
				put_image(game, game -> textures.player, col, row);
			else if (game -> map[row][col] == 'E')
				put_image(game, game -> textures.exit, col, row);
			else if (game -> map[row][col] == 'C')
				put_image(game, game -> textures.collect, col, row);
			else
				put_image(game, game -> textures.floor, col, row);
		}
	}
}
