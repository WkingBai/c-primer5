#include "Matrix.h"

using namespace std;

struct AddOnly
{
	int v;
	AddOnly operator +(AddOnly& rop)
	{
		return AddOnly{ v + rop.v };
	}
};

int main()
{
	try {
	/*
	//*******************动态矩阵测试************************
		//Matrix<void*> mat1;
		//Matrix<const int> mat1;
		//Matrix<int*> mat1;
		//Matrix< volatile int> mat1;
		//Matrix<int&> mat1;
		//以上均非法
		Matrix<int> mat1;
		cout << "mat1:" << endl;
		mat1.Mat_Print();

		Matrix<int> mat2(2, 2);
		cout << "mat2:" << endl;
		mat2.Mat_Print();
		mat2[1][0] = 42;
		cout << "mat2.at(2): ";
		cout << mat2.at(2) << endl; //通过at访问
		mat2.at(1) = 1;   //通过at赋值
		//mat2.at(5);  //越界抛出错误
		mat2.push_back(13);
		mat2.push_back(14);
		mat2.reshape(3, 3);
		cout << "mat2(3,3):" << endl;
		mat2.Mat_Print();

		Matrix<int> mat3{ 1, 2, 3, 4 };
		Matrix<int> mat4{ 5, 6, 7, 8 };
		Matrix<int> mat5{ 2, 4, 6, 8 };
		mat3.reshape(2, 3);
		mat4.reshape(2, 3);
		mat5.reshape(3, 2);
		cout << "mat3:" << endl;
		mat3.Mat_Print();
		cout << "mat4:" << endl;
		mat4.Mat_Print();
		cout << "mat5:" << endl;
		mat5.Mat_Print();
		auto mat_add = mat3 + mat4;
		cout << "mat3 + mat4:" << endl;
		mat_add.Mat_Print();
		auto mat_min = mat4 - mat3;
		cout << "mat4 - mat3:" << endl;
		mat_min.Mat_Print();
		//auto mat_mul = mat3 * mat4; //不满足矩阵乘法定义， 抛出异常
		auto mat_mul = mat3 * mat5;
		cout << "mat3 * mat5:" << endl;
		mat_mul.Mat_Print();

		//Matrix<AddOnly> mat;
		// mat + mat; //无编译错误
		// mat - mat; //编译错误
		//mat * mat; //编译错误

		Matrix<int> con_r = concatenate(mat3, mat4, ROW); //矩阵行拼接
		cout << "mat3、mat4 行拼接:" << endl;
		con_r.Mat_Print();
		Matrix<int> con_c = concatenate(mat3, mat4, COL); //矩阵列拼接
		cout << "mat3、mat4 列拼接:" << endl;
		con_c.Mat_Print();

		//Matrix<int> con = concatenate(mat3, mat5, COL);  //不满足矩阵拼接要求，抛出异常
		//Matrix<int> con = concatenate(mat3, mat5, ROW);  //不满足矩阵拼接要求，抛出异常
		*/

	//*******************静态矩阵测试************************

		//Matrix<int, 0, 0> mat;  //编译错误 （矩阵相关尺寸不能为0）
		//以上均非法
		Matrix<int, 3, 3> mat{ 1,2,3,4,5,6,7,8,9 };
		mat.Mat_Print();
		mat[2][2] = 11;
		mat.at(1) = 10; //通过at赋值
		mat.Mat_Print();

		Matrix<int, 3, 4> mat1{ 1,2,3,4,5,6,7,8,9,10,11,12 };
		mat1.Mat_Print();
		Matrix<int, 3, 4> mat2{ 1,2,3,4,5,6,7,8,9,10,11,12 };
		mat2.Mat_Print();
		Matrix<int, 3, 3> mat3{ 9,8,7,6,5,4,3,2,1 };
		mat3.Mat_Print();

		Matrix<int, 4, 3> res = mat1.reshape<4, 3>(); // 改变矩阵尺寸
		res.Mat_Print();

		Matrix<int, 3, 4> Add = mat1 + mat2; //矩阵相加
		Add.Mat_Print();

		Matrix<int, 3, 4> Min = mat1 - mat2; //矩阵相减
		Min.Mat_Print();

		Matrix<int, 3, 3> Mul = mat1 * res;//矩阵相乘
		Mul.Mat_Print();

		Matrix<int, 3, 7> con_r = concatenate<ROW>(mat1, mat3); //矩阵按行拼接
		con_r.Mat_Print();

		Matrix<int, 6, 4> con_c = concatenate<COL>(mat1, mat2); //矩阵按列拼接
		con_c.Mat_Print();




	}
	catch (char const* str)
	{
		cout << "ERROR:" << str << endl;
	}
	

}