///#include "httplib.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <string>
#include <iostream>

// HTTP
///static httplib::Client cli("http://localhost:4334");


namespace Logger
{
	static void DEBUG(std::string d_message) {
		std::string url = "/?event=DEBUG&message=" + d_message;

		std::cout << d_message << std::endl;
	}
	static void INFO(std::string i_message) {
		std::string url = "/?event=INFO&message=" + i_message;

		std::cout << i_message << std::endl;
	}
	static void ERR(std::string e_message) {
		std::string url = "/?event=ERROR&message=" + e_message;

		std::cout << e_message << std::endl;;
	}
	static void FATAL(std::string f_message) {
		std::string url = "/?event=FATAL&message=" + f_message;

		std::cout << f_message << std::endl;
	}
}
