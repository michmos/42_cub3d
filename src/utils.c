
#include "../cub3d.h"

static bool	did_overflow(int sign, int prev_num, int num)
{
	return ((sign == 1 && prev_num > num) || (sign == -1 && prev_num < num));
}

// atoi with error detection.
// returns 0 on success. 
// returns -1 in case of overflow or uncexpected char.
int	safe_atoi(const char *str, int	*result)
{
	size_t	i;
	int		num;
	int		prev;
	int		sign;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		// check for overflow
		prev = num;
		num = (num * 10) + sign * (str[i] - '0');
		if (did_overflow(sign, prev, num))
			return (-1);
		i++;
	}
	if (i == 1 && (str[0] == '+' || str[0] == '-'))
	{
		return (-1);
	}
	*result = num;
	return (0);
}

// returns true if wall found at cor
bool	is_wall(t_cor_bl cor, t_map *map)
{
	return (map->map[cor.y * map->width + cor.x] == WALL);
}

// returns sum ensuring 0 <= sum < 360
t_deg	sum_angle(t_deg angle1, t_deg angle2)
{
	t_deg	sum;

	sum = angle1 + angle2;
	if (sum >= 360)
	{
		sum -= 360;
	}
	else if (sum < 0)
	{
		sum += 360;
	}
	return (sum);
}

// redraw 'img' using 'redraw_foo' that takes a ptr to a new image and a ptr
// to cub3d as arguments to draw the new image.
// returns 0 on success and -1 on failure.
t_error	redraw_img(t_cub3d *cub3d, mlx_image_t **img, t_error (*redraw_foo)(t_cub3d *, mlx_image_t *))
{
	mlx_image_t	*new_img;

	new_img = mlx_new_image(cub3d->mlx, (*img)->width, (*img)->height);
	if (!new_img)
	{
		perror("mlx_new_image failed");
		return (-1);
	}
	if (redraw_foo(cub3d, new_img) == -1)
	{
		mlx_delete_image(cub3d->mlx, *img);
		return (-1);
	}
	if (mlx_image_to_window(cub3d->mlx, new_img, (*img)->instances[0].x, (*img)->instances[0].y) == -1)
	{
		perror("mlx_image_to_window failed");
		mlx_delete_image(cub3d->mlx, *img);
		return (-1);
	}
	mlx_delete_image(cub3d->mlx, *img);
	*img = new_img;
	return (0);
}
