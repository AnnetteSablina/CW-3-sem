#include "Header.h"
int Client::menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "     Меню Пользователя:     " << "\n\n";
		key = (key + 7) % 7;
		if (key == 0) draw(" ->   Найти договор по его номеру");
		else  cout << "   Найти договор по его номеру" << endl;

		if (key == 1) draw(" ->   Найти договор по номеру паспорта. ");
		else  cout << "   Найти договор по номеру паспорта. " << endl;

		if (key == 2)  draw(" ->   Найти договор по дате заключения.");
		else  cout << "   Найти договор по дате заключения." << endl;

		if (key == 3)  draw(" ->   Посмотреть информацию о себе.");
		else  cout << "   Посмотреть информацию о себе." << endl;

		if (key == 4)  draw(" ->   Изменить логин или пароль.");
		else  cout << "   Изменить логин или пароль." << endl;

		if (key == 5)  draw(" ->   Изменить информацию о себе.");
		else  cout << "   Изменить информацию о себе." << endl;

		if (key == 6)  draw(" ->   Выйти в главное меню.");
		else  cout << "   Выйти в главное меню." << endl;

		code = getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;
	
	} while (code != 13);
	system("cls");
	return key;
}
void Client::enterAccount(vector<Human>&users) {
	system("cls");
	bool access = true;
	bool exit = false;
	do {
		if (access) {
			login = BOO::login(1, exit);
		}
		else {
			login = BOO::login(2, exit);
		};
		if (exit) break;
	    password = BOO::password(1,exit);
		if (exit) break;
		access = true;
		Human check(login, sha256(password));
		if (find(users.begin(), users.end(), check) == users.end()) access = false;

	} while (!access);
	if (exit) {
		BOO::menu(0);
	};
	if (access) {
		BOO::menu(2);
	}
}
void Client::changelogpass(int type) {
	system("cls");
	bool access = true;
	bool exit = false;
	Human temp;
	vector<Human> users;
	data_user_file(users);
	string choice;
	string login = BOO::login(4, exit);
	system("cls");
	int a = users.size();
	users.erase(std::remove_if(users.begin(), users.end(), [=](Human& a) { return a.login == login; }), users.end());
	int k = users.size();
	if (a == k) cout << "Вы ввели некорректные данные. Пользователя с таким логином не существует." << endl;
	if (a != k) {
		while (true) {
			system("cls");
			cout << " Введите:  \n 1.Если хотите изменить пароль.\n 2.Если хотите изменить логин и пароль. " << endl;
			getline(cin, choice);
			if (choice != "1" && choice != "2") continue;
			else break;
		}
		if (choice == "1") {
			system("cls");
			temp.login = login;
			temp.password = sha256(BOO::password(2,exit));
		}
		if (choice == "2") {
			system("cls");
			temp.login = BOO::login(4, exit);
			temp.password = sha256(BOO::password(2,exit));
		}
		users.push_back(temp);
		rewrite_user_file(users);
	}
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);

} 
void Client::changeinfo(int type) {
	system("cls");
	vector<Client> userss;
	data_client_file(userss);
	string passport_code = BOO::client_code("Введите номер паспорта для обновления информации.");
	int a = userss.size();
	userss.erase(remove_if(userss.begin(), userss.end(), [=](Client& s) { return s.client_code == passport_code; }), userss.end());
	int k = userss.size();
	if (k != a) {
		Client temp;
		temp.client_code = passport_code;
		temp.name = ccsns("Введите имя.");
		temp.surname = ccsns("Введите фамилию.");
		temp.telephone_number = stoi(hfst("Введите номер телефона.",3));
		temp.country = ccsns("Введите страну проживания.");
		temp.city = ccsns("Введите город проживания.");
		temp.street = ccsns("Введите улицу проживания.");
		temp.housenumber = stoi(hfst("Введите номер дома.",1));
		temp.flatnumber = stoi(hfst("Введите номер квартиры, введите 0 ,если клиент проживает в частном доме.",1));
		userss.push_back(temp);
		rewrite_information_file(userss);
		vector <Client> passport;
		data_passport_file(passport);
		passport.erase(remove_if(passport.begin(), passport.end(), [=](Client& s) { return s.client_code == passport_code; }), passport.end());
		Client tmp;
		tmp.client_code = passport_code;
		tmp.name = temp.name;
		tmp.surname = temp.surname;
		passport.push_back(tmp);
		rewrite_passport_file(passport);
		vector <Client> magic;
		data_contract_file(magic);
		int n = 0;
		for (auto i : magic) {
			if (i.client_code == passport_code) n++;
		}
		magic.erase(std::remove_if(magic.begin(), magic.end(), [=](Client& s) { return s.client_code == passport_code; }), magic.end());
		for (int i = 0; i < n; i++) {
			magic.push_back(tmp);
		}
		rewrite_contract_file(magic);
	}
	else cout << "Такого номера паспорта в нотариальной базе нет." << endl;
	system("pause");
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);
	return;
}
void Client::find_contract_number(int type) {
	system("cls");
	int u = 0;
	bool access = true;
	string dogovor_number;
	dogovor_number = BOO::contract_code(1, access);
	vector<Outputs> dogovors;
	data_dogovor_file(dogovors);
	TablePrinter tp(&cout);
	tp.AddColumn("Номер договора", 14);
	tp.AddColumn("Код услуги", 10);
	tp.AddColumn("Название договора", 38);
	tp.AddColumn("Сумма", 9);
	tp.AddColumn("Комиссия", 9);
	tp.AddColumn("Дата подписания", 15);
	tp.AddColumn("Номер паспорта", 14);
	tp.PrintHeader();
	for (auto i : dogovors) {
		if (dogovor_number == i.document_code) {
			u++;
			tp << i.document_code << i.service_code << i.name << i.summ << i.comission << i.date << i.client_code << bprinter::endl();
			tp.PrintFooter();
		}
	}
	if (u == 0) {
		tp << " " << bprinter::endl();
		tp.PrintFooter();
		cout << "Такого номера договора в базе не существует." << endl;
	}
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);
	return;
}
void Client::find_passport(int type) {
	system("cls");
	int u = 0;
	string passport_code;
	passport_code = BOO::client_code("Введите номер паспорта.");
	std::vector<Outputs> dogovors;
	data_dogovor_file(dogovors);
	TablePrinter tp(&cout);
	tp.AddColumn("Номер паспорта", 14);
	tp.AddColumn("Номер договора", 14);
	tp.AddColumn("Код услуги", 10);
	tp.AddColumn("Название договора", 38);
	tp.AddColumn("Сумма", 9);
	tp.AddColumn("Комиссия", 9);
	tp.AddColumn("Дата подписания", 15);
	tp.PrintHeader();
	for (auto i : dogovors) {
		if (passport_code == i.client_code) {
			u++;
			tp << i.client_code << i.document_code << i.service_code << i.name << i.summ << i.comission << i.date << bprinter::endl();
			tp.PrintFooter();
		}
	}
	if (u == 0) {
		tp << " " << bprinter::endl();
		tp.PrintFooter();
		cout << "На этот номер паспорта не зарегистрирован договор." << endl;
	}
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);
	return;
}
void Client::find_date(int type) {
	system("cls");
	int u = 0;
	bool isLeap = true;
	int days, months, years;
	if (type == 2) this->client_code = BOO::client_code("Введите свой номер паспорта.");
	years = year("Введите год:");
	if (years % 4 == 0) {
		system("cls");
		isLeap = true;
	}
	if (years % 100 == 0) {
		if (years % 400 == 0) isLeap = true;
		else isLeap = false;
	}
	months = month("Введиет месяц:");
	days = day("Введите день:", isLeap, months);
	string date = to_string_date(days, months, years);
	vector<Outputs> dogovors;
	data_dogovor_file(dogovors);
	TablePrinter tp(&cout);
	tp.AddColumn("Дата подписания", 15);
	tp.AddColumn("Номер паспорта", 14);
	tp.AddColumn("Номер договора", 14);
	tp.AddColumn("Код услуги", 10);
	tp.AddColumn("Название договора", 38);
	tp.AddColumn("Сумма", 9);
	tp.AddColumn("Комиссия", 9);
	tp.PrintHeader();
	if (type == 2) {
		for (auto i : dogovors) {
			if (date == i.date && this->client_code == i.client_code) {
				u++;
				tp << i.date << i.client_code << i.document_code << i.service_code << i.name << i.summ << i.comission << bprinter::endl();
				tp.PrintFooter();
			}
		}
	} 
	else {
		for (auto i : dogovors) {
			if (date == i.date) {
				u++;
				tp << i.date << i.client_code << i.document_code << i.service_code << i.name << i.summ << i.comission << bprinter::endl();
				tp.PrintFooter();
			}
		}
	}
	if (u == 0) {
		tp << " " << bprinter::endl();
		tp.PrintFooter();
		cout << "В такой день договор не заключали." << endl;
	}
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);
	return;
}
void Client::find_user(int type) {
	system("cls");
	int u = 0;
	string passport;
	passport = BOO::client_code("Введите номер паспорта.");
	std::vector<Client> info;
	data_client_file(info);
	TablePrinter tp(&std::cout);
	tp.AddColumn("Номер паспорта", 14);
	tp.AddColumn("Имя и Фамилия", 15);
	tp.AddColumn("Номер телефона", 14);
	tp.AddColumn("Страна и Город", 20);
	tp.AddColumn("Улица", 20);
	tp.AddColumn("Номер дома", 10);
	tp.AddColumn("Номер квартиры", 14);
	tp.PrintHeader();
	for (auto i : info) {
		if (passport == i.client_code) {
			u++;
			tp << i.client_code << i.name << i.telephone_number << i.country << i.street << i.housenumber << i.flatnumber << bprinter::endl();
			tp << " " << i.surname << " " << i.city << " " << " " << " " << bprinter::endl(); ;
			tp.PrintFooter();
		}

	}
	if (u == 0) {
		tp << " " << bprinter::endl();
		tp.PrintFooter();
		std::cout << "Этого номера паспорта нет в базе." << std::endl;
	}
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);
	return;
}
