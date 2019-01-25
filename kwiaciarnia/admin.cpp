#include "pch.h"
#include "admin.h"

typedef std::vector<std::string> obj;

admin::admin()
{

}

admin::admin(database mysql, std::string id_user)
{
	
}


admin::~admin()
{
}


void admin::addNewClient(database& mysql)
{
	std::cout << std::endl;
	std::cout << " --- DODAWANIA KLIENTA --- " << std::endl;
	client _client;
	std::cout << "Podaj login: ";
	std::getline(std::cin, _client.login);
	std::cout << "Podaj haslo: ";
	std::getline(std::cin, _client.pass);
	std::cout << "Podaj imie: ";
	std::getline(std::cin, _client.name);
	std::cout << "Podaj nazwisko: ";
	std::getline(std::cin, _client.surname);
	std::cout << "Podaj date urodzenia (w formacie yyyy-mm-dd): ";
	std::getline(std::cin, _client.dateOfBirth);
	std::cout << "Podaj adres (ulica nr): ";
	std::getline(std::cin, _client.street);
	std::cout << "Podaj kod pocztowy: ";
	std::getline(std::cin, _client.post);
	std::cout << "Podaj miejscowosc: ";
	std::getline(std::cin, _client.city);
	std::cout << std::endl;
	if (!validation::isPost(_client.post))
	{
		if (!_client._insertC(mysql))
		{
			std::cout << "Dodano klienta";;
		}
	}
}

void admin::editClient(database &mysql)
{
	client s;
	menu mx("Lekarze");
	std::vector<std::string> snlist;
	std::vector<client> list;
	std::string doc;
	mx.setHL(5);
	int xpointer = 1, xenter = 0;
	while (xpointer)
	{
		/*****/
		list.clear();
		snlist.clear();
		list = s.retAllClients(mysql);
		for (int i = 0; i < list.size(); i++)
		{
			doc = list[i].surname + " " + list[i].name + " : ";
			snlist.push_back(doc);
		}
		snlist.push_back("Cofnij");
		mx.setOptionVector(snlist);

		/*****/
		system("cls");
		std::cout << " --- EDYTUJ KLIENTA --- " << std::endl;
		mx.write(xpointer, xenter);
		mx.setPointer(xpointer, xenter);
		if (xenter == 1)
		{
			if (xpointer == mx.option.size()) xpointer = 0;
			else
			{
				client d(mysql, list[xpointer - 1].id_client);
				menu _menu("Edycja klienta");
				obj list;
				_menu.setHL(3);
				int ypointer = 1, yenter = 0;
				while (ypointer)
				{
					/***/
					std::string input;
					list.clear();
					list = { "Imie: " + d.name, "Nazwisko: " + d.surname, "Adres (ulica nr domu): " + d.street, "Kod pocztowy: " + d.post, "Miejscowosc: " + d.city };
					list.push_back("Cofnij");
					_menu.setOptionVector(list);
					/****/
					system("cls");
					std::cout << " --- EDYTUJ KLIENTA --- " << std::endl;
					_menu.write(ypointer, yenter);
					_menu.setPointer(ypointer, yenter);
					if (yenter == 1)
					{
						if (ypointer == _menu.option.size()) ypointer = 0;
						else
						{
							input = "";
							switch (ypointer)
							{
							case 1:
							{
								std::cout << std::endl << "Podaj nowe imie (" << d.name << "): ";
								getline(std::cin, input);
								if (!validation::isAppropriateLength(input, 2, 40))
								{
									d.name = input;
									if (!d._updateC(mysql))
									{
										std::cout << "Edytowano imie klienta";
										_getch();
									}
								}
								else std::cout << "Niepoprawna dlugosc!";
							};
							break;
							case 2:
							{
								std::cout << std::endl << "Podaj nowe nazwisko (" << d.surname << "): ";
								getline(std::cin, input);
								if (!validation::isAppropriateLength(input, 2, 40))
								{
									d.surname = input;
									if (!d._updateC(mysql))
									{
										std::cout << "Edytowano nazwisko klienta";
										_getch();
									}
								}
								else std::cout << "Niepoprawna dlugosc!";
							};
							break;
							case 3:
							{
								std::cout << std::endl << "Podaj nowy adres klienta (ulica nr domu) (" << d.street << "): ";
								getline(std::cin, input);
								if (!validation::isAppropriateLength(input, 2, 40))
								{
									d.street = input;
									if (!d._updateC(mysql))
									{
										std::cout << "Edytowano adres klienta";
										_getch();
									}
								}
								else std::cout << "Niepoprawna dlugosc!";
							};
							break;
							case 4:
							{
								std::cout << std::endl << "Podaj nowy kod pocztowy klienta (" << d.post << "): ";
								getline(std::cin, input);
								if (!validation::isPost(input))
								{
									d.post = input;
									if (!d._updateC(mysql))
									{
										std::cout << "Edytowano kod pocztowy klienta";
										_getch();
									}
								}
								else std::cout << "Niepoprawny kod pocztowy!";
							};
							break;
							case 5:
							{
								std::cout << std::endl << "Podaj nowa miejscowosc (poczty) (" << d.city << "): ";
								getline(std::cin, input);
								if (!validation::isAppropriateLength(input, 2, 40))
								{
									d.city = input;
									if (!d._updateC(mysql))
									{
										std::cout << "Edytowano miejscowosc (poczta) klienta";
										_getch();
									}
								}
								else std::cout << "Niepoprawna dlugosc!";
							};
							break;
							}
						}
						yenter = 0;
						//_getch();
					}
				}
				xenter = 0;
			}
		}
	}
}

