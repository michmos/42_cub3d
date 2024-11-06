
#include "../cub3d.h"

int	main(int argc, char *argv[])
{
	t_cub3d	cub3d;
	t_input	input;

	if (argc != 2)
	{
		put_err(USAGE);
		return (-1);
	}
	ft_bzero(&input, sizeof(t_input));
	if (parse_file(&input, argv[1]) == -1)
	{
		return (-1);
	}
	return (0);
}

