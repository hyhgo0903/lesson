#pragma once

template <typename TEMPL>
class arraySample
{
public:
	TEMPL* buffer;
	int size;

	void push_back(TEMPL value)
	{
		if (size != 0)
		{
			TEMPL* temp;
			temp = new TEMPL[size + 1];
			memcpy(temp, buffer, size * sizeof(TEMPL));
			// 메모리 카피
			// sizeof(T) 자료형에따라 메모리크기 반환하려고
			delete[] buffer;
			buffer = temp;
		}

		buffer[size++] = value;
	}

	int GetSize() { return size; }

	TEMPL operator[](int index) const
	{
		return buffer[index];
	}

	arraySample()
	{
		size = 0;
		buffer = new TEMPL[1];
	};
	~arraySample()
	{
		delete[] buffer;
	};
};