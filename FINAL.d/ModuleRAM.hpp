#ifndef MODULERAM_HPP
# define MODULERAM_HPP

# include <iostream>
# include <map>
# include <utility>
# include "AModule.hpp"


// ** retourne une struct data ** //
// ** data.memory.first donne la memoire totale (long long) ** //
// ** data.memory.second donne la memoire libre (long long) ** //
// ** data.used_mem.first donne la memoire utilisee (long long) ** //
// ** data.used_mem.second donne le pourcentage de memoire utilisee (float) ** //

class ModuleRAM : public AModule
{
public:
	struct Data {
		std::pair<long long , long long>	memory;
		std::pair<long long , float>		used_mem;
	};

	ModuleRAM(void);
	ModuleRAM(const ModuleRAM&);
	~ModuleRAM(void);

	ModuleRAM&		operator=(const ModuleRAM&);

	void			initialize(void);
	void			update(void);

	Data			getData(void) const;

private:
	Data			_data;

};

#endif // MODULERAM_HPP
