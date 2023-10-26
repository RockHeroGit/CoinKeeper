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
#include "CoinKeeper.h"
#include "Cin_check.h"


CoinKeeper::CoinKeeper(const string& name) :profile(name)
{
	std::cout << std::fixed<< std::setprecision(2);
	profile += ".txt";
	load();
}

CoinKeeper::~CoinKeeper()
{
}

void CoinKeeper::main_menu()
{
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
	}

	std::cout << "\t\t\tCoinKeeper\t\t" << "Баланс: " << money << "\n"
		<< "1)Добавить расход\n"
		<< "2)Добавить финансы\n"
		<< "3)Вывести отчет\n"
		<< "4)Подробный отчет\n"
		<< "5)Выход\n";

	std::cin >> menu;
	Valid_cin(menu);
	system("cls");
}

void CoinKeeper::menu_app()
{
	do
	{
		main_menu();

		switch (menu)
		{
		case 1: // кейс расходов
		{
			consumption_menu();

			switch (menu)
			{
			case 1:
			{
				add_consumption(food);
				break;
			}
			case 2:
			{
				add_consumption(fun);
				break;
			}
			case 3:
			{
				add_consumption(clothes);
				break;
			}
			case 4:
			{
				add_consumption(medeciny);

				break;
			}
			default:
				break;
			} // конец пред подготовленныцх веток меню

			if (menu == 5 + other_Category.size()) // поскольку уже сдесь может возникнуть сдвиг меню то это меню = 5 + количество новых веток
			{
				add_category();
				break;
			}

			if (menu > 4 && menu < 6 + other_Category.size()) // вызов мап иниц
			{
				add_consumption(menu - 5);
				break;
			}

			if (menu == 6 + other_Category.size()) // проверка на exit 
			{
				delete_category();
				break;
			}

			if (menu >= 7 + other_Category.size()) // проверка на exit 
				break;

			break;
		}
		case 2:
		{
			add_money();
			break;
		}
		case 3:
		{
			info();
			break;
		}
		case 4:
		{
			full_info_menu();
			break;
		}
		case 5:
		{
			exit = true;
			break;
		}
		default:
			break;
		}

		save();

	} while (!exit);
}

void CoinKeeper::consumption_menu()
{
	std::cout << "\t\t\tCoinKeeper\t\t" << "Баланс: " << money << "\n"
		<< "1)Еда\n"
		<< "2)Развлечения\n"
		<< "3)Одежда\n"
		<< "4)Медикаменты\n";

	int x = 5;
	for (auto it = other_Category.begin(); it != other_Category.end(); it++)
	{
		std::cout << x++ << ")" << (it)->first << "\n";
	}

	std::cout << x++ << ")Добавить новую статью расходов\n";
	std::cout << x++ << ")Удалить статью расходов\n";
	std::cout << x << ")Назад\n";;

	std::cin >> menu;
	Valid_cin(menu);
	system("cls");
}


void CoinKeeper::add_category()
{
	vector<double> x;
	string str;

	std::cout << "\t\t\tCoinKeeper\t\t" << "Баланс: " << money << "\n";
	std::cout << "Укажите название категории: ";
	getline(std::cin,str);
	other_Category.insert(std::pair<string, vector<double>>(str, x));
	system("cls");
}

void CoinKeeper::delete_category()
{
	int x = 1;
	for (auto it = other_Category.begin(); it != other_Category.end(); it++)
	{
		std::cout << x++ << ")" << (it)->first << "\n";
	}
	std::cout<<x << ")Назад\n";

	std::cin >> menu;
	Valid_cin(menu);

	auto it = other_Category.begin();
	std::advance(it, menu-1);

	money += sum(it->second);

	other_Category.erase(it);

	system("cls");
}

void CoinKeeper::add_consumption(vector<double>& vect)
{
	double how_many;

	std::cout << "\t\t\tCoinKeeper\t\t" << "Баланс: " << money << "\n";
	std::cout << "Укажите количество потраченых денег: ";
	std::cin >> how_many;
	Valid_cin(how_many);

	if (how_many > money)
	{
		std::cout << "У вас нету таких денег!\n";
		system("pause");
		system("cls");
		return;
	}

	money -= how_many;

	vect.push_back(how_many);
	system("cls");
}

