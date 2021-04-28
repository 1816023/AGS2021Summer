#pragma once
template<class T>class VECTOR2_TEMPLE
{
public:
	VECTOR2_TEMPLE();
	VECTOR2_TEMPLE(T x, T y);
	~VECTOR2_TEMPLE();
	T x;
	T y;
	//ë„ì¸ââéZéq------------------------------------------
	VECTOR2_TEMPLE& operator = (const VECTOR2_TEMPLE& vec);

	//ìYÇ¶éöââéZéq----------------------------------------
	T& operator[](int i);

	//î‰ärââéZéq------------------------------------------
	  /*ì«Ç›çûÇ›êÍópÇ≈égópÇ∑ÇÈÇ∆Ç´ÇÃÇ›constÇégópÇ∑ÇÈ*/
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

	// êÿÇËéÃÇƒ
	VECTOR2_TEMPLE<float> Floor();
	// éléÃå‹ì¸
	VECTOR2_TEMPLE<float> Round();

	//íPçÄââéZéq------------------------------------------
	VECTOR2_TEMPLE& operator +=(const VECTOR2_TEMPLE& vec);
	VECTOR2_TEMPLE& operator -=(const VECTOR2_TEMPLE& vec);
	VECTOR2_TEMPLE& operator *=(T k);
	VECTOR2_TEMPLE& operator /=(T k);
	VECTOR2_TEMPLE& operator +=(const T& vec);
	VECTOR2_TEMPLE& operator -=(const T& vec);

	VECTOR2_TEMPLE operator+()const;
	VECTOR2_TEMPLE operator-()const;
	

	
};

//Õﬁ∏ƒŸÇÃââéZ//////////////////////////////////
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
VECTOR2_TEMPLE<T> operator+(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<T>& v);

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
template<class T>
VECTOR2_TEMPLE<T> operator+(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<float>& v);

//VECTOR2 - Vec2Float----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator-(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<float>& v);

//VECTOR2 * Vec2Float----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator*(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<float>& v);

//VECTOR2 / Vec2Float----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator/(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<float>& v);

//Vec2Float + VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator+(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<T>& v);

//Vec2Float - VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator-(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<T>& v);

//Vec2Float * VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator*(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<int>& v);

//Vec2Float / VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator/(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<T>& v);

using VECTOR2 = VECTOR2_TEMPLE<int>;
using Vec2Int = VECTOR2_TEMPLE<int>;
using Vec2Float = VECTOR2_TEMPLE<float>;
using Vec2Double = VECTOR2_TEMPLE<double>;


#include"./details/VECTOR2.h"