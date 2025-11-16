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
  IntMatrix & operator=(const IntMatrix & rhs);
  void add_string(size_t str_id, int element);
  void add_column(size_t str_id, int element);
  void add(size_t str_id1, size_t str_id2);
  void output();
  int * data;
  size_t size;
  size_t rows;
  size_t cols;
};

int main(int argc, char ** argv)
{
  try
  {
    std::ifstream input(argv[1]);
    size_t rows = 0, cols = 0;
    int first = 0;
    input >> rows >> cols >> first;
    if (std::cin.fail())
    {
      throw std::invalid_argument("Invalid data");
    }
    IntMatrix matrix(first);
    matrix.rows = rows;
    matrix.cols = cols;
    for (size_t i = 1; i < rows * cols; ++i)
    {
      int temp = 0;
      if(input >> temp)
      {
        matrix.add(temp);
      }
      else
      {
        throw std::invalid_argument("Bad element");
      }
    }
    std::cout << "Write your commands\n";
    while(true)
    {
      int c1 = 0, c2 = 0, c3 = 0;
      if (std::cin >> c1 >> c2 >> c3)
      {
        if (c1 == 1)
        {
          if (c2 > rows)
          {
            throw std::logic_error("Overflow mean: not enough");
          }
          else
          {
            matrix.add_string(c2, c3);
          }
        }
        else if (c1 == 2)
        {
          if (c2 > cols)
          {
            throw std::logic_error("Oveflow mean: not enough columns");
          }
          else
          {
            matrix.add_column(c2, c3);
          }
        }
        else if (c1 == 3)
        {
          if (c2 > rows or c3 > cols)
          {
            throw std::logic_error("Overflow mean: not enough rows and columns");
          }
          else
          {
            matrix.add(c2, c3);
          }
        }
        else
        {
          throw std::logic_error("Unknown command");
        }
      }
      else
      {
        if (std::cin.eof())
        {
          break;
        }
        else
        {
          throw std::logic_error("Wrong commands or arguments");
        }
      }
    }
    matrix.output();
  }
  catch(std::invalid_argument & err)
  {
    std::cerr << err.what();
    return 1;
  }
  catch (std::logic_error & msg)
  {
    std::cerr << msg.what();
    return 3;
  }
  catch (std::bad_alloc& e)
  {
    std::cerr << e.what();
    return 2;
  }
}
IntMatrix::~IntMatrix()
{
  delete [] data;
}
IntMatrix::IntMatrix(int i) :
  data(new int [1]),
  size(1),
  rows(1),
  cols(1)
  
{
  data[0] = i;
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
    temp[n] = get(n);
  }
  temp[getsize()] = i;
  delete[] data;
  data = temp;
  ++size;
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
  data(new int [rhs.getsize()]),
  size(rhs.getsize()),
  rows(rhs.rows),
  cols(rhs.cols)
{
  for (size_t i = 0; i < getsize(); ++i){
    data[i] = rhs.get(i);
  }
}
IntMatrix& IntMatrix::operator=(const IntMatrix & rhs){
  int * temp = new int [rhs.getsize()];
  for (size_t i = 0; i < rhs.getsize(); ++i){
    temp[i] = rhs.get(i);
  }
  delete [] data;
  data = temp;
  size = rhs.getsize();
  rows = rhs.rows;
  cols = rhs.cols;
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
void IntMatrix::add_column(size_t str_id, int element)
{
    size_t count = 0;
    int * temp = new int [size + rows];
    for (size_t i = 0; i < size + rows; ++i)
    {
        if (i == count * (rows + 1) + str_id and count < rows)
        {
            temp[i] = element;
            count++;
        }
        else
        {
            temp[i] = get(i - count);
        }
    }
    delete[] data;
    data = temp;
    size+=rows;
    cols++;
}
void IntMatrix::add(size_t str_id1, size_t str_id2)
{
  int * temp = new int [size + cols + rows + 1];
  size_t count = 0, count_data = 0;
  for (size_t i = 0; i < size + rows + cols + 1; ++i)
  {
    if (count < rows + 1 and i == (cols + 1) * count + str_id2)
    {
      temp[i] = 0;
      count++;
    }
    else if (i >= (cols + 1) * str_id1 and i < (cols + 1) * (str_id1 + 1))
    {
      temp[i] = 0;
    }
    else
    {
      temp[i] = get(count_data);
      count_data++;
    }
  }
  size+=(cols + rows + 1);
  rows++;
  cols++;
  delete [] data;
  data = temp;
}
void IntMatrix::output()
{
  for (size_t i = 0; i < size; i++)
  {
    std::cout << data[i] << " ";
    if ((i + 1) % cols == 0)
    {
      std::cout << "\n";
    }
  }
}  
