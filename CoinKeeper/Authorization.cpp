#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <Windows.h>
#include <numeric>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Authorization.h"
#include "CoinKeeper.h"
#include "Cin_check.h"

Authorization::Authorization()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

void Authorization::start()
{
	load();
	main_menu();
}


void Authorization::main_menu()
{
	do
	{
		save();
		std::cout << "\t\t\tCoinKeeper\t\t" << "\n"
			<< "1)Войти в профиль\n"
			<< "2)Создать профиль\n"
			<< "3)Удалить профиль\n"
			<< "4)Выход\n";

		std::cin >> menu;
		Valid_cin(menu);

		system("cls");
		menu_app();

	} while (!exit);
}

void Authorization::menu_app()
{
	switch (menu)
	{
	case 1:
	{
		enter_the_profile();
		break;
	}
	case 2:
	{
		create_the_profile();
		break;
	}
	case 3:
	{
		delete_profile();
		break;
	}
	case 4:
	{
		exit = true;
		break;
	}
	default:
	{
		break;
	}
	}
}

void Authorization::enter_the_profile()
{
	if (profile.size() == 0)
	{
		std::cout << "\t\t\tCoinKeeper\t\t" << "\n"
			<< "Не один профиль еще не создан. Возврат в главное меню...\n";
		system("pause");
		system("cls");
		return;
	}

	auto it = profile.begin();
	int menu_count = 0;
	std::cout << "\t\t\tCoinKeeper\t\t" << "\n";
	for (int i = 1; i < profile.size() + 1; i++)
	{
		std::cout << i << ") " << it->first << "\n";

		if (i == profile.size())
		{
			std::cout << i + 1 << ") Назад" << "\n";
			menu_count = i;
		}
		it++;
	}

	std::cin >> menu;
	Valid_cin(menu);
	if (menu > profile.size() || menu == 0)
	{
		system("cls");
		return;
	}

	it = profile.begin();
	std::advance(it, menu - 1);

	system("cls");
	std::cout << "\t\t\tCoinKeeper\t\t" << "\n"
		<< "Введите пароль:\n";
	getline(std::cin, password);

	system("cls");

	if (it->second == password)
	{
		CoinKeeper app(it->first);
		app.menu_app();
	}
	else
	{
		std::cout << "\t\t\tCoinKeeper\t\t" << "\n";
		std::cerr << "Вы ввели неверный пароль!\n";
		system("pause");
		system("cls");
	}
}

void Authorization::create_the_profile()
{
	std::cout << "\t\t\tCoinKeeper\t\t" << "\n";
	std::cout << "Введите логин профиля:\n";
	getline(std::cin, login);
	system("cls");

	std::cout << "\t\t\tCoinKeeper\t\t" << "\n";
	std::cout << "Введите пароль:\n";
	getline(std::cin, password);
	system("cls");

	profile.insert(std::pair<std::string, std::string>(login, password));

	save(); // добавь проверку на неудачу

	std::cout << "\t\t\tCoinKeeper\t\t" << "\n";
	std::cout << "Профиль успешно создан\n";
	system("pause");
	system("cls");
}

void Authorization::delete_profile()
{
	if (profile.size() == 0)
	{
		std::cout << "\t\t\tCoinKeeper\t\t" << "\n"
			<< "Не один профиль еще не создан. Возврат в главное меню...\n";
		system("pause");
		system("cls");
		return;
	}

	auto it = profile.begin();
	int menu_count = 0;
	std::cout << "\t\t\tCoinKeeper\t\t" << "\n";
	for (int i = 1; i < profile.size() + 1; i++)
	{
		std::cout << i << ") " << it->first << "\n";

		if (i == profile.size())
		{
			std::cout << i + 1 << ") Назад" << "\n";
			menu_count = i;
		}
		it++;
	}

	std::cin >> menu;
	Valid_cin(menu);
	if (menu > profile.size() || menu == 0)
	{
		system("cls");
		return;
	}

	it = profile.begin();
	std::advance(it, menu - 1);

	system("cls");
	std::cout << "\t\t\tCoinKeeper\t\t" << "\n"
		<< "Введите пароль:\n";
	getline(std::cin, password);

	system("cls");

	if (it->second == password)
	{
		std::string filename = it->first + ".txt";
		remove(filename.c_str());
		profile.erase(it);
		std::cout << "\t\t\tCoinKeeper\t\t" << "\n";
		std::cerr << "Профиль был удален!\n";
		system("pause");
		system("cls");
	}
	else
	{

		std::cout << "\t\t\tCoinKeeper\t\t" << "\n";
		std::cerr << "Вы ввели неверный пароль!\n";
		system("pause");
		system("cls");

	}
}

void Authorization::save()
{
	std::ofstream ofs("Profile.txt");
	if (ofs.is_open())
	{
		int size = profile.size();
		auto it = profile.begin();

		ofs.write((char*)&size, sizeof(int)); // запись длины мапа
		for (int i = 0; i < profile.size(); i++)  // итерация по длине мапа
		{
			size = it->first.size();
			ofs.write((char*)&size, sizeof(int)); // запись длины стринга

			for (int j = 0; j < it->first.size(); j++)// итерация по длине стринга
			{
				ofs.write((char*)&it->first[j], sizeof(char)); // почаровая запись
			}

			size = it->second.size();
			ofs.write((char*)&size, sizeof(int));

			for (int j = 0; j < it->second.size(); j++)
			{
				ofs.write((char*)&it->second[j], sizeof(char));
			}

			it++;
		}
		ofs.close();
	}
}

void Authorization::load()
{
	std::ifstream ifs("Profile.txt");
	if (ifs.is_open())
	{
		int size;// для внутренних циклов
		int size1; // для итерации по мап

		ifs.read((char*)&size1, sizeof(int)); // считываение длины мапа

		for (int i = 0; i < size1; i++) // итерация по мапу
		{

			ifs.read((char*)&size, sizeof(int)); // считывание длины стринга
			for (int j = 0; j < size; j++) // итерация по стрингу
			{
				char temp;
				ifs.read((char*)&temp, sizeof(char)); // почаровое считывание для конкатенации
				login += temp;
			}

			ifs.read((char*)&size, sizeof(int));
			for (int j = 0; j < size; j++)
			{
				char temp;
				ifs.read((char*)&temp, sizeof(char));
				password += temp;
			}

			profile.insert(std::pair<std::string, std::string>(login, password)); // добавление в мап данных что были считаны

		}

		ifs.close();
	}
	else
	{
		std::cout << "\t\t\tCoinKeeper\t\t" << "\n";
		std::cerr << "Нарушение загрузки, Profile.txt будет сгенерирован с нуля.\n";
		system("pause");
		std::ofstream ofs("Profile.txt");
		ofs.close();

		system("cls");
	}
}