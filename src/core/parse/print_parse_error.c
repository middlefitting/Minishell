/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parse_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:53:55 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:19:02 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parse_error(char *msg)
{
	ft_putstr_fd("minishell: parse error by ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	print_syntax_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("'\n", 2);
}
