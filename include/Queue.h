#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <deque>

template <class T>
class Queue
{
  private:
    std::deque<T> elems;
    std::function<int(T, T)> sort_method;

  public:
    Queue(std::function<int(T, T)> f) : sort_method(f) {};
    bool in(T item) const;
    bool is_empty() const;
    T front() const;
    std::deque<T> raw_deque() const;
    unsigned int size() const;
    void pop();
    void print();
    void push(T const &);
};

template <class T>
bool Queue<T>::is_empty() const
{
  return elems.empty();
}

template <class T>
bool Queue<T>::in(T item) const
{
  return std::find(elems.begin(), elems.end(), item) != elems.end();
}

template <class T>
T Queue<T>::front() const
{
  if (elems.empty())
  {
    std::cout << "cannot 'Queue<>::front()': empty queue\n";
    exit(1);
  }

  return elems.front();
}

template <class T>
std::deque<T> Queue<T>::raw_deque() const
{
  return elems;
}

template <class T>
unsigned int Queue<T>::size() const
{
  return elems.size();
}

template <class T>
void Queue<T>::pop()
{
  if (elems.empty())
  {
    std::cout << "cannot 'Queue<>::pop()': empty queue\n";
    exit(1);
  }

  elems.pop_front();
}

template <class T>
void Queue<T>::print()
{
  std::ostream_iterator<T> out(std::cout, "\n");
  copy(elems.begin(), elems.end(), out);
}

template <class T>
void Queue<T>::push(T const & elem)
{
  elems.push_back(elem);
  sort(elems.begin(), elems.end(), sort_method);
}