void admin::deleteClient(database& mysql)
{
	client _c;
	menu mx("Klienci");
	std::vector<std::string> snlist;
	std::vector<client> list;
	std::string clnt;
	mx.setHL(5);
	int xpointer = 1, xenter = 0;
	while (xpointer)
	{
		/****/
		list.clear();
		snlist.clear();
		list = _c.retAllClients(mysql);
		//std::cout << list.size();
		for (int i = 0; i < list.size(); i++)
		{
			clnt = list[i].surname + " " + list[i].name + " [" + list[i].login + "]";
			snlist.push_back(clnt);
		}
		snlist.push_back("Cofnij");
		mx.setOptionVector(snlist);
		/****/
		system("cls");
		std::cout << " --- USUN KLIENTA --- " << std::endl;
		mx.write(xpointer, xenter);
		mx.setPointer(xpointer, xenter);
		if (xenter == 1)
		{
			if (xpointer == mx.option.size()) xpointer = 0;
			else
			{
				client c(mysql, list[xpointer - 1].id_client);
				std::cout << c.id_user;
				if (!c._deleteC(mysql)) std::cout << "Usunieto klienta";
				else std::cout << "Nie mozna usunac";
				xenter = 0;
			}
		}
	}
}


void admin::addNewOffert(database& mysql)
{
	std::string input, input2;
	std::cout << std::endl;
	std::cout << " --- DODAWANIA NOWEJ POZYCJI DO OFERT --- " << std::endl;
	assortment _assortment;
	std::cout << "Podaj nazwe (np. roza, bukiet roz itd.): ";
	std::getline(std::cin, input);
	std::cout << "Podaj cene: ";
	std::getline(std::cin, input2);
	_assortment.count = "10";
	if (!validation::isAppropriateLength(input, 0, 40))
	{
		_assortment.name = input;
		if (!validation::isAppropriateLength(input2, 0, 40))
		{
			_assortment.price = input2;
			if (!_assortment._insert(mysql))
			{
				std::cout << "Dodano nowa pozycje do ofert";;
			}
		}
	}
}

void admin::deleteOffert(database& mysql)
{
	assortment _a;
	menu mx("Oferta");
	std::vector<std::string> snlist;
	std::vector<assortment> list;
	std::string assort;
	mx.setHL(5);
	int xpointer = 1, xenter = 0;
	while (xpointer)
	{
		/****/
		list.clear();
		snlist.clear();
		list = _a.retAllAssortment(mysql,"");
		for (int i = 0; i < list.size(); i++)
		{
			assort = list[i].name + " [" + list[i].price + " PLN]";
			snlist.push_back(assort);
		}
		snlist.push_back("Cofnij");
		mx.setOptionVector(snlist);
		/****/
		system("cls");
		std::cout << " --- USUN OFERTE --- " << std::endl;
		mx.write(xpointer, xenter);
		mx.setPointer(xpointer, xenter);
		if (xenter == 1)
		{
			if (xpointer == mx.option.size()) xpointer = 0;
			else
			{
				assortment a(mysql, list[xpointer - 1].id_assortment);
				if (!a._delete(mysql)) std::cout << "Usunieto oferte";
				else std::cout << "Nie mozna usunac";
				xenter = 0;
			}
		}
	}
}


