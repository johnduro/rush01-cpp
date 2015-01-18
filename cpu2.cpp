#include <mach/mach.h>
#include <mach/processor_info.h>
#include <sys/sysctl.h>
#include <sstream>
#include <list>
#include <iostream>

int		main ()
{
unsigned int                                cpu_count;
processor_cpu_load_info_t                   cpu_load;
mach_msg_type_number_t                      cpu_msg_count;
float                                       totaltime[4][2];
std::list<std::string>		data;

host_processor_info( mach_host_self(), PROCESSOR_CPU_LOAD_INFO,
					 &cpu_count,
					 reinterpret_cast<processor_info_array_t*>(&cpu_load),
					 &cpu_msg_count);

std::ostringstream sstr;
for (unsigned int i = 0; i < cpu_count; ++i) {
	std::ostringstream sstr2;
        totaltime[i][0] = cpu_load[i].cpu_ticks[CPU_STATE_USER] +
			cpu_load[i].cpu_ticks[CPU_STATE_SYSTEM];
        sstr2 << "   [" << i << "]: " << (totaltime[i][0] - totaltime[i][1]) << "%%  ";
        data.push_back(sstr2.str());
        totaltime[i][1] = totaltime[i][0];
}
std::list<std::string>::iterator	it = data.begin();

while (it != data.end())
	std::cout << *it << std::endl;
}
