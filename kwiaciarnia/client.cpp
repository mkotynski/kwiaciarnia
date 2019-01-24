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
		user u(mysql, id_user);
		bool t = mysql.query("DELETE FROM `flwr_client` WHERE `flwr_client`.`id_client` = '" + id_client + "'");
		u._delete(mysql);
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
	std::string query = "select flwr_client.id_client from flwr_client";
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
				//std::cout << row[i] << "\n";
				client cx(mysql, row[i]);
				c = cx;
			}
			i++;
		}
		clients.push_back(c);
	}
	return clients;
}

void client::makeOrder(database &mysql)
{
	assortment _a;
	std::string ab;
	std::string where;
	menu mx("Oferta");
	std::vector<std::string> snlist;
	std::vector<assortment> cart;
	std::vector<int> count;
	std::vector<assortment> list;
	std::string assort;
	mx.setHL(5);
	mx.type = 2;
	int xpointer = 1, xenter = 0;
	while (xpointer)
	{
		/****/
		list.clear();
		snlist.clear();
		list = _a.retAllAssortment(mysql,where);
		for (int i = 0; i < list.size(); i++)
		{
			assort = std::to_string(i+1) + ". " +list[i].name + " [" + list[i].price + " PLN]";
			if (i == list.size() - 1) assort += "\n\n";
			snlist.push_back(assort);
		}
		snlist.push_back("--[FILTR WYSZUKIWANIA]--");
		snlist.push_back("--[EDYTUJ KOSZYK]--");
		snlist.push_back("--[ZATWIERDZ ZAKUP]--");
		snlist.push_back("[COFNIJ]");
		mx.setOptionVector(snlist);
		/****/
		system("cls");
		int cost = 0;
		std::cout << " --- WYBIERZ PRZEDMIOT KTORY CHCESZ DODAC DO KOSZYKA --- " << std::endl;
		std::cout << "\nTWOJ KOSZYK: \n";
		for (int i = 0; i < cart.size(); i++)
		{
			std::cout << std::to_string(i+1) + ". " + cart[i].name << " |\t ILOSC: " << count[i] << "\n";
			cost = cost + std::stoi(cart[i].price)*count[i];
		}
		std::cout << "\nAKTUALNA WARTOSC KOSZYKA: " << cost << " PLN";
		std::cout << "\n\n--- OFERTA ---\n";
		mx.write(xpointer, xenter);
		mx.setPointer(xpointer, xenter);
		if (xenter == 1)
		{
			if (xpointer == mx.option.size()) xpointer = 0;
			else if (xpointer == mx.option.size()-1)
			{
				for (int a = 0; a < cart.size(); a++)
				{
					cost = cost + std::stoi(cart[a].price)*count[a];
				}
				if (cost > 0)
				{
					order _order;
					_order.id_client = id_client;
					_order._insert(mysql);
					obj ret = mysql.retRow("select max(id_order) from flwr_order");
					for (int a = 0; a < cart.size(); a++)
					{
						pos_order _pos_order;
						_pos_order.id_order = ret[1];
						_pos_order.id_assortment = cart[a].id_assortment;
						_pos_order.count = std::to_string(count[a]);
						_pos_order._insert(mysql);
					}
					order _o(mysql, ret[1]);
					_o.cost = cost;
					_o._update(mysql);
					std::cout << "DODANO NOWE ZAMOWIENIE o wartosci " << cost << " PLN - CZEKAJ NA POTWIERDZENIE";
					_getch();
					cart.clear();
					count.clear();
				}
				else std::cout << "Nie mozesz zlozyc pustego zamowienia";
			}
			else if (xpointer == mx.option.size()-2)
			{
				int zpointer = 1;
				int zenter = 0;
				std::string buy;
				while (zpointer)
				{
					/****/
					list.clear();
					snlist.clear();
					for (int i = 0; i < cart.size(); i++)
					{
						buy = std::to_string(i + 1) + ". " + cart[i].name + " |\t ILOSC: " + std::to_string(count[i]);
						snlist.push_back(buy);

					}
					snlist.push_back("Cofnij");
					mx.setOptionVector(snlist);
					/****/
					system("cls");
					std::cout << "\nTWOJ KOSZYK: \n";
					mx.write(zpointer, zenter);
					//std::cout << "Wcisnij strzalke w prawo aby edytowac / w lewo zeby usunac pozyje";
						int it = _getch();
						if (it == 77)
						{
							std::cout << "\nEdytowanie ilosci \n";
							std::cout << "Podaj nowa ilosc: ";
							getline(std::cin, ab);
							if (validation::isnum(ab)) {
								int a = validation::conv(ab);
								if (a > 0)
								{
									count[zpointer - 1] = a;
									std::cout << "Zmieniono ilosc wybranego przedmiotu";
								}
							}
						}
						else if (it == 75)
						{
							std::cout << "Usunieto z koszyka";
							cart.erase(cart.begin() + zpointer - 1);
							count.erase(count.begin() + zpointer - 1);
						}
						if (it == 72)
						{
							if ((zpointer - 1) > 0) zpointer -= 1;
							else zpointer = snlist.size();
						}
						if (it == 80)
						{
							if (zpointer + 1 < snlist.size() + 1) zpointer += 1;
							else zpointer = 1;
						}
						if (it == 13) zenter = 1;
					
					if (zenter == 1)
					{
						if (zpointer == mx.option.size()) zpointer = 0;
						else
						{
							zenter = 0;
						}
					}
				}
			}
			else if (xpointer == mx.option.size() - 3)
			{
				std::string filtr;
				std::cout << "\nFiltruj wyniki wyszukiwania po nazwie: ";
				getline(std::cin, filtr);
				where = " where upper(name) like upper('%" + filtr + "%')";
			}
			else
			{
				bool is = 0;
				int j = 0;
				assortment a(mysql, list[xpointer - 1].id_assortment);
				for (int i = 0; i < cart.size(); i++)
				{
					if (cart[i].id_assortment == a.id_assortment)
					{
						is = 1;
						j = i;
					}
				}
				if (is == 0)
				{
					cart.push_back(a);
					std::cout << "\n Podaj ilosc: ";
					getline(std::cin, ab);
					if (validation::isnum(ab)) {
						int a = validation::conv(ab);
						if (a > 0)
						{
							count.push_back(a);
							std::cout << "Dodano do koszyka";
						}
					}
				}
				if (is == 1)
				{
					std::cout << "\n Podaj nowa ilosc: ";
					getline(std::cin, ab);
					if (validation::isnum(ab)) {
						int a = validation::conv(ab);
						if (a > 0)
						{
							count[j] = a;
							std::cout << "Zmieniono ilosc wybranego przedmiotu";
						}
					}
				}
			}
			xenter = 0;
		}
	}
}