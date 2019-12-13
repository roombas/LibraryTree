#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>

using namespace std;

int addbook();
int deletebook();

class Admin
{
private:
   
public:
 string username = "Darkling-01";
 string passwd = "Welcome2CS";


};

int setAdmin(){
    Admin Admin1;

    string user, paswd;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> paswd;

    if(user == Admin1.username || paswd == Admin1.passwd){
        int value;
        cout << "OPTIONS: \n";
        cout << "1-Add Book\n";
	    cout << "2-Delete Book\n";	
	    //cout << "3-Back\n";	
        cin >> value;

        switch (value)
        {
        case 1:
            addbook();
            break;
        case 2:
            deletebook();
            break;
       /* case 3:
            main();
            break; */
        default:

            break;
        }
    }else{
        cout << "Exiting now...";
    }
}

int addbook(){
    //increment the book from previous number..
    //add title
    //author
    //nodes should be involved and .txt
}

int deletebook(){
    //book title from .txt
}
#endif