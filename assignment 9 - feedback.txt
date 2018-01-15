Eric -  5.9 of 0  (extra credit).

Apologies for it taking this long to grade assignment 9.  I've been
focusing on writing final exams and marking papers for research 
methods.

Congratulations on being the only person to complete this assignment. 
Well done.   

The issue with AbstractGradeLineSummary::getName() was that your code 
was returning a reference to a stack-allocated variable instead of a 
value that would persist beyond the method's lifetime:  i.e., instead
of writing

    AbstractGradeLineSummary::summary_name_t& GradeLineSummaryOptions::getName(const GradeLineSummaryOptions::summary_option_t& optionEnum) const
    {
        AbstractGradeLineSummary::summary_name_t temp = (GradeLineSummaryStatics::mapEnumToString.at(optionEnum));
        //string test = "TEST";
        return temp;
    } 
    
write

    AbstractGradeLineSummary::summary_name_t GradeLineSummaryOptions::getName(const GradeLineSummaryOptions::summary_option_t& optionEnum) const
    {
        AbstractGradeLineSummary::summary_name_t temp = (GradeLineSummaryStatics::mapEnumToString.at(optionEnum));
        //string test = "TEST";
        return temp;
    }
    
which returns the string by value.