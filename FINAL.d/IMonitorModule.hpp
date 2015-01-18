// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IMonitorModule.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/18 02:26:19 by mle-roy           #+#    #+#             //
//   Updated: 2015/01/18 02:26:23 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

class IMonitorModule
{
	public:
		virtual void	activate(bool) = 0;
		virtual bool	isActive(void) const = 0;
		virtual void	initialize(void) = 0;
		virtual void	update(void) = 0;
};

#endif // IMONITORMODULE_HPP
