#include "User.hpp"
#include "Permission.hpp"

User::User()
{
	this->isValid = false;
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
		userXmlDocument.getContent(this->userXmlContent);

		/*
		querry password , assign to correctPassword, compare password and assign isValid
		query groups, assign groups
		*/
		this->correctPassword = this->queryPassword();
		if (this->password == this->correctPassword) 
		{
			this->isValid = true;
			cout << "User valid" <<endl;
		}
		this->groups = this->queryGroups();

	} 
	catch (XmlException &xe) //document not found => user not exist
	{
		this->userXmlContent = "";
		cout<<"Error"<<endl;
	}
};

string User::queryPassword()
{
	string pw = "";
	XmlManager xmlManager;
	XmlContainer usersXmlContainer = xmlManager.openContainer(this->getUsersContainerName());

	XmlQueryContext context = xmlManager.createQueryContext();
	string query ="collection('../../Tethys/metadata/Users')/User[@username=$username]/password/string()";
	context.setVariableValue("username", this->username);
	XmlQueryExpression qe = xmlManager.prepare(query, context);
	XmlResults results = qe.execute(context,0);
	XmlValue value;
	while (results.next(value))
	{
		pw = value.asString();
	}
	return pw;
}

vector<string> User::queryGroups()
{
	vector<string> groups;
	XmlManager xmlManager;
	XmlContainer usersXmlContainer = xmlManager.openContainer(this->getUsersContainerName());

	XmlQueryContext context = xmlManager.createQueryContext();
	string query ="collection('../../Tethys/metadata/Users')/User[@username=$username]/groups/group/string()";
	context.setVariableValue("username", this->username);
	XmlQueryExpression qe = xmlManager.prepare(query, context);
	XmlResults results = qe.execute(context,0);
	XmlValue value;
	while (results.next(value))
	{
		groups.push_back(value.asString());
	}
	return groups;
}

bool User::hasPermission(string containerName, string documentName, PermissionType type)
{
	string permissionContainerName = this->getPermissionsContainerName();
	string permissionDocumentName = this->getPermissionDocumentName(containerName, documentName);
	//string permissionDocumentName = "Deployments_deployment1";
	XmlManager xmlManager;
	XmlContainer permissionsXmlContainer = xmlManager.openContainer(permissionContainerName);
	XmlDocument permissionXmlDocument = permissionsXmlContainer.getDocument(permissionDocumentName);
	string content;
	permissionXmlDocument.getContent(content);
	/* for normal document, read permission document and check permission
	if permission xml not found, return true
	if user is admin, return true
	if user is owner, return permission.xml/owner/read
	iterate through each group of the user, for each group name
		check permission.xml/groups/group[@name="group_name"]/read
		if true, return true
	return false
	*/

	return true;
};

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
	string s(METADATA_PATH);
	s += USERS_CONTAINER_NAME;
	return s;
}
string User::getPermissionsContainerName()
{
	string s(METADATA_PATH);
	s += PERMISSIONS_CONTAINER_NAME;
	return s;
}

string User::getPermissionDocumentName(string containerName, string documentName)
{
	string docName = containerName + "_" + documentName;
	return docName;
};

string User::getPermissionType(PermissionType type)
{
	switch(type)
	{
		case read:
			return "read";
		case modify:
			return "modify";
		default:
			return "read";
	}
};