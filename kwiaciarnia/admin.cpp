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