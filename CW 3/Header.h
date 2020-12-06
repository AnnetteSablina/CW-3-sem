#pragma once
#include "Sha256.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <ctime>
#include "table_printer.h"
#define _USE_MATH_DEFINES
#include <math.h>
#if defined(USE_BOOST_KARMA)
#include <boost/spirit/include/karma.hpp>
namespace karma = boost::spirit::karma;
#endif
using bprinter::TablePrinter;
#pragma warning(disable : 4996)

using namespace std;

class Human;
class Client;
class Admin;
class Contract;
class Human_actions;


 
int menu_1(int);//���� ������� ������
string pass(string );//������ �����������
string yes_no(string);
void draw(string);//������� ��� �������� ������
//string getString(string);//����� ������
string client_code(string);//�������� �� ���� ������ ��������
string ccsns(string);//�������� �� ���� ������,������, ����� , ������� � ��
string hfst(string,int);//�������� �� ���� ������ ���� � ��������
string contract_name(string );//�������� ��������
string service_code(string);//��� ������

int get_int(string);//
int year(string);//�������� �� ���� ����
int month(string);//������� �� ���� ������
int day(string , bool , int&);//������� �� ���� ���
bool current_time(int &, int &, int &, bool );//������� ������� � ���������
string to_string_date(int& , int& , int& );// �������������� ���� � ������


namespace BOO {
	string login(int, bool&);//���� ������
	string password(int,bool&);//���� ������
	void menu(int);//����
	string client_code(string);//�������� �� ����� ��������
	string contract_code(int, bool&);//�������� �� ����� ��������
	void choice(int);//����� � ����� ���� ��������
}







 class Human {
protected:
	string login; //�����
	string password; //������
public:
	Human(string, string);
	Human() {};
	bool operator==(Human human);
	friend void data_user_file(vector<Human>&);// ��������� ������� �������� � �������� �������������
	friend void data_admin_file(vector<Human>&);// ��������� ������� �������� � �������� ��������������
	static void rewrite_user_file(vector<Human>& );
    bool check_login_once();//��������� ������� ������ �� ��������
	~Human() {};
	friend class Client;
	friend class Admin;
};

 
 class Human_actions {
 public:
	 virtual int menu() = 0;//����
	 virtual void enterAccount(vector<Human>&) = 0;//���� � �������
 };

 class Client :public Human, virtual public Human_actions {
protected:
	string client_code;// ��� �������/����� ��������
	string name;//���
	string surname;//�������
	string telephone_number;//����� ��������
	string country;//������
    string city;//�����
	string street;//�����
	string housenumber;//����� ����
	string flatnumber;//����� ��������
	string quantity;//���������� ����������� ���������
 public:
	Client() {};
	~Client() {};
	friend class Admin;
	int menu() override; //���� ������������
	void enterAccount(vector<Human>&) override;// ���� � ������� ������������
	friend void data_passport_file(vector<Client>&);//���������� ������� � �������� ��������� �������������
	friend void data_client_file(vector<Client>&);//���������� ������� ���� � ����� �������������
	friend void rewrite_information_file(vector <Client>&);//���������� ����� � ����� � ������������
	friend void rewrite_passport_file(vector <Client>&);//���������� ����� � ����������� �������
	friend void rewrite_contract_file(vector <Client>&);// ���������� ����� � ������������ ����������(����� + ��� � �������)
	friend void data_contract_file(vector<Client>& );//���������� ������� � ������������ ����������(����� + ��� � �������)
	void changelogpass(int);//������� �����/������
	void changeinfo(int);//����� ���������� � ������������
	void find_contract_number(int);//����� ������� �� ��� ������
	void find_passport(int);//����� �������� �� ������ ��������
	void find_date(int);//����� ��������� �� ���� ����������
	void find_user(int);//����� ���������� � ������������
};

 class Admin :public Client {
public:
	void enterAccount(vector<Human>&) override;//���� � ������� ��������������
	int menu() override; //���� ��������������
	void conclusion_contract();// ���������� ��������
	bool add_logpass(); // �������� ����� � ������ ������������
	void add_user_information_contract();//���������� ���� � ����� ��� ���������� �������
	bool add_client_code_into_contract();// ���������� ������ �������� ��� ���������� ��������
	void add_dogovor();//���������� ������ ��������
	void output(int);// ����� ������ � ��������� �����
	int find_sort_menu();//���� ���������� � ������
	void find_service(int);//����� ��������� �� ���� �����
	void sort(int);//���������� ���������� �� ���� �����
	void top_10(int);//��� 10 ��������
	void add_information(int);//���������� ���������� � ������������
	void delete_user(int);// �������� ������������
};


 class Contract {
 protected:
	 string contract_code;//��� ��������
 public:
	 Contract() {};
	 ~Contract() {};
	 string name;//�������� ��������
	 string service_code;// ��� ������
	 string summ;//�����
	 string commition;//�����c������
	 friend void contract_code(vector<Contract>&);//���������� ������� � �������� ���������
	 friend class Admin;
	 friend class Client;
	 void add_document_code();//�������� ��� ��������
};

 template <class T>
 class Outputs {
 protected:
	 string client_code;//����� ��������
	 string service_code;//��� ������
	 string name;//�������� ��������
	 string summ;//�����
	 string comission;//������������
	 string document_code;//����� ��������
	 string date;//���� ����������
 public:
	 Outputs() {};
	 ~Outputs() {};
	 friend void data_dogovor_file(vector<Outputs>&);//���������� ������� � ������������ ����������
	 friend class Admin;
	 friend class Client;
 };

 template <typename T>
 string getString(T p)
 {
	 system("cls");
	 string mystring;
	 cout << p << endl;
	 getline(cin, mystring);
	 return mystring;
 }