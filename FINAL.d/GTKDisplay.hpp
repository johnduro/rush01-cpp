#ifndef GTKDISPLAY_HPP
# define GTKDISPLAY_HPP

# include <gtk/gtk.h>
# include <iostream>
# include <vector>
# include "IMonitorDisplay.hpp"
# include "AModule.hpp"
#include "ModuleTime.hpp"
#include "ModuleCPU.hpp"
#include "ModuleRAM.hpp"
#include "ModuleName.hpp"
#include "ModuleOS.hpp"

class GTKDisplay : public IMonitorDisplay {
	public:
		GTKDisplay(void);
		GTKDisplay(const GTKDisplay&);
		~GTKDisplay(void);

		GTKDisplay&		operator=(const GTKDisplay&);

		void			initDisplay(std::vector<AModule*>&);
		bool			updateDisplay(std::vector<AModule*>&);
		void    		displayCPU (AModule&);
		void    		displayRAM (AModule&);
		void    		displayHostUserName(AModule&);
		void    		displayOSInfo(AModule&);
		void   		 	displayNetworking(AModule&);
		void    		displayDateTime(AModule&);
		void    		displayMenu(void);
		void    		signal(void);

		static bool	leavetrew;

	private:
		GObject *button_exit;
		GObject *date_time;
		GObject *name;

		GtkBuilder *builder;
		GtkWidget *window;
		GtkWidget *grid;
		GtkWidget *menu_box;
		GtkWidget *menu_bar;

		GtkWidget *displaymenu;
		GtkWidget *displaymenu_display;
		GtkWidget *displaymenu_all;
		GtkWidget *displaymenu_cpu;
		GtkWidget *displaymenu_ram;

		GtkWidget *filemenu;
		GtkWidget *filemenu_file;
		GtkWidget *filemenu_quit;

		GtkWidget *cpu_box;
		GtkWidget *cpu_box_label;
	 	GtkWidget *cpu_box_bar;
	 	GtkWidget *cpu_label;
		GObject *cpu_bar;

		GtkWidget *ram_box;
		GObject *ram_bar;
};

#endif // NCURSESDISPLAY_HPP