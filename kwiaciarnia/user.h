#pragma once
#include <string>
#include "database.h"
typedef std::vector<std::string> obj;

class user
{
public:
	std::string id_user, login, pass, permission, id_client;
	bool _setParameters(database & mysql);
	user();
	user(database &mysql, std::string id_user);
	~user();
	bool _insert(database &mysql);
	bool _delete(database &mysql);
	bool _update(database &mysql);
};

