#include "ft_timer.hpp"

ft_timer::ft_timer(void)
{
}

ft_timer::ft_timer(unsigned int add, char type)
{
	this->_tick.tv_sec = 0;
	this->_tick.tv_usec = 0;
	this->_add.tv_sec = 0;
	this->_add.tv_usec = 0;
	this->updateTimeAdd( add, type );
	this->_makeNextTick();
}

ft_timer::~ft_timer(void)
{
}

ft_timer::ft_timer(ft_timer const &src)
{
	*this = src;
}

ft_timer		&ft_timer::operator=(ft_timer const &src)
{
	this->_tick.tv_sec = src._tick.tv_sec;
	this->_tick.tv_usec = src._tick.tv_usec;
	this->_add.tv_sec = src._add.tv_sec;
	this->_add.tv_usec = src._add.tv_usec;
	return *this;
}


bool			ft_timer::isTick( void )
{
	struct timeval		time;
	bool				ret = false ;

	gettimeofday(&time, NULL);
	if (time.tv_sec == this->_tick.tv_sec)
	{
		if (time.tv_usec > this->_tick.tv_usec)
			ret = true;
	}
	else if (time.tv_sec > this->_tick.tv_sec)
		ret = true;
	if (ret == true)
		this->_makeNextTick();
	return (ret);
}

void			ft_timer::updateTimeAdd( unsigned int add, char type )
{
	if (type == SECONDS)
		this->_add.tv_sec = add;
	else if (type == MICRO_SECONDS)
		this->_add.tv_sec = add;
}

void			ft_timer::_makeNextTick( void )
{
	struct timeval		cur;

	gettimeofday(&cur, NULL);
	timeradd(&cur, &(this->_add), &(this->_tick));
}
