#include "User.hpp"
#include "Permission.hpp"
#include "dbxml/DbXml.hpp"
#include <iostream>

using namespace std;
using namespace DbXml;


int main(int argc, char **argv)
{	
	User user("user1","1111");
	/*user.setUsername("user1");
	user.setPassword("1111");
	user.validateUser();*/
	cout<< user.getUsername() <<endl;
	cout<< user.getUsersContainerName() <<endl;

	XmlManager xmlManager;
	if (user.isAdmin()) cout<<"admin"<<endl;
	//string userContainerName = "C:/Users/thuanPC/Desktop/Tethys/metadata/Users";
	/*string content = user.getUserXmlContent();
	cout<<content<<endl;*/

	//cout << userContainerName <<endl;
	XmlContainer usersContainer = xmlManager.openContainer("C:/Users/thuanPC/Desktop/Tethys/metadata/Users");
	
	XmlDocument userXmlDocument = usersContainer.getDocument(user.getUsername());
	cout << "Doc name = " << userXmlDocument.getName() << endl;
	//cout << "Metadata name = " << userXmlDocument.getMetaData() << endl;

	/*string password;
	userXmlDocument.getContent(password);
	cout<<password<<endl;*/


	//Permission permission = new Permission();
	cout<<"Finish"<<endl;
	return 0;
}