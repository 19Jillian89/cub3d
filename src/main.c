/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:11:59 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 20:12:16 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Sets dir and room_plane vectors to 0, then assigns non-zero values */
/* based on the spawn direction character (N/S/E/W). */
static void	set_player_vectors(t_game *game, char dir)
{
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.room_plane_x = 0;
	game->player.room_plane_y = 0;
	if (dir == 'N')
		game->player.dir_y = -1;
	else if (dir == 'S')
		game->player.dir_y = 1;
	else if (dir == 'E')
		game->player.dir_x = 1;
	else
		game->player.dir_x = -1;
	if (dir == 'N')
		game->player.room_plane_x = 0.66;
	else if (dir == 'S')
		game->player.room_plane_x = -0.66;
	else if (dir == 'E')
		game->player.room_plane_y = 0.66;
	else
		game->player.room_plane_y = -0.66;
}

/* Positions the player at the center of the spawn cell (+0.5), */
/* sets direction vectors and replaces spawn char with '0'. */
static void	init_player(t_game *game)
{
	char	dir;

	dir = game->map.player_dir;
	game->player.pos_x = game->map.player_x + 0.5;
	game->player.pos_y = game->map.player_y + 0.5;
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
	set_player_vectors(game, dir);
}

/* Checks that all 4 texture paths and both colors were parsed. */
/* Calls error_exit if any mandatory element is missing. */
static void	check_elements(t_game *game)
{
	int	i;

	if (game->floor_color == -1 || game->ceiling_color == -1)
		error_exit(game, "Missing floor or ceiling color");
	i = 0;
	while (i < 4)
	{
		if (!game->textures[i].path)
			error_exit(game, "Missing texture path");
		i++;
	}
}

/* Allocates t_game, parses and validates the map, inits mlx, */
/* window, image, keys, textures and hooks. Returns t_game ptr. */
t_game	*init_game(char *cub_path)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		error_exit(NULL, "Failed to allocate game struct");
	ft_memset(game, 0, sizeof(t_game));
	game->floor_color = -1;
	game->ceiling_color = -1;
	parse_file(game, cub_path);
	check_elements(game);
	validate_map(game);
	init_player(game);
	game->mlx = init_mlx();
	game->win = create_window(game->mlx);
	init_image(game);
	init_keys(game);
	if (load_all_textures(game))
		error_exit(game, "Failed to load textures");
	load_weapon(game);
	setup_hooks(game);
	return (game);
}

/* Validates argument count, inits the game and starts the loop. */
int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		error_exit(NULL, "Usage: ./cub3D <map.cub>");
	game = init_game(argv[1]);
	start_loop(game);
	return (0);
}
