#ifndef IMONITORDISPLAY_HPP
# define IMONITORDISPLAY_HPP

# include <iostream>
# include <vector>
# include "AModule.hpp"

class IMonitorDisplay {
	public:
		virtual ~IMonitorDisplay(void) {}

		virtual void	initDisplay(std::vector<AModule*>&) = 0;
		virtual bool	updateDisplay(std::vector<AModule*>&) = 0;
		virtual void    displayCPU (AModule&) = 0;
		virtual void    displayRAM (AModule&) = 0;
		virtual void    displayHostUserName(AModule&) = 0;
		virtual void    displayOSInfo(AModule&) = 0;
		virtual void    displayNetworking(AModule&) = 0;
		virtual void    displayDateTime(AModule&) = 0;
};

#endif // IMONITORDISPLAY_HPP
