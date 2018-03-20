#include "User.hpp"
#include "Permission.hpp"
#include <dbxml/DbXml.hpp>
#include <iostream>

using namespace std;
using namespace DbXml;

int main(int argc, char **argv)
{	
	User user;
	user.setUsername("user1");
	user.setPassword("");
	cout<< user.getUsername() <<endl;

	//Permission permission = new Permission();
	cout<<"Hello"<<endl;
	return 0;
}