#include <iostream>
#include <string>
#include <fstream>

#include "include/httplib.h"

std::string host;
int port;

std::string configPath = "./config.json";

int main() {
	host = "0.0.0.0";
	port = 8080;

	// Server setup
	std::cout << "Starting server on host: " << host << ":" << port << "\n";

	httplib::Server server;

	// Get
	std::cout << "Setting up get requests...\n";

	server.Get("/.*", [](const httplib::Request &req, httplib::Response &res) {
		const std::string* remote_addr = &req.remote_addr;
		const int* remote_port = &req.remote_port;
		const std::string* path = &req.path;

		std::cout << "Recieved a request on " << *remote_addr << ":" << *remote_port << " to " << *path << "\n";

		std::string output = *path;

		res.set_content(output, "text/plain");
	});

	// Listen
	std::cout << "Listening on port " << port << "\n";

	server.listen(host, port);
	

	return 0;
}
