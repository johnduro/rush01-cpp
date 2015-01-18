
#ifndef MODULENAME_HPP
# define MODULENAME_HPP

# define HOST	'h'
# define USER	'u'


# include <string>
# include <utility>
# include "AModule.hpp"

class ModuleName : public AModule {
private:
	std::pair<std::string, std::string>		_data;

public:
	ModuleName(void);
	ModuleName(const ModuleName&);
	~ModuleName(void);

	ModuleName&		operator=(const ModuleName&);

	void										initialize(void);
	void										update(void);

	std::pair<std::string, std::string>			getData(void) const;

};

#endif // MODULENAME_HPP
