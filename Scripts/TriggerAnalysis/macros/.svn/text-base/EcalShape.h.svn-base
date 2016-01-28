//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 14 18:55:28 2009 by ROOT version 5.18/00a
// from TTree EcalShape/EcalShape
// found on file: ../scripts/ECALTPGtree.root
//////////////////////////////////////////////////////////

#ifndef EcalShape_h
#define EcalShape_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class EcalShape {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          evtNb;
   Int_t           ieta;
   Int_t           iphi;
   UInt_t          nbOfSamples;
   Int_t           samp[290];   //[nbOfSamples]

   // List of branches
   TBranch        *b_evtNb;   //!
   TBranch        *b_ieta;   //!
   TBranch        *b_iphi;   //!
   TBranch        *b_nbOfSamples;   //!
   TBranch        *b_samp;   //!

   EcalShape(TTree *tree=0);
   virtual ~EcalShape();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef EcalShape_cxx
EcalShape::EcalShape(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../scripts/ECALTPGtree.root");
      if (!f) {
         f = new TFile("../scripts/ECALTPGtree.root");
      }
      tree = (TTree*)gDirectory->Get("EcalShape");

   }
   Init(tree);
}

EcalShape::~EcalShape()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t EcalShape::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t EcalShape::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void EcalShape::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evtNb", &evtNb, &b_evtNb);
   fChain->SetBranchAddress("ieta", &ieta, &b_ieta);
   fChain->SetBranchAddress("iphi", &iphi, &b_iphi);
   fChain->SetBranchAddress("nbOfSamples", &nbOfSamples, &b_nbOfSamples);
   fChain->SetBranchAddress("samp", samp, &b_samp);
   Notify();
}

Bool_t EcalShape::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void EcalShape::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t EcalShape::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef EcalShape_cxx
