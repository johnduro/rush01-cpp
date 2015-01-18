#ifndef AMODULE_HPP
# define AMODULE_HPP

# define INFO	'i'

# include <iostream>
# include <map>
# include "IMonitorModule.hpp"

class AModule : public IMonitorModule {
	public:
		AModule(void);
		AModule(char name);
		AModule(const AModule&);
		~AModule(void);

		AModule&						operator=(const AModule&);

		void							activate(bool);
		bool							isActive(void) const;
		virtual void					initialize(void) = 0;
		virtual void					update(void) = 0;

		char							getName(void) const;

	protected:
		char							_name;
		bool							_active;
};

#endif // AMODULE_HPP