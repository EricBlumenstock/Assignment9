#include "gradeLine.h"

#include <ostream>
#include <sstream>

struct GradeLine::gradeLineImpl{
	grade_line_t _gradeLine;
};

GradeLine::GradeLine(void) : pImpl{new gradeLineImpl} {};
GradeLine::GradeLine(const grade_line_t& grade_data) : pImpl{ new gradeLineImpl }
{
	pImpl->_gradeLine = grade_data;
};


const GradeLine& GradeLine::operator=(const GradeLine& source) {
  pImpl->_gradeLine = source.pImpl->_gradeLine;
  return *this;
}


// supporting functions
//
ostream& operator<<(ostream& os, const GradeLine& gl) {
  os.precision(1);
  os << fixed;
  string result{};
  for (GradeLine::const_iterator it = gl.cbegin(); it != gl.cend(); ++it) {
    ostringstream this_value;
    this_value << *it << ", ";
    result += this_value.str();
  }
  os << result.substr(0, result.size() - 2);
  return os;
}

//Supposed to be "delete pImpl;" according to slides however that does not compile.
//pImpl.~shared_ptr(); destroys the pointer right after their value changes by assignment.
//shared ptr objects destroy themselves once all ownerships have been released
GradeLine::~GradeLine() {};//pImpl.~shared_ptr(); };

bool GradeLine::isEmpty(void) const { return pImpl->_gradeLine.size() == 0; }
size_t GradeLine::size(void) const { return pImpl->_gradeLine.size(); }

//    
// iterators for GradeLine objects: delegate iteration to the _gradeLine object
//
GradeLine::iterator GradeLine::begin() { return pImpl->_gradeLine.begin(); };
GradeLine::iterator GradeLine::end() { return pImpl->_gradeLine.end(); };


GradeLine::const_iterator GradeLine::cbegin() const { return pImpl->_gradeLine.cbegin(); };
GradeLine::const_iterator GradeLine::cend() const { return pImpl->_gradeLine.cend(); };