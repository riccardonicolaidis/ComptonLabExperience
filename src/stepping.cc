#include "stepping.hh"


MySteppingAction::MySteppingAction(MyDetectorConstruction* det, MyEventAction* event)
: G4UserSteppingAction(), fDetector(det), fEventAction(event)
{}

MySteppingAction::~MySteppingAction()
{}


void MySteppingAction::UserSteppingAction(const G4Step *step)
{}