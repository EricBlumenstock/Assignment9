#ifndef __studentRecord_h__
#define __studentRecord_h__

#include <string>
#include <vector>
#include <iosfwd>
#include <map>

using namespace std;

#include "gradeLine.h"
#include "gradeLineSummary.h"

class MeasurableOptions
{
public:
	typedef enum measurable_t{ homework, quiz, test };
	typedef string measurable_name_t;

private:
	vector<measurable_t> vecEnums;

public:
	//Constructors
	MeasurableOptions();

	//Accessor
	measurable_name_t getNameT(const measurable_t);

	//Const Iterators
	inline vector<measurable_t>::const_iterator itcbegin() const { return vecEnums.cbegin(); };
	inline vector<measurable_t>::const_iterator itcend() const { return vecEnums.cend(); };

	//Destructor
	~MeasurableOptions(){};
};

ostream& operator<<(ostream&, MeasurableOptions::measurable_t);


class StudentRecord {
  public:
    typedef map<MeasurableOptions::measurable_t, GradeLine> measurables_to_grade_lines_t;
    typedef string student_name_t;
    
    // constructors
    //
	StudentRecord() = delete;
	StudentRecord(const student_name_t) = delete;
    StudentRecord(const student_name_t, const measurables_to_grade_lines_t&);

    // copy assignment -- should be defined when constructors are defined (rule of 3)
    //
    const StudentRecord& operator=(const StudentRecord&);

    // accessors
    //
    const inline student_name_t name(void) const {return _student_name;}
    //
    // here, it makes sense to expose the measurable structures directly
    //
    GradeLine& measurable(const MeasurableOptions::measurable_t);
	const GradeLine& measurable(const MeasurableOptions::measurable_t) const;

    // destructor
    //
    ~StudentRecord() {};
     
  private:
	MeasurableOptions MO = MeasurableOptions();

    string _student_name;
    measurables_to_grade_lines_t _measurables;
};

ostream& operator<<(ostream&, const StudentRecord&);

#endif