#include "NcursesDisplay.hpp"

NcursesDisplay::NcursesDisplay(void) {
	return;
}

NcursesDisplay::NcursesDisplay(const NcursesDisplay& src) {
	*this = src;
	return;
}

NcursesDisplay::~NcursesDisplay(void) {
	delete_windows();
	endwin();
	return;
}

NcursesDisplay&		NcursesDisplay::operator=(const NcursesDisplay& src) {
	*this = src;
	return *this;
}

void				NcursesDisplay::initDisplay( std::vector<AModule*>& vectorGlobal) {
	init_ncurses(vectorGlobal);
	updateDisplay(vectorGlobal);
	return;
}

bool				NcursesDisplay::updateDisplay( std::vector<AModule*>& vectorGlobal) {
	int c = getch();
	if (!displayNcurses(vectorGlobal, c))
		return false;
	wrefresh(_HostUserName);
	wrefresh(_Date);
	wrefresh(_OSInfo);
	wrefresh(_CPU);
	wrefresh(_RAM);
	wrefresh(_Network);
	return true;
}

void    			NcursesDisplay::displayCPU ( AModule& mcpu) {
	wclear(_CPU);
	draw_borders(_CPU);
	wattron(_CPU, A_STANDOUT | A_BOLD);
	mvwprintw(_CPU, 0, 1," CPU ");
	wattroff(_CPU, A_STANDOUT | A_BOLD);

	ModuleCPU *m = static_cast<ModuleCPU*> (&mcpu);
	mvwprintw(_CPU, 1,1,"CPU name : %s", m->getData().cpu_name.c_str());
	mvwprintw(_CPU, 2,1,"CPU core : %d", m->getData().nb_core);
	mvwprintw(_CPU, 3,1,"CPU activity : %d%%", static_cast<int>(m->getData().cpu_usage.first));
	for (int f = 0; f < m->getData().cpu_usage.first; f++) {
		if (m->getData().cpu_usage.first < 70) {
			wattron(_CPU, COLOR_PAIR(1));
			mvwprintw(_CPU, 4, (f / 2) + 1 , " ");
			wattroff(_CPU, COLOR_PAIR(1));
		}
		if (m->getData().cpu_usage.first >= 70) {
			wattron(_CPU, COLOR_PAIR(2));
			mvwprintw(_CPU, 4, (f / 2) + 1 , " ");
			wattroff(_CPU, COLOR_PAIR(2));
		}
	}
	wattron(_CPU, COLOR_PAIR(3));
	mvwprintw(_CPU, 4, 1 + 50, "|");
	wattroff(_CPU, COLOR_PAIR(3));

	mvwprintw(_CPU, 3, 65,"CPU inactivity : %d%%", static_cast<int>(m->getData().cpu_usage.second));
	for (int f = 0; f < m->getData().cpu_usage.second; f++) {
		if (m->getData().cpu_usage.second > 30) {
			wattron(_CPU, COLOR_PAIR(1));
			mvwprintw(_CPU, 4, (f / 2) + 65 , " ");
			wattroff(_CPU, COLOR_PAIR(1));
		}
		if (m->getData().cpu_usage.second <= 30) {
			wattron(_CPU, COLOR_PAIR(2));
			mvwprintw(_CPU, 4, (f / 2) + 65 , " ");
			wattroff(_CPU, COLOR_PAIR(2));
		}
	}


	wattron(_CPU, COLOR_PAIR(3));
	mvwprintw(_CPU, 4, 65 + 50, "|");
	wattroff(_CPU, COLOR_PAIR(3));
	return;
}

void    			NcursesDisplay::displayRAM ( AModule& mram) {
	wclear(_RAM);
	draw_borders(_RAM);

	wattron(_RAM, A_STANDOUT | A_BOLD);
	mvwprintw(_RAM, 0, 1," RAM ");
	wattroff(_RAM, A_STANDOUT | A_BOLD);

	ModuleRAM *m = static_cast<ModuleRAM*> (&mram);
	
	mvwprintw(_RAM, 1, 1,"Total Memory : %lld bytes", m->getData().memory.first);
	mvwprintw(_RAM, 2, 1,"Free Memory : %lld bytes", m->getData().memory.second);
	mvwprintw(_RAM, 3, 1,"Used Memory : %lld bytes", m->getData().used_mem.second);
	for (float f = 0; f < m->getData().used_mem.second; f++) {
		if (m->getData().used_mem.second < 70.0) {
			wattron(_RAM, COLOR_PAIR(1));
			mvwprintw(_RAM, 3, (f / 2) + 40 , " ");
			wattroff(_RAM, COLOR_PAIR(1));
		}
		if (m->getData().used_mem.second >= 70.0) {
			wattron(_RAM, COLOR_PAIR(2));
			mvwprintw(_RAM, 3, (f / 2) + 35 , " ");
			wattroff(_RAM, COLOR_PAIR(2));
		}
	}

	wattron(_RAM, COLOR_PAIR(3));
	mvwprintw(_RAM, 3, 30 + 50, "|");
	wattroff(_RAM, COLOR_PAIR(3));
	
	return;
}

