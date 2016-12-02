#include <iostream>
#include <iterator>
#include <vector>

template <class T>
class Stack
{
  private:
    std::vector<T> elems;

  public:
    bool is_empty() const;
    T top() const;
    std::vector<T> raw_vector() const;
    void pop();
    void print();
    void push(T const &);
};

template <class T>
bool Stack<T>::is_empty() const
{
  return elems.empty();
}

template <class T>
T Stack<T>::top() const
{
  if (elems.empty())
  {
    std::cout << "cannot 'Stack<>::top()': empty stack\n";
    exit(1);
  }

  return elems.back();
}

template <class T>
std::vector<T> Stack<T>::raw_vector() const
{
  return elems;
}

template <class T>
void Stack<T>::pop()
{
  if (elems.empty())
  {
    std::cout << "cannot 'Stack<>::pop()': empty stack\n";
    exit(1);
  }

  elems.pop_back();
}

template <class T>
void Stack<T>::print()
{
  std::ostream_iterator<T> out(std::cout, "\n");
  copy(elems.begin(), elems.end(), out);
}

template <class T>
void Stack<T>::push(T const & elem)
{
  elems.push_back(elem);
}
