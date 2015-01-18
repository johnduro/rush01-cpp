#include <net/route.h>
#include <net/if.h>
#include <sys/sysctl.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

int main() {
	short network_layer;
	short link_layer;
	int mib[6];
	char *buf = NULL, *lim, *next;
	size_t len;
	struct if_msghdr *ifm;


	static int64_t prev_ipackets;
	static int64_t prev_opackets;
	static int64_t prev_ibytes;
	static int64_t prev_obytes;

	int64_t ipackets = 0;
	int64_t opackets = 0;
	int64_t ibytes = 0;
	int64_t obytes = 0;

	mib[0]= CTL_NET;// networking subsystem
	mib[1]= PF_ROUTE;// type of information
	mib[2]= 0;// protocol (IPPROTO_xxx)
	mib[3]= 0;// address family
	mib[4]= NET_RT_IFLIST2;// operation
	mib[5]= 0;
	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
		return 0.0;

	if ((buf = (char*) malloc(len)) == NULL) {
		printf("malloc failed\n");
		exit(1);
	}
	if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
		if (buf) free(buf);
		return 0.0;
	}

	lim = buf + len;
	for (next = buf; next < lim; ) {
		network_layer = link_layer = 0;
		ifm = (struct if_msghdr *)next;
		next += ifm->ifm_msglen;

		if (ifm->ifm_type == RTM_IFINFO2) {
			struct if_msghdr2 *if2m = (struct if_msghdr2 *)ifm;

			if(if2m->ifm_data.ifi_type!=18) { /* do not count loopback traffic */
				opackets += if2m->ifm_data.ifi_opackets;
				ipackets += if2m->ifm_data.ifi_ipackets;
				obytes   += if2m->ifm_data.ifi_obytes;
				ibytes   += if2m->ifm_data.ifi_ibytes;
			}
		}
	}

	int64_t delta_obytes = obytes - prev_obytes;
	int64_t delta_ibytes = ibytes - prev_ibytes;

	free(buf);

	prev_ipackets = ipackets;
	prev_opackets = opackets;
	prev_ibytes = ibytes;
	prev_obytes = obytes;

	printf("total network bytes input: %f\n", (double) delta_ibytes);
	printf("total network bytes output: %f\n", (double) delta_obytes);
	printf("total network packet input: %f\n", (double) ipackets);
	printf("total network packet output: %f\n", (double) opackets);

	double result = ((double) delta_obytes + delta_ibytes) / ((double) 1024 * 1024 * (250.0 / 1000.0));
	return 0;
}
