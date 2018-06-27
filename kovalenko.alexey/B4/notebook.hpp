#ifndef NOTEBOOK
#define NOTEBOOK

#include <iostream>
#include <string>
#include <set>
#include <list>
#include <map>

class Notebook
{
public:

  struct PhonebookEntry
  {
    std::string phoneNumber, username;
  };

  Notebook();
  Notebook(const Notebook & other);
  Notebook(Notebook && other) = default;
  Notebook & operator=(const Notebook & other);
  Notebook & operator=(Notebook && other) = default;

  void addNewRecord(const PhonebookEntry & record);
  void addMarkName(const std::string & mark, const std::string & newMark);
  void insertBefore(const std::string & mark, const PhonebookEntry & record);
  void insertAfter(const std::string & mark, const PhonebookEntry & record);
  void replaceEntry(const std::string & mark, const PhonebookEntry & record);
  void deleteRecord(const std::string & mark);
  void showName(const std::string & mark);
  void moveToNext(const std::string & mark);
  void moveToPrev(const std::string & mark);
  void moveMark(const std::string & mark, int steps);
  void moveMark(const std::string & mark, const std::string & location);

private:

  struct EntryElement
  {
    PhonebookEntry record;
    std::set<std::string> marks;
  };

  typedef std::list<EntryElement> recording_type;
  typedef std::map<std::string, recording_type::iterator> bookmarks_type;
  typedef bookmarks_type::iterator bookmarksIt_type;

  recording_type recording_;
  bookmarks_type bookmarks_;
  bookmarksIt_type getIterator(const std::string & mark);
};

#endif
