/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilelmahi <ilelmahi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 11:00:16 by ilelmahi          #+#    #+#             */
/*   Updated: 2025/07/03 11:02:14 by ilelmahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strndup(const char *s, size_t len)
{
    char    *result;
    size_t  s_len;

    s_len = ft_strlen((char *)s);
    if (len > s_len)
        len = s_len;

    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);
    ft_memcpy(result, s, len);
    result[len] = '\0';
    return (result);
}
