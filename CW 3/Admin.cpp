#include "Header.h"

int Admin::menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "       ���� ��������������:     " << "\n\n";
		key = (key + 8) % 8;
		if (key == 0) draw(" ->   ��������� ����� �������.");
		else  cout << "   ��������� ����� �������" << endl;

		if (key == 1) draw(" ->   �������������� ���������� � ������������. ");
		else  cout << "   �������������� ���������� � ������������. " << endl;

		if (key == 2)  draw(" ->   �������� ����������� ���������.");
		else  cout << "   �������� ����������� ���������." << endl;

		if (key == 3)  draw(" ->   ����� � ���������� ������.");
		else  cout << "   ����� � ���������� ������." << endl;

		if (key == 4)  draw(" ->   ���������� ������ � ������ ������ ������������ ��� ���������� � ���.");
		else  cout << "   ���������� ������ � ������ ������ ������������ ��� ���������� � ���." << endl;

		if (key == 5)  draw(" ->   �������� ������������ �� ����(������������ � ������ ��� ������).");
		else  cout << "   �������� ������������ �� ����(������������ � ������ ��� ������)." << endl;

		if (key == 6)  draw(" ->   ��� 10 ����� �������� ��������.");
		else  cout << "   ��� 10 ����� �������� ��������." << endl;

		if (key == 7)  draw(" ->   ��������� � ������� ����.");
		else  cout << "   ��������� � ������� ����." << endl;

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

	string choice = yes_no("������������ ��� ��������������� � �������? ��/���.");
	if (choice == "��") {
		check = human.check_login_once();
		if (!check) {
			system("cls");
			cout << "������������ � ����� ������� �� ����������." << endl;
			cout << "�������� ��� � ����." << endl;
			Sleep(2500);
			exit = add_logpass();
		}

	}
	else {
		system("cls");
		cout << "�������� ���������� � ������������." << endl;
		Sleep(2500);
		exit = add_logpass();
	}

	if (exit) { BOO::menu(1); return; }
	
	Sleep(2500);

	string choice_2 = yes_no("������������ ����� ��������� ������ � ����? ��/���");

	if (choice_2 == "��" || choice_2 == "���") {
		check = add_client_code_into_contract();
		if (check) {
			system("cls");
			cout << "���������� �� ���� ������������ �� ���� � �� �������� ��� ����������������� ����� � ����." << endl;
			cout << "������� ���������� � ������������." << endl;
			system("pause");
			add_user_information_contract();
			cout << "������ ������� ���������." << endl;
			system("pause");
			add_dogovor();
		}
		else {
			system("cls");
			cout << "������ ������� ��� ���� � ����." << endl;
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
		cout << "�� �������� ������������ � ����." << endl;
	}
	return exit;
}
bool Admin::add_client_code_into_contract() {
	system("cls");
	int u = 0;
	bool next;
	std::vector<Client> passport;
	data_passport_file(passport);
	client_code = BOO::client_code("������� ����� ��������.");
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
	name = ccsns("������� ���.");
	surname = ccsns("������� �������.");
	telephone_number = hfst("������� ����� �������� �������.",3);
	country = ccsns("������� ������ ����������");
	city = ccsns("������� ����� ����������.");
	street = ccsns("������� ����� ����������.");
	housenumber = hfst("������� ����� ����.",1);
	flatnumber = hfst("������� ����� ��������. ������� 0, ���� ������ ��������� � ������� ����.",1);
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
	std::cout << "������� ������ ��������." << std::endl;
	system("pause");
	contract.service_code = service_code("������� ����� ������.\n 1111 - ������������. \n 2222 - ������� �������. \n 3333 - ���������. \n 4444 - ������������. \n 5555 - �������������� �������. \n 6666 - ���������� ����������� ���������. \n 7777 - ���������� �� ������ ���������. \n 8888 - ���������� �� ����� ������� �� ������. \n 9999 - ��������. ");
	contract.name = contract_name(contract.service_code);
	system("cls");
	contract.summ = hfst("������� ����� �� 100.000.000",2);
	contract.commition = hfst("������� ������������.",2);
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
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("��� ������", 10);
	tp.AddColumn("�������� ��������", 38);
	tp.AddColumn("�����", 9);
	tp.AddColumn("��������", 9);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("���� ����������", 15);
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
		cout << "     ��� �����:     " << "\n\n";
		key = (key + 7) % 7;
		if (key == 0) draw(" ->   ����� �������� �� ������ ��������.");
		else  cout << "   ����� �������� �� ������ ��������." << endl;

		if (key == 1) draw(" ->   ����� ��������� �� ������ ��������.  ");
		else  cout << "   ����� �������� �� ������ ��������. " << endl;

		if (key == 2)  draw(" ->   ����� ��������� �� ������ ������.");
		else  cout << "   ����� ������� �� ���� ����������." << endl;

		if (key == 3)  draw(" ->   ����� ��������� �� ����.");
		else  cout << "   ����� �������� �� ����." << endl;

		if (key == 4)  draw(" ->   ����������� ���������� � ������������.");
		else  cout << "   ����������� ���������� � ������������." << endl;

		if (key == 5)  draw(" ->   ����������� �� ���� ������.");
		else  cout << "   ����������� �� ���� ������." << endl;

		if (key == 6)  draw(" ->   ��������� � ���� ��������������.");
		else  cout << "   ��������� � ���� ��������������." << endl;

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
	service = service_code("������� ����� ������.\n 1111 - ������������. \n 2222 - ������� �������. \n 3333 - ���������. \n 4444 - ������������. \n 5555 - �������������� �������. \n 6666 - ���������� ����������� ���������. \n 7777 - ���������� �� ������ ���������. \n 8888 - ���������� �� ����� ������� �� ������. \n 9999 - ��������. ");
	vector<Outputs<string>> dogovors;
	data_dogovor_file(dogovors);
	TablePrinter tp(&cout);
	tp.AddColumn("��� ������", 11);
	tp.AddColumn("�������� ��������", 37);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("�����", 9);
	tp.AddColumn("��������", 9);
	tp.AddColumn("���� ����������", 15);
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
		cout << "������� ������ ���� �� ����������." << endl;
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
	tp.AddColumn("��� ������", 10);
	tp.AddColumn("�������� ��������", 38);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("�����", 9);
	tp.AddColumn("��������", 9);
	tp.AddColumn("���� ����������", 15);
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
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("���", 15);
	tp.AddColumn("�������", 15);
	tp.AddColumn("���������� ����������� ���������", 35);
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
		user.client_code = BOO::client_code("������� ����� ��������");
		system("cls");
		for (auto a : passport) {
			if (user.client_code == a.client_code) {
				w++;
				cout << "����� ����� �������� ��� ����������. ��������� ����.";
				break;
			}
		}
		if (w == 0) { break; }
		else { continue; }
	}
	user.name = ccsns("������� ���.");
	user.surname = ccsns("������� �������.");
	user.telephone_number = hfst("������� ����� �������� �������.",3);
	user.country = ccsns("������� ������ ����������");
	user.city = ccsns("������� ����� ����������.");
	user.street = ccsns("������� ����� ����������.");
	user.housenumber = hfst("������� ����� ����.",1);
	user.flatnumber = hfst("������� ����� ��������. ������� 0, ���� ������ ��������� � ������� ����.",1);
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
	string choice = yes_no("�� ����� ������� � ���, ��� ������ ������� ������������? \n 1.������� '��',���� �� \n 2.������� '���',���� ��� ��� ��� ���� ��������� �������. ��������� � ���� ��������������.");
	if (choice == "���")  BOO::menu(1);
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
	if (a == k) cout << "������������ � ����� ������� �� ����������." << endl;
	else {
		while (true) {
			string passport_code = BOO::client_code("������� ����� �������� �������");
			a = userss.size();
			userss.erase(remove_if(userss.begin(), userss.end(), [=](Client& a) { return a.client_code == passport_code; }), userss.end());
			k = userss.size();
			if (a == k) {
				cout << "�� ����� ������������ ����� �������� ��������� ��� ���." << std::endl;
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

