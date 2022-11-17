#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4Proton.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"
#include "G4GenericMessenger.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"


#include "Analysis.hh"


class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
  MyPrimaryGenerator();
  ~MyPrimaryGenerator();

  virtual void GeneratePrimaries(G4Event*);

private:
  G4ParticleGun *fParticleGun;
  G4int ParticleNumber;

  
  G4bool IsRadioactive;
  
  
  G4double xgen, ygen, zgen;
  G4double zGenUser;
  G4ThreeVector momentumDirection;
  G4ThreeVector myParticlePosition;
  G4GenericMessenger *fMessenger;

};

#endif
