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
		this->cost = ret[6];
		pos_order pos;
		this->pos_orders = pos.retAllPosOrders(mysql, " where id_order = '" + id_order + "'");
	}
	else this->id_order = "0";
}


bool order::_insert(database &mysql)
{
	bool t = mysql.query("INSERT INTO `flwr_order` (`id_client`, `status`, `date_order`, `cost`) VALUES ('" + id_client + "', '0', (select current_date), '0' )");
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
		bool t = mysql.query("UPDATE `flwr_order` SET `status` = '" + status + "', `date_realization` = '" + date_realization + "', `cost` = '"+cost+"' WHERE `flwr_order`.`id_order` = '" + id_order + "'");
		if (t == false) return false;
		else return true;
	}
	else return true;
}



std::vector<order> order::retAllOrders(database mysql, std::string where)
{
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	std::vector<order> orderz;
	std::string query = "select flwr_order.id_order from flwr_order" + where;
	mysql_query(mysql.connect, query.c_str());
	res_set = mysql_store_result(mysql.connect);
	int numrows = mysql_num_rows(res_set);
	int num_col = mysql_num_fields(res_set);
	int i = 0;
	order c;
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		i = 0;
		while (i < num_col)
		{
			if (i == 0)
			{
				//std::cout << row[i] << "\n";
				order cx(mysql, row[i]);
				c = cx;
			}
			i++;
		}
		orderz.push_back(c);
	}
	return orderz;
}
