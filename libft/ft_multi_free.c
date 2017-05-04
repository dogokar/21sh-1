/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogokar <dogokar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 21:15:24 by dogokar           #+#    #+#             */
/*   Updated: 2017/05/03 21:15:24 by dogokar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_multi_free(char *s1, char *s2, char *s3, char *s4)
{
	(s1) ? ft_strdel(&s1) : 0;
	(s2) ? ft_strdel(&s2) : 0;
	(s3) ? ft_strdel(&s3) : 0;
	(s4) ? ft_strdel(&s4) : 0;
}
