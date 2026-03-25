/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:56:57 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 19:31:41 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <mlx.h>

/* t_img: MLX image used for screen buffer and wall textures (XPM) */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		byte_order;
}	t_img;

/* t_keys: key state flags for smooth movement in the game loop */
typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_keys;

/* t_texture: wall texture — NO=0, SO=1, WE=2, EA=3 */
typedef struct s_texture
{
	t_img	img;
	int		width;
	int		height;
	char	*path;
}	t_texture;

/* t_wall: per-column wall slice data computed during raycasting */
typedef struct s_wall
{
	int	draw_start;
	int	draw_end;
	int	line_height;
	int	tex_x;
	int	y;
}	t_wall;

/* t_player: camera position, direction vector and FOV plane */
/* Initial orientations: N dir=(0,-1) E dir=(1,0) S dir=(0,1) W dir=(-1,0) */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	room_plane_x;
	double	room_plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		hit_side;
	int		wall_map_x;
	int		wall_map_y;
}	t_player;

/* t_map: 2D grid — 0=floor, 1=wall, 2=door, N/S/E/W=spawn */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

/* t_dda: incremental values for the DDA wall-hit algorithm */
typedef struct s_dda
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
}	t_dda;

/* t_weapon: overlay weapon sprite image */
typedef struct s_weapon
{
	t_img	img;
	int		width;
	int		height;
}	t_weapon;

/* t_game: top-level struct passed by pointer to all functions */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_texture	textures[4];
	t_texture	door_texture;
	t_map		map;
	t_player	player;
	t_keys		keys;
	int			floor_color;
	int			ceiling_color;
	t_weapon	weapon;
	char		**raw_lines;
	int			anim_frame;
}	t_game;

#endif