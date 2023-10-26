#pragma once


using std::vector;
using std::map;
using std::string;

class Authorization;

class CoinKeeper
{
	friend class Authorization;						// доступ для запуска работы из другого класса
private:
	bool exit = false;								// переменая для выхода
	int menu = 0;									// переменная для управления меню
	float money = 0;								// переменная для текущих денег
	float all_money = 0;							// переменная для подсчета денег за все время
	string profile;									// переменная для создания файла профиля
	vector<double> food;							// контейнер стандартного расхода(еда)
	vector<double> fun;							    // контейнер стандартного расхода(развлечения)
	vector<double> clothes;							// контейнер стандартного расхода(одежда)
	vector<double> medeciny;						// контейнер стандартного расхода(медикаменты)
	map< string, vector<double> > other_Category;	// контейнерпользовательского расхода

	CoinKeeper(const string& name);					// конструктор принимающий имя профиля
	~CoinKeeper();									// дефолтный деструктор

	void main_menu();								// главное меню с выбором поля
	void menu_app();								// меню обработки запроса пользователя
	void consumption_menu();						// меню с выбором расхода
	void add_category();							// добавить пользовательскую категорию расходов
	void delete_category();							// удалить пользовательскую категорию расходов
	void add_consumption(vector<double>& vect);		// внести расход в стандартную категорию 
	void add_consumption(int x);					// внести расход в пользовательскую категорию 
	void add_money();								// внести приход денег
	void info();									// отчет о расходах
	double sum(vector<double>& vect);				// вспомогательная функция для отчета
	double greated();								// вспомогательная функция для отчета
	void full_info_menu();							// меню с подробным отчетом о каждой категории
	void print_category(int x);						// вывод на экран подробного отчета
	void save();									// сериализация в бинарном виде
	void load();									// десериализация
};