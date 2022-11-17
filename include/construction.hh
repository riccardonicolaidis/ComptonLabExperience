#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH


#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4GenericMessenger.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4GenericMessenger.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
//#include "G4GDMLParser.hh"
#include <cmath>
#include "G4VisAttributes.hh"


#include "Analysis.hh"
#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  MyDetectorConstruction();
  ~MyDetectorConstruction();


  virtual G4VPhysicalVolume *Construct();

private:

  virtual void ConstructSDandField();

  // World
  G4Box             *solidWorld;
  G4LogicalVolume   *logicWorld;
  G4VPhysicalVolume *physWorld;
  G4VisAttributes   *visWorld;

  //G4Tubs            *solidNaI;
  //G4LogicalVolume   *logicNaI;
  //G4VPhysicalVolume *physNaI;
  //G4VisAttributes   *visNaI;

  

  G4Tubs            *solidTarget;
  G4LogicalVolume   *logicTarget;
  G4VPhysicalVolume *physTarget;
  G4VisAttributes   *visTarget;


  


  void DefineMaterials();

  // Materials
  G4Material *worldMat, *EJ200, *CdZnTe, *Al, *LYSO, *NaI, *LeadOxide;
  G4Element *Lutetium, *Yttrium, *Oxygen, *Cerium, *Silicon;
  
  // World
  G4double xWorld, yWorld, zWorld;
  
  // Target
  G4double xTarget, yTarget, zTarget;
  G4double RTarget, LTarget;
  
  // Detectors
  G4int nDetectors;
  G4double ThetaSpanned;
  G4double ThetaEmptySpace;
  G4double ThetaStep;
  G4double ThetaRotation;
  G4double ThetaInitial;
  G4double RIn, ROut, LDet;

  G4Tubs *solidDet;
  G4LogicalVolume *logicDet;
  G4VPhysicalVolume *physDet;
  G4VisAttributes *visDet;
  

  // Shielding

  G4Tubs *solidShield;
  G4LogicalVolume *logicShield;
  G4VPhysicalVolume *physShield;
  G4VisAttributes *visShield;
  


};

#endif
  
