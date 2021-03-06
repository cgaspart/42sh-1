/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/26 13:28:48 by jjaniec           #+#    #+#             */
/*   Updated: 2018/12/05 17:57:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

/*
** Return pointer to t_env_entry struct w/ corresponding name in self->environ
** if varname contains a '=',
** temporary mask env value by replacing it with a '\0'
*/

t_env_entry		*get_env_var(t_environ *self, char *varname)
{
	t_env_entry	*ptr;
	char		*equal_sign_ptr;

	if (!(self && self->env_entries_list))
		return (NULL);
	ptr = self->env_entries_list;
	if ((equal_sign_ptr = ft_strchr(varname, '=')))
		*equal_sign_ptr = '\0';
	while (ptr && ft_strcmp(ptr->entry, varname) != 61 && \
		*(ptr->ptr_to_pos_in_environ_tab) != varname)
		ptr = ptr->next;
	if (ptr)
	{
		log_debug("Found %s env var w/ data %s", varname, ptr->entry);
		self->last_used_elem = ptr;
	}
	else
		log_error("%s environnement variable not found !", varname);
	if (equal_sign_ptr)
		*equal_sign_ptr = '=';
	return (ptr);
}
