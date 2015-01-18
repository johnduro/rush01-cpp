#ifndef MODULEOS_HPP
# define MODULEOS_HPP

# define OS		'o'
# define MODEL	'm'
# define KERNEL	'k'

# include <iostream>
# include <vector>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>

# include "AModule.hpp"
struct osver {
    int minor;
    int sub;
} ;
typedef struct osver osxver ;


// ** retourne un vecteur ** //
// ** vec[0] contient la version de l OS ** //
// ** vec[1] contient le model ** //
// ** vec[2] contient le kernel ** //
class ModuleOS : public AModule {
public:
	ModuleOS(void);
	ModuleOS(const ModuleOS&);
	~ModuleOS(void);

	ModuleOS&						operator=(const ModuleOS&);

	void							initialize(void);
	void							update(void);

	std::vector<std::string>		getData(void) const;

private:
	std::vector<std::string>		_data;
	std::string						_getOsName( void );
	char *							_osversionString( void ) ;
	void							_macosx_ver(char *darwinversion, osxver *osxversion );

};

#endif // MODULEOS_HPP
