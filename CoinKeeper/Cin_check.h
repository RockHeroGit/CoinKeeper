#pragma once

template <typename T>
void Valid_cin (T& x)
{
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "Вы ввели недопустимое значение. Повторите ввод.\n";
		
		std::cin >> x;
		return Valid_cin(x);
	}
	else
	{
		std::cin.ignore(32767, '\n');
		return;
	}
}
