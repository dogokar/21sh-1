/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_locale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:22 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:13:22 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_builtin_locale(t_core *core, char **args)
{
	if (args == NULL || args[0] == NULL)
	{
		if (core != NULL && core->set != NULL && core->set->head != NULL)
		{
			ft_print_lst(core->set);
		}
	}
	return (0);
}
