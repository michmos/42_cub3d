
#include "../../cub3d.h"

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

void	append_char(char *str, char c, size_t n)
{
	size_t	len;
	size_t	i;
	

	len = ft_strlen(str);
	i = 0;
	while (i < n)
	{
		str[len + i] = VOID;
		i++;
	}
}

void	skip_whitespaces(const char *str, size_t *idx)
{
	while (str[*idx] && ft_is_whitespace(str[*idx]))
	{
		(*idx)++;
	}
}

void	skip_chars(const char *charset, const char *str, size_t *idx)
{
	while (str[*idx] && ft_strchr(charset, str[*idx]))
	{
		(*idx)++;
	}
}

void	skip_num(const char *str, size_t *idx)
{
	if (str[*idx] == '-' || str[*idx] == '+')
	{
		(*idx)++;
	}
	while (str[*idx] && ft_isdigit(str[*idx]))
	{
		(*idx)++;
	}
}

void	put_cur_line(int fd, const char *str)
{
	size_t	len;
	char	*nl_ptr;

	nl_ptr = ft_strchr(str, '\n');
	if (nl_ptr)
	{
		len = nl_ptr - str;
	}
	else
	{
		len = ft_strlen(str);
	}
	write(fd, str, len);
	write(fd, "\n", 1);
}

void	put_cur_word(int fd, const char *str)
{
	size_t	len;

	len = ft_wordlen(str);
	write(fd, str, len);
	write(fd, "\n", 1);
}
