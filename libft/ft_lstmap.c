/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:01:00 by sechung           #+#    #+#             */
/*   Updated: 2022/07/08 20:01:02 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*new;
	t_list	*temp;

	result = 0;
	temp = lst;
	while (temp != 0)
	{
		new = ft_lstnew(f(temp -> content));
		if (new == 0)
		{
			ft_lstclear(&result, del);
			return (0);
		}
		ft_lstadd_back(&result, new);
		temp = temp -> next;
	}
	return (result);
}
