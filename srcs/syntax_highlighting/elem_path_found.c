/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_path_found.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 21:24:19 by jjaniec           #+#    #+#             */
/*   Updated: 2018/08/25 08:39:09 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

int		elem_path_found(struct stat *elem_stats, char *lexeme_data, char **env, int item_nb)
{
	char		**paths;
	char		*tmp;

	if (ft_strchr(lexeme_data, '/') || item_nb > 0)
	{
		if (access(lexeme_data, F_OK) == 0)
			return (1);
	}
	else
	{
		paths = get_path(get_env("PATH", (const char**)env));
		if ((tmp = isin_path(paths, lexeme_data)))
		{
			lstat(tmp, elem_stats);
			return (1);
		}
		ft_strdel(&tmp);
	}
	return (0);
}