#include "Permission.hpp"

Permission::Permission(std::string containerName){
    this->containerName = containerName;
};

Permission::Permission(std::string containerName, std::string documentName){
    this->containerName = containerName;
    this->documentName = documentName;
}

bool Permission::isUserOrPermissionDocument(){
    return this->containerName==USERS_CONTAINER_NAME || this->containerName==PERMISSIONS_CONTAINER_NAME;
};

bool Permission::hasPermission(User user, std::string permissionType){
    if(isUserOrPermissionDocument()){
        return user.isAdmin();
    }

	/* for normal document, read permission document and check permission
	if permission xml not found, return true
	if user is admin, return true
	if user is owner, return permission.xml/owner/read
	iterate through each group of the user, for each group name
		check permission.xml/groups/group[@name="group_name"]/read
		if true, return true
	return false
	*/

    return false;
};

//XmlDocument Permission::getPermissionDocument(){
//
//};
