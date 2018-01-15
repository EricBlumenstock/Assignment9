#ifndef __gradeLineSummary_h__
#define __gradeLineSummary_h__

#include <string>
#include <vector>
#include <iosfwd>
#include <stdexcept>
#include <map>

using namespace std;

#include "gradeLine.h"

class LiftedGradeLineSummaryValue
{
public:
	typedef float summary_value_t;

private:
	summary_value_t summary;
	bool summaryIsValid;

public:
	//Constructors
	LiftedGradeLineSummaryValue() : summaryIsValid(false) {};
	LiftedGradeLineSummaryValue(const summary_value_t sum) : summary(sum), summaryIsValid(true) {};

	//Accessor
	summary_value_t getSummary();


};

ostream& operator<<(ostream&, LiftedGradeLineSummaryValue&);







class AbstractGradeLineSummary
{
public:
	typedef LiftedGradeLineSummaryValue (*summarizer_t)(const GradeLine::grade_line_t&);
	typedef string summary_name_t;

private:
	summarizer_t funcSummarizer;
	const char* summaryName;
	LiftedGradeLineSummaryValue summary;

public:
	//Constructors
	AbstractGradeLineSummary() : funcSummarizer(nullptr), summaryName(nullptr), summary() {};
	AbstractGradeLineSummary(summarizer_t function) : funcSummarizer(function), summaryName(nullptr), summary() {};
	AbstractGradeLineSummary(summarizer_t function, const char* sumName) : funcSummarizer(function), summaryName(sumName), summary() {};
	AbstractGradeLineSummary(summarizer_t& function, const char* sumName, LiftedGradeLineSummaryValue& sum) : funcSummarizer(function), summaryName(sumName), summary(sum) {};

	//copy assignment
	const AbstractGradeLineSummary& operator=(const AbstractGradeLineSummary&);

	//Accessors
	summary_name_t getObjName();
	LiftedGradeLineSummaryValue::summary_value_t getSummaryValue();

	//Mutator
	LiftedGradeLineSummaryValue updateGradeLine(const GradeLine&);

	//destructor
	virtual ~AbstractGradeLineSummary() {};

};

ostream& operator<<(ostream&, AbstractGradeLineSummary&);







template <const char* T, AbstractGradeLineSummary::summarizer_t P> 
class GradeLineSummary : public AbstractGradeLineSummary
{
public:
	//Constructors
	GradeLineSummary() : AbstractGradeLineSummary(P, T) {};
	GradeLineSummary(const GradeLine&) : AbstractGradeLineSummary(P, T) {};

	//Copy assignment
	const GradeLineSummary& operator=(const GradeLineSummary&)
	{
		return *this;
	};

};






class GradeLineSummaryOptions
{
public:
	typedef enum summary_option_t {Minimum, Maximum, Average};

private:
	vector<summary_option_t> enumVec;
	bool summaryIsValid = false;

public:
	//Constructor
	GradeLineSummaryOptions();

	//Accessor
	AbstractGradeLineSummary::summary_name_t& getName(const summary_option_t&) const;

	//Iterators
	inline vector<summary_option_t>::const_iterator itcbegin() const { return enumVec.cbegin(); };
	inline vector<summary_option_t>::const_iterator itcend() const { return enumVec.cend(); };

	//null destructor
	~GradeLineSummaryOptions(){};
};

ostream& operator<<(ostream& x, GradeLineSummaryOptions::summary_option_t);








class GradeLineSummaryFactory
{
public:
	typedef unique_ptr<AbstractGradeLineSummary> (*facFunPtr)(const GradeLine&);

private:
	facFunPtr facFunction;

public:
	
	//Constructors
	GradeLineSummaryFactory() = delete;
	GradeLineSummaryFactory(GradeLineSummaryOptions::summary_option_t option);

	//Accessors
	unique_ptr<AbstractGradeLineSummary> createPtrAbstractGradeLine();
	unique_ptr<AbstractGradeLineSummary> createPtrAbstractGradeLine(const GradeLine&);
		
	//Null decstructor
	~GradeLineSummaryFactory() {};
};

#endif