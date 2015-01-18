// #include <stdio.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <netdb.h>
// #include <sys/ioctl.h>
// #include <net/if.h>

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main () {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        } else if (ifa->ifa_addr->sa_family == AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return 0;
}

// int main(void)
// {
// 	char buf[8192] = {0};
// 	struct ifconf ifc = {0};
// 	struct ifreq *ifr = NULL;
// 	int sck = 0;
// 	int nInterfaces = 0;
// 	int i = 0;
// 	char ip[INET6_ADDRSTRLEN] = {0};
// 	char macp[19];
// 	struct ifreq *item;
// 	struct sockaddr *addr;

// 	/* Get a socket handle. */
// 	sck = socket(PF_INET, SOCK_DGRAM, 0);
// 	if(sck < 0)
// 	{
// 		perror("socket");
// 		return 1;
// 	}

// 	/* Query available interfaces. */
// 	ifc.ifc_len = sizeof(buf);
// 	ifc.ifc_buf = buf;
// 	if(ioctl(sck, SIOCGIFCONF, &ifc) < 0)
// 	{
// 		perror("ioctl(SIOCGIFCONF)");
// 		return 1;
// 	}

// 	/* Iterate through the list of interfaces. */
// 	ifr = ifc.ifc_req;
// 	nInterfaces = ifc.ifc_len / sizeof(struct ifreq);

// 	for(i = 0; i < nInterfaces; i++)
// 	{
// 		item = &ifr[i];

// 		addr = &(item->ifr_addr);

// 		/* Get the IP address*/
// 		if(ioctl(sck, SIOCGIFADDR, item) < 0)
// 		{
// 			perror("ioctl(OSIOCGIFADDR)");
// 		}

// 		if (inet_ntop(AF_INET, &(((struct sockaddr_in *)addr)->sin_addr), ip, sizeof ip) == NULL) //vracia adresu interf
//         {
// 			perror("inet_ntop");
// 			continue;
//         }

// 		/* Get the MAC address */
// 		if(ioctl(sck, SIOCGIFHWADDR, item) < 0) {
// 			perror("ioctl(SIOCGIFHWADDR)");
// 			return 1;
// 		}

// 		/* display result */

// 		sprintf(macp, " %02x:%02x:%02x:%02x:%02x:%02x",
// 				(unsigned char)item->ifr_hwaddr.sa_data[0],
// 				(unsigned char)item->ifr_hwaddr.sa_data[1],
// 				(unsigned char)item->ifr_hwaddr.sa_data[2],
// 				(unsigned char)item->ifr_hwaddr.sa_data[3],
// 				(unsigned char)item->ifr_hwaddr.sa_data[4],
// 				(unsigned char)item->ifr_hwaddr.sa_data[5]);

// 		printf("%s %s ", ip, macp);

// 	}

// 	return 0;
// }
