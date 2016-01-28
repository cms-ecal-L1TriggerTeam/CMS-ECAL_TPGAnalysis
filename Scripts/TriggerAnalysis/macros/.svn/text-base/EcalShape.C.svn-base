#define EcalShape_cxx
#include "EcalShape.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <sstream>

TH1F * pulse ;

void EcalShape::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L EcalShape.C
//      Root > EcalShape t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TH3D * timing = new TH3D("timing", "Timing TP data", 72, 1, 73, 56, -28, 28, 10, 0.5, 10.5) ;
   timing->GetYaxis()->SetTitle("eta index") ;
   timing->GetXaxis()->SetTitle("phi index") ;
   TH2D * timing2D = new TH2D("timing2D", "Timing TP data", 72, 1, 73, 56, -28, 28) ;
   timing2D->GetYaxis()->SetTitle("eta index") ;
   timing2D->GetXaxis()->SetTitle("phi index") ;
   TH1D * timing1D = new TH1D("timing1D", "Timing TP data", 10, 0.5, 10.5) ;
  
   bool display(true) ;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (display) {
	stringstream ss ;
	ss<<"ieta="<<ieta<<", iphi="<<iphi<<", evt="<<evtNb ;
	pulse = new TH1F("pulse", ss.str().c_str(), 10, 0, 10) ;
	int max = 0 ;
	int min = 999999999 ;
	for (int i=0 ; i<10 ; i ++) {
	  pulse->Fill(i, samp[i]) ;
	  if (samp[i]<min) min = samp[i] ;
	  if (samp[i]>max) max = samp[i] ;
	}
	pulse->Draw() ;
	int pause ;
	c1->Update() ;
	cin >> pause ;
	if (pause==0) break ;
      }
      delete pulse ;

      int max = 0 ;
      float time = 0 ;
      for (int i=0 ; i<10 ; i ++) {
	if (samp[i]>max) {
	  max = samp[i] ;
	  time = i+1 ;
	}
      }
      timing->Fill(iphi, ieta, time) ;
      timing1D->Fill(time) ;
   }


   for (int binx=1 ; binx<=72 ; binx++)    
     for (int biny=1 ; biny<=56 ; biny++) {
       double t = 0. ;
       int nbTime(0) ;
       for (int binz=1; binz<=10 ; binz++) {   
	 int content = timing->GetBinContent(binx, biny, binz) ;
	 if (content>0) {
	   cout<<binx<<" "<<biny<<" "<<binz<<" "<<content<<endl; 
	   t += content*binz ;
	   nbTime += content ;
	 }
       }
       if (nbTime>0) {
	 t /= nbTime ;
	 cout<<t<<endl ;
	 timing2D->SetBinContent(binx, biny, t) ;
       }
     }
}
