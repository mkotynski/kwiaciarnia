#pragma once
#include <string>
#include "database.h"

class user
{
public:
	std::string id_user, login, pass, permission, id_client;
	user();
	~user();
	bool _insert(database &mysql);
	bool _delete(database &mysql);
	bool _update(database &mysql);
};

