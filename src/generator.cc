#include "generator.hh"
#include "myglobals.hh"
#include "Randomize.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{ 
  // PARTICLE GUN DEFINITION
  fParticleGun = new G4ParticleGun(1);
  // COUNTER
  ParticleNumber = 0;
  IsRadioactive = false;
  zGenUser = 0*cm;

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "gamma";
  G4ParticleDefinition *particle = particleTable -> FindParticle(particleName);

  fMessenger = new G4GenericMessenger(this, "/ParticleGeneration/","Generation Properties");
  fMessenger -> DeclareProperty("Radioactive", IsRadioactive, "Generation properties Radioactive");
  fMessenger -> DeclareProperty("zGenUser", zGenUser, "Generation z position");


  fParticleGun -> SetParticleDefinition(particle);  
  fParticleGun -> SetParticleEnergy(1*MeV);
  fParticleGun -> SetParticlePosition(G4ThreeVector(-100.*cm,0.*cm,0.*cm));
  fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  double Pi = 3.14159265358979323846;

  if(IsRadioactive)
  {  
    //G4int Z = 71, A = 176;
    // Americio 241
    G4int Z = 71;
    G4int A = 176;
    G4double TkAlDet = 7.9 *mm;

    G4double LxLYSO = 1 * mm;
    G4double LyLYSO = 1 * mm;
    G4double LzLYSO = 1 * mm;

    G4double xLYSO = 0.;
    G4double yLYSO = 0.;
    G4double zLYSO = 2 * mm;

    G4double PercentageDepth = 0.1;
    xgen = xLYSO + PercentageDepth * LxLYSO * (G4UniformRand() - 0.5);
    ygen = yLYSO + PercentageDepth * LyLYSO * (G4UniformRand() - 0.5);
    zgen = zLYSO + PercentageDepth * LzLYSO * (G4UniformRand() - 0.5);

    //G4int Z = 27, A = 60;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;
    
    G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);
    fParticleGun -> SetParticleDefinition(ion);
    fParticleGun -> SetParticleCharge(ionCharge);
    fParticleGun -> SetParticlePosition(G4ThreeVector(xgen, ygen, zgen));
    fParticleGun -> SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    fParticleGun -> SetParticleEnergy(0*eV);
    fParticleGun -> GeneratePrimaryVertex(anEvent);
  }
  else
  {
    fParticleGun -> GeneratePrimaryVertex(anEvent);
  }



  // COUNTER
  if(ParticleNumber%10000 == 0)
  {
    G4cout << ParticleNumber << G4endl;
  }
  ++ParticleNumber;  
}
