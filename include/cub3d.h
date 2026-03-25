/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:00:47 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 19:43:48 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* INCLUDES */

# include <mlx.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "structs.h"
# include "defines.h"

/* INITIALIZATION */

/* Allocates t_game, inits mlx, parses file, loads textures */
/* Returns pointer to t_game, NULL on error. File: src/main.c */
t_game			*init_game(char *cub_path);

/* PARSING */

/* Opens and reads the .cub file, validates and stores all elements */
/* Returns 0 on success, 1 on error. File: src/parser/parse_file.c */
int				parse_file(t_game *game, char *cub_path);

/* Extracts texture id and XPM path, checks file existence */
/* Returns 0 on success, 1 on error. File: src/parser/parse_textures.c */
int				parse_texture(t_game *game, char *line);

/* Extracts F/C identifier, validates RGB range 0-255, converts color */
/* Returns 0 on success, 1 on error. File: src/parser/parse_colors.c */
int				parse_color(t_game *game, char *line);

/* Reads lines, builds 2D grid, finds player spawn position */
/* Returns 0 on success, 1 on error. File: src/parser/parse_map.c */
int				parse_map(t_game *game, char **lines);

/* Checks closed map, exactly one player, valid characters */
/* Returns 0 if valid, 1 if invalid. File: src/parser/validate_map.c */
int				validate_map(t_game *game);

/* RAYCASTING */

/* Returns 1 if position (x, y) is walkable, 0 otherwise */
int				is_walkable(t_game *game, double x, double y);

/* Rotates player direction and camera plane by rot_speed */
void			rotate_player(t_game *game, double rot_speed);

/* Moves player forward (direction=1) or backward (direction=-1) */
void			move_forward_back(t_game *game, int direction);

/* Strafes player left (direction=-1) or right (direction=1) */
void			move_strafe(t_game *game, int direction);

/* Reads key flags and applies movement and rotation each frame */
void			move_player(t_game *game);

/* Runs raycasting loop for every screen column */
/* File: src/raycaster/raycaster.c */
void			raycast(t_game *game);

/* Computes deltaDist and sideDist, steps until wall hit */
/* Returns perpendicular wall distance. File: src/raycaster/dda.c */
double			perform_dda(t_game *game, int x);

/* RENDERING */

/* Loads the four wall textures from paths stored in t_game */
int				load_all_textures(t_game *game);

/* Returns pointer to the correct texture for the given side */
t_texture		*get_texture(t_game *game, int side);

/* Returns the color of pixel (tex_x, tex_y) inside a texture */
int				get_tex_pixel(t_texture *tex, int tex_x, int tex_y);

/* Computes the x column to sample on the texture for the hit wall */
int				get_tex_x(t_game *game, t_texture *tex, int side,
					double perp_dist);

/* Loads the weapon overlay image */
int				load_weapon(t_game *game);

/* Draws the weapon sprite over the rendered frame */
void			draw_weapon(t_game *game);

/* Frees all memory allocated for the weapon image */
void			free_weapon(t_game *game);

/* Clears image, runs raycasting, puts image to window */
/* File: src/render/render.c */
int				render(t_game *game);

/* Computes column height, start/end, selects and applies texture */
/* File: src/render/draw_walls.c */
void			draw_wall(t_game *game, int x, double perp_wall_dist,
					int side);

/* Fills top half with ceiling_color, bottom half with floor_color */
/* File: src/render/draw_floor_ceiling.c */
void			draw_floor_ceiling(t_game *game);

/* Loads XPM file and stores pixel address in t_texture */
/* File: src/render/textures.c */
int				load_texture(t_game *game, t_texture *tex, char *path);

/* Computes sprite distance and sorts by distance */
/* File: src/render/sprites.c */
void			render_sprites(t_game *game);

/* EVENTS */

/* Initializes miniLibX and returns mlx pointer */
void			*init_mlx(void);

/* Creates and returns the game window */
void			*create_window(void *mlx);

/* Registers key, window and loop hooks */
void			setup_hooks(t_game *game);

/* Starts the mlx event loop */
void			start_loop(t_game *game);

/* Sets all key flags to 0 */
void			init_keys(t_game *game);

/* Allocates the rendering image buffer */
void			init_image(t_game *game);

/* Frees all memory then exits with exit(0) */
/* Returns 0 (mlx_hook convention). File: src/events/events.c */
int				close_window(t_game *game);

/* Sets the corresponding key flag, closes on ESC */
/* Returns 0. File: src/events/keys.c */
int				key_press(int keycode, t_game *game);

/* Clears the corresponding key flag */
/* Returns 0. File: src/events/keys.c */
int				key_release(int keycode, t_game *game);

/* UTILITIES */

/* Frees each string and the array itself */
void			free_str_array(char **arr);

/* Frees *ptr and sets it to NULL */
void			safe_free(void **ptr);

/* PARSER UTILITIES — File: src/utils/parser_utils.c */

/* Reads all lines from fd into a NULL-terminated array */
char			**read_all_lines(int fd);

/* Returns 1 if line starts with NO/SO/WE/EA/F/C header token */
int				is_header_line(char *line);

/* Skips leading spaces and tabs, returns pointer to first char */
char			*skip_whitespace(char *line);

/* Removes trailing newline from string in-place */
void			trim_newline(char *line);

/* Returns 1 if string contains only decimal digits (no sign) */
int				is_valid_uint_str(char *s);

/* Counts non-NULL elements in a NULL-terminated array */
int				count_str_array(char **arr);

/* Combines r, g, b into 0x00RRGGBB color format */
/* File: src/utils/color_utils.c */
int				create_color(int r, int g, int b);

/* Frees all resources allocated inside t_game */
void			free_game(t_game *game);

/* BONUS */

/* Renders the minimap overlay. File: src/bonus/minimap_bonus.c */
void			render_minimap(t_game *game);

/* Opens or closes the door in front of the player */
/* File: src/bonus/doors_bonus.c */
void			handle_doors(t_game *game);

/* Rotates player based on mouse x movement */
/* File: src/bonus/mouse_bonus.c */
int				mouse_move(int x, int y, t_game *game);

/* Renders animated sprites. File: src/bonus/sprites_anim_bonus.c */
void			render_animated_sprites(t_game *game);

/* Prints error message and exits freeing all resources */
void			error_exit(t_game *game, char *message);

/* Writes color to pixel (x, y) in the image buffer */
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* Loads the door texture from its path */
void			load_door_texture(t_game *game);

/* Clears the image buffer to black */
void			clear_image(t_game *game);

#endif