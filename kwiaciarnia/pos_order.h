#pragma once
#include <string>
#include "database.h"

typedef std::vector<std::string> obj;

class pos_order
{
public:
	std::string id_pos_order, id_order, id_assortment, count;
	pos_order();
	~pos_order();
	pos_order(database & mysql, std::string id_pos_order);
	bool _insert(database & mysql);
	bool _delete(database & mysql);
	bool _update(database & mysql);
};

