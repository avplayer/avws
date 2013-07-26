#include <iostream>
#include "avws.hpp"

int main(int argc, char* argv[])
{
	boost::asio::io_service io;
	avws::web_socket s(io);

	INIT_LOGGER(".", "avws.log");

	s.open("ws://echo.websocket.org");

	UNINIT_LOGGER();
	return 0;
}
