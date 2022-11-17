#ifndef TRACKING_HH
#define TRACKING_HH

#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4HadronicProcessType.hh"
#include "G4SystemOfUnits.hh"

#include "construction.hh"

#include "Analysis.hh"

class MyDetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MyTrackingAction : public G4UserTrackingAction {

  public:  
    MyTrackingAction(MyDetectorConstruction*);
   ~MyTrackingAction();
   
    virtual void  PreUserTrackingAction(const G4Track*);   
    virtual void PostUserTrackingAction(const G4Track*);
    
  private:
    MyDetectorConstruction* fDetector;
};




#endif