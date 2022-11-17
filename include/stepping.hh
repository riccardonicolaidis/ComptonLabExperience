#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include "construction.hh"
#include "event.hh"

#include "Analysis.hh"

class MyDetectorConstruction;
class MyEventAction;

class MySteppingAction : public G4UserSteppingAction
{
public:
    MySteppingAction(MyDetectorConstruction* ,MyEventAction *);
    ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step*);

private:
    MyEventAction *fEventAction;
    MyDetectorConstruction *fDetector;
};

#endif