/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 01:40:34 by ilnassi           #+#    #+#             */
/*   Updated: 2026/03/24 19:35:03 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Loads XPM file as mlx texture and reads pixel address. */
/* Returns 1 on error, 0 on success. */
int	load_texture(t_game *game, t_texture *tex, char *path)
{
	tex->img.img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img.img)
		return (1);
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bpp,
			&tex->img.line_length, &tex->img.byte_order);
	return (0);
}

/* Loads all 4 wall textures (NO=0, SO=1, WE=2, EA=3). */
/* Returns 1 on first error, 0 if all succeed. */
int	load_all_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (load_texture(game, &game->textures[i], game->textures[i].path))
			return (1);
		i++;
	}
	return (0);
}

/* Returns the texture pointer for the wall or door hit. */
/* side 0 (E/W): ray_dir_x > 0 -> EA, else WE. */
/* side 1 (N/S): ray_dir_y > 0 -> SO, else NO. */
t_texture	*get_texture(t_game *game, int side)
{
	if (game->map.grid[game->player.wall_map_y][game->player.wall_map_x]
		== '2')
		return (&game->door_texture);
	if (side == 0)
	{
		if (game->player.ray_dir_x > 0)
			return (&game->textures[TEX_EA]);
		return (&game->textures[TEX_WE]);
	}
	if (game->player.ray_dir_y > 0)
		return (&game->textures[TEX_SO]);
	return (&game->textures[TEX_NO]);
}

/* Returns the color of pixel (tex_x, tex_y) in the texture. */
/* Offset: y * line_length + x * (bpp / 8). */
int	get_tex_pixel(t_texture *tex, int tex_x, int tex_y)
{
	char	*pixel;

	if (!tex->img.addr)
		return (0);
	if (tex_x < 0 || tex_x >= tex->width
		|| tex_y < 0 || tex_y >= tex->height)
		return (0);
	pixel = tex->img.addr
		+ (tex_y * tex->img.line_length + tex_x * (tex->img.bpp / 8));
	return (*(int *)pixel);
}

/* Computes the texture column for the wall hit point. */
/* side 0 uses pos_y, side 1 uses pos_x to find wall_x. */
int	get_tex_x(t_game *game, t_texture *tex, int side, double perp_dist)
{
	double	wall_x;
	int		tex_x;

	if (side == 0)
		wall_x = game->player.pos_y
			+ perp_dist * game->player.ray_dir_y;
	else
		wall_x = game->player.pos_x
			+ perp_dist * game->player.ray_dir_x;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * tex->width);
	if (side == 0 && game->player.ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (side == 1 && game->player.ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
