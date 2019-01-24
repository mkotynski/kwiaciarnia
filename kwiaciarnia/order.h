#pragma once
#include <string>
#include "database.h"
#include "pos_order.h"

typedef std::vector<std::string> obj;

class order
{
public:
	std::string id_order, id_client, status, date_order, date_realization, cost;
	std::vector<pos_order> pos_orders;
	order();
	~order();
	order(database & mysql, std::string id_order);
	bool _insert(database & mysql);
	bool _delete(database & mysql);
	bool _update(database & mysql);
	std::vector<order> retAllOrders(database mysql, std::string where);
};

