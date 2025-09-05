/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:37:40 by manufern          #+#    #+#             */
/*   Updated: 2025/08/19 10:47:26 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t  count;
    char    *str;
    size_t  i;

    if (!s)
        return (NULL);
    count = ft_strlen(s);
    if (start >= count || len == 0)
        return (ft_strdup(""));
    if (len > count - start)
        len = count - start;
    str = (char *)malloc(len + 1);
    if (!str)
        return (NULL);
    i = 0;
    while (s[start] && i < len)
    {
        str[i] = s[start];
        start++;
        i++;
    }
    str[i] = '\0';
    return (str);
}
