#include "pch.h"
#include "pos_order.h"


pos_order::pos_order()
{
}


pos_order::~pos_order()
{
}

pos_order::pos_order(database & mysql, std::string id_pos_order)
{
	this->id_pos_order = id_pos_order;
	std::string query = "SELECT * FROM flwr_pos_order WHERE id_pos_order = '" + id_pos_order + "';";
	obj ret = mysql.retRow(query);
	if (mysql.isExist(query))
	{
		this->id_order = ret[2];
		this->id_assortment = ret[3];
		this->count = ret[4];
	}
	else this->id_pos_order = "0";
}


bool pos_order::_insert(database &mysql)
{
	bool t = mysql.query("INSERT INTO `flwr_pos_order` (`id_order`, `id_assortment`, `count`) VALUES ('" + id_order + "', '" + id_assortment + "', '" + count + "');");
	if (t == false) return false;
	else return true;
}

bool pos_order::_delete(database &mysql)
{
	if (mysql.isExist("SELECT * FROM `flwr_pos_order` WHERE `id_pos_order` = '" + id_pos_order + "';"))
	{
		bool t = mysql.query("DELETE FROM `flwr_pos_order` WHERE `flwr_pos_order`.`id_pos_order` = '" + id_pos_order + "'");
		if (t == false) return false;
		else return true;
	}
	else return true;
}

bool pos_order::_update(database &mysql)
{
	/*if (mysql.isExist("SELECT * FROM `flwr_order` WHERE `id_order` = '" + id_order + "';"))
	{
		//bool t = mysql.query("UPDATE `flwr_order` SET `status` = '" + status + "', `date_realization` = '" + date_realization + "' WHERE `flwr_order`.`id_order` = '" + id_order + "'");
		if (t == false) return false;
		else return true;
	}
	else return true;*/
}
