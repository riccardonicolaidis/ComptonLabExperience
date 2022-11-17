#ifndef RUN_HH
#define RUN_HH


#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4GenericMessenger.hh"


#include "construction.hh"
#include "generator.hh"


#include "Analysis.hh"

class MyDetectorConstruction;
class MyPrimaryGenerator;

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction(MyDetectorConstruction*, MyPrimaryGenerator*);
    ~MyRunAction();

    virtual void BeginOfRunAction(const G4Run* );
    virtual void EndOfRunAction(const G4Run* );

private:
    MyDetectorConstruction *fDetector;
    MyPrimaryGenerator *fPrimary;
    G4String TotalFileName;
    G4String TotalFileName2;
    G4GenericMessenger *fMessenger;
};

#endif