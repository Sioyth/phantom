#ifndef UNIFORMVALUE_H
#define UNIFORMVALUE_H
#include <iostream>

enum DataType {Float, Int, Double, Vec3, All};

class UniformValue
{
	public:
		inline void SetData(std::shared_ptr<void> data) { _data = data; };
		inline std::shared_ptr<void> GetData() { return _data; }
		inline void* GetDataAddress() { return &_data; };
		inline DataType GetDataType() { return _dataType; };
		inline void SetDataType(DataType dataType) { _dataType = dataType; };
	private:
		std::shared_ptr<void> _data = nullptr;
		DataType _dataType;
};

template<typename T>
T* CastTo(void* data)
{
	return (T*)data;
};

template<typename T>
T* CastTo(std::shared_ptr<void> data)
{
	return (T*)&data;
};


#endif 


