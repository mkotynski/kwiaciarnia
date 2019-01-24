#pragma once
#include <string>
#include "database.h"

typedef std::vector<std::string> obj;

class order
{
public:
	std::string id_order, id_client, status, date_order, date_realization, cost;
	order();
	~order();
	order(database & mysql, std::string id_order);
	bool _insert(database & mysql);
	bool _delete(database & mysql);
	bool _update(database & mysql);
};

