#include "Header.h"

void data_user_file(vector<Human>& users) {   
	ifstream file("users.txt");
	while (file)
	{
		Human temp;
		getline(file, temp.login);
		getline(file, temp.password);
		users.push_back(temp);
	}
	if (!users.empty()) users.erase(users.end() - 1);
	file.close();
}
void data_admin_file(vector<Human>& admins) {
	ifstream file("admins.txt");
	while (file)
	{
		Human temp;
		getline(file, temp.login);
		getline(file, temp.password);
		admins.push_back(temp);
	}
	if (!admins.empty()) admins.erase(admins.end() - 1);
	file.close();
}
void data_passport_file(vector<Client>& passport) {
	ifstream file("passport.txt");
	while (file)
	{
		Client temp;
		getline(file, temp.client_code);
		getline(file, temp.name);
		getline(file, temp.surname);
		passport.push_back(temp);
	}
	if (!passport.empty()) passport.erase(passport.end() - 1);
	file.close();
}
void contract_code(vector<Contract>& documentCode) {
	ifstream file("document_code.txt");
	while (file) {
		Contract temp;
		getline(file, temp.contract_code);
		documentCode.push_back(temp);
	}
	if (!documentCode.empty()) documentCode.erase(documentCode.end() - 1);
	file.close();
	return;
}
void Human::rewrite_user_file(vector<Human>& users){
	ofstream file("users.txt", ios::trunc);
	for (auto i : users)
		file << i.login << endl << i.password << endl;
	file.close();
	return;
}
void data_client_file(vector<Client>& userss) {
	ifstream file("info.txt");
	while (file) {
		Client temp;
		getline(file, temp.client_code);
		getline(file, temp.name);
		getline(file, temp.surname);
		getline(file, temp.telephone_number);
		getline(file, temp.country);
		getline(file, temp.city);
		getline(file, temp.street);
		getline(file, temp.housenumber);
		getline(file, temp.flatnumber);
		userss.push_back(temp);
	}
	if (!userss.empty()) userss.erase(userss.end() - 1);
	file.close();
}
void rewrite_information_file( vector <Client>& userss) {
	ofstream file("info.txt", ios::trunc);
	for (auto i : userss)
		file << i.client_code << endl << i.name << endl << i.surname << endl
		<< i.telephone_number << endl << i.country << endl << i.city << endl << i.street << endl << i.housenumber 
		<< endl << i.flatnumber << endl;
	file.close();
	return;
}
void rewrite_passport_file(vector <Client>& passport) {
	ofstream file("passport.txt", ios::trunc);
	for (auto i : passport)
		file << i.client_code << endl << i.name << endl << i.surname << endl;
	file.close();
	return;
}
void rewrite_contract_file(vector <Client>& magic) {
	ofstream file("magic.txt", ios::trunc);
	for (auto i : magic)
		file << i.client_code << endl << i.name << endl << i.surname << endl;
	file.close();
	return;
}
void data_contract_file(vector<Client>& magic) {
	ifstream file("magic.txt");
	while (file){
		Client temp;
		getline(file, temp.client_code);
		getline(file, temp.name);
		getline(file, temp.surname);
		magic.push_back(temp);
	}
	if (!magic.empty()) magic.erase(magic.end() - 1);
	file.close();
}
void data_dogovor_file(vector<Outputs<string>>& dogovors) {
	ifstream file("dogovor.txt");
	while (file) {
		Outputs<string> temp;
		getline(file, temp.client_code);
		getline(file, temp.service_code);
		getline(file, temp.name);
		getline(file, temp.summ);
		getline(file, temp.comission);
		getline(file, temp.document_code);
		getline(file, temp.date);
		dogovors.push_back(temp);
	}
	if (!dogovors.empty()) dogovors.erase(dogovors.end() - 1);
	file.close();
	return;
}