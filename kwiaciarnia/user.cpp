#include "pch.h"
#include "user.h"


bool user::_setParameters(database & mysql)
{
	std::string query = "SELECT * FROM flwr_user WHERE id_user = '" + id_user + "';";
	obj ret = mysql.retRow(query);
	if (mysql.isExist(query))
	{
		this->login = ret[2];
		this->pass = ret[3];
		this->permission = ret[4];
		this->id_client = ret[5];

		return false;
	}
	else return true;
}


user::user()
{
}

user::user(database & mysql, std::string id_user)
{
	this->id_user = id_user;
	this->_setParameters(mysql);
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
	std::cout << "tutaj jestem-";
	std::cout << id_user;
	_getch();
	if (mysql.isExist("SELECT * FROM `flwr_user` WHERE `id_user` = '" + id_user + "'"))
	{
		std::cout << "here-";
		_getch();
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