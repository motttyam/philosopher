/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:25:45 by motttyam          #+#    #+#             */
/*   Updated: 2024/09/05 00:12:37 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int ft_strdigit(char *str)
{
	int len;
	int i;

	if(str == NULL)
		return (0);
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if(ft_isdigit((int)str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

