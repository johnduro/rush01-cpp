#ifndef AMODULE_HPP
# define AMODULE_HPP

# define HOST	'h'
# define TIME	't'
# define OS		'o'
# define CPU	'c'
# define RAM	'r'
# define NET	'n'

# include <iostream>
# include <map>
# include "IMonitorModule.hpp"

class AModule : public IMonitorModule {
	public:
		AModule(void);
		AModule(char name, int y);
		AModule(const AModule&);
		~AModule(void);

		AModule&						operator=(const AModule&);

		void							activate(bool);
		bool							isActive(void) const;
		virtual void					initialize(void) = 0;
		virtual void					update(void) = 0;

		char							getName(void) const;
		int								getY(void) const;
		int								getX(void) const;
		void							setY(int const &);
		void							setX(int const &);

	protected:
		char							_name;
		bool							_active;
		int								_y;
		int								_x;
};

#endif // AMODULE_HPP