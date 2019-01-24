#include "pch.h"
#include "client.h"


bool client::_setParametersC(database & mysql)
{
	std::string query = "SELECT * FROM flwr_client WHERE id_client = '" + id_client + "';";
	obj ret = mysql.retRow(query);
	if (mysql.isExist(query))
	{
		this->id_user = ret[2];
		this->name = ret[3];
		this->surname = ret[4];
		this->dateOfBirth = ret[5];
		this->city = ret[6];
		this->street = ret[7];
		this->post = ret[8];

		return false;
	}
	else return true;
}

client::client(database mysql, std::string id_client)
{
	this->id_client = id_client;
	this->_setParametersC(mysql);
	std::string query = "SELECT * FROM flwr_user WHERE id_user = '" + id_user + "';";
	obj ret = mysql.retRow(query);
	this->login = ret[2];
	this->pass = ret[3];
	this->permission = ret[4];
	this->id_client = ret[5];
}

client::client()
{

}


client::~client()
{
}


bool client::_insertC(database &mysql)
{
	this->_insert(mysql);
	obj ret1 = mysql.retRow("select max(id_user) from flwr_user;");
	bool t = mysql.query("INSERT INTO `flwr_client` (`id_user`, `name`, `surname`, `dateOfBirth`, `city`, `street`, `post`) VALUES ('" + ret1[1] + "', '" + name + "', '" + surname + "', '" + dateOfBirth + "', '" + city + "', '" + street + "', '" + post + "');");
	obj ret = mysql.retRow("select max(flwr_client.id_client), max(flwr_user.id_user) from flwr_client, flwr_user;");
	user _u(mysql, ret[2]);
	_u.id_client = ret[1];
	_u._update(mysql);
	if (t == false) return false;
	else return true;
}

bool client::_deleteC(database &mysql)
{
	if (mysql.isExist("SELECT * FROM `flwr_client` WHERE `id_client` = '" + id_client + "'"))
	{
		this->_delete(mysql);
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


std::vector<client> client::retAllClients(database mysql)
{
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	std::vector<client> clients;
	std::string query = "select flwr_client.id_client from flwr_client inner join flwr_user on flwr_client.id_client = flwr_user.id_client";
	mysql_query(mysql.connect, query.c_str());
	res_set = mysql_store_result(mysql.connect);
	int numrows = mysql_num_rows(res_set);
	int num_col = mysql_num_fields(res_set);
	int i = 0;
	client c;
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		i = 0;
		while (i < num_col)
		{
			if (i == 0)
			{
				std::cout << "\n" <<row[i];
				/*client cx(mysql, row[i]);
				c = cx;*/
			}
			i++;
		}
		//clients.push_back(c);
	}
	return clients;
}