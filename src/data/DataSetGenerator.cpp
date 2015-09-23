#include <DataSetGenerator.h>
#include <DataSet.h>
#include <OXSXDataSet.h>
#include <DataExceptions.h>
#include <math.h>
#include <EventData.h>
#include <stdlib.h>

void
DataSetGenerator::SetDataHandles(const std::vector<DataSet*> handles_){
    fDataSets = handles_;
}

void
DataSetGenerator::SetExpectedRates(const std::vector<double>& rates_){
    fExpectedRates = rates_;
}

OXSXDataSet
DataSetGenerator::ExpectedRatesDataSet() const{
    if(fExpectedRates.size() != fDataSets.size())
        throw DataException("Can't generate fake data: need one rate exactly for each data set");

    OXSXDataSet dataSet;
    for(size_t i = 0; i < fDataSets.size(); i++){
        unsigned expectedCounts = round(fExpectedRates.at(i));
    for(unsigned j = 0; j < expectedCounts; j++)
        dataSet.AddEntry(RandomEvent(i));
    }
    return dataSet;
}

EventData
DataSetGenerator::RandomEvent(size_t handleIndex_) const{
    unsigned eventNum = (rand() % (int)(fDataSets.at(handleIndex_)->GetNEntries() + 1));
    return fDataSets.at(handleIndex_)->GetEntry(eventNum);
}
