#include <iostream>
#include <string>
#include <string_view>

#include "G4Types.hh"
#include "G4GenericPhysicsList.hh"

#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
//#include "QGSP_BERT_HP.hh"
#include "FTFP_BERT.hh"

#include "construction.hh" 
#include "physics.hh"
#include "verbose.hh"
#include "action.hh"       
#include "myglobals.hh"


int main(int argc, char** argv)
{

  G4UIExecutive *ui = 0;
  if( argc == 1)
  {
    ui = new G4UIExecutive(argc,argv);
  }
  
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4VSteppingVerbose::SetInstance(new SteppingVerbose);

  G4RunManager *runManager = new G4RunManager();

  
  PhysicsList* phys = new PhysicsList;
  runManager->SetUserInitialization(phys);

  MyDetectorConstruction* det= new MyDetectorConstruction;
  runManager -> SetUserInitialization(det);
  runManager -> SetUserInitialization(new MyActionInitialization(det));



  

  G4VisManager  *visManager = new G4VisExecutive();
  visManager -> Initialize();

  G4UImanager *UImanager =  G4UImanager::GetUIpointer();
  
  runManager -> Initialize();
  
  if(ui)
  {
      UImanager -> ApplyCommand("/control/execute vis.mac");      
      ui ->SessionStart();
      delete ui;
  }
  else 
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager -> ApplyCommand(command + fileName);
  }

  delete visManager;
  delete runManager;
  return 0;
}
