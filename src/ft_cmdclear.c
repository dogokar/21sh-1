/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:22 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:13:22 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		ft_cmdclear(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*elem;

	if (cmd == NULL)
		return ;
	elem = (*cmd)->prev;
	tmp = (*cmd)->next;
	if (!elem)
		*cmd = (*cmd)->next;
	else
	{
		elem->next = tmp;
		tmp->prev = elem;
	}
	ft_memdel((void *)cmd);
}
