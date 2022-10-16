#include <iostream>
#include <type_traits>
using namespace std;


//���鶨��
template<unsigned... >
class Cont;

//��ӡ�������� print
template<typename T>
struct print;

template<unsigned T, unsigned... TRemain>
struct print<Cont<T, TRemain...>>
{
	inline static void fun()
	{
		if constexpr (T < 10)
			cout << T;
		if constexpr (T >= 10) {
			constexpr static char  t = T - 10 + 'a';
			cout << t;
		}

		print<Cont<TRemain...>>::fun();
	}
};

template<>
struct print<Cont<>>
{
	inline static void fun()
	{
		cout << endl;
	}
};

//��ת����
template<typename T, typename S>
struct Reverse;

template <unsigned... Processed, unsigned T, unsigned... TRemain>
struct Reverse<Cont<Processed...>, Cont<T, TRemain...>>
{
	using type1 = Cont<T, Processed...>;
	using type = typename Reverse<type1, Cont<TRemain...>>::type;
};

template <unsigned... Processed>
struct Reverse<Cont<Processed...>, Cont<>>
{
	using type = Cont<Processed...>;
};

////�ӷ�����

//��λ
template<unsigned T, typename = void>
struct Carry;

template<unsigned T>
struct Carry<T, enable_if_t<(T < 10)>>
{
	constexpr static unsigned cf = 0;
	constexpr static unsigned value = T;
};

template<unsigned T>
struct Carry<T, enable_if_t<(T >= 10)>>
{
	constexpr static unsigned cf = 1;
	constexpr static unsigned value = T - 10;
};

//�������
template<typename...T>
struct Plus;

template<unsigned T1, unsigned...T1Remain, unsigned T2, unsigned... T2Remain, unsigned Cf, unsigned... Res>
struct Plus<Cont<T1, T1Remain...>, Cont<T2, T2Remain...>, Cont<Cf>, Cont<Res...>>
{
	constexpr static unsigned cf = Carry<T1 + T2 + Cf>::cf;
	constexpr static unsigned value = Carry<T1 + T2 + Cf>::value;

	using type = typename Plus<Cont<T1Remain...>, Cont<T2Remain...>, Cont<cf>, Cont<Res..., value>>::type;
};

//����T2Ϊ��
template<unsigned T, unsigned...TRemain, unsigned Cf, unsigned... Res>
struct Plus<Cont<T, TRemain...>, Cont<>, Cont<Cf>, Cont<Res...>>
{
	constexpr static unsigned cf = Carry<T + Cf>::cf;
	constexpr static unsigned value = Carry<T + Cf>::value;

	using type = typename Plus<Cont<TRemain...>, Cont<>, Cont<cf>, Cont<Res..., value>>::type;
};

//����T1Ϊ��
template<unsigned T, unsigned...TRemain, unsigned Cf, unsigned... Res>
struct Plus<Cont<>, Cont<T, TRemain...>, Cont<Cf>, Cont<Res...>>
{
	constexpr static unsigned cf = Carry<T + Cf>::cf;
	constexpr static unsigned value = Carry<T + Cf>::value;

	using type = typename Plus<Cont<>, Cont<TRemain...>, Cont<cf>, Cont<Res..., value>>::type;
};

//����T1��T2��Ϊ�� ��������
template<unsigned Cf, unsigned... Res>
struct Plus<Cont<>, Cont<>, Cont<Cf>, Cont<Res...>>
{
	using type = conditional_t<Cf, Cont<Res..., Cf>, Cont<Res...>>;
};

//***************��չ***********************
//bool 
template <unsigned T>
constexpr bool isNum = (T < 10);

template <unsigned T>
constexpr bool isChar_B = ((T >= 65) && (T <= 90));

template <unsigned T>
constexpr bool isChar_L = ((T >= 97) && (T <= 122));

template <unsigned T>
constexpr bool isBad = !isNum<T> && !isChar_B<T> && !isChar_L<T>;



