#include "Header.h"

int Client::menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		cout << "     ���� ������������:     " << "\n\n";
		key = (key + 7) % 7;
		if (key == 0) draw(" ->   ����� ������� �� ��� ������");
		else  cout << "   ����� ������� �� ��� ������" << endl;

		if (key == 1) draw(" ->   ����� ������� �� ������ ��������. ");
		else  cout << "   ����� ������� �� ������ ��������. " << endl;

		if (key == 2)  draw(" ->   ����� ������� �� ���� ����������.");
		else  cout << "   ����� ������� �� ���� ����������." << endl;

		if (key == 3)  draw(" ->   ���������� ���������� � ����.");
		else  cout << "   ���������� ���������� � ����." << endl;

		if (key == 4)  draw(" ->   �������� ����� ��� ������.");
		else  cout << "   �������� ����� ��� ������." << endl;

		if (key == 5)  draw(" ->   �������� ���������� � ����.");
		else  cout << "   �������� ���������� � ����." << endl;

		if (key == 6)  draw(" ->   ����� � ������� ����.");
		else  cout << "   ����� � ������� ����." << endl;

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
	if (a == k) cout << "�� ����� ������������ ������. ������������ � ����� ������� �� ����������." << endl;
	if (a != k) {
		while (true) {
			system("cls");
			cout << " �������:  \n 1.���� ������ �������� ������.\n 2.���� ������ �������� ����� � ������. " << endl;
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
	string passport_code = BOO::client_code("������� ����� �������� ��� ���������� ����������.");
	int a = userss.size();
	userss.erase(remove_if(userss.begin(), userss.end(), [=](Client& s) { return s.client_code == passport_code; }), userss.end());
	int k = userss.size();
	if (k != a) {
		Client temp;
		temp.client_code = passport_code;
		temp.name = ccsns("������� ���.");
		temp.surname = ccsns("������� �������.");
		temp.telephone_number = hfst("������� ����� ��������.",3);
		temp.country = ccsns("������� ������ ����������.");
		temp.city = ccsns("������� ����� ����������.");
		temp.street = ccsns("������� ����� ����������.");
		temp.housenumber = hfst("������� ����� ����.",1);
		temp.flatnumber = hfst("������� ����� ��������, ������� 0 ,���� ������ ��������� � ������� ����.",1);
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
	else cout << "������ ������ �������� � ������������ ���� ���." << endl;
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
	vector<Outputs<string>> dogovors;
	data_dogovor_file(dogovors);
	TablePrinter tp(&cout);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("��� ������", 10);
	tp.AddColumn("�������� ��������", 38);
	tp.AddColumn("�����", 9);
	tp.AddColumn("��������", 9);
	tp.AddColumn("���� ����������", 15);
	tp.AddColumn("����� ��������", 14);
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
		cout << "������ ������ �������� � ���� �� ����������." << endl;
	}
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);
	return;
}
void Client::find_passport(int type) {
	system("cls");
	int u = 0;
	string passport_code;
	passport_code = BOO::client_code("������� ����� ��������.");
	std::vector<Outputs<string>> dogovors;
	data_dogovor_file(dogovors);
	TablePrinter tp(&cout);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("��� ������", 10);
	tp.AddColumn("�������� ��������", 38);
	tp.AddColumn("�����", 9);
	tp.AddColumn("��������", 9);
	tp.AddColumn("���� ����������", 15);
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
		cout << "�� ���� ����� �������� �� ��������������� �������." << endl;
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
	if (type == 2) this->client_code = BOO::client_code("������� ���� ����� ��������.");
	years = year("������� ���:");
	if (years % 4 == 0) {
		system("cls");
		isLeap = true;
	}
	if (years % 100 == 0) {
		if (years % 400 == 0) isLeap = true;
		else isLeap = false;
	}
	months = month("������� �����:");
	days = day("������� ����:", isLeap, months);
	string date = to_string_date(days, months, years);
	vector<Outputs<string>> dogovors;
	data_dogovor_file(dogovors);
	TablePrinter tp(&cout);
	tp.AddColumn("���� ����������", 15);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("��� ������", 10);
	tp.AddColumn("�������� ��������", 38);
	tp.AddColumn("�����", 9);
	tp.AddColumn("��������", 9);
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
		cout << "� ����� ���� ������� �� ���������." << endl;
	}
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);
	return;
}
void Client::find_user(int type) {
	system("cls");
	int u = 0;
	string passport;
	passport = BOO::client_code("������� ����� ��������.");
	std::vector<Client> info;
	data_client_file(info);
	TablePrinter tp(&std::cout);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("��� � �������", 15);
	tp.AddColumn("����� ��������", 14);
	tp.AddColumn("������ � �����", 20);
	tp.AddColumn("�����", 20);
	tp.AddColumn("����� ����", 10);
	tp.AddColumn("����� ��������", 14);
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
		std::cout << "����� ������ �������� ��� � ����." << std::endl;
	}
	if (type == 1) BOO::choice(1);
	else BOO::choice(2);
	return;
}
