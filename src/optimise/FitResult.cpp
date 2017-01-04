#include <FitResult.h>
#include <Histogram.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <Exceptions.h>
#include <Formatter.hpp>

FitResult::~FitResult(){
    delete fStatSpace;
}

void
FitResult::SetBestFit(const std::vector<double>& bestFit_){
    fBestFit = bestFit_;
}

std::vector<double>
FitResult::GetBestFit() const{
    return fBestFit;
}

void
FitResult::SetStatSpace(const Histogram& statSpace_){
    fStatSpace = new Histogram(statSpace_);
}

const Histogram&
FitResult::GetStatSpace() const{
    return *fStatSpace;
}

FitResult
FitResult::operator=(const FitResult& other_){
    if (!fStatSpace)
        fStatSpace = NULL;
    else
        fStatSpace = new Histogram(*other_.fStatSpace);
    fIsValid = other_.fIsValid;
    fBestFit = other_.fBestFit;
    fStatSample = other_.fStatSample;
    fParameterNames = other_.fParameterNames;
    f1DProjections = other_.f1DProjections;
    f2DProjections = other_.f2DProjections;
    return *this;
}

FitResult::FitResult(const FitResult& other_){
    if (!other_.fStatSpace)
        fStatSpace = NULL;

    else
        fStatSpace = new Histogram(*other_.fStatSpace);
    fParameterNames = other_.fParameterNames;
    fStatSample = other_.fStatSample;
    fBestFit = other_.fBestFit;
    fIsValid = other_.fIsValid;
    f1DProjections = other_.f1DProjections;
    f2DProjections = other_.f2DProjections;
}

const std::vector<std::vector<double> >&
FitResult::GetStatSample() const{
    return fStatSample;
}

void
FitResult::SetStatSample(const std::vector<std::vector<double> >& statSample_){
    fStatSample = statSample_;
}

bool
FitResult::GetValid() const {
    return fIsValid;
}

void
FitResult::SetValid(bool b_){
    fIsValid = b_;
}

void
FitResult::SetParameterNames(const std::vector<std::string>& names_){
    fParameterNames = names_;
}

std::vector<std::string>
FitResult::GetParameterNames() const{
    return fParameterNames;
}

void
FitResult::Print() const{
  std::cout << AsString() << std::endl;
}

void
FitResult::SaveAs(const std::string& fileName_) const{
  std::ofstream fs;
  fs.open(fileName_);
  fs << fileName_;
  fs.close();
}

std::string
FitResult::AsString() const{
  if(fParameterNames.size() != fBestFit.size())
      throw NotFoundError(Formatter() << "FitResult::Expected one name for each parameter - got " 
                            << fParameterNames.size() << " names and " << fBestFit.size() << " params"
                            );

  time_t t = time(0);
  struct tm * now = localtime(&t);
  
  std::stringstream ss;
  ss << "-----------------------------------"
     << "-----------------------------------" << std::endl
     << "OXSX Fit Result: "
     << now -> tm_year + 1900 << '-' 
     << now -> tm_mon + 1 << '-'
     << now -> tm_mday
     << "  "
     << now -> tm_hour
     << ":"
     << now -> tm_min
     << ":"
     << now -> tm_sec
     << std::endl
     << "-----------------------------------"
     << "-----------------------------------" << std::endl
     << std::endl;
       
  ss << "Best Fit Values: " << std::endl << std::endl;
  for(size_t i = 0; i < fParameterNames.size(); i++){
    ss << std::setw(25) 
       << fParameterNames.at(i) << "\t\t" 
       << std::setw(10) 
       << fBestFit.at(i)
       << std::endl;
  }
  return ss.str();
}

void 
FitResult::Set1DProjections(const HistMap& hists_){
  f1DProjections = hists_;
}

void 
FitResult::Set2DProjections(const HistMap& hists_){
  f2DProjections = hists_;
}

HistMap 
FitResult::Get1DProjections() const{
  return f1DProjections;
}

HistMap 
FitResult::Get2DProjections() const{
  return f2DProjections;
}
