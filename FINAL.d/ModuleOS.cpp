#include "ModuleOS.hpp"


ModuleOS::ModuleOS(void) : AModule(OS, 2) {
	return;
}

ModuleOS::ModuleOS(const ModuleOS& src) : AModule(src) {
	return;
}

ModuleOS::~ModuleOS(void) {
	return;
}

ModuleOS&						ModuleOS::operator=(const ModuleOS& src) {
	this->_data = src.getData();
	this->_active = src.isActive();
	this->_name = src.getName();
	return *this;
}

std::string		ModuleOS::_getOsName( void )
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

char *		ModuleOS::_osversionString(void) {
    int mib[2];
    size_t len;
    char *kernelVersion = NULL;

    mib[0] = CTL_KERN;
    mib[1] = KERN_OSRELEASE;

    if (sysctl(mib, 2, NULL, &len, NULL, 0) < 0 ) {
        fflush(stdout);
        exit(4) ;
    }

    kernelVersion = new char(len);
    if (kernelVersion == NULL ) {
        fflush(stdout);
        exit(4) ;
    }
    if (sysctl(mib, 2, kernelVersion, &len, NULL, 0) < 0 ) {
        fflush(stdout);
        exit(4) ;
    }
	return kernelVersion;
}

void		ModuleOS::_macosx_ver(char *darwinversion, osxver *osxversion ) {
/*
    From the book Mac Os X and IOS Internals:
    In version 10.1.1, Darwin (the core OS) was renumbered from v1.4.1 to 5.1,
    and since then has followed the OS X numbers consistently by being four
    numbers ahead of the minor version, and aligning its own minor with the
    sub-version.
*/
    char firstelm[2]= {0,0},secElm[2]={0,0};

    if (strlen(darwinversion) < 5 ) {
        fflush(stdout);
        exit(2);
    }
    char *s = darwinversion,*t = firstelm, *curdot = strchr(darwinversion,'.' );

    while ( s != curdot )
        *t++ = *s++;
    t=secElm ;
    curdot=strchr(++s,'.' );
    while ( s != curdot )
        *t++ = *s++;
    int maj = 0, min = 0;
    maj = static_cast<int>(strtol(firstelm, static_cast<char **>(NULL), 10));
    if ( maj == 0 && errno == EINVAL ) {
        fflush(stdout);
        exit(4);
    }

    min = static_cast<int>(strtol(secElm, static_cast<char **>(NULL), 10));

    if ( min  == 0 && errno == EINVAL ) {
        fflush(stdout);
        exit(4);
    }
    osxversion->minor = maj - 4;
    osxversion->sub = min;
}

void							ModuleOS::initialize(void) {

    osxver foundver;
	char *osverstr = NULL ;
    osverstr = this->_osversionString();
    this->_macosx_ver(osverstr, &foundver);

	int minor = foundver.minor;
	int sub = foundver.sub;
	std::stringstream smin;
	std::stringstream ssub;

	smin << minor;
	ssub << sub;
	this->_data.insert(this->_data.begin(), this->_getOsName());
	this->_data[0].append(" 10.").append(smin.str()).append(".").append(ssub.str());

	char	model[100];
	char	machine[100];
	size_t	joe = 100;

    sysctlbyname("hw.model", &model, &joe, NULL, 0);
    sysctlbyname("hw.machine", &machine, &joe, NULL, 0);
	std::string		mach = model;
	mach.append(" ").append(machine);
	this->_data.push_back(mach);
	char	kernOS[100];
	char	kernVers[100];
    sysctlbyname("kern.ostype", &kernOS, &joe, NULL, 0);
    sysctlbyname("kern.osrelease", &kernVers, &joe, NULL, 0);
	std::string		kern = kernOS;
	kern.append(" ").append(kernVers);
	this->_data.push_back(kern);
	return;
}

void							ModuleOS::update(void) {
	this->initialize();
	return;
}

std::vector<std::string>		ModuleOS::getData(void) const {
	return this->_data;
}


// int		main()
// {
// 	ModuleOS	modO;
// 	std::vector<std::string>	vec;

// 	modO.initialize();
// 	vec = modO.getData();
// 	std::cout << vec[0] << std::endl;
// 	std::cout << "Model : " << vec[1] << std::endl;
// 	std::cout << "Kernel : " << vec[2] << std::endl;
// }
