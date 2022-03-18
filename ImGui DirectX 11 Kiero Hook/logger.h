#include "httplib.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT

// HTTP
static httplib::Client cli("http://localhost:4334");


namespace Logger
{
	static void DEBUG(std::string d_message) {
		std::string url = "/?event=DEBUG&message=" + d_message;

		auto res = cli.Get(url.data());
	}
	static void INFO(std::string i_message) {
		std::string url = "/?event=INFO&message=" + i_message;

		auto res =  cli.Get(url.data());
	}
	static void ERR(std::string e_message) {
		std::string url = "/?event=ERROR&message=" + e_message;

		auto res = cli.Get(url.data());
	}
	static void FATAL(std::string f_message) {
		std::string url = "/?event=FATAL&message=" + f_message;

		auto res = cli.Get(url.data());
	}
}
