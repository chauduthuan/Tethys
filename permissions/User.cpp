#include "User.hpp"
#include "Permission.hpp"

User::User()
{
    /*this->validateUser();*/
};

User::User(std::string username, std::string password)
{
    this->username = username;
    this->password = password;
    //this->validateUser();
};

void User::validateUser()
{

};

bool User::isAdmin()
{
	return false;
};

bool User::userExist(string username)
{
	return false;
};

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
