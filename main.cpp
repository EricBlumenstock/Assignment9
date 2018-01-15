#include "studentRecordCollection.h"

#include <iostream>

using namespace std;

namespace student_data{
   StudentRecordCollection student_records =
    StudentRecordCollection{
      StudentRecordCollection::student_record_collection_t{
        StudentRecord{
          string("alan alda"),
          StudentRecord::measurables_to_grade_lines_t{
           {MeasurableOptions::quiz,     GradeLine( GradeLine::grade_line_t{ 8, 4, 3, 5, 1, 6, 2, 9, 7 })},
           {MeasurableOptions::test,     GradeLine( GradeLine::grade_line_t{ 80, 90 })},
           {MeasurableOptions::homework, GradeLine( GradeLine::grade_line_t{ 19, 14, 13, 12, 16, 10, 14, 18 })}
          }
        },
        StudentRecord{
          string("bob behr"),
          StudentRecord::measurables_to_grade_lines_t{
		   { MeasurableOptions::quiz, GradeLine(GradeLine::grade_line_t{ 7, 3, 4, 9, 10, 10, 4, 8, 7 }) },
		   { MeasurableOptions::test, GradeLine(GradeLine::grade_line_t{ 91, 90 }) },
		   { MeasurableOptions::homework, GradeLine(GradeLine::grade_line_t{ 13, 18, 10, 19, 20, 14, 14, 12 }) }
          }
        },
        StudentRecord{
          string("carol crawford"),
          StudentRecord::measurables_to_grade_lines_t{
		   { MeasurableOptions::quiz, GradeLine(GradeLine::grade_line_t{ 7, 8, 10, 8, 7, 1, 4, 2, 10 }) },
		   { MeasurableOptions::test, GradeLine(GradeLine::grade_line_t{ 55, 80 }) },
		   { MeasurableOptions::homework, GradeLine(GradeLine::grade_line_t{ 3, 8, 10, 9, 4, 9, 4, 2 }) }
          }
        },
        StudentRecord{
          string("dawn dawes"),
          StudentRecord::measurables_to_grade_lines_t{
		   { MeasurableOptions::quiz, GradeLine(GradeLine::grade_line_t{ 10, 10, 10, 9, 10, 8, 10, 6, 4 }) },
		   { MeasurableOptions::test, GradeLine(GradeLine::grade_line_t{ 85, 100 }) },
		   { MeasurableOptions::homework, GradeLine(GradeLine::grade_line_t{ 18, 10, 19, 8, 13, 17, 4, 12 }) }
          }
        }
      }
    };
};

int main(void) {
  using namespace student_data;

  MeasurableOptions measurableInstance = MeasurableOptions();
  GradeLineSummaryOptions gradeLineOptionsInstance = GradeLineSummaryOptions();
  SortOptions sortInstance = SortOptions();

  for (auto measurable = measurableInstance.itcbegin(); measurable != measurableInstance.itcend(); ++measurable) {
	  for (auto summary = gradeLineOptionsInstance.itcbegin(); summary != gradeLineOptionsInstance.itcend(); ++summary) {
		  for (auto direction = sortInstance.itcbegin(); direction != sortInstance.itcend(); ++direction) {
        StudentRecordComparator comparator{*measurable, *summary, *direction};
        cout << "sorted by " << comparator << endl;
        student_records.sort(comparator);
		cout << student_records << endl << endl;
      }
    }
  }
}
