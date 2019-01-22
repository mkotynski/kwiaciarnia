#pragma once
#include "user.h"
typedef std::vector<std::string> obj;
class client : public user
{
public:
	std::string name, surname, dateOfBirth, city, street, post;
	client();
	~client();
	bool _insertC(database &mysql);
	bool _deleteC(database &mysql);
	bool _updateC(database &mysql);
};

