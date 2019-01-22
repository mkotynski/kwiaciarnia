#include "pch.h"
#include "client.h"


client::client()
{
}


client::~client()
{
}


bool client::_insertC(database &mysql)
{
	this->_insert(mysql);
	bool t = mysql.query("INSERT INTO `flwr_client` (`name`, `surname`, `dateOfBirth`, `city`, `street`, `post`) VALUES ('" + name + "', '" + surname + "', '" + dateOfBirth + "', '" + city + "', '" + street + "', '" + post + "');");
	obj ret = mysql.retRow("SELECT MAX(id_client) FROM flwr_client");
	this->id_client = ret[1];
	std::cout << "-- " << this->_update(mysql);
	if (t == false) return false;
	else return true;
}

bool client::_deleteC(database &mysql)
{
	if (mysql.isExist("SELECT * FROM `flwr_client` WHERE `id_client` = '" + id_client + "'"))
	{
		bool t = mysql.query("DELETE FROM `flwr_client` WHERE `flwr_client`.`id_client` = '" + id_client + "'");
		if (t == false) return false;
		else return true;
	}
	else return true;
}

bool client::_updateC(database &mysql)
{
	bool t = mysql.query("UPDATE `flwr_client` SET `name` = '" + name + "', `surname` = '" + surname + "', `dateOfBirth` = '" + dateOfBirth + "', `city` = '" + city + "', `street` = '" + street + "', `post` = '" + post + "' WHERE `flwr_client`.`id_client` = '" + id_client + "';");
	if (t == false) return false;
	else return true;
}