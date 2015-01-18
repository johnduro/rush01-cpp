#ifndef MODULECPU_HPP
# define MODULECPU_HPP

# include <iostream>
# include <map>
# include <utility>
# include "AModule.hpp"



// ** retourne une struct Data ** //
// ** data.cpu_name est le nom et frequence du proc en std::string ** //
// ** data.nb_core donne le nombre de cpu en int ** //
// ** data.cpu_usage retourne une pair de deux float ** //
// ** data.cpu_usage.first donne le % d'activite ** //
// ** data.cpu_usage.second donne le % d'inactivite ** //
class ModuleCPU : public AModule {
public:

	struct Data {
		std::string					cpu_name;
		int							nb_core;
		std::pair<float , float>	cpu_usage;
	};
	ModuleCPU(void);
	ModuleCPU(const ModuleCPU&);
	~ModuleCPU(void);

	ModuleCPU&		operator=(const ModuleCPU&);

	void			initialize(void);
	void			update(void);

	Data			getData(void) const;

private:
	Data				_data;
	unsigned long long _previousTotalTicks;
	unsigned long long _previousIdleTicks;
	float			_CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
	float			_GetCPULoad( void );

};

#endif // MODULECPU_HPP
