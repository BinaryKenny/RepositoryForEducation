#include <iostream>
#include <fstream>

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
  void IntMatrix::add_string(size_t str_id, int element);
  int * data;
  size_t size;
};

int main(int argc, char ** argv)
{
  std:ifstream input (argv[1]);
  size_t rows = 0, cols = 0;
  int first = 0;
  input >> rows >> cols >> first;
  IntMatrix matrix(first);
  for (size_t i = 1; i < rows * cols; ++i)
  {
    int temp = 0;
    if(input >> temp)
    {
      matrix.add(temp);
    }
    else
    {
      delete [] matrix;
      throw std::invalid_argument("Bad element");
    }
    std::cout << "Write your commands\n";
    while(!(std::cin.eof()))
    {
      int c1 = 0, c2 = 0, c3 = 0;
      if (!(std::cin >> c1 >> c2 >> c3))
      {
        throw std::logic_error("Wong commands or arguments");
      }
      if (c1 == 1)
      {
        matrix.add_string(c2, c3);
      }
      else if (c1 == 2)
      {
        //second method
      }
      else if (c3 == 3)
      {
        //third method
      }
      else
      {
        throw std::invalid_argument("Unknown command");
      }
    }
}

IntMatrix::~IntMatrix()
{
  delete [] data;
}
IntMatrix::IntMatrix(int i) :
  data(new int [1]),
  size(1)
{
  a[0] = i;
}
int IntMatrix::get(size_t id) const noexcept
{
  return data[id];
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
void IntMatrix::add_string(size_t str_id, int element)
{
  int * temp = new int [size + cols];
  for (size_t i = 0; i < size + cols; ++i)
  {
    if (i < cols * str_id){
      temp[i] = get(i);
    }
      else if (cols * str_id <= i and i < cols * (str_id + 1))
    {
      temp[i] = element;
    }
    else if (i >= cols * (str_id + 1))
    {
      temp[i] = get(i - cols);
    }
  }
  delete [] data;
  data = temp;
  size+=cols;
  rows++;
}
