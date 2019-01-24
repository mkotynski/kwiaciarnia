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
		_getch();
		list = _c.retAllClients(mysql);
		std::cout << list.size();
		_getch();
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
				if (!c._delete(mysql)) std::cout << "Usunieto klienta";
				else std::cout << "Nie mozna usunac";
				_getch();
				xenter = 0;
			}
		}
	}
}