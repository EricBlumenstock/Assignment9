#ifndef __studentRecordCollection_h__
#define __studentRecordCollection_h__

#include <string>
#include <vector>
#include <iosfwd>
#include <map>

using namespace std;

#include "gradeLineSummary.h"
#include "studentRecord.h"


class SortOptions
{
public:
	typedef enum sort_option_t {ascending, decending};
	typedef string sort_option_name_t;

private:
	vector<sort_option_t> vecEnums;

public:
	//Constructor
	SortOptions();

	//Accessor
	sort_option_name_t getNameT(const sort_option_t);

	//Const Iterators
	inline vector<sort_option_t>::const_iterator itcbegin() const { return vecEnums.cbegin(); };
	inline vector<sort_option_t>::const_iterator itcend() const { return vecEnums.cend(); };

	//Null destructor
	~SortOptions(){};
};

ostream& operator<<(ostream&, SortOptions::sort_option_t);

class StudentRecordComparator {
public:
  // constructors
  //
  StudentRecordComparator() = delete;
  StudentRecordComparator(MeasurableOptions::measurable_t m_type) = delete;
  StudentRecordComparator(MeasurableOptions::measurable_t m_type, GradeLineSummaryOptions::summary_option_t);
  StudentRecordComparator(MeasurableOptions::measurable_t m_type, GradeLineSummaryOptions::summary_option_t, SortOptions::sort_option_t);

  // accessors
  //
  const string comparison_name(void) const;

  // comparator
  //
  bool operator() (const StudentRecord&, const StudentRecord&) const;

  // destructor
  //
  ~StudentRecordComparator() {};

private:
	MeasurableOptions::measurable_t  _meas_type;
	GradeLineSummaryOptions::summary_option_t _sum_type;
	SortOptions::sort_option_t  _sort_dir;
};

ostream& operator<<(ostream&, const StudentRecordComparator&);


class StudentRecordCollection {
public:
  typedef vector<StudentRecord> student_record_collection_t;

  // constructors
  //
  StudentRecordCollection(void);
  StudentRecordCollection(const student_record_collection_t&);

  // copy assignment -- should be defined when constructors are defined (rule of 3)
  //
  const StudentRecordCollection& operator=(const StudentRecordCollection&);

  //    
  // iterators for GradeLine objects: delegate iteration to the _gradeLine object
  //
  typedef student_record_collection_t::iterator iterator;
  inline iterator begin() { return _studentRecords.begin(); };
  inline iterator end() { return _studentRecords.end(); };
    
  typedef student_record_collection_t::const_iterator const_iterator;
  inline const_iterator cbegin() const { return _studentRecords.cbegin(); };
  inline const_iterator cend() const { return _studentRecords.cend(); };

  // mutator
  //
  void sort(const StudentRecordComparator&);
  
  // destructor
  //
  ~StudentRecordCollection() {};

private:
  student_record_collection_t _studentRecords;
};

ostream& operator<<(ostream&, const StudentRecordCollection&);

#endif