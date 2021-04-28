#pragma once
template<class T>class VECTOR2_TEMPLE
{
public:
	VECTOR2_TEMPLE();
	VECTOR2_TEMPLE(T x, T y);
	~VECTOR2_TEMPLE();
	T x;
	T y;
	//������Z�q------------------------------------------
	VECTOR2_TEMPLE& operator = (const VECTOR2_TEMPLE& vec);

	//�Y�������Z�q----------------------------------------
	T& operator[](int i);

	//��r���Z�q------------------------------------------
	  /*�ǂݍ��ݐ�p�Ŏg�p����Ƃ��̂�const���g�p����*/
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

	// �؂�̂�
	VECTOR2_TEMPLE<float> Floor();
	// �l�̌ܓ�
	VECTOR2_TEMPLE<float> Round();

	//�P�����Z�q------------------------------------------
	VECTOR2_TEMPLE& operator +=(const VECTOR2_TEMPLE& vec);
	VECTOR2_TEMPLE& operator -=(const VECTOR2_TEMPLE& vec);
	VECTOR2_TEMPLE& operator *=(T k);
	VECTOR2_TEMPLE& operator /=(T k);
	VECTOR2_TEMPLE& operator +=(const T& vec);
	VECTOR2_TEMPLE& operator -=(const T& vec);

	VECTOR2_TEMPLE operator+()const;
	VECTOR2_TEMPLE operator-()const;
	

	
};

//�޸�ق̉��Z//////////////////////////////////
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