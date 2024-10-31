
#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "external_libs/42_libs/ft_libs.h"
# include "external_libs/MLX42/include/MLX42/MLX42.h"

# define USAGE "USAGE: ./cub3d <map>"
# define READ_BUF_SIZE 100

typedef enum e_fields
{
	VOID,
	SPACE,
	WALL,
	PLAYER_EAST,
	PLAYER_SOUTH,
	PLAYER_WEST,
	PLAYER_NORTH,
	TERMINATOR
} t_fields;

typedef union u_rgba
{
	struct
	{
		char	r;
		char	g;
		char	b;
		char	a;
	};
	int	rgba;
} t_rgba;

typedef struct s_input
{
	int		**map;
	char	*north_txt;
	char	*south_txt;
	char	*west_txt;
	char	*east_txt;
	t_rgba	floor;
	t_rgba	ceiling;
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
	int		**map;
	t_vec	player_pos;

}	t_cub3d;


char	*read_file(int	fd);

#endif // !CUB3D_H
