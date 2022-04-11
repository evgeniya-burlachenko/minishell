/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_array.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 10:20:40 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 12:15:09 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/z_array.h"

int	z_array_init(t_z_array *a)
{
	(*a).size = 0;
	(*a).elem = NULL;
	(*a).elem = z_array_utls_ft_alloc(sizeof(char **));
	if (NULL == (*a).elem)
	{
		(*a).status = 1;
		return (1);
	}
	(*a).status = 0;
	return (0);
}

int	z_array_append(t_z_array *a, char *str)
{
	char		**temp;
	char		*tstr;
	int			i;

	if ((*a).status != 0)
		return (1);
	i = 0;
	tstr = z_array_utls_ft_strdup(str);
	if (NULL == tstr)
		return (1);
	temp = z_array_utls_ft_alloc(sizeof(char *) * ((*a).size + 1));
	if (NULL == temp)
	{
		free(tstr);
		return (1);
	}
	*(temp + (*a).size) = tstr;
	i = (*a).size;
	while (i-- != 0)
		temp[i] = (*a).elem[i];
	free((*a).elem);
	(*a).elem = temp;
	(*a).size += 1;
	return (0);
}

int	z_array_remove(t_z_array *a, size_t index)
{
	size_t	i;
	char	*backup;

	if ((*a).status != 0)
		return (1);
	if (index + 1 > (*a).size || (*a).size == 0)
		return (1);
	backup = (*a).elem[index];
	if (index + 1 != (*a).size)
	{
		i = index;
		while (i < (*a).size - 1)
		{
			(*a).elem[i] = (*a).elem[i + 1];
			i++;
		}
	}
	(*a).size -= 1;
	free(backup);
	(*a).elem[(*a).size] = NULL;
	return (0);
}

int	z_array_null_terminate(t_z_array *a)
{
	if ((*a).status != 0)
		return (1);
	z_array_append(a, "N");
	z_array_remove(a, (*a).size - 1);
	return (0);
}
