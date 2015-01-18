#include "GTKDisplay.hpp"

GTKDisplay::GTKDisplay(void) {
	return;
}

GTKDisplay::GTKDisplay(const GTKDisplay& src) {
	*this = src;
	return;
}

GTKDisplay::~GTKDisplay(void) {
	return;
}

GTKDisplay&		GTKDisplay::operator=(const GTKDisplay& src) {
	*this = src;
	return *this;
}

void				GTKDisplay::fdisplaymenu_ram(GtkWidget *widget){
	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))) {
		gtk_widget_show(this->ram_box);
	} else {
		gtk_widget_hide(this->ram_box);
	}
}

void				GTKDisplay::fdisplaymenu_cpu(GtkWidget *widget)
{
  if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))) {
  	gtk_widget_show(this->cpu_box);
  } else {
    gtk_widget_hide(this->cpu_box);
  }
}


void				GTKDisplay::initDisplay(std::vector<AModule*>& vect) {
	(void)vect;
	//WINDOW
	gtk_init(NULL, NULL);
	this->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(this->window), GTK_WIN_POS_CENTER);
  	gtk_window_set_title (GTK_WINDOW (this->window), "Monitor");
  	gtk_window_set_default_size(GTK_WINDOW (this->window), 500, 500);

  	//GRID
  	this->grid = gtk_grid_new();
  	gtk_grid_insert_row(GTK_GRID(this->grid), 10);
  	gtk_grid_insert_column(GTK_GRID(this->grid), 10);
  	gtk_grid_set_column_spacing(GTK_GRID(this->grid), 10);
  	gtk_grid_set_row_spacing(GTK_GRID(this->grid), 10);

  	//MENU
  	this->displayMenu();

  	for(unsigned it=0; it < vect.size(); it++){
  		if (vect[it]->getName() == CPU){
  			this->displayCPU(*vect[it]);
  		}else if (vect[it]->getName() == RAM){
  			this->displayRAM(*vect[it]);
  		}
  	}

    this->signal();

    gtk_widget_show_all(this->window);
	return;
}

void    			GTKDisplay::displayMenu(void){
	this->menu_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  	this->menu_bar = gtk_menu_bar_new();

  	//menu file
  	this->filemenu = gtk_menu_new();
  	this->filemenu_file = gtk_menu_item_new_with_label("File");
  	this->filemenu_quit = gtk_menu_item_new_with_label("Quit");
  	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->filemenu_file), this->filemenu);
  	gtk_menu_shell_append(GTK_MENU_SHELL(this->filemenu), this->filemenu_quit);

  	//menu display
  	this->displaymenu = gtk_menu_new(); //creer un nouveau menu
  	this->displaymenu_display = gtk_menu_item_new_with_label("Display"); //Defini le nom du menu
  	gtk_menu_item_set_submenu(GTK_MENU_ITEM(this->displaymenu_display), this->displaymenu); //Set le nom du menu

  	this->displaymenu_all = gtk_menu_item_new_with_label("All"); //Creer un item du menu
  	this->displaymenu_cpu = gtk_check_button_new_with_label("Cpu"); //Creer une checkbox du menu
  	this->displaymenu_ram = gtk_check_button_new_with_label("Ram"); //Creer une checkbox du menu


  	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(this->displaymenu_cpu), TRUE); //Default checkbox
  	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(this->displaymenu_ram), TRUE); //Default checkbox

  	gtk_menu_shell_append(GTK_MENU_SHELL(this->displaymenu), this->displaymenu_all);
  	gtk_menu_shell_append(GTK_MENU_SHELL(this->displaymenu), this->displaymenu_cpu);
  	gtk_menu_shell_append(GTK_MENU_SHELL(this->displaymenu), this->displaymenu_ram);

  	//Ajout dans la menubar
  	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_bar), this->filemenu_file);
  	gtk_menu_shell_append(GTK_MENU_SHELL(this->menu_bar), this->displaymenu_display);
  	gtk_box_pack_start(GTK_BOX(this->menu_box), this->menu_bar, FALSE, FALSE, 3);
  	gtk_grid_attach (GTK_GRID (grid), this->menu_box, 0, 0, 1, 1); //width - height - sizeW - sizeHeight

  	gtk_container_add(GTK_CONTAINER(window), grid);

	return;
}

