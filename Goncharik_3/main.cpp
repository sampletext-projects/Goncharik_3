#include <iostream>
#include <conio.h>
#include <math.h>
#include <exception>
#include <iomanip>

using namespace std;

#define debug false

class Matrix
{
	int** m_;
public:

	Matrix()
	{
		if (debug) cout << "Matrix Empty Constructor\n";
		m_ = new int*[3];
		m_[0] = new int[3]{0};
		m_[1] = new int[3]{0};
		m_[2] = new int[3]{0};
	}

	Matrix(Matrix& m) : Matrix()
	{
		if (debug) cout << "Matrix Copy Constructor\n";
		// copy values
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->set(i, j, m.get(i, j));
			}
		}
	}

	int get(int x, int y)
	{
		if (debug) cout << "Matrix Get " << x << " " << y << "\n";
		if (x < 0 || x >= 3)
		{
			throw new invalid_argument("x is incorrect");
		}
		if (y < 0 || y >= 3)
		{
			throw new invalid_argument("y is incorrect");
		}
		return m_[x][y];
	}

	void set(int x, int y, int val)
	{
		if (debug) cout << "Matrix Set " << x << " " << y << ": " << val << "\n";
		if (x < 0 || x >= 3)
		{
			throw new invalid_argument("x is incorrect");
		}
		if (y < 0 || y >= 3)
		{
			throw new invalid_argument("y is incorrect");
		}
		m_[x][y] = val;
	}

	Matrix& operator+(Matrix& matrix)
	{
		if (debug) cout << "Matrix Operator+\n";
		Matrix* m = new Matrix();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m->set(i, j, this->get(i, j) + matrix.get(i, j));
			}
		}
		return *m;
	}

	Matrix& operator+=(Matrix& matrix)
	{
		if (debug) cout << "Matrix Operator+=\n";
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->set(i, j, this->get(i, j) + matrix.get(i, j));
			}
		}
		return *this;
	}

	Matrix& operator-(Matrix& matrix)
	{
		if (debug) cout << "Matrix Operator-\n";
		Matrix* m = new Matrix();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m->set(i, j, this->get(i, j) - matrix.get(i, j));
			}
		}
		return *m;
	}

	Matrix& operator-=(Matrix& matrix)
	{
		if (debug) cout << "Matrix Operator-=\n";
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->set(i, j, this->get(i, j) - matrix.get(i, j));
			}
		}
		return *this;
	}

	Matrix& operator*(Matrix& matrix)
	{
		if (debug) cout << "Matrix Operator* matrix\n";
		Matrix* m = new Matrix();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int sum = 0;
				for (int k = 0; k < 3; ++k)
				{
					sum += this->get(i, k) * matrix.get(k, j);
				}
				m->set(i, j, sum);
			}
		}
		return *m;
	}

	Matrix& operator*=(Matrix& matrix)
	{
		if (debug) cout << "Matrix Operator*= matrix\n";
		// multiply 
		Matrix m = *this * matrix;

		// copy into this
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->set(i, j, m.get(i, j));
			}
		}
		return *this;
	}

	Matrix& operator*(int val)
	{
		if (debug) cout << "Matrix Operator* int\n";
		Matrix* m = new Matrix();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m->set(i, j, this->get(i, j) * val);
			}
		}
		return *m;
	}

	Matrix& operator*=(int val)
	{
		if (debug) cout << "Matrix Operator* int\n";
		// multiply 
		Matrix m = *this * val;

		// copy into this
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->set(i, j, m.get(i, j));
			}
		}
		return *this;
	}

	int det()
	{
		if (debug) cout << "Matrix det()\n";
		// bruteforce determinant formula
		// https://en.wikipedia.org/wiki/Determinant
		int res = this->get(0, 0) * this->get(1, 1) * this->get(2, 2) +
		          this->get(0, 1) * this->get(1, 2) * this->get(2, 0) +
		          this->get(0, 2) * this->get(1, 0) * this->get(2, 1) -
		          this->get(0, 2) * this->get(1, 1) * this->get(2, 0) -
		          this->get(0, 1) * this->get(1, 0) * this->get(2, 2) -
		          this->get(0, 0) * this->get(1, 2) * this->get(2, 1);
		return res;
	}

	friend std::ostream& operator<<(std::ostream& out, Matrix& m)
	{
		if (debug) cout << "Matrix Operator<<\n";
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				out << setw(5) << m.get(i, j) << " ";
			}
			out << "\n";
		}
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Matrix& m)
	{
		if (debug) cout << "Matrix Operator>>\n";
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				int t;
				in >> t;
				m.set(i, j, t);
			}
		}
		return in;
	}

	~Matrix()
	{
		if (debug) cout << "Matrix Destructor\n";
		delete[] m_[0];
		delete[] m_[1];
		delete[] m_[2];
		delete[] m_;
	}
};

