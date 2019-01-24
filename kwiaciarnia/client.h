#pragma once
#include "user.h"
#include "assortment.h"
#include "menu.h"
#include "order.h"
#include "pos_order.h"
#include "validation.h"

typedef std::vector<std::string> obj;
class client : public user
{
public:
	std::string id_user, name, surname, dateOfBirth, city, street, post;
	bool _setParameters(database & mysql);
	bool _setParametersC(database & mysql);
	client(database mysql, std::string id_client);
	client();
	~client();
	bool _insertC(database &mysql);
	bool _deleteC(database &mysql);
	bool _updateC(database &mysql);
	std::vector<client> retAllClients(database mysql);
	void makeOrder(database & mysql);
	void writeOrders(database mysql);
	void cancelOrder(database mysql);
};

