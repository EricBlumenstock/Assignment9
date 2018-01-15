#include "gradeLineSummary.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

LiftedGradeLineSummaryValue::summary_value_t LiftedGradeLineSummaryValue::getSummary() 
{
	if (!summaryIsValid)
		throw runtime_error("Boolean summary flag is FALSE");

	return summary;
}

ostream& operator<<(ostream& x, LiftedGradeLineSummaryValue& gradeSum)
{
	try
	{
		x << gradeSum.getSummary();
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}

	return x;
}

const AbstractGradeLineSummary& AbstractGradeLineSummary::operator=(const AbstractGradeLineSummary& source)
{
	funcSummarizer = source.funcSummarizer;
	summaryName = source.summaryName;
	summary = source.summary;
	return *this;
};

AbstractGradeLineSummary::summary_name_t AbstractGradeLineSummary::getObjName()
{
	string temp(summaryName);
	return temp;
}

namespace GradeLineSummaryStatics
{
	char maxi[] = "Maximum",
		mini[] = "Minimum",
		avrg[] = "Average";
	
	static map < GradeLineSummaryOptions::summary_option_t, char*> mapEnumToString {
			{GradeLineSummaryOptions::summary_option_t::Maximum, maxi},
			{ GradeLineSummaryOptions::summary_option_t::Minimum, mini },
			{ GradeLineSummaryOptions::summary_option_t::Average, avrg },
	};

	LiftedGradeLineSummaryValue minFunc(const GradeLine::grade_line_t& grades)
	{
		if (grades.empty())
			return LiftedGradeLineSummaryValue();
		else
		{
			float min = *(min_element(grades.cbegin(), grades.cend()));
			return LiftedGradeLineSummaryValue(min);
		}
	}

	LiftedGradeLineSummaryValue maxFunc(const GradeLine::grade_line_t& grades)
	{
		if (grades.empty())
			return LiftedGradeLineSummaryValue();
		else
		{
			float max = *(max_element(grades.cbegin(), grades.cend()));
			return LiftedGradeLineSummaryValue(max);
		}
	}

	LiftedGradeLineSummaryValue avgFunc(const GradeLine::grade_line_t& grades)
	{
		if (grades.empty())
			return LiftedGradeLineSummaryValue();
		else
		{
			float avg = (accumulate(grades.cbegin(), grades.cend(), 0)) / grades.size();
			return LiftedGradeLineSummaryValue(avg);
		}
	}

	typedef unique_ptr<AbstractGradeLineSummary>(*factoryFunc)(const GradeLine& grades);
	/*Templates are instantiated during the compilation, so that their parameters have to be known before the program runs.
	That means you cannot use a variable as a template parameter. Such a parameters must be constant expressions
	(constant variables is not enough), addresses of functions or objects with external linkage, or addresses of static class members.*/
	unique_ptr<AbstractGradeLineSummary> factoryMin(const GradeLine& grades)
	{
		return unique_ptr<AbstractGradeLineSummary>(new GradeLineSummary<mini, minFunc>(grades));
	}

	unique_ptr<AbstractGradeLineSummary> factoryMax(const GradeLine& grades)
	{
		return unique_ptr<AbstractGradeLineSummary>(new GradeLineSummary<maxi, maxFunc>(grades));
	}

	unique_ptr<AbstractGradeLineSummary> factoryAvg(const GradeLine& grades)
	{
		return unique_ptr<AbstractGradeLineSummary>(new GradeLineSummary<avrg, avgFunc>(grades));
	}

	
	static map < GradeLineSummaryOptions::summary_option_t, factoryFunc > mapEnumToFunction {
	{GradeLineSummaryOptions::summary_option_t::Maximum, factoryMax},
	{ GradeLineSummaryOptions::summary_option_t::Minimum, factoryMin },
	{ GradeLineSummaryOptions::summary_option_t::Average, factoryAvg },
	};
}


ostream& operator<<(ostream& x, AbstractGradeLineSummary& summary)
{
	stringstream ss;
	x << summary.getObjName();
	
	try
	{
		ss << summary.getSummaryValue();
		x << "Grade: " << ss.str() << endl;
	}
	catch (exception& e)
	{
	}

	return x;
}

LiftedGradeLineSummaryValue::summary_value_t AbstractGradeLineSummary::getSummaryValue()
{
	return summary.getSummary();
}

LiftedGradeLineSummaryValue AbstractGradeLineSummary::updateGradeLine(const GradeLine& grades)
{
	if (funcSummarizer == NULL)
		throw runtime_error("Summarizer is NULL");
	else
	{
		GradeLine::grade_line_t temp;
		for (auto it = grades.cbegin(); it != grades.cend(); ++it)
		{
			temp.push_back(*it);
		}
		
		return funcSummarizer(temp);
	}
}

GradeLineSummaryOptions::GradeLineSummaryOptions()
{
	for (auto it = GradeLineSummaryStatics::mapEnumToString.cbegin(); it != GradeLineSummaryStatics::mapEnumToString.cend(); ++it)
	{
		enumVec.push_back(it->first);
	}
	summaryIsValid = true;
}


//Strange issues within this getName
AbstractGradeLineSummary::summary_name_t& GradeLineSummaryOptions::getName(const GradeLineSummaryOptions::summary_option_t& optionEnum) const
{
	AbstractGradeLineSummary::summary_name_t temp = (GradeLineSummaryStatics::mapEnumToString.at(optionEnum));
	//string test = "TEST";
	return temp;
}




ostream& operator<<(ostream& x, GradeLineSummaryOptions::summary_option_t enumer)
{
	static const GradeLineSummaryOptions options = GradeLineSummaryOptions();
	x << options.getName(enumer);

	return x;
}

GradeLineSummaryFactory::GradeLineSummaryFactory(GradeLineSummaryOptions::summary_option_t option) : facFunction(GradeLineSummaryStatics::mapEnumToFunction.at(option))
{
	facFunction = GradeLineSummaryStatics::mapEnumToFunction.at(option);
}

unique_ptr<AbstractGradeLineSummary> GradeLineSummaryFactory::createPtrAbstractGradeLine()
{
	GradeLine temp;
	return facFunction(temp);
}

unique_ptr<AbstractGradeLineSummary> GradeLineSummaryFactory::createPtrAbstractGradeLine(const GradeLine& grades)
{
	return facFunction(grades);
}