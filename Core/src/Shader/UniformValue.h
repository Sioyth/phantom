#ifndef UNIFORMVALUE_H
#define UNIFORMVALUE_H

template <class T>
class UniformValue
{
	public:
		T GetValue();
	private:
		T _value;
};

template<class T>
inline T UniformValue<T>::GetValue()
{
	return _value;
}


#endif 

