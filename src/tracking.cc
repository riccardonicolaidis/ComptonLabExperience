#include "tracking.hh"

MyTrackingAction::MyTrackingAction(MyDetectorConstruction* det)
:G4UserTrackingAction(), fDetector(det)
{}

MyTrackingAction::~MyTrackingAction()
{}


void MyTrackingAction::PreUserTrackingAction(const G4Track* track)
{}


void MyTrackingAction::PostUserTrackingAction(const G4Track* )
{}