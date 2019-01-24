#pragma once
#include "client.h"
#include "validation.h"
#include "menu.h"
#include "assortment.h"
class admin : public user
{
public:
	admin();
	admin(database mysql, std::string id_user);
	~admin();
	void addNewClient(database & mysql);
	void deleteClient(database & mysql);
	void addNewOffert(database & mysql);
	void deleteOffert(database & mysql);
	void cancelOrder(database mysql);
};

