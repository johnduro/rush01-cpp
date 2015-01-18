
#include "ModuleName.hpp"
#include <unistd.h>

ModuleName::ModuleName(void) : AModule(INFO) {
	return;
}

ModuleName::ModuleName(const ModuleName& src) : AModule(src) {
	return;
}

ModuleName::~ModuleName(void) {
	return;
}

ModuleName&		ModuleName::operator=(const ModuleName& src) {
	this->_data = src.getData();
	this->_active = src.isActive();
	this->_name = src.getName();
	return *this;
}

void			ModuleName::initialize(void) {
  	char hostname[1024];
	char username[100];

	hostname[1023] = '\0';
	gethostname(hostname, 1023);
	getlogin_r(username, 100);
	this->_data.first = hostname;
	this->_data.second = username;
	return;
}

void			ModuleName::update(void) {
	this->initialize();
	return ;
}

std::pair<std::string, std::string>				ModuleName::getData(void) const {
	return this->_data;
}

// # include <iostream>
// int main ()
// {
// 	ModuleName	modN;

// 	modN.initialize();
// 	std::pair<std::string, std::string>		dat;
// 	dat = modN.getData();
// 	std::cout << dat.first << std::endl;
// 	std::cout << dat.second << std::endl;

// 	return 0;
// }
