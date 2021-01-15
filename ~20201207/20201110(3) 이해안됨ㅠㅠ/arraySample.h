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
			// �޸� ī��
			// sizeof(T) �ڷ��������� �޸�ũ�� ��ȯ�Ϸ���
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