void				GTKDisplay::signal(void){
	//g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 	//g_signal_connect(G_OBJECT(filemenu_quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
 	//g_signal_connect(G_OBJECT(displaymenu_cpu), "clicked", G_CALLBACK(fdisplaymenu_cpu), NULL);
 	//g_signal_connect(G_OBJECT(displaymenu_ram), "clicked", G_CALLBACK(fdisplaymenu_ram), NULL);
 	//g_signal_connect(G_OBJECT(window), "key-release-event", G_CALLBACK(key_event), NULL);
 	gtk_widget_show_all(window);
}

void				GTKDisplay::updateDisplay(std::vector<AModule*>& datas) {

	for(unsigned it=0; it < datas.size(); it++){
  		if (datas[it]->getName() == RAM){
  			ModuleRAM* ram = static_cast<ModuleRAM*>(datas[it]);
				float r = ((float)(8589934592 - ram->getData().memory.second) /(float)8589934592);
				std::cout << ram->getData().used_mem.first<< "   "<< ram->getData().memory.second << "     " << ram->getData().memory.first << "  "<< r << "r && 1-r "<< 1 - r <<std::endl;
				ram->update();
				gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->ram_bar2), 1 - r);
				gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->ram_bar), r);
			}
			if (datas[it]->getName() == CPU){
					ModuleCPU* cpu = static_cast<ModuleCPU*>(datas[it]);
					cpu->update();
					gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->cpu_bar), (cpu->getData().cpu_usage.first)/ 100);
  		}
  	}
	//gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->cpu_bar), 0.5);

	return;
}

void    			GTKDisplay::displayCPU (AModule& datas) {


	ModuleCPU *m = static_cast<ModuleCPU*> (&datas);
	std::string name = m->getData().cpu_name;
	this->cpu_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	this->cpu_box_label = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	this->cpu_box_label2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	this->cpu_box_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

	gtk_grid_attach (GTK_GRID (this->grid), this->cpu_box, 0, 1, 2, 2);
//	gtk_grid_attach (GTK_GRID (this->grid), this->cpu_box, 2, 1, 5, 5);
	gtk_box_pack_start(GTK_BOX(cpu_box), this->cpu_box_label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(cpu_box), this->cpu_box_label2, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(cpu_box), this->cpu_box_bar, FALSE, FALSE, 0);

	//gtk_container_add(GTK_CONTAINER(cpu_box), cpu_box_label);
	//gtk_container_add(GTK_CONTAINER(cpu_box), cpu_box_bar);

this->cpu_label = gtk_label_new(&(m->getData().cpu_name)[0]);
this->cpu_label2 = gtk_label_new("/ Cores = 4 / ");
this->cpu_bar = gtk_progress_bar_new();
  	//gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->cpu_bar), 0.5);
 	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(this->cpu_bar), TRUE);
 	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(this->cpu_bar), "USED CPU");

 gtk_box_pack_start(GTK_BOX(this->cpu_box_label), this->cpu_label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(this->cpu_box_label2), this->cpu_label2, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(this->cpu_box_bar), this->cpu_bar, FALSE, FALSE, 0);
	return;
}

void    			GTKDisplay::displayRAM (AModule& datas) {
	ModuleRAM *m = static_cast<ModuleRAM*> (&datas);
	(void)m;
	this->ram_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
 	this->ram_bar = gtk_progress_bar_new();
	this->ram_bar2 = gtk_progress_bar_new();
	this->ram_box_label = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
 	//gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->ram_bar), datas.used_mem.second);
 gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(this->ram_bar), TRUE);
gtk_progress_bar_set_text(GTK_PROGRESS_BAR(this->ram_bar), "RAM USED");
	gtk_grid_attach (GTK_GRID (this->grid), this->ram_box, 0, 4, 1, 2); //width - height - sizeW - sizeHeight
	gtk_box_pack_start(GTK_BOX(this->ram_box), this->ram_box_label, FALSE, FALSE, 4);

this->cpu_label2 = gtk_label_new("Total Ram: 8G");

	gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(this->ram_bar2), TRUE);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(this->ram_bar2), "RAM FREE");

gtk_box_pack_start(GTK_BOX(this->ram_box), this->ram_bar2, FALSE, FALSE, 3);
gtk_box_pack_start(GTK_BOX(this->ram_box), this->ram_bar, FALSE, FALSE, 3);
	return;
}

void    			GTKDisplay::displayHostUserName(AModule&) {
	return;
}

void    			GTKDisplay::displayOSInfo(AModule&) {
	return;
}

void   		 		GTKDisplay::displayNetworking(AModule&) {
	return;
}

void    			GTKDisplay::displayDateTime(AModule&) {
	return;
}
