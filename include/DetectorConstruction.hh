//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1/include/DetectorConstruction.hh
/// \brief Definition of the B1::DetectorConstruction class

#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Tubs.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

namespace B1
{

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
     DetectorConstruction() = default;
    ~DetectorConstruction() override = default;

    G4VPhysicalVolume* Construct() override;

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
 G4LogicalVolume* GetPb_AirVolume() const { return fPb_AirVolume; }

  protected:
    G4LogicalVolume* fScoringVolume = nullptr;
  G4LogicalVolume* fPb_AirVolume= nullptr;






  public:
//材料
 G4Material*Galactic,*SteelMat,*SewageMat,*Pb,*WaterMat,*AirMat ;


G4Box*solidWorld;
  G4Tubs*solidSteel,*solidPb,*solidSewage,
*solidPb_Air,*solidSteel_Air;
  G4LogicalVolume*logicWorld,
  *logicSteel,*logicPb,*logicSewage,
*logicPb_Air,*logicSteel_Air;


G4VPhysicalVolume*physWorld,
*physSteel,*physPb,*physSewage,
*physPb_Air,*physSteel_Air;
private:
void DefineMaterial();

void ConstructSteel();
void ConstructPb();
void ConstructSewage();
};


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