void    			NcursesDisplay::displayHostUserName( AModule& mname ) {
	wclear(_HostUserName);
	draw_borders(_HostUserName);
	ModuleName *m = static_cast<ModuleName*>(&mname);
	wattron(_HostUserName, A_STANDOUT | A_BOLD);
	mvwprintw(_HostUserName, 0, 1," Hostname/username ");
	wattroff(_HostUserName, A_STANDOUT | A_BOLD);
	mvwprintw(_HostUserName, 1, 1,"Host : %s", m->getData().first.c_str());
	mvwprintw(_HostUserName, 2, 1,"User : %s", m->getData().second.c_str());
	return;
}

void    			NcursesDisplay::displayOSInfo( AModule& mos) {
	wclear(_OSInfo);
	draw_borders(_OSInfo);
	wattron(_OSInfo, A_STANDOUT | A_BOLD);
	mvwprintw(_OSInfo, 0, 1," OS info ");
	wattroff(_OSInfo, A_STANDOUT | A_BOLD);
	ModuleOS *m = static_cast<ModuleOS*>(&mos);
	mvwprintw(_OSInfo, 1, 1,"OS Info : %s", m->getData()[0].c_str());
	mvwprintw(_OSInfo, 2, 1,"model : %s", m->getData()[1].c_str());
	mvwprintw(_OSInfo, 3, 1,"OS kernel : %s", m->getData()[2].c_str());
	return;
}

void   		 		NcursesDisplay::displayNetworking( AModule& mnet) {
	wclear(_Network);
	draw_borders(_Network);
	wattron(_Network, A_STANDOUT | A_BOLD);
	mvwprintw(_Network, 0, 1," Network throughput ");
	wattroff(_Network, A_STANDOUT | A_BOLD);

	ModuleNet *m = static_cast<ModuleNet*>(&mnet);	
	mvwprintw(_Network, 1, 1, "IP : %s", m->getData().ip.c_str());
	mvwprintw(_Network, 2, 1,"Incoming bytes : %lld", m->getData().net[OCTETS].first.first);
	mvwprintw(_Network, 2, 40,"Incoming bytes/sec : %lld", m->getData().net[OCTETS].first.second);
	mvwprintw(_Network, 3, 1, "Outgoing bytes : %lld", m->getData().net[OCTETS].second.first);
	mvwprintw(_Network, 3, 40, "Outgoing bytes/sec : %lld", m->getData().net[OCTETS].second.second);
	mvwprintw(_Network, 4, 1,"Incoming packets : %lld", m->getData().net[PACKETS].first.first);
	mvwprintw(_Network, 4, 40,"Incoming packets/sec : %lld", m->getData().net[PACKETS].first.second);
	mvwprintw(_Network, 5, 1,"Outgoing packets : %lld", m->getData().net[PACKETS].second.first);
	mvwprintw(_Network, 5, 40,"Outgoing packets/sec : %lld", m->getData().net[PACKETS].second.second);
	return;
}

void    			NcursesDisplay::displayDateTime(AModule& mtime) {
	wclear(_Date);
	draw_borders(_Date);
	wattron(_Date, A_STANDOUT | A_BOLD);
	mvwprintw(_Date, 0, 1," Date/time ");
	wattroff(_Date, A_STANDOUT | A_BOLD);
	ModuleTime *m = static_cast<ModuleTime*>(&mtime);
	mvwprintw(_Date, 1,1,"Time : %s", m->getData().c_str());
	return;
}

void				NcursesDisplay::draw_borders(WINDOW *screen) {
	int x, y, i;
	getmaxyx(screen, y, x);
	// 4 corners
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+");
	// sides
	for (i = 1; i < (y - 1); i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x - 1, "|");
	}
	// top and bottom
	for (i = 1; i < (x - 1); i++) {
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y - 1, i, "-");
	}
}

void				NcursesDisplay::delete_windows() {
	delwin(_HostUserName);
	delwin(_Date);
	delwin(_OSInfo);
	delwin(_CPU);
	delwin(_RAM);
	delwin(_Network);
}

