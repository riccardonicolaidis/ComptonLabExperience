#include "hit.hh"

G4ThreadLocal G4Allocator<HitClass>* HitAllocator=0;


HitClass::HitClass()
 : G4VHit(),
   fTrackID(-1),
   fReplicaNb(-1),
   fEdep(0.),
   fTime(0.),
   fPos(G4ThreeVector())
{}


HitClass::~HitClass() {}


const HitClass& HitClass::operator=(const HitClass& right)
{
  fTrackID   = right.fTrackID;
  fReplicaNb = right.fReplicaNb;
  fEdep      = right.fEdep;
  fTime      = right.fTime;
  fPos       = right.fPos;

  return *this;
}

G4bool HitClass::operator==(const HitClass& right) const
{
  return ( this == &right ) ? true : false;
}



void HitClass::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(fPos);
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}


void HitClass::Print()
{
  G4cout
     << "  trackID: " << fTrackID << " replicaNb: " << fReplicaNb
     << "Edep: "
     << std::setw(7) << G4BestUnit(fEdep,"Energy")
     << "Time: "
     << std::setw(7) << G4BestUnit(fTime,"Time")
     << " Position: "
     << std::setw(7) << G4BestUnit( fPos,"Length")
     << G4endl;
}

