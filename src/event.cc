#include "event.hh"
#include "myglobals.hh"

MyEventAction::MyEventAction()
{}

MyEventAction::~MyEventAction()
{}



void MyEventAction::BeginOfEventAction(const G4Event*)
{}


void MyEventAction::EndOfEventAction(const G4Event* event)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  //man -> FillNtupleDColumn(0,);

  // DEFINITIONS OF THE HISTOGRAMNS WITH COUNTS
  //G4VHitsCollection* hc_Thin        = event->GetHCofThisEvent()->GetHC(0);
  //G4VHitsCollection* hc_LYSO        = event->GetHCofThisEvent()->GetHC(1);
  //G4VHitsCollection* hc_NaI         = event->GetHCofThisEvent()->GetHC(2);
  
  G4VHitsCollection *hTarget        = event->GetHCofThisEvent()->GetHC(0);

  G4VHitsCollection* hDetector      = event->GetHCofThisEvent()->GetHC(1);

 

  

  G4double Ed_Target = 0.;
  G4double Ed_Det[NDetectors];

  for(G4int i = 0; i < NDetectors; ++i)
  {
    Ed_Det[i] = 0.;
  }
  
  


  // ENERGY MEASUREMENTS

  // TARGET
  for(G4int iH = 0; iH < (hTarget->GetSize()); ++iH)
  {
    
    HitClass* hit=static_cast<HitClass*>(hTarget->GetHit(iH));
    Ed_Target += hit->GetEdep();
  }

  G4int ReplicaNo;
  for(G4int iH = 0; iH < (hDetector -> GetSize()); ++iH)
  {
    HitClass* hit=static_cast<HitClass*>(hDetector->GetHit(iH));
    ReplicaNo = hit->GetReplicaNb();
    Ed_Det[ReplicaNo] += hit->GetEdep();
  }

  for(G4int j = 0 ; j < NDetectors; ++j)
  {
    man -> FillNtupleDColumn(j,Ed_Det[j]);
  }
  man -> FillNtupleDColumn(NDetectors, Ed_Target);


  bool SaveEvent = false;

  for(int i = 0; i < NDetectors; ++i)
  {
    if(Ed_Det[i] > 0.)
    {
      SaveEvent = true;
    }
  }


  if((Ed_Target > 0) & SaveEvent)
  {
    man -> AddNtupleRow(0);
  }
  
  


}
