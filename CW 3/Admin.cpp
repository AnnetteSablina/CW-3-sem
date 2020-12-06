#include "Header.h"

int Admin::menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "       Меню Администратора:     " << "\n\n";
		key = (key + 8) % 8;
		if (key == 0) draw(" ->   Заключить новый договор.");
		else  cout << "   Заключить новый договор" << endl;

		if (key == 1) draw(" ->   Редактирование информации о пользователе. ");
		else  cout << "   Редактирование информации о пользователе. " << endl;

		if (key == 2)  draw(" ->   Просмотр заключённых договоров.");
		else  cout << "   Просмотр заключённых договоров." << endl;

		if (key == 3)  draw(" ->   Поиск и сортировка данных.");
		else  cout << "   Поиск и сортировка данных." << endl;

		if (key == 4)  draw(" ->   Добавление логина и пароля нового пользователя или информации о нем.");
		else  cout << "   Добавление логина и пароля нового пользователя или информации о нем." << endl;

		if (key == 5)  draw(" ->   Удаление пользователя из базы(производится в случае его смерти).");
		else  cout << "   Удаление пользователя из базы(производится в случае его смерти)." << endl;

		if (key == 6)  draw(" ->   Топ 10 самых активных клиентов.");
		else  cout << "   Топ 10 самых активных клиентов." << endl;

		if (key == 7)  draw(" ->   Вернуться в главное меню.");
		else  cout << "   Вернуться в главное меню." << endl;

		code = getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;

		
	} while (code != 13);
	system("cls");
	return key;
}
void Admin::enterAccount(std::vector<Human>& admins) {
	system("cls");
	bool access = true;
	bool exit = false;
	do {
		if (access) {
			login = BOO::login(1, exit);
		}
		if (!access) {
			login = BOO::login(2, exit);
		};
		if (exit) {
			break;
		};
		password = BOO::password(1,exit);
		if (exit) {
			break;
		};
		access = true;
		Human check(login, sha256(password));
		if (find(admins.begin(), admins.end(), check) == admins.end()) {
			access = false;
		}

	} while (!access);
	if (exit) {
		BOO::menu(0);
	}
	if (access) {
		BOO::menu(1);
	}

};
void Admin::conclusion_contract() {
	Human human;
	bool exit = false;
	bool check = true;

	string choice = yes_no("Пользователь уже зарегистрирован в системе? да/нет.");
	if (choice == "да") {
		check = human.check_login_once();
		if (!check) {
			system("cls");
			cout << "Пользователя с таким логином не существует." << endl;
			cout << "Добавьте его в базу." << endl;
			Sleep(2500);
			exit = add_logpass();
		}

	}
	else {
		system("cls");
		cout << "Добавьте информацию о пользователе." << endl;
		Sleep(2500);
		exit = add_logpass();
	}

	if (exit) { BOO::menu(1); return; }
	
	Sleep(2500);

	string choice_2 = yes_no("Пользователь имеет введенные данные в базе? да/нет");

	if (choice_2 == "да" || choice_2 == "нет") {
		check = add_client_code_into_contract();
		if (check) {
			system("cls");
			cout << "Информации об этом пользователе не было и вы добавили его идентификационный номер в базу." << endl;
			cout << "Добавим информацию о пользователе." << endl;
			system("pause");
			add_user_information_contract();
			cout << "Данные успешно добавлены." << endl;
			system("pause");
			add_dogovor();
		}
		else {
			system("cls");
			cout << "Данные клиента уже есть в базе." << endl;
			system("pause");
			add_dogovor();
		}
	}
    return;
}
bool Admin::add_logpass() {
	system("cls");
	bool access = true;
	bool exit = false;
	do {
		if (access) {
			login = BOO::login(1, exit);
		}
		else {
			login = BOO::login(3, exit);
		}
		if (exit) break;
		ifstream file("users.txt");
		while (file)
		{
			string tmp;
			getline(file, tmp);
			if (tmp == login)
			{
				access = false;
				break;
			}
			else {
				access = true;
			}
			getline(file, tmp);
		}
		file.close();
		if (access) {
			password = BOO::password(1,exit);
		}
		if (exit) break;
	} while (!access);
	if (!exit)
	{
		ofstream file1("users.txt", ios::app);
		file1 << login << endl << sha256(password) << endl;
		file1.close();
		system("cls");
		cout << "Вы добавили пользователя в базу." << endl;
	}
	return exit;
}
bool Admin::add_client_code_into_contract() {
	system("cls");
	int u = 0;
	bool next;
	std::vector<Client> passport;
	data_passport_file(passport);
	client_code = BOO::client_code("Введите номер паспорта.");
	for (auto i : passport) {
		if (i.client_code == client_code) {
			u++;
			system("cls");
			ofstream file2("dogovor.txt", ios::app);
			file2 << client_code << endl;
			file2.close();
			ofstream file3("magic.txt", ios::app);
			file3 << client_code << endl << i.name << endl << i.surname << endl;
			file3.close();
			next = false;
		}
	}
	if (u == 0) {
		ofstream file("passport.txt", ios::app);
		file << client_code << std::endl;
		file.close();
	    ofstream file1("dogovor.txt", ios::app);
		file1 << client_code << endl;
		file1.close();
		ofstream file4("magic.txt", ios::app);
		file4 << client_code << std::endl;
		file4.close();
		ofstream file5("info.txt", ios::app);
		file5 << client_code << endl;
		file5.close();
		next = true;
	}
	return next;
}
void Admin::add_user_information_contract() {
	system("cls");
	name = ccsns("Введите имя.");
	surname = ccsns("Введите фамилию.");
	telephone_number = hfst("Введите номер телефона клиента.",3);
	country = ccsns("Введите страну проживания");
	city = ccsns("Введите город проживания.");
	street = ccsns("Введите улицу проживания.");
	housenumber = hfst("Введите номер дома.",1);
	flatnumber = hfst("Введите номер квартиры. Введите 0, если клиент проживает в частном доме.",1);
	ofstream file("magic.txt", ios::app);
	file << name << endl << surname << endl;
	file.close();
	ofstream file1("info.txt", ios::app);
	file1 << name << endl << surname << endl << telephone_number << endl << country << endl << city << endl << street << endl << housenumber << endl << flatnumber << endl;
	file1.close();
	ofstream file2("passport.txt", ios::app);
	file2 << name << endl << surname << endl;
	file2.close();
	return;
}
void Admin::add_dogovor() {
	vector <Contract> documentCode;
	contract_code(documentCode);
	Contract contract;
	system("cls");
	std::cout << "Добавим данные договора." << std::endl;
	system("pause");
	contract.service_code = service_code("Введите номер услуги.\n 1111 - Доверенность. \n 2222 - Брачный договор. \n 3333 - Завещание. \n 4444 - Приватизация. \n 5555 - Исполнительные надписи. \n 6666 - Отчуждение недвижимого имущества. \n 7777 - Соглашение об уплате алиментов. \n 8888 - Соглашение на выезд ребенка из страны. \n 9999 - Согласие. ");
	contract.name = contract_name(contract.service_code);
	system("cls");
	contract.summ = hfst("Введите сумму до 100.000.000",2);
	contract.commition = hfst("Введите комиссионные.",2);
	ofstream file("dogovor.txt", ios::app);
	file << contract.service_code << endl << contract.name << endl << contract.summ << endl << contract.commition << endl;
	file.close();
	contract.add_document_code();
	Sleep(3000);
	BOO::choice(1);
}
void Admin::output(int type) {
	vector<Outputs<string>> dogovors;
	data_dogovor_file(dogovors);
	TablePrinter tp(&cout);
	tp.AddColumn("Номер паспорта", 14);
	tp.AddColumn("Код услуги", 10);
	tp.AddColumn("Название договора", 38);
	tp.AddColumn("Сумма", 9);
	tp.AddColumn("Комиссия", 9);
	tp.AddColumn("Номер договора", 14);
	tp.AddColumn("Дата подписания", 15);
	tp.PrintHeader();
	for (auto i : dogovors) {
		tp << i.client_code << i.service_code << i.name << i.summ << i.comission << i.document_code << i.date << bprinter::endl();
		tp.PrintFooter();
	}
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);
};
int Admin::find_sort_menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "     Ваш выбор:     " << "\n\n";
		key = (key + 7) % 7;
		if (key == 0) draw(" ->   Поиск договора по номеру договора.");
		else  cout << "   Поиск договора по номеру договора." << endl;

		if (key == 1) draw(" ->   Поиск договоров по номеру парпорта.  ");
		else  cout << "   Поиск договора по номеру парпорта. " << endl;

		if (key == 2)  draw(" ->   Поиск договоров по номеру услуги.");
		else  cout << "   Найти договор по дате заключения." << endl;

		if (key == 3)  draw(" ->   Поиск договоров по дате.");
		else  cout << "   Поиск договора по дате." << endl;

		if (key == 4)  draw(" ->   Просмотреть информацию о пользователе.");
		else  cout << "   Просмотреть информацию о пользователе." << endl;

		if (key == 5)  draw(" ->   Сортировать по коду услуги.");
		else  cout << "   Сортировать по коду услуги." << endl;

		if (key == 6)  draw(" ->   Вернуться в меню администратора.");
		else  cout << "   Вернуться в меню администратора." << endl;

		code = getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;

	} while (code != 13);
	system("cls");
	return key;
}
void Admin::find_service(int type) {
	system("cls");
	int u = 0;
	string service;
	service = service_code("Введите номер услуги.\n 1111 - Доверенность. \n 2222 - Брачный договор. \n 3333 - Завещание. \n 4444 - Приватизация. \n 5555 - Исполнительные надписи. \n 6666 - Отчуждение недвижимого имущества. \n 7777 - Соглашение об уплате алиментов. \n 8888 - Соглашение на выезд ребенка из страны. \n 9999 - Согласие. ");
	vector<Outputs<string>> dogovors;
	data_dogovor_file(dogovors);
	TablePrinter tp(&cout);
	tp.AddColumn("Код услуги", 11);
	tp.AddColumn("Название договора", 37);
	tp.AddColumn("Номер договора", 14);
	tp.AddColumn("Номер паспорта", 14);
	tp.AddColumn("Сумма", 9);
	tp.AddColumn("Комиссия", 9);
	tp.AddColumn("Дата подписания", 15);
	tp.PrintHeader();
	for (auto i : dogovors) {
		if (service == i.service_code) {
			u++;
			tp << i.service_code << i.name << i.document_code << i.client_code << i.summ << i.comission << i.date << bprinter::endl();
			tp.PrintFooter();
		}

	}
	if (u == 0) {
		tp << " " << bprinter::endl();
		tp.PrintFooter();
		cout << "Договор такого типа не заключался." << endl;
	}
	if (type == 1) BOO::choice(1);
	return;
}
void Admin::sort(int type) {
	system("cls");
	vector<Outputs<string>> dogovors;
	data_dogovor_file(dogovors);
	std::sort(dogovors.begin(), dogovors.end(), [](Outputs<string> & a, Outputs<string> & b) {
		return a.service_code < b.service_code;
		});
	TablePrinter tp(&cout);
	tp.AddColumn("Код услуги", 10);
	tp.AddColumn("Название договора", 38);
	tp.AddColumn("Номер договора", 14);
	tp.AddColumn("Номер паспорта", 14);
	tp.AddColumn("Сумма", 9);
	tp.AddColumn("Комиссия", 9);
	tp.AddColumn("Дата подписания", 15);
	tp.PrintHeader();
	for (auto i : dogovors) {
		tp << i.service_code << i.name << i.document_code << i.client_code << i.summ << i.comission << i.date << bprinter::endl();
		tp.PrintFooter();
	}
	if (type == 1) BOO::choice(1);
	return;
}
void Admin::top_10(int type) {
	Client temp;
	vector<Client> kolvo;
	vector<Client>userss;
	string client_code;
	data_contract_file(userss);
	int c;
again:
	for (auto i : userss) {
		client_code = i.client_code;
		c = 0;
		for (auto i : userss) {
			if (i.client_code == client_code)  c++;
		}
		userss.erase(remove_if(userss.begin(), userss.end(), [=](Client& i) { return i.client_code == client_code; }), userss.end());
		if (c >= 1) {
			temp.client_code = i.client_code;
			temp.name = i.name;
			temp.surname = i.surname;
			string a = to_string(c);
			temp.quantity = a;
			kolvo.push_back(temp);
		}
		goto again;
	}
	std::sort(kolvo.begin(), kolvo.end(), [](Client& a, Client& b) {
		return a.quantity > b.quantity;
	});
	if (kolvo.size() > 10) {
		kolvo.erase(kolvo.begin() + 10, kolvo.end());
	}
	TablePrinter tp(&cout);
	tp.AddColumn("Номер паспорта", 14);
	tp.AddColumn("Имя", 15);
	tp.AddColumn("Фамилия", 15);
	tp.AddColumn("Количество заключенных договоров", 35);
	tp.PrintHeader();
	for (auto i : kolvo) {
		tp << i.client_code << i.name << i.surname << i.quantity << bprinter::endl();
		tp.PrintFooter();
	}
	if (type == 1) BOO::choice(1);
	return;
};
void Admin::add_information(int type) {
	system("cls");
	Client user;
	vector<Client> passport;
	data_passport_file(passport);
	while (true) {
		int w = 0;
		user.client_code = BOO::client_code("Введите номер паспорта");
		system("cls");
		for (auto a : passport) {
			if (user.client_code == a.client_code) {
				w++;
				cout << "Такой номер паспорта уже существует. Повторите ввод.";
				break;
			}
		}
		if (w == 0) { break; }
		else { continue; }
	}
	user.name = ccsns("Введите имя.");
	user.surname = ccsns("Введите фамилию.");
	user.telephone_number = hfst("Введите номер телефона клиента.",3);
	user.country = ccsns("Введите страну проживания");
	user.city = ccsns("Введите город проживания.");
	user.street = ccsns("Введите улицу проживания.");
	user.housenumber = hfst("Введите номер дома.",1);
	user.flatnumber = hfst("Введите номер квартиры. Введите 0, если клиент проживает в частном доме.",1);
	ofstream file("info.txt", ios::app);
	file << user.client_code << endl << user.name << endl << user.surname << endl << user.telephone_number << endl << user.country << endl
		<< user.city << endl << user.street << endl << user.housenumber << endl << user.flatnumber << endl;
	file.close();
	ofstream file1("passport.txt", ios::app);
	file1 << user.client_code << endl << user.name << endl << user.surname << endl;
	file1.close();
	if (type == 1) BOO::choice(1);
	return;
}
void Admin::delete_user(int type){
	system("cls");
	string choice = yes_no("Вы точно уверены в том, что хотите удалить пользователя? \n 1.Введите 'да',если да \n 2.Введите 'нет',если нет или это было случайное нажатие. Вернуться в меню администратора.");
	if (choice == "нет")  BOO::menu(1);
	system("cls");
	bool exit = true;
    vector<Human> users;
	data_user_file(users);
	vector<Client> userss;
	data_client_file(userss);
	vector <Client> passport;
	data_passport_file(passport);
	string login = BOO::login(5,exit);
	int a = users.size();
	users.erase(remove_if(users.begin(), users.end(), [=](Human& s) { return s.login == login; }), users.end());
	int k = users.size();
	if (a == k) cout << "Пользователя с таким логином не существует." << endl;
	else {
		while (true) {
			string passport_code = BOO::client_code("Введите номер паспорта клиента");
			a = userss.size();
			userss.erase(remove_if(userss.begin(), userss.end(), [=](Client& a) { return a.client_code == passport_code; }), userss.end());
			k = userss.size();
			if (a == k) {
				cout << "Вы ввели некорректный номер паспорта повторите еще раз." << std::endl;
				continue;
			}
			else {
				passport.erase(remove_if(passport.begin(), passport.end(), [=](Client& r) { return r.client_code == passport_code; }), passport.end());
				rewrite_user_file(users);
				rewrite_information_file(userss);
				rewrite_passport_file(passport);
				break;
			}
		}
	}
	if (type == 1) BOO::choice(1);
	return;
}

