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

	session ses;
	if (ses.login(mysql))
		ses.works(mysql);
}