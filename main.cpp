#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include "include/httplib.h"

std::string host;
int port;

std::string configPath = "config.conf";

std::string readFile(std::string path) {
	std::fstream file(path.c_str());

	if(!file.is_open()) return "";

	std::string line;
	std::string text;

	while(getline(file, line)) {
		text.append(line);
		text.append("\n");
	}

	file.close();

	return text;
}

std::map<std::string, std::string> parseConf(std::string text) {
	std::map<std::string, std::string> lines;

	int pointer = 0;
	bool searchingOption = true;

	while(text[pointer] != '\0') { // Repeating until we're at the end of the line
		std::string option = "";
		std::string value = "";

		while(text[pointer] != '\n') { // Each of the config items are seperated by \n
			const char* character = &text[pointer];

			if(searchingOption) {
				if(*character == ':') {
					searchingOption = false;
				
					continue;
				}

				option.append(character);
			} else {
				value.append(character);
			}

			pointer++;
		}

		lines.insert({option, value});

		searchingOption = true;
	}

	return lines;
}

int main() {
	// Getting config data
	std::string configText = readFile(configPath);
	std::map<std::string, std::string> configData = parseConf(configText);

	// Moving config data to variables
	host = configData.at("host");
	port = std::stoi(configData.at("port"));

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
