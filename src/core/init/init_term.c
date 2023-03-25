/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechung <sechung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:48:26 by sechung           #+#    #+#             */
/*   Updated: 2023/03/23 20:18:11 by sechung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tflag(struct termios *t)
{
	t->c_lflag &= ~ECHOCTL;
}

void	init_cc(struct termios *t)
{
	t->c_cc[VDISCARD] = 0xf;
	t->c_cc[VDSUSP] = 0x19;
	t->c_cc[VEOF] = 0x04;
	t->c_cc[VERASE] = 0x7F;
	t->c_cc[VINTR] = 0x3;
	t->c_cc[VKILL] = 0x15;
	t->c_cc[VLNEXT] = 0x16;
	t->c_cc[VMIN] = 1;
	t->c_cc[VQUIT] = 0x1c;
	t->c_cc[VREPRINT] = 0x12;
	t->c_cc[VSTART] = 0x11;
	t->c_cc[VSTATUS] = 0x14;
	t->c_cc[VSTOP] = 0x13;
	t->c_cc[VSUSP] = 0x1a;
	t->c_cc[VWERASE] = 0x17;
	t->c_cc[VTIME] = 0;
}
