#ifndef QUEUEWITHPRIORITY_HPP_INCLUDED
#define QUEUEWITHPRIORITY_HPP_INCLUDED

#include <iostream>
#include <stdexcept>
#include <list>

typedef enum
{
  LOW,
  NORMAL,
  HIGH
} ElementPriority;

template <typename QueueElement>
class QueueWithPriority
{
public:
  QueueWithPriority() = default;
  virtual ~QueueWithPriority() = default;
  
  void putElementToQueue(const QueueElement& element,
    ElementPriority priority);
  ElementPriority getAvailablePriority() const;
  QueueElement getElementFromQueue();
  void accelerate();

private:
  std::list<QueueElement> queue_[3];
};

template <typename QueueElement>
void QueueWithPriority<QueueElement>::putElementToQueue(const QueueElement& element,
  ElementPriority priority)
{
  queue_[priority].push_back(element);
}

template <typename QueueElement>
ElementPriority QueueWithPriority<QueueElement>::getAvailablePriority() const
{
  if (!queue_[HIGH].empty())
  {
    return HIGH;
  }
  else if (!queue_[NORMAL].empty())
  {
    return NORMAL;
  }
  else if (!queue_[LOW].empty())
  {
    return LOW;
  }
  else
  {
    throw std::logic_error("<EMPTY>");
  }
}

template <typename QueueElement>
QueueElement QueueWithPriority<QueueElement>::getElementFromQueue()
{
  ElementPriority priority = getAvailablePriority();

  QueueElement element = queue_[priority].front();
  queue_[priority].pop_front();

  return element;
}

template <typename QueueElement>
void QueueWithPriority<QueueElement>::accelerate()
{
  queue_[HIGH].splice(queue_[HIGH].end(), queue_[LOW]);
}

#endif