class MatrixArray
{
	// amount of existing matrices
	int rm_;
	// amount of reserved matrices
	int m_;
	Matrix* matrices_;
public:
	MatrixArray(int m)
	{
		m_ = m;
		rm_ = 0;
		matrices_ = new Matrix[m];
	}

	Matrix& sum()
	{
		Matrix* accumulator = new Matrix();
		if (rm_ == 0) return *accumulator;
		for (int i = 0; i < rm_; i++)
		{
			*accumulator += matrices_[i];
		}
		return *accumulator;
	}

	int find_max_det_index()
	{
		if (rm_ == 0) return 0;
		int max_det = matrices_[0].det();
		int max_index = 0;
		for (int i = 1; i < rm_; i++)
		{
			int det = matrices_[i].det();
			if (det > max_det)
			{
				max_det = det;
				max_index = i;
			}
		}
		return max_index;
	}

	void subtract_multiplication_multiplied_by_max_det_from_item_with_largest_det()
	{
		if (rm_ == 0) return;
		 
		// find max det index
		int max_det_index = find_max_det_index();

		// find multiplication of all matrixes
		Matrix multiplication = matrices_[0];

		for (int i = 1; i < rm_; i++)
		{
			multiplication *= matrices_[i];
		}

		// multiply multiplication by max det
		multiplication *= matrices_[max_det_index].det();

		// subtract the result from matrix with max det
		matrices_[max_det_index] -= multiplication;
	}

	friend std::ostream& operator<<(std::ostream& out, MatrixArray& m)
	{
		if (m.rm_ == 0) return out;
		for (int i = 0; i < m.rm_; i++)
		{
			out << "[" << i << "]: \n" << m.matrices_[i] << "\n";
		}
		return out;
	}

	void add(Matrix& m)
	{
		if (rm_ < m_)
		{
			matrices_[rm_] = m;
			rm_++;
		}
	}

	~MatrixArray()
	{
		delete[] matrices_;
	}
};

int main()
{
	MatrixArray matrix_array(3);

	if (debug) cout << "default matrix init\n";
	Matrix default_matrix;
	default_matrix.set(0, 0, 1);
	default_matrix.set(0, 1, 2);
	default_matrix.set(0, 2, 1);
	default_matrix.set(1, 0, 1);
	default_matrix.set(1, 1, 3);
	default_matrix.set(1, 2, 2);
	default_matrix.set(2, 0, 1);
	default_matrix.set(2, 1, 1);
	default_matrix.set(2, 2, 1);


	for (int i = 0; i < 3; i++)
	{
		if (debug) cout << "matrix m constructed in main\n";
		Matrix* m = new Matrix(default_matrix);
		for (int j = 0; j < i; j++)
		{
			if (debug) cout << "matrix m multiplied by default_matrix in main\n";
			*m *= default_matrix;
		}
		// cin >> m;
		if (debug) cout << "matrix m added to matrix_array in main\n";
		matrix_array.add(*m);
	}

	cout << matrix_array << "\n";

	matrix_array.subtract_multiplication_multiplied_by_max_det_from_item_with_largest_det();

	cout << matrix_array << "\n";

	return 0;
}
