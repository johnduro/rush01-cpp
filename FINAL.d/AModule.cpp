#include "AModule.hpp"

AModule::AModule(void) {
	return;
}

AModule::AModule(char name) : _name(name), _active(false) {
	return;
}

AModule::AModule(const AModule& src) {
	*this = src;
	return;
}

AModule::~AModule(void) {
	return;
}

AModule&	AModule::operator=(const AModule& src) {
	this->_active = src.isActive();
	return *this;
}

void		AModule::activate(bool active) {
	this->_active = active;
	return;
}

bool		AModule::isActive(void) const {
	return this->_active;
}

char		AModule::getName(void) const {
	return this->_name;
}
