/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:38:55 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/06 14:38:56 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game	*game, void *img, int col, int row)
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
