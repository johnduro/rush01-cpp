#ifndef MODULENET_HPP
# define MODULENET_HPP

# define OCTETS		'o'
# define PACKETS	'p'

# include <iostream>
# include <map>
# include <utility>
#include <net/route.h>
#include <net/if.h>
#include <sys/sysctl.h>
//#include <cstdio>
#include <cstdlib>
#include <unistd.h>
# include "AModule.hpp"
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

/*
retourne une struct Data

access a une string device + ip : data.ip

access aux valeurs suivantes :

bytes entrant  : data.net[OCTETS].first.first
bytes/sec entrants  : data.net[OCTETS].first.second
bytes sortant  : data.net[OCTETS].second.first
bytes/sec sortant  : data.net[OCTETS].second.second
packets entrant  : data.net[PACKETS].first.first
packets/sec entrants  : data.net[PACKETS].first.second
packets sortant  : data.net[PACKETS].second.first
packets/sec sortant  : data.net[PACKETS].second.second

*/
class ModuleNet : public AModule {
public:
	struct Data {
		std::string																	ip;
		std::map<char, std::pair<std::pair<long long, long long>, std::pair<long long, long long> > >		net;
	};
	ModuleNet(void);
	ModuleNet(int);
	ModuleNet(const ModuleNet&);
	~ModuleNet(void);

	ModuleNet&		operator=(const ModuleNet&);

	void			initialize(void);
	void			update(void);

	Data			getData(void) const;

private:
	Data			_data;
	int64_t 		_prev_ipackets;
	int64_t 		_prev_opackets;
	int64_t 		_prev_ibytes;
	int64_t 		_prev_obytes;
};

#endif // MODULENET_HPP
