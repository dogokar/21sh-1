/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:13:22 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:13:22 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_cmdadd(t_cmd **begin, t_cmd *new)
{
	if (*begin != NULL)
	{
		new->next = *begin;
		(*begin)->prev = new;
	}
	*begin = new;
}
