#include <iostream>

struct IntArray{
  void add (unsigned int i);
  unsigned int get(size_t id) const noexcept;
  int at(size_t id) const;
  size_t getsize() const noexcept;
  unsigned int last() const noexcept;
  IntArray(unsigned int i);
  ~IntArray();
  IntArray(const IntArray & rhs);
  IntArray operator=(const IntArray & rhs);
  unsigned int * a;
  size_t size;
};

int main()
{
  try
  {
    unsigned int next = 0;
    std::cin >> next;
    IntArray a(next);
    while (std::cin >> next)
    {
      a.add(next);
    }
    if (std::cin.fail() and !std::cin.eof())
    {
      std::cerr << "Error: wrong input\n";
      return 1;
    }
    size_t count = 1;
    for (size_t i = 0; i < a.size() - 1; ++i)
    {
      unsigned int d = a.get(i);
      count += !(d % a.last())? 1 : 0;
    }
    std::cout << count << "\n";
  }
  catch( const std::bad_alloc & error)
  {
    std::cerr << error.what() << "\n";
    return 2;
  }
}

IntArray::~IntArray()
{
  delete [] a;
}
IntArray::IntArray(unsigned int i) :
  a(new unsigned int [1]),
  k(1)
{
  a[0] = i;
}
unsigned int IntArray::get(size_t id) const noexcept
{
  return a[id];
}
size_t IntArray::size() const noexcept
{
  return k;
}
unsigned int IntArray::last() const noexcept
{
  return get(size() - 1);
}
void IntArray::add(unsigned int i)
{
  unsigned int * temp = new unsigned int [size() + 1];
  for (size_t n = 0; n < size(); ++n)
  {
    temp[i] = get(i);
  }
  temp[size()] = i;
  delete[] a;
  a = temp;
  ++size;
}
IntArray3::IntArray(const IntArray & rhs) :
  data(new unsigned int [rhs.getsize()]),
  getsize(rhs.getsize())
{
  for (size_t i = 0; i < getsize(); ++i){
    data[i] = rhs.get(i);
  }
}
IntArray & IntArray::operator=(const IntArray & rhs){
  unsigned int * temp = new unsigned int [rhs.getsize()];
  for (size_t i = 0; i < rhs.getsize(); ++i){
    temp[i] = rhs.get(i);
  }
  delete [] data;
  data = temp;
  size = rhs.getsize();
  return *this;
}
