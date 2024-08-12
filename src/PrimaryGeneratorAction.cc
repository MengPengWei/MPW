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
/// \file B1/src/PrimaryGeneratorAction.cc
/// \brief Implementation of the B1::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "constants.hh"


#include "G4GeneralParticleSource.hh"
#include "G4IonTable.hh"
namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
:G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
 fParticleGun  = new G4ParticleGun(1);

  fParticleGun->SetParticleEnergy(0*eV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{



  //fParticleGun->SetParticlePosition(G4ThreeVector(0,-worldSize/4,-worldSize/2));


  fParticleGun->GeneratePrimaryVertex(anEvent);



  // G4IonTable* ionTable = particleTable->GetIonTable();//！！！！获取离子列表
//   G4int Cs137_Z = 55; // 原子序数  
//   G4int Cs137_A = 137; // 质量数 
//   G4ParticleDefinition*ion_CS137= ionTable->GetIon(Cs137_Z, Cs137_A);


//   if (ion_CS137) {  
//     fParticleGun->SetParticleDefinition(ion_CS137);  
// } else {  
//     G4cout << "Cs-137 Ion not found!" << G4endl;  
// }  
//   G4int Cs134_Z = 55; // 原子序数  
//   G4int Cs134_A = 134; // 质量数 
//   G4ParticleDefinition*ion_Cs134= ionTable->GetIon(Cs134_Z, Cs134_A);
//   G4int Co60_Z = 27; // 原子序数  
//   G4int Co60_A = 60; // 质量数 
//   G4ParticleDefinition*ion_Co60= ionTable->GetIon(Co60_Z, Co60_A);
//   G4int Co58_Z = 27; // 原子序数  
//   G4int Co58_A = 58; // 质量数 
//   G4ParticleDefinition*ion_Co58= ionTable->GetIon(Co58_Z, Co58_A);
//   G4int Mn54_Z = 25; // 原子序数  
//   G4int Mn54_A = 54; // 质量数 
//   G4ParticleDefinition*ion_Mn54= ionTable->GetIon(Mn54_Z, Mn54_A);


// //比例   0.35：0.15：0.05：0.05：0.4
// //粒子数之比   0.35/137  ：0.15/134   ：0.05/60   ：0.05/58  ：0.4/54
// //约化   2554：1119：833：862：7407



//   fParticleGun->SetParticleDefinition(ion_CS137);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}


