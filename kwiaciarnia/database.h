#pragma once
#include <mysql.h>
#include <string>
#include <vector>
#include <iostream>
#include <conio.h>

class database
{
	std::string server, user, password, db;
public:
	MYSQL* connect;
	database() : server("localhost"), user("root"), password(""), db("flower_shop")
	{
		this->connect = mysql_init(NULL);
		this->connect = mysql_real_connect(connect, server.c_str(), user.c_str(), password.c_str(), db.c_str(), 0, NULL, 0);
	};
	~database();

	std::vector<std::string> retRow(std::string query);
	bool query(std::string query);
	int numberOfRows(std::string query, std::string where);
	bool isExist(std::string query);
	friend class book;
	friend void dbInfo(database& db);
};

