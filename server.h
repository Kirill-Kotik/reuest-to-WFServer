#pragma once
#include <iostream>
#include <string>

using namespace std;
class server
{
private:
	string name;
	string service;
	string version;
	string request;

public:
	server() = default;

	server(string name, string service, string version, string request) :name(name), service(service), version(version), request(request) {}

	//server(string name, string service, string version) :name(name), service(service), version(version), request(0) {}
	
	void setName(const string& newName) {
		name = newName;
	}
	string getName() const {
		return name;
	}
	void setService(const string& newService) {
		service = newService;
	}
	string getService() const {
		return service;
	}
	void setVersion(string newVersion) {
		version = newVersion;
	}
	string getVersion() const {
		return version;
	}
	void setRequest(const string& newRequest) {
		request = newRequest;
	}
	string getRequest() const {
		return request;
	}
	string getServInfo() {
		string info = "?service = "+ getService() + "&version = " + getVersion() + "&request=" + getRequest();
		return info;
		
	}
	

};
	

