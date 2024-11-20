
#include "../cub3d.h"

static bool	did_overflow(int sign, int prev_num, int num)
{
	return ((sign == 1 && prev_num > num) || (sign == -1 && prev_num < num));
}

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

bool	is_wall(t_cor_bl cor, t_map *map)
{
	return (map->map[cor.y * map->width + cor.x] == WALL);
}
