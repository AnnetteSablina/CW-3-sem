#include "Header.h"

bool Human::check_login_once() {
	system("cls");
	bool check = true;
	bool access = true;
	bool exit = false;
	Client client;
	Admin admin;
	do {
		if (access)client.login = BOO::login(1, exit);
	
		if (exit) break;
		access = true;
		vector<Human> users;
		data_user_file(users);
		if (users.empty()) {
			check = false;
		}
		for (auto i : users)
		{
			if (i.login == client.login)
			{
				system("cls");
				cout << "ѕользователь с таким логином действительно есть." << endl;
				check = true;
				access = true;
				break;
			}
			else {
				check = false;
			}
		}
	} while (!access);
	if (exit) {
		BOO::menu(1);
	}
	return check;
}