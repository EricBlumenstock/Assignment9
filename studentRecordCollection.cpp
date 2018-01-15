#include "studentRecordCollection.h"
#include "studentRecord.h"
#include "gradeLine.h"
#include "gradeLineSummary.h"

#include <ostream>
#include <algorithm>
#include <sstream>

static SortOptions SOStatic = SortOptions();

SortOptions::SortOptions()
{
	vecEnums.push_back(SortOptions::sort_option_t::ascending);
	vecEnums.push_back(SortOptions::sort_option_t::decending);
}

SortOptions::sort_option_name_t SortOptions::getNameT(const SortOptions::sort_option_t enumToConvert)
{
	static map <SortOptions::sort_option_t, SortOptions::sort_option_name_t> mapEnumToName{
			{ SortOptions::sort_option_t::ascending , "Ascending" },
			{ SortOptions::sort_option_t::decending, "Decending" },
	};

	return mapEnumToName.at(enumToConvert);
}

ostream& operator<<(ostream& x, SortOptions::sort_option_t enumToPrint)
{
	StudentRecordComparator comparer = StudentRecordComparator(MeasurableOptions::quiz, GradeLineSummaryOptions::Average, enumToPrint);
	stringstream ss;
	string temp;
	string tempReturn;

	ss << comparer;
	ss >> temp;
	ss >> temp;
	ss >> tempReturn;

	x << tempReturn;

	return x;
}


// method definitions for class StudentRecordComparator
//
StudentRecordComparator::StudentRecordComparator(MeasurableOptions::measurable_t m_type, GradeLineSummaryOptions::summary_option_t s_type) :
_meas_type(m_type), _sum_type(s_type), _sort_dir(SortOptions::sort_option_t::ascending) {};

StudentRecordComparator::StudentRecordComparator(MeasurableOptions::measurable_t m_type, GradeLineSummaryOptions::summary_option_t s_type, SortOptions::sort_option_t s_dir) :
   _meas_type(m_type), _sum_type(s_type), _sort_dir(s_dir) {};

const string StudentRecordComparator::comparison_name(void) const {
	//After much debugging:
	//Using GradeLineSummary option's accessor getName() was giving std::bad_alloc and [rethrow] errors
	//For a reason unknown it was supposedly returning the actual string "Minimum" but somewhere WITHIN the 
	//return process in external code the string gets deleted or disappears
	//I even tried just hard-coding-returning the string "TEST" but to no avail.
	//GradeLineSummaryOptions GLSumOptions = GradeLineSummaryOptions();
	//AbstractGradeLineSummary::summary_name_t name = GLSumOptions.getName(_sum_type);
	//string nameTwo = GLSumOptions.getName(_sum_type);

	MeasurableOptions tempOptions = MeasurableOptions();

	GradeLineSummaryFactory optionFunction = GradeLineSummaryFactory(_sum_type);
	unique_ptr<AbstractGradeLineSummary> temp = (optionFunction.createPtrAbstractGradeLine());
	
	string toRet = tempOptions.getNameT(_meas_type) + ", " + temp->getObjName() + ", " + SOStatic.getNameT(_sort_dir);
	return toRet;
}

bool StudentRecordComparator::operator() (const StudentRecord& sr1, const StudentRecord& sr2) const {
	GradeLineSummaryOptions options = GradeLineSummaryOptions();
	LiftedGradeLineSummaryValue sr1Value = LiftedGradeLineSummaryValue();
	LiftedGradeLineSummaryValue sr2Value = LiftedGradeLineSummaryValue();
	GradeLineSummaryFactory optionFunction = GradeLineSummaryFactory(_sum_type);

	unique_ptr<AbstractGradeLineSummary> sr1_sum = (optionFunction.createPtrAbstractGradeLine(sr1.measurable(_meas_type)));
	unique_ptr<AbstractGradeLineSummary> sr2_sum = (optionFunction.createPtrAbstractGradeLine(sr2.measurable(_meas_type)));
	sr1Value = sr1_sum->updateGradeLine(sr1.measurable(_meas_type));
	sr2Value = sr2_sum->updateGradeLine(sr2.measurable(_meas_type));

	float sumOne, sumTwo;
	stringstream ssOne, ssTwo;
	ssOne << sr1Value;
	ssOne >> sumOne;
	ssTwo << sr2Value;
	ssTwo >> sumTwo;

	return (_sort_dir == SortOptions::sort_option_t::ascending) ? (sumOne < sumTwo) : (sumOne > sumTwo);
}

// supporting functions
//
ostream& operator<<(ostream& os, const StudentRecordComparator& comparator) {
  os << comparator.comparison_name();
  return os;
}





// method definitions for class StudentRecordCollection
//
StudentRecordCollection::StudentRecordCollection(void): _studentRecords{} {};

StudentRecordCollection::StudentRecordCollection(const student_record_collection_t& student_records): _studentRecords(student_records) {};

const StudentRecordCollection& StudentRecordCollection::operator=(const StudentRecordCollection& source) {
  _studentRecords = source._studentRecords;
  return *this;
}

void StudentRecordCollection::sort(const StudentRecordComparator& comparator) {
  std::sort(_studentRecords.begin(), _studentRecords.end(), comparator);
  /* for (unsigned i = 0; (i + 1) < _studentRecords.size(); ++i)
    for (auto j = i + 1; j < _studentRecords.size(); ++j)
      if (!comparator(_studentRecords.at(i), _studentRecords.at(j))) swap(_studentRecords[i], _studentRecords[j]); */
}


// supporting functions
//
ostream& operator<<(ostream& os, const StudentRecordCollection& collection) {
  for (StudentRecordCollection::const_iterator it = collection.cbegin(); it != collection.cend(); ++it) os << *it << endl;
  os << endl;
  return os;
}

