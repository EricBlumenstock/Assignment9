#ifndef __gradeLine_h__
#define __gradeLine_h__

#include <string>
#include <vector>
#include <iosfwd>
#include <memory>

using namespace std;

class GradeLine {
  public:
    typedef unsigned grade_t;
    typedef vector<grade_t> grade_line_t;
      
    // constructors
    //
    GradeLine(void);
    GradeLine(const grade_line_t&);

    // copy assignment -- should be defined when constructors are defined (rule of 3)
    //
    const GradeLine& operator=(const GradeLine&);

    // accessors
    //
	bool isEmpty(void) const;
	size_t size(void) const;
    //    
    // iterators for GradeLine objects: delegate iteration to the _gradeLine object
    //
    typedef grade_line_t::iterator iterator;
	iterator begin();
	iterator end();
    
    typedef grade_line_t::const_iterator const_iterator;
    const_iterator cbegin() const;
	const_iterator cend() const;

    // destructor
    //
	~GradeLine();
     
  private:
	struct gradeLineImpl;
	shared_ptr<gradeLineImpl> pImpl;

};

ostream& operator<<(ostream&, const GradeLine&);

#endif
