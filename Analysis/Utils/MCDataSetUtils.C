#define MCDataSetUtils_cxx
//////////////////////////////////////////////////////////////////////
// 
// Author   : Atlas LPNHE Paris
// Creation : 01/10/2015
// Purpose  : Utilities to handle MC datasets
// Updated  :
//////////////////////////////////////////////////////////////////////

#include "MCDataSetUtils.h"

#include <TStyle.h>
#include <TCanvas.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h> 

ClassImp(MCDataSetUtils);

// Constructor
MCDataSetUtils::MCDataSetUtils() 
{
}

// ================================================================
// DESTRUCTOR:
MCDataSetUtils::~MCDataSetUtils()
{ 
} 

// =========================================================
float MCDataSetUtils::XSection(int mcChannelNumber)
{
  float xs = 0.;
  float kf = 1.;
  bool isTOPQ1 = true;
  // ttbar samples
  if (mcChannelNumber==410000) { xs = 377.9932; kf = 1.1949; }
  if (mcChannelNumber==410001) { xs = 377.9932; kf = 1.1949; }
  if (mcChannelNumber==410002) { xs = 377.9932; kf = 1.1949; }
  if (mcChannelNumber==410003) { xs = 377.3090; kf = 1.1970; }
  if (mcChannelNumber==410004) { xs = 378.7006; kf = 1.1926; }
  
  if (mcChannelNumber==410006) { xs = 378.7169; kf = 1.1926; }
  if (mcChannelNumber==410007) { xs = 317.3591; kf = 1.1977; }		
  if (mcChannelNumber==410008) { xs = 317.3591; kf = 1.1977; }

  // Sherpa samples
  if (mcChannelNumber==410021) { xs = 78.126; kf = 1.17; }
  if (mcChannelNumber==410022) { xs = 165.95; kf = 1.17; }
  if (mcChannelNumber==410023) { xs = 159.18; kf = 1.17; }
  if (mcChannelNumber==410024) { xs = 309.27; kf = 1.17; }
  
  // b-filter
  if (mcChannelNumber==410120) { xs = 24.1063; kf = 1.1949; }
  if (mcChannelNumber==410121) { xs = 4.4954;  kf = 1.1949; }

  // ttV, ttWW 
  if (mcChannelNumber==410066) { xs = 0.17656;   kf = 1.247; }  // ttW,0j
  if (mcChannelNumber==410067) { xs = 0.14062;   kf = 1.247; }  // ttW,1j
  if (mcChannelNumber==410068) { xs = 0.1368;    kf = 1.247; }  // ttW,2j
  if (mcChannelNumber==410111) { xs = 0.0088155; kf = 1.2; }    // ttee,0j
  if (mcChannelNumber==410112) { xs = 0.01438;   kf = 1.2; }    // ttee,1j
  if (mcChannelNumber==410113) { xs = 0.0088422; kf = 1.2; }    // ttmumu,0j
  if (mcChannelNumber==410114) { xs = 0.014375;  kf = 1.2; }    // ttmumu,1j
  if (mcChannelNumber==410115) { xs = 0.0090148; kf = 1.2; }    // tttautau,0j
  if (mcChannelNumber==410116) { xs = 0.014636;  kf = 1.2; }    // tttautau,1j
  if (mcChannelNumber==410069) { xs = 0.018103;  kf = 1.0; }    // ttZ on-shell only
  if (mcChannelNumber==410070) { xs = 0.030629;  kf = 1.0; }    // ttZ on-shell only
  if (mcChannelNumber==410073) { xs = 0.11122;   kf = 1.0; }    // ttZ, only for Z->nunu
  if (mcChannelNumber==410074) { xs = 0.095466;  kf = 1.0; }    // ttZ, only for Z->nunu
  if (mcChannelNumber==410075) { xs = 0.10512;   kf = 1.0; }    // ttZ, only for Z->nunu
  if (mcChannelNumber==410081) { xs = 0.0080975; kf = 1.2231; } // ttWW

    // 4 tops, 3 tops SM
  if (mcChannelNumber==410080) { xs = 0.0091622; kf = 1.0042; }
  if (mcChannelNumber==304014) { xs = 0.0016398; kf = 1.0; }

  // single top
  if (mcChannelNumber==410011) { xs = 43.739; kf = 1.0094; }
  if (mcChannelNumber==410012) { xs = 25.778; kf = 1.0193; }
  if (mcChannelNumber==410013) { xs = 34.009; kf = 1.054; }
  if (mcChannelNumber==410014) { xs = 33.989; kf = 1.054; }
  if (mcChannelNumber==410015) { xs = 3.5835; kf = 1.054; }
  if (mcChannelNumber==410016) { xs = 3.5814; kf = 1.054; }
  if (mcChannelNumber==410025) { xs = 2.0517; kf = 1.6806; }
  if (mcChannelNumber==410026) { xs = 1.2615; kf = 1.7088; }
  
  // Single Top
  // taken from CentralMC15ProductionList
  if (mcChannelNumber==410065) { xs = 3.409;   kf = 1.054; }
  if (mcChannelNumber==410064) { xs = 3.4133;  kf = 1.054; }
  if (mcChannelNumber==410062) { xs = 32.384;  kf = 1.054; }   
  if (mcChannelNumber==410063) { xs = 32.357;  kf = 1.054; }
  if (mcChannelNumber==410099) { xs = 34.917;  kf = 1.027; }
  if (mcChannelNumber==410100) { xs = 33.407;  kf = 1.073; }
  if (mcChannelNumber==410101) { xs = 34.893;  kf = 1.027; }
  if (mcChannelNumber==410102) { xs = 33.388;  kf = 1.073; }
  if (mcChannelNumber==410103) { xs = 3.679;   kf = 1.027; }
  if (mcChannelNumber==410104) { xs = 3.5201;  kf = 1.073; }
  if (mcChannelNumber==410105) { xs = 3.6767;  kf = 1.027; }
  if (mcChannelNumber==410106) { xs = 3.5181;  kf = 1.073; }
  if (mcChannelNumber==410050) { xs = 0.24013; kf = 1.0; }

  // Powheg inclusive W 
  if (mcChannelNumber==361100) { xs = 11306.0; kf = 1.01724; }
  if (mcChannelNumber==361101) { xs = 11306.0; kf = 1.01724; }
  if (mcChannelNumber==361102) { xs = 11306.0; kf = 1.01724; }
  if (mcChannelNumber==361103) { xs = 8282.6;  kf = 1.03579; }
  if (mcChannelNumber==361104) { xs = 8282.6;  kf = 1.03579; }
  if (mcChannelNumber==361105) { xs = 8282.6;  kf = 1.03579; }
  
  // Powheg inclusive Z
  if (mcChannelNumber==361106) { xs = 1901.2000; kf = 1.026; }
  if (mcChannelNumber==361107) { xs = 1901.2000; kf = 1.026; }
  if (mcChannelNumber==361108) { xs = 1901.2000; kf = 1.026; }
  
  // Sherpa W NLO xsec from Sherpa
  if (mcChannelNumber==361300) { xs = 18957.3;     kf = 0.90824; }
  if (mcChannelNumber==361301) { xs = 1053.77;     kf = 0.90824; }
  if (mcChannelNumber==361302) { xs = 1278.94;     kf = 0.90824; }
  if (mcChannelNumber==361303) { xs = 461.341;     kf = 0.90824; }
  if (mcChannelNumber==361304) { xs = 111.847;     kf = 0.90824; }
  if (mcChannelNumber==361305) { xs = 61.1585;     kf = 0.90824; }
  if (mcChannelNumber==361306) { xs = 61.4394;     kf = 0.90824; }
  if (mcChannelNumber==361307) { xs = 18.5252;     kf = 0.90824; }
  if (mcChannelNumber==361308) { xs = 10.1085;     kf = 0.90824; }

  // for 
  if (isTOPQ1) {
    if (mcChannelNumber==361309) { xs = 4.26261;     kf = 0.90824; }
    if (mcChannelNumber==361310) { xs = 1.46812;     kf = 0.90824; }
    if (mcChannelNumber==361311) { xs = 0.857316;    kf = 0.90824; }
    if (mcChannelNumber==361312) { xs = 0.264652;    kf = 0.90824; }
    if (mcChannelNumber==361313) { xs = 0.0970859;   kf = 0.90824; }
    if (mcChannelNumber==361314) { xs = 0.0616011;   kf = 0.90824; }
    if (mcChannelNumber==361315) { xs = 0.0444194;   kf = 0.90824; }
    if (mcChannelNumber==361316) { xs = 0.0206127;   kf = 0.90824; }
    if (mcChannelNumber==361317) { xs = 0.0130291;   kf = 0.90824; }
    if (mcChannelNumber==361318) { xs = 0.00734014;  kf = 0.90824; }
    if (mcChannelNumber==361319) { xs = 0.00254079;  kf = 0.90824; }
    if (mcChannelNumber==361320) { xs = 0.00161246;  kf = 0.90824; }
    if (mcChannelNumber==361321) { xs = 2.17153e-05; kf = 0.90824; }
    if (mcChannelNumber==361322) { xs = 1.24252e-05; kf = 0.90824; }
    if (mcChannelNumber==361323) { xs = 8.67045e-06; kf = 0.90824; }
  } else {
    // for e4133
    if (mcChannelNumber==361309) { xs = 3.743021;    kf = 0.9083; }
    if (mcChannelNumber==361310) { xs = 1.2700869;   kf = 0.9083; }
    if (mcChannelNumber==361311) { xs = 0.75515579;  kf = 0.9083; }
    if (mcChannelNumber==361312) { xs = 0.219385739; kf = 0.9083; }
    if (mcChannelNumber==361313) { xs = 0.08280019;  kf = 0.9083; }
    if (mcChannelNumber==361314) { xs = 0.05545526;  kf = 0.9083; }
    if (mcChannelNumber==361315) { xs = 0.038058823; kf = 0.9083; }
    if (mcChannelNumber==361316) { xs = 0.013239975; kf = 0.9083; }
    if (mcChannelNumber==361317) { xs = 0.009862805; kf = 0.9083; }
    if (mcChannelNumber==361318) { xs = 0.0040615301;kf = 0.9083; }
    if (mcChannelNumber==361319) { xs = 0.0015777124;kf = 0.9083; }
    if (mcChannelNumber==361320) { xs = 0.0011266528;kf = 0.9083; }
    if (mcChannelNumber==361321) { xs = 1.5969954e-05; kf = 0.9083; }
    if (mcChannelNumber==361322) { xs = 6.93999e-06; kf = 0.9083; }
    if (mcChannelNumber==361323) { xs = 4.911172e-06; kf = 0.9083; }
  }

  if (mcChannelNumber==361324) { xs = 19092.6;     kf = 0.90824; }
  if (mcChannelNumber==361325) { xs = 1012.58;     kf = 0.90824; }
  if (mcChannelNumber==361326) { xs = 1275.58;     kf = 0.90824; }
  if (mcChannelNumber==361327) { xs = 462.582;     kf = 0.90824; }
  if (mcChannelNumber==361328) { xs = 110.649;     kf = 0.90824; }
  if (mcChannelNumber==361329) { xs = 61.1091;     kf = 0.90824; }
  if (mcChannelNumber==361330) { xs = 61.5886;     kf = 0.90824; }
  if (mcChannelNumber==361331) { xs = 18.3497;     kf = 0.90824; }
  if (mcChannelNumber==361332) { xs = 10.1626;     kf = 0.90824; }

  if (isTOPQ1) {
    if (mcChannelNumber==361333) { xs = 4.25566;     kf = 0.90824; }
    if (mcChannelNumber==361334) { xs = 1.44075;     kf = 0.90824; }
    if (mcChannelNumber==361335) { xs = 0.861333;    kf = 0.90824; }
    if (mcChannelNumber==361336) { xs = 0.26097;     kf = 0.90824; }
    if (mcChannelNumber==361337) { xs = 0.0992602;   kf = 0.90824; }
    if (mcChannelNumber==361338) { xs = 0.0669962;   kf = 0.90824; }
    if (mcChannelNumber==361339) { xs = 0.048537;    kf = 0.90824; }
    if (mcChannelNumber==361340) { xs = 0.0169408;   kf = 0.90824; }
    if (mcChannelNumber==361341) { xs = 0.0135496;   kf = 0.90824; }
    if (mcChannelNumber==361342) { xs = 0.00638427;  kf = 0.90824; }
    if (mcChannelNumber==361343) { xs = 0.00228772;  kf = 0.90824; }
    if (mcChannelNumber==361344) { xs = 0.00182928;  kf = 0.90824; }
    if (mcChannelNumber==361345) { xs = 2.72241e-05; kf = 0.90824; }
    if (mcChannelNumber==361346) { xs = 1.55984e-05; kf = 0.90824; }
    if (mcChannelNumber==361347) { xs = 6.84621e-06; kf = 0.90824; }
  } else {
    if (mcChannelNumber==361333) { xs = 3.743021;    kf = 0.9083; }
    if (mcChannelNumber==361334) { xs = 1.270086;    kf = 0.9083; }
    if (mcChannelNumber==361335) { xs = 0.7551557;   kf = 0.9083; }
    if (mcChannelNumber==361336) { xs = 0.21938573;  kf = 0.9083; }
    if (mcChannelNumber==361337) { xs = 0.08280019;  kf = 0.9083; }
    if (mcChannelNumber==361338) { xs = 0.05545525;  kf = 0.9083; }
    if (mcChannelNumber==361339) { xs = 0.038058823; kf = 0.9083; }
    if (mcChannelNumber==361340) { xs = 0.01323997;  kf = 0.9083; }
    if (mcChannelNumber==361341) { xs = 0.009862805; kf = 0.9083; }
    if (mcChannelNumber==361342) { xs = 0.000406153; kf = 0.9083; }
    if (mcChannelNumber==361343) { xs = 0.001577712; kf = 0.9083; }
    if (mcChannelNumber==361344) { xs = 0.0011266528;kf = 0.9083; }
    if (mcChannelNumber==361345) { xs = 1.5969954e-05; kf = 0.9083; }
    if (mcChannelNumber==361346) { xs = 6.93999e-06; kf = 0.9083; }
    if (mcChannelNumber==361347) { xs = 4.911172e-06; kf = 0.9083; }
  }

  if (mcChannelNumber==361348) { xs = 19063.7;     kf = 0.90824; }
  if (mcChannelNumber==361349) { xs = 1041.24;     kf = 0.90824; }
  if (mcChannelNumber==361350) { xs = 1276.56;     kf = 0.90824; }
  if (mcChannelNumber==361351) { xs = 457.502;     kf = 0.90824; }
  if (mcChannelNumber==361352) { xs = 112.004;     kf = 0.90824; }
  if (mcChannelNumber==361353) { xs = 60.441;      kf = 0.90824; }
  if (mcChannelNumber==361354) { xs = 61.7018;     kf = 0.90824; }
  if (mcChannelNumber==361355) { xs = 18.4259;     kf = 0.90824; }
  if (mcChannelNumber==361356) { xs = 10.177;      kf = 0.90824; }

  if (isTOPQ1) {
    if (mcChannelNumber==361357) { xs = 4.13792;     kf = 0.90824; }
    if (mcChannelNumber==361358) { xs = 1.47517;     kf = 0.90824; }
    if (mcChannelNumber==361359) { xs = 0.860674;    kf = 0.90824; }
    if (mcChannelNumber==361360) { xs = 0.260783;    kf = 0.90824; }
    if (mcChannelNumber==361361) { xs = 0.09558;     kf = 0.90824; }
    if (mcChannelNumber==361362) { xs = 0.0659577;   kf = 0.90824; }
    if (mcChannelNumber==361363) { xs = 0.049746;    kf = 0.90824; }
    if (mcChannelNumber==361364) { xs = 0.0172089;   kf = 0.90824; }
    if (mcChannelNumber==361365) { xs = 0.0125405;   kf = 0.90824; }
    if (mcChannelNumber==361366) { xs = 0.00644265;  kf = 0.90824; }
    if (mcChannelNumber==361367) { xs = 0.00241759;  kf = 0.90824; }
    if (mcChannelNumber==361368) { xs = 0.00198589;  kf = 0.90824; }
    if (mcChannelNumber==361369) { xs = 2.65271e-05; kf = 0.90824; }
    if (mcChannelNumber==361370) { xs = 1.35842e-05; kf = 0.90824; }
    if (mcChannelNumber==361371) { xs = 8.49481e-06; kf = 0.90824; }
  } else {
    if (mcChannelNumber==361357) { xs = 3.743021;    kf = 0.9083; }
    if (mcChannelNumber==361358) { xs = 1.270086;    kf = 0.9083; }
    if (mcChannelNumber==361359) { xs = 0.7551557;   kf = 0.9083; }
    if (mcChannelNumber==361360) { xs = 0.2193857;   kf = 0.9083; }
    if (mcChannelNumber==361361) { xs = 0.08280019;  kf = 0.9083; }
    if (mcChannelNumber==361362) { xs = 0.05545525;  kf = 0.9083; }
    if (mcChannelNumber==361363) { xs = 0.03805882;  kf = 0.9083; }
    if (mcChannelNumber==361364) { xs = 0.01323997;  kf = 0.9083; }
    if (mcChannelNumber==361365) { xs = 0.009862805; kf = 0.9083; }
    if (mcChannelNumber==361366) { xs = 0.000406153; kf = 0.9083; }
    if (mcChannelNumber==361367) { xs = 0.001577712; kf = 0.9083; }
    if (mcChannelNumber==361368) { xs = 0.0011266527;kf = 0.9083; }
    if (mcChannelNumber==361369) { xs = 1.5969954e-05; kf = 0.9083; }
    if (mcChannelNumber==361370) { xs = 6.93999e-06; kf = 0.9083; }
    if (mcChannelNumber==361371) { xs = 4.911172e-06; kf = 0.9083; }
  } 

  // W+jets Madgraph+Py8
  if (mcChannelNumber==361520) { xs = 13939;  kf = 1.20185; }
  if (mcChannelNumber==361521) { xs = 1894;   kf = 1.20185; }
  if (mcChannelNumber==361522) { xs = 642.66; kf = 1.20185; }
  if (mcChannelNumber==361523) { xs = 179.18; kf = 1.20185; }
  if (mcChannelNumber==361524) { xs = 70.785; kf = 1.20185; }
  if (mcChannelNumber==361525) { xs = 13935;  kf = 1.20185; }
  if (mcChannelNumber==361526) { xs = 1893.3; kf = 1.20185; }
  if (mcChannelNumber==361527) { xs = 642.7;  kf = 1.20185; }
  if (mcChannelNumber==361528) { xs = 179.19; kf = 1.20185; }
  if (mcChannelNumber==361529) { xs = 70.761; kf = 1.20185; }
  if (mcChannelNumber==361530) { xs = 13920;  kf = 1.20185; }
  if (mcChannelNumber==361531) { xs = 1891.9; kf = 1.20185; }
  if (mcChannelNumber==361532) { xs = 641.87; kf = 1.20185; }
  if (mcChannelNumber==361533) { xs = 179.21; kf = 1.20185; }
  if (mcChannelNumber==361534) { xs = 71.012; kf = 1.20185; }
  
  // Sherpa Z
  // NLO xsec from Sherpa
  if (mcChannelNumber==361372) { xs =    1718.99   ; kf = 0.9013; }
  if (mcChannelNumber==361373) { xs =    313.795   ; kf = 0.9013; }
  if (mcChannelNumber==361374) { xs =    175.654   ; kf = 0.9013; }
  if (mcChannelNumber==361375) { xs =    48.9553   ; kf = 0.9013; }
  if (mcChannelNumber==361376) { xs =    16.5568   ; kf = 0.9013; }
  if (mcChannelNumber==361377) { xs =    10.0217   ; kf = 0.9013; }
  if (mcChannelNumber==361378) { xs =    7.25553   ; kf = 0.9013; }
  if (mcChannelNumber==361379) { xs =    2.81840   ; kf = 0.9013; }
  if (mcChannelNumber==361380) { xs =    1.75343   ; kf = 0.9013; }
  if (mcChannelNumber==361381) { xs =    0.46428   ; kf = 0.9013; }
  if (mcChannelNumber==361382) { xs =    0.22164   ; kf = 0.9013; }
  if (mcChannelNumber==361383) { xs =    0.13491   ; kf = 0.9013; }
  if (mcChannelNumber==361384) { xs =    0.02991   ; kf = 0.9013; }
  if (mcChannelNumber==361385) { xs =    0.01459   ; kf = 0.9013; }
  if (mcChannelNumber==361386) { xs =    0.00949   ; kf = 0.9013; }
  if (mcChannelNumber==361387) { xs =    0.00587   ; kf = 0.9013; }
  if (mcChannelNumber==361388) { xs = 0.00302   ; kf = 0.9013; }
  if (mcChannelNumber==361389) { xs = 0.00188   ; kf = 0.9013; }
  if (mcChannelNumber==361390) { xs = 0.00073   ; kf = 0.9013; }
  if (mcChannelNumber==361391) { xs = 0.000459  ; kf = 0.9013; }
  if (mcChannelNumber==361392) { xs = 0.000257  ; kf = 0.9013; }
  if (mcChannelNumber==361393) { xs = 3.1868e-06; kf = 0.9013; }
  if (mcChannelNumber==361394) { xs = 3.0549e-06; kf = 0.9013; }
  if (mcChannelNumber==361395) { xs = 2.0788e-06; kf = 0.9013; }
  if (mcChannelNumber==361396) { xs = 1716.87   ; kf = 0.9013; }
  if (mcChannelNumber==361397) { xs = 312.919   ; kf = 0.9013; }
  if (mcChannelNumber==361398) { xs = 175.396   ; kf = 0.9013; }
  if (mcChannelNumber==361399) { xs = 49.2600   ; kf = 0.9013; }
  if (mcChannelNumber==361400) { xs = 16.7057   ; kf = 0.9013; }
  if (mcChannelNumber==361401) { xs = 9.89667   ; kf = 0.9013; }
  if (mcChannelNumber==361402) { xs = 7.08911   ; kf = 0.9013; }
  if (mcChannelNumber==361403) { xs = 2.80404   ; kf = 0.9013; }
  if (mcChannelNumber==361404) { xs = 1.72818   ; kf = 0.9013; }
  if (mcChannelNumber==361405) { xs = 0.50135   ; kf = 0.9013; }
  if (mcChannelNumber==361406) { xs = 0.23597   ; kf = 0.9013; }
  if (mcChannelNumber==361407) { xs = 0.14069   ; kf = 0.9013; }
  if (mcChannelNumber==361408) { xs = 0.03083   ; kf = 0.9013; }
  if (mcChannelNumber==361409) { xs = 0.01495   ; kf = 0.9013; }
  if (mcChannelNumber==361410) { xs = 0.00969   ; kf = 0.9013; }
  if (mcChannelNumber==361411) { xs = 0.00472   ; kf = 0.9013; }
  if (mcChannelNumber==361412) { xs = 0.00285   ; kf = 0.9013; }
  if (mcChannelNumber==361413) { xs = 0.00182   ; kf = 0.9013; }
  if (mcChannelNumber==361414) { xs = 0.000686  ; kf = 0.9013; }
  if (mcChannelNumber==361415) { xs = 0.000394  ; kf = 0.9013; }
  if (mcChannelNumber==361416) { xs = 0.000279  ; kf = 0.9013; }
  if (mcChannelNumber==361417) { xs = 3.986419e-06; kf = 0.9013; }
  if (mcChannelNumber==361418) { xs = 2.209044e-06; kf = 0.9013; }
  if (mcChannelNumber==361419) { xs = 3.198544e-06; kf = 0.9013; }
  if (mcChannelNumber==361420) { xs = 1709.18   ;  kf = 0.9013; }
  if (mcChannelNumber==361421) { xs = 313.721   ;  kf = 0.9013; }
  if (mcChannelNumber==361422) { xs = 174.677   ;  kf = 0.9013; }
  if (mcChannelNumber==361423) { xs = 49.4525   ;  kf = 0.9013; }
  if (mcChannelNumber==361424) { xs = 16.8731   ;  kf = 0.9013; }
  if (mcChannelNumber==361425) { xs = 10.0215   ;  kf = 0.9013; }
  if (mcChannelNumber==361426) { xs = 7.10919   ;  kf = 0.9013; }
  if (mcChannelNumber==361427) { xs = 2.81562   ;  kf = 0.9013; }
  if (mcChannelNumber==361428) { xs = 1.64983   ;  kf = 0.9013; }
  if (mcChannelNumber==361429) { xs = 0.50533   ;  kf = 0.9013; }
  if (mcChannelNumber==361430) { xs = 0.22258   ;  kf = 0.9013; }
  if (mcChannelNumber==361431) { xs = 0.13902   ;  kf = 0.9013; }
  if (mcChannelNumber==361432) { xs = 0.03147   ;  kf = 0.9013; }
  if (mcChannelNumber==361433) { xs = 0.01489   ;  kf = 0.9013; }
  if (mcChannelNumber==361434) { xs = 0.00940   ;  kf = 0.9013; }
  if (mcChannelNumber==361435) { xs = 0.00533   ;  kf = 0.9013; }
  if (mcChannelNumber==361436) { xs = 0.00295   ;  kf = 0.9013; }
  if (mcChannelNumber==361437) { xs = 0.00189   ;  kf = 0.9013; }
  if (mcChannelNumber==361438) { xs = 0.00076   ;  kf = 0.9013; }
  if (mcChannelNumber==361439) { xs = 0.000439  ;  kf = 0.9013; }
  if (mcChannelNumber==361440) { xs = 0.000228  ;  kf = 0.9013; }
  if (mcChannelNumber==361441) { xs = 3.6399e-06;  kf = 0.9013; }
  if (mcChannelNumber==361442) { xs = 2.3389e-06;  kf = 0.9013; }
  if (mcChannelNumber==361443) { xs = 2.4476e-06;  kf = 0.9013; }
  if (mcChannelNumber==361444) { xs = 9292.49;     kf = 0.9141; }
  if (mcChannelNumber==361445) { xs = 1672.57;     kf = 0.9141; }
  if (mcChannelNumber==361446) { xs = 955.982;     kf = 0.9141; }
  if (mcChannelNumber==361447) { xs = 278.000;     kf =  0.9141; }
  if (mcChannelNumber==361448) { xs = 93.5176;     kf =  0.9141; }
  if (mcChannelNumber==361449) { xs = 56.9431;     kf =  0.9141; }
  if (mcChannelNumber==361450) { xs = 40.4600;     kf =  0.9141; }
  if (mcChannelNumber==361451) { xs = 15.6915;     kf =  0.9141; }
  if (mcChannelNumber==361452) { xs = 9.72404;     kf =  0.9141; }
  if (mcChannelNumber==361453) { xs = 2.83776;     kf =  0.9141; }
  if (mcChannelNumber==361454) { xs = 1.25440;     kf =  0.9141; }
  if (mcChannelNumber==361455) { xs = 0.78752;     kf =  0.9141; }
  if (mcChannelNumber==361456) { xs = 0.16347;     kf =  0.9141; }
  if (mcChannelNumber==361457) { xs = 0.08385;     kf =  0.9141; }
  if (mcChannelNumber==361458) { xs = 0.04945;     kf =  0.9141; }
  if (mcChannelNumber==361459) { xs = 0.02904;     kf =  0.9141; }
  if (mcChannelNumber==361460) { xs = 0.01650;     kf =  0.9141; }
  if (mcChannelNumber==361461) { xs = 0.00915;     kf =  0.9141; }
  if (mcChannelNumber==361462) { xs = 0.00328;     kf =  0.9141; }
  if (mcChannelNumber==361463) { xs = 0.00245;     kf =  0.9141; }
  if (mcChannelNumber==361464) { xs = 0.00159;     kf =  0.9141; }
  if (mcChannelNumber==361465) { xs = 1.81635e-05; kf = 0.9141; }
  if (mcChannelNumber==361466) { xs = 1.14102e-05; kf = 0.9141; }
  if (mcChannelNumber==361467) { xs = 7.52484e-06; kf = 0.9141; }

  // Sherpa Low Mass DY
  if (mcChannelNumber==361468) { xs = 2146.84; kf = 0.9013; }
  if (mcChannelNumber==361469) { xs = 106.231; kf = 0.9013; }
  if (mcChannelNumber==361470) { xs = 6.95992; kf = 0.9013; }
  if (mcChannelNumber==361471) { xs = 0.774166; kf = 0.9013; }
  if (mcChannelNumber==361472) { xs = 0.617445; kf = 0.9013; }
  if (mcChannelNumber==361473) { xs = 0.0742106; kf = 0.9013; }
  if (mcChannelNumber==361474) { xs = 0.00605652; kf = 0.9013; }
  if (mcChannelNumber==361475) { xs = 0.001498; kf = 0.9013; }
  if (mcChannelNumber==361476) { xs = 2141.34; kf = 0.9013; }
  if (mcChannelNumber==361477) { xs = 106.373; kf = 0.9013; }
  if (mcChannelNumber==361478) { xs = 6.93811; kf = 0.9013; }
  if (mcChannelNumber==361479) { xs = 0.793501; kf = 0.9013; }
  if (mcChannelNumber==361480) { xs = 0.621546; kf = 0.9013; }
  if (mcChannelNumber==361481) { xs = 0.0825398; kf = 0.9013; }
  if (mcChannelNumber==361482) { xs = 0.00628191; kf = 0.9013; }
  if (mcChannelNumber==361483) { xs = 0.00151; kf = 0.9013; }
  if (mcChannelNumber==361484) { xs = 2159; kf = 0.9013; }
  if (mcChannelNumber==361485) { xs = 105.918; kf = 0.9013; }
  if (mcChannelNumber==361486) { xs = 6.93153; kf = 0.9013; }
  if (mcChannelNumber==361487) { xs = 0.811135; kf = 0.9013; }
  if (mcChannelNumber==361488) { xs = 0.617549; kf = 0.9013; }
  if (mcChannelNumber==361489) { xs = 0.0833129; kf = 0.9013; }
  if (mcChannelNumber==361490) { xs = 0.00700123; kf = 0.9013; }
  if (mcChannelNumber==361491) { xs = 0.001437; kf = 0.9013; }

  // Z+jets Madgraph+Py8
  if (mcChannelNumber==361500) { xs = 1401.6	; kf = 1.2320; }
  if (mcChannelNumber==361501) { xs = 211.99	; kf = 1.2320; }
  if (mcChannelNumber==361502) { xs = 67.305	; kf = 1.2320; }
  if (mcChannelNumber==361503) { xs = 18.679	; kf = 1.2320; }
  if (mcChannelNumber==361504) { xs = 7.291	; kf = 1.2320; }
  if (mcChannelNumber==361505) { xs = 1402	; kf = 1.2320; }
  if (mcChannelNumber==361506) { xs = 211.95	; kf = 1.2320; }
  if (mcChannelNumber==361507) { xs = 67.353	; kf = 1.2320; }
  if (mcChannelNumber==361508) { xs = 18.633	; kf = 1.2320; }
  if (mcChannelNumber==361509) { xs = 7.3013	; kf = 1.2320; }
  if (mcChannelNumber==361510) { xs = 1397.8	; kf = 1.2320; }
  if (mcChannelNumber==361511) { xs = 211.4	; kf = 1.2320; }
  if (mcChannelNumber==361512) { xs = 67.176	; kf = 1.2320; }
  if (mcChannelNumber==361513) { xs = 18.609	; kf = 1.2320; }
  if (mcChannelNumber==361514) { xs = 7.2749	; kf = 1.2320; }
  if (mcChannelNumber==361515) { xs = 7518.4	; kf = 1.2283; }
  if (mcChannelNumber==361516) { xs = 1200.1	; kf = 1.2283; }
  if (mcChannelNumber==361517) { xs = 387.16	; kf = 1.2283; }
  if (mcChannelNumber==361518) { xs = 110.08	; kf = 1.2283; }
  if (mcChannelNumber==361519) { xs = 43.389	; kf = 1.2283; }
 
    // low mll Z+jets Madgraph samples
  if (mcChannelNumber==361628) { xs = 	  2677.1 ; kf = 1.232; }
  if (mcChannelNumber==361629) { xs = 	  44.988 ; kf = 1.232; }
  if (mcChannelNumber==361630) { xs = 	  29.292 ; kf = 1.232; }
  if (mcChannelNumber==361631) { xs = 	  6.117  ; kf = 1.232; }
  if (mcChannelNumber==361632) { xs = 	  2.2091 ; kf = 1.232; }
  if (mcChannelNumber==361633) { xs = 	  2677.1 ; kf = 1.232; }
  if (mcChannelNumber==361634) { xs = 	  44.98  ; kf = 1.232; }
  if (mcChannelNumber==361635) { xs = 	  29.302 ; kf = 1.232; }
  if (mcChannelNumber==361636) { xs = 	  6.1088 ; kf = 1.232; }
  if (mcChannelNumber==361637) { xs = 	  2.2231 ; kf = 1.232; }
  if (mcChannelNumber==361638) { xs = 	  2412.4 ; kf = 1.232; }
  if (mcChannelNumber==361639) { xs = 	  46.019 ; kf = 1.232; }
  if (mcChannelNumber==361640) { xs = 	  28.852 ; kf = 1.232; }
  if (mcChannelNumber==361641) { xs = 	  6.0513 ; kf = 1.232; }
  if (mcChannelNumber==361642) { xs = 	  2.2111 ; kf = 1.232; }

    // Powheg+Py8 mc15        VV
  if (mcChannelNumber==361600	) { xs = 10.631	; kf = 1.0; }
  if (mcChannelNumber==361601	) { xs = 4.4625	; kf = 1.0; }
  if (mcChannelNumber==361602	) { xs = 2.7778	; kf = 1.0; }
  if (mcChannelNumber==361603	) { xs = 1.2568	; kf = 1.0; }
  if (mcChannelNumber==361604	) { xs = 0.92498 ; kf = 1.0; }
  if (mcChannelNumber==361605	) { xs = 0.54901 ; kf = 1.0; }
  if (mcChannelNumber==361606	) { xs = 44.176 ; kf = 1.0; }
  if (mcChannelNumber==361607	) { xs = 3.2849 ; kf = 1.0; }
  if (mcChannelNumber==361608	) { xs = 5.7743 ; kf = 1.0; }
  if (mcChannelNumber==361609	) { xs = 10.099 ; kf = 1.0; }
  if (mcChannelNumber==361610	) { xs = 2.2739 ; kf = 1.0; }
  if (mcChannelNumber==361611	) { xs = 3.9448 ; kf = 1.0; }
  
  // Sherpa	VV
  if (mcChannelNumber==361063) { xs =   12.583	 ; kf = 1.0; }  
  if (mcChannelNumber==361064) { xs =   1.8446  ; kf = 1.0; }   
  if (mcChannelNumber==361065) { xs =   3.6235  ; kf = 1.0; }   
  if (mcChannelNumber==361066) { xs =   2.5656  ; kf = 1.0; }   
  if (mcChannelNumber==361067) { xs =   5.0169  ; kf = 1.0; }   
  if (mcChannelNumber==361068) { xs =   14.022  ; kf = 1.0; }   
  if (mcChannelNumber==361069) { xs =   0.02575  ; kf = 1.0; }   
  if (mcChannelNumber==361070) { xs =   0.043375  ; kf = 1.0; }   
  if (mcChannelNumber==361071) { xs =   0.042017  ; kf = 1.0; }   
  if (mcChannelNumber==361072) { xs =   0.1279   ; kf = 1.0; }   
  if (mcChannelNumber==361073) { xs =   0.02095  ; kf = 1.0; }  
  if (mcChannelNumber==361074) { xs =   0.015884 ; kf = 1.0; }  
  if (mcChannelNumber==361075) { xs =   0.011826 ; kf = 1.0; }  
  if (mcChannelNumber==361076) { xs =   0.006272 ; kf = 1.0; }  
  if (mcChannelNumber==361077) { xs =   0.85492  ; kf = 1.0; }  
  if (mcChannelNumber==361078) { xs =   0.3763  ; kf = 1.0; }  
  if (mcChannelNumber==361079) { xs =   0.5374 ; kf = 1.0; }  
  if (mcChannelNumber==361080) { xs =   0.0508  ; kf = 1.0; }  
  if (mcChannelNumber==361081) { xs =   25.995  ; kf = 1.0; }   
  if (mcChannelNumber==361082) { xs =   25.974  ; kf = 1.0; }   
  if (mcChannelNumber==361083) { xs =   12.543  ; kf = 1.0; }   
  if (mcChannelNumber==361084) { xs =   3.7583  ; kf = 1.0; }   
  if (mcChannelNumber==361085) { xs =   7.4151  ; kf = 1.0; }   
  if (mcChannelNumber==361086) { xs =   2.3647  ; kf = 1.0; }  
  if (mcChannelNumber==361087) { xs =   4.6336  ; kf = 1.0; }  
  
  // Sherpa gamma+jet
  if (mcChannelNumber==361039) { xs =   34988; kf = 0.41028; } 
  if (mcChannelNumber==361040) { xs =   34986; kf = 0.48609; } 
  if (mcChannelNumber==361041) { xs =   35002; kf = 0.10752; } 
  if (mcChannelNumber==361042) { xs =   3129   ; kf = 0.39960;} 
  if (mcChannelNumber==361043) { xs =   3132.9   ; kf = 0.48199; } 
  if (mcChannelNumber==361044) { xs =   3135.2   ; kf = 0.11728; } 
  if (mcChannelNumber==361045) { xs =   247.41   ; kf = 0.41049; } 
  if (mcChannelNumber==361046) { xs =   247.39   ; kf = 0.50284; } 
  if (mcChannelNumber==361047) { xs =   249.37   ; kf = 0.12874; } 
  if (mcChannelNumber==361048) { xs =   13.648   ; kf = 0.41834; } 
  if (mcChannelNumber==361049) { xs =   13.617   ; kf = 0.47349; } 
  if (mcChannelNumber==361050) { xs =   13.874   ; kf = 0.14069; } 
  if (mcChannelNumber==361051) { xs =   0.92334   ; kf = 0.38226; } 
  if (mcChannelNumber==361052) { xs =   0.92185   ; kf = 0.47148; } 
  if (mcChannelNumber==361053) { xs =   0.93819   ; kf = 0.14811; } 
  if (mcChannelNumber==361054) { xs =   0.018432   ; kf = 0.37036; } 
  if (mcChannelNumber==361055) { xs =   0.018388   ; kf = 0.46691; } 
  if (mcChannelNumber==361056) { xs =   0.019046   ; kf = 0.15751; } 
  if (mcChannelNumber==361057) { xs =   7.9163e-05   ; kf = 0.38030; } 
  if (mcChannelNumber==361058) { xs =   8.0515e-05   ; kf = 0.45148; } 
  if (mcChannelNumber==361059) { xs =   8.2153e-05   ; kf = 0.16549; } 
  if (mcChannelNumber==361060) { xs =   2.4843e-09   ; kf = 0.40351; } 
  if (mcChannelNumber==361061) { xs =   2.5134e-09   ; kf = 0.41614; } 
  if (mcChannelNumber==361062) { xs =   2.5431e-09   ; kf = 0.14831; } 

  // Pythia8 dijet
  if (mcChannelNumber==361000) { xs = 76508904600; kf = 1.0; }   
  if (mcChannelNumber==361001) { xs = 1946305980 ; kf = 1.0; }   
  if (mcChannelNumber==361002) { xs = 24431336   ; kf = 1.0; }   
  if (mcChannelNumber==361003) { xs = 312104     ; kf = 1.0; }   
  if (mcChannelNumber==361004) { xs = 3422.36    ; kf = 1.0; }   
  if (mcChannelNumber==361005) { xs = 66.3778    ; kf = 1.0; }   
  if (mcChannelNumber==361006) { xs = 2.57984    ; kf = 1.0; }   
  if (mcChannelNumber==361007) { xs = 0.1803     ; kf = 1.0; }   
  if (mcChannelNumber==361008) { xs = 0.00645739 ; kf = 1.0; }   
  if (mcChannelNumber==361009) { xs = 0.00023784 ; kf = 1.0; }   
  if (mcChannelNumber==361010) { xs = 7.04754e-06; kf = 1.0; }   
  if (mcChannelNumber==361011) { xs = 1.13058e-07; kf = 1.0; }   
  if (mcChannelNumber==361012) { xs = 4.40618e-10; kf = 1.0; }   
  
  if (mcChannelNumber==361020) { xs = 80302080000; kf = 1.0; }   
  if (mcChannelNumber==361021) { xs = 5.26967e+07; kf = 1.0; }   
  if (mcChannelNumber==361022) { xs = 809380     ; kf = 1.0; }   
  if (mcChannelNumber==361023) { xs = 8452.85    ; kf = 1.0; }   
  if (mcChannelNumber==361024) { xs = 134.977    ; kf = 1.0; }   
  if (mcChannelNumber==361025) { xs = 4.20402    ; kf = 1.0; }   
  if (mcChannelNumber==361026) { xs = 0.242119   ; kf = 1.0; }   
  if (mcChannelNumber==361027) { xs = 0.00636958 ; kf = 1.0; }   
  if (mcChannelNumber==361028) { xs = 0.00635145 ; kf = 1.0; }   
  if (mcChannelNumber==361029) { xs = 0.000236729; kf = 1.0; }   
  if (mcChannelNumber==361030) { xs = 7.0498e-06 ; kf = 1.0; }   
  if (mcChannelNumber==361031) { xs = 1.1416e-07 ; kf = 1.0; }   
  if (mcChannelNumber==361032) { xs = 4.40618e-10; kf = 1.0; }   
  
  // PowhegPythia8 dijet
  if (mcChannelNumber==426001) { xs = 1473849828 ; kf = 1.0; }   
  if (mcChannelNumber==426002) { xs = 1.97235e+07; kf = 1.0; }   
  if (mcChannelNumber==426003) { xs = 286031     ; kf = 1.0; }   
  if (mcChannelNumber==426004) { xs = 3238.71    ; kf = 1.0; }   
  if (mcChannelNumber==426005) { xs = 62.3029    ; kf = 1.0; }   
  if (mcChannelNumber==426006) { xs = 2.30961    ; kf = 1.0; }   
  if (mcChannelNumber==426007) { xs = 0.176181   ; kf = 1.0; }   
  if (mcChannelNumber==426008) { xs = 0.00643204 ; kf = 1.0; }   
  if (mcChannelNumber==426009) { xs = 0.000248606; kf = 1.0; }   
  
  // ttH samples 
  // ttH H -> gamgam, all ttbar decays
  if (mcChannelNumber==341081) { xs = 0.0011187; kf = 1.0; }
  // ttH H->all, different ttbar decays
  if (mcChannelNumber==341177) { xs = 0.0536   ; kf = 1.0; }
  if (mcChannelNumber==341270) { xs = 0.2234   ; kf = 1.0; }
  if (mcChannelNumber==341271) { xs = 0.2315   ; kf = 1.0; }
    
  // VBH
  if (mcChannelNumber==341488) { xs = 3.8299 ; kf = 1.0; }
  // ZH
  if (mcChannelNumber==342285) { xs = 0.60072; kf = 1.0; }
  if (mcChannelNumber==342284) { xs = 1.1021 ; kf = 1.0; }
  // ggH
  if (mcChannelNumber==341471) { xs = 30.188 ; kf = 1.0; } 
  
  // W'->tb right-handed, leptonic
  if (mcChannelNumber==302713) { xs = 37.052;   kf = 1.2; }
  if (mcChannelNumber==302714) { xs = 8.9483;   kf = 1.2; }
  if (mcChannelNumber==302715) { xs = 2.9332;   kf = 1.2; }
  if (mcChannelNumber==302716) { xs = 1.1945;   kf = 1.2; }
  if (mcChannelNumber==302717) { xs = 0.52897;  kf = 1.2; }
  if (mcChannelNumber==302718) { xs = 0.25534;  kf = 1.2; }
  if (mcChannelNumber==302719) { xs = 0.13355;  kf = 1.2; }
  if (mcChannelNumber==302720) { xs = 0.071687; kf = 1.2; }
  if (mcChannelNumber==302721) { xs = 0.040492; kf = 1.2; }
  if (mcChannelNumber==302722) { xs = 0.023185; kf = 1.2; }
  if (mcChannelNumber==302723) { xs = 0.013754; kf = 1.2; }
  
  // W'->tb left-handed + STs, leptonic 
  if (mcChannelNumber==302724) { xs = 26.661; kf = 1.2; }
  if (mcChannelNumber==302725) { xs = 7.8852; kf = 1.2; }
  if (mcChannelNumber==302726) { xs = 4.0102; kf = 1.2; }
  if (mcChannelNumber==302727) { xs = 2.8584; kf = 1.2; }
  if (mcChannelNumber==302728) { xs = 2.4813; kf = 1.2; }
  if (mcChannelNumber==302729) { xs = 2.3465; kf = 1.2; }
  if (mcChannelNumber==302730) { xs = 2.295;  kf = 1.2; }
  
  // W'->tb left-handed, leptonic 
  if (mcChannelNumber==302731) { xs = 0.10205;  kf = 1.2; }
  if (mcChannelNumber==302732) { xs = 0.031279; kf = 1.2; }
  if (mcChannelNumber==302733) { xs = 0.010681; kf = 1.2; }
  
  // W'->tb right-handed, full-had
  if (mcChannelNumber==302734) { xs = 1.0596;   kf = 1.2; }
  if (mcChannelNumber==302735) { xs = 0.081045; kf = 1.2; }
  if (mcChannelNumber==302736) { xs = 0.01011;  kf = 1.2; }
  
  // W'->tb left-handed, full-had
  if (mcChannelNumber==302737) { xs = 0.80064;   kf = 1.2; }
  if (mcChannelNumber==302738) { xs = 0.062575;  kf = 1.2; }
  if (mcChannelNumber==302739) { xs = 0.0080124; kf = 1.2; }
  
  // Monotop
  if (mcChannelNumber==302740) { xs = 2.3654;    kf = 1.0; }
  if (mcChannelNumber==302741) { xs = 0.55645;   kf = 1.0; }
  if (mcChannelNumber==302742) { xs = 0.17367;   kf = 1.0; }
  if (mcChannelNumber==302743) { xs = 0.065191;  kf = 1.0; }
  if (mcChannelNumber==302744) { xs = 0.027735;  kf = 1.0; }
  if (mcChannelNumber==302745) { xs = 0.012895;  kf = 1.0; }
  if (mcChannelNumber==302746) { xs = 0.0063956; kf = 1.0; }
  if (mcChannelNumber==302747) { xs = 0.0033304; kf = 1.0; }
  if (mcChannelNumber==302748) { xs = 0.0018022; kf = 1.0; }
  if (mcChannelNumber==302749) { xs = 14.429;    kf = 1.0; }
  if (mcChannelNumber==302750) { xs = 0.17878;   kf = 1.0; }
  if (mcChannelNumber==302751) { xs = 0.012609;  kf = 1.0; }
  if (mcChannelNumber==302752) { xs = 52.774;    kf = 1.0; }
  if (mcChannelNumber==302753) { xs = 0.76989;   kf = 1.0; }
  if (mcChannelNumber==302754) { xs = 0.066446;  kf = 1.0; }
  if (mcChannelNumber==302755) { xs = 147.25;    kf = 1.0; }
  if (mcChannelNumber==302756) { xs = 2.9285;    kf = 1.0; }
  if (mcChannelNumber==302757) { xs = 0.34373;   kf = 1.0; }
  if (mcChannelNumber==302758) { xs = 2.1909;    kf = 1.0; }
  if (mcChannelNumber==302759) { xs = 197.58;    kf = 1.0; }
  if (mcChannelNumber==302760) { xs = 777.29;    kf = 1.0; }
  if (mcChannelNumber==302761) { xs = 245.13;    kf = 1.0; }
  if (mcChannelNumber==302762) { xs = 130.6;     kf = 1.0; }
  if (mcChannelNumber==302763) { xs = 82.934;    kf = 1.0; }
  if (mcChannelNumber==302764) { xs = 41.318;    kf = 1.0; }
  if (mcChannelNumber==302765) { xs = 23.405;    kf = 1.0; }
  if (mcChannelNumber==302766) { xs = 14.19;     kf = 1.0; }
  if (mcChannelNumber==302767) { xs = 9.0838;    kf = 1.0; }
  if (mcChannelNumber==302768) { xs = 2.1468;    kf = 1.0; }
  if (mcChannelNumber==302769) { xs = 0.54548;   kf = 1.0; }
  if (mcChannelNumber==302770) { xs = 0.17974;   kf = 1.0; }
  if (mcChannelNumber==302771) { xs = 0.069379;  kf = 1.0; }
  if (mcChannelNumber==302772) { xs = 0.029753;  kf = 1.0; }
  if (mcChannelNumber==302773) { xs = 0.013731;  kf = 1.0; }
  if (mcChannelNumber==302774) { xs = 0.0066796; kf = 1.0; }
  if (mcChannelNumber==302775) { xs = 0.0033791; kf = 1.0; }
  if (mcChannelNumber==302776) { xs = 0.0017625; kf = 1.0; }

    // TTS samples: taken from https://cds.cern.ch/record/1662536/files/ATL-COM-PHYS-2014-112.pdf?
  if (mcChannelNumber==302468) { xs = 3.38      ; kf = 1.0; }
  if (mcChannelNumber==302469) { xs = 1.16      ; kf = 1.0; }
  if (mcChannelNumber==302470) { xs = 0.455     ; kf = 1.0; }
  if (mcChannelNumber==302471) { xs = 0.295     ; kf = 1.0; }
  if (mcChannelNumber==302472) { xs = 0.195     ; kf = 1.0; }
  if (mcChannelNumber==302473) { xs = 0.132     ; kf = 1.0; }
  if (mcChannelNumber==302474) { xs = 0.0900    ; kf = 1.0; }
  if (mcChannelNumber==302475) { xs = 0.0624    ; kf = 1.0; }
  if (mcChannelNumber==302476) { xs = 0.0438    ; kf = 1.0; }
  if (mcChannelNumber==302477) { xs = 0.0311    ; kf = 1.0; }
  if (mcChannelNumber==302478) { xs = 0.0223    ; kf = 1.0; }
  if (mcChannelNumber==302479) { xs = 0.0161    ; kf = 1.0; }
  if (mcChannelNumber==302480) { xs = 0.0117    ; kf = 1.0; }
  if (mcChannelNumber==302481) { xs = 0.00634   ; kf = 1.0; }
  if (mcChannelNumber==302482) { xs = 0.00350   ; kf = 1.0; }
  // TTD
  if (mcChannelNumber==302483) { xs = 0.455;  kf = 1.0; }
  if (mcChannelNumber==302484) { xs = 0.0624; kf = 1.0; }
  if (mcChannelNumber==302485) { xs = 0.0117; kf = 1.0; }

    // BBS samples: taken from https://cds.cern.ch/record/1662536/files/ATL-COM-PHYS-2014-112.pdf?
  if (mcChannelNumber==302486) { xs = 3.38      ; kf = 1.0; }
  if (mcChannelNumber==302487) { xs = 1.16      ; kf = 1.0; }
  if (mcChannelNumber==302488) { xs = 0.455     ; kf = 1.0; }
  if (mcChannelNumber==302489) { xs = 0.295     ; kf = 1.0; }
  if (mcChannelNumber==302490) { xs = 0.195     ; kf = 1.0; }
  if (mcChannelNumber==302491) { xs = 0.132     ; kf = 1.0; }
  if (mcChannelNumber==302492) { xs = 0.0900    ; kf = 1.0; }
  if (mcChannelNumber==302493) { xs = 0.0624    ; kf = 1.0; }
  if (mcChannelNumber==302494) { xs = 0.0438    ; kf = 1.0; }
  if (mcChannelNumber==302495) { xs = 0.0311    ; kf = 1.0; }
  if (mcChannelNumber==302496) { xs = 0.0223    ; kf = 1.0; }
  if (mcChannelNumber==302497) { xs = 0.0161    ; kf = 1.0; }
  if (mcChannelNumber==302498) { xs = 0.0117    ; kf = 1.0; }
  if (mcChannelNumber==302499) { xs = 0.00634   ; kf = 1.0; }
  if (mcChannelNumber==302500) { xs = 0.00350   ; kf = 1.0; }
  // BBD
  if (mcChannelNumber==302501 ) { xs = 0.455;  kf = 1.0; }
  if (mcChannelNumber==302502 ) { xs = 0.0624; kf = 1.0; }
  if (mcChannelNumber==302503 ) { xs = 0.0117; kf = 1.0; }

  // XX,YY samples: taken from https://cds.cern.ch/record/1662536/files/ATL-COM-PHYS-2014-112.pdf?
  if (mcChannelNumber==302504) { xs = 3.38     ; kf = 1.0; }
  if (mcChannelNumber==302505) { xs = 0.455    ; kf = 1.0; }
  if (mcChannelNumber==302506) { xs = 0.195    ; kf = 1.0; }
  if (mcChannelNumber==302507) { xs = 0.0900   ; kf = 1.0; }
  if (mcChannelNumber==302508) { xs = 0.0438   ; kf = 1.0; }
  if (mcChannelNumber==302509) { xs = 0.0223   ; kf = 1.0; }
  if (mcChannelNumber==302510) { xs = 0.0117   ; kf = 1.0; }
  if (mcChannelNumber==302511) { xs = 0.00350  ; kf = 1.0; }
  if (mcChannelNumber==302512) { xs = 3.38     ; kf = 1.0; }
  if (mcChannelNumber==302513) { xs = 0.455    ; kf = 1.0; }
  if (mcChannelNumber==302514) { xs = 0.195    ; kf = 1.0; }
  if (mcChannelNumber==302515) { xs = 0.0900   ; kf = 1.0; }
  if (mcChannelNumber==302516) { xs = 0.0438   ; kf = 1.0; }
  if (mcChannelNumber==302517) { xs = 0.0223   ; kf = 1.0; }
  if (mcChannelNumber==302518) { xs = 0.0117   ; kf = 1.0; }
  if (mcChannelNumber==302519) { xs = 0.00350  ; kf = 1.0; }

    // ttH(->tautau)
  if (mcChannelNumber==342170) { xs = 0.0536; kf = 0.0632; }
  if (mcChannelNumber==342171) { xs = 0.2234; kf = 0.0632; } 
  if (mcChannelNumber==342172) { xs = 0.2315; kf = 0.0632; }  
  
  return xs*kf;
}

