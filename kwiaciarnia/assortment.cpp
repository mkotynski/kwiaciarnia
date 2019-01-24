#include "pch.h"
#include "assortment.h"


assortment::assortment()
{
}


assortment::~assortment()
{
}

assortment::assortment(database & mysql, std::string id_assortment)
{
	this->id_assortment = id_assortment;
	std::string query = "SELECT * FROM flwr_assortment WHERE id_assortment = '" + id_assortment + "';";
	obj ret = mysql.retRow(query);
	if (mysql.isExist(query))
	{
		this->name = ret[2];
		this->price = ret[3];
		this->count = ret[4];
	}
	else this->id_assortment = "0";
}


bool assortment::_insert(database &mysql)
{
	bool t = mysql.query("INSERT INTO `flwr_assortment` (`name`, `price`, `count`) VALUES ('" + name + "', '" + price + "', '" + count + "');");
	if (t == false) return false;
	else return true;
}

bool assortment::_delete(database &mysql)
{
	if (mysql.isExist("SELECT * FROM `flwr_assortment` WHERE `id_assortment` = '" + id_assortment + "';"))
	{
		bool t = mysql.query("DELETE FROM `flwr_assortment` WHERE `flwr_assortment`.`id_assortment` = '" + id_assortment + "'");
		if (t == false) return false;
		else return true;
	}
	else return true;
}

bool assortment::_update(database &mysql)
{
	if (mysql.isExist("SELECT * FROM `flwr_assortment` WHERE `id_assortment` = '" + id_assortment + "';"))
	{
		bool t = mysql.query("UPDATE `flwr_order` SET `status` = '" + status + "', `date_realization` = '" + date_realization + "' WHERE `flwr_order`.`id_order` = '" + id_order + "'");
		if (t == false) return false;
		else return true;
	}
	else return true;
}

