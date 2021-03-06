/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 12:12:54 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/14 21:46:20 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static void	ft_print_cd_err(char *path, int errno_err)
{
	ft_putstr_fd(SH_NAME": ", 2);
	ft_putstr_fd(path, 2);
	if (errno_err == EACCES)
		ft_putstr_fd(": permission denied\n", 2);
	else if (errno_err == ENOENT)
		ft_putstr_fd(": does not exists\n", 2);
	else if (errno_err == ENOTDIR)
		ft_putstr_fd(": not a directory\n", 2);
	else
		exit(MALLOC_ERROR);
}

char		*cd_get_last_path(char *path)
{
	int		i;
	char	*res;
	char	*tmp;

	tmp = cd_clean_last_slash(path);
	i = ft_strlen(tmp);
	while (i != 0 && tmp[i] != '/')
		i--;
	if (i == 0)
	{
		free(tmp);
		return (ft_xstrdup("/"));
	}
	res = ft_xmalloc(sizeof(char) * (i + 2));
	res = ft_strncpy(res, tmp, (i + 2));
	res[i + 1] = '\0';
	free(tmp);
	return (res);
}

char		*cd_clean_last_slash(char *str)
{
	char	*res;

	if (str[0] == '/' && ft_strlen(str) == 1)
		return (ft_xstrdup(str));
	if (str[ft_strlen(str) - 1] == '/')
	{
		res = ft_xmalloc(sizeof(char) * (ft_strlen(str)));
		ft_bzero(res, ft_strlen(str));
		ft_strncpy(res, str, (ft_strlen(str) - 1));
		return (res);
	}
	return (ft_xstrdup(str));
}

static void	set_var_after_cd(t_environ *env, char *cwd)
{
	char *tmp;

	tmp = NULL;
	if (env->get_var(env, "PWD"))
		tmp = env->last_used_elem->val_begin_ptr;
	if (env->get_var(env, "OLDPWD"))
	{
		if (!tmp)
			ft_strncpy(env->last_used_elem->val_begin_ptr,
			cwd, MAX_ENV_ENTRY_LEN - 7);
		else
			ft_strncpy(env->last_used_elem->val_begin_ptr,
			tmp, MAX_ENV_ENTRY_LEN - 7);
	}
	else
		env->add_var(env, "OLDPWD", cwd);
	log_debug("OLDPWD set to |%s|", env->last_used_elem->val_begin_ptr);
}

int			cd_change_dir(t_environ *env, char *path, char *cwd)
{
	if (path && !chdir(path))
	{
		set_var_after_cd(env, cwd);
		return (0);
	}
	else
	{
		log_error("Failed to change cwd to %s", path);
		ft_print_cd_err(path, errno);
		return (1);
	}
}
