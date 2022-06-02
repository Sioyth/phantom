#ifndef UNIFORMVALUE_H
#define UNIFORMVALUE_H
#include <iostream>

enum DataType {Float, Int, Double, Vec3, All};

class UniformValue
{
	public:
		inline void SetData(void* data) { _data = data; };
		inline void* GetData() { return _data; }
		inline void* GetDataAddress() { return &_data; };
		inline DataType GetDataType() { return _dataType; };
		inline void SetDataType(DataType dataType) { _dataType = dataType; };
	private:
		void* _data;
		DataType _dataType;
};

template<typename T>
T* CastTo(void* data)
{
	return (T*)data;
}

#endif 


