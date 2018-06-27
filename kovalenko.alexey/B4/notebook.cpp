#include "notebook.hpp"

Notebook::Notebook()
{
  bookmarks_["current"] = recording_.end();
}

Notebook::Notebook(const Notebook &other)
{
  *this = other;
}

Notebook& Notebook::operator =(const Notebook &other)
{
  if (this != &other)
  {
    recording_ = other.recording_;
    bookmarks_.clear();
    for (auto i = other.bookmarks_.cbegin(); i != other.bookmarks_.cend(); i++)
    {
      std::list<EntryElement>::const_iterator bookmarked = i->second;
      bookmarks_[i->first] = std::next(recording_.begin(), std::distance(other.recording_.cbegin(), bookmarked));
    }
  }
  return *this;
}

void Notebook::addNewRecord(const PhonebookEntry &record)
{
  EntryElement newElement;
  newElement.record = record;

  if (recording_.empty())
  {
    newElement.marks.insert("current");
    recording_.push_back(newElement);
    bookmarks_["current"] = recording_.begin();
  }
  else
  {
    recording_.push_back(newElement);
  }
}

void Notebook::addMarkName(const std::string &mark, const std::string &newMark)
{
  auto i = getIterator(mark);
  bookmarks_[newMark] = i->second;

  if (i->second != recording_.end())
  {
    i->second->marks.insert(newMark);
  }
}

void Notebook::insertBefore(const std::string &mark, const PhonebookEntry &record)
{
  if (recording_.empty())
  {
    addNewRecord(record);
    return;
  }
  auto i = getIterator(mark);
  if (i->second != recording_.end())
  {
    recording_.insert(i->second, EntryElement{ record, });
  }
  else
  {
    recording_.push_back(EntryElement{ record, });
  }
}

void Notebook::insertAfter(const std::string &mark, const PhonebookEntry &record)
{
  if (recording_.empty())
  {
    addNewRecord(record);
    return;
  }
  auto i = getIterator(mark);
  if (i->second != recording_.end())
  {
    recording_.insert(std::next(i->second), EntryElement{ record, });
  }
  else
  {
    recording_.push_back(EntryElement{ record, });
  }
}

void Notebook::replaceEntry(const std::string &mark, const PhonebookEntry &record)
{
  auto i = getIterator(mark);
  i->second->record = record;
}

void Notebook::deleteRecord(const std::string &mark)
{
  auto i = getIterator(mark);
  if (i->second != recording_.end())
  {
    auto clistElem = i->second;
    for (auto j = clistElem->marks.begin(); j != clistElem->marks.end(); j++)
    {
      if ((std::next(clistElem) == recording_.end()) && (recording_.size() > 1))
      {
        bookmarks_[*j] = std::prev(clistElem);
        std::prev(clistElem)->marks.insert(*j);
      }
      else
      {
        bookmarks_[*j] = std::next(clistElem);
        if (std::next(clistElem) != recording_.end())
        {
          std::next(clistElem)->marks.insert(*j);
        }
      }
    }
    recording_.erase(clistElem);
  }
}

void Notebook::showName(const std::string &mark)
{
  auto i = getIterator(mark);
  if (i->second == recording_.end())
  {
    std::cout << "<EMPTY>" << std::endl;
  }
  else
  {
    std::cout << i->second->record.phoneNumber << " " << i->second->record.username << std::endl;
  }
}

void Notebook::moveToNext(const std::string &mark)
{
  moveMark(mark, 1);
}

void Notebook::moveToPrev(const std::string &mark)
{
  moveMark(mark, -1);
}

void Notebook::moveMark(const std::string &mark, int steps)
{
  auto i = getIterator(mark);

  if (i->second != recording_.end())
  {
    i->second->marks.erase(mark);
  }

  std::advance(i->second, steps);

  if (i->second != recording_.end())
  {
    i->second->marks.insert(mark);
  }

}

void Notebook::moveMark(const std::string &mark, const std::string &location)
{
  auto i = getIterator(mark);
  if (location == "first")
  {
    if (i->second != recording_.end())
    {
      i->second->marks.erase(mark);
    }

    if (!recording_.empty())
    {
      i->second = recording_.begin();
      i->second->marks.insert(mark);
    }
    else
    {
      i->second = recording_.end();
    }
  }
  else if (location == "last")
  {
    if (i->second != recording_.end())
    {
      i->second->marks.erase(mark);
    }
    if (!recording_.empty())
    {
      i->second = std::prev(recording_.end());
      i->second->marks.insert(mark);
    }
    else
    {
      i->second = recording_.end();
    }
  }
  else
  {
    throw std::invalid_argument("<INVALID STEP>");
  }
}

Notebook::bookmarksIt_type Notebook::getIterator(const std::string &mark)
{
  auto i = bookmarks_.find(mark);
  if (i == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }
  return i;
}
