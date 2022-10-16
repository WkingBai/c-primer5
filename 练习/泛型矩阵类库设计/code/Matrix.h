# ifndef MATRIX_H_
# define MATRIX_H_

#include "MatrixBase.h"

template <typename T, size_t... sizes> 
class Matrix;

//****************************动态矩阵***********************
enum ROC { ROW, COL }; //枚举类型，用于判断矩阵行列拼接

template <class T>
concept Able = !(std::is_const<T>::value || std::is_volatile<T>::value || std::is_reference<T>::value || std::is_void<T>::value || std::is_pointer<T>::value);

template <typename T>
class Matrix<T> : public MatrixBase<MatrixDynamic<T>>
{
	static_assert(Able<T>, "The template parameter type is not legal");
public:
	//构造函数
	Matrix(const size_t r = 1, const size_t c = 1) : MatrixBase<MatrixDynamic<T>>(r, c) {}

	Matrix(const std::initializer_list<T>& list)
	{
		for (auto a : list) {
			this->elems.push_back(a);
		}
	}
	//拷贝构造函数
	Matrix(const Matrix& M)
	{
		this->rows = M.rows;
		this->cols = M.cols;
		this->elems = M.elems;
	}
	//移动构造函数
	Matrix(Matrix&& M) {
		this->rows = M.rows;
		this->cols = M.cols;
		M.rows = 0;
		M.cols = 0;
		this->elems.swap(M.elems);
	}

	//添加元素
	void push_back(const T v)
	{
		this->elems.push_back(v);
	}

	//修改矩阵尺寸
	void reshape(const size_t& r, const size_t& c);

	//运算符重载
	//Matrix operator= (Matrix& mat);
	Matrix operator+ (Matrix& mat);
	Matrix operator- (Matrix& mat);
	Matrix operator* (Matrix& mat);

	//矩阵拼接
	template<class T>
	friend Matrix<T> concatenate(Matrix<T>& mat1, Matrix<T>& mat2, ROC v);

	//析构函数
	~Matrix() {};
};


//修改矩阵尺寸
template <class T>
void Matrix<T>::reshape(const size_t& r, const size_t& c)
{
	this->rows = r;
	this->cols = c;
	auto size = this->rows * this->cols;
	if (size < this->elems.size())
	{
		auto n = this->elems.size() - size;
		while (n--)
			this->elems.pop_back();
	}
	else if (size > this->elems.size())
	{
		auto n = size - this->elems.size();
		while (n--)
			this->elems.push_back(0);
	}
}

//运算符重载
//=
/*
template <class T>
Matrix<T> Matrix<T>::operator= (Matrix& mat)
{
	this->rows = mat.rows;
	this->cols = mat.cols;
	Matrix<T> res(this->rows, this->cols);
	for (unsigned int i = 0; i < this->rows * this->cols; ++i) {
		this->elems[i] = mat.elems[i];
	}
	return res;
}
*/
//+
template <class T>
concept isAddable = requires(T a, T b)
{
	a + b;
};

template <class T>
Matrix<T> Matrix<T>::operator+ (Matrix& mat)
{
	static_assert(isAddable<T>, "This type is not support addition");
	if (this->rows == 0 || this->cols == 0 || !(this->rows == mat.rows && this->cols == mat.cols))
		throw "The matrix size is different and cannot be added";
	Matrix<T> res(this->rows, this->cols);
	size_t n = this->rows * this->cols;
	this->Add(n, this->elems, mat.elems, res.elems);
	return res;
}

//-
template <class T>
concept isMinable = requires(T a, T b)
{
	a - b;
};

template <class T>
Matrix<T> Matrix<T>::operator- (Matrix& mat)
{
	static_assert(isMinable<T>, "This type is not support subtraction");
	if (this->rows == 0 || this->cols == 0 || !(this->rows == mat.rows && this->cols == mat.cols))
		throw "The matrix size is different and cannot be subtracted";
	Matrix<T> res(this->rows, this->cols);
	size_t n = this->rows * this->cols;
	this->Minus(n, this->elems, mat.elems, res.elems);
	return res;
}

//* 
template <class T>
concept isMulable = requires(T a, T b)
{
	a * b;
};

template <class T>
Matrix<T> Matrix<T>::operator* (Matrix& mat)
{
	static_assert(isMulable<T>, "This type is not support multiplication");
	if (this->rows == 0 || this->cols == 0 || mat.rows == 0 || mat.cols == 0 || this->cols != mat.rows)
		throw "The matrix dimension does not satisfy the matrix multiplication definition";
	Matrix<T> res(this->rows, mat.cols);
	for (size_t i = 0; i < this->rows; ++i) {
		for (size_t j = 0; j < mat.cols; ++j) {
			T val = 0;
			for (size_t k = 0; k < this->cols; ++k) {
				val += (*this)[i][k] * mat[k][j];
			}
			res[i][j] = val;
		}
	}
	return res;
}

