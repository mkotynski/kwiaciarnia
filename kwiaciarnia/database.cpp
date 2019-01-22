#include "pch.h"
#include "database.h"


database::~database()
{
}

std::vector<std::string> database::retRow(std::string query)
{
	std::vector<std::string> rRow;
	MYSQL_RES *res_set;
	MYSQL_ROW row;

	bool t = mysql_query(connect, query.c_str());

	if (t == false)
	{
		res_set = mysql_store_result(connect);
		int num_col = mysql_num_fields(res_set);
		rRow.push_back(std::to_string(num_col));

		if (((row = mysql_fetch_row(res_set)) != NULL))
		{
			for (int i = 0; i < num_col; i++)
			{
				rRow.push_back(row[i]);
			}
		}
		return rRow;
	}
}

bool database::query(std::string query)
{
	if (mysql_query(this->connect, query.c_str()) == 0) return false;
	else return true;
}

int database::numberOfRows(std::string tab, std::string where)
{
	std::vector<std::string> row = retRow("select count(*) from " + tab + " " + where);
	return atoi(row[1].c_str());
}

bool database::isExist(std::string query)
{
	std::vector<std::string> ret = this->retRow(query);
	if (ret.size() > 1) return true;
	else return false;
}

void dbInfo(database& db)
{
	std::cout << std::endl << "Server: " << db.server;
	std::cout << std::endl << "User: " << db.user;
	std::cout << std::endl << "DB Name: " << db.db;
	_getch();
}