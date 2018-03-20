#include "User.hpp"
#include "Permission.hpp"

User::User()
{
};

User::User(std::string username, std::string password)
{
    this->username = username;
    this->password = password;
	this->isValid = false;
    this->validateUser();
};

void User::validateUser()
{
	try
	{
		XmlManager xmlManager;
		XmlContainer usersXmlContainer = xmlManager.openContainer(this->getUsersContainerName());
		XmlDocument userXmlDocument = usersXmlContainer.getDocument(this->username);
		//userXmlDocument.getContent(this->userXmlContent);
		/*
		querry password , assign to correctPassword, compare password and assign isValid
		query groups, assign groups
		*/
	} 
	catch (XmlException &xe) //document not found => user not exist
	{
		this->userXmlContent = "";
		

	}
};

string User::queryPassword()
{
	string password;
	return password;
}
vector<string> User::queryGroups()
{
	vector<string> groups;
	return groups;
}

bool User::isAdmin()
{
	return (this->username == ADMIN_USERNAME) && (this->password == ADMIN_PASSWORD);
};

bool User::isUserValid()
{
	return this->isValid;
};

//bool User::userExist(string username)
//{
//
//	return false;
//};

void User::setUsername(string username)
{
	this->username = username;
};

string User::getUsername(){
	return this->username;
}

void User::setPassword(string password)
{
	this->password = password;
};

string User::getPassword()
{
	return this->password;
};

void User::setGroups(vector<string> groups)
{
	this->groups = groups;
};

vector<string> User::getGroups()
{
	return this->groups;
};

string User::getUserXmlContent()
{
	return this->userXmlContent;
};
string User::getUsersContainerName()
{
	string s(DBXML_DIR);
	s += USERS_CONTAINER_NAME;
	return s;
}