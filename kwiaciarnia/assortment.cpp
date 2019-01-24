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
		bool t = mysql.query("UPDATE `flwr_assortment` SET `name` = '" + name + "', `price` = '" + price + "', `count` = '" + count + "' WHERE `flwr_assortment`.`id_assortment` = '" + id_assortment + "';");
		if (t == false) return false;
		else return true;
	}
	else return true;
}

std::vector<assortment> assortment::retAllAssortment(database mysql, std::string where)
{
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	std::vector<assortment> assorts;
	std::string query = "select flwr_assortment.id_assortment from flwr_assortment"+where;
	mysql_query(mysql.connect, query.c_str());
	res_set = mysql_store_result(mysql.connect);
	int numrows = mysql_num_rows(res_set);
	int num_col = mysql_num_fields(res_set);
	int i = 0;
	assortment c;
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		i = 0;
		while (i < num_col)
		{
			if (i == 0)
			{
				//std::cout << row[i] << "\n";
				assortment cx(mysql, row[i]);
				c = cx;
			}
			i++;
		}
		assorts.push_back(c);
	}
	return assorts;
}