void CoinKeeper::add_consumption(int x) // списание денег из пользовательской категории путем итерации 
{
	double how_many;

	std::cout << "\t\t\tCoinKeeper\t\t" << "Баланс: " << money << "\n";
	std::cout << "Укажите количество потраченых денег: ";
	std::cin >> how_many;
	Valid_cin(how_many);

	if (how_many > money)
	{
		std::cout << "У вас нету таких денег!\n";
		system("pause");
		system("cls");
		return;
	}

	money -= how_many;

	auto it = other_Category.begin();
	std::advance(it, x);
	it->second.push_back(how_many);

	system("cls");
}

void CoinKeeper::add_money()
{
	double tmp;

	std::cout << "\t\t\tCoinKeeper\t\t" << "Баланс: " << money << "\n";
	std::cout << "Введите сколько денег вы хотите внести: ";
	std::cin >> tmp;
	Valid_cin(tmp);
	money += tmp;
	all_money += tmp;
	system("cls");
}


void CoinKeeper::info()
{
	auto it = other_Category.begin();

	std::cout << "\t\t\tCoinKeeper\t\t" << "Баланс: " << money << "\n";
	std::cout << "\t\t\tОтчет растрат\n\n"
		<< "Общее количество денег: " << all_money << "\n"
		<< "Текущий баланс: " << money << "\n"
		<< "Расход на еду: " << sum(food) << "\n"
		<< "Расход на развлечения: " << sum(fun) << "\n"
		<< "Расход на одежду: " << sum(clothes) << "\n"
		<< "Расход на медикаменты: " << sum(medeciny) << "\n";
	for (; it != other_Category.end(); it++)
	{
		std::cout << "Расход на " << it->first << ": " << sum(it->second) << "\n";
	}

	std::cout << "\nНаибольший расход: " << greated() << "\n";

	system("pause");
	system("cls");
}

double CoinKeeper::sum(vector<double>& vect)
{
	double sum = 0;

	for (int i = 0; i < vect.size(); i++)
	{
		sum += vect[i];
	}

	return sum;
}

double CoinKeeper::greated()
{
	double greated;
	vector<double> vect;
	double max = 0;

	max = std::accumulate(food.begin(), food.end(), 0.0);
	vect.push_back(max);

	max = std::accumulate(fun.begin(), fun.end(), 0.0);
	vect.push_back(max);

	max = std::accumulate(clothes.begin(), clothes.end(), 0.0);
	vect.push_back(max);

	max = std::accumulate(medeciny.begin(), medeciny.end(), 0.0);
	vect.push_back(max);

	for (auto it = other_Category.begin(); it != other_Category.end(); it++)
	{
		max = std::accumulate(it->second.begin(), it->second.end(), 0.0);
		vect.push_back(max);
	}

	greated = *std::max_element(vect.begin(), vect.end());

	return greated;
}

void CoinKeeper::full_info_menu()
{
	std::cout << "\t\t\tCoinKeeper\t\t" << "Баланс: " << money << "\n"
		<< "1)Еда\n"
		<< "2)Развлечения\n"
		<< "3)Одежда\n"
		<< "4)Медикаменты\n";

	int x = 5;
	for (auto it = other_Category.begin(); it != other_Category.end(); it++)
	{
		std::cout << x++ << ")" << (it)->first << "\n";
	}

	std::cout << x << ")Назад\n";

	std::cin >> menu;
	Valid_cin(menu);
	system("cls");
	print_category(menu);
}

void CoinKeeper::print_category(int x)
{
	switch (x)
	{
	case 1:
	{
		for (int i = 0; i < food.size(); i++)
		{
			std::cout << food[i] << "\n";
		}
		if (food.empty())
			std::cout << 0 << "\n";
		break;
	}
	case 2:
	{
		for (int i = 0; i < fun.size(); i++)
		{
			std::cout << fun[i] << "\n";
		}
		if (fun.empty())
			std::cout << 0 << "\n";
		break;
	}
	case 3:
	{
		for (int i = 0; i < clothes.size(); i++)
		{
			std::cout << clothes[i] << "\n";
		}
		if (clothes.empty())
			std::cout << 0 << "\n";
		break;
	}
	case 4:
	{
		for (int i = 0; i < medeciny.size(); i++)
		{
			std::cout << medeciny[i] << "\n";
		}
		if (medeciny.empty())
			std::cout << 0 << "\n";
		break;
	}
	}

	if (x == 5 + other_Category.size())
		return;

	if (x > 4)
	{
		auto it = other_Category.begin();
		std::advance(it, x - 5);
		for (int i = 0; i < it->second.size(); i++)
		{
			std::cout << it->second[i] << "\n";
		}
	}

	system("pause");
	system("cls");
}

