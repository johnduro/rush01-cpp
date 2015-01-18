#include "GTKDisplay.hpp"

bool GTKDisplay::leavetrew = false;

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

void				GTKDisplay::initDisplay(std::vector<AModule*>& vect) {
  (void) vect;
  gtk_init(NULL, NULL);

  this->builder = gtk_builder_new ();
  gtk_builder_add_from_file (this->builder, "test.glade", NULL);
  this->window = GTK_WIDGET (gtk_builder_get_object (this->builder, "window"));
  gtk_builder_connect_signals (this->builder, NULL);
  

  button_exit = gtk_builder_get_object (this->builder, "exit");

	//WINDOW	
	/*this->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
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
*/
  	for(unsigned it=0; it < vect.size(); it++){
  		if (vect[it]->getName() == CPU){
  			this->displayCPU(*vect[it]);
  		}else if (vect[it]->getName() == RAM){
  			this->displayRAM(*vect[it]);
  		}else if (vect[it]->getName() == TIME){
        this->displayDateTime(*vect[it]);
      }else if (vect[it]->getName() == HOST){
        this->displayHostUserName(*vect[it]);
      }
  	}
    
    this->signal();

    g_object_unref (G_OBJECT (this->builder));
    gtk_widget_show_all(this->window);
    //gtk_main();
	return;
}

bool        GTKDisplay::updateDisplay(std::vector<AModule*>& datas) {


  for(unsigned it=0; it < datas.size(); it++){
      if (datas[it]->getName() == RAM){
        ModuleRAM* ram = static_cast<ModuleRAM*>(datas[it]);
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->ram_bar), ram->getData().used_mem.second/100);
      }else if (datas[it]->getName() == CPU){
        ModuleCPU* cpu = static_cast<ModuleCPU*>(datas[it]);
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->cpu_bar), cpu->getData().cpu_usage.first/100);
      }else if (datas[it]->getName() == TIME){
        ModuleTime* datetime = static_cast<ModuleTime*>(datas[it]);
        gtk_label_set_text(GTK_LABEL(this->date_time), datetime->getData().c_str());
      }else if (datas[it]->getName() == HOST){
        ModuleName* name = static_cast<ModuleName*>(datas[it]);
        gtk_label_set_text(GTK_LABEL(this->name), name->getData().second.c_str());
      }
    }
  //gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(this->cpu_bar), 0.5);
  
  return true;
}

void  make_leave() {

  GTKDisplay::leavetrew = true;
}

void        GTKDisplay::signal(void){
  g_signal_connect (button_exit, "clicked", G_CALLBACK (make_leave), NULL);
   // g_signal_connect_swapped(G_OBJECT(this->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
 // g_signal_connect(G_OBJECT(filemenu_quit), "activate", G_CALLBACK(gtk_main_quit), this);
  //g_signal_connect(G_OBJECT(window), "key-release-event", G_CALLBACK(testClass), this);
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

void    			GTKDisplay::displayCPU (AModule& datas) {
  (void)datas;
  this->cpu_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    this->cpu_bar = gtk_builder_get_object (this->builder, "progressbar1");
	return;
}

void    			GTKDisplay::displayRAM (AModule& datas) {
	(void)datas;
	this->ram_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
 	  this->ram_bar = gtk_builder_get_object (this->builder, "progressbar2");
	return;
}

void    			GTKDisplay::displayHostUserName(AModule&) {
  this->name = gtk_builder_get_object(this->builder, "user_label");
	return;
}

void    			GTKDisplay::displayOSInfo(AModule&) {
	return;
}

void   		 		GTKDisplay::displayNetworking(AModule&) {
	return;
}

void    			GTKDisplay::displayDateTime(AModule& datas) {
  (void)datas;
  //this->ram_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    this->date_time = gtk_builder_get_object (this->builder, "date_label");
	return;
}