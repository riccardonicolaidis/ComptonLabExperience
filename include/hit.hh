#ifndef HIT_HH
#define HIT_HH

#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include <iomanip>
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"


#include "Analysis.hh"

class HitClass : public G4VHit
{
  public:
    HitClass();
    HitClass(const HitClass&);
    virtual ~HitClass();

    // operators
    const HitClass& operator=(const HitClass&);
    G4bool operator==(const HitClass&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
    void SetTrackID  (G4int track)      { fTrackID = track; };
    void SetChamberNb(G4int replica)      { fReplicaNb = replica; };
    void SetEdep     (G4double de)      { fEdep = de; };
    void SetTime     (G4double time)    { fTime = time; };
    void SetPos      (G4ThreeVector xyz){ fPos = xyz; };

    // Get methods
    G4int GetTrackID() const     { return fTrackID; };
    G4int GetReplicaNb() const   { return fReplicaNb; };
    G4double GetEdep() const     { return fEdep; };
    G4double GetTime() const     { return fTime; };
    G4ThreeVector GetPos() const { return fPos; };

  private:

      G4int         fTrackID;
      G4int         fReplicaNb;
      G4double      fEdep;
      G4double      fTime;
      G4ThreeVector fPos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<HitClass> HitsCollection;

extern G4ThreadLocal G4Allocator<HitClass>* HitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* HitClass::operator new(size_t)
{
  if(!HitAllocator)
      HitAllocator = new G4Allocator<HitClass>;
  return (void *) HitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void HitClass::operator delete(void *hit)
{
  HitAllocator->FreeSingle((HitClass*) hit);
}




#endif