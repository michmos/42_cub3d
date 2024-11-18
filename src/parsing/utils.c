
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

char	cur_char(t_in_stream *stream)
{
	return (stream->buffer[stream->idx]);
}

char	*cur_ptr(t_in_stream *stream)
{
	return (&stream->buffer[stream->idx]);
}

void	skip_whitespaces(t_in_stream *stream)
{
	while (cur_char(stream) && ft_is_whitespace(cur_char(stream)))
	{
		if (cur_char(stream) == '\n')
		{
			stream->crnt_lne_nbr++;
		}
		stream->idx++;
	}
}

void	skip_chars(const char *charset, t_in_stream *stream)
{
	while (cur_char(stream) && ft_strchr(charset, cur_char(stream)))
	{
		if (cur_char(stream) == '\n')
		{
			stream->crnt_lne_nbr++;
		}
		stream->idx++;
	}
}

void	skip_num(t_in_stream *stream)
{
	if (cur_char(stream) == '-' || cur_char(stream) == '+')
	{
		stream->idx++;
	}
	while (cur_char(stream) && ft_isdigit(cur_char(stream)))
	{
		stream->idx++;
	}
}

void	put_cur_line(int fd, t_in_stream *stream)
{
	size_t	len;
	char	*nl_ptr;
	size_t	i;

	// set i to beginning of line
	i = stream->idx;
	if (stream->crnt_lne_nbr > 1)
	{
		while (stream->buffer[i] != '\n')
		{
			i--;
		}
		i++;
	}
	else
	{
		i = 0;
	}
	// get output len - either until nl or end
	nl_ptr = ft_strchr(&stream->buffer[i], '\n');
	if (nl_ptr)
	{
		len = nl_ptr - &stream->buffer[i];
	}
	else
	{
		len = ft_strlen(&stream->buffer[i]);
	}
	write(fd, &stream->buffer[i], len);
	write(fd, "\n", 1);
}

void	put_cur_word(int fd, const char *str)
{
	size_t	len;

	len = ft_wordlen(str);
	write(fd, str, len);
	write(fd, "\n", 1);
}
