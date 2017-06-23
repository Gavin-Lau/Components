#ifndef _DOMAIN_2_IP_H_
#define _DOMAIN_2_IP_H_

#include <iostream>
#include <string>
#include <list>

#if defined(_MSC_VER)
# include<winsock2.h>
# pragma   comment(lib,"WS2_32.lib") 
# include<Ws2tcpip.h>
# pragma comment(lib,"Ws2_32.lib")
#elif defined(__GNUC__)
# include <netdb.h>
# include <sys/socket.h>
#else
# error current platform isn't supported....
#endif

using std::cout;
using std::endl;

namespace NetHelper {
	/**
	* win32 attention: WSAStartup func must be called before
	*/

	inline std::list<std::string> domain2ip(const std::string& domain)
	{
		std::list<std::string> result;
		
		struct hostent* ent;
		if((ent = gethostbyname(domain.c_str())) ==  NULL)
		{
			cout << "gethostbyname error!\n";
			return result;
		}
		
		char **pptr = ent->h_addr_list;
		for( ; *pptr != NULL ; pptr++)
		{
			char ip[32] = {0};
#if defined(_MSC_VER)
			InetNtop(ent->h_addrtype , *pptr, ip , sizeof(ip));
#elif defined(__GNUC__)
			inet_ntop(hptr->h_addrtype, *pptr, ip, sizeof(ip));
#else
# error current platform isn't supported....
#endif
			result.append(ip);
		}
		return result;
	}
}


#endif //_DOMAIN_2_IP_H_