//ɾ0
template<typename T, typename = void>
struct DelZero;

template<unsigned T, unsigned... TRemain>
struct DelZero<Cont<T, TRemain...>, enable_if_t<(T == 0)>>
{
	using type = typename DelZero<Cont<TRemain...>>::type;
};

template<unsigned T, unsigned... TRemain>
struct DelZero<Cont<T, TRemain...>, enable_if_t<(T > 0)>>
{
	using type = Cont<T, TRemain...>;
};

template<>
struct DelZero<Cont<>>
{
	using type = Cont<>;
};

//����˷�����
template<typename...T>
struct Mul;

template<unsigned T, unsigned...TRemain, unsigned S, unsigned Cf, unsigned... Res>
struct Mul<Cont<T, TRemain...>, Cont<S>, Cont<Cf>, Cont<Res...>>
{
	constexpr static unsigned temp = T * S + Cf;
	constexpr static unsigned cf = temp / 10;
	constexpr static unsigned value = temp % 10;

	using type = typename Mul<Cont<TRemain...>, Cont<S>, Cont<cf>, Cont<Res..., value>>::type;

};

template<unsigned S, unsigned Cf, unsigned... Res>
struct Mul<Cont<>, Cont<S>, Cont<Cf>, Cont<Res...>>
{
	constexpr static unsigned nt = Cf / 10;
	constexpr static unsigned ng = Cf % 10;
	using type1 = Cont<Res..., ng, nt>;
	using type2 = typename Reverse<Cont<>, type1>::type;
	using type3 = typename DelZero<type2>::type;
	using type = typename Reverse<Cont<>, type3>::type;
};

template<unsigned S, unsigned Cf>
struct Mul<Cont<>, Cont<S>, Cont<Cf>, Cont<>>
{
	using type = Cont<>;
};



//M ����ת 10���� (�� ����
template <typename... T>
struct MtoTen;

template<unsigned T, unsigned... TRemain, unsigned S, unsigned... Res>
struct MtoTen< Cont<T, TRemain...>, Cont<S>, Cont<Res...>>
{

	using type1 = typename Mul<Cont<Res...>, Cont<S>, Cont<0>, Cont<>>::type;
	using type2 = typename Plus<type1, Cont<T>, Cont<0>, Cont<>>::type;
	using type = typename MtoTen<Cont<TRemain...>, Cont<S>, type2>::type;
};

template<unsigned S, unsigned... Res>
struct MtoTen< Cont<>, Cont<S>, Cont<Res...>>
{
	using type = typename Reverse<Cont<>, Cont<Res...>>::type;
};

//�������
template<typename...T>
struct Div;

template<unsigned T, unsigned...TRemain, unsigned D, unsigned B, unsigned... Res>
struct Div<Cont<T, TRemain...>, Cont<D>, Cont<B>, Cont<Res...>>
{
	constexpr static unsigned temp = B * 10 + T;
	constexpr static unsigned value = temp / D;
	constexpr static unsigned remain = temp % D;

	using type = typename Div<Cont<TRemain...>, Cont<D>, Cont<remain>, Cont<Res..., value>>::type;
	constexpr static unsigned ret = Div<Cont<TRemain...>, Cont<D>, Cont<remain>, Cont<Res..., value>>::ret;
};

template<unsigned D, unsigned B, unsigned... Res>
struct Div<Cont<>, Cont<D>, Cont<B>, Cont<Res...>>
{
	using type = typename DelZero<Cont<Res...>>::type;
	constexpr static unsigned ret = B;
};
//10 ����ת N���ƣ��� ����
template <typename... T>
struct TentoN;

template<unsigned... T, unsigned D, unsigned... Res>
struct TentoN<Cont<T...>, Cont<D>, Cont<Res...>>
{
	using A_t = typename Div<Cont<T...>, Cont<D>, Cont<0>, Cont<>>::type;
	constexpr static unsigned A_r = Div<Cont<T...>, Cont<D>, Cont<0>, Cont<>>::ret;
	using type = typename TentoN<A_t, Cont<D>, Cont<A_r, Res...>>::type;
};