void admin::cancelOrder(database mysql)
{
	order _a;
	menu mx("Zamowienia klientow");
	std::vector<std::string> snlist;
	std::vector<order> list;
	std::string assort;
	mx.setHL(5);
	int xpointer = 1, xenter = 0;
	while (xpointer)
	{
		/****/
		std::string stat;
		list.clear();
		snlist.clear();
		list = _a.retAllOrders(mysql, " where status in (0,1,2) ");
		for (int i = 0; i < list.size(); i++)
		{
			if (stoi(list[i].status) == 0) stat = "Oczekuje na potwierdzenie";
			else if (stoi(list[i].status) == 1) stat = "Potwierdzone - w realizacji";
			else if (stoi(list[i].status) == 2) stat = "Anulowane";
			else stat = "Nieokreslony";
			client _client(mysql, list[i].id_client);
			assort = "ZAMOWIENIE #" + list[i].id_order + " | ZLOZONO: " + list[i].date_order + " | PRZEZ " + _client.surname + " " + _client.name + " | " + stat;
			snlist.push_back(assort);
		}
		snlist.push_back("Cofnij");
		mx.setOptionVector(snlist);
		/****/
		system("cls");
		std::cout << " --- POTWIERDZ / ANULUJ ZAMOWIENIE --- " << std::endl;
		mx.write(xpointer, xenter);
		//mx.setPointer(xpointer, xenter);
		int it = _getch();
		if (it == 77)
		{
			order a(mysql, list[xpointer - 1].id_order);
			a.status = "0";
			a._update(mysql);
			xenter = 0;
		}
		else if (it == 75)
		{
			order a(mysql, list[xpointer - 1].id_order);
			if (!a._delete(mysql)) std::cout << "Anulowano zamowienie";
			else std::cout << "Nie mozna anulowac";
			xenter = 0;
		}
		if (it == 72)
		{
			if ((xpointer - 1) > 0) xpointer -= 1;
			else xpointer = snlist.size();
		}
		if (it == 80)
		{
			if (xpointer + 1 < snlist.size() + 1) xpointer += 1;
			else xpointer = 1;
		}
		if (it == 13) xenter = 1;

		if (xenter == 1)
		{
			if (xpointer == mx.option.size()) xpointer = 0;
			else
			{
				order a(mysql, list[xpointer - 1].id_order);
				a.status = "1";
				a._update(mysql);
				xenter = 0;
			}
		}
	}
}

void admin::writeOrders(database mysql)
{
	order _a;
	menu mx("Zamowienia zatwierdzone");
	std::vector<std::string> snlist;
	std::vector<order> list;
	std::string assort;
	mx.setHL(5);
	int xpointer = 1, xenter = 0;
	while (xpointer)
	{
		/****/
		std::string stat;
		list.clear();
		snlist.clear();
		list = _a.retAllOrders(mysql, " where status = 1");
		for (int i = 0; i < list.size(); i++)
		{
			assort = "ZAMOWIENIE #" + list[i].id_order + " | ZLOZONO: " + list[i].date_order;
			snlist.push_back(assort);
		}
		snlist.push_back("Cofnij");
		mx.setOptionVector(snlist);
		/****/
		system("cls");
		std::cout << " --- ZAMOWIENIA ZATWIERDZONE DO REALIZACJI --- " << std::endl;
		mx.write(xpointer, xenter);
		mx.setPointer(xpointer, xenter);
		if (xenter == 1)
		{
			if (xpointer == mx.option.size()) xpointer = 0;
			else
			{
				order a(mysql, list[xpointer - 1].id_order);
				std::cout << "\nPOZYCJE ZAMOWIENIA O NR " << a.id_order << " \n";
				for (int i = 0; i < a.pos_orders.size(); i++)
				{
					assortment assort(mysql, a.pos_orders[i].id_assortment);
					std::cout << "#" << i + 1 << ". " << assort.name << " " << assort.price << " PLN | " << "Ilosc: " << a.pos_orders[i].count << "\n";
				}
				std::cout << "LACZNE KOSZTY ZAMOWIENIA: " << a.cost << " PLN\n";
				_getch();
				xenter = 0;
			}
		}
	}
}

