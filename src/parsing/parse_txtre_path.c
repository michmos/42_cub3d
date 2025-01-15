
#include "../../cub3d.h"

t_error	parse_txtre_path(t_in_stream *stream, char **txtre_path)
{
	size_t		path_len;

	stream->idx += 3;
	skip_chars(" ", stream);
	path_len = ft_wordlen(cur_ptr(stream));
	*txtre_path = ft_substr(stream->buffer, stream->idx, path_len);
	if (!txtre_path)
	{
		perror("malloc");
		return (-1);
	}
	stream->idx += path_len;
	return (0);
}

