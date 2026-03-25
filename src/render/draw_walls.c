/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 01:19:17 by ilnassi           #+#    #+#             */
/*   Updated: 2026/03/24 17:33:53 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Calculates the start and end pixels of the wall's vertical column.
line_height is inversely proportional to the distance.
Values ​​are clamped to the edges of the screen. */
static void	calc_draw_bounds(double perp_wall_dist, int *draw_start,
				int *draw_end, int *line_height)
{
	*line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
	*draw_start = SCREEN_HEIGHT / 2 - *line_height / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = SCREEN_HEIGHT / 2 + *line_height / 2;
	if (*draw_end >= SCREEN_HEIGHT)
		*draw_end = SCREEN_HEIGHT - 1;
}

/* Calculate tex_y: the line in the texture for pixel y.
* Uses the actual position relative to the entire height of the column,
* not just the visible portion. The clamp avoids out-of-bounds near the wall.*/
static int	calc_tex_y(int y, int line_height, t_texture *tex)
{
	int	real_y;
	int	tex_y;

	real_y = y + line_height / 2 - SCREEN_HEIGHT / 2;
	tex_y = (real_y * tex->height) / line_height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	return (tex_y);
}

/* Draws the vertical column of the textured wall.
* Selects the correct texture for each side (N/S/E/W),
* calculates tex_x and for each pixel calculates tex_y and prints the color. */
void	draw_wall(t_game *game, int x, double perp_wall_dist, int side)
{
	t_wall		w;
	t_texture	*tex;

	if (perp_wall_dist <= 0)
		perp_wall_dist = 0.0001;
	calc_draw_bounds(perp_wall_dist, &w.draw_start,
		&w.draw_end, &w.line_height);
	tex = get_texture(game, side);
	w.tex_x = get_tex_x(game, tex, side, perp_wall_dist);
	w.y = w.draw_start;
	while (w.y <= w.draw_end)
	{
		my_mlx_pixel_put(&game->img, x, w.y,
			get_tex_pixel(tex, w.tex_x,
				calc_tex_y(w.y, w.line_height, tex)));
		w.y++;
	}
}