void CoinKeeper::save()
{
	std::ofstream ofs;
	ofs.open(profile);
	if (ofs.is_open())
	{
		int size = food.size();
		ofs.write((char*)&size, sizeof(int));
		for (int i = 0; i < food.size(); i++)
		{
			ofs.write((char*)&food[i], sizeof(double));
		}

		size = fun.size();
		ofs.write((char*)&size, sizeof(int));
		for (int i = 0; i < fun.size(); i++)
		{
			ofs.write((char*)&fun[i], sizeof(double));
		}

		size = clothes.size();
		ofs.write((char*)&size, sizeof(int));
		for (int i = 0; i < clothes.size(); i++)
		{
			ofs.write((char*)&clothes[i], sizeof(double));
		}

		size = medeciny.size();
		ofs.write((char*)&size, sizeof(int));
		for (int i = 0; i < medeciny.size(); i++)
		{
			ofs.write((char*)&medeciny[i], sizeof(double));
		}

		size = other_Category.size();
		ofs.write((char*)&size, sizeof(int));
		auto it = other_Category.begin();
		for (int i = 0; i < other_Category.size(); i++)
		{
			size = it->first.size();
			ofs.write((char*)&size, sizeof(int));
			for (int i = 0; i < it->first.size(); i++)
			{
				ofs.write((char*)&it->first[i], sizeof(char));
			}

			size = it->second.size();
			ofs.write((char*)&size, sizeof(int));
			for (int i = 0; i < it->second.size(); i++)
			{
				ofs.write((char*)&it->second[i], sizeof(double));
			}

			it++;
		}

		ofs.write((char*)&money, sizeof(float));
		ofs.write((char*)&all_money, sizeof(float));

		ofs.close();
	}
	else
		std::cerr << "Error" << std::endl;
}

void CoinKeeper::load()
{
	std::ifstream ifs;
	ifs.open(profile);
	if (ifs.is_open())
	{
		int size = 0;
		ifs.read((char*)&size, sizeof(int));;
		for (int i = 0; i < size; i++)
		{
			double temp = 0;
			ifs.read((char*)&temp, sizeof(double));
			food.push_back(temp);
		}

		ifs.read((char*)&size, sizeof(int));
		for (int i = 0; i < size; i++)
		{
			double temp = 0;
			ifs.read((char*)&temp, sizeof(double));
			fun.push_back(temp);
		}

		ifs.read((char*)&size, sizeof(int));
		for (int i = 0; i < size; i++)
		{
			double temp = 0;
			ifs.read((char*)&temp, sizeof(double));
			clothes.push_back(temp);
		}

		ifs.read((char*)&size, sizeof(int));
		for (int i = 0; i < size; i++)
		{
			double temp = 0;
			ifs.read((char*)&temp, sizeof(double));
			medeciny.push_back(temp);
		}

		int size1;
		ifs.read((char*)&size1, sizeof(int));
		for (int i = 0; i < size1; i++)
		{
			double x_temp;
			vector<double> temp;
			std::string temp_str;

			ifs.read((char*)&size, sizeof(int));
			for (size_t i = 0; i < size; i++)
			{
				char x;
				ifs.read((char*)&x, sizeof(char));
				temp_str += x;
			}

			other_Category.insert(std::pair<string, vector<double>>(temp_str, temp));

			ifs.read((char*)&size, sizeof(int));
			for (int i = 0; i < size; i++)
			{
				ifs.read((char*)&x_temp, sizeof(double));
				other_Category[temp_str].push_back(x_temp);
			}
		}

		ifs.read((char*)&money, sizeof(float));
		ifs.read((char*)&all_money, sizeof(float));

		ifs.close();
	}
}