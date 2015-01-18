
#ifndef MODULENAME_HPP
# define MODULENAME_HPP

# include <string>
# include <utility>
# include "AModule.hpp"

// ** retourne une pair ** //
// ** acces par par.first(hostname) et pair.second(username) ** //

class ModuleName : public AModule {
private:
	std::pair<std::string, std::string>		_data;

public:
	ModuleName(void);
	ModuleName(int);
	ModuleName(const ModuleName&);
	~ModuleName(void);

	ModuleName&		operator=(const ModuleName&);

	void										initialize(void);
	void										update(void);

	std::pair<std::string, std::string>			getData(void) const;

};

#endif // MODULENAME_HPP
