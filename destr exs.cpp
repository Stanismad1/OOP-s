include <iostream>

class Entity1
{
public:
	Entity1()
	{
		std::cout << "Constructor E1 called" << std::endl;
	}

	~Entity1()
	{
		std::cout << "Destructor E1 called" << std::endl;
	}
};

class Entity2
{
public:
	Entity2()
	{
		std::cout << "Constructor E2 called" << std::endl;
	}

	~Entity2()
	{
		std::cout << "Destructor E2 called" << std::endl;
	}
};

class Entity
{
	Entity1 e1;
	Entity2	e2;
public:
	Entity()
	{
		std::cout << "Constructor E called" << std::endl;
	}

	~Entity()
	{
		std::cout << "Destructor E called" << std::endl;
	}
};

void drawLine()
{
	std::cout << std::endl << "==========================" << std::endl;
}

int main()
{
	{
		Entity1 e;
	}
	drawLine();

	Entity1* e;
	{
		e = new Entity1;
	}

	delete e;

	drawLine();
	{
		Entity1 arr[20];
	}

	drawLine();

	Entity e2;
}
//zad2
#include <iostream>

namespace Constraints
{
	constexpr size_t BUCKETS_COUNT = 32;
	constexpr size_t BUCKETS_SIZE = 8;
	constexpr size_t TOWNS_COUNT = 256;
}

class Path
{
private:
	unsigned char data[Constraints::BUCKETS_COUNT];

	size_t getBucket(unsigned index) const
	{
		return index / Constraints::BUCKETS_SIZE;
	}

	size_t getElement(unsigned index) const
	{
		return (index - Constraints::BUCKETS_SIZE * getBucket(index));
	}

public:
	Path()
	{
		for (size_t i = 0; i < Constraints::BUCKETS_COUNT; i++)
			data[i] = 0;
	}

	void addTown(unsigned index)
	{
		size_t bucket = getBucket(index);
		size_t element = getElement(index);

		data[bucket] |= (1 << element);
	}

	void removeTown(unsigned index)
	{
		size_t bucket = getBucket(index);
		size_t element = getElement(index);

		data[bucket] &= ~(1 << element);
	}

	bool hasTown(unsigned index) const
	{
		size_t bucket = getBucket(index);
		size_t element = getElement(index);

		return ((data[bucket] & (1 << element)) != 0);
	}

	Path unionOfTwo(const Path& other) const
	{
		Path toReturn;
		for (size_t i = 0; i < Constraints::BUCKETS_COUNT; i++)
			toReturn.data[i] = data[i] | other.data[i];

		return toReturn;
	}

	Path intersectionOfTwo(const Path& other) const
	{
		Path toReturn;
		for (size_t i = 0; i < Constraints::BUCKETS_COUNT; i++)
			toReturn.data[i] = data[i] & other.data[i];

		return toReturn;
	}

	bool empty() const
	{
		for (size_t i = 0; i < Constraints::BUCKETS_COUNT; i++)
			if (data[i])
				return false;

		return true;
	}

	bool hasCommonStop(const Path& other) const
	{
		for (size_t i = 0; i < Constraints::BUCKETS_COUNT; i++)
			if (data[i] & other.data[i])
				return true;

		return false;
	}

	size_t size() const
	{
		size_t toReturn = 0;

		for (size_t i = 0; i < Constraints::TOWNS_COUNT; i++)
		{
			if (hasTown(i))
				++toReturn;
		}
		return toReturn;
	}

	void print() const
	{
		for (size_t i = 0; i < Constraints::TOWNS_COUNT; i++)
		{
			if (hasTown(i))
				std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	unsigned* toArray(size_t& arraySize) const
	{
		arraySize = size();
		unsigned* toreturn = new unsigned[arraySize];
		unsigned at = 0;

		for (size_t i = 0; i < Constraints::TOWNS_COUNT; i++)
		{
			if (hasTown(i))
				toreturn[at++] = i;
		}
		return toreturn;
	}
};

int main()
{
	Path p;
	std::cout << p.empty() << std::endl; // true

	p.addTown(4);
	p.addTown(17);
	p.addTown(123);

	std::cout << p.empty() << std::endl; // false
	std::cout << p.size() << std::endl; // 3

	std::cout << p.hasTown(4) << std::endl; // true
	p.removeTown(4);
	std::cout << p.hasTown(4) << std::endl; // false

	Path p1;
	p1.addTown(17);
	p1.addTown(200);

	Path Union = p.unionOfTwo(p1);
	Path Intersection = p.intersectionOfTwo(p1);

	Intersection.print();
	Union.print();

	size_t size = 0;
	unsigned* arr = Union.toArray(size);

	for (size_t i = 0; i < size; i++)
		std::cout << arr[i] << ",";
	// 16, 17, 200,

	std::cout << std::endl;
	delete[] arr;
}

