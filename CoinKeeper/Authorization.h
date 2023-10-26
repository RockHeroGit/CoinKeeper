#pragma once


class Authorization
{
	bool exit = false;							 // переменая для выхода
	int menu=0;									 // переменная для управления меню
	std::string password;						 // переменная для установки и верификации пароля
	std::string login;							 // переменная для установки и верификации логина
	std::map<std::string, std::string> profile;  //  мап для хранения логина и пароля
	
public:

	Authorization();							// конструктор устанавливающий локализацию
	void start();								// запускает приложение

private:

	void main_menu();							// главное меню с выбором поля
	void menu_app();							// меню обработки запроса пользователя
	void enter_the_profile();					// войти в профиль
	void create_the_profile();					// создание нового профиля
	void delete_profile();						// удаление существующего профиля
	void save();								// сериализация в бинарном виде
	void load();    							// десериализация
};