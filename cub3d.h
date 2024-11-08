
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


char	*read_file(int	fd);
int		safe_atoi(const char *str, int	*result);
t_error	parse_rgb(const char *str, size_t *idx, t_rgb *rgb);
t_error	parse_file(t_input *input, const char *map_path);
t_error	parse_txtre_path(const char *str, size_t *idx, char **txtre_path);
t_error	parse_map(const char *str, size_t *idx, t_map *map);
bool	is_valid_map_char(char c);


void	skip_num(const char *str, size_t *idx);
void	skip_whitespaces(const char *str, size_t *idx);
void	skip_chars(const char *charset, const char *str, size_t *idx);
void	append_char(char *str, char c, size_t n);
size_t	get_line_len(const char *str);
int		safe_atoi(const char *str, int	*result);
void	put_cur_line(int fd, const char *str);
void	put_cur_word(int fd, const char *str);

void	free_input(t_input *input);

#endif // !CUB3D_H
