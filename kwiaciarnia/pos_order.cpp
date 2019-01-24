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
	return true;
}

std::vector<pos_order> pos_order::retAllPosOrders(database mysql, std::string where)
{
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	std::vector<pos_order> pos;
	std::string query = "select flwr_pos_order.id_pos_order from flwr_pos_order" + where;
	mysql_query(mysql.connect, query.c_str());
	res_set = mysql_store_result(mysql.connect);
	int numrows = mysql_num_rows(res_set);
	int num_col = mysql_num_fields(res_set);
	int i = 0;
	pos_order c;
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		i = 0;
		while (i < num_col)
		{
			if (i == 0)
			{
				//std::cout << row[i] << "\n";
				pos_order cx(mysql, row[i]);
				c = cx;
			}
			i++;
		}
		pos.push_back(c);
	}
	return pos;
}