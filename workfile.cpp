#include <iostream>

struct IntMatrix{
  void add (int i);
  int get(size_t id) const noexcept;
  int at(size_t id) const;
  size_t getsize() const noexcept;
  int last() const noexcept;
  IntMatrix(int i);
  ~IntMatrix();
  IntMatrix(const IntMatrix & rhs);
  IntMatrix operator=(const IntMatrix & rhs);
  int * data;
  size_t size;
};

int main()
{
  try
  {
    int next = 0;
    std::cin >> next;
    IntMatrix a(next);
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
      int d = a.get(i);
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

IntMatrix::~IntMatrix()
{
  delete [] a;
}
IntMatrix::IntMatrix(int i) :
  data(new int [1]),
  size(1)
{
  a[0] = i;
}
int IntMatrix::get(size_t id) const noexcept
{
  return a[id];
}
size_t IntMatrix::getsize() const noexcept
{
  return size;
}
int IntMatrix::last() const noexcept
{
  return get(getsize() - 1);
}
void IntMatrix::add(int i)
{
  int * temp = new int [getsize() + 1];
  for (size_t n = 0; n < getsize(); ++n)
  {
    temp[i] = get(i);
  }
  temp[getsize()] = i;
  delete[] data;
  data = temp;
  ++size;
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
  data(new int [rhs.getsize()]),
  size(rhs.getsize())
{
  for (size_t i = 0; i < getsize(); ++i){
    data[i] = rhs.get(i);
  }
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs){
  int * temp = new int [rhs.getsize()];
  for (size_t i = 0; i < rhs.getsize(); ++i){
    temp[i] = rhs.get(i);
  }
  delete [] data;
  data = temp;
  size = rhs.getsize();
  return *this;
}
