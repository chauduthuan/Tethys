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
	cout<< "Users Container path = " << user.getUsersContainerName() <<endl;
	string xmlString = user.getUserXmlContent();
	cout <<xmlString<<endl;


	//if (user.isAdmin()) cout<<"admin"<<endl;
	//string content = user.getUserXmlContent();
	//cout<<content<<endl;

	//cout << userContainerName <<endl;
	//XmlContainer usersContainer = xmlManager.openContainer("C:/Users/thuanPC/Desktop/Tethys/metadata/Users");
	
	//XmlDocument userXmlDocument = usersContainer.getDocument(user.getUsername());
	//cout << "Doc name = " << userXmlDocument.getName() << endl;
	//cout << "Metadata name = " << userXmlDocument.getMetaData() << endl;

	/*string password;
	userXmlDocument.getContent(password);
	cout<<password<<endl;*/

	//XmlManager xmlManager;
	//XmlContainer usersXmlContainer = xmlManager.openContainer("../../Tethys/metadata/Users");
	//XmlDocument userXmlDocument = usersXmlContainer.getDocument("user1");
	//cout << "the doc name = " << userXmlDocument.getName()<<endl;

	//XmlQueryContext context = xmlManager.createQueryContext();
	//string query = "collection('../../Tethys/metadata/Users')/User/password";
	////context.setVariableValue("name", this->username);
	//XmlResults results = xmlManager.query(query, context);
	
	//XmlQueryExpression qe = xmlManager.prepare("collection('C:/Users/thuanPC/Desktop/Tethys/metadata/Users')/User", context);
	//XmlResults results = qe.execute(context);
	
	//cout<<results.size()<<endl;

	//XmlValue value;
	//while (results.next(value))
	//{
		//cout<<"haha"<<endl;
		//cout<<value.asString()<<endl;
	//}

	//Permission permission = new Permission();


	cout<<"Finish"<<endl;
	return 0;
}