#include "run.hh"
#include "myglobals.hh"
#include <iostream>
#include <string>
#include <string_view>
#include <fstream>

MyRunAction::MyRunAction(MyDetectorConstruction* det, MyPrimaryGenerator* prim)
  : G4UserRunAction(),
    fDetector(det), fPrimary(prim)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    fMessenger = new G4GenericMessenger(this, "/NameOfFile/","Name of the file to save data");
    fMessenger -> DeclareProperty("NameOfFile", TotalFileName, "Name of the file to save data");
 
    man -> SetVerboseLevel(1);
    man -> CreateNtuple("Edep","Edep");
    
    for(G4int i = 0; i < NDetectors; ++i)
    {
        G4String NameColumn = "Ed_"+std::to_string(i);
        man -> CreateNtupleDColumn(NameColumn);
    }
    man -> CreateNtupleDColumn("EdTarget");


}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    TotalFileName2 = TotalFileName + ".root";
    man -> OpenFile(TotalFileName2);
}

void MyRunAction::EndOfRunAction(const G4Run* )
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man -> Write();
    man -> CloseFile(TotalFileName2);
}