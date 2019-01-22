// kwiaciarnia.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "database.h"
#include "session.h"

#include "user.h"

int main()
{
	database mysql;

	user uz;

/*	uz.login = "jakislogin";
	uz.pass = "haslo";
	uz.permission = "0";
	uz.id_client = "1";

	std::cout << uz._insert(mysql);*/

	session ses;
	if (ses.login(mysql))
		ses.works(mysql);
}