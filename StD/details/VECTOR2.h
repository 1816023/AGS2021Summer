#include "..\VECTOR2.h"
#include <cmath>

template<class T>
VECTOR2_TEMPLE<T>::VECTOR2_TEMPLE()
{
	x = 0;
	y = 0;
}

template<class T>
VECTOR2_TEMPLE<T>::VECTOR2_TEMPLE(T x, T y)
{
	this->x = x;
	this->y = y;
}



template<class T>
VECTOR2_TEMPLE<T>::~VECTOR2_TEMPLE()
{
}

template<class T>
VECTOR2_TEMPLE<T>& VECTOR2_TEMPLE<T>::operator=(const VECTOR2_TEMPLE<T>& vec)
{
	/*(*this).x = vec.x;
	  (*this).y = vec.y;*/
	this->x = vec.x;
	this->y = vec.y;
	return (*this);
}

template<class T>
T& VECTOR2_TEMPLE<T>::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	else if (i == 1)
	{
		return y;
	}
	else
	{
		return x;
	}

}

template<class T>
VECTOR2_TEMPLE<float> VECTOR2_TEMPLE<T>::Floor()
{
	return VECTOR2_TEMPLE<float>(std::floorf(this->x), std::floorf(this->y));
}

template<class T>
inline VECTOR2_TEMPLE<float> VECTOR2_TEMPLE<T>::Round()
{
	return VECTOR2_TEMPLE<float>(std::roundf(this->x), std::roundf(this->y));
}

template<class T>
VECTOR2_TEMPLE<T>& VECTOR2_TEMPLE<T>::operator+=(const VECTOR2_TEMPLE<T>& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

template<class T>VECTOR2_TEMPLE<T>& 
VECTOR2_TEMPLE<T>::operator-=(const VECTOR2_TEMPLE<T>& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

template<class T>
VECTOR2_TEMPLE<T>& VECTOR2_TEMPLE<T>::operator*=(T k)
{
	this->x *= k;
	this->y *= k;
	return (*this);
}

template<class T>
VECTOR2_TEMPLE<T>& VECTOR2_TEMPLE<T>::operator/=(T k)
{
	if (k != 0)
	{
		this->x /= k;
		this->y /= k;
	}
	return (*this);
}

template<class T>
VECTOR2_TEMPLE<T>& VECTOR2_TEMPLE<T>::operator+=(const T& vec)
{
	this->x += vec;
	this->y += vec;
	return (*this);
}

template<class T>
VECTOR2_TEMPLE<T>& VECTOR2_TEMPLE<T>::operator-=(const T& vec)
{
	this->x -= vec;
	this->y -= vec;
	return (*this);
}

template<class T>
VECTOR2_TEMPLE<T> VECTOR2_TEMPLE<T>::operator+()const
{
	return VECTOR2_TEMPLE<T>(x, y);
	//return (*this);
}

template<class T>
VECTOR2_TEMPLE<T> VECTOR2_TEMPLE<T>::operator-()const
{
	return VECTOR2_TEMPLE<T>(-this->x, -this->y);
}


//VECTOR2 + int
template<class T>
VECTOR2_TEMPLE<T> operator+(const VECTOR2_TEMPLE<T>& u, T v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x + v;
	vec.y = u.y + v;

	return vec;
}

//VECTOR2 - int
template<class T>
VECTOR2_TEMPLE<T> operator-(const VECTOR2_TEMPLE<T>& u, T v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x - v;
	vec.y = u.y - v;

	return vec;
}

//VECTOR2 * int
template<class T>
VECTOR2_TEMPLE<T> operator*(const VECTOR2_TEMPLE<T>& u, T v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x * v;
	vec.y = u.y * v;

	return vec;
}

//VECTOR2 / int
template<class T>
VECTOR2_TEMPLE<T> operator/(const VECTOR2_TEMPLE<T>& u, T v)
{
	if (v == 0)
	{
		return VECTOR2_TEMPLE<T>();
	}
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x / v;
	vec.y = u.y / v;

	return vec;
}

//VECTOR2 % int
template<class T>
VECTOR2_TEMPLE<T> operator%(const VECTOR2_TEMPLE<T>& u, T v)
{
	if (v.x == 0 || v.y == 0)
	{
		return VECTOR2_TEMPLE<T>();
	}
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x % v;
	vec.y = u.y % v;

	return vec;
}

//int * VECTOR2
template<class T>
VECTOR2_TEMPLE<T> operator+(T u, const VECTOR2_TEMPLE<T>& v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u + v.x;
	vec.y = u + v.y;
	return vec;
}

//VECTOR2 + VECTOR2
template<class T>
VECTOR2_TEMPLE<T> operator+(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<T>& v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;
}

//VECTOR2 - VECTOR2
template<class T>
VECTOR2_TEMPLE<T> operator-(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<T>& v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;
}

//VECTOR2 * VECTOR2
template<class T>
VECTOR2_TEMPLE<T> operator*(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<T>& v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	return vec;
}

template<class T>
VECTOR2_TEMPLE<T> operator/(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<T>& v)
{
	if (v.x == 0 || v.y == 0)
	{
		return VECTOR2_TEMPLE<T>();
	}
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;
	return vec;
}

template<class T>
VECTOR2_TEMPLE<T> operator%(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<T>& v)
{
	if (v.x == 0 || v.y == 0)
	{
		return VECTOR2_TEMPLE<T>();
	}
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;
	return vec;
}

//VECTOR2 + Vec2Float----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator+(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<float>& v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;

}
//VECTOR2 - Vec2Float----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator-(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<float>& v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;

}

//VECTOR2 * Vec2Float----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator*(const VECTOR2_TEMPLE<int>& u, const VECTOR2_TEMPLE<float>& v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	return vec;

}

//VECTOR2 / Vec2Float----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator/(const VECTOR2_TEMPLE<T>& u, const VECTOR2_TEMPLE<float>& v)
{
	if (v.x == 0 || v.y == 0)
	{
		return VECTOR2_TEMPLE<T>();
	}
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;
	return vec;

}

//Vec2Float + VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator+(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<T>& v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	return vec;

}

//Vec2Float - VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator-(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<T>& v)
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	return vec;

}

//Vec2Float * VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator*(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<int>& v) 
{
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	return vec;
}

//Vec2Float / VECTOR2----------------------------
template<class T>
VECTOR2_TEMPLE<T> operator/(const VECTOR2_TEMPLE<float>& u, const VECTOR2_TEMPLE<T>& v)
{
	if (v.x == 0 || v.y == 0)
	{
		return VECTOR2_TEMPLE<T>();
	}
	VECTOR2_TEMPLE<T> vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;
	return vec;

}

