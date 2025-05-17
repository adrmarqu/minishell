/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:35:31 by adrmarqu          #+#    #+#             */
/*   Updated: 2024/05/23 11:23:12 by adrmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*tmp;
	void	*p;

	if (!lst || !f)
		return (NULL);
	r = NULL;
	while (lst)
	{
		p = (f)(lst->content);
		tmp = ft_lstnew(p);
		if (!tmp)
		{
			ft_lstclear(&r, del);
			free(p);
			return (NULL);
		}
		ft_lstadd_back(&r, tmp);
		lst = lst->next;
	}
	return (r);
}
