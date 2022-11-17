#ifndef VERBOSE_HH
#define VERBOSE_HH



#include "G4SteppingVerbose.hh"
#include "G4SteppingManager.hh"
#include "G4ParticleTypes.hh"
#include "G4UnitsTable.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class SteppingVerbose : public G4SteppingVerbose {

public:   

  SteppingVerbose();
 ~SteppingVerbose();
 
  virtual void TrackingStarted();
  virtual void StepInfo();
};



#endif