#include <boost/uuid/uuid_io.hpp>

#include <breep/network/tcp.hpp>

#include <iostream>

int main(int argc, char * argv[])
{
	if (argc != 2 && argc != 4) {
		std::cout << "Usage: chat.elf <hosting port> [<target ip> <target port>]" << std::endl;
		return 1;
	}

	// taking the local hosting port as parameter.
	breep::tcp::peer_manager peer_manager(static_cast<unsigned short>(atoi(argv[1])));
	return 0;
}
