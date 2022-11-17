#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"
#include "stepping.hh"
#include "event.hh"
#include "detector.hh"
#include "tracking.hh"

class MyDetectorConstruction;


class MyActionInitialization : public  G4VUserActionInitialization
{
public:
  MyActionInitialization(MyDetectorConstruction *detector);
  virtual ~MyActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;


private:
  MyDetectorConstruction *fDetector;
};

#endif
