#include <bits/stdc++.h>
using namespace std;
#include "database.h"
void registerUser()
{
    string name;
    cout << "Enter name:";
    cin >> name;
    string email;
    cout << "Enter email:";
    cin >> email;
    string password;
    cout << "Enter password:";
    cin >> password;
    bool userREG = insertUser(name, password,email);
    if (userREG)
    {
        cout << "USER REGISTERD" << endl;
    }
    else
    {
        cout << "FAILED" << endl;
    }
}

void loginUserDB()
{
    string userEmail;
    string userPassword;
    cout << "Enter email:";
    cin >> userEmail;
    cout << "Enter password:";
    cin >> userPassword;
    bool login = loginUser(userEmail, userPassword);
    if (login)
    {
        cout << "User logged In" << endl;
    }
    else
    {
        cout << "failed" << endl;
    }
}

int main()
{
    if (connectToDatabase())
    {
        cout << "Database operation successfully!" << endl;
    }
    else
    {
        cout << "Database operation failed!" << endl;
        return 1;
    }
    while (true)
    {
        cout << "Enter 1 to register user\nEnter 2 to login\nEnter 3 to logout\n 0 to close program" << endl;
        int a;
        cin >> a;
        switch (a)
        {
        case 0:
            cout << "Closing the program..." << endl;
            return 0;
        case 1:
            registerUser();
            break;
        case 2:
            loginUserDB();
            break;
        case 3:
        {
            string email;

            cout << "Enter Valid Email: ";
            cin >> email;

            if (logoutUser(email))
            {
                cout << "User logged out successfully!" << endl;
            }
            else
            {
                cout << "Logout failed!" << endl;
            }

            break;
        }

        default:
            cout << "Enter valid command" << endl;
            break;
        }
    }
}