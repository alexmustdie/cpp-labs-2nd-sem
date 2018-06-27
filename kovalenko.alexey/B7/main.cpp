#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iomanip>

class GetStats
{
public:
  GetStats() :
    max_(std::numeric_limits<int>::min()),
    min_(std::numeric_limits<int>::max()),
    positive_(0),
    negative_(0),
    numElements_(0),
    oddSum_(0),
    evenSum_(0)
  {
  }
  void operator() (int val)
  {
    max_ = std::max(max_, val);
    min_ = std::min(min_, val);

    if(val > 0)
    {
      positive_++;
    }
    else if(val < 0)
    {
      negative_++;
    }

    if(val % 2 == 0)
    {
      evenSum_ += val;
    }
    else
    {
      oddSum_ += val;
    }

    if(numElements_ == 0)
    {
      first_ = val;
    }

    last_ = val;
    numElements_++;
  }

  void printStats(std::ostream &out)
  {
    if(numElements_ == 0)
    {
      out << "No Data" << std::endl;
      return;
    }

    out << "Max: " << max_ << std::endl;
    out << "Min: " << min_ << std::endl;

    double mean = static_cast<double>(evenSum_ + oddSum_) / static_cast<double>(numElements_);

    out << "Mean: " << std::setprecision(1) << std::fixed << mean << std::endl;
    out << "Positive: " << positive_ << std::endl;
    out << "Negative: " << negative_ << std::endl;
    out << "Odd Sum: " << oddSum_ << std::endl;
    out << "Even Sum: " << evenSum_ << std::endl;
    out << "First/Last Equal: " << (first_ == last_ ? "yes" : "no") << std::endl;

  }

private:
  int max_, min_, positive_, negative_, first_, last_, numElements_;
  long long oddSum_, evenSum_;
};

int main()
{
  GetStats getStats;
  std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), std::ref(getStats));

  if(!std::cin.eof())
  {
    std::cerr << "Invalid input";
    return 1;
  }

  getStats.printStats(std::cout);

  return 0;
}
