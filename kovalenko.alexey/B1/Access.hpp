#ifndef ACCESS_HPP_INCLUDED
#define ACCESS_HPP_INCLUDED

#include <memory>

template <typename ContainerType>
struct Access
{
  using element_t = typename ContainerType::value_type;

  struct Bracket
  {
    element_t* getElement(const ContainerType &container, size_t index) const
    {
      return const_cast<element_t*>(&container[index]);
    }
  };

  struct At
  {
    element_t* getElement(const ContainerType &container, size_t index) const
    {
      return const_cast<element_t*>(&container.at(index));
    }
  };

  struct Iter
  {
    element_t* getElement(const ContainerType &container, size_t index) const
    {
      auto iter = container.begin();

      for (size_t i = 0; iter != container.end();++iter, i++)
      {
        if (i == index)
        {
          break;
        }
      }

      return const_cast<element_t*>(&(*iter));
    }
  };
};

#endif
