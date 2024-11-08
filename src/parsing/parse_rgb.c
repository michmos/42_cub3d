
#include "../../cub3d.h"

static int	skip_separators(const char *str, size_t *idx)
{
	skip_chars(" ", str, idx);
	if (str[*idx] != ',')
	{
		put_err("Error occurred when parsing rgb value: Unexpected token: ");
		put_cur_word(STDERR_FILENO, &str[*idx]);
		put_err("Expected: ,\n");
		return (-1);
	}
	(*idx)++;
	skip_chars(" ", str, idx);
	return (0);
}

static t_error	parse_rgb_component(const char *str, size_t *idx, u_int8_t *comp)
{
	int	temp;

	if (!ft_isdigit(str[*idx]))
	{
		put_err("Error occurred when parsing rgb value: Unexpected token: ");
		put_cur_word(STDERR_FILENO, &str[*idx]);
		put_err("Expected: <num between 0 and 255>\n");
		return (-1);
	}
	else if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("Error occurred when parsing rgb value: Unvalid number\n");
		put_err("Please provide a number between 0 and 255");
		return (-1);
	}
	*comp = temp;
	skip_num(str, idx);
	return (0);
}

t_error	parse_rgb(const char *str, size_t *idx, t_rgb *rgb)
{
	const char	*keyword_pos;

	keyword_pos = &str[*idx];
	// skip keyword
	(*idx) += 2;
	skip_chars(" ", str, idx);
	// parse r
	if (parse_rgb_component(str, idx, &rgb->r) == -1)
	{
		return (-1);
	}
	if (skip_separators(str, idx) == -1)
	{
		return (-1);
	}
	// parse g
	if (parse_rgb_component(str, idx, &rgb->g) == -1)
	{
		return (-1);
	}
	if (skip_separators(str, idx) == -1)
	{
		return (-1);
	}
	// parse b
	if (parse_rgb_component(str, idx,&rgb->b) == -1)
	{
		return (-1);
	}
	return (0);
}
