#include "action.hh"

MyActionInitialization::MyActionInitialization(MyDetectorConstruction *detector) 
  : G4VUserActionInitialization(),
  fDetector(detector)
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{
  MyRunAction *runAction = new MyRunAction(fDetector, 0);
  SetUserAction(runAction);
}


void MyActionInitialization::Build() const
{
  MyPrimaryGenerator *primary = new MyPrimaryGenerator();
  SetUserAction(primary);

  MyRunAction *runAction = new MyRunAction(fDetector, primary);
  SetUserAction(runAction);

  MyEventAction *eventAction = new MyEventAction();
  SetUserAction(eventAction);

  MyTrackingAction* trackingAction = new MyTrackingAction(fDetector);
  SetUserAction(trackingAction);

  MySteppingAction *steppingAction = new MySteppingAction(fDetector,eventAction);
  SetUserAction(steppingAction);

}
