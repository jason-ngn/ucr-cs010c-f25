#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Matrix2D
{
private:
	T **dynamic_array = new T *[3];

public:
	Matrix2D()
	{
		for (int i = 0; i < 3; i++)
		{
			dynamic_array[i] = new T[4];
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				dynamic_array[i][j] = i + j;
			}
		}
	}
	~Matrix2D()
	{
		for (int i = 0; i < 3; i++)
		{
			delete[] dynamic_array[i];
		}

		delete[] dynamic_array;
	}

	friend ostream &operator<<(ostream &out, const Matrix2D<T> &rhs)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out << rhs.dynamic_array[i][j] << " ";
			}
			out << "\n";
		}
		return out;
	}

	void Display()
	{
		cout << dynamic_array;
	}
};