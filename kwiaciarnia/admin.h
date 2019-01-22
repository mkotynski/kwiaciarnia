#pragma once
#include "client.h"
#include "validation.h"
class admin : public user
{
public:
	admin();
	admin(database mysql, std::string id_user);
	~admin();
	bool _setParameters(database & mysql);
	void addNewClient(database & mysql);
};

