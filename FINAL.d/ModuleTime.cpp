

#include "ModuleTime.hpp"
#include <time.h>
#include <algorithm>

ModuleTime::ModuleTime(void) : AModule(TIME, 1) {
	return;
}

ModuleTime::ModuleTime(int y) : AModule(TIME, y) {
	return;
}

ModuleTime::ModuleTime(const ModuleTime& src) : AModule(src) {
	return;
}

ModuleTime::~ModuleTime(void) {
	return;
}

ModuleTime&		ModuleTime::operator=(const ModuleTime& src) {
	this->_data = src.getData();
	this->_active = src.isActive();
	this->_name = src.getName();
	return *this;
}

void			ModuleTime::initialize(void) {

	time_t timer;
	struct tm * timeInfo;
	std::string	str;

	time(&timer);
	timeInfo = localtime(&timer);
	str = asctime(timeInfo);
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	this->_data = str;
	return ;
}

void			ModuleTime::update(void) {
	this->initialize();
	return ;
}

std::string		ModuleTime::getData(void) const {
	return this->_data;
}
