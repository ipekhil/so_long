/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:38:58 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/06 15:55:55 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	initialize_game_values(t_game *game)
{
	game -> mlx = NULL;
	game -> win = NULL;
	game -> map = NULL;
	game -> textures.player = NULL;
	game -> textures.wall = NULL;
	game -> textures.floor = NULL;
	game -> textures.exit = NULL;
	game -> textures.collect = NULL;
	game -> height = 0;
	game -> width = 0;
	game -> player_x = -1;
	game -> player_y = -1;
	game -> moves = 0;
	game -> collectibles = 0;
	game -> collected = 0;
	game -> count = 0;
	game -> exit_reached = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		handle_error("Usage: ./so_long map.ber\n", NULL, 1);
	if (!parse_map(argv[1], &game))
		return (1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	game.win = mlx_new_window(game.mlx, game.width * 64,
			game.height * 64, "so_long");
	if (!game.win)
		return (1);
	init_textures(&game);
	if (!game.textures.player || !game.textures.wall || !game.textures.floor
		|| !game.textures.collect || !game.textures.exit)
	{
		ft_printf("Error\nImage could not be loaded.\n");
		exit_game(&game);
	}
	render(&game);
	mlx_hook(game.win, 17, 0, handle_exit, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
