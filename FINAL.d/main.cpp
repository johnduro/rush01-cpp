#include "NcursesDisplay.hpp"
#include "ModuleTime.hpp"
#include "ModuleCPU.hpp"
#include "ModuleRAM.hpp"
#include "ModuleName.hpp"
#include "ModuleOS.hpp"
#include "AModule.hpp"
#include "ft_timer.hpp"
#include <iostream>
#include <ncurses.h>
#include <stdlib.h>

#define NCURSES 1
#define GTK 	2

int main (void) {
	std::vector<AModule*> 	vectorGlobal;
	ft_timer				timer(1, SECONDS);
	AModule*				mtime = new ModuleTime();
	AModule*				mname = new ModuleName();
	AModule*				mcpu = new ModuleCPU();
	AModule*				mram = new ModuleRAM();
	AModule*				mos = new ModuleOS();
	AModule*				mnet = new ModuleNet();
	NcursesDisplay			Display;

	// if (argc > 1 && strcmp(argv[1], "-gtk") == 0)
	// 	GTKDisplay				Display;
	// else
	// 	NcursesDisplay			Display;
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
	Display.initDisplay(vectorGlobal);
	while (42) {
		if (timer.isTick())
		{
			for (unsigned int i = 0; i < vectorGlobal.size(); i++)
				vectorGlobal[i]->update();
			Display.updateDisplay(vectorGlobal);
		}
	}
	return (0);
}