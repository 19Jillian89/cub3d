# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/05 21:12:49 by vhacman           #+#    #+#              #
#    Updated: 2026/03/24 19:13:41 by vhacman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                VARIABLES                                     #
# **************************************************************************** #

NAME        = cub3D
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f
MAKEFLAGS   += -s

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
OBJ_DIR_BONUS = obj_bonus
INC_DIR     = include
LIBFT_DIR   = libft

# Library
LIBFT       = $(LIBFT_DIR)/libft.a

# MiniLibX (Linux)
MLX_DIR     = minilibx-linux
MLX         = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

# Sources mandatory (senza file bonus)
SRCS        = $(SRC_DIR)/main.c \
              $(SRC_DIR)/parser/parse_file.c \
              $(SRC_DIR)/parser/parse_map.c \
              $(SRC_DIR)/parser/parse_textures.c \
              $(SRC_DIR)/parser/parse_colors.c \
              $(SRC_DIR)/parser/validate_map.c \
              $(SRC_DIR)/parser/parser_utils/parser_utils.c \
              $(SRC_DIR)/parser/parser_utils/parser_utils2.c \
              $(SRC_DIR)/raycaster/raycaster.c \
              $(SRC_DIR)/raycaster/dda.c \
              $(SRC_DIR)/raycaster/player_move.c \
              $(SRC_DIR)/render/render.c \
              $(SRC_DIR)/render/draw_walls.c \
              $(SRC_DIR)/render/draw_floor_ceiling.c \
              $(SRC_DIR)/render/textures.c \
              $(SRC_DIR)/render/sprites.c \
              $(SRC_DIR)/render/weapon.c \
              $(SRC_DIR)/events/events.c \
              $(SRC_DIR)/events/keys.c \
              $(SRC_DIR)/utils/utils.c \
              $(SRC_DIR)/utils/error.c \
              $(SRC_DIR)/utils/free.c

OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Sources bonus: sostituisce render.c e keys.c con le versioni bonus,
# poi aggiunge i file bonus aggiuntivi.
SRCS_BASE   = $(filter-out $(SRC_DIR)/render/render.c \
              $(SRC_DIR)/events/keys.c \
              $(SRC_DIR)/events/events.c \
              $(SRC_DIR)/parser/validate_map.c, $(SRCS))

SRCS_BONUS  = $(SRCS_BASE) \
              $(SRC_DIR)/bonus/render_bonus.c \
              $(SRC_DIR)/bonus/keys_bonus.c \
              $(SRC_DIR)/bonus/minimap_bonus.c \
              $(SRC_DIR)/bonus/doors_bonus.c \
              $(SRC_DIR)/bonus/sprites_anim_bonus.c \
              $(SRC_DIR)/bonus/events_bonus.c \
              $(SRC_DIR)/bonus/mouse_bonus.c \
              $(SRC_DIR)/bonus/validate_map_bonus.c
              
OBJS_BONUS  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_BONUS)/%.o, $(SRCS_BONUS))

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes \
		-L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled successfully."

# Regola per i .o del mandatory (senza -DBONUS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

# Regola bonus: compila in obj_bonus/ con -DBONUS
bonus: $(LIBFT) $(MLX) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -I$(INC_DIR) -I$(LIBFT_DIR)/includes \
		-L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) with bonuses compiled successfully."

# Regola per i .o del bonus (con -DBONUS, directory separata)
$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -DBONUS -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -c $< -o $@

clean:
	@$(RM) -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "🧽 Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "💀 $(NAME) and libft removed."

re: fclean all

.PHONY: all bonus clean fclean re