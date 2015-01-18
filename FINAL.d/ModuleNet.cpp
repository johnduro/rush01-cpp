
#include "ModuleNet.hpp"

ModuleNet::ModuleNet(void) : AModule(NET), _prev_ipackets(0), _prev_opackets(0), _prev_ibytes(0), _prev_obytes(0) {
	return;
}

ModuleNet::ModuleNet(const ModuleNet& src) : AModule(src) {
	return;
}

ModuleNet::~ModuleNet(void) {
	return;
}

ModuleNet&			ModuleNet::operator=(const ModuleNet& src) {
	this->_data = src.getData();
	this->_active = src.isActive();
	this->_name = src.getName();
	return *this;
}

void				ModuleNet::initialize(void) {

	this->update();

    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET)
		{ // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr = &((reinterpret_cast<struct sockaddr_in *>(ifa->ifa_addr)))->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			if (strcmp(addressBuffer, "127.0.0.1"))
			{
				this->_data.ip = ifa->ifa_name;
				this->_data.ip.append(" : ").append(addressBuffer);
			}
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);

	return ;
}

void				ModuleNet::update(void) {


	short network_layer;
	short link_layer;
	int mib[6];
	char  *lim, *next;
	size_t len;
	struct if_msghdr *ifm;

	int64_t ipackets = 0;
	int64_t opackets = 0;
	int64_t ibytes = 0;
	int64_t obytes = 0;

	static_cast<void>(network_layer);
	mib[0]= CTL_NET;// networking subsystem
	mib[1]= PF_ROUTE;// type of information
	mib[2]= 0;// protocol (IPPROTO_xxx)
	mib[3]= 0;// address family
	mib[4]= NET_RT_IFLIST2;// operation
	mib[5]= 0;
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
		return ;

	char		buf[len];

	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0)
	{
		return ;
	}
	lim = buf + len;
	for (next = buf; next < lim; )
	{
		network_layer = link_layer = 0;
		ifm = reinterpret_cast<struct if_msghdr *>(next);
		next += ifm->ifm_msglen;

		if (ifm->ifm_type == RTM_IFINFO2)
		{
			struct if_msghdr2 *if2m = reinterpret_cast<struct if_msghdr2 *>(ifm);

			if(if2m->ifm_data.ifi_type!=18)
			{ /* do not count loopback traffic */
				opackets += if2m->ifm_data.ifi_opackets;
				ipackets += if2m->ifm_data.ifi_ipackets;
				obytes   += if2m->ifm_data.ifi_obytes;
				ibytes   += if2m->ifm_data.ifi_ibytes;
			}
		}
	}

	int64_t delta_obytes = obytes - this->_prev_obytes;
	int64_t delta_ibytes = ibytes - this->_prev_ibytes;
	int64_t delta_opackets = opackets - this->_prev_opackets;
	int64_t delta_ipackets = ipackets - this->_prev_ipackets;

	this->_prev_ipackets = ipackets;
	this->_prev_opackets = opackets;
	this->_prev_ibytes = ibytes;
	this->_prev_obytes = obytes;

	this->_data.net[OCTETS].first.first = static_cast<long long>(ibytes);
	this->_data.net[OCTETS].first.second = static_cast<long long>(delta_ibytes);
	this->_data.net[OCTETS].second.first = static_cast<long long>(obytes);
	this->_data.net[OCTETS].second.second = static_cast<long long>(delta_obytes);

	this->_data.net[PACKETS].first.first = static_cast<long long>(ipackets);
	this->_data.net[PACKETS].first.second = static_cast<long long>(delta_ipackets);
	this->_data.net[PACKETS].second.first = static_cast<long long>(opackets);
	this->_data.net[PACKETS].second.second = static_cast<long long>(delta_opackets);
	return ;
}

ModuleNet::Data		ModuleNet::getData(void) const {
	return this->_data;
}


// int main ()
// {
// 	ModuleNet	modN;
// 	ModuleNet::Data		data;

// 	modN.initialize();
// 	while (1)
// 	{
// 		sleep(1);
// 		system("clear");
// 		modN.update();
// 		data = modN.getData();
// 		std::cout << data.ip << std::endl;
// 		std::cout << "bytes entrant " << data.net[OCTETS].first.first    << std::endl;
// 		std::cout << "bytes/sec entrants " << data.net[OCTETS].first.second	  << std::endl;
// 		std::cout << "bytes sortant " << data.net[OCTETS].second.first	  << std::endl;
// 		std::cout << "bytes/sec sortant " << data.net[OCTETS].second.second  << std::endl;
// 		std::cout << "packets entrant " << data.net[PACKETS].first.first	  << std::endl;
// 		std::cout << "packets/sec entrants " << data.net[PACKETS].first.second  << std::endl;
// 		std::cout << "packets sortant " << data.net[PACKETS].second.first  << std::endl;
// 		std::cout << "packets/sec sortant " << data.net[PACKETS].second.second << std::endl;
// 	}
// 	return 0;
// }
