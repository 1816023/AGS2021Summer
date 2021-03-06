#pragma once
template<class T>
class VECTOR2_TEMPLE
{
public:
	VECTOR2_TEMPLE();
	VECTOR2_TEMPLE(T x, T y);
	~VECTOR2_TEMPLE();
	T x;
	T y;
	//代入演算子------------------------------------------
	VECTOR2_TEMPLE& operator = (const VECTOR2_TEMPLE& vec);

	//添え字演算子----------------------------------------
	T& operator[](int i);

	//比較演算子------------------------------------------
	  /*読み込み専用で使用するときのみconstを使用する*/
	bool operator==(const VECTOR2_TEMPLE& vec)const
	{
		return ((this->x == vec.x) && (this->y == vec.y));
	}
	bool operator>=(const VECTOR2_TEMPLE& vec)const
	{
		return ((this->x >= vec.x) && (this->y >= vec.y));
	}
	bool operator<=(const VECTOR2_TEMPLE& vec)const
	{
		return ((this->x <= vec.x) && (this->y <= vec.y));
	}
	bool operator>(const VECTOR2_TEMPLE& vec)const
	{
		return ((this->x > vec.x) && (this->y > vec.y));
	}
	bool operator<(const VECTOR2_TEMPLE& vec)const
	{
		return ((this->x < vec.x) && (this->y < vec.y));
	}
	bool operator!=(const VECTOR2_TEMPLE& vec)const
	{
		return !((this->x == vec.x) && (this->y == vec.y));
		/*return ((this->x != vec.x) || (this->y != vec.y));*/
	}

	// 切り捨て
	VECTOR2_TEMPLE<float> Floor();
	// 四捨五入
	VECTOR2_TEMPLE<float> Round();
	// 大きさ
	float Magnitude();
	// 正規化
	VECTOR2_TEMPLE<float> Normarize();

	//単項演算子------------------------------------------
	VECTOR2_TEMPLE& operator +=(const VECTOR2_TEMPLE& vec);
	VECTOR2_TEMPLE& operator -=(const VECTOR2_TEMPLE& vec);
	VECTOR2_TEMPLE& operator *=(T k);
	VECTOR2_TEMPLE& operator /=(T k);
	VECTOR2_TEMPLE& operator +=(const T& vec);
	VECTOR2_TEMPLE& operator -=(const T& vec);

	VECTOR2_TEMPLE operator+()const;
	VECTOR2_TEMPLE operator-()const;
};

//ﾍﾞｸﾄﾙの演算//////////////////////////////////
//VECTOR2 + int-------------------------------- 
template<class T>
VECTOR2_TEMPLE<T> operator+(const VECTOR2_TEMPLE<T>& u, T v);

//VECTOR2 - int--------------------------------
template<class T>
VECTOR2_TEMPLE<T> operator-(const VECTOR2_TEMPLE<T>& u, T v);

//VECTOR2 * int--------------------------------
template<class T>
VECTOR2_TEMPLE<T> operator*(const VECTOR2_TEMPLE<T>& u, T v);

//VECTOR2 / int--------------------------------
template<class T>
VECTOR2_TEMPLE<T> operator/(const VECTOR2_TEMPLE<T>& u, T v);

//VECTOR2 % int--------------------------------
template<class T>
VECTOR2_TEMPLE<T> operator%(const VECTOR2_TEMPLE<T>& u, T v);

//int * VECTOR2--------------------------------
template<class T>
VECTOR2_TEMPLE<T> operator+(T u, const VECTOR2_TEMPLE<T>& v);

//VECTOR2 + VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator+(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<T>& v);

//VECTOR2 - VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator-(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<T>& v);

//VECTOR2 * VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator*(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<T>& v);

//VECTOR2 / VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator/(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<T>& v);

//VECTOR2 / VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator%(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<T>& v);

//VECTOR2 + Vec2Float----------------------------
static VECTOR2_TEMPLE<float> operator+(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<float>& v);

//VECTOR2 - Vec2Float----------------------------
static VECTOR2_TEMPLE<float> operator-(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<float>& v);

//VECTOR2 * Vec2Float----------------------------
static VECTOR2_TEMPLE<float> operator*(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<float>& v);

//VECTOR2 / Vec2Float----------------------------
static VECTOR2_TEMPLE<float> operator/(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<float>& v);

//Vec2Float + VECTOR2----------------------------
static VECTOR2_TEMPLE<float> operator+(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<int>& v);

//Vec2Float - VECTOR2----------------------------
static VECTOR2_TEMPLE<float> operator-(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<int>& v);

//Vec2Float * VECTOR2----------------------------
static VECTOR2_TEMPLE<float> operator*(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<int>& v);

//Vec2Float / VECTOR2----------------------------
static VECTOR2_TEMPLE<float> operator/(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<int>& v);

static VECTOR2_TEMPLE<float> VecFCast(const VECTOR2_TEMPLE<int>& u);
static VECTOR2_TEMPLE<int> VecICast(const VECTOR2_TEMPLE<float>& u);

using VECTOR2 = VECTOR2_TEMPLE<int>;
using Vec2Int = VECTOR2_TEMPLE<int>;
using Vec2Float = VECTOR2_TEMPLE<float>;
using Vec2Double = VECTOR2_TEMPLE<double>;


#include"./details/VECTOR2.h"