#include "GTKDisplay.hpp"
#include "ModuleTime.hpp"
#include "ModuleCPU.hpp"
#include "ModuleRAM.hpp"
#include "ModuleName.hpp"
#include "ModuleOS.hpp"
#include "AModule.hpp"
#include <ncurses.h>
#include <stdlib.h>

int main (void) {
	srand(time(NULL));
	std::vector<AModule*> vectorGlobal;

	AModule		*mtime = new ModuleTime();
	AModule		*mname = new ModuleName();
	AModule		*mcpu = new ModuleCPU();
	AModule		*mram = new ModuleRAM();
	AModule		*mos = new ModuleOS();
	GTKDisplay	disp;

	mtime->initialize();
	mname->initialize();
	mcpu->initialize();
	mram->initialize();
	mos->initialize();
	vectorGlobal.push_back(mtime);
	vectorGlobal.push_back(mname);
	vectorGlobal.push_back(mcpu);
	vectorGlobal.push_back(mram);
	vectorGlobal.push_back(mos);
	disp.initDisplay(vectorGlobal);

	double			i = 0.0;

	while (i <= 100){
		//mram->update();
		disp.updateDisplay(vectorGlobal);
		gtk_main_iteration();

	    //------------------------------------------------ SHOW IN WINDOW -------------------------------------
	    //gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(cpu_bar), i/100);
	    //gtk_main_iteration();
	    //gtk_main();

	    usleep(90000);

	    //std::cout << i/100 << std::endl;
	    //i++;
	  }
	return (0);
}