//矩阵拼接
template <class T>
Matrix<T> concatenate(Matrix<T>& mat1, Matrix<T>& mat2, ROC v)
{
	Matrix<T> res;
	if (v == COL) {
		if (mat1.cols != mat2.cols) {
			throw "The matrix columns is different and cannot be stitched";
		}
		res.rows = mat1.rows + mat2.rows;
		res.cols = mat1.cols;
		res.reshape(res.rows, res.cols);
		for (unsigned int i = 0; i < res.rows; ++i) {
			for (unsigned int j = 0; j < res.cols; ++j) {
				if (i < mat1.rows)
					res[i][j] = mat1[i][j];
				else
					res[i][j] = mat2[i - mat1.rows][j];
			}
		}
	}
	else if (v == ROW) {
		if (mat1.rows != mat2.rows) {
			throw "The matrix rows are different and cannot be stitched";
		}
		res.rows = mat1.rows;
		res.cols = mat1.cols + mat2.cols;
		res.reshape(res.rows, res.cols);
		for (unsigned int i = 0; i < res.rows; ++i) {
			for (unsigned int j = 0; j < res.cols; ++j) {
				if (j < mat1.cols)
					res[i][j] = mat1[i][j];
				else
					res[i][j] = mat2[i][j - mat1.cols];
			}
		}
	}
	else
	{
		throw "The specified stitching method is undefined";
	}
	return res;
}



//****************************静态矩阵***********************

template <typename T, size_t R, size_t C>
class Matrix<T, R, C> : public MatrixBase<MatrixStatic<T, R, C>>
{
	static_assert(Able<T>, "The template parameter type is not legal");
	static_assert((R !=0 && C!=0), "Matrix-dependent dimensions cannot be zero");
public:
	//构造函数
	Matrix() = default;
	Matrix(const std::initializer_list<T>& list)
	{
		std::copy(list.begin(), list.end(), this->elems.begin());
	}

	//改变矩阵尺寸
	template <size_t R_, size_t C_>
	Matrix<T, R_, C_> reshape();

	//运算符重载
	Matrix operator+ (Matrix& mat);
	Matrix operator- (Matrix& mat);

	template <size_t R_, size_t C_>
	Matrix<T, R, C_> operator* (Matrix<T, R_, C_>& mat);

	//矩阵拼接
	template<ROC Ty, typename T, size_t R1, size_t C1, size_t R2, size_t C2 >
	friend Matrix<T, R1 + Ty * R2, C1 + (1 - Ty) * C2 > concatenate(Matrix<T, R1, C1>& mat1, Matrix<T, R2, C2>& mat2);
	//析构函数
	~Matrix() {};
};



template<typename T, size_t R, size_t C>
template <size_t R_, size_t C_>
Matrix<T, R_, C_> Matrix<T, R, C>::reshape()
{
	Matrix<T, R_, C_> res;
	size_t n1 = R * C;
	size_t n2 = R_ * C_;
	if (n1 <= n2) {
		std::copy(this->elems.begin(), this->elems.end(), res.elems.begin());
	}
	else {
		std::copy(this->elems.begin(), this->elems.begin() + n2, res.elems.begin());
	}
	return res;
}

//运算符重载
//+
template<typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator+ (Matrix& mat)
{
	static_assert(isAddable<T>, "This type is not support addition");
	Matrix<T, R, C> res;
	size_t n = R * C;
	this->Add(n, this->elems, mat.elems, res.elems);
	return res;
}

//-
template<typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator- (Matrix& mat)
{
	static_assert(isMinable<T>, "This type is not support subtraction");
	Matrix<T, R, C> res;
	size_t n = R * C;
	this->Minus(n, this->elems, mat.elems, res.elems);
	return res;
}


//*
template<typename T, size_t R, size_t C>
template <size_t R_, size_t C_>
Matrix<T, R, C_> Matrix<T, R, C>::operator* (Matrix<T, R_, C_>& mat)
{
	static_assert(isMulable<T>, "This type is not support multiplication");
	if (C != R_)
		throw "The matrix dimension does not satisfy the matrix multiplication definition";
	Matrix<T, R, C_> res;
	for (size_t i = 0; i < R; ++i) {
		for (size_t j = 0; j < C_; ++j) {
			T val = 0;
			for (size_t k = 0; k < C; ++k) {
				val += (*this)[i][k] * mat[k][j];
			}
			res[i][j] = val;
		}
	}
	return res;
}

//矩阵拼接
template<ROC Ty, typename T, size_t R1, size_t C1, size_t R2, size_t C2 >
Matrix<T, R1 + Ty * R2, C1 + (1 - Ty) * C2 > concatenate(Matrix<T, R1, C1>& mat1, Matrix<T, R2, C2>& mat2)
{
	Matrix<T, R1 + Ty * R2, C1 + (1 - Ty) * C2 > res;
	if (Ty == COL) {
		if (C1 != C2) {
			throw "The matrix columns is different and cannot be stitched";
		}
		for (size_t i = 0; i < res.rows; ++i) {
			for (size_t j = 0; j < res.cols; ++j) {
				if (i < R1)
					res[i][j] = mat1[i][j];
				else
					res[i][j] = mat2[i - R1][j];
			}
		}
	}
	else if (Ty == ROW) {
		if (R1 != R2) {
			throw "The matrix rows are different and cannot be stitched";
		}
		for (size_t i = 0; i < res.rows; ++i) {
			for (size_t j = 0; j < res.cols; ++j) {
				if (j < C1)
					res[i][j] = mat1[i][j];
				else
					res[i][j] = mat2[i][j - C1];
			}
		}
	}
	else
	{
		throw "The specified stitching method is undefined";
	}
	return res;
}
#endif
