// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/17 16:02:30 by mle-roy           #+#    #+#             //
//   Updated: 2015/01/17 19:49:57 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#include <iostream>
#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

//#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

#include <sys/param.h>
#include <sys/mount.h>

#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>

	static unsigned long long _previousTotalTicks = 0;
	static unsigned long long _previousIdleTicks = 0;

	float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
	{
		unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
		unsigned long long idleTicksSinceLastTime  = idleTicks-_previousIdleTicks;
		float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);
		_previousTotalTicks = totalTicks;
		_previousIdleTicks  = idleTicks;
		return ret;
	}

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.
	float GetCPULoad()
	{
		float sysLoadPercentage;
		host_cpu_load_info_data_t cpuinfo;
		mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
		if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count) == KERN_SUCCESS)
		{
			unsigned long long totalTicks = 0;
			for(int i=0; i<CPU_STATE_MAX; i++) totalTicks += cpuinfo.cpu_ticks[i];
			sysLoadPercentage = CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
		}
		else return -1.0f;
		return sysLoadPercentage;
	}



//get Os
std::string getOsName()
{
#ifdef _WIN32
	return "Windows 32-bit";
#elif _WIN64
	return "Windows 64-bit";
#elif __unix || __unix__
	return "Unix";
#elif __APPLE__ || __MACH__
	return "Mac OSX";
#elif __linux__
	reutnr "Linux";
#elif __FreeBSD__
	return "FreeBSD";
#else
	return "Other";
#endif
}

// BOOL WINAPI GetProcessTimes(
// 	_In_   HANDLE hProcess,
// 	_Out_  LPFILETIME lpCreationTime,
// 	_Out_  LPFILETIME lpExitTime,
// 	_Out_  LPFILETIME lpKernelTime,
// 	_Out_  LPFILETIME lpUserTime
// );
uint64_t get_cpu_freq(void)
{
    uint64_t freq = 0;
    size_t size = sizeof(freq);

    if (sysctlbyname("hw.cpufrequency", &freq, &size, NULL, 0) < 0)
    {
        perror("sysctl");
    }
    return freq;
}


int		main( void )
{
	// struct addrinfo hints, *info, *p;
	// int gai_result;

	// ** HOSTNAME ** //
	while (1)
	{
		sleep(1);
		system("clear");
	char hostname[1024];
	hostname[1023] = '\0';
	gethostname(hostname, 1023);

	std::cout << "hostname : " << hostname << std::endl;

	// ** LOGIN ** //
	char buf[100];

	getlogin_r(buf, 100);
	std::cout << "login : "<< buf  << std::endl;

	// ** TIME ** //
	time_t timer; //time
	struct tm * timeInfo; //time

	time(&timer); //time
	timeInfo = localtime(&timer); //time
	std::cout << getOsName() << std::endl; //get Os
	std::cout << asctime(timeInfo) << std::endl;//time


	// ** MEMORY ** //
	int		memDiv = 1048576;
	int mib[2];
	int64_t physical_memory;
	size_t length;

	mib[0] = CTL_HW;
	mib[1] = HW_MEMSIZE;
	length = sizeof(int64_t);
	sysctl(mib, 2, &physical_memory, &length, NULL, 0);

	std::cout << "total memory : " <<  (physical_memory / memDiv) << std::endl;

    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
										  reinterpret_cast<host_info64_t>(&vm_stats), &count))
    {
        long long free_memory = static_cast<int64_t>(vm_stats.free_count) * static_cast<int64_t>(page_size);

		long long used_memory = (static_cast<int64_t>(vm_stats.active_count) +
								 static_cast<int64_t>(vm_stats.inactive_count) +
								 static_cast<int64_t>(vm_stats.wire_count) *  static_cast<int64_t>(page_size));
		printf("free memory: %lld\nused memory: %lld\n", free_memory / memDiv, used_memory / memDiv);
    }

	// ** VIRTUAL MEM ** //
	struct statfs stats;
	uint64_t	myFreeSwap;

	if (0 == statfs("/", &stats))
	{
		myFreeSwap = static_cast<uint64_t>(stats.f_bsize) * stats.f_bfree;
	}
	std::cout << "free swap : " << myFreeSwap << std::endl;

	// xsw_usage vmusage = {0};
	// size_t size = sizeof(vmusage);
	// if( sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0)!=0 )
	// {
	// 	perror( "unable to get swap usage by calling sysctlbyname(\"vm.swapusage\",...)" );
	// }


	// ** CPU ** //
	std::cout << get_cpu_freq() << std::endl;

	struct rusage	r_usage;

	getrusage(RUSAGE_SELF, &r_usage);
	std::cout << "user : " << r_usage.ru_utime.tv_usec << std::endl;
	std::cout << "system : " << r_usage.ru_stime.tv_usec << std::endl;
		std::cout << ">";
		float cpuLoad = GetCPULoad();
//	float cpuLoad2 = CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
		std::cout << "cpuLoad : " << cpuLoad << std::endl;
	}
//	std::cout << "cpuLoad2 : " << cpuLoad2 << std::endl;


	/*
	** info supplementaire, recupere ip/socket etc...
	*/
	// memset(&hints, 0, sizeof hints);
	// hints.ai_family = AF_UNSPEC; /*either IPV4 or IPV6*/
	// hints.ai_socktype = SOCK_STREAM;
	// hints.ai_flags = AI_CANONNAME;

	// if ((gai_result = getaddrinfo(hostname, "http", &hints, &info)) != 0) {
	// 	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_result));
	// 	exit(1);
	// }

	// std::cout << gai_result << std::endl;
	// for(p = info; p != NULL; p = p->ai_next) {
	// 	printf("hostname: %s\n", p->ai_canonname);
	// }

	// freeaddrinfo(info);
}
