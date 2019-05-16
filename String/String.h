#pragma once
#include<iostream>
#include<string.h>
using namespace std;
namespace Cqh
{
	class String
	{
	public:
		typedef char* iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}
		 
		String(char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];

			strcpy(_str, str);
		}

		// copy(s1)
		String(const String& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			String tmp(s._str);
			this->Swap(tmp);
		}
		// copy = s2;
		String& operator=(String s)
		{
			this->Swap(s);
			return *this;
		}

		void Swap(String& s)
		{
			swap(_str, s._str);
			swap(_size, s._size);
			swap(_capacity, s._capacity);
		}


		~String()
		{
			if (_str)
			{
				delete[] _str;
				_size = 0;
				_capacity = 0;
			}
		}

		bool operator<(const String& s)
		{
			int begin = 0;
			while (begin < _size&&begin<s._size)
			{
				if (_str[begin] < s._str[begin])
					return true;
				else if (_str[begin] == s._str[begin])
					begin++;
				else
					return false;
			}
			if (begin < s._size)
				return true;
			return false;

		}
		bool operator>(const String& s)
		{
			if (*this < s || *this == s)
			{
				return false;
			}
			else
				return true;
		}
		bool operator<=(const String& s)
		{
			if (!(*this>s))
				return true;
			else
				return false;
		}
		bool operator>=(const String& s)
		{
			if (!(*this < s))
			
				return true;
			
			else
				return false;
		}
		bool operator==(const String& s)
		{
			if (_size != s._size)
				return false;
			int begin = 0;
			while (begin < _size)
			{
				if (_str[begin] != s._str[begin])
					return false;
				begin++;
			}
			return true;
		}
		bool operator!=(const String& s)
		{
			if (!(*this == s))
				return true;
			else
				return false;
		}

		void Reserve(size_t n)
		{
			String tmp;
			tmp._str = new char[_capacity + n + 1];
			tmp._capacity = _capacity + n;
			tmp._size = _size;
			strcpy(tmp._str, _str);
			Swap(tmp);

		}

		void PushBack(char ch)
		{
			// ?
			if (this->_size==this->_capacity)
				Reserve(10);
			_str[_size] = ch;
			++_size;
		}

		// "hello"  "xxxxxxxxxxxxxxxxxxxxxxxxxx"
		void Append(const char* str)
		{
			// ?
			int i = strlen(str);
			if (_capacity < (_size + i))
				Reserve(i);
			int j = 0;
			while (j < i)
			{
				_str[_size + j] = str[j];
				j++;
			}
			_str[_size + j] = '\0';
			_size += i;
		}

		String& operator+=(char ch)
		{
			if (_size == _capacity)
				Reserve(10);
			_str[_size] = ch;
			_size++;
			return *this;
		}
		String& operator+=(const char* str)
		{
			int i = strlen(str);
			if (_capacity < (_size + i))
				Reserve(i);

			int j = 0;
			while (j < i)
			{
				_str[_size + j] = str[j];
				j++;
			}
			_str[_size + j] = '\0';
			_size += i;
			return *this;
		}
		void Insert(size_t pos, char ch)
		{
			if (_size == _capacity)
				Reserve(10);
			int x = _size;
			while (x >pos)
			{
				_str[x] = _str[x - 1];
				--x;
			}
			_str[pos] = ch;
			_size++;
		}
		void Insert(size_t pos, const char* str)
		{
			int i = strlen(str);
			if (_capacity < (_size + i))
				Reserve(i);
			int x = _size + i - 1;
			while (x >pos + i - 1)
			{
				_str[x] = _str[x - i];
				--x;
			}
			x = 0;
			while (x<i)
			{
				_str[pos + x] = str[x];
				x++;
			}
			_size += i;
			_str[_size] = '\0';
		}

		void Erase(size_t pos, size_t len)
		{
			size_t i = 0;

			while ((pos+i+len)<_size)
			{
				_str[pos + i] = _str[pos + i + len];
				i++;
			}

			_size -= len;
			_str[_size] = '\0';
			

		}
		size_t Find(char ch, size_t pos = 0)
		{
			while (pos < _size)
			{
				if (_str[pos] == ch)
					return pos;
				pos++;
			}
			return npos;
		}
		size_t Find(const char* str, size_t pos = 0)
		{


			while (pos < _size)
			{
				if (_str[pos] == str[0])
				{
					int i = 1;
					while (str[i] != '\0')
					{
						if (_str[pos + i] == str[i])
							i++;
						else
							break;
					}

					if (str[i] == '\0')
						return pos;
					else
						++pos;
				}
				else
				{
					++pos;
				}
			}
			return npos;

		}


		char* c_str()
		{
			return _str;
		}

		char& operator[](size_t pos)
		{
			//assert(pos < _size);

			return _str[pos];
		}

		size_t Size()
		{
			return _size;
		}

		size_t Capacity()
		{
			return _capacity;
		}

	private:
		char* _str;
		size_t _size;
		size_t _capacity;

		static size_t npos;
	};

	size_t String::npos = -1;

	void TestString1()
	{
		String s1("hello");
		String s2("world");
		String copy(s1);
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		cout << copy.c_str() << endl;
		if (s1 < s2)
			cout << "s1<s2" << endl;
		else
			cout << "s1>=s2" << endl;
		if (s1 == copy)
			cout << "s1==copy" << endl;
		else
			cout << "s1!=copy" << endl;
		copy += "world";
		cout << copy.c_str() << endl;
		copy.Insert(5, " ");
		cout << copy.c_str() << endl;
		copy.Erase(1, 3);
		cout << copy.c_str() << endl;
		cout<<copy.Find("or")<<endl;

	}
}