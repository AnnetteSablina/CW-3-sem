#include "Header.h"

int menu_1(int mode) {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 3) % 3;
		if (mode == 0) {
			if (key == 0) draw(" ->   ����� �� ����� ��������������");
			else  cout << "   ����� �� ����� ��������������" << endl;

			if (key == 1 ) draw(" ->   ����� �� ����� ������������ ");
			else  cout << "   ����� �� ����� ������������ " << endl;


			if (key == 2 && mode == 0)  draw(" ->   ����� �� ���������");
			else  cout << "   ����� �� ���������" << endl;
		}
		
		if (mode == 1) {

			if (key == 0) draw(" ->   �������� ����� � ������ ������������");
			else cout << "   �������� ����� � ������ ������ ������������ " << endl;

			if (key == 1) draw("->   �������� ���������� � ������������");
			else  cout << "   �������� ���������� � ������������ " << endl;

			if (key == 2 )  draw(" ->   ��������� � ���� ��������������");
			else  cout << "   ��������� � ���� ��������������" << endl;
		}

		if (mode == 2) {

			if (key == 0) draw(" ->   �������� ����� � ������ ������������");
			else cout << "   �������� ����� � ������ ������������ " << endl;

			if (key == 1) draw("->   �������� ���������� � ������������");
			else  cout << "   �������� ���������� � ������������ " << endl;

			if (key == 2 )  draw(" ->   ��������� � ���� ��������������");
			else  cout << "   ��������� � ������� ��������������" << endl;
		}
		
		code = getch();
		if (code == 80 || code == 115) key++;
		if (code == 72 || code == 119) key--;
		
	} while (code != 13);
	system("cls");
	return key;
}
void BOO::menu(int a) {
	vector<Human>admins;
	data_admin_file(admins);
	vector <Human> users;
	data_user_file(users);
	Client client;
	Admin admin;

	if (a == 0) { //���� ������� ������
		int answer = menu_1(0);
		switch (answer)
		{
		case 0: admin.enterAccount(admins); break;
		case 1: client.enterAccount(users); break;
		case 2: {cout << "\n �� ������� ����� �� ���������." << endl; exit(0); } break;
		}
	}

	if (a == 1) { // ���� ������
		int answer = admin.menu();
		switch (answer)
		{
		case 0: admin.conclusion_contract(); break;
		case 1: BOO::menu(3); break;
		case 2: admin.output(1); break;
		case 3: BOO::menu(4); break;
		case 4: BOO::menu(5); break;
		case 5: admin.delete_user(1); break;
		case 6: admin.top_10(1); break;
		case 7: BOO::menu(0); break;
	    }
    }

	if (a == 2) { // ���� ������������
		int answer = client.menu(); 
		switch (answer)
		{
		case 0: client.find_contract_number(2); break;
		case 1: client.find_passport(2); break;
		case 2: client.find_date(2); break;
		case 3: client.find_user(2); break;
		case 4: client.changelogpass(2); break;
		case 5: client.changeinfo(2); break;
		case 6: BOO::menu(0); break;
		}
	}
	if (a == 3) {
		int answer = menu_1(2);
		switch (answer) {
		case 0: admin.changelogpass(1); break;
		case 1: admin.changeinfo(1); break;
		case 2: BOO::menu(1); break;
		}
	}
	if (a == 4) {
		int answer = admin.find_sort_menu();
		switch (answer){
		case 0: admin.find_contract_number(1); break;
		case 1: admin.find_passport(1); break;
		case 2: admin.find_service(1); break;
		case 3: admin.find_date(1); break;
		case 4: admin.find_user(1); break;
		case 5: admin.sort(1); break;
		case 6: BOO::menu(1); break;
		}
	}
	if (a == 5) {
		int answer = menu_1(1);
		switch (answer) {
		case 0: {
			bool n = admin.add_logpass();
			if (n)  BOO::menu(1); 
			else  BOO::choice(1);
			break;
		}
		case 1: admin.add_information(1); break;
		case 2: BOO::menu(1); break;
		}
	}
	return;
}
void draw(string string) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED);
	cout << "\n" << string << "\n\n";
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
}
string BOO::login(int type, bool& exit) {
	int u = 0;
	string login;
	switch (type) {
	case 1:
		system("cls");
		login = getString(" ������� �����.��� ������ ������� menu.");
		break;
	case 2:
		system("cls");
		login = getString(" �� ����� �������� ����� ��� ������. ������� ����� ��� ���. ��� ������ ������� menu.");
		break;
	case 3:
		system("cls");
		login = getString(" ����� ����� ��� ����������. ������� ������ ����� ��� ��� ������ ������� menu.");
		break;
	case 4:
		system("cls");
		login = getString(" ������� ����� , ����� �������� ������.");
		break;
	case 5:
		system("cls");
		login = getString(" ������� ����� ������������, �������� �� ������ �������.");
		break;
	};
	do
	{   
		u = 0;
		if (type != 4 && type != 5) {
			if (login == "menu")
			{
				exit = true;
				break;
			}
		}
		if (login.size() < 5 || login.size() > 15)
		{
			login = getString(" ������� ����� �� 5 �� 15 ��������.");
			continue;
		}

		for (unsigned int i = 0; i < login.size(); ++i)
			if (!((login[i] >= 'a' && login[i] <= 'z')
				|| (login[i] >= 'A' && login[i] <= 'Z')
				|| (login[i] >= '0' && login[i] <= '9')))
			{
				login = getString(" ����� �������� ������������ �������.");
				break;
			}
			else u++;
		if (u == login.size()) break;

	} while (true);
	return login;
};
string BOO::password(int type,bool& exit) {
	string password;
	switch (type) {
	case 1:
		system("cls");
		password = pass(" ������� ������. ��� ������ ������� menu.");
		break;
	case 2:
		system("cls");
		password = pass(" ������� ����� ������.");
		break;
	}
	do {
		int u = 0;
		if (type != 2) {
			if (password == "menu")
			{
				exit = true;
				break;
			}
		}
		if (password.size() < 8 || password.size() > 12)
		{
			password = pass(" ������ ������ ���������  �� 8 �� 12 ��������");
			continue;
		}

		for (auto a : password) {
			if (!((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')))
			{
				password = pass(" ������ �������� ������������ �������.");
				break;
			}
			else {
				u++;
			}
		}
		if (u == password.size()) {
			break;
		}

	} while (true);
	return password;
};
string pass(string string) {
	system("cls");
	std::string pass;
	cout << string << endl;
	char c;
	while ((c = _getch()) != 13) {
		if (c == '\b' && !pass.empty()) {
			cout << '\b' << ' ' << '\b';
			pass.pop_back();
			continue;
		}
		if (c == '\b')continue;
		if (c != ' ') {
			pass.push_back(c);
			std::cout << '*';
		}
		else {
			system("cls");
			cout << " �� ����������� ������" << endl;
			pass.erase();
			cout << " ������� ������. ��� ������ ������� menu." << endl;
		}
	}
	return pass;
}
string yes_no(string message) {
	string choice;
	while (true) {
		cout << message << endl;
		getline(cin, choice);
		if (choice != "��" && choice != "���") { 
			system("cls");
			cout << "������� ������ �� ��� ���" << "\n";
			continue; }
		else break;
	}
	return choice;
}
string BOO::client_code(string message) {
	string client_code;
	while(true){
		cout << message << endl;
		int u = 0;
		int s = 0;
		getline(cin, client_code);
		system("cls");
		if (client_code.empty())continue;
		if (client_code.size() != 8) { cout << "����� �������� ������ ��������� 8 ��������." << endl; continue; }
		for (unsigned int i = 0; i < client_code.size(); i++) {
			if (client_code[i] == ' ') {
				s++;
				cout << " ������� ����� �������� ��� ��������" << endl;
				break;
			}
		}
		if (s == 0) {
			for (unsigned int i = 0; i < client_code.size(); i++) {

				if (client_code[i] >= 'a' && client_code[i] <= 'z' || client_code[i] >= '0' && client_code[i] <= '9' || client_code[i] >= 'A' && client_code[i] <= 'Z')
					u++;
				else {
					cout << "����������� ����� ���������� �������� � ����� ��� �����" << endl;
					break;
				}
				if (u == client_code.size()) {
					break;
				}
			}
		}
		else { continue; }

		if (u == client_code.size()) {
			break;
		}
	}
	return client_code;
}
string ccsns(string message) {
	string ccs;
	while(true) {
		cout << message << endl;
		int u = 0;
		int s = 0;
		getline(cin, ccs);
		system("cls");
		for (unsigned int i = 0; i < ccs.size(); i++) {
			if (ccs.size() < 2 || ccs.size() >= 20) {
				cout << "������� 2 �������. �������� 20." << endl;
				break;
			}
			if (ccs[0] >= (-64) && ccs[0] <= (-33) || ccs[0] == (-88)) i = 1;
			else
			{
				cout << "������ ����� ������ ���� ���������. ����������� ��� ����� ����� ����������� ��������.\n" << endl;
				break;
			}

			for (i; i < ccs.size(); i++) {

				if ((ccs[i] >= (-32) && ccs[i] <= (-1))  || ccs[i]==(-72) || ccs[i] == '.' || ccs[i] == ' ') u++;
				
				else {
					cout << "����������� �� ����� ����� ����������� ��������. �� ������������ ��� ����� ��������� �����. " << endl;
					u = 0;
					break;
				}

			}
			if (u == 0 || u == ccs.size() - 1) break;
		}
		if (u == ccs.size() - 1) break;
	}
	return ccs;
}
string hfst(string message,int mode) {
	string hfs;
	while(true) {
		cout << message << endl;
		int u = 0;
		int s = 0;
		getline(cin, hfs);
		system("cls");
		if (hfs.empty())continue;
		for (unsigned int i = 0; i < hfs.size(); i++) {
			if (mode == 1) {
				if (hfs.size() > 3) {
					s++;
					cout << "�������� 3 �������." << endl;
					break;
				}
			}
			if (mode == 2)
			{
				if (hfs.size() >= 9) {
					s++;
					cout << "����� ������� ������." << endl;
					break;
				}
			}
			if (mode == 3) {
				if (hfs.size() != 9) {
					s++;
					cout << "����� �������� ������ ��������� 9 ��������." << endl;
					break;
				}
			}
			if (hfs[i] == ' ') {
				s++;
				cout << " ������� ��� ��������" << endl;
				break;
			}
		}
		if (s == 0) {
			for (unsigned int i = 0; i < hfs.size(); i++) {

				if (hfs[i] >= '0' && hfs[i] <= '9') u++;
				else {
					cout << "����������� ������ ����� ��� �����" << endl;
					u = 0;
					break;
				}
				if (u == 0|| u == hfs.size()) break;
			}
		}
		if (u == hfs.size()) break;
	}
	return hfs;
}
string contract_name(string code) {
	std::string name;
	if (code == "1111") name = "������������";
	if (code == "2222") name = "������� �������";
	if (code == "3333") name = "���������";
	if (code == "4444") name = "������������";
	if (code == "5555") name = "�������������� �������";
	if (code == "6666") name = "���������� ������������";
	if (code == "7777") name = "���������� �� ������ ���������";
	if (code == "8888") name = "���������� � ������ ������� �� �������";
	if (code == "9999") name = "����������";
	return name;
}
string service_code(string message) {
	string service_code;
	while (true) {
		system("cls");
		cout << message << endl;
		getline(cin, service_code);
		if (service_code != "1111" && service_code != "2222" && service_code != "3333" && service_code != "4444" && service_code != "5555" && service_code != "6666" && service_code != "7777" && service_code != "8888" && service_code != "9999")
			continue;
		else break;
	}
	return service_code;
}
void Contract::add_document_code() {
	system("cls");
	int days, months, years;
	bool correct = false;
	bool isLeap = false;
	bool access = true;
	string date;
	do {
		if (access) {
		contract_code = BOO::contract_code(1, access);
		}
		else {
		contract_code = BOO::contract_code(2, access);
		}
		ifstream file("document_code.txt", ios::app);
		while (file) {
			string tmp;
			getline(file, tmp);
			if (tmp == contract_code){access = false;break;}
			else access = true;
		}
		file.close();
	} while (!access);
	system("cls");
	while (correct == false) {
		system("cls");
		correct = true;
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
		days = day("������� ����:",isLeap,months);
		correct = current_time(days, months, years, correct);
		if (!correct)system("pause");
	}
	if (correct == true) {  date = to_string_date(days, months, years); }
	ofstream file1("dogovor.txt", ios::app);
	file1 << contract_code << endl << date << endl;
    file1.close();
	ofstream file2("document_code.txt", ios::app);
	file2 << contract_code << endl;
	file2.close();
	cout << date;
	system("cls");
	cout << "�� �������� �������." << endl;
	return;
}
string BOO::contract_code(int type, bool& access) {
	bool run = true;
	int u = 0;
	string document_code;
	switch (type) {
	case 1:
		system("cls");
		if (access) document_code = getString("������� ����� ��������.");
		else document_code = getString("������� ��� ��������� ��� ���.");
		break;
	case 2:
		system("cls");
		document_code = getString("����� ����� �������� ��� ���������� � ����. ������� ����� ��������� ��� ���.");
		break;
	};
	do {
		u = 0;
		if (document_code.size() != 10)
		{
			document_code = getString("��� �������� ������ ��������� 10 ��������.");
			continue;
		}

		for (unsigned int i = 0; i < document_code.size(); ++i)
			if (!((document_code[i] >= 'a' && document_code[i] <= 'z')
				|| (document_code[i] >= 'A' && document_code[i] <= 'Z')
				|| (document_code[i] >= '0' && document_code[i] <= '9')))
			{
				document_code = getString("��� �������� �������� ������������ �������.");
				break;
			}
			else u++;
		if (u == document_code.size())break;
	} while (true);
	return document_code;
}
int year(string message) {
	int years;
	while (true) {
		years = get_int("������� ���");
		if (years < 2020 || years > 2030) {
			system("cls");
			cout << "������ ��� 2020-2030" << endl;
			continue;
		}
		break;
	}
	return years;
}
int month(string message) {
	int month;
	while (true) {
		month = get_int("������� �����");
		if (month < 1 || month > 12) {
			system("cls");
			cout << "���� ������ 12 ������� � ����" << endl;
			continue;
		}
		break;
	}
	return month;
}
int day(string message, bool isLeap, int& month) {
	int day;
	while (true) {
		day = get_int("������� ����");
		if (day < 1 || day >31) {
			system("cls");
			cout << "�������� 31 ����" << endl;
			continue;
		}
		if (month == 4 || month == 6 || month == 9 || month == 11) {
			system("cls");
			if (day > 30) {
				cout << "� ������, ����, �������� � ������ 30 ����" << endl;
				continue;
			}
		}
		if (month == 2 && isLeap == true) {
			system("cls");
			if (day > 29) {
				cout << "� ���������� ���� � ������� 29 ����" << endl;
				continue;
			}
		}
		if (month == 2 && isLeap == false) {
			system("cls");
			if (day > 28) {
				cout << "� ������� 28 ����" << endl;
				continue;
			}
		}
		break;
	}
	return day;
}
int get_int(string message) {
	int c;
	cout << message << endl;
	while (true) {
		cin >> c;
		system("cls");
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			system("cls");
			cout << "������� ����� �����" << endl;
			cout << message << endl;
			continue;
		}
		if (c < 0) { cout << "������� ������������� �����" << endl; continue; }
		break;
	};
	return c;
 };
bool current_time(int &day, int &month, int &year,bool correct) {
	time_t t = time(nullptr); 
	tm* now = localtime(&t); 
    if (day != now->tm_mday) { correct = false; cout << "���� �� ��������� � ��������" << endl; }
	if (month != now->tm_mon + 1) { correct = false; cout << "����� �� ��������� � ��������" << endl; }
    if (year != now->tm_year + 1900) { correct = false; cout << "��� �� ��������� � ��������" << endl; }
	cout << " ������� ���� ��� ���" << endl;
	return correct;
};
string to_string_date(int& day, int& month, int& year) {
	string day1 = to_string(day);
	string month1 = to_string(month);
	string year1 = to_string(year);
	if (day1 == "1" || day1 == "2" || day1 == "3" || day1 == "4" || day1 == "5" || day1 == "6" || day1 == "7" || day1 == "8" || day1 == "9") { day1 = "0" + day1; }
    if (month1 == "1" || month1 == "2" || month1 == "3" || month1 == "4" || month1 == "5" || month1 == "6" || month1 == "7" || month1 == "8" || month1 == "9") { month1 = "0" + month1; }
	string date = day1 + "." + month1 + "." + year1;
	return date;
 };
void BOO::choice(int type) {
	cout << "\n";
	system("pause");
	system("cls");
	string choice;
	switch (type) {
      case 1:
		choice = yes_no("��� �� ������ ����������? ������� '��' , ���� ������ ��������� � ���� �������������� � '���', ���� � ��������� ����.");
		if (choice == "��") BOO::menu(1);
		break;
	  case 2:
	    choice = yes_no("��� �� ������ ����������? ������� '��' , ���� ������ ��������� � ���� ������������ � '���', ���� � ��������� ����.");
		if (choice == "��") BOO::menu(2);
		break;
	 }
	if (choice == "���") BOO::menu(0);
 }