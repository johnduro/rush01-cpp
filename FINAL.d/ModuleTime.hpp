
#ifndef MODULETIME_HPP
# define MODULETIME_HPP

# define HOST	'h'
# define USER	'u'

# include <iostream>
# include <string>
# include "AModule.hpp"

// ** retourne std::string ** //

class ModuleTime : public AModule {
private:
	std::string		_data;

public:
	ModuleTime(void);
	ModuleTime(const ModuleTime&);
	~ModuleTime(void);

	ModuleTime&		operator=(const ModuleTime&);

	void			initialize(void);
	void			update(void);

	std::string		getData(void) const;

};

#endif // MODULETIME_HPP
