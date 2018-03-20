#include <string>
#include <vector>

#define USERS_CONTAINER_NAME "Users"
#define ADMINS_CONTAINER_NAME "Admins"
#define PERMISSIONS_CONTAINER_NAME "Permissions"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "asdf"

using namespace std;

#ifndef User_H
#define User_H
class User
{
public:
	User();
	User(string username, string password);


	void setUsername(string username);
	string getUsername();

	void setPassword(string password);
	string getPassword();

	void setGroups(vector<string> groups);
	vector<string> getGroups();

	//XmlDocument getUserXmlDocument();

	bool userExist(string username);
	//string generateUserXml();
	//void addUser();	//add user to Users container

	void validateUser(); //similar to isUserValid
	bool isAdmin(); // compare with admin account
	//bool isUserValid(); //chkeck username and password



private:
	string username;
	string password;
	vector<string> groups;
	//XmlDocument userXmlDocument;

};

#endif