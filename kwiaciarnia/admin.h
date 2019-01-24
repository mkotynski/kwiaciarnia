#pragma once
#include "client.h"
#include "validation.h"
#include "menu.h"
class admin : public user
{
public:
	admin();
	admin(database mysql, std::string id_user);
	~admin();
	void addNewClient(database & mysql);
	void deleteClient(database & mysql);
};

