
#include <sys/sysctl.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

#include "ModuleCPU.hpp"

ModuleCPU::ModuleCPU(void) : AModule(CPU, 3), _previousTotalTicks(0), _previousIdleTicks(0) {
	return;
}

ModuleCPU::ModuleCPU(const ModuleCPU& src) : AModule(src) {
	return;
}

ModuleCPU::~ModuleCPU(void) {
	return;
}

ModuleCPU&			ModuleCPU::operator=(const ModuleCPU& src) {
	this->_data = src.getData();
	this->_active = src.isActive();
	this->_name = src.getName();
	return *this;
}

float		ModuleCPU::_CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	unsigned long long totalTicksSinceLastTime = totalTicks - this->_previousTotalTicks;
	unsigned long long idleTicksSinceLastTime  = idleTicks - this->_previousIdleTicks;
	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? (static_cast<float>(idleTicksSinceLastTime)) / totalTicksSinceLastTime : 0);
	this->_previousTotalTicks = totalTicks;
	this->_previousIdleTicks  = idleTicks;
	return ret;
}

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.
float		ModuleCPU::_GetCPULoad( void )
{
	float sysLoadPercentage;
	host_cpu_load_info_data_t cpuinfo;
	mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
	if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, reinterpret_cast<host_info_t>(&cpuinfo), &count) == KERN_SUCCESS)
	{
		unsigned long long totalTicks = 0;
		for(int i=0; i<CPU_STATE_MAX; i++) totalTicks += cpuinfo.cpu_ticks[i];
		sysLoadPercentage = this->_CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
	}
	else return -1.0f;
	return sysLoadPercentage;
}



void				ModuleCPU::initialize(void) {

	char	cpuBrand[100];
	size_t	nbCpu;
	size_t	joe = 100;
	size_t	joe2 = sizeof(nbCpu);

    sysctlbyname("machdep.cpu.brand_string", &cpuBrand, &joe, NULL, 0);
    sysctlbyname("hw.ncpu", &nbCpu, &joe2, NULL, 0);

	this->_data.cpu_name = cpuBrand;
	this->_data.nb_core = nbCpu;

	this->_data.cpu_usage.first = (this->_GetCPULoad() * 100);
	this->_data.cpu_usage.second = 100 - this->_data.cpu_usage.first;
	return;
}

void				ModuleCPU::update(void) {


	this->_data.cpu_usage.first = (this->_GetCPULoad() * 100);
	this->_data.cpu_usage.second = 100 - this->_data.cpu_usage.first;
	return;
}

ModuleCPU::Data		ModuleCPU::getData(void) const {
	return this->_data;
}



// #include <unistd.h>
// #include <stdlib.h>

// int	main ( void )
// {
// 	ModuleCPU	modC;
// 	ModuleCPU::Data		dat;

// 	modC.initialize();
// 	while (1)
// 	{
// 		sleep(1);
// 		modC.update();
// 		system("clear");
// 		dat = modC.getData();
// 		std::cout << "CPU name : " << dat.cpu_name << std::endl;
// 		std::cout << "CPU cores : " << dat.nb_core << std::endl;
// 		std::cout << "CPU activity : " << dat.cpu_usage.first << " %" <<  std::endl;
// 		std::cout << "CPU idle : " << dat.cpu_usage.second << " %" <<  std::endl;
// 	}
// 	return 0;
// }
