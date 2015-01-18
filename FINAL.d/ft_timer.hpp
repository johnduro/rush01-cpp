#ifndef FT_TIMER_HPP
#define FT_TIMER_HPP

#define SECONDS 1
#define MICRO_SECONDS 2

#include <sys/time.h>

class ft_timer
{

private:
	struct timeval		_tick;
	struct timeval		_add;
	ft_timer(void);

	void			_makeNextTick( void );

public:
	ft_timer(unsigned int add, char type);
	~ft_timer(void);
	ft_timer(ft_timer const &);

	ft_timer		&operator=(ft_timer const &);

	bool			isTick( void );
	void			updateTimeAdd( unsigned int add, char type );

};

#endif // ** FT_TIMER ** //
