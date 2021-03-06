//#ifndef CONFIGUREEMCALRECOUTILS_C
//#define CONFIGUREEMCALRECOUTILS_C

///
/// \file ConfigureEMCALRecoUtils.C
/// \ingroup EMCALPerfAddTaskMacros
/// \brief Configuration of AliEMCALRecoUtils.
///
/// Example of configuration of AliEMCALRecoUtils. Called in different analysis configuration macros.
/// This class is used to calibrate/correct/accept EMCal clusters.
///
/// \author : Gustavo Conesa Balbastre <Gustavo.Conesa.Balbastre@cern.ch>, (LPSC-CNRS)
///

/*
#if !defined(__CINT__) || defined(__MAKECINT__) || !defined(__CLING__)

#include "AliEMCALRecoUtils.h"

#endif
*/

/// Main method
///
/// The input parameters:
/// \param reco: pointer to object to initialize in this macro.
/// \param bMC: Bool, indicates if data is MC.
/// \param bExotic: Bool, indicates if exotic clusters are removed.
/// \param bNonLin: Int, indicates if and which non linearity correction is applied on clusters.
/// \param bRecalE: Bool, indicates if energy recalibration is applied.
/// \param bBad: Bool, indicates if bad channels/clusters are removed.
/// \param bRecalT: Bool, indicates if time is calibrated.
/// \param debug: int debug level, print info on settings in the macro

///
void ConfigureEMCALRecoUtils(AliEMCALRecoUtils* reco,
                             Bool_t  bMC    = kFALSE,
                             Bool_t  bExotic= kTRUE,
                             Int_t   bNonLin= 0,
                             Bool_t  bRecalE= kTRUE,
                             Bool_t  bBad   = kTRUE,
                             Bool_t  bRecalT= kTRUE,
                             Int_t   debug  = -1)
{
  if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() - **** Start ***\n");
  
  // Exotic cells removal
  
  if(bExotic)
  {
    if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() - Remove exotics in EMCAL\n");
    reco->SwitchOnRejectExoticCell() ;
    reco->SwitchOnRejectExoticCluster(); 
    
//  reco->SetExoticCellDiffTimeCut(50);     // If |t cell max - t cell in cross| > 50 do not add its energy, avoid 
    reco->SetExoticCellFractionCut(0.97);   // 1-Ecross/Ecell > 0.97 -> out
    reco->SetExoticCellMinAmplitudeCut(4.); // 4 GeV    
  }  
  
  // Recalibration factors
  
  if(bRecalE && ! bMC)
  {
    if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() - Switch on energy recalibration in EMCAL\n");
    reco->SwitchOnRecalibration();
    reco->SwitchOnRunDepCorrection();    
  } 

  // Remove EMCAL hot channels 
  
  if(bBad)
  {
    if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() - Switch on bad channels removal in EMCAL\n");
    reco->SwitchOnBadChannelsRemoval();
    reco->SwitchOnDistToBadChannelRecalculation();
  }
 
  // *** Time recalibration settings ***
  
  if(bRecalT && ! bMC)
  {
    if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() - Switch on time recalibration in EMCAL\n");
    reco->SwitchOnTimeRecalibration();
    reco->SwitchOnL1PhaseInTimeRecalibration() ;
  }
    
  // Recalculate position with method
    
  reco->SetPositionAlgorithm(AliEMCALRecoUtils::kPosTowerGlobal);   

  // Non linearity

  switch( bNonLin ){
    case 0:
      if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() xxx DON'T SET Non linearity correction xxx\n");
      reco->SetNonLinearityFunction(AliEMCALRecoUtils::kNoCorrection);
      break;
    case 1:
      if( !bMC ) {
        if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() xxx SET Non linearity correction kBeamTestCorrected xxx\n");
        reco->SetNonLinearityFunction(AliEMCALRecoUtils::kBeamTestCorrected);
      } else {
        if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() xxx SET Non linearity correction kPi0MCv3 xxx\n");
        reco->SetNonLinearityFunction(AliEMCALRecoUtils::kPi0MC);
      }
      break;
    case 2:
      if( !bMC ) {
        if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() xxx SET Non linearity correction kBeamTestCorrected xxx\n");
        reco->SetNonLinearityFunction(AliEMCALRecoUtils::kBeamTestCorrectedv3);
      } else {
        if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() xxx SET Non linearity correction kPi0MCv3 xxx\n");
        reco->SetNonLinearityFunction(AliEMCALRecoUtils::kPi0MCv3);
      }
      break;
    case 3:
      if( !bMC ) {
        if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() xxx SET Non linearity correction kBeamTestCorrected xxx\n");
        reco->SetNonLinearityFunction(AliEMCALRecoUtils::kTestBeamShaper);
      } else {
        if ( debug > 0 ) printf("ConfigureEMCALRecoUtils() xxx SET Non linearity correction kPi0MCv3 xxx\n");
        reco->SetNonLinearityFunction(AliEMCALRecoUtils::kTestBeamFinalMC);
      }
      break;
  }
  
}

//#endif //CONFIGUREEMCALRECOUTILS_C

