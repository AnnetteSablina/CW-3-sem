#include "Header.h"

Human::Human(string login, string password) {
	this->login = login;
	this->password = password;
}
bool Human::operator ==(Human human) {
	if (this->login == human.login && this->password == human.password)
		return true;
	else
		return false;
}

