#include "pch.h"
#include "user.h"


user::user()
{
}


user::~user()
{
}


bool user::_insert(database &mysql)
{
	bool t = mysql.query("INSERT INTO `flwr_user` (`login`, `pass`, `permission`, `id_client`) VALUES ('" + login + "', '" + pass + "', '" + permission + "', '" + id_client + "');");
	if (t == false) return false;
	else return true;
}

bool user::_delete(database &mysql)
{
	if (mysql.isExist("SELECT * FROM `flwr_user` WHERE `id_user` = '" + id_user + "'"))
	{
		bool t = mysql.query("DELETE FROM `flwr_user` WHERE `flwr_user`.`id_user` = '"+id_user+"'");
		if (t == false) return false;
		else return true;
	}
	else return true;
}

bool user::_update(database &mysql)
{
		bool t = mysql.query("UPDATE `flwr_user` SET `login` = '" + login + "', `pass` = '" + pass + "', `permission` = '" + permission + "', `id_client` = '" + id_client + "' WHERE `flwr_user`.`id_user` = '" + id_user + "';");
		if (t == false) return false;
		else return true;
}