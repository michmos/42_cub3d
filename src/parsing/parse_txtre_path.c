
#include "../../cub3d.h"

t_error	parse_txtre_path(const char *str, size_t *idx, char **txtre_path)
{
	size_t	path_len;

	// skip keyword
	(*idx) += 3;
	skip_whitespaces(str, idx);
	// set path
	path_len = ft_wordlen(&str[*idx]);
	*txtre_path = ft_substr(str, *idx, path_len);
	if (!txtre_path)
	{
		perror("malloc");
		return (-1);
	}
	// update index
	(*idx) += path_len;
	return (0);
}

