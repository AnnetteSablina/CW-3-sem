#pragma once
#include "SHA256.h"
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
template<typename T, typename R>
class Human_actions;


int menu_1(int);//меню первого уровня
string pass(string);//пароль звездочками
string yes_no(string);
void draw(string);//функция для покраски текста
string client_code(string);//проверка на ввод номера паспорта
string ccsns(string);//проверка на ввод страны,города, имени , фамилии и тд
string hfst(string, int);//проверка на ввод номера дома и квартиры
string contract_name(string);//название договора
string service_code(string);//код услуги

int get_int(string);//
int year(string);//проверка на ввод года
int month(string);//проверк на воод месяца
int day(string, bool, int&);//провека на ввод дня
bool current_time(int&, int&, int&, bool);//сравние времени с настоящим
string to_string_date(int&, int&, int&);// преобразование даты в строку


namespace BOO { // пользовательское пронстранство имен 
	string login(int, bool&);//ввод логина
	string password(int, bool&);//ввод пароля
	void menu(int);//меню
	string client_code(string);//проверка на номер паспорта
	string contract_code(int, bool&);//проверка на номер договора
	void choice(int);//выбор в каком меню остаться
}







class Human {
protected:
	string login; //логин
	string password; //пароль
public:
	Human(string, string);//контсруктор с 2 полями типа string
	Human() = default;//конструктор по умолчанию
	bool operator==(Human human);// перегрузка оператора ==
	friend void data_user_file(vector<Human>&);// заполение вектора логинами и паролями пользователей
	friend void data_admin_file(vector<Human>&);// заполение вектора логинами и паролями администратора
	static void rewrite_user_file(vector<Human>&);
	bool check_login_once();//проверить наличие логина на единство
	~Human() = default;//деструктор
	friend class Client;//дружетсвенный класс Client
	friend class Admin;//дружественный класс Admin
};

template<typename T, typename R>//шаблонный интерфейс
class Human_actions {
public:
	virtual R menu() = 0;// виртуальная функция меню
	virtual void enterAccount(vector<T>&) = 0;//виртуальная функция входа в аккаунт
};

class Client :public Human, virtual public Human_actions<Human, int> {//класс Клиент, который наследуется от 2 классов
protected:
	string client_code;// код клиента/номер паспорта
    string name;//Имя
	string surname;//Фамилия
	int telephone_number = 0;//Номер телефона
	string country;//Страна
	string city;//Город
	string street;//Улица
	int housenumber = 0 ;//Номер дома
	int flatnumber = 0 ;//Номер квартиры
	int quantity = 0;//количество заключенных договоров
public:
	Client() = default;//конструктор по умолчанию
	~Client() = default;//деструктор
	friend class Admin;// дружественный класс Admin
	int menu() override; //меню пользователя (переопределение)
	void enterAccount(vector<Human>&) override;//  вход в аккаунт пользователя (переопределение функции)
	friend void data_passport_file(vector<Client>&);//заполнения вектора с номерами паспортов пользователей (дружественная)
	friend void data_client_file(vector<Client>&);//заполнение вектора инфы с инфой пользователей (дружественная)
	friend void rewrite_information_file(vector <Client>&);//перезапись файла с инфой о пользователе (дружественная)
	friend void rewrite_passport_file(vector <Client>&);//перезапись файла с паспортными данными (дружественная)
	friend void rewrite_contract_file(vector <Client>&);// перезапись файла с заключенными договорами(номер + имя и фамилия) (дружествнная)
	friend void data_contract_file(vector<Client>&);//заполнение вектора с заключенными договорами(номер + имя и фамилия) (дружественная)
	void changelogpass(int);//сменить логин/пароль
	void changeinfo(int);//смена информации о пользователе
	void find_contract_number(int);//поиск договор по его номеру
	void find_passport(int);//поиск договора по номеру паспорта
	void find_date(int);//поиск договоров по дате заключения
	void find_user(int);//поиск информации о пользователе
};

class Admin :public Client {
public:
	void enterAccount(vector<Human>&) override;//вход в аккаунт администратора (переопределение функции)
	int menu() override; //меню администратора (переопределение)
	void conclusion_contract();// заключение договора
	bool add_logpass(); // добавить логин и пароль пользователя
	void add_user_information_contract();//добавление инфы о юзере при заключении договра
	bool add_client_code_into_contract();// добавления номера паспорта при заключении договора
	void add_dogovor();//добавление данных договора
	void output(int);// вывод данных в табличной форме
	int find_sort_menu();//меню сортировки и поиска
	void find_service(int);//поиск договоров по коду услуг
	void sort(int);//сортировка документов по коду услуг
	void top_10(int);//топ 10 клиентов
	void add_information(int);//добавление информации о пользователе
	void delete_user(int);// удаление пользователя
};


class Contract {
protected:
	string contract_code;//Код договора
public:
	Contract() = default; // конструктор по умолчанию
	~Contract() = default;//деструктор
	string name;//Название договора
	string service_code;// Код услуги
	int summ = 0;//Сумма
	int commition = 0;//Комисcионные
	friend void contract_code(vector<Contract>&);//заполнение вектора с номерами договоров
	friend class Admin;// дружественный класс Admin
	friend class Client;//дружественный класс Client
	void add_document_code();//добавить код договора
};

class Outputs {
protected:
	string client_code;//номер паспорта
	string service_code;//код услуги
	string name;//название договора
	int summ = 0;//сумма
	int comission = 0;//комиссионные
	string document_code;//номер договора
	string date;//дата подписания
public:
	Outputs() = default;// конструктор по умелчанию
	~Outputs() = default;//деструктор
	friend void data_dogovor_file(vector<Outputs>&);//заполнение вектора с заключенными договорами
	friend class Admin;// дружественный класс Admin
	friend class Client;//дружественный класс Client
};

template <typename T> // шаблонная функция получения строки
string get_string(const T& p)
{
	system("cls");
	string mystring;
	cout << p << endl;
	getline(cin, mystring);
	return mystring;
}
