#include <iostream>

int main()
{

		int number;
		std::cout << std::endl << "Write number: ";
		std::cin >> number;

		if (number < 1)
		{
			std::cout << "You write wrong nuber";
			return;
		}

		int result = 0;
		int size_pn = 0;

		int *prime_number = new int[number];
		for (int i = 2; i <= number; i++)
		{

			bool prost = true;

			if (i != 2)
			{
				for (int j = 0; j < size_pn; j++)
					if (i % prime_number[j] == 0)
						prost = false;
			}


			if (prost)
			{
				prime_number[size_pn] = i;
				size_pn++;
			}
		}

		if (prime_number[size_pn - 1] == number)
		{
			result = number - 1;
		}
		else
		{
			int size_dpn = 0;
			int *divide_prime_number = new int[size_pn];
			for (int i = 0; i <= size_pn; i++)
			{
				if (number % prime_number[i] == 0)
				{
					divide_prime_number[size_dpn] = prime_number[i];
					size_dpn++;
				}
			}

			size_pn = 0;

			for (int i = 1; i < number; i++)
			{
				bool check = false;

				for (int j = 0; j < size_dpn; j++)
				{
					if (i % divide_prime_number[j] == 0)
					{
						check = true;
					}
				}

				if (check)
					size_pn++;
			}

			result = number - 1 - size_pn;

			delete[] divide_prime_number;
		}

		delete[] prime_number;

		if (number == 1)
			result = 1;

		std::cout << result;
}
