#include <iostream>

struct IntArray{
  void add (int i);
  int get(size_t id) const noexcept;
  int at(size_t id) const;
  size_t size() const noexcept;
  int last() const noexcept;
  IntArray(int i);
  ~IntArray();
  int * a;
  size_t k;
};

int main()
{
  try
  {
    int next = 0;
    std::cin >> next;
    IntArray a(next);
    while (std::cin >> next)
    {
      a.add(next);
    }
    if (std::cin.fail() and !std::cin.eof())
    {
      retrun 1;
    }
    size_t count = 1;
    for (size_t i = 0; i < a.size() - 1; ++i)
    {
      int d = a.get(i);
      count += !(d % a.last)? 1 : 0;
    }
    std::cout << count << "\n";
  }
  catch( const std::bad_alloc & error)
  {
    std::cerr << error.what() << "\n";
  }
}

IntArray::~IntArray()
{
  delete [] a;
}
IntArray::~IntArray(int i):
  a(new int [1]),
  k(1)
{
  a[0] = i;
}
int IntArray::get(size_t id) const noexcept
{
  return a[id];
}
size_t IntArray::size() const noexcept
{
  return k;
}
int IntArray::last (int i) const noexcept
{
  return get(size() - 1);
}
void IntArray::add(int i)
{
  int * temp = new int [size() + 1];
  for (size_t i = 0; i < size(); ++i)
  {
    temp[i] = get[i];
  }
  delete[] a;
  a = temp;
  ++k;
}

