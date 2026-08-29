#ifndef DATABASE_H
#define DATABASE_H

#include <string>


bool connectToDatabase();


bool insertUser(
    const std::string& username,
    const std::string& password,
    const std::string& email
);


bool loginUser(
    const std::string& email,
    const std::string& password
);

bool logoutUser(
    const std::string& email
);

bool isUserLoggedIn(
    const std::string& email
);

#endif