template<unsigned D, unsigned... Res>
struct TentoN<Cont<>, Cont<D>, Cont<Res...>>
{
	using type = Cont<Res...>;
};


// ����ת��

template<typename T, typename S, typename = void>
struct Atoi;

template<unsigned T, unsigned... TRemain, unsigned... res>
struct Atoi<Cont<T, TRemain...>, Cont<res...>, enable_if_t<isNum<T>>>
{
	using type = typename Atoi<Cont<TRemain...>, Cont<res..., T >> ::type;
};

template<unsigned T, unsigned... TRemain, unsigned... res>
struct Atoi<Cont<T, TRemain...>, Cont<res...>, enable_if_t<isChar_B<T>>>
{
	constexpr static unsigned num = T - 65 + 10;
	using type = typename Atoi<Cont<TRemain...>, Cont<res..., num>>::type;
};

template<unsigned T, unsigned... TRemain, unsigned... res>
struct Atoi<Cont<T, TRemain...>, Cont<res...>, enable_if_t<isChar_L<T>>>
{
	constexpr static unsigned num = T - 97 + 10;
	using type = typename Atoi<Cont<TRemain...>, Cont<res..., num>>::type;
};

template<unsigned... res>
struct Atoi<Cont<>, Cont<res...>>
{
	using type = Cont<res...>;
};

//����Ϸ��Լ��	

template <typename T, unsigned M, typename S>
struct Check;

template<unsigned T, unsigned... TRemain, unsigned M, unsigned... Res>
struct Check < Cont<T, TRemain...>, M, Cont<Res...>>
{
	static_assert((T < M), "The array contains illegal numeric values that are greater than or equal to the input base number.");
	using type = typename Check<Cont<TRemain...>, M, Cont<Res..., T>>::type;
};

template<unsigned M, unsigned... Res>
struct Check<Cont<>, M, Cont<Res...>>
{
	using type = Cont<Res...>;
};

//M���� ת N����
template<typename T, unsigned M, unsigned N>
struct Convert;

template<unsigned...T, unsigned M, unsigned N>
struct Convert<Cont<T...>, M, N>
{

	static_assert((M <= 36 && M > 1), "The input base number is not legal.");
	static_assert((N <= 36 && N > 1), "The output base number is not legitimate.");
	using a = typename Check<Cont<T...>, M, Cont<>>::type;
	using type1 = typename MtoTen<a, Cont<M>, Cont<>>::type;
	using type = typename TentoN<type1, Cont<N>, Cont<>>::type;
};

int main()
{
	cout << "***********���������***********\n";
	using a1 = Cont<1,9, 9>; //����1
	using a2 = Cont<1>;       //����2
	cout << "����1: ";
	print<a1>::fun();
	cout << "����2: ";
	print<a2>::fun();
	using R_a1 = Reverse<Cont<>, a1>::type;  //��ת����1
	using R_a2 = Reverse<Cont<>, a2>::type;  //��ת����2
	using R_add = Plus<R_a1, R_a2, Cont<0>, Cont<>>::type; //��ת����ӽ��
	cout << "��ӽ����";
	using add = Reverse<Cont<>, R_add>::type;  //���ս��
	print<add>::fun();
	cout << "\n\n***********��չ���֣�����ת����***********\n";
// ��չ���֣�����ת����
	using a3 = Cont<'a','C',7>;
	constexpr unsigned M = 16 ; //������� (2 <= M <= 36��
	constexpr unsigned N = 8; //������� (2 <= N <= 36��
	using a4 = Atoi<a3, Cont<>>::type; // ����ת����char -> unsigned)
	cout << M << "���ƴ�ת������: ";
	print<a4>::fun();  //��ʾ��ת������
	using res = Convert<a4, M, N>::type; //��M����ת��ΪN����
	cout << "ת��Ϊ" << N << "���ƽ��: ";
	print<res>::fun();
	return 0;
}