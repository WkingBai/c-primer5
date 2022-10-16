# ifndef MATRIXBASE_H_
# define MATRIXBASE_H_

#include<iostream>
#include<initializer_list>
#include<vector>
#include<array>
#include<type_traits>

template <typename T>
class MatrixDynamic {
public:
	using type = std::vector<T>;
	using T_ = T;
	MatrixDynamic() = default;
	MatrixDynamic(const size_t r, const size_t c) 
		: rows(r), cols(c), elems(std::vector<T>(r* c)) {}
	~MatrixDynamic() = default;
protected:
	size_t rows;
	size_t cols;
	std::vector<T> elems;
};

template <typename T, size_t R, size_t C>
class MatrixStatic {
public:
	using type = std::array<T, R* C>;
	using T_ = T;
	MatrixStatic() = default;
	~MatrixStatic() = default;

	static constexpr size_t rows = R;
	static constexpr size_t cols = C;
	std::array<T, R* C> elems{};
};

template <class T>
class MatrixBase : public T
{
public:
	using type =  T::type;
	using T_ = T::T_;

	//构造函数
	MatrixBase() = default;
	MatrixBase(const size_t r, const size_t c) : T(r, c) {}

	//打印矩阵
	void Mat_Print()
	{
		for (unsigned int i = 0; i < this->rows; ++i) {
			for (unsigned int j = 0; j < this->cols; ++j) {
				std::cout << *(this->elems.begin() + i * this->cols + j) << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	//[]操作符重载
	typename type::iterator operator[] (std::size_t idx)
	{
		return this->elems.begin() + (idx * this->cols);
	}

	//访问元素
	T_& at(const size_t& n)
	{
		if (n >= this->elems.size())
			throw "Matrix subscript out of bounds";
		return this->elems[n];
	}

	T_ at(const size_t& n) const
	{
		if (n >= this->elems.size())
			throw "Matrix subscript out of bounds";
		return this->elems[n];
	}

	//矩阵运算
	static void Add(size_t n, const type& lhs, const type& rhs, type& res);
	static void Minus(size_t n, const type& lhs, const type& rhs, type& res);

	//析构函数
	~MatrixBase() {};
};

template <class T>
void MatrixBase<T>::Add(size_t n, const type& lhs, const type& rhs, type& res)
{
	for (size_t i = 0; i < n; ++i) {
		res[i] = lhs[i] + rhs[i];
	}
}

template <class T>
void MatrixBase<T>::Minus(size_t n, const type& lhs, const type& rhs, type& res)
{
	for (size_t i = 0; i < n; ++i) {
		res[i] = lhs[i] - rhs[i];
	}
}

#endif
