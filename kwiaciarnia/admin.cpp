#include "pch.h"
#include "admin.h"

typedef std::vector<std::string> obj;

admin::admin()
{

}

admin::admin(database mysql, std::string id_user)
{
	this->id_user = id_user;
	this->_setParameters(mysql);
}


admin::~admin()
{
}

bool admin::_setParameters(database & mysql)
{
	std::string query = "SELECT * FROM flwr_user WHERE id_user = '" + id_user + "';";
	obj ret = mysql.retRow(query);
	if (mysql.isExist(query))
	{
		this->login = ret[2];
		this->pass = ret[3];
		this->permission = ret[4];
		this->id_client = ret[5];

		return false;
	}
	else return true;
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