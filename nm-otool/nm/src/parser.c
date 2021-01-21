#include "nm.h"

static void		fill_pars(t_pars *pars_data, int pos)
{
	int			*ptr;

	ptr = (int *)pars_data;
	*(ptr + pos) = 1;
}

static void		is_arg(char inf)
{
	int				i;
	static char		arg_tab[NB_ARG] = {'r', 'u', 'U', 'n', 'g', 'p', 'j'};

	i = 0;
	while (i < NB_ARG)
	{
		if (inf == arg_tab[i])
			return (i);
		i++;
	}
	return (-1);
}

static int		is_valid(char *arg, t_pars *pars_data)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(arg);
	while (i < len)
	{
		if ((pos = is_arg(arg[i])) == -1)
		{
			pars_data->error = arg[i];
			return (-1);
		}
		else
			fill_pars(pars_data, pos);
		i++;
	}
	return (0);
}

t_pars			parser(char **arg, int nb)
{
	int		i;
	t_pars	pars_data;

	i = 0;
	ft_memset(&pars_data, 0, sizeof(pars_data));
	while (i < nb)
	{
		if (arg[i][0] == '-' && ft_strlen(arg[i]) > 1)
		{
			if (is_valid(arg[i] + 1, &pars_data) == -1)
				return (pars_data);
		}
		else
		{
			pars_data.file_idx = i;
			break ;
		}
		i++;
	}
	return (pars_data);
}
