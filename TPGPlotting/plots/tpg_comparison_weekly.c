{

  gStyle->SetLabelSize(0.05,"xyz");
  gStyle->SetTitleSize(0.06,"xyz");


  gStyle->SetTitleOffset(1.0,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetPalette(1);

  gStyle->SetPadRightMargin(0.14);

  TLatex t1;
  t1.SetNDC();
  t1.SetTextAlign(26);
  t1.SetTextSize(0.06);

  //  TFile f1("histoTPG_251643_before_252113_full_eg12.root");
    //TFile f1("histoTPG_251643_no_transpcorr_eg12.root");
  //  TFile f2("histoTPG_251643_with_252113_eg12.root");
  //  TFile f1("histoTPG_251643_with_252519_eg12.root"); 

  //  TFile f1("histoTPG_251643_with_252519_eg12.root"); 
  //  TFile f1("histoTPG_251643_with_253517_eg12.root");
  //  TFile f2("histoTPG_251643_with_253894_eg12.root");
  //  TFile f1("histoTPG_251643_eg12_Aug10.root");
  //  TFile f2("histoTPG_251643_eg12_Aug17.root");

  TFile f2("newhistoTPG_257682_nov2_eg12.root");
  TFile f1("newhistoTPG_257682_oct26_eg12.root");
  

  TFile f3("etaphi_ee.root");

  Float_t scaling=1.;



  TH2F *eta2d=(TH2F*)f3.Get("eta");

  Float_t vec[8]={1.5,1.6,1.8,2.0,2.2,2.4,2.6,3.0};

  TH1F *eta1d_eep_1=new TH1F("eta1d_eep_1","",7,vec);
  TH1F *eta1d_eep_2=new TH1F("eta1d_eep_2","",7,vec);
  TH1F *eta1d_eep_rat=new TH1F("eta1d_eep_rat","",7,vec);

  TH1F *eta1d_eem_1=new TH1F("eta1d_eem_1","",7,vec);
  TH1F *eta1d_eem_2=new TH1F("eta1d_eem_2","",7,vec);
  TH1F *eta1d_eem_rat=new TH1F("eta1d_eem_rat","",7,vec);


  TH1F *eep_spect_1=(TH1F*)f1.Get("TPEmulEEPlus");
  TH1F *eem_spect_1=(TH1F*)f1.Get("TPEmulEEMinus");
  TH1F *eb_spect_1=(TH1F*)f1.Get("TPEmulEB");

  TH1F *eep_spect_2=(TH1F*)f2.Get("TPEmulEEPlus");
  TH1F *eem_spect_2=(TH1F*)f2.Get("TPEmulEEMinus");
  TH1F *eb_spect_2=(TH1F*)f2.Get("TPEmulEB");


  TH2F *eep_occup_1=(TH2F*)f1.Get("occupancyTPEmulEEPlus");
  TH2F *eem_occup_1=(TH2F*)f1.Get("occupancyTPEmulEEMinus");


 

  TH2F *eep_occup_2=(TH2F*)f2.Get("occupancyTPEmulEEPlus");
  TH2F *eem_occup_2=(TH2F*)f2.Get("occupancyTPEmulEEMinus");


  TH2F *eb_occup_1=(TH2F*)f1.Get("occupancyTPEmulEB");
  TH2F *eb_occup_2=(TH2F*)f2.Get("occupancyTPEmulEB");

  //  TH1F *eb_occrat_1d=new TH1F("eb_occrat_1d","",100,0.8,1.3);
  TH1F *eb_occrat_1d=new TH1F("eb_occrat_1d","",100,0.8,1.3);

  TH1F *eep_occrat_1d=new TH1F("eep_occrat_1d","",1000,0,20);
  TH1F *eep_occrat_etabin1_1d=new TH1F("eep_occrat_etabin1_1d","",1000,0,20);
  TH1F *eep_occrat_etabin2_1d=new TH1F("eep_occrat_etabin2_1d","",1000,0,20);
  TH1F *eep_occrat_etabin3_1d=new TH1F("eep_occrat_etabin3_1d","",1000,0,20);
  TH1F *eep_occrat_etabin4_1d=new TH1F("eep_occrat_etabin4_1d","",1000,0,20);
  TH1F *eep_occrat_etabin5_1d=new TH1F("eep_occrat_etabin5_1d","",1000,0,20);

  TH1F *eem_occrat_1d=new TH1F("eem_occrat_1d","",1000,0,20);
  TH1F *eem_occrat_etabin1_1d=new TH1F("eem_occrat_etabin1_1d","",1000,0,20);
  TH1F *eem_occrat_etabin2_1d=new TH1F("eem_occrat_etabin2_1d","",1000,0,20);
  TH1F *eem_occrat_etabin3_1d=new TH1F("eem_occrat_etabin3_1d","",1000,0,20);
  TH1F *eem_occrat_etabin4_1d=new TH1F("eem_occrat_etabin4_1d","",1000,0,20);
  TH1F *eem_occrat_etabin5_1d=new TH1F("eem_occrat_etabin5_1d","",1000,0,20);



  TLegend leg2(0.2,0.6,0.4,0.8);
  leg2.SetBorderSize(0);
  leg2.SetFillStyle(0);
  leg2.SetFillColor(0);
  eta1d_eem_rat->SetLineStyle(2);
  leg2.AddEntry(eta1d_eep_rat,"EE+","l");
  leg2.AddEntry(eta1d_eem_rat,"EE-","l");



  TCanvas c1("c1","c1",10,10,1000,700);

  eep_spect_1->Rebin(4);
  eep_spect_2->Rebin(4);

  eem_spect_1->Rebin(4);
  eem_spect_2->Rebin(4);

  eb_spect_1->Rebin(4);
  eb_spect_2->Rebin(4);


  c1.SetLogy(1);

  eep_spect_1->SetLineColor(921);
  eep_spect_1->SetLineWidth(2);
  eep_spect_2->SetLineWidth(2);
  eep_spect_2->SetLineStyle(2);
  eep_spect_2->SetLineColor(1);


  eem_spect_1->SetLineColor(921);
  eem_spect_1->SetLineWidth(2);
  eem_spect_2->SetLineWidth(2);
  eem_spect_2->SetLineStyle(2);
  eem_spect_2->SetLineColor(1);


  eb_spect_1->SetLineColor(921);
  eb_spect_1->SetLineWidth(2);
  eb_spect_2->SetLineWidth(2);
  eb_spect_2->SetLineStyle(2);
  eb_spect_2->SetLineColor(1);

  eb_spect_2->Scale(scaling);
  eep_spect_2->Scale(scaling);
  eem_spect_2->Scale(scaling);


  TLegend leg1(0.5,0.5,0.75,0.75);
  leg1.SetBorderSize(0);
  leg1.AddEntry(eep_spect_1,"OLD","l");
  leg1.AddEntry(eep_spect_2,"NEW","l");

  eep_spect_1->SetTitle("");
  eep_spect_2->SetTitle("");
  eem_spect_1->SetTitle("");
  eem_spect_2->SetTitle("");
  eb_spect_1->SetTitle("");
  eb_spect_2->SetTitle("");




  eep_spect_1->Draw();
  eep_spect_2->Draw("same"); 

  leg1.Draw();

  t1.DrawLatex(0.5,0.92,"Emulated TP Spectrum, EE+");

  c1.SaveAs("./validationplots_nov2/tpspect_eep_2015vs2013.png");

   eem_spect_1->Draw();
   eem_spect_2->Draw("same"); 

  leg1.Draw();

  t1.DrawLatex(0.5,0.92,"Emulated TP Spectrum, EE-");

  c1.SaveAs("./validationplots_nov2/tpspect_eem_2015vs2013.png");


  eb_spect_1->Draw();
  eb_spect_2->Draw("same"); 
  leg1.Draw();

  t1.DrawLatex(0.5,0.92,"Emulated TP Spectrum, EB");

  c1.SaveAs("./validationplots_nov2/tpspect_eb_2015vs2013.png");

  c1.SetLogy(0);

  TH1F *eeprat=new TH1F("eeprat","",64,0.0,256.0);
  TH1F *eemrat=new TH1F("eemrat","",64,0.0,256.0);
  TH1F *ebrat=new TH1F("ebrat","",64,0.0,256.0);


  TH1F *ebaccum_1=new TH1F("ebaccum_1","",64,0,128);
  TH1F *ebaccum_2=new TH1F("ebaccum_2","",64,0,128);
  TH1F *ebaccum_rat=new TH1F("ebaccum_rat","",64,0,128);

  TH1F *eepaccum_1=new TH1F("eepaccum_1","",64,0,128);
  TH1F *eepaccum_2=new TH1F("eepaccum_2","",64,0,128);
  TH1F *eepaccum_rat=new TH1F("eepaccum_rat","",64,0,128);

  TH1F *eemaccum_1=new TH1F("eemaccum_1","",64,0,128);
  TH1F *eemaccum_2=new TH1F("eemaccum_2","",64,0,128);
  TH1F *eemaccum_rat=new TH1F("eemaccum_rat","",64,0,128);


  for (Int_t i=0;i<64;i++) {

    Float_t integ1=eb_spect_1->Integral(i+1,64);
    Float_t integ2=eb_spect_2->Integral(i+1,64);
    Float_t integrat=0;
    if (integ1>0) integrat=integ2/integ1;

    ebaccum_1->SetBinContent(i+1,integ1);
    ebaccum_2->SetBinContent(i+1,integ2);
    ebaccum_rat->SetBinContent(i+1,integrat);

  }



  for (Int_t i=0;i<64;i++) {

   Float_t integ1=eep_spect_1->Integral(i+1,64)-eep_spect_1->GetBinContent(32);
   Float_t integ2=eep_spect_2->Integral(i+1,64)-eep_spect_2->GetBinContent(32);
   Float_t integrat=0;
   if (integ1>0) integrat=integ2/integ1;
   
   eepaccum_1->SetBinContent(i+1,integ1);
    eepaccum_2->SetBinContent(i+1,integ2);
    eepaccum_rat->SetBinContent(i+1,integrat);

 }

  for (Int_t i=0;i<64;i++) {

   Float_t integ1=eem_spect_1->Integral(i+1,64)-eem_spect_1->GetBinContent(32);
   Float_t integ2=eem_spect_2->Integral(i+1,64)-eem_spect_2->GetBinContent(32);
   Float_t integrat=0;
   if (integ1>0) integrat=integ2/integ1;
   
   eemaccum_1->SetBinContent(i+1,integ1);
   eemaccum_2->SetBinContent(i+1,integ2);
   eemaccum_rat->SetBinContent(i+1,integrat);

 }



  eeprat->Divide(eep_spect_2,eep_spect_1);
  eemrat->Divide(eem_spect_2,eem_spect_1);
  ebrat->Divide(eb_spect_2,eb_spect_1);
  eeprat->GetYaxis()->SetRangeUser(0.6,1.8);
  eemrat->GetYaxis()->SetRangeUser(0.6,1.8);
  ebrat->GetYaxis()->SetRangeUser(0.6,1.8);

  TLine lin1(0,1,256,1);
  lin1.SetLineStyle(3);
  lin1.SetLineWidth(3);

  eeprat->SetXTitle("Trigger primitive E_{T} (ADC counts)");
  eeprat->SetYTitle("Ratio: NEW/OLD");


  eeprat->Draw();
  lin1.Draw();


  t1.DrawLatex(0.5,0.92,"Emulated TP Spectrum Ratio, EE+");

  c1.SaveAs("./validationplots_nov2/tpspectrat_eep_2015vs2013.png");

  eemrat->SetXTitle("Trigger primitive E_{T} (ADC counts)");
  eemrat->SetYTitle("Ratio: NEW/OLD");

  eemrat->Draw();
  lin1.Draw();


  t1.DrawLatex(0.5,0.92,"Emulated TP Spectrum Ratio, EE-");


  c1.SaveAs("./validationplots_nov2/tpspectrat_eem_2015vs2013.png");


  ebrat->SetXTitle("Trigger primitive E_{T} (ADC counts)");
  ebrat->SetYTitle("Ratio: NEW/OLD");

  ebrat->Draw();
  lin1.Draw();


  t1.DrawLatex(0.5,0.92,"Emulated TP Spectrum Ratio, EB");


  c1.SaveAs("./validationplots_nov2/tpspectrat_eb_2015vs2013.png");


  c1.SetLogy(1);

  ebaccum_1->SetXTitle("Trigger primitive E_{T} threshold [GeV]");
  ebaccum_1->SetYTitle("Counts");
  ebaccum_2->SetLineStyle(2);
  ebaccum_1->Draw();
  ebaccum_2->Draw("same");

  leg1.Draw();
  t1.DrawLatex(0.5,0.92,"TP Rate, E_{T}>thresh, EB");


  c1.SaveAs("./validationplots_nov2/tpspect_accum_eb_2015vs2013.png");


  eepaccum_1->SetXTitle("Trigger primitive E_{T} threshold [GeV]");
  eepaccum_1->SetYTitle("Counts");
  eepaccum_2->SetLineStyle(2);
  eepaccum_1->Draw();
  eepaccum_2->Draw("same");

  leg1.Draw();
  t1.DrawLatex(0.5,0.92,"TP Rate, E_{T}>thresh, EE+");


  c1.SaveAs("./validationplots_nov2/tpspect_accum_eep_2015vs2013.png");



  eemaccum_1->SetXTitle("Trigger primitive E_{T} threshold [GeV]");
  eemaccum_1->SetYTitle("Counts");
  eemaccum_2->SetLineStyle(2);
  eemaccum_1->Draw();
  eemaccum_2->Draw("same");

  leg1.Draw();
  t1.DrawLatex(0.5,0.92,"TP Rate, E_{T}>thresh, EE-");


  c1.SaveAs("./validationplots_nov2/tpspect_accum_eem_2015vs2013.png");


  c1.SetLogy(0);

  eepaccum_rat->SetMinimum(0.9);
  eepaccum_rat->SetMaximum(1.1);
  eepaccum_rat->SetXTitle("Trigger primitive E_{T} threshold [GeV]");
  eepaccum_rat->SetYTitle("Ratio");

  eepaccum_rat->Draw();
  eemaccum_rat->SetLineStyle(2);
  eemaccum_rat->Draw("same");
  t1.DrawLatex(0.5,0.92,"TP Ratio of Rates, E_{T}>thresh, EE");
  leg2.Draw();
  c1.SaveAs("./validationplots_nov2/tpspect_accumrat_ee_2015vs2013.png");



  ebaccum_rat->SetMinimum(0.9);
  ebaccum_rat->SetMaximum(1.1);
  ebaccum_rat->SetXTitle("Trigger primitive E_{T} threshold [GeV]");
  ebaccum_rat->SetYTitle("Ratio");

  ebaccum_rat->Draw();
  t1.DrawLatex(0.5,0.92,"TP Ratio of Rates, E_{T}>thresh, EB");

  c1.SaveAs("./validationplots_nov2/tpspect_accumrat_eb_2015vs2013.png");


  c1.SetLogy(0);
  c1.SetLogz(1);

  eep_occup_2->Scale(scaling);
  eem_occup_2->Scale(scaling);

  Float_t maxim=eep_occup_1->GetMaximum()*1.2;
  eep_occup_1->SetMaximum(maxim);
  eep_occup_2->SetMaximum(maxim);
  eem_occup_1->SetMaximum(maxim);
  eem_occup_2->SetMaximum(maxim);


  eep_occup_1->SetTitle("");
  eep_occup_2->SetTitle("");

  eem_occup_1->SetTitle("");
  eem_occup_2->SetTitle("");
 


  eep_occup_1->Draw("colz");
  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy, EE+ - OLD");
  c1.SaveAs("./validationplots_nov2/eep_occ_old_2015vs2013.png");

  eep_occup_2->Draw("colz");
  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy, EE+ - NEW");
  c1.SaveAs("./validationplots_nov2/eep_occ_new_2015vs2013.png");

  eem_occup_1->Draw("colz");
  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy, EE- - OLD");
  c1.SaveAs("./validationplots_nov2/eem_occ_old_2015vs2013.png");

  eem_occup_2->Draw("colz");
  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy, EE- - NEW");
  c1.SaveAs("./validationplots_nov2/eem_occ_new_2015vs2013.png");


  TH2F *eeprat2d=new TH2F("eeprat2d","",100,0,100,100,0,100);
  TH2F *eemrat2d=new TH2F("eemrat2d","",100,0,100,100,0,100);


  for (Int_t i=11;i<111;i++) {

    for (Int_t j=11;j<111;j++) {


      Float_t tmp1=eep_occup_1->GetBinContent(i+1,j+1);
      Float_t tmp2=eep_occup_2->GetBinContent(i+1,j+1);
      Float_t eta=eta2d->GetBinContent(i-10,j-10);


      Float_t rat=0;

      if (tmp1>0) {
         rat=tmp2/tmp1;
         eta1d_eep_1->Fill(eta,tmp1);
         eta1d_eep_2->Fill(eta,tmp2);

         eep_occrat_1d->Fill(rat);

	 if (eta<1.8) eep_occrat_etabin1_1d->Fill(rat);
	 if (eta>=1.8 && eta<2.1) eep_occrat_etabin2_1d->Fill(rat);
	 if (eta>=2.1 && eta<2.4) eep_occrat_etabin3_1d->Fill(rat);
	 if (eta>=2.4 && eta<2.7) eep_occrat_etabin4_1d->Fill(rat);
	 if (eta>=2.7) eep_occrat_etabin5_1d->Fill(rat);


      }

      eeprat2d->SetBinContent(i-10,j-10,rat);

      Float_t tmp1eem=eem_occup_1->GetBinContent(i+1,j+1);
      Float_t tmp2eem=eem_occup_2->GetBinContent(i+1,j+1);

      Float_t rateem=0;

      if (tmp1eem>0) {

	rateem=tmp2eem/tmp1eem;
	eta1d_eem_1->Fill(eta,tmp1eem);
	eta1d_eem_2->Fill(eta,tmp2eem);

        eem_occrat_1d->Fill(rateem);
	if (eta<1.8) eem_occrat_etabin1_1d->Fill(rateem);
	if (eta>=1.8 && eta<2.1) eem_occrat_etabin2_1d->Fill(rateem);
	if (eta>=2.1 && eta<2.4) eem_occrat_etabin3_1d->Fill(rateem);
	if (eta>=2.4 && eta<2.7) eem_occrat_etabin4_1d->Fill(rateem);
	if (eta>=2.7) eem_occrat_etabin5_1d->Fill(rateem);

      }

      eemrat2d->SetBinContent(i-10,j-10,rateem);

    }
  }

  // eeprat2d->SetMinimum(0.65);
  // eeprat2d->SetMaximum(2.0);

  // eemrat2d->SetMinimum(0.65);
  // eemrat2d->SetMaximum(2.0);


  eeprat2d->SetMinimum(0.8);
  eeprat2d->SetMaximum(1.8);

  eemrat2d->SetMinimum(0.8);
  eemrat2d->SetMaximum(1.8);


  c1.SetLogz(0);
  eeprat2d->SetXTitle("X index");
  eeprat2d->SetYTitle("Y index");

  eemrat2d->SetXTitle("X index");
  eemrat2d->SetYTitle("Y index");

  eeprat2d->Draw("colz");

  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy, EE+ RATIO: NEW/OLD");
  c1.SaveAs("./validationplots_nov2/eep_occ_newoverold_2015vs2013.png");


  eemrat2d->Draw("colz");
 
  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy, EE- RATIO: NEW/OLD");
  c1.SaveAs("./validationplots_nov2/eem_occ_newoverold_2015vs2013.png");




  eta1d_eep_1->SetLineColor(921);
  eta1d_eep_1->SetLineWidth(2);
  eta1d_eep_2->SetLineWidth(2);
  eta1d_eep_2->SetLineStyle(2);
  eta1d_eep_2->SetLineColor(1);
  eta1d_eep_1->SetMinimum(0.75);

  Float_t max2=eta1d_eep_1->GetMaximum()*1.5;
  eta1d_eep_1->SetMaximum(max2);

  eta1d_eep_1->Draw();
  eta1d_eep_2->Draw("same");
  eta1d_eep_1->SetXTitle("|#eta|");
  eta1d_eep_1->SetYTitle("Occupancy");
  leg1.Draw();


  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy vs #eta: EE+");
  c1.SaveAs("./validationplots_nov2/eep_occ_vs_eta_2015vs2013.png");

  eta1d_eem_1->SetLineColor(921);
  eta1d_eem_1->SetLineWidth(2);
  eta1d_eem_2->SetLineWidth(2);
  eta1d_eem_2->SetLineStyle(2);
  eta1d_eem_2->SetLineColor(1);
  eta1d_eem_1->SetMinimum(0);
  eta1d_eem_1->SetMaximum(max2);

  eta1d_eem_1->Draw();
  eta1d_eem_2->Draw("same");

  eta1d_eem_1->SetXTitle("|#eta|");
  eta1d_eem_1->SetYTitle("Occupancy");
  leg1.Draw();


  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy vs #eta: EE-");
  c1.SaveAs("./validationplots_nov2/eem_occ_vs_eta_2015vs2013.png");


  eta1d_eep_rat->SetLineColor(1);
  eta1d_eep_rat->SetLineStyle(1);
  eta1d_eep_rat->SetLineWidth(2);
  eta1d_eem_rat->SetLineColor(1);
  eta1d_eem_rat->SetLineStyle(2);
  eta1d_eem_rat->SetLineWidth(2);

  eta1d_eep_rat->Divide(eta1d_eep_2,eta1d_eep_1);
  eta1d_eem_rat->Divide(eta1d_eem_2,eta1d_eem_1);

  eta1d_eep_rat->SetMinimum(0.9);
  eta1d_eep_rat->SetMaximum(1.6);

  eta1d_eep_rat->Draw();
  eta1d_eem_rat->Draw("same");

 
  eta1d_eep_rat->SetXTitle("|#eta|");
  eta1d_eep_rat->SetYTitle("Ratio: NEW/OLD");
  leg2.Draw();


  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy vs #eta: NEW/OLD");
  c1.SaveAs("./validationplots_nov2/occ_ratio_vs_eta_2015vs2013.png");




  TH2F *eboccrat=new TH2F("eboccrat","",72,1,73,38,-19,19);

  eboccrat->Divide(eb_occup_2,eb_occup_1);
  eboccrat->SetMinimum(0.9);
  eboccrat->SetMaximum(1.1);

  eboccrat->SetXTitle("#phi index");
  eboccrat->SetYTitle("#eta index");

  eboccrat->Draw("colz");
  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy, EB RATIO: NEW/OLD");

  c1.SaveAs("./validationplots_nov2/eb_occ_ratio_2d_2015vs2013.png");

  TH1F *ebocc_eta_1=new TH1F("ebocc_eta_1","",35,-17.5,17.5);
  TH1F *ebocc_eta_2=new TH1F("ebocc_eta_2","",35,-17.5,17.5);
  TH1F *eboccrat_eta=new TH1F("eboccrat_eta","",35,-17.5,17.5);


  for (Int_t i=0;i<35;i++) {

    Float_t count1=0;
    Float_t count2=0;

    for (Int_t j=0;j<72;j++) {

      Float_t temp1=eb_occup_1->GetBinContent(j+1,i+3);
      Float_t temp2=eb_occup_2->GetBinContent(j+1,i+3);
      
      count1+=temp1;
      count2+=temp2;

      if (temp1>0 && temp2>0) {
	eb_occrat_1d->Fill(count2/count1);
      }
      //   cout << "i:j" << i << ":" << j << " count1=" << count1 << " count2=" << count2 << endl;

    }

    ebocc_eta_1->SetBinContent(i+1,count1);
    ebocc_eta_2->SetBinContent(i+1,count2);

    Float_t rat=0;

    if (count1>0 && count2>0)  {

      eboccrat_eta->SetBinContent(i+1,count2/count1);


    }


  }


  ebocc_eta_1->SetLineColor(921);
  ebocc_eta_1->SetLineWidth(2);
  ebocc_eta_2->SetLineWidth(2);
  ebocc_eta_2->SetLineStyle(2);
  ebocc_eta_2->SetLineColor(1);
  ebocc_eta_1->SetMinimum(0);

  Float_t max2eb=ebocc_eta_1->GetMaximum()*1.5;
  ebocc_eta_1->SetMaximum(max2eb);

  ebocc_eta_1->Draw();
  ebocc_eta_2->Draw("same");
  ebocc_eta_1->SetXTitle("#eta index");
  ebocc_eta_1->SetYTitle("Occupancy");


  TLegend leg1a(0.2,0.65,0.4,0.83);
  leg1a.SetBorderSize(0);
  leg1a.SetFillStyle(0);
  leg1a.AddEntry(eep_spect_1,"OLD","l");
  leg1a.AddEntry(eep_spect_2,"NEW","l");



  leg1a.Draw();


  t1.DrawLatex(0.5,0.92,"Emulated TP Occupancy vs #eta: EB");
  c1.SaveAs("./validationplots_nov2/eb_occ_vs_eta_2015vs2013.png");

      
  eboccrat_eta->SetLineColor(1);
  eboccrat_eta->SetLineStyle(1);
  eboccrat_eta->SetLineWidth(2);
 
  eboccrat_eta->SetMinimum(0.9);
  //  eboccrat_eta->SetMaximum(1.5);
  eboccrat_eta->SetMaximum(1.1);

  eboccrat_eta->SetXTitle("#eta index");
  eboccrat_eta->SetYTitle("Ratio: NEW/OLD");
  eboccrat_eta->Draw();
 

  t1.DrawLatex(0.5,0.92,"EB Emulated TP Occupancy vs #eta: NEW/OLD");
  c1.SaveAs("./validationplots_nov2/eb_occ_ratio_vs_eta_2015vs2013.png");



  TCanvas c5("c5","",10,10,800,600);
  c5.SetLogy(1);
  gStyle->SetOptStat(1111110);
  eb_occrat_1d->SetXTitle("Occupancy ratio");
  eb_occrat_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EB");
  c5.SaveAs("./validationplots_nov2/eb_occ_ratio_1d_2015vs2013.png");

  c5.SetLogx(1);

  //Orignial ones have the plot range only from 0.8 to 20 

  eep_occrat_1d->GetXaxis()->SetRangeUser(0.4,20);
  eep_occrat_1d->SetXTitle("Occupancy ratio");
  eep_occrat_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE+");
  c5.SaveAs("./validationplots_nov2/eep_occ_ratio_1d_2015vs2013.png");

  eep_occrat_etabin1_1d->GetXaxis()->SetRangeUser(0.4,20);
  eep_occrat_etabin1_1d->SetXTitle("Occupancy ratio");
  eep_occrat_etabin1_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE+, 1.5<|#eta|<1.8");
  c5.SaveAs("./validationplots_nov2/eep_occ_ratio_1d_etabin1_2015vs2013.png");

  eep_occrat_etabin2_1d->GetXaxis()->SetRangeUser(0.4,20);
  eep_occrat_etabin2_1d->SetXTitle("Occupancy ratio");
  eep_occrat_etabin2_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE+, 1.8<|#eta|<2.1");
  c5.SaveAs("./validationplots_nov2/eep_occ_ratio_1d_etabin2_2015vs2013.png");

  eep_occrat_etabin3_1d->GetXaxis()->SetRangeUser(0.4,20);
  eep_occrat_etabin3_1d->SetXTitle("Occupancy ratio");
  eep_occrat_etabin3_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE+, 2.1<|#eta|<2.4");
  c5.SaveAs("./validationplots_nov2/eep_occ_ratio_1d_etabin3_2015vs2013.png");

  eep_occrat_etabin4_1d->GetXaxis()->SetRangeUser(0.4,20);
  eep_occrat_etabin4_1d->SetXTitle("Occupancy ratio");
  eep_occrat_etabin4_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE+, 2.4<|#eta|<2.7");
  c5.SaveAs("./validationplots_nov2/eep_occ_ratio_1d_etabin4_2015vs2013.png");

  eep_occrat_etabin5_1d->GetXaxis()->SetRangeUser(0.4,20);
  eep_occrat_etabin5_1d->SetXTitle("Occupancy ratio");
  eep_occrat_etabin5_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE+, |#eta|>2.7");
  c5.SaveAs("./validationplots_nov2/eep_occ_ratio_1d_etabin5_2015vs2013.png");


  eem_occrat_1d->GetXaxis()->SetRangeUser(0.4,20);
  eem_occrat_1d->SetXTitle("Occupancy ratio");
  eem_occrat_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE-");
  c5.SaveAs("./validationplots_nov2/eem_occ_ratio_1d_2015vs2013.png");

  eem_occrat_etabin1_1d->GetXaxis()->SetRangeUser(0.4,20);
  eem_occrat_etabin1_1d->SetXTitle("Occupancy ratio");
  eem_occrat_etabin1_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE-, 1.5<|#eta|<1.8");
  c5.SaveAs("./validationplots_nov2/eem_occ_ratio_1d_etabin1_2015vs2013.png");

  eem_occrat_etabin2_1d->GetXaxis()->SetRangeUser(0.4,20);
  eem_occrat_etabin2_1d->SetXTitle("Occupancy ratio");
  eem_occrat_etabin2_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE-, 1.8<|#eta|<2.1");
  c5.SaveAs("./validationplots_nov2/eem_occ_ratio_1d_etabin2_2015vs2013.png");

  eem_occrat_etabin3_1d->GetXaxis()->SetRangeUser(0.4,20);
  eem_occrat_etabin3_1d->SetXTitle("Occupancy ratio");
  eem_occrat_etabin3_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE-, 2.1<|#eta|<2.4");
  c5.SaveAs("./validationplots_nov2/eem_occ_ratio_1d_etabin3_2015vs2013.png");

  eem_occrat_etabin4_1d->GetXaxis()->SetRangeUser(0.4,20);
  eem_occrat_etabin4_1d->SetXTitle("Occupancy ratio");
  eem_occrat_etabin4_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE-, 2.4<|#eta|<2.7");
  c5.SaveAs("./validationplots_nov2/eem_occ_ratio_1d_etabin4_2015vs2013.png");

  eem_occrat_etabin5_1d->GetXaxis()->SetRangeUser(0.4,20);
  eem_occrat_etabin5_1d->SetXTitle("Occupancy ratio");
  eem_occrat_etabin5_1d->Draw();
  t1.DrawLatex(0.5,0.92,"EE-, |#eta|>2.7");
  c5.SaveAs("./validationplots_nov2/eem_occ_ratio_1d_etabin5_2015vs2013.png");







}
