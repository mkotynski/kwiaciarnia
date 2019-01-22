#pragma once
#include "database.h"
#include "menu.h"
#include "client.h"
#include "admin.h"

typedef std::vector<std::string> obj;

class session
{
	client _client;
	admin _admin;
public:
	int permission;
	session();
	~session();
	bool login(database &mysql);
	void works(database &mysql);
	void setMenu(menu &m);
	void getOptionForClient(database mysql, menu m, int &pointer, int &enter);
	void getOptionForAdmin(database mysql, menu m, int & pointer, int & enter);
};

