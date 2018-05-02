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
	if(!this->isValid)
	{
		try
		{	
			//query user to check if user valid
			if(this->isUserValid())	//User valid
			{	
				cout << this->username <<" is valid" << endl;
				this->groups = this->queryGroups();
			}
			else //User is not valid
			{
			}
		} 
		catch (XmlException &xe) //document not found => user not exist
		{
			this->userXmlContent = "";
			cout<<"Error"<<endl;
		}
	}
};

string User::queryPassword()
{
	string pw = "";
	string containerName = this->getUsersContainerName();
	string query ="collection($containerName)/User[@username=$username]/password/string()";
	string variables[] = {"username"};
	int numberOfVariables = sizeof(variables)/sizeof(variables[0]) ;
	string values[] = {this->username};
	XmlResults results = this->query(containerName, query, variables, values, numberOfVariables);

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
	string containerName = this->getUsersContainerName();
	string query ="collection($containerName)/User[@username=$username]/groups/group/string()";
	string variables[] = {"username"};
	string values[] = {this->username};
	int numberOfVariables = sizeof(variables)/sizeof(variables[0]) ;

	XmlResults results = this->query(containerName, query, variables, values, numberOfVariables);
	XmlValue value;
	while (results.next(value))
	{
		groups.push_back(value.asString());
	}
	return groups;
}

bool User::hasPermission(string containerName, string documentName, PermissionType type)
{
	/* 
	if user is admin, return true
	if permission document not found, return false
	query owner permission, return true if has owner permission
	query group permission, return true if has group permission
	return false
	*/
	
	string permissionContainerName = this->getPermissionsContainerName();
	string permissionDocumentName = this->getPermissionDocumentName(containerName, documentName);
	
	//check admin permission
	if (this->isAdmin()) {
		return true;
	}
	//check if permission file exist
	string query = "if(empty(collection($containerName)/Permission[@name=$permissionDocument])) then ('false') else ('true')";
	string variables[] = {"permissionDocument"};
	string values[] = {permissionDocumentName};
	int numberOfVariables = sizeof(variables)/sizeof(variables[0]) ;

	XmlResults results = this->query(permissionContainerName, query, variables, values, numberOfVariables);

	if (this->isTrue(results)){	//if permission document exist
		//check owner permission
		if (this->hasOwnerPermission(permissionContainerName, permissionDocumentName, type)){
			cout <<"user has owner permission" << endl;		
			return true;
		}

		//check group permission
		if (this->hasGroupsPermission(permissionContainerName, permissionDocumentName, type)){
			cout <<"user has group permission" << endl;		
			return true;
		}
	}
	return false;
};

bool User::hasOwnerPermission(string permissionContainerName, string permissionDocumentName, PermissionType type)
{
	string query = "collection($containerName)/Permission[@name=$permissionDocument]/owner[@username=$username]/permission[@type=$permissionType]/string()";
	string permissionType = this->getPermissionType(type);
	string variables[] = {"permissionDocument","username", "permissionType"};
	string values[] = {permissionDocumentName, this->getUsername(), permissionType};
	int numberOfVariables = sizeof(variables)/sizeof(variables[0]) ;

	XmlResults results = this->query(permissionContainerName, query, variables, values, numberOfVariables);
	return this->isTrue(results); 
};

bool User::hasGroupsPermission(string permissionContainerName, string permissionDocumentName, PermissionType type)
{
	string query = "for $group in collection($containerName)/Permission[@name=$permissionDocument]/groups/group where contains($groupsString, $group/@name/string())return $group/permission[@type=$permissionType]/string()";
	string permissionType = this->getPermissionType(type);
	vector<string> groupsList = this->getGroups();
	string groupsString = "";
	for (int i = 0; i < groupsList.size(); i++){
		groupsString += groupsList[i];
	}
	string variables[] = {"permissionDocument","groupsString", "permissionType"};
	string values[] = {permissionDocumentName, groupsString, permissionType};
	int numberOfVariables = sizeof(variables)/sizeof(variables[0]) ;

	XmlResults results = this->query(permissionContainerName, query, variables, values, numberOfVariables);
	return this->isTrue(results); 
};

XmlResults User::query(string containerName, string query, string variables[], string values[], int numberOfVariables)
{
	XmlManager xmlManager;
	XmlContainer xmlContainer = xmlManager.openContainer(containerName);

	XmlQueryContext context = xmlManager.createQueryContext();	
	context.setVariableValue("containerName", containerName);
	for (int i = 0; i < numberOfVariables ; i++)
	{
		context.setVariableValue(variables[i], values[i]);
	}
	XmlQueryExpression qe = xmlManager.prepare(query, context);
	XmlResults results = qe.execute(context,0);
	return results;
};

bool User::isAdmin()
{
	return (this->username == ADMIN_USERNAME) && (this->password == ADMIN_PASSWORD);
};

bool User::isUserValid()
{
	if(!this->isValid) //not valid
	{
		string containerName = this->getUsersContainerName();
		string query ="collection($containerName)/User[@username=$username and password=$password]";
		string variables[] = {"username","password"};
		int numberOfVariables = sizeof(variables)/sizeof(variables[0]) ;
		string values[] = {this->username, this->password};
		XmlResults results = this->query(containerName, query, variables, values, numberOfVariables);
		if (results.size() == 1) //user exists
		{
			this->isValid = true;
		} 
		else //user not exist
		{
			this->isValid = false;
		}
	}
	return this->isValid;
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

bool User::isTrue(XmlResults results)
{
	XmlValue value;
	while (results.next(value))
	{
		if (value.asString() == "true") return true;
	}
	return false;
};
