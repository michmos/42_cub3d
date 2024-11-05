
#ifndef CUB3D_H
# define CUB3D_H

#include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "external_libs/42_libs/ft_libs.h"
# include "external_libs/MLX42/include/MLX42/MLX42.h"

# define USAGE "USAGE: ./cub3d <map>"
# define READ_BUF_SIZE 100

typedef char t_error;

typedef enum e_fields
{
	VOID = ' ',
	SPACE = '0',
	WALL = '1',
	PLAYER_EAST = 'E',
	PLAYER_SOUTH = 'S',
	PLAYER_WEST = 'W',
	PLAYER_NORTH = 'N',
	TERMINATOR
} t_fields;

typedef enum e_inputs
{
	NO = 1 << 0,
	SO = 1 << 1,
	WE = 1 << 2,
	EA = 1 << 3,
	C  = 1 << 4,
	F  = 1 << 5,
	ALL_FLAGS = NO | SO | WE | EA | C | F
} t_inputs;

typedef union u_rgb
{
	struct
	{
		u_int8_t r;
		u_int8_t g;
		u_int8_t b;
	};
	int	rgb;
} t_rgb;

typedef struct s_map
{
	char	*map;
	size_t	width;
	size_t	height;

} t_map;

typedef struct s_input
{
	t_map	map;
	char	*north_txtre;
	char	*south_txtre;
	char	*west_txtre;
	char	*east_txtre;
	t_rgb	floor;
	t_rgb	ceiling;
}	t_input;

typedef struct s_vec
{
	double	x;
	double	y;
} t_vec;

typedef struct	s_txts
{
	char	*north_txt;
	char	*south_txt;
	char	*west_txt;
	char	*east_txt;
} t_txts;

typedef struct s_cub3d
{
	char	**map;
	t_vec	player_pos;

}	t_cub3d;

typedef enum e_screendimensions
{
	SCREEN_WIDTH = 3840,
	SCREEN_HEIGHT = 2160,
	IMAGE_WIDTH = SCREEN_WIDTH / 2,
	IMAGE_HEIGHT = SCREEN_HEIGHT / 2
}	t_screendimensions;

typedef struct s_minimap
{
	int	rect_height;
	int	rect_width;
	int	y;
	int	x;
}		t_minimap;

typedef enum e_minimapcolours
{
	VOID_COLOUR,
	SPACE_COLOUR = 0xF73E3E,
	WALL_COLOUR = 0x3EF776,
	PLAYER_COLOUR
}	t_minimapcolours;

char	*read_file(int	fd);
int		safe_atoi(const char *str, int	*result);

#endif // !CUB3D_H
