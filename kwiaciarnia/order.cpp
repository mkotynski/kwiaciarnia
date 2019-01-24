#include "pch.h"
#include "order.h"


order::order()
{
}


order::~order()
{
}

order::order(database & mysql, std::string id_order)
{
	this->id_order = id_order;
	std::string query = "SELECT * FROM flwr_order WHERE id_order = '" + id_order + "';";
	obj ret = mysql.retRow(query);
	if (mysql.isExist(query))
	{
		this->id_client = ret[2];
		this->status = ret[3];
		this->date_order = ret[4];
		this->date_realization = ret[5];
	}
	else this->id_order = "0";
}


bool order::_insert(database &mysql)
{
	bool t = mysql.query("INSERT INTO `flwr_order` (`id_client`, `status`, `date_order`, `cost`) VALUES ('" + id_client + "', '0', (select current_date)), '" + cost + "' ");
	if (t == false) return false;
	else return true;
}

bool order::_delete(database &mysql)
{
	if (mysql.isExist("SELECT * FROM `flwr_order` WHERE `id_order` = '" + id_order + "';"))
	{
		bool t = mysql.query("UPDATE `flwr_order` SET `status` = '2' WHERE `flwr_order`.`id_order` = '" + id_order + "'");
		if (t == false) return false;
		else return true;
	}
	else return true;
}

bool order::_update(database &mysql)
{
	if (mysql.isExist("SELECT * FROM `flwr_order` WHERE `id_order` = '" + id_order + "';"))
	{
		bool t = mysql.query("UPDATE `flwr_order` SET `status` = '" + status + "', `date_realization` = '" + date_realization + "' WHERE `flwr_order`.`id_order` = '" + id_order + "'");
		if (t == false) return false;
		else return true;
	}
	else return true;
}