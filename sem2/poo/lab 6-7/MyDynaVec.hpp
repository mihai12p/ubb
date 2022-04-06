#pragma once

#define INITIAL_CAP 1

template <typename TElem>
class MyDynaVecIt;

template <typename TElem>
class MyDynaVec
{
	int len, cap;
	TElem* elems;

	public:
		MyDynaVec();
		~MyDynaVec();

		MyDynaVec(const MyDynaVec& other); // constructor de copiere
		MyDynaVec& operator=(const MyDynaVec& other); // assignment operator
		MyDynaVec(const MyDynaVec&& other); // move constructor
		MyDynaVec& operator=(const MyDynaVec&& other); // move assignment

		void push_back(const TElem& elem);
		void erase(const int poz);
		TElem& at(const int poz) const noexcept;
		void set(const int poz, const TElem& elem);
		int size() const noexcept;

		friend class MyDynaVecIt<TElem>;
		MyDynaVecIt<TElem> begin() const noexcept;
		MyDynaVecIt<TElem> end() const noexcept;
};

template <typename TElem>
class MyDynaVecIt
{
	int poz = 0;
	const MyDynaVec<TElem>& myVec;

	public:
		MyDynaVecIt(const MyDynaVec<TElem>& myVec) noexcept;
		MyDynaVecIt(const MyDynaVec<TElem>& myVec, const int poz) noexcept;
		bool valid() const;
		TElem& elem() const noexcept;
		void urm() noexcept;

		TElem& operator*() noexcept;
		MyDynaVecIt& operator++() noexcept;
		bool operator==(const MyDynaVecIt& other) noexcept;
		bool operator!=(const MyDynaVecIt& other) noexcept;
};

template <typename TElem>
MyDynaVec<TElem>::MyDynaVec() : elems{ new TElem[INITIAL_CAP] }, cap{ INITIAL_CAP }, len{ 0 } { }

template <typename TElem>
MyDynaVec<TElem>::~MyDynaVec()
{
	if (this->elems) 
		delete[] this->elems;
}

template <typename TElem>
MyDynaVec<TElem>::MyDynaVec(const MyDynaVec<TElem>& other)
{
	this->elems = new TElem[other.cap];
	for (int i = 0; i < other.len; ++i)
		this->elems[i] = other.elems[i];
	this->len = other.len;
	this->cap = other.cap;
}

template <typename TElem>
MyDynaVec<TElem>& MyDynaVec<TElem>::operator=(const MyDynaVec& other)
{
	if (this == &other)
		return *this;

	if (this->elems)
		delete[] this->elems;

	this->elems = new TElem[other.cap];
	for (int i = 0; i < other.len; ++i)
		this->elems[i] = other.elems[i];
	this->len = other.len;
	this->cap = other.cap;

	return *this;
}

template <typename TElem>
MyDynaVec<TElem>::MyDynaVec(const MyDynaVec&& other)
{
	this->elems = other.elems;
	this->cap = other.cap;
	this->len = other.len;

	other.elems = nullptr;
	other.cap = other.len = 0;
}

template <typename TElem>
MyDynaVec<TElem>& MyDynaVec<TElem>::operator=(const MyDynaVec&& other)
{
	if (this == &other)
		return *this;

	if (this->elems)
		delete[] this->elems;

	this->elems = other.elems;
	this->cap = other.cap;
	this->len = other.len;

	other.elems = nullptr;
	other.cap = other.len = 0;

	return *this;
}

template <typename TElem>
void MyDynaVec<TElem>::push_back(const TElem& elem)
{
	if (this->len == this->cap)
	{
		this->cap *= 2;
		TElem* newVec = new TElem[this->cap];
		for (int i = 0; i < this->len; ++i)
			newVec[i] = this->elems[i];
		if (this->elems)
			delete[] this->elems;
		this->elems = newVec;
	}

	this->elems[this->len++] = elem;
}

template <typename TElem>
void MyDynaVec<TElem>::erase(const int poz)
{
	for (int i = poz; i < this->len - 1; ++i)
		this->elems[i] = this->elems[i + 1];

	--this->len;
}

template <typename TElem>
TElem& MyDynaVec<TElem>::at(const int poz) const noexcept
{
	return this->elems[poz];
}

template <typename TElem>
void MyDynaVec<TElem>::set(const int poz, const TElem& elem)
{
	this->elems[poz] = elem;
}

template <typename TElem>
int MyDynaVec<TElem>::size() const noexcept
{
	return this->len;
}

template <typename TElem>
MyDynaVecIt<TElem> MyDynaVec<TElem>::begin() const noexcept
{
	return MyDynaVecIt<TElem>(*this);
}

template <typename TElem>
MyDynaVecIt<TElem> MyDynaVec<TElem>::end() const noexcept
{
	return MyDynaVecIt<TElem>(*this, this->len);
}

template <typename TElem>
MyDynaVecIt<TElem>::MyDynaVecIt(const MyDynaVec<TElem>& myVec) noexcept : myVec{ myVec } { }

template <typename TElem>
MyDynaVecIt<TElem>::MyDynaVecIt(const MyDynaVec<TElem>& myVec, const int poz) noexcept : myVec{ myVec }, poz{ poz } { }

template <typename TElem>
bool MyDynaVecIt<TElem>::valid() const
{
	return this->poz < this->myVec.len;
}

template <typename TElem>
TElem& MyDynaVecIt<TElem>::elem() const noexcept
{
	return this->myVec.at(this->poz);
}

template <typename TElem>
void MyDynaVecIt<TElem>::urm() noexcept
{
	++this->poz;
}

template <typename TElem>
TElem& MyDynaVecIt<TElem>::operator*() noexcept
{
	return elem();
}

template <typename TElem>
MyDynaVecIt<TElem>& MyDynaVecIt<TElem>::operator++() noexcept
{
	urm();
	return *this;
}

template <typename TElem>
bool MyDynaVecIt<TElem>::operator==(const MyDynaVecIt& other) noexcept
{
	return this->poz == other.poz;
}

template <typename TElem>
bool MyDynaVecIt<TElem>::operator!=(const MyDynaVecIt& other) noexcept
{
	return !(*this == other);
}
