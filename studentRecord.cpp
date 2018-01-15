#include "studentRecord.h"
#include "studentRecordCollection.h"

#include <ostream>
#include <map>
#include <sstream>

static MeasurableOptions MOStatic = MeasurableOptions();

// method definitions for class StudentRecord
//
StudentRecord::StudentRecord(const student_name_t name, const measurables_to_grade_lines_t& measurables): _student_name(name), _measurables(measurables) {};


const StudentRecord& StudentRecord::operator=(const StudentRecord& source) {
   _student_name = source.name();
   _measurables = source._measurables;
   return *this;
}

GradeLine& StudentRecord::measurable(const MeasurableOptions::measurable_t m_type) { return _measurables.at(m_type); };

const GradeLine& StudentRecord::measurable(const MeasurableOptions::measurable_t m_type) const { return _measurables.at(m_type); };

 
// supporting functions for class StudentRecord
//
ostream& operator<<(ostream& os, const StudentRecord& student) {
   os.precision(1);
   os << fixed;
   os << "student name: " << student.name() << endl;
   for (auto m_type = MOStatic.itcbegin(); m_type != MOStatic.itcend(); ++m_type)
	   os << *m_type << " grades: " << student.measurable(*m_type) << endl;
   os << endl;
   return os;
}


MeasurableOptions::MeasurableOptions()
{
	vecEnums.push_back(measurable_t::homework);
	vecEnums.push_back(measurable_t::quiz);
	vecEnums.push_back(measurable_t::test);
}

//Why give this function "max" "min" and "avg" enums from gradeLineSummaryOptions?
MeasurableOptions::measurable_name_t MeasurableOptions::getNameT(const MeasurableOptions::measurable_t enumToConvert)
{
	static map <MeasurableOptions::measurable_t, MeasurableOptions::measurable_name_t> mapEnumToName{
			{ MeasurableOptions::measurable_t::homework, "Homework" },
			{ MeasurableOptions::measurable_t::quiz, "Quiz" },
			{ MeasurableOptions::measurable_t::test, "Test" },
	};


	return mapEnumToName.at(enumToConvert);
}

ostream& operator<<(ostream& x, MeasurableOptions::measurable_t theEnum)
{
	StudentRecordComparator comparer = StudentRecordComparator(theEnum, GradeLineSummaryOptions::Average);
	stringstream ss;
	ss << comparer;
	string temp;
	ss >> temp;

	x << temp;

	return x;
}