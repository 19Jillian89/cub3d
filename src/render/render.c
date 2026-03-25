/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:20:09 by ilnassi           #+#    #+#             */
/*   Updated: 2026/03/24 19:35:13 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Creates the image buffer for double buffering.
mlx_new_image allocates the image; mlx_get_data_addr returns
the pointer to the raw pixels for direct writing. */
void	init_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img.img)
		error_exit(game, "Failed to create image");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.byte_order);
}

/* Writes a pixel to the image buffer.
offset = y * line_length + x * (bpp / 8). Ignores off-screen coordinates. */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(int *)dst = color;
}

/* Clear all pixels in the buffer (black). */
void	clear_image(t_game *game)
{
	ft_memset(game->img.addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT
		* (game->img.bpp / 8));
}

/* Render a frame: move the player, clear the buffer,
draw the floor/ceiling, perform raycasting, send to the viewport,
draw the weapon above. Called approximately 60 times per second 
by mlx_loop_hook. */
int	render(t_game *game)
{
	move_player(game);
	clear_image(game);
	draw_floor_ceiling(game);
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	draw_weapon(game);
	return (0);
}
