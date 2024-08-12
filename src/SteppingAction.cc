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
/// \file B1/src/SteppingAction.cc
/// \brief Implementation of the B1::SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "constants.hh"

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction,RunAction*runAction)
: fEventAction(eventAction),fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const auto detConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detConstruction->GetScoringVolume();
  }

  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
  // check if we are in scoring volume
  





G4int EventID,ParentID,TrackID,StepID;
  EventID=fEventAction->GetEventId();
  ParentID =step->GetTrack()->GetParentID();
  TrackID=step->GetTrack()->GetTrackID();
  StepID=step->GetTrack()->GetCurrentStepNumber();//得到当前步号   


   G4String ParticleName,ProcessName,VolumeName;
const G4VProcess*StepProcess=step->GetPostStepPoint()->GetProcessDefinedStep();
 ProcessName=StepProcess->GetProcessName();


  ParticleName=step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();

VolumeName=volume->GetName();



G4double VolumeMass=volume->GetMass();



  if (volume != fScoringVolume) return;
 if(ParticleName=="gamma")
 {

  G4double GlobeTime=step->GetTrack()->GetGlobalTime();
    G4double LocalTimeTime=step->GetTrack()->GetLocalTime();
  //G4cout<<" GlobeTime_track "<< G4BestUnit(GlobeTime,"Time") <<" LocalTime_track "<< G4BestUnit(LocalTimeTime,"Time") <<G4endl;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
\
  fEventAction->AddEdep(edepStep);
  //G4cout<<"edepStep"<<edepStep<<G4endl;


 }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}
