#include <string>
#include <vector>
#include <iostream>

#include "dbxml/DbXml.hpp"

#define METADATA_PATH "../../Tethys/metadata/permission/"
//#define METADATA_PATH "C:/Users/tchau/Desktop/Tethys/metadata/permission"

#define USERS_CONTAINER_NAME "Users"
#define ADMINS_CONTAINER_NAME "Admins"
#define PERMISSIONS_CONTAINER_NAME "Permissions"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "asdf"

using namespace std;
using namespace DbXml;

#ifndef User_H
#define User_H

enum PermissionType {
	read,
	modify,
};

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

	string getUserXmlContent();
	//XmlDocument getUserXmlDocument();

	//bool userExist(string username);
	//string generateUserXml();
	//void addUser();	//add user to Users container

	void validateUser(); //similar to isUserValid
	bool isAdmin(); // compare with admin account
	bool isUserValid(); //check username and password
	
	//bool hasPermission(XmlContainer container, XmlDocument document, PermissionType type);
	bool hasPermission(string containerName, string documentName, PermissionType type);
	string getUsersContainerName();
	string getPermissionsContainerName();
	string getPermissionDocumentName(string containerName, string documentName);
	//XmlDocument getPermissionDocument(XmlContainer container, XmlDocument document);
	

private:
	string username;
	string password;
	//string correctPassword;
	vector<string> groups;

	bool isValid;
	//XmlDocument userXmlDocument;
	string queryPassword();
	string getPermissionType(PermissionType type);
	vector<string> queryGroups();
	
	int getArraySize(string *arr[]);
	XmlResults query(string containerName, string query, string variables[], string values[], int numberOfVariables);
	/*XmlManager xmlManager;
	XmlContainer usersXmlContainer;
	XmlDocument userXmlDocument;*/

	string userXmlContent;

};

#endif