#include <sys/types.h>
#include <sys/sysctl.h>

#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

#include "ModuleRAM.hpp"

ModuleRAM::ModuleRAM(void) : AModule(RAM) {
	return;
}

ModuleRAM::ModuleRAM(const ModuleRAM& src) : AModule(src) {
	return;
}

ModuleRAM::~ModuleRAM(void) {
	return;
}

ModuleRAM&			ModuleRAM::operator=(const ModuleRAM& src) {
	this->_data = src.getData();
	this->_active = src.isActive();
	this->_name = src.getName();
	return *this;
}

void				ModuleRAM::initialize(void) {
	int mib[2];
	int64_t physical_memory;
	size_t length;

	mib[0] = CTL_HW;
	mib[1] = HW_MEMSIZE;
	length = sizeof(int64_t);
	sysctl(mib, 2, &physical_memory, &length, NULL, 0);
	this->_data.memory.first = physical_memory;
	this->update();
	return;
}

void				ModuleRAM::update(void) {
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;
	float		keep;

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
										  reinterpret_cast<host_info64_t>(&vm_stats), &count))
    {
        this->_data.memory.second = static_cast<int64_t>(vm_stats.free_count) * static_cast<int64_t>(page_size);

		this->_data.used_mem.first =  (static_cast<int64_t>(vm_stats.active_count) +
									   static_cast<int64_t>(vm_stats.inactive_count) +
									   static_cast<int64_t>(vm_stats.wire_count) *  static_cast<int64_t>(page_size));

		keep = static_cast<float>(this->_data.used_mem.first) / static_cast<float>(this->_data.memory.first);
		this->_data.used_mem.second = (keep * 100);
    }
	return;
}

ModuleRAM::Data		ModuleRAM::getData(void) const {
	return this->_data;
}


// int main ()
// {
// 	ModuleRAM  modR;
// 	ModuleRAM::Data		s;

// 	modR.initialize();
// 	s = modR.getData();
// 	std::cout << "total : " << s.memory.first << std::endl;
// 	std::cout << "free : " << s.memory.second << std::endl;
// 	std::cout << "used : " << s.used_mem.first << std::endl;
// 	std::cout << "percent : " << s.used_mem.second << " %" << std::endl;
// 	return 0;
// }
