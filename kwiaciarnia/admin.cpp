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
				_getch();
				if (!c._deleteC(mysql)) std::cout << "Usunieto klienta";
				else std::cout << "Nie mozna usunac";
				_getch();
				xenter = 0;
			}
		}
	}
}


void admin::addNewOffert(database& mysql)
{
	std::cout << std::endl;
	std::cout << " --- DODAWANIA NOWEJ POZYCJI OFERT --- " << std::endl;
	assortment _assortment;
	std::cout << "Podaj nazwe (np. roza, bukiet roz itd.): ";
	std::getline(std::cin, _assortment.name);
	std::cout << "Podaj cene: ";
	std::getline(std::cin, _assortment.price);
	_assortment.count = "10";
	if (!_assortment._insert(mysql))
	{
		std::cout << "Dodano nowa pozycje do ofert";;
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
		list = _a.retAllOrders(mysql, " where status in (0,1) ");
		for (int i = 0; i < list.size(); i++)
		{
			if (stoi(list[i].status) == 0) stat = "Oczekuje na potwierdzenie";
			else if (stoi(list[i].status) == 1) stat = "Potwierdzone - w realizacji";
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
		mx.setPointer(xpointer, xenter);
		int it = _getch();
		if (it == 77)
		{
			order a(mysql, list[xpointer - 1].id_order);
			a.status = "1";
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
				xenter = 0;
			}
		}
	}
}