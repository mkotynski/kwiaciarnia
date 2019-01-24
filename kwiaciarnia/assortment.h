#pragma once
#include <string>
#include "database.h"

typedef std::vector<std::string> obj;

class assortment
{
public:
	std::string id_assortment, name, price, count;
	assortment();
	~assortment();
	assortment(database & mysql, std::string id_assortment);
	bool _insert(database & mysql);
	bool _delete(database & mysql);
	bool _update(database & mysql);
	std::vector<assortment> retAllAssortment(database mysql, std::string where);
};

