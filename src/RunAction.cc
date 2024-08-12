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
/// \file B1/src/RunAction.cc
/// \brief Implementation of the B1::RunAction class

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
// #include "Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "constants.hh"
namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{
  // add new units for dose
  //
  const G4double mGy = 1.e-3*gray;
  const G4double uGy = 1.e-6*gray;
  const G4double nGy  = 1.e-9*gray;
  const G4double pGy  = 1.e-12*gray;
  const G4double fGy  = 1.e-15*gray;
  const G4double aGy  = 1.e-18*gray;


  new G4UnitDefinition("mGy", "mGy" , "Dose", mGy);
  new G4UnitDefinition("uGy", "uGy" , "Dose", uGy);
  new G4UnitDefinition("nGy" , "nGy"  , "Dose", nGy);
  new G4UnitDefinition("pGy" , "pGy"  , "Dose", pGy);
  new G4UnitDefinition("fGy" , "fGy"  , "Dose", fGy);
  new G4UnitDefinition("aGy" , "aGy"  , "Dose", aGy);


  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fEdep2);









}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
runTimer.Start();





}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Compute dose = total energy deposit in a run and its variance
  //
  G4double edep  = fEdep.GetValue();
  G4double edep2 = fEdep2.GetValue();

  G4double rms = edep2 - edep*edep/nofEvents;
  if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;

  const auto detConstruction = static_cast<const DetectorConstruction*>(
    G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double mass = detConstruction->GetScoringVolume()->GetMass();
  G4String SoreName=detConstruction->GetScoringVolume()->GetName();
  G4double dose = edep/mass;
  G4double rmsDose = rms/mass;
 // G4int Number_Event=run->GetNumberOfEvent();

  //G4double GlobalTime=

    // Calculate dose rate in dose/hour  
   

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const auto generatorAction = static_cast<const PrimaryGeneratorAction*>(
    G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition,gunName,gunName1;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
     gunName=particleGun->GetParticleDefinition()->GetParticleName();
  }

  // Print
  //
      std::fstream file;
    file.open("Analysis.txt",std::ios::out|std::ios::app);
  if (IsMaster()) {
    // G4cout
    //  << G4endl
    //  << "--------------------End of Global Run-----------------------";


  file
  //<<" Ion:"<<gunName
  <<"  Event number:"<< nofEvents 
  << "  gun number:" <<n_particle
  <<"  volume:"<< SoreName
  //<<" Number_Event:"<<Number_Event
  <<"  Pb_Thickness:"<<G4BestUnit(Pb_Thickness,"Length") 
  <<"  edep:"<< G4BestUnit(edep,"Energy") 
  <<"  mass:" <<G4BestUnit(mass,"Mass") 
  <<"  dose:"<<G4BestUnit(dose,"Dose") 
  <<G4endl;
  file.close();
  }
  // else {
  //   G4cout
  //    << G4endl
  //    << "--------------------End of Local Run------------------------";
  //    file  <<" Ion:"<<gunName
  //    <<G4endl;
  // }
// 
  // G4cout
  //    << G4endl
  //    << " The run consists of " << nofEvents << " "<< runCondition
  //    << G4endl
  //    <<"edep"
  //    <<edep
  //    <<G4endl
  //    << " Cumulated dose per run, in  "
  //    <<SoreName 
  //    <<" volume :"
  //    << G4BestUnit(dose,"Dose") << " rms = " << G4BestUnit(rmsDose,"Dose")
  //    << G4endl
  //    << "------------------------------------------------------------"
  //    << G4endl
  //    << G4endl;






    // G4AnalysisManager*analysisManager=G4AnalysisManager::Instance();

    // analysisManager->Write();
    // analysisManager->CloseFile(false);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
  fEdep2 += edep*edep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
