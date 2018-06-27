#ifndef READSTATE
#define READSTATE

class ReadState
{
public:
  ReadState();
  
  void setWord();
  void setSyntax();
  void setSpace();
  void setComma();
  void setDash();

  bool getSpace() const;
  bool getNewWord() const;

private:
  bool word_;
  bool syntax_;
  bool space_;
  bool comma_;
};

#endif
