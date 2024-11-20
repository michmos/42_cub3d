
#ifndef CUB3D_H
# define CUB3D_H

#include <stddef.h>
#include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <assert.h>
# include <math.h>
# include "external_libs/42_libs/ft_libs.h"
# include "external_libs/MLX42/include/MLX42/MLX42.h"
# include "colors.h"

# define USAGE "USAGE: ./cub3d <map>"

# define READ_BUF_SIZE 100	// size of chunk of bytes to read config file
# define FOV 60				// Field of view in degrees
# define BLOCK_SIZE 64		// in pixel
# define PLAYER_SIZE 32		// in pixel

typedef char t_error;
typedef double t_rad;
typedef double t_deg;

typedef enum e_fields
{
	VOID = ' ',
	SPACE = '0',
	WALL = '1',
	PLAYER_EAST = 'E',
	PLAYER_SOUTH = 'S',
	PLAYER_WEST = 'W',
	PLAYER_NORTH = 'N',
	TERMINATOR = 88
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
		u_int8_t a;
	};
	int	rgb;
} t_rgb;

typedef struct s_in_stream
{
	char	*buffer;
	size_t	idx;			// to go through the file
	size_t	crnt_lne_nbr;	// for error messages
} t_in_stream;

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
	u_int32_t	x;
	u_int32_t	y;
} t_vec;

// coordinates in blocks
typedef t_vec t_cor_bl;

// coordinates in pixel
typedef t_vec t_cor_px;

typedef struct	s_view
{
	t_deg		dir_angle;		// current orientation of player (direction)
	size_t		plane_distance; // distance between player and plane
} t_view;

typedef struct	s_window
{
	mlx_t 	*mlx;
	size_t	width;				// in pixel
	size_t	height;				// in pixel
} t_window;

typedef struct s_cub3d
{
	t_window	window;			// mlx window data
	t_map		map;			// map data
	t_view		view;			// viewing field
	t_cor_px	player_px;		// player position in pixel
}	t_cub3d;

typedef enum e_screendimensions
{
	SCREEN_WIDTH = 3840,
	SCREEN_HEIGHT = 2160,
	IMAGE_WIDTH = SCREEN_WIDTH / 2,
	IMAGE_HEIGHT = SCREEN_HEIGHT / 2,
	MINIMAP_MAX_WIDTH = IMAGE_WIDTH / 2,
	MINIMAP_MAX_HEIGHT = IMAGE_HEIGHT / 2
}	t_screendimensions;

typedef struct s_minimap_dims
{
	uint16_t	square;
	uint16_t	height;
	uint16_t	width;
}	t_minimap_dims;

typedef struct s_minimap_help
{
	int			y;
	int			x;
	mlx_image_t	*img;
	mlx_t		*mlx;
}		t_minimap_help;

typedef enum e_minimapcolours
{
	VOID_COLOUR = 0x010000,
	SPACE_COLOUR = 0xF73E3E,
	WALL_COLOUR = 0x3EF776,
	PLAYER_COLOUR = 0xFFFFFF 
}	t_minimapcolours;

typedef enum e_player
{
	MODE_X,
	MODE_Y
}	t_player;

char	*read_file(int	fd);
int		safe_atoi(const char *str, int	*result);
t_error	parse_rgb(t_in_stream *stream, t_rgb *rgb);
t_error	parse_file(t_input *input, const char *map_path);
t_error	parse_txtre_path(t_in_stream *stream, char **txtre_path);
t_error	parse_map(t_in_stream *stream, t_map *map);
bool	is_valid_map_char(char c);


void	skip_num(t_in_stream *stream);
void	skip_whitespaces(t_in_stream *stream);
void	skip_chars(const char *charset, t_in_stream *stream);
char	cur_char(t_in_stream *stream);
char	*cur_ptr(t_in_stream *stream);
void	append_char(char *str, char c, size_t n);
size_t	get_line_len(const char *str);
int		safe_atoi(const char *str, int	*result);
void	put_cur_line(int fd, t_in_stream *stream);
void	put_cur_word(int fd, const char *str);

void	free_input(t_input *input);


void	put_parsing_err(t_in_stream *stream, const char *msg);
void	put_expected_tokens(int input_flags);



// xxxxxxx.c ---------------------------------------------------------------- //

// init_cub3d.c ------------------------------------------------------------- //
t_error	init_cub3d(t_cub3d *cub3d, t_input *input);

// intersec_hit.c ----------------------------------------------------------- //
t_cor_px	get_ver_intersec_hit(t_cor_px pov, t_deg ray_angle, t_map *map);
t_cor_px	get_hor_intersec_hit(t_cor_px pov, t_deg ray_angle, t_map *map);

// ray_distance.c ----------------------------------------------------------- //
double	get_distance_to_wall(t_deg ray_angle, t_cor_px pov, t_deg view_dir, t_map *map);

// conversions.c ------------------------------------------------------------ //
double	rad_to_deg(t_rad radians);
double	deg_to_rad(t_deg degrees);
t_cor_bl	cor_px_to_bl(t_cor_px cor);

// utils.c ------------------------------------------------------------------ //
bool	is_wall(t_cor_bl cor, t_map *map);
t_deg	sum_angle(t_deg angle1, t_deg angle2);
t_error	redraw_img(t_cub3d *cub3d, mlx_image_t **img, t_error (*redraw_foo)(t_cub3d *, mlx_image_t *));
int		safe_atoi(const char *str, int	*result);

#endif // !CUB3D_H
