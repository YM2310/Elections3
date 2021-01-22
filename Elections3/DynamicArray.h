#include <iostream>
using namespace std;

template <class T>
class DynamicArray
{
public:
	DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}

	DynamicArray(const DynamicArray& other) : _arr(nullptr) {
		*this = other;
	}
	~DynamicArray() {
		delete[] _arr;
	}
	// standard STL iterator implementation:
	// (no duplication for const)
	template <bool is_const>
	class base_iterator
	{
	public:
		using ds_type = std::conditional_t<is_const, const DynamicArray, DynamicArray>;

		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = std::conditional_t<is_const, const T, T>;
		using pointer = value_type*;
		using reference = value_type&;

		base_iterator(ds_type& arr, int i) : _da(&arr), _i(i) {}

		// we want to use the default copy constructor
		base_iterator(const base_iterator&) = default;

		// and the default assignment operator
		constexpr base_iterator& operator=(const base_iterator&) = default;

		// we want to allow construction of const_iterator from iterator
		friend class base_iterator<true>;
		template <bool _is_const = is_const, class = std::enable_if_t<_is_const>>
		base_iterator(const base_iterator<false>& other) : _da(other._da), _i(other._i) {}


		// comparison with another iterator
		bool operator==(const base_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const base_iterator& other) const {
			return !(*this == other);
		}
		// smart-pointer iterator methods
		reference operator*() {
			return _da->_arr[_i];
		}
		pointer operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		base_iterator& operator++() {
			++_i;
			return *this;
		}
		base_iterator operator++(int) {
			base_iterator temp(*this);
			++_i;
			return temp;
		}

		base_iterator& operator--() {
			--_i;
			return *this;
		}
		base_iterator operator--(int) {
			base_iterator temp(*this);
			--_i;
			return temp;
		}

		base_iterator& operator+(int add) {
			_i += add;
			return *this;
		}
		base_iterator& operator-(int sub) {
			base_iterator temp(*this);
			temp._i = _i - sub;
			return temp;
		}
		int operator-(base_iterator& sub) {
			return _i - sub._i;
		}


	private:
		ds_type* _da;
		int		_i;
	};
	using iterator = base_iterator<false>;
	using const_iterator = base_iterator<true>;

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			_logicalSize = other._logicalSize;
			_physicalSize = other._physicalSize;
			delete[] _arr;
			_arr = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const { return _arr[i]; }
	T& operator[](int i) { return _arr[i]; }

	void push_back(const T& value) {
		if (_logicalSize == _physicalSize)
			resize();
		_arr[_logicalSize++] = value;
	}

	const T& front()    const { return _arr[0]; }
	int      size()     const { return _logicalSize; }
	int      capacity() const { return _physicalSize; }
	bool     empty()    const { return _logicalSize == 0; }
	void     clear() { _logicalSize = 0; }


	// should return iterator to new element
	void insert(const iterator& pos, const T& val) {
		if (_logicalSize == _physicalSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++_logicalSize;
	}

	// returns iterator to first element after deleted element/s
	iterator erase(const iterator& iter) {
		iterator itrCurrent = iter;
		iterator itrNext = iter;
		itrNext++;
		iterator itrEnd = end();

		while (itrCurrent != itrEnd) {
			*itrCurrent = *itrNext;
			itrCurrent = itrNext++;
		}
		--_logicalSize;
		return iter;

	}
	iterator erase(const iterator& first, const iterator& last) {
		iterator itrTake = last;
		itrTake++;
		iterator itrPut = first;
		iterator itrEnd = end();

		while (itrTake != itrEnd) {
			*itrPut = *itrTake;
			itrPut++;
			itrTake++;
		}
		itrPut = first;
		while (itrPut != last) {
			itrPut++;
			_logicalSize--;
		}
		_logicalSize--;
		return first;
	}

	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, _logicalSize);
	}
	const_iterator cbegin() const {
		return const_iterator(*this, 0);
	}
	const_iterator cend() const {
		return const_iterator(*this, _logicalSize);
	}

	iterator rend() {
		return iterator(*this, 0);
	}

	iterator rbegin() {
		return iterator(*this, _logicalSize - 1);
	}

	void print() const {
		for (int i = 0; i < _logicalSize; i++)
			cout << _arr[i] << " ";
		cout << endl;
	}

private:
	void resize() {
		_physicalSize *= 2;
		T* temp = new T[_physicalSize];
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

	T* _arr;
	int _logicalSize;
	int _physicalSize;
};

