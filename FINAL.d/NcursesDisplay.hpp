#ifndef NCURSESDISPLAY_HPP
# define NCURSESDISPLAY_HPP
# define DEFAULT_SIZE 7

# include <iostream>
# include <vector>
# include <ncurses.h>
# include "IMonitorDisplay.hpp"
# include "AModule.hpp"
# include "ModuleTime.hpp"
# include "ModuleName.hpp"
# include "ModuleCPU.hpp"
# include "ModuleRAM.hpp"
# include "ModuleOS.hpp"
#include "ModuleNet.hpp"


class NcursesDisplay : public IMonitorDisplay {
	public:
		NcursesDisplay(void);
		NcursesDisplay(const NcursesDisplay&);
		~NcursesDisplay(void);

		NcursesDisplay&		operator=(const NcursesDisplay&);

		void				initDisplay(std::vector<AModule*>&);
		bool				updateDisplay(std::vector<AModule*>&);
		void    			displayCPU (AModule&);
		void    			displayRAM (AModule&);
		void    			displayHostUserName(AModule&);
		void    			displayOSInfo(AModule&);
		void   		 		displayNetworking(AModule&);
		void    			displayDateTime(AModule&);

		void				draw_borders(WINDOW *screen);
		void				delete_windows();
		void				init_ncurses(std::vector<AModule*>&);
		bool				displayNcurses (std::vector<AModule*>&, int c);

		void				input_win(std::vector<AModule*>&, int c);
		int					findLastPos(std::vector<AModule*>&);
		int					checkModule(std::vector<AModule*>&, AModule&, char c);
		void				pop(std::vector<AModule*>&, char c);

	private:
		WINDOW				*_HostUserName;
		WINDOW				*_OSInfo;
		WINDOW				*_Date;
		WINDOW				*_CPU;
		WINDOW				*_RAM;
		WINDOW				*_Network;
};


#endif // NCURSESDISPLAY_HPP