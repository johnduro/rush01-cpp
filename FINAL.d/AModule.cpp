#include "AModule.hpp"

AModule::AModule(void) {
	return;
}

AModule::AModule(char name, int y) : _name(name), _active(true), _y(y) {
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

int			AModule::getY(void) const {
	return this->_y;
}

int			AModule::getX(void) const {
	return this->_x;
}

void		AModule::setY(int const &y) {
	_y = y;
}

void		AModule::setX(int const &x) {
	_x = x;
}