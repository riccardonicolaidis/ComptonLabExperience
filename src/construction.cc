#include "construction.hh"
#include "myglobals.hh"
#include <iostream>
#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>

using namespace std;


MyDetectorConstruction::MyDetectorConstruction()
{
  DefineMaterials();  
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
  G4NistManager *nist = G4NistManager::Instance();

  EJ200     = nist -> FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  CdZnTe    = nist -> FindOrBuildMaterial("G4_CADMIUM_TELLURIDE");
  worldMat  = nist -> FindOrBuildMaterial("G4_Galactic");
  NaI       = nist -> FindOrBuildMaterial("G4_SODIUM_IODIDE");
  Al        = nist -> FindOrBuildMaterial("G4_Al");
  LeadOxide = nist -> FindOrBuildMaterial("G4_LEAD_OXIDE");

  G4double energy[2]        = {1.239841939*eV/0.9 , 1.239841939*eV/0.2};
  G4double rindexWorld[2]   = {1.0                , 1.0};
  G4double rindexEJ200[2]   = {1.58               , 1.58};
  G4double rindexCdZnTe[2]  = {3.09               , 3.09};
  G4double rindexLYSO[2]    = {1.8                , 1.8};

  G4MaterialPropertiesTable *mptWorld   = new G4MaterialPropertiesTable();
  G4MaterialPropertiesTable *mptEJ200   = new G4MaterialPropertiesTable();
  G4MaterialPropertiesTable *mptCdZnTe  = new G4MaterialPropertiesTable();
  G4MaterialPropertiesTable *mptLYSO    = new G4MaterialPropertiesTable();

  mptWorld -> AddProperty("RINDEX", energy, rindexWorld, 2);
  worldMat -> SetMaterialPropertiesTable(mptWorld);
  
  mptEJ200    -> AddProperty("RINDEX", energy, rindexEJ200, 2);
  EJ200       -> SetMaterialPropertiesTable(mptEJ200);

  mptCdZnTe   -> AddProperty("RINDEX", energy, rindexCdZnTe, 2);
  CdZnTe      -> SetMaterialPropertiesTable(mptCdZnTe);


  Lutetium = nist -> FindOrBuildElement("Lu");
  Yttrium  = nist -> FindOrBuildElement("Y");
  Oxygen   = nist -> FindOrBuildElement("O");
  Cerium   = nist -> FindOrBuildElement("Ce");
  Silicon  = nist -> FindOrBuildElement("Si");

  LYSO = new G4Material("LYSO",7.1*g/cm3,(G4int) 5);
  LYSO -> AddElement(Lutetium,71.43*perCent);
  LYSO -> AddElement(Yttrium,4.03*perCent);
  LYSO -> AddElement(Silicon,6.37*perCent);
  LYSO -> AddElement(Oxygen,18.14*perCent);
  LYSO -> AddElement(Cerium,0.02*perCent); 

  mptLYSO     -> AddProperty("RINDEX", energy, rindexLYSO, 2);
  LYSO        -> SetMaterialPropertiesTable(mptLYSO);

}






