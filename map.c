#include "so_long.h"
void	file_extension(char *filename)
{
	int i;

	i = 0;
	while (filename[i])
		i++;
	if (i < 4)
		handle_error("Error: Invalid file name\n", NULL, 0);	
	i -= 4;
	if (!(filename[i] == '.' && filename[i + 1] == 'b' && filename[i + 2] == 'e' && filename[i + 3] == 'r'))
		handle_error("Error: Must have \".ber\" extension \n", NULL, 0);
}
/*
open() → dosyayı okuma modunda açar
get_next_line() ile satır satır okuruz
Her satırı free() ederiz çünkü sadece saymak istiyoruz
Okuma bittikten sonra get_next_line(fd, 1) ile static buffer’ı temizleriz
Sonunda satır sayısı height döner
*/
int	map_height(char	*filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	while ((line = get_next_line(fd, 0)))
	{
		height++;
		free(line);
	}
	get_next_line(fd, 1);
	close(fd);
	return (height);
}
/*
malloc ile mape yer açar
open() → dosyayı okuma modunda açar
get_next_line() ile satır satır okuruz heighte kadar
satır sonlarındaki \n leri kırpıp mape atıyoruz
Okuma bittikten sonra get_next_line(fd, 1) ile static buffer’ı temizleriz
Sonunda mapi döner
*/
char	**read_map(char	*filename, int	height)
{
	int 	i;
	int		fd;
	char	**map;
	char	*line;
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while ((line = get_next_line(fd, 0)) && (i < height))
	{
		map[i] = ft_strtrim(line, "\n");
		free(line);
		i++;
	}
	map[i] = NULL;
	get_next_line(fd, 1);
	close(fd);
	return (map);
}
/*
map_height() → satır sayısını buluyor
read_map() → haritayı satır satır okuyup game->map içine yazıyor
game->width = ft_strlen(game->map[0]) ile genişlik hesaplanıyor
Sonra validate_map(game) çağrılıyor
*/
int	parse_map(char	*filename, t_game	*game)
{
	file_extension(filename);
	initialize_game_values(game);
	game -> height = map_height(filename);
	if (game -> height == 0)
		return (handle_error("Map height could not be determined", NULL, 1));
	game -> map = read_map(filename, game -> height);
	if (!game -> map)
		return (handle_error("Map could not be read", game -> map, 1));
	game -> width = ft_strlen(game -> map[0]);
	if (!game -> width)
		return (handle_error("Map width is invalid\n", game -> map, 1));
	if (!validate_map(game))
		return (handle_error("Invalid map format.\n", game -> map, 1));
	if (!validate_walls(game))
		return (handle_error("Map is not enclosed by walls\n", game -> map, 1));
	flood_fill_controller(game);
	return (1);
}