void admin::orderHistory(database mysql)
{
	order _a;
	menu mx("Zamowienia zrealizowane");
	std::vector<std::string> snlist;
	std::vector<order> list;
	std::string assort;
	mx.setHL(5);
	int xpointer = 1, xenter = 0;
	while (xpointer)
	{
		/****/
		std::string stat;
		list.clear();
		snlist.clear();
		list = _a.retAllOrders(mysql, " where status = 5");
		for (int i = 0; i < list.size(); i++)
		{
			assort = "ZAMOWIENIE #" + list[i].id_order + " | ZLOZONO: " + list[i].date_order;
			snlist.push_back(assort);
		}
		snlist.push_back("Cofnij");
		mx.setOptionVector(snlist);
		/****/
		system("cls");
		std::cout << " --- ZAMOWIENIA ZREALIZOWANE --- " << std::endl;
		mx.write(xpointer, xenter);
		mx.setPointer(xpointer, xenter);
		if (xenter == 1)
		{
			if (xpointer == mx.option.size()) xpointer = 0;
			else
			{
				order a(mysql, list[xpointer - 1].id_order);
				std::cout << "\nPOZYCJE ZAMOWIENIA O NR " << a.id_order << " \n";
				for (int i = 0; i < a.pos_orders.size(); i++)
				{
					assortment assort(mysql, a.pos_orders[i].id_assortment);
					std::cout << "#" << i + 1 << ". " << assort.name << " " << assort.price << " PLN | " << "Ilosc: " << a.pos_orders[i].count << "\n";
				}
				std::cout << "LACZNE KOSZTY ZAMOWIENIA: " << a.cost << " PLN\n";
				_getch();
				xenter = 0;
			}
		}
	}
}

void admin::realizeOrder(database mysql)
{
	order _a;
	menu mx("Zamowienia do realizacji");
	std::vector<std::string> snlist;
	std::vector<order> list;
	std::string assort;
	mx.setHL(5);
	int xpointer = 1, xenter = 0;
	while (xpointer)
	{
		/****/
		std::string stat;
		list.clear();
		snlist.clear();
		list = _a.retAllOrders(mysql, " where status = 1 ");
		for (int i = 0; i < list.size(); i++)
		{
			assort = "ZAMOWIENIE #" + list[i].id_order + " | ZLOZONO: " + list[i].date_order;
			snlist.push_back(assort);
		}
		snlist.push_back("Cofnij");
		mx.setOptionVector(snlist);
		/****/
		system("cls");
		std::cout << " --- ZREALZUJ ZAMOWIENIE --- " << std::endl;
		mx.write(xpointer, xenter);
		mx.setPointer(xpointer, xenter);
		if (xenter == 1)
		{
			if (xpointer == mx.option.size()) xpointer = 0;
			else
			{
				order a(mysql, list[xpointer - 1].id_order);
				a.status = "5";
				a._update(mysql);
				xenter = 0;
			}
		}
	}
}

void admin::mostPopularFlower(database &mysql)
{
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	std::vector<order> orderz;
	std::string query = "select flwr_assortment.name,sum(flwr_pos_order.id_assortment) as ile from flwr_pos_order inner join flwr_order on flwr_order.id_order = flwr_pos_order.id_order inner join flwr_assortment on flwr_pos_order.id_assortment = flwr_assortment.id_assortment where flwr_order.status = 5 group by flwr_assortment.id_assortment order by ile desc limit 5";
	mysql_query(mysql.connect, query.c_str());
	res_set = mysql_store_result(mysql.connect);
	int numrows = mysql_num_rows(res_set);
	int num_col = mysql_num_fields(res_set);
	int i = 0;
	int j = 0;
	order c;
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		i = 0;
		std::cout << j + 1 << ". ";
		while (i < num_col)
		{
			std::cout << " " << row[i] << " ";
			i++;
		}
		std::cout << "\n";
		j++;
	}
	_getch();
}

void admin::statSpendMoney(database &mysql)
{
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	std::vector<order> orderz;
	std::string query = "select flwr_client.name, flwr_client.surname, sum(flwr_order.cost) from flwr_order inner join flwr_client on flwr_client.id_client = flwr_order.id_client group by (flwr_client.id_client)";
	mysql_query(mysql.connect, query.c_str());
	res_set = mysql_store_result(mysql.connect);
	int numrows = mysql_num_rows(res_set);
	int num_col = mysql_num_fields(res_set);
	int i = 0;
	int j = 0;
	order c;
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		i = 0;
		std::cout << j + 1 << ". ";
		while (i < num_col)
		{
			std::cout << " " << row[i] << " ";
			i++;
		}
		std::cout << "\n";
		j++;
	}
	_getch();
}
	/*
	select flwr_assortment.name,sum(flwr_pos_order.id_assortment) from flwr_pos_order inner join flwr_order on flwr_order.id_order = flwr_pos_order.id_order inner join flwr_assortment on flwr_pos_order.id_assortment = flwr_assortment.id_assortment
where flwr_order.status = 5
group by flwr_assortment.id_assortment;

select flwr_assortment.name,sum(flwr_pos_order.id_assortment) as ile from flwr_pos_order inner join flwr_order on flwr_order.id_order = flwr_pos_order.id_order inner join flwr_assortment on flwr_pos_order.id_assortment = flwr_assortment.id_assortment
where flwr_order.status = 5
group by flwr_assortment.id_assortment
order by ile desc
limit 5;
	*/
