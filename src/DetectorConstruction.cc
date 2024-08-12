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
/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "constants.hh"
namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  void DetectorConstruction::DefineMaterial()//定义材料
  {

   G4NistManager*nistManager=G4NistManager::Instance();
  //世界真空
  Galactic=nistManager->FindOrBuildMaterial("G4_Galactic");

AirMat = nistManager->FindOrBuildMaterial("G4_AIR"); // 获取空气材料 

// 定义水的材料  
WaterMat = nistManager->FindOrBuildMaterial("G4_WATER"); // 获取水材料 

// // 定义污水内的各种同位素  
// G4Isotope* Cs137 = new G4Isotope("Cs137", 55, 137, 132.905*g/mole);  
// G4Isotope* Cs134 = new G4Isotope("Cs134", 55, 134, 133.906*g/mole);  
// G4Isotope* Co58 = new G4Isotope("Co58", 27, 58, 57.933*g/mole);  
// G4Isotope* Co60 = new G4Isotope("Co60", 27, 60, 59.933*g/mole);  
// G4Isotope* Mn54 = new G4Isotope("Mn54", 25, 54, 54.938*g/mole);  

//     G4Element* Cs = new G4Element("Cesium", "Cs", 2);  
//     Cs->AddIsotope(Cs134, 0.3 );  
//     Cs->AddIsotope(Cs137, 0.7);  

//     G4Element* Co = new G4Element("Cobalt", "Co", 2);  
//     Co->AddIsotope(Co58,0.5);  
//     Co->AddIsotope(Co60, 0.5);  
    
//     G4Element* Mn = new G4Element("Manganese", "Mn", 1);  
//     Mn->AddIsotope(Mn54, 1);



// 创建污水材料  
// SewageMat  = new G4Material("Sewage", 1.0 * g/cm3, 4); // 假定污水的平均密度为1 g/cm^3  


//    SewageMat->AddMaterial(WaterMat, (1-mixture_percent)); // 水 95%  
//     SewageMat->AddElement(Cs, 0.5* mixture_percent); // 假设根据需求添加  
//     SewageMat->AddElement(Co, 0.1* mixture_percent);  
//     SewageMat->AddElement(Mn, 0.4* mixture_percent); 


// // 定义不锈钢材料  
 SteelMat = new G4Material("StainlessSteel", 8.0 * g/cm3, 3); // 假设不锈钢密度为 8 g/cm³  

    
    // 创建元素  
    G4Element* Fe = new G4Element("Iron", "Fe", 26, 55.845 * g / mole);  
    G4Element* Ni = new G4Element("Nickel", "Ni", 28, 58.693 * g / mole);  
    G4Element* Cr = new G4Element("Chromium", "Cr", 24, 51.9961 * g / mole);  
    
    // 添加元素  
    SteelMat->AddElement(Fe, 0.7);  // 70% 铁  
    SteelMat->AddElement(Ni, 0.2);   // 20% 镍  
    SteelMat->AddElement(Cr, 0.1);   // 10% 铬 


// 定义铅材料  
Pb =  nistManager->FindOrBuildMaterial("G4_Pb"); // 铅的密度为 11.34 g/cm³  

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  if (!Galactic || !WaterMat||!SteelMat||! Pb||!AirMat)
  {
    G4ExceptionDescription msg;
    msg << "Cannot retrieve materials already defined."; 
    G4Exception("Construction::DefineVolumes()",
      "MyCode0001", FatalException, msg);


  }
  }


//结构
void  DetectorConstruction:: ConstructSewage()//污水
{

    solidSewage
    = new  G4Tubs( "Sewage",
                 0,
                 Sewage_Thickness,
                 Length,
                  0,
                 2*CLHEP::pi );
               
   logicSewage
    = new G4LogicalVolume(
                 solidSewage,           // its solid
                 WaterMat,          // its material
                 "Sewage");         // its name
                                   
   physSewage
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0.,0,0),  // at (0,0,0)
                 logicSewage,          // its logical volume                         
                 "Sewage",        // its name
                 logicWorld,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 true);  // checking overlaps 


}
void DetectorConstruction:: ConstructSteel()//不锈钢
{

 auto SMin=Sewage_Thickness;
 auto SMax=SMin+Steel_Thickness;
    solidSteel
    = new  G4Tubs( "Steel",
                SMin,
                SMax,
                Length,
                0,
                2*CLHEP::pi );      //0-2pi

    logicSteel
    = new G4LogicalVolume(
                 solidSteel,           // its solid
                 SteelMat,          // its material
                 "Steel");         // its name
  physSteel
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0.,0.,0),  // at (0,0,0)
                 logicSteel,          // its logical volume                         
                 "Steel",        // its name
                 logicWorld,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 true);  // checking overlaps 

auto AMin=SMax;
auto AMax=SMax+Air_Thickness;
   solidSteel_Air
    = new  G4Tubs( "Steel_Air",
                AMin,
                AMax,
                Length,
                  0,
                2*CLHEP::pi );
              
 logicSteel_Air
    = new G4LogicalVolume(
                 solidSteel_Air,           // its solid
                 AirMat,          // its material
                 "Steel_Air");         // its name
                                
  physSteel_Air
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0.,0,0),  // at (0,0,0)
                 logicSteel_Air,          // its logical volume                         
                 "Steel_Air",        // its name
                 logicWorld,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 true);  // checking overlaps 


}
 void DetectorConstruction:: ConstructPb()//铅层
 {

   
  auto PbRMin=Sewage_Thickness+Steel_Thickness+Air_Thickness;
  auto PbRMax=PbRMin+Pb_Thickness;
    solidPb
    = new  G4Tubs( "Pb",
                 PbRMin,
                 PbRMax,
                Length,
                  0,
                2*CLHEP::pi );
               
   logicPb
    = new G4LogicalVolume(
                 solidPb,           // its solid
                 Pb,          // its material
                 "Pb");         // its name
                                   
   physPb
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0.,0,0),  // at (0,0,0)
                 logicPb,          // its logical volume                         
                 "Pb",        // its name
                 logicWorld,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 true);  // checking overlaps 

//
auto AMin=PbRMax;
auto AMax=PbRMax+Air_Thickness;
  solidPb_Air
    = new  G4Tubs( "Pb_Air",
                AMin,
                AMax,
                Length,
                  0,
                2*CLHEP::pi );
              
  logicPb_Air
    = new G4LogicalVolume(
                 solidPb_Air,           // its solid
                 AirMat,          // its material
                 "Pb_Air");         // its name
    physPb_Air
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(0.,0,0),  // at (0,0,0)
                 logicPb_Air,          // its logical volume                         
                 "Pb_Air",        // its name
                 logicWorld,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 true);  // checking overlaps 
 }


G4VPhysicalVolume* DetectorConstruction::Construct()
{
 
  DefineMaterial();

  solidWorld=new G4Box("World",worldSize/2,worldSize/2,worldSize/2);
      logicWorld=new G4LogicalVolume(solidWorld,Galactic,"World");

      physWorld=
       new G4PVPlacement(0,
                          G4ThreeVector(0,0,0),
                          logicWorld,
                          "World",
                          0,
                          false,//no boolean operation
                          0,
                          true
       );
    

ConstructSteel();
ConstructPb();
ConstructSewage();



  //logicSewage    logicSteel_Air  logicPb logicPb_Air
fScoringVolume = logicPb_Air;//铅层外的剂量
 //  fPb_AirVolume = logicSteel_Air;
  


  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