void				NcursesDisplay::init_ncurses( std::vector<AModule*>& vectorGlobal) {
	int parent_y = 0;
	int parent_x;

	initscr();
	timeout(0);
	start_color();
	use_default_colors();
	getmaxyx(stdscr, parent_y, parent_x);
	for (unsigned int i = 0; i < vectorGlobal.size();i++) {
		if (vectorGlobal[i]->getName() == HOST)
			_HostUserName = newwin(DEFAULT_SIZE, parent_x, vectorGlobal[i]->getY() * DEFAULT_SIZE, 0);
		if (vectorGlobal[i]->getName() == TIME)
			_Date = newwin(DEFAULT_SIZE, parent_x, vectorGlobal[i]->getY() * DEFAULT_SIZE, 0);
		if (vectorGlobal[i]->getName() == CPU)
			_CPU = newwin(DEFAULT_SIZE, parent_x, vectorGlobal[i]->getY() * DEFAULT_SIZE, 0);
		if (vectorGlobal[i]->getName() == RAM)
			_RAM = newwin(DEFAULT_SIZE, parent_x, vectorGlobal[i]->getY() * DEFAULT_SIZE, 0);
		if (vectorGlobal[i]->getName() == OS)
			_OSInfo = newwin(DEFAULT_SIZE, parent_x, vectorGlobal[i]->getY() * DEFAULT_SIZE, 0);
		if (vectorGlobal[i]->getName() == NET)
	 		_Network = newwin(DEFAULT_SIZE, parent_x, vectorGlobal[i]->getY() * DEFAULT_SIZE, 0);
	}
	clear();
	noecho();
	cbreak();
	curs_set(0);
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	if (parent_y == 0)
		return;
}

bool				NcursesDisplay::displayNcurses ( std::vector<AModule*>& vectorGlobal, int c) {
	input_win(vectorGlobal, c);
	if (c == 'q' || c == 'Q')
		return false;
	for (unsigned int i = 0; i < vectorGlobal.size(); i++) {
		if (vectorGlobal[i]->getName() == CPU && vectorGlobal[i]->isActive())
			displayCPU(*vectorGlobal[i]);
		if (vectorGlobal[i]->getName() == RAM && vectorGlobal[i]->isActive())
			displayRAM(*vectorGlobal[i]);
		if (vectorGlobal[i]->getName() == HOST && vectorGlobal[i]->isActive())
			displayHostUserName(*vectorGlobal[i]);
		if (vectorGlobal[i]->getName() == OS && vectorGlobal[i]->isActive())
			displayOSInfo(*vectorGlobal[i]);
		if (vectorGlobal[i]->getName() == TIME && vectorGlobal[i]->isActive())
			displayDateTime(*vectorGlobal[i]);
		if (vectorGlobal[i]->getName() == NET && vectorGlobal[i]->isActive())
			displayNetworking(*vectorGlobal[i]);
	}
	return true;
}

void				NcursesDisplay::pop(std::vector<AModule*>& vectorGlobal, char c) {
	int o = 0;
	for (unsigned int i = 0; i < vectorGlobal.size();i++) {
		if (vectorGlobal[i]->getName() == c && vectorGlobal[i]->isActive()) 
			vectorGlobal[i]->activate(false);
		else if (vectorGlobal[i]->getName() == c && !vectorGlobal[i]->isActive())
			vectorGlobal[i]->activate(true);
	}
	for (unsigned int i = 0; i < vectorGlobal.size();i++) {
		if (vectorGlobal[i]->isActive() && vectorGlobal[i]->getName() == HOST) 
			mvwin(_HostUserName, o++ * DEFAULT_SIZE, 0);
		else if (vectorGlobal[i]->isActive() && vectorGlobal[i]->getName() == OS) 
			mvwin(_OSInfo, o++ * DEFAULT_SIZE, 0);
		else if (vectorGlobal[i]->isActive() && vectorGlobal[i]->getName() == CPU) 
			mvwin(_CPU, o++ * DEFAULT_SIZE, 0);
		else if (vectorGlobal[i]->isActive() && vectorGlobal[i]->getName() == TIME) 
			mvwin(_Date, o++ * DEFAULT_SIZE, 0);
		else if (vectorGlobal[i]->isActive() && vectorGlobal[i]->getName() == RAM) 
			mvwin(_RAM, o++ * DEFAULT_SIZE, 0);
		else if (vectorGlobal[i]->isActive() && vectorGlobal[i]->getName() == NET) 
			mvwin(_Network, o++ * DEFAULT_SIZE, 0);
	}
	clear();
}

void				NcursesDisplay::input_win(std::vector<AModule*>& vectorGlobal, int c) {
	if (c == '0')
		pop(vectorGlobal, HOST);
	if (c == '1')
		pop(vectorGlobal, TIME);
	if (c == '2')
		pop(vectorGlobal, OS);
	if (c == '3')
		pop(vectorGlobal, CPU);
	if (c == '4')
		pop(vectorGlobal, RAM);
	if (c == '5')
		pop(vectorGlobal, NET);
}

