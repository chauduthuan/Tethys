#include <string>

#include "User.hpp"

#define READ_PERMISSION "read"
#define WRITE_PERMISSION "write"
#define DELETE_PERMISSION "delete"

#ifndef Permission_H
#define Permission_H
//enum PermissionType {
//	read,
//	modify,
//};

class Permission{
public:

	Permission(std::string containerName);
	Permission(std::string containerName, std::string documentName);

	bool isUserOrPermissionDocument();

	bool hasPermission(User user, std::string permissionType);
	
	//bool hasReadPermission(User user);
	// bool hasWritePermission(User user);
	// bool hasDeletePermission(User user);
	// bool hasCreatePermission(User user);

private:
	std::string containerName;
	std::string documentName;

	std::string permissionXmlDocumentPath;
	//XmlDocument getPermissionDocument();


};

#endif