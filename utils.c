/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:39:05 by ubuntu            #+#    #+#             */
/*   Updated: 2025/04/06 14:59:45 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	handle_exit(void *parameter)
{
	t_game	*game;

	game = (t_game *)parameter;
	exit_game(game);
	return (0);
}

void	exit_game(t_game *game)
{
	free_map(game -> map);
	mlx_destroy_image(game -> mlx, game ->textures.collect);
	mlx_destroy_image(game -> mlx, game ->textures.exit);
	mlx_destroy_image(game -> mlx, game ->textures.floor);
	mlx_destroy_image(game -> mlx, game ->textures.player);
	mlx_destroy_image(game -> mlx, game ->textures.wall);
	mlx_destroy_window(game -> mlx, game -> win);
	mlx_destroy_display(game -> mlx);
	free(game -> mlx);
	exit(0);
}

int	handle_error(char *msg, char **map, int exit_mode)
{
	ft_printf("Error\n%s\n", msg);
	if (map)
		free_map(map);
	if (exit_mode == 1)
		exit(1);
	return (0);
}

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
