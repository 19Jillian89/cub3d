/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:00:00 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 18:08:01 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** WHY: Bonus version of render.c — identical to the mandatory one, except
**      it calls render_minimap() after raycast() and 
** 		before mlx_put_image_to_window.
**      Kept in a separate file to comply with norminette:
**      #ifdef inside a function body is forbidden.
**      Compiled only with `make bonus` (obj_bonus/, -DBONUS flag).
**      Replaces src/render/render.c in the bonus build.
**
** CALLED FROM: mlx_loop_hook (via setup_hooks), every frame.
*/

#include "cub3d.h"

/* Creates the image used for rendering (double buffering). */
void	init_image(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img.img)
		error_exit(game, "Failed to create image");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp,
			&game->img.line_length, &game->img.byte_order);
}

/* Writes a pixel into the image buffer with bounds check. */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(int *)dst = color;
}

/* Clears all pixels in the image buffer (sets to black). */
void	clear_image(t_game *game)
{
	ft_memset(game->img.addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT
		* (game->img.bpp / 8));
}

/* Bonus rendering: calls render_minimap after raycast and before
 * pushing the image to the window. */
int	render(t_game *game)
{
	move_player(game);
	clear_image(game);
	draw_floor_ceiling(game);
	raycast(game);
	render_animated_sprites(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	draw_weapon(game);
	return (0);
}
