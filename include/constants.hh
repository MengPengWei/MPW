
#ifndef CONSTANTS_HH
#define CONSTANTS_HH 

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"


constexpr G4double worldSize=20*m;//世界尺寸50*cm
constexpr G4double standardSize = 15*cm;//标准尺寸10cm
constexpr G4double standardDistance= 10*cm;//标准距离10cm
constexpr G4double Length=2*m;     //管长度

constexpr G4double Sewage_Thickness =50*mm;      //废水半径           1
constexpr G4double Steel_Thickness=4*mm;         //管道半径
constexpr G4double Air_Thickness=5*mm;           //Air厚度
constexpr G4double Pb_Thickness=10*mm;//Pb厚度

constexpr G4int n_particle=1000;
constexpr G4double mixture_percent=0.05; 
#endif
