/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:29:38 by mmoser        #+#    #+#                 */
/*   Updated: 2025/01/20 10:31:46 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// char is allowed as part of map
bool	is_valid_map_char(char c)
{
	return (c == VOID || c == SPACE || c == WALL || c == PLAYER_SOUTH
		|| c == PLAYER_EAST || c == PLAYER_WEST || c == PLAYER_NORTH);
}

static bool	did_overflow(int sign, int prev_num, int num)
{
	return ((sign == 1 && prev_num > num) || (sign == -1 && prev_num < num));
}

// atoi with error detection.
// returns 0 on success.
// returns -1 in case of overflow or uncexpected char.
int	safe_atoi(const char *str, int *result)
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
		prev = num;
		num = (num * 10) + sign * (str[i] - '0');
		if (did_overflow(sign, prev, num))
			return (-1);
		i++;
	}
	if (i == 1 && (str[0] == '+' || str[0] == '-'))
		return (-1);
	return (*result = num, 0);
}

// get len until new line character
size_t	get_line_len(const char *str)
{
	char	*nwln_ptr;

	nwln_ptr = ft_strchr(str, '\n');
	if (nwln_ptr)
	{
		return (nwln_ptr - str);
	}
	else
	{
		return (ft_strlen(str));
	}
}

// append char at the end of string.
// no reallocation - assuming enough space
void	append_char(char *str, char c, size_t n)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	while (i < n)
	{
		str[len + i] = c;
		i++;
	}
}
