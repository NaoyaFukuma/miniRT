/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_put_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukuma <nfukuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:56:52 by nfukuma           #+#    #+#             */
/*   Updated: 2023/01/17 16:02:33 by nfukuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PUT_ERROR_H
# define RT_PUT_ERROR_H

void	rt_put_error_exit(const char *msg);
void	rt_perror_exit(const char *msg);

#endif
