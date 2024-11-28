
#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <assert.h>
# include <math.h>
# include "external_libs/42_libs/ft_libs.h"
# include "external_libs/MLX42/include/MLX42/MLX42.h"
# include "colors.h"

# define USAGE_ERR "USAGE: ./cub3d <map>"
# define BLOCK_SIZE_ERR "BLOCK_SIZE needs to be a power of two for performance reasons"

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 512
# define READ_BUF_SIZE 100							// size of chunk of bytes to read config file
# define FOV 60										// Field of view in degrees
# define BLOCK_SIZE 64								// in pixel
# define LOG2_BLOCKS_SIZE ((int) log2(BLOCK_SIZE))	// used for bit shifting when div or mult
# define PLAYER_SIZE 32								// in pixel
# define MOVE_DISTANCE 4
# define ROTATE_AMT 2

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

typedef struct s_dvec
{
	double	x;
	double	y;
} t_dvec;

typedef struct s_vec
{
	u_int32_t	x;
	u_int32_t	y;
} t_vec;

// coordinates in blocks
typedef t_vec t_cor_bl;

// coordinates in pixel
typedef t_vec t_cor_px;

// data per ray
typedef struct s_ray
{
	t_deg		angle;				// angle in deg
	t_cor_px	intersec;			// coordinates of intersection with wall block
	bool		vrtcl_intersec;		// type of intersec
	double		ray_distance;		// distance to wall intersec
	double		actual_distance;	// undistorted distance
} t_ray;

// data per vertical
typedef struct s_wall_data
{
	u_int16_t	upper_end;			// upper y coordinate of the wall in pxl
	u_int16_t	scld_height;		// scaled height of the wall in pxl
	u_int16_t	txtre_x_pos;		// offset in texture
	u_int16_t	distance;		// distance to wall
	mlx_image_t	*img;				// wall image (E, N, W or S)
} t_wall_data;

typedef struct	s_view
{
	t_deg		dir_angle;		// current orientation of player (direction)
	size_t		plane_distance; // distance between player and plane
} t_view;

typedef struct	s_walls
{
	mlx_image_t	*east;
	mlx_image_t	*north;
	mlx_image_t	*west;
	mlx_image_t	*south;
} t_walls;

typedef struct s_cub3d
{
	mlx_t		*mlx;			// mlx window
	mlx_image_t	*cur_img;		// TODO: rename to frame maybe
	mlx_image_t	*nxt_img;
	t_walls		wall_imgs;		// wall textures
	t_rgb		floor;
	t_rgb		ceiling;
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

typedef enum e_movedata
{
	COUNTER_CLOCKWISE = 1,
	CLOCKWISE = -1,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
}	t_movedata;

////////////////////////////////////////////////////////////////////////////////
// parsing																	  //
////////////////////////////////////////////////////////////////////////////////

// read_file.c =------------------------------------------------------------- //
char	*read_file(int	fd);

// parse_file.c ------------------------------------------------------------- //
t_error	parse_file(t_input *input, const char *map_path);

// parse_map.c -------------------------------------------------------------- //
t_error	parse_map(t_in_stream *stream, t_map *map);
bool	is_valid_map_char(char c);

// parse_rgb.c -------------------------------------------------------------- //
t_error	parse_rgb(t_in_stream *stream, t_rgb *rgb);

// parse_txtre_path.c ------------------------------------------------------- //
t_error	parse_txtre_path(t_in_stream *stream, char **txtre_path);

// put_errors.c ------------------------------------------------------------- //
void		put_parsing_err(t_in_stream *stream, const char *msg);
void		put_expected_tokens(int input_flags);

// utils.c ------------------------------------------------------------------ //
void	put_cur_line(int fd, t_in_stream *stream);
void	put_cur_word(int fd, const char *str);
void	skip_num(t_in_stream *stream);
void	skip_whitespaces(t_in_stream *stream);
void	skip_chars(const char *charset, t_in_stream *stream);
char	cur_char(t_in_stream *stream);
char	*cur_ptr(t_in_stream *stream);
void	append_char(char *str, char c, size_t n);
size_t	get_line_len(const char *str);
int		safe_atoi(const char *str, int	*result);


////////////////////////////////////////////////////////////////////////////////
// ray_casting																  //
////////////////////////////////////////////////////////////////////////////////

// init_cub3d.c ------------------------------------------------------------- //
t_error		init_cub3d(t_cub3d *cub3d, t_input *input);

// intersec_hit.c ----------------------------------------------------------- //
t_cor_px	get_ver_intersec_hit(t_cor_px pov, t_deg ray_angle, t_map *map);
t_cor_px	get_hor_intersec_hit(t_cor_px pov, t_deg ray_angle, t_map *map);

// ray_distance.c ----------------------------------------------------------- //
void		find_distance_to_wall(t_ray	*ray, t_cor_px pov, t_deg view_angle, t_map *map);

// draw_view.c -------------------------------------------------------------- //
t_error draw_view(t_cub3d *cub3d);

// draw_vertical.c ---------------------------------------------------------- //
void	draw_vertical(t_cub3d *cub3d, u_int16_t frame_x_pos, u_int16_t scaled_height, t_ray *ray);

// conversions.c ------------------------------------------------------------ //
double		rad_to_deg(t_rad radians);
double		deg_to_rad(t_deg degrees);
t_cor_bl	cor_px_to_bl(t_cor_px cor);
t_cor_bl	dvec_to_cor_bl(t_dvec cor);

// shader.c ----------------------------------------------------------------- //
void	shader_pxl(t_rgb *pxl, u_int32_t shader_mltplr);
u_int16_t	get_shader_multplr(u_int32_t distance);

// utils.c ------------------------------------------------------------------ //
bool		is_wall(t_cor_bl cor, t_map *map);
char		get_map_char(t_cor_bl cor, t_map *map);
t_deg		sum_angle(t_deg angle1, t_deg angle2);
int			safe_atoi(const char *str, int	*result);
bool		is_in_map(t_cor_bl cor, t_map *map);
u_int32_t	mult_by_block_size(u_int32_t num);
u_int32_t	div_by_block_size(u_int32_t num);
u_int32_t	get_rgba(int r, int g, int b, int a);
t_rgb		get_pxl_rgba(mlx_image_t *img, int y, int x);

// cleanup.c ---------------------------------------------------------------- //
void	free_input(t_input *input);

#endif // !CUB3D_H
