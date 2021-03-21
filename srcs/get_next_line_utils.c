/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legunshi <legunshi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:32:08 by legunshi          #+#    #+#             */
/*   Updated: 2021/03/21 19:35:06 by legunshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strjoin1(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return ((ft_strdup1(s2)));
	if (!(string = (char *)malloc(sizeof(char) * (ft_strlen1(s1) +
		ft_strlen1(s2) + 1))))
		return (NULL);
	while (s1[++i])
		string[i] = s1[i];
	while (s2[j])
		string[i++] = s2[j++];
	string[i] = '\0';
	ft_lstadd_front(&g_rubbish, ft_lstnew((char *)string));
	ft_lstadd_front(&g_rubbish, ft_lstnew((char *)s1));
	ft_lstadd_front(&g_rubbish, ft_lstnew((char *)s2));
	return (string);
}

size_t	ft_strlen1(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		++i;
	}
	return (i);
}

char	*ft_strdup1(const char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char*)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	ft_lstadd_front(&g_rubbish, ft_lstnew((char *)s));
	ft_lstadd_front(&g_rubbish, ft_lstnew((char *)str));
	return (str);
}

char	*ft_strchr1(const char *str, int c)
{
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char*)str);
}