G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // .oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo
  // .oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo
  //
  //        NUMERICAL DATA - PARAMETRIZATION
  //
  // .oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo
  // .oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo
  
  // World dimensions

  xWorld = 10 *m;
  yWorld = 10 *m;
  zWorld = 10 *m;
  

  solidWorld = new G4Box("solidWorld",xWorld*0.5, yWorld*0.5, zWorld*0.5);  
  logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
  visWorld   = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  visWorld   -> SetVisibility(false);
  logicWorld -> SetVisAttributes(visWorld);
  physWorld  = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
    

  
  // Definition of the target for the Compton Scattering

  xTarget = 0 *cm;
  yTarget = 0 *cm;
  zTarget = 0 *cm;

  RTarget = 1.5 *cm;
  LTarget = 1 *cm;

  solidTarget = new G4Tubs("solidTarget", 0, RTarget, LTarget*0.5, 0, 360*deg);
  logicTarget = new G4LogicalVolume(solidTarget, NaI, "logicTarget");
  visTarget   = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  visTarget   -> SetVisibility(true);
  logicTarget -> SetVisAttributes(visTarget);
  physTarget  = new G4PVPlacement(0, G4ThreeVector(xTarget,yTarget,zTarget), logicTarget, "physTarget", logicWorld, false, 0, true);


  // Detectors: We want to define an array of detectors with a given spacing in angle
  
  nDetectors = NDetectors;
  ThetaSpanned = 350 * deg;
  ThetaEmptySpace = 1 * deg;
  ThetaStep = (ThetaSpanned - (nDetectors)*ThetaEmptySpace)/nDetectors;
  ThetaRotation = ThetaSpanned/nDetectors;
  ThetaInitial = ThetaSpanned/2. - ThetaEmptySpace/2. - ThetaStep;
  
  RIn = 30 *cm;
  ROut = 1 *m;
  LDet = 20 *cm;

  solidDet = new G4Tubs("solidDet", RIn, ROut, LDet*0.5, ThetaInitial, ThetaStep);
  logicDet = new G4LogicalVolume(solidDet, CdZnTe, "logicDet");
  visDet   = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  visDet   -> SetVisibility(true);
  logicDet -> SetVisAttributes(visDet);

  solidShield = new G4Tubs("solidShield", 30*cm, ROut ,LDet/2., ThetaInitial - 3*ThetaEmptySpace/4, ThetaEmptySpace/2);
  logicShield = new G4LogicalVolume(solidShield, LeadOxide, "logicShield");
  
  
  fstream file;
  file.open("../DetectorAngles.csv", ios::out);

  G4double Theta0 = (ThetaSpanned - ThetaEmptySpace - ThetaStep)/2.;


  for (G4int i = 0; i < nDetectors+1; i++)
    {
      G4double xDet = 0 *cm;
      G4double yDet = 0 *cm;
      G4double zDet = 0 *cm;
      G4double ThetaDet = ThetaInitial - i*(ThetaStep + ThetaEmptySpace);
      G4double RotationDet = ThetaRotation*i;
      G4RotationMatrix *rotDet = new G4RotationMatrix();
      rotDet -> rotateZ(RotationDet);
      G4ThreeVector posDet(xDet,yDet,zDet);
      G4String nameDet = "physDet";
      G4String numberDet = std::to_string(i);
      nameDet += numberDet;
      if(i<nDetectors)
      {
        new G4PVPlacement(rotDet, posDet, logicDet, nameDet, logicWorld, false, i, true);
        new G4PVPlacement(rotDet, posDet, logicShield, "physShield", logicWorld, false, i, true);
        file << i << "\t" << (Theta0 - i*ThetaRotation)/deg << endl;
      }
      else
      {
        //new G4PVPlacement(rotDet, posDet, logicShield, "physShield", logicWorld, false, i, true);
      }
      
    
      
    }

  file.close();
  //new G4PVPlacement(0, G4ThreeVector(0,0,0), logicDet, "physDet", logicWorld, false, 0, true);

  // Objects for the transformations 
  // G4RotationMatrix Identity;  
  // G4ThreeVector position1;
  // G4Transform3D tr1;

  // Example of transformation 
  // Identity = G4RotationMatrix();
  // position1 = G4ThreeVector(0.,0.,(TkDrilledVeto0+LzDrilledVeto1)/2. -TkCompenetration);
  // tr1 = G4Transform3D(Identity, position1);
  

  /* -------------------------------------------------------------------------- */
  /*                           DEFINITION OF THE FRAME                          */
  /* -------------------------------------------------------------------------- */

  
  G4RotationMatrix MyRotationMatrix = G4RotationMatrix();
  // G4ThreeVector MyTranslationVector = G4ThreeVector(-1.,1.,0.);
  // RotationConnector.rotate(-90.*deg, RotationAxisConnector);
  // RotationConnector.invert();
  
  //G4ThreeVector MyTranslationVector = G4ThreeVector(0., 0., -TkAlDet*0.5 - TkBottom*0.5 +100*um);
  //G4Transform3D TransformConnector = G4Transform3D(MyRotationMatrix, MyTranslationVector);
  //solidFrame = new G4UnionSolid("solidFrame", solidFrameCircle, solidBottomFrame, TransformConnector);

  

  //physSiDetThin   = new G4PVPlacement(0, G4ThreeVector(xThin,yThin,zThin) , logicSiDetThin, "physSiDetThin", logicWorld, false, 0, true);
  //physSiDetThinBarrier   = new G4PVPlacement(0, G4ThreeVector(xThin,yThin,zThin+TkThin/2.+2*um) , logicSiDetThinBarrier, "physSiDetThinBarrier", logicWorld, false, 0, true);
  //physFrame   = new G4PVPlacement(0, G4ThreeVector(xThin,yThin,zThin-2*mm) , logicFrame, "physFrameThin", logicWorld, false, 0, true);
    
  return physWorld;  
}


void MyDetectorConstruction::ConstructSDandField()
{
  // Thin Silicon 100 um or 300 um 
  G4String NaITargetSD = "NaITargetSD";
  MySensitiveDetector *aNaITargetSD = new MySensitiveDetector(NaITargetSD, "NaITargetSD");
  G4SDManager::GetSDMpointer()->AddNewDetector(aNaITargetSD);
  logicTarget->SetSensitiveDetector(aNaITargetSD);
  
  // CdZnTe detectors
  G4String CdZnTeSD = "CdZnTeSD";
  MySensitiveDetector *aCdZnTeSD = new MySensitiveDetector(CdZnTeSD, "CdZnTeSD");
  G4SDManager::GetSDMpointer()->AddNewDetector(aCdZnTeSD);
  logicDet->SetSensitiveDetector(aCdZnTeSD);
  

  //MySensitiveDetector* aThinDetectorSD = new MySensitiveDetector(ThinDetectorSD, "SiThin");
  //G4SDManager::GetSDMpointer()->AddNewDetector(aThinDetectorSD);
  //SetSensitiveDetector( logicSiDetThin, aThinDetectorSD );

  /*
  G4String LYSOSD = "LYSO";
  MySensitiveDetector* aLYSOSD = new MySensitiveDetector(LYSOSD, "LYSO");
  G4SDManager::GetSDMpointer()->AddNewDetector(aLYSOSD);
  SetSensitiveDetector( logicLYSO, aLYSOSD ); 

  G4String NaISD = "NaI";
  MySensitiveDetector* aNaISD = new MySensitiveDetector(NaISD, "NaI");
  G4SDManager::GetSDMpointer()->AddNewDetector(aNaISD);
  SetSensitiveDetector( logicNaI, aNaISD );
  */


  
}


