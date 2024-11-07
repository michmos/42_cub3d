
#include "../../cub3d.h"

t_error	parse_rgb(const char *str, size_t *idx, t_rgb *rgb)
{
	int	temp;

	temp = 0;
	// skip keyword
	(*idx) += 2;
	skip_whitespaces(str, idx);
	// parse r
	if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("wrong nb"); // TODO: add correct msg (overflow or just - or +)
		return (-1);
	}
	rgb->r = temp;
	skip_num(str, idx);
	skip_whitespaces(str, idx);
	if (str[*idx] != ',')
	{
		put_err("syntax error"); // TODO: add correct msg (Syntax error)
		return (-1);
	}
	(*idx)++;

	// parse g
	skip_whitespaces(str, idx);
	if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("wrong number"); // TODO: add correct msg (overflow or just - or +)
		return (-1);
	}
	rgb->g = temp;
	skip_num(str, idx);
	skip_whitespaces(str, idx);
	if (str[*idx] != ',')
	{
		put_err("syntax error"); // TODO: add correct msg (Syntax error)
		return (-1);
	}
	(*idx)++;

	// parse b
	skip_whitespaces(str, idx);
	if (safe_atoi(&str[*idx], &temp) == -1 || temp < 0 || temp > 255)
	{
		put_err("wrong number"); // TODO: add correct msg (overflow or just - or +)
		return (-1);
	}
	rgb->b = temp;
	skip_num(str, idx);
	return (0);
}
