#include "pch.h"
#include "session.h"

typedef std::vector<std::string> obj;

session::session()
{
	this->permission = 0;
}


session::~session()
{
}

bool session::login(database &mysql)
{
	bool logged = 0;
	obj log;
	std::string login,pass;
	//login = "login";
	//pass = "haslo";
	std::string query;
	permission = 0;
	while (!logged)
	{
		system("cls");
		std::cout << " *******************************************************" << std::endl;
		std::cout << " *                                                     *" << std::endl;
		std::cout << " *                       Kwiaciarnia                   *" << std::endl;
		std::cout << " *                                                     *" << std::endl;
		std::cout << " *******************************************************" << std::endl << std::endl;
		std::cout << "---- PANEL LOGOWANIA ---- \n";
		std::cout << "Podaj login: ";
		getline(std::cin, login);
		std::cout << "Podaj haslo: ";
		getline(std::cin, pass);
		query = "SELECT * FROM `flwr_user` WHERE login = '" + login + "' and pass = '" + pass + "'";
		if (mysql.isExist(query))
		{
			logged = 1;
			log = mysql.retRow("SELECT * FROM `flwr_user` WHERE login = '" + login + "' and pass = '" + pass + "'");
			permission = std::stoi(log[4]);
		}
	}

	if (logged == 1)
	{
		if (permission == 0)
		{
			client _c(mysql, log[5]);
			this->_client = _c;
			return true;
		}
		if (permission == 1)
		{
			admin _a(mysql, log[1]);
			this->_admin = _a;
			return true;
		}

	}
	return false;
}

void session::works(database &mysql)
{
	if (permission == 0)
	{
		menu _menu("Panel klienta");
		_menu.setHL(6);
		_menu.type = 1;
		setMenu(_menu);
		int pointer = 1, enter = 0;
		while (pointer)
		{
			system("cls");
			std::cout << " --- PANEL KLIENTA --- \n\n";
			_menu.write(pointer, enter);
			_menu.setPointer(pointer, enter);
			if (enter == 1)
			{
				if (pointer == _menu.option.size()) pointer = 0;
				else getOptionForClient(mysql, _menu, pointer, enter);
				enter = 0;
			}
		}
	}
	if (permission == 1)
	{
		menu _menu("Panel admina");
		_menu.setHL(6);
		_menu.type = 1;
		setMenu(_menu);
		int pointer = 1, enter = 0;
		while (pointer)
		{
			system("cls");
			std::cout << " --- PANEL ADMINA --- \n\n";
			_menu.write(pointer, enter);
			_menu.setPointer(pointer, enter);
			if (enter == 1)
			{
				if (pointer == _menu.option.size()) pointer = 0;
				else getOptionForAdmin(mysql, _menu, pointer, enter);
				enter = 0;
			}
		}
	}
}

void session::setMenu(menu &m)
{
	if (permission == 0)
	{
		obj list = { "ZLOZ ZAMOWIENIE","TWOJE ZAMOWIENIA","ANULUJ ZAMOWIENIE","HISTORIA ZAMOWIEN", "WYSZUKIWARKA KWIATOW", "WYLOGUJ" };
		m.setOptionVector(list);
	}
	if (permission == 1)
	{
		obj list = { "ZMIEN STATUS ZAMOWIENIA", "ZAMOWIENIA ZATWIERDZONE", "HISTORIA ZAMOWIEN", "ZREALIZUJ ZAMOWIENIE", "DODAJ KLIENTA","EDYTUJ KLIENTA","USUN KLIENA","DODAJ NOWA OFERTE", "USUN OFERTE", "NAJPOPULARNIEJSZE KWIATKI","ZESTAWIENIE KLIENTOW Z NAJWIEKSZYMI WYDATKAMI", "WYLOGUJ" };
		m.setOptionVector(list);
	}
}


void session::getOptionForClient(database mysql, menu m, int &pointer, int &enter)
{
	switch (pointer)
	{
	case 1: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_client.makeOrder(mysql);
		//_getch();
	}; break;
	case 2: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_client.writeOrders(mysql);
		//_getch();
	}; break;
	case 3: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_client.cancelOrder(mysql);
		//_getch();
	}; break;
	case 4: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_client.orderHistory(mysql);
		//_getch();
	}; break;
	case 5: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_client.searchFlower(mysql);
		//_getch();
	}; break;
	}
	enter = 0;
}


void session::getOptionForAdmin(database mysql, menu m, int &pointer, int &enter)
{
	switch (pointer)
	{
	case 1: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.cancelOrder(mysql);
		//_getch();
	}; break;
	case 2: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.writeOrders(mysql);
		//_getch();
	}; break;
	case 3: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.orderHistory(mysql);
		//_getch();
	}; break;
	case 4: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.realizeOrder(mysql);
		//_getch();
	}; break;
	case 5: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.addNewClient(mysql);
		//_getch();
	}; break;
	case 6: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.editClient(mysql);
		//_getch();
	}; break;
	case 7: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.deleteClient(mysql);
		//_getch();
	}; break;
	case 8: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.addNewOffert(mysql);
		//_getch();
	}; break;
	case 9: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.deleteOffert(mysql);
		//_getch();
	}; break;
	case 10: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.mostPopularFlower(mysql);
		//_getch();
	}; break;
	case 11: {
		std::cout << std::endl;
		std::cout << " --- " << m.option[pointer - 1] << " --- " << std::endl;
		_admin.statSpendMoney(mysql);
		//_getch();
	}; break;
	}
	enter = 0;
}
