#include "NcursesDisplay.hpp"
#include "GTKDisplay.hpp"
#include "ModuleTime.hpp"
#include "ModuleCPU.hpp"
#include "ModuleRAM.hpp"
#include "ModuleName.hpp"
#include "ModuleOS.hpp"
#include "AModule.hpp"
#include "ft_timer.hpp"
#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <stdlib.h>

#define NCURSES 1
#define GTK 	2

int main (int argc, char **argv) {
	std::vector<AModule*> 	vectorGlobal;
	std::string				line;
	char					option = NCURSES;
	int						i = 0;
	ft_timer				timer(1, SECONDS);
	AModule*				mtime = new ModuleTime();
	AModule*				mname = new ModuleName();
	AModule*				mcpu = new ModuleCPU();
	AModule*				mram = new ModuleRAM();
	AModule*				mos = new ModuleOS();
	AModule*				mnet = new ModuleNet();
	GTKDisplay				gtkDisplay;
	NcursesDisplay			nDisplay;

	if (argc > 1 && strcmp(argv[1], "-gtk") == 0)
		option = GTK;
	mtime->initialize();
	mname->initialize();
	mcpu->initialize();
	mram->initialize();
	mos->initialize();
	mnet->initialize();
	vectorGlobal.push_back(mtime);
	vectorGlobal.push_back(mname);
	vectorGlobal.push_back(mcpu);
	vectorGlobal.push_back(mram);
	vectorGlobal.push_back(mos);
	vectorGlobal.push_back(mnet);
	std::ifstream	ifs("display.config");
	if (ifs)
	{
		while (std::getline(ifs, line) && i < 6)
		{
			if (line.empty())
				continue;
			for (unsigned int j = 0; j < vectorGlobal.size(); j++)
			{
				if (vectorGlobal[j]->getName() == line.at(0) && !vectorGlobal[j]->isActive())
				{
					vectorGlobal[j]->setY(i);
					vectorGlobal[j]->activate(true);
				}
			}
			i++;
		}
	}
	ifs.close();

	if (option == GTK)
		gtkDisplay.initDisplay(vectorGlobal);
	else
		nDisplay.initDisplay(vectorGlobal);

	while (42) {
		if ((GTKDisplay::leavetrew == true) || !gtk_main_iteration_do(FALSE))
			exit(0);
		if (timer.isTick())
		{
			for (unsigned int i = 0; i < vectorGlobal.size(); i++)
				vectorGlobal[i]->update();
			if (option == GTK)
				gtkDisplay.updateDisplay(vectorGlobal);
			else
			{
				if (!nDisplay.updateDisplay(vectorGlobal))
					break;
			}
		}
	}

	delete mtime;
	delete mname;
	delete mcpu;
	delete mram;
	delete mos;
	delete mnet;

	return (0);
}