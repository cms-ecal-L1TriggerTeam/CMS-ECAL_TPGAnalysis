void DrawTPGplots(Char_t* infile = 0, Int_t runNum=0, Bool_t printPics = kTRUE, Char_t* fileType = "png", Char_t* dirName = ".",int trigger=0) 
{

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0); 
  gStyle->SetOptStat(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadRightMargin(0.15);
  //  gStyle->SetPadTopMargin(0.04);
  //  gStyle->SetPadBottomMargin(0.16);

  if (!infile) {
    cout << " No input file specified !" << endl;
    return;
  }

  cout << "Producing TPG plots for: " << infile << endl;

  TFile* f = new TFile(infile);
  Char_t fname[2000];
  char name[2000];

  vector<string> RCT_EB;
  RCT_EB.push_back("maskedRCTEB");
  const int num_RCTEB = RCT_EB.size();

  vector<string> RCT_EE;
  RCT_EE.push_back("maskedRCTEEPlus");
  RCT_EE.push_back("maskedRCTEEMinus");
  const int num_RCTEE = RCT_EE.size();

   vector<string> TP_Plots;

  TP_Plots.push_back("TPEB");
  TP_Plots.push_back("TPEmulEB");
  TP_Plots.push_back("TPEmulMaxEB");
  TP_Plots.push_back("TPMatchEmulEB");
  TP_Plots.push_back("TPEmulMaxIndexEB");

  TP_Plots.push_back("TPEEPlus");
  TP_Plots.push_back("TPEmulEEPlus");
  TP_Plots.push_back("TPEmulMaxEEPlus");
  TP_Plots.push_back("TPMatchEmulEEPlus");
  TP_Plots.push_back("TPEmulMaxIndexEEPlus");

  TP_Plots.push_back("TPEEMinus");
  TP_Plots.push_back("TPEmulEEMinus");
  TP_Plots.push_back("TPEmulMaxEEMinus");
  TP_Plots.push_back("TPMatchEmulEEMinus");
  TP_Plots.push_back("TPEmulMaxIndexEEMinus");

  TP_Plots.push_back("bx");
  TP_Plots.push_back("eventNb");
  TP_Plots.push_back("orbit");
  TP_Plots.push_back("occupancyTP_vs_EvtNb");
  TP_Plots.push_back("TPEtaEB");
  TP_Plots.push_back("TPPhiEB");
  TP_Plots.push_back("TPEtaEEPlus");
  TP_Plots.push_back("TPPhiEEPlus");
  TP_Plots.push_back("TPEtaEEMinus");
  TP_Plots.push_back("TPPhiEEMinus");
  TP_Plots.push_back("TimeStamp");
  TP_Plots.push_back("FiredTriggers");
  TP_Plots.push_back("triggerBit");
//   TP_Plots.push_back("L1Isotiming");
//   TP_Plots.push_back("L1Nonisotiming");



 const int num_TP = TP_Plots.size();  

  vector<string> L1_Plots;

  L1_Plots.push_back("L1Isotiming");
  L1_Plots.push_back("L1Nonisotiming");
  L1_Plots.push_back("L1IsotimingEB");
  L1_Plots.push_back("L1NonisotimingEB");
  L1_Plots.push_back("L1IsotimingEEPlus");
  L1_Plots.push_back("L1NonisotimingEEPlus");
  L1_Plots.push_back("L1IsotimingEEMinus");
  L1_Plots.push_back("L1NonisotimingEEMinus");



  const int num_L1 = L1_Plots.size();
  


  vector<string> TimingOccupancy_Plots;
  TimingOccupancy_Plots.push_back("TP_vs_bx");
  TimingOccupancy_Plots.push_back("TPEmul_vs_bx");
  TimingOccupancy_Plots.push_back("Orbit_vs_bx");
  TimingOccupancy_Plots.push_back("TriggerBit_vs_bx");
  TimingOccupancy_Plots.push_back("iEta_vs_Time");
  TimingOccupancy_Plots.push_back("iPhi_vs_Time");
  const int num_TimingOccupancy = TimingOccupancy_Plots.size();



  vector<string> BarrelOccupancy_Plots;
  BarrelOccupancy_Plots.push_back("occupancyTPEB");
  BarrelOccupancy_Plots.push_back("occupancyTPEmulEB");
  BarrelOccupancy_Plots.push_back("TPspectrumMapEB");  
  BarrelOccupancy_Plots.push_back("TPTimingEBFromEmulOK");  
  BarrelOccupancy_Plots.push_back("TPTimingEBFromEmulWrong");  
  BarrelOccupancy_Plots.push_back("TPTimingEBFromEmulOKAndMatch");  
  //BarrelOccupancy_Plots.push_back("L1MissingTPIsoEB");  
  //BarrelOccupancy_Plots.push_back("L1MissingTPNonisoEB");  
  BarrelOccupancy_Plots.push_back("occupancyL1IsoEB");
  BarrelOccupancy_Plots.push_back("occupancyL1NonisoEB");
  BarrelOccupancy_Plots.push_back("occupancyL1preIsoEB");
  BarrelOccupancy_Plots.push_back("occupancyL1preNonisoEB");
  BarrelOccupancy_Plots.push_back("occupancyL1postIsoEB");
  BarrelOccupancy_Plots.push_back("occupancyL1postNonisoEB");
  BarrelOccupancy_Plots.push_back("TPCompEmulEB");
  BarrelOccupancy_Plots.push_back("L1RatioTPIsoEB");
  BarrelOccupancy_Plots.push_back("L1RatioTPNonisoEB");
  BarrelOccupancy_Plots.push_back("L1TPCompIsoEB");
  BarrelOccupancy_Plots.push_back("L1TPCompNonisoEB");
  const int num_BarrelOccupancy = BarrelOccupancy_Plots.size();



  vector<string> EndcapOccupancy_Plots;
  EndcapOccupancy_Plots.push_back("occupancyTPEEPlus");
  EndcapOccupancy_Plots.push_back("occupancyTPEmulEEPlus");
  EndcapOccupancy_Plots.push_back("TPspectrumMapEEPlus");

  EndcapOccupancy_Plots.push_back("occupancyTPEEMinus");
  EndcapOccupancy_Plots.push_back("occupancyTPEmulEEMinus");
  EndcapOccupancy_Plots.push_back("TPspectrumMapEEMinus");

  EndcapOccupancy_Plots.push_back("TPTimingEEPlusFromEmulOK");  
  EndcapOccupancy_Plots.push_back("TPTimingEEPlusFromEmulWrong");  
  EndcapOccupancy_Plots.push_back("TPTimingEEPlusFromEmulOKAndMatch");  

  EndcapOccupancy_Plots.push_back("TPTimingEEMinusFromEmulOK");  
  EndcapOccupancy_Plots.push_back("TPTimingEEMinusFromEmulWrong");  
  EndcapOccupancy_Plots.push_back("TPTimingEEMinusFromEmulOKAndMatch"); 

  //EndcapOccupancy_Plots.push_back("L1MissingTPIsoEEPlus");
  //EndcapOccupancy_Plots.push_back("L1MissingTPIsoEEMinus");
  //EndcapOccupancy_Plots.push_back("L1MissingTPNonisoEEPlus");
  //EndcapOccupancy_Plots.push_back("L1MissingTPNonisoEEMinus");

  EndcapOccupancy_Plots.push_back("occupancyL1IsoEEPlus");
  EndcapOccupancy_Plots.push_back("occupancyL1IsoEEMinus");
  EndcapOccupancy_Plots.push_back("occupancyL1NonisoEEPlus");
  EndcapOccupancy_Plots.push_back("occupancyL1NonisoEEMinus");

  EndcapOccupancy_Plots.push_back("occupancyL1preIsoEEPlus");
  EndcapOccupancy_Plots.push_back("occupancyL1preIsoEEMinus");
  EndcapOccupancy_Plots.push_back("occupancyL1preNonisoEEPlus");
  EndcapOccupancy_Plots.push_back("occupancyL1preNonisoEEMinus");

  EndcapOccupancy_Plots.push_back("occupancyL1postIsoEEPlus");
  EndcapOccupancy_Plots.push_back("occupancyL1postIsoEEMinus");
  EndcapOccupancy_Plots.push_back("occupancyL1postNonisoEEPlus");
  EndcapOccupancy_Plots.push_back("occupancyL1postNonisoEEMinus");

  EndcapOccupancy_Plots.push_back("TPCompEmulEEPlus");
  EndcapOccupancy_Plots.push_back("TPCompEmulEEMinus");

  EndcapOccupancy_Plots.push_back("L1RatioTPIsoEEPlus");
  EndcapOccupancy_Plots.push_back("L1RatioTPIsoEEMinus");
  EndcapOccupancy_Plots.push_back("L1RatioTPNonisoEEPlus");
  EndcapOccupancy_Plots.push_back("L1RatioTPNonisoEEMinus");

  EndcapOccupancy_Plots.push_back("L1TPCompIsoEEPlus");
  EndcapOccupancy_Plots.push_back("L1TPCompIsoEEMinus");
  EndcapOccupancy_Plots.push_back("L1TPCompNonisoEEPlus");
  EndcapOccupancy_Plots.push_back("L1TPCompNonisoEEMinus");


  const int num_EndcapOccupancy = EndcapOccupancy_Plots.size();

  vector<string> match_barrel_2F_Plots;
  match_barrel_2F_Plots.push_back("TPMatchEmulEB2D");
  match_barrel_2F_Plots.push_back("TPEmulMapMaxIndexEB");
  const int num_barrel_match_2F = match_barrel_2F_Plots.size();
  

  vector<string> match_barrel_fr_2F_Plots;
  match_barrel_fr_2F_Plots.push_back("TPMatchFractionEB2D");
  match_barrel_fr_2F_Plots.push_back("TPMatchFraction2EB2D");
  match_barrel_fr_2F_Plots.push_back("L1FractionMissingTPIsoEB");  
  match_barrel_fr_2F_Plots.push_back("L1FractionMissingTPNonisoEB");  

  const int num_barrel_match_fr_2F = match_barrel_fr_2F_Plots.size();

  

  vector<string> match_endcap_2F_Plots;
  match_endcap_2F_Plots.push_back("TPMatchEmulEEPlus2D");
  match_endcap_2F_Plots.push_back("TPMatchEmulEEMinus2D");
  match_endcap_2F_Plots.push_back("TPEmulMapMaxIndexEEPlus");
  match_endcap_2F_Plots.push_back("TPEmulMapMaxIndexEEMinus");

  const int num_endcap_match_2F = match_endcap_2F_Plots.size();


  vector<string> match_endcap_fr_2F_Plots;
  match_endcap_fr_2F_Plots.push_back("TPMatchFractionEEPlus2D");
  match_endcap_fr_2F_Plots.push_back("TPMatchFraction2EEPlus2D");
  match_endcap_fr_2F_Plots.push_back("TPMatchFractionEEMinus2D");
  match_endcap_fr_2F_Plots.push_back("TPMatchFraction2EEMinus2D");
  match_endcap_fr_2F_Plots.push_back("L1FractionMissingTPIsoEEPlus");
  match_endcap_fr_2F_Plots.push_back("L1FractionMissingTPIsoEEMinus");
  match_endcap_fr_2F_Plots.push_back("L1FractionMissingTPNonisoEEPlus");
  match_endcap_fr_2F_Plots.push_back("L1FractionMissingTPNonisoEEMinus");
 
  const int num_endcap_match_fr_2F = match_endcap_fr_2F_Plots.size();


  vector<string> ttf_2I_Plots; 
  ttf_2I_Plots.push_back("ttfMismatchEB"); 
  ttf_2I_Plots.push_back("ttfMismatchEEPlus"); 
  ttf_2I_Plots.push_back("ttfMismatchEEMinus"); 
  const int num_ttf_2I = ttf_2I_Plots.size();


  TCanvas* can_RCTEB[num_RCTEB];
  TCanvas* can_RCTEE[num_RCTEE];
  TCanvas* can_TP[num_TP];
  TCanvas* can_L1[num_L1];
  TCanvas* can_TimingOccupancy[num_TimingOccupancy];
  TCanvas* can_EndcapOccupancy[num_EndcapOccupancy];
  TCanvas* can_BarrelOccupancy[num_BarrelOccupancy];
  TCanvas* can_barrel_match_2F[num_barrel_match_2F]; 
  TCanvas* can_barrel_match_fr_2F[num_barrel_match_fr_2F];
  TCanvas* can_endcap_match_2F[num_endcap_match_2F]; 
  TCanvas* can_endcap_match_fr_2F[num_endcap_match_fr_2F]; 
  TCanvas* can_ttf_2I[num_ttf_2I]; 

  char cname[200];

  int Canvas_size_w = 1050;
  int Canvas_size_h = 750;
  int Canvas_size_Lx = 1150;
  int Canvas_size_Ly = 1100;


  TH2I * label = new TH2I("label", "",72, 1, 73, 38, -19, 19) ;
  label->SetMarkerSize(0.6);
  label->SetBit(kCanDelete);
  for (int x=3 ; x<73 ; x+=4) {
    for (int y=21; y<=37; y++) {
      int towernb = 4*(y-21)+1 ;
      label->SetBinContent(x-1, y, towernb) ; //EB+
      label->SetBinContent(x, 40-y, towernb) ; //EB-
    }
  }

  TH2I * label2 = new TH2I("label2", "",100, 1, 101, 100, 1, 101) ;
  label2->SetMarkerSize(0.35);
  
  TH2C * iphilabels = new TH2C("iphilabels", "",121,-10,111,121,-10, 111) ;


  // creating canvases
  for (int i=0; i < num_TP; i++){
    sprintf(cname, "can_TP_%i",i);
    int x = (i%3)*500;     //int x = (i%3)*600;
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600;
    can_TP[i]= new TCanvas(cname,cname,x,y,Canvas_size_w,Canvas_size_h);
  }
  for (int i=0; i < num_L1; i++){
    sprintf(cname, "can_L1_%i",i);
    int x = (i%3)*500;     //int x = (i%3)*600;
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600;
    can_L1[i]= new TCanvas(cname,cname,x,y,Canvas_size_w,Canvas_size_h);
  }
  for (int i=0; i < num_TimingOccupancy; i++){
    sprintf(cname, "can_TimingOccupancy_%i",i);
    int x = (i%3)*500;     //int x = (i%3)*600;
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600;
    can_TimingOccupancy[i]= new TCanvas(cname,cname,x,y,Canvas_size_w,Canvas_size_h);
  }

  for (int i=0; i < num_RCTEB; i++){
    sprintf(cname, "can_RCTEB_%i",i);
    int x = (i%3)*500;     //int x = (i%3)*600;
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600;
    can_RCTEB[i]= new TCanvas(cname,cname,x,y,Canvas_size_w,Canvas_size_h);
  }
  for (int i=0; i < num_RCTEE; i++){
    sprintf(cname, "can_RCTEE_%i",i);
    int x = (i%3)*500;     //int x = (i%3)*600;
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600;
    can_RCTEE[i]= new TCanvas(cname,cname,x,y,Canvas_size_Lx,Canvas_size_Ly);
  }

  for (int i=0; i < num_BarrelOccupancy; i++){
    sprintf(cname, "can_BarrelOccupancy_%i",i);
    int x = (i%3)*500;     //int x = (i%3)*600;
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600;
    can_BarrelOccupancy[i]= new TCanvas(cname,cname,x,y,Canvas_size_w,Canvas_size_h);
  }   
  for (int i=0; i < num_EndcapOccupancy; i++){
    sprintf(cname, "can_EndcapOccupancy_%i",i);
    int x = (i%3)*500;     //int x = (i%3)*600;
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600;
    can_EndcapOccupancy[i]= new TCanvas(cname,cname,x,y,Canvas_size_Lx,Canvas_size_Ly);
  }
  for (int i=0; i < num_barrel_match_2F; i++){ 
    sprintf(cname, "can_barrel_match_2F_%i",i); 
    int x = (i%3)*500;     //int x = (i%3)*600; 
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600; 
    can_barrel_match_2F[i]= new TCanvas(cname,cname,x,y,Canvas_size_w,Canvas_size_h); 
  }
  for (int i=0; i < num_barrel_match_fr_2F; i++){ 
    sprintf(cname, "can_barrel_match_fr_2F_%i",i); 
    int x = (i%3)*500;     //int x = (i%3)*600; 
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600; 
    can_barrel_match_fr_2F[i]= new TCanvas(cname,cname,x,y,Canvas_size_w,Canvas_size_h); 
  }
  for (int i=0; i < num_endcap_match_2F; i++){ 
    sprintf(cname, "can_endcap_match_2F_%i",i); 
    int x = (i%3)*500;     //int x = (i%3)*600; 
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600; 
    can_endcap_match_2F[i]= new TCanvas(cname,cname,x,y,Canvas_size_Lx,Canvas_size_Ly); 
  }
  for (int i=0; i < num_endcap_match_fr_2F; i++){ 
    sprintf(cname, "can_endcap_match_fr_2F_%i",i); 
    int x = (i%3)*500;     //int x = (i%3)*600; 
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600; 
    can_endcap_match_fr_2F[i]= new TCanvas(cname,cname,x,y,Canvas_size_Lx,Canvas_size_Ly); 
  }
  for (int i=1; i < num_ttf_2I; i++){ 
    sprintf(cname, "can_ttf_2I_%i",i);
    int x = (i%3)*500;     //int x = (i%3)*600;
    int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600;
    can_ttf_2I[i] = new TCanvas(cname,cname,x,y,Canvas_size_Lx,Canvas_size_Ly);
  }
  sprintf(cname, "can_ttf_2I_0",0);
  int x = (i%3)*500;     //int x = (i%3)*600;
  int y = (i/3)*100;     //int y = (i/3)*200;    int x = (i%3)*500;     //int x = (i%3)*600;
  can_ttf_2I[0] = new TCanvas(cname,cname,x,y,Canvas_size_w,Canvas_size_h);

  

  // drawing histos


  for (int ic=0; ic<num_TP; ic++) {
    sprintf(fname,TP_Plots[ic].c_str());
    draw_TP(fname,can_TP[ic],f,runNum);
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_TP[ic]->Print(name);}
  } 


    for (int ic=0; ic<num_L1; ic++) {
    sprintf(fname,L1_Plots[ic].c_str());
    draw_TP(fname,can_L1[ic],f,runNum);
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_L1[ic]->Print(name);}
  } 
  for (int ic=0; ic<num_TimingOccupancy; ic++) {
    sprintf(fname,TimingOccupancy_Plots[ic].c_str());
    draw_TimingOccupancy(fname,can_TimingOccupancy[ic],f,runNum);
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_TimingOccupancy[ic]->Print(name);}
  }

  //////barrel

  for (int ic=0; ic<num_RCTEB; ic++) {
    sprintf(fname,RCT_EB[ic].c_str());
    draw_RCTEB(fname,can_RCTEB[ic],f,runNum, label);
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_RCTEB[ic]->Print(name);}
  }


  for (int ic=0; ic<num_BarrelOccupancy; ic++) {
    sprintf(fname,BarrelOccupancy_Plots[ic].c_str());
    draw_BarrelOccupancy(fname,can_BarrelOccupancy[ic],f,runNum, label);
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_BarrelOccupancy[ic]->Print(name);}
  }

  for (int ic=0; ic<num_barrel_match_2F; ic++) { 
    sprintf(fname,match_barrel_2F_Plots[ic].c_str()); 
    draw_BarrelOccupancy(fname,can_barrel_match_2F[ic],f,runNum, label); 
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_barrel_match_2F[ic]->Print(name);} 
  }

  for (int ic=0; ic<num_barrel_match_fr_2F; ic++) { 
    sprintf(fname,match_barrel_fr_2F_Plots[ic].c_str());
    draw_BarrelOccupancy(fname,can_barrel_match_fr_2F[ic],f,runNum, label); 
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_barrel_match_fr_2F[ic]->Print(name);} 
  }
  
  sprintf(fname,ttf_2I_Plots[0].c_str());  
  draw_BarrelOccupancy(fname,can_ttf_2I[0],f,runNum, label);  
  if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_ttf_2I[0]->Print(name);} 


  //////endcaps

  for (int ic=0; ic<num_RCTEE; ic++) {
    sprintf(fname,RCT_EE[ic].c_str());
    draw_RCTEE(fname,can_RCTEE[ic],f,runNum, label2,iphilabels);
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_RCTEE[ic]->Print(name);}
  }

  for (int ic=0; ic<num_EndcapOccupancy; ic++) {
    sprintf(fname,EndcapOccupancy_Plots[ic].c_str());
    draw_EndcapOccupancy(fname,can_EndcapOccupancy[ic],f,runNum, label2,iphilabels);
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_EndcapOccupancy[ic]->Print(name);}
  }
  
  for (int ic=0; ic<num_endcap_match_2F; ic++) { 
    sprintf(fname,match_endcap_2F_Plots[ic].c_str()); 
    draw_EndcapOccupancy(fname,can_endcap_match_2F[ic],f,runNum, label2,iphilabels); 
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_endcap_match_2F[ic]->Print(name);} 
  }

  for (int ic=0; ic<num_endcap_match_fr_2F; ic++) { 
    sprintf(fname,match_endcap_fr_2F_Plots[ic].c_str());
    draw_EndcapOccupancy(fname,can_endcap_match_fr_2F[ic],f,runNum, label2,iphilabels); 
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_endcap_match_fr_2F[ic]->Print(name);} 
  }

   for (int ic=1; ic<num_ttf_2I; ic++) {   
    sprintf(fname,ttf_2I_Plots[ic].c_str());  
    draw_EndcapOccupancy(fname,can_ttf_2I[ic],f,runNum, label2,iphilabels);  
    if (printPics) { sprintf(name,"%s/TPGAnalysis_%s_%i_%i.%s",dirName,fname,trigger,runNum,fileType); can_ttf_2I[ic]->Print(name);} 
  } 


  return;
}




void draw_TP(Char_t* fname, TCanvas* c, TFile* f, int runNum) 
{

  c->cd();
  char runChar[50];  sprintf(runChar,", run %i",runNum);
  char hname[200]; 
  gStyle->SetOptStat(111);
  TH1F* h1 = (TH1F*)f->Get(fname);
  if(h1->GetEntries()!=0) c->SetLogy(); 
  h1->Draw(); 
  char mytitle[100]; 
  sprintf(mytitle,"%s",h1->GetTitle());
  strcat(mytitle,runChar);
  h1->SetTitle(mytitle);
  return;
}




void draw_TimingOccupancy(Char_t* fname, TCanvas* c, TFile* f, int runNum)
{
  c->cd();
  char runChar[50];  sprintf(runChar,", run %i",runNum);
  char hname[200];
  
  gStyle->SetOptStat(10);
  gStyle->SetPalette(1);
  
  TH2F* h1 = (TH2F*)f->Get(fname);
  if ( h1->GetEntries()!=0) c->SetLogz();  
  h1->Draw("colz");
  char mytitle[100]; 
  sprintf(mytitle,"%s",h1->GetTitle()); 
  strcat(mytitle,runChar);
  h1->SetTitle(mytitle);
  
  return;
}


void draw_RCTEB(Char_t* fname, TCanvas* c, TFile* f, int runNum, TH2I* label) 
{
    
  c->cd();
  char runChar[50];  sprintf(runChar,", run %i",runNum);
  char hname[200];

  gStyle->SetOptStat(10);
  
  TH2F* h1 = (TH2F*)f->Get(fname);

  h1->Draw("colz");

  if(string(fname).find("maskedRCT")!= std::string::npos){
    //int color[10]={12,10,3,4,5,6,7} ; 
    gStyle->SetPalette(5) ;
    gStyle->SetOptStat(0);
  }
  else gStyle->SetPalette(1,0);

  char mytitle[100]; 
  sprintf(mytitle,"%s",h1->GetTitle()); 
  strcat(mytitle,runChar);
  h1->SetTitle(mytitle);

  TLatex txt;
  txt.SetTextSize(0.02);
  TLine line;
  line.SetLineColor(1) ;
  line.SetLineStyle(1) ;
  line.SetLineWidth(1) ;

  // draw SM borders and numbers
  float sm ;
  for (int i=0; i<36 ; i++ ) {
    if (i<18) {
      sm = 4*i+3 ;
      line.DrawLine(sm, 1, sm, 18) ;
      txt.SetTextAlign(32);
      txt.DrawText(sm-1+0.3, -17.7, Form("-%d",i+1));
    }
    else {
      sm = 4*(i-18)+3 ;
      line.DrawLine(sm, 0, sm, -17) ;
      txt.SetTextAlign(12);
      txt.DrawText(sm-2+0.3, 18.5, Form("+%d",i-17));
    }
  }
  line.DrawLine(1, 0, 73, 0) ;
  line.DrawLine(1, -17, 73, -17) ;
  line.DrawLine(1, 1, 73, 1) ;
  line.DrawLine(1, 18, 73, 18) ;
  
  label->Draw("same text") ;
  
  return;

}




void draw_BarrelOccupancy(Char_t* fname, TCanvas* c, TFile* f, int runNum, TH2I* label) 
{
    
  c->cd();
  char runChar[50];  sprintf(runChar,", run %i",runNum);
  char hname[200];

  gStyle->SetOptStat(10);
  
  TH2F* h1 = (TH2F*)f->Get(fname);

  h1->Draw("colz");

  //applying draw options based on titles of histograms 

  if(string(fname).find("TPMatchEmul")!= std::string::npos){

    //int color[10]={12,10,3,4,5,6,7} ; 
    int color[10]={kGray+2,kWhite,kRed,kOrange,kGreen,kAzure,kViolet} ;
    gStyle->SetPalette(7, color) ;
    gStyle->SetOptStat(0);
    h1->GetZaxis()->SetRangeUser(-1,6) ;
  }
  else if(string(fname).find("EmulMapMaxIndex")!= std::string::npos){
    //int color[10]={12,10,3,4,5,6,7} ; 
    int color[10]={kGray+2,kWhite,kRed,kOrange,kGreen,kAzure,kViolet} ;
    gStyle->SetPalette(7, color) ;
    gStyle->SetOptStat(0);
    h1->GetZaxis()->SetRangeUser(-1,6) ;
  }
  else gStyle->SetPalette(1,0);
  

  if(string(fname).find("Fraction")!= std::string::npos){
    gStyle->SetOptStat(0);
  }

  if(string(fname).find("L1Ratio")!= std::string::npos){
    h1->SetMinimum(0);
    h1->SetMaximum(1.5);
    //if(h1->GetEntries()!=0)  c->SetLogz();
  }

  if(string(fname).find("spectrum")!= std::string::npos){
    h1->SetMinimum(0);
    h1->SetMaximum(256);
    if(h1->GetEntries()!=0)  c->SetLogz();
  }
  else if(string(fname).find("occupancy")!= std::string::npos){
    if(h1->GetEntries()!=0)  c->SetLogz();
  }
  else if(string(fname).find("TPComp")!= std::string::npos){
    if(h1->GetEntries()!=0)  c->SetLogz();
  }

  TH2F* Mask = (TH2F*)f->Get("MaskedTowersEB");
 

  gStyle->SetHatchesSpacing(1.3);
  gStyle->SetHatchesLineWidth(0.05);

  for(int x=1;x!=Mask->GetNbinsX();++x){
    for(int y=1;y!=Mask->GetNbinsY();++y){
      if(Mask->GetBinContent(x,y)!=0){
	TBox b;
	b.SetFillStyle(3144);
	b.SetFillColor(1);
	b.DrawBox(x,y-20,x+1,y-19);
      }
    }
  }



  TH2F* MaskR = (TH2F*)f->Get("MaskedReadOutEB");
 

  //gStyle->SetHatchesSpacing(2.);
  //gStyle->SetHatchesLineWidth(0.2);

  for(int x=1;x!=MaskR->GetNbinsX();++x){
    for(int y=1;y!=MaskR->GetNbinsY();++y){
      if(MaskR->GetBinContent(x,y)!=0){
	TBox bR;
	bR.SetFillStyle(3109);
	bR.SetFillColor(1);
	bR.DrawBox(x,y-20,x+1,y-19);
      }
    }
  }





  char mytitle[100]; 
  sprintf(mytitle,"%s",h1->GetTitle()); 
  strcat(mytitle,runChar);
  h1->SetTitle(mytitle);

  TLatex txt;
  txt.SetTextSize(0.02);
  TLine line;
  line.SetLineColor(1) ;
  line.SetLineStyle(1) ;
  line.SetLineWidth(1) ;

  // draw SM borders and numbers
  float sm ;
  for (int i=0; i<36 ; i++ ) {
    if (i<18) {
      sm = 4*i+3 ;
      line.DrawLine(sm, 1, sm, 18) ;
      txt.SetTextAlign(32);
      txt.DrawText(sm-1+0.3, -17.7, Form("-%d",i+1));
    }
    else {
      sm = 4*(i-18)+3 ;
      line.DrawLine(sm, 0, sm, -17) ;
      txt.SetTextAlign(12);
      txt.DrawText(sm-2+0.3, 18.5, Form("+%d",i-17));
    }
  }
  line.DrawLine(1, 0, 73, 0) ;
  line.DrawLine(1, -17, 73, -17) ;
  line.DrawLine(1, 1, 73, 1) ;
  line.DrawLine(1, 18, 73, 18) ;
  
  label->Draw("same text") ;
  
  return;
}



void draw_RCTEE(Char_t* fname, TCanvas* c, TFile* f, int runNum, TH2I* label2, TH2C* iphilabels) 
{
  //printf("helloendcapoccupancy\n");


  c->cd();
  char runChar[50];  sprintf(runChar,", run %i",runNum);
  char hname[200];
  
  gStyle->SetOptStat(10);


  TH2F* h1 = (TH2F*)f->Get(fname);
  
  h1->Draw("colz");


  if(string(fname).find("maskedRCT")!= std::string::npos){
    //int color[10]={12,10,3,4,5,6,7} ; 
    gStyle->SetPalette(5) ;
    gStyle->SetOptStat(0);
  }
  else gStyle->SetPalette(1,0);


  char mytitle[100]; 
  sprintf(mytitle,"%s",h1->GetTitle()); 
  strcat(mytitle,runChar);
  h1->SetTitle(mytitle);



  TLine line2;
  //line.SetLineColor(1) ;  
  //line.SetLineStyle(1) ;  
  //line.SetLineWidth(1) ;

  

//drawing TT boundaries
  
  //note: for TTs each list is split into two because as one giant list root complains that there are too many arguments
  
  int ixTTEEHorizontal1[1381] = {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
  
  int ixTTEEHorizontal2[1386] = {51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 100, 100, 100, 100, 100};
  
  
  
  int iyTTEEHorizontal1[1381] = {42, 46, 51, 56, 60, 61, 42, 46, 51, 56, 60, 61, 42, 46, 51, 56, 60, 61, 39, 42, 44, 46, 51, 56, 58, 60, 63, 66, 38, 42, 43, 46, 51, 56, 59, 60, 64, 66, 31, 34, 39, 43, 48, 51, 54, 59, 63, 68, 71, 76, 31, 33, 35, 39, 43, 44, 48, 50, 51, 52, 54, 58, 59, 63, 67, 69, 71, 76, 29, 31, 35, 39, 40, 42, 43, 46, 47, 48, 51, 54, 55, 56, 59, 60, 62, 63, 67, 71, 73, 76, 23, 26, 27, 31, 35, 36, 37, 38, 39, 43, 48, 51, 54, 59, 63, 64, 65, 66, 67, 71, 75, 76, 79, 81, 24, 26, 27, 31, 36, 39, 43, 48, 51, 54, 59, 63, 66, 71, 75, 76, 78, 81, 24, 28, 31, 32, 36, 41, 43, 46, 51, 56, 59, 61, 66, 70, 71, 74, 78, 81, 22, 24, 29, 31, 33, 36, 41, 44, 46, 47, 51, 55, 56, 58, 61, 66, 69, 71, 73, 78, 80, 81, 22, 25, 29, 33, 36, 38, 41, 44, 47, 51, 55, 58, 61, 64, 66, 69, 73, 77, 80, 81, 19, 21, 26, 28, 29, 34, 37, 41, 44, 48, 50, 51, 52, 54, 58, 61, 65, 68, 73, 74, 76, 81, 83, 86, 18, 21, 26, 30, 33, 38, 41, 45, 47, 51, 55, 57, 61, 64, 69, 72, 76, 81, 84, 86, 16, 22, 25, 27, 31, 36, 39, 42, 44, 48, 51, 54, 58, 60, 63, 66, 71, 75, 77, 80, 85, 86, 88, 16, 17, 22, 24, 27, 31, 32, 36, 38, 42, 44, 48, 49, 51, 53, 54, 58, 60, 64, 66, 70, 71, 75, 78, 80, 84, 86, 88, 15, 19, 23, 24, 28, 30, 32, 36, 39, 42, 45, 47, 48, 51, 54, 55, 57, 60, 63, 66, 70, 72, 74, 78, 79, 84, 87, 88, 19, 22, 26, 27, 29, 33, 35, 36, 39, 42, 45, 46, 48, 51, 54, 56, 57, 60, 63, 66, 67, 69, 73, 75, 76, 80, 81, 88, 19, 21, 26, 29, 32, 36, 40, 42, 46, 48, 51, 54, 56, 60, 62, 66, 70, 73, 76, 81, 88, 14, 16, 20, 22, 25, 26, 30, 31, 33, 36, 37, 41, 43, 46, 48, 51, 54, 56, 59, 61, 65, 66, 69, 71, 72, 76, 77, 81, 82, 86, 88, 93, 12, 18, 19, 22, 24, 28, 29, 31, 34, 36, 38, 41, 44, 46, 49, 51, 53, 56, 58, 61, 64, 66, 68, 71, 73, 74, 78, 79, 83, 84, 90, 93, 10, 12, 18, 23, 24, 28, 31, 35, 36, 38, 41, 44, 46, 49, 51, 53, 56, 58, 61, 64, 66, 67, 71, 74, 79, 84, 90, 92, 93, 11, 13, 17, 19, 22, 26, 27, 28, 31, 33, 34, 36, 39, 41, 44, 46, 49, 51, 53, 56, 58, 61, 63, 66, 68, 69, 71, 74, 75, 78, 80, 83, 85, 89, 91, 93, 11, 14, 16, 19, 21, 26, 30, 31, 34, 36, 38, 41, 45, 46, 50, 51, 52, 56, 57, 61, 64, 66, 68, 71, 72, 76, 78, 81, 83, 86, 88, 91, 93, 11, 15, 16, 20, 22, 25, 27, 30, 31, 34, 37, 39, 41, 42, 45, 47, 49, 51, 53, 55, 57, 60, 61, 63, 65, 68, 71, 73, 76, 77, 80, 82, 86, 87, 91, 96, 9, 11, 15, 18, 19, 22, 24, 28, 30, 31, 33, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 69, 71, 73, 75, 78, 80, 83, 84, 87, 91, 93, 96, 9, 12, 14, 19, 23, 25, 28, 31, 32, 36, 38, 39, 40, 41, 43, 45, 48, 49, 50, 51, 52, 53, 54, 57, 59, 61, 62, 63, 64, 66, 70, 71, 73, 74, 77, 79, 83, 88, 90, 93, 96, 8, 13, 15, 19, 21, 22, 25, 26, 31, 33, 36, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 66, 69, 71, 73, 74, 77, 80, 81, 83, 87, 89, 94, 96, 8, 13, 16, 18, 21, 26, 31, 33, 36, 39, 41, 44, 45, 46, 49, 51, 53, 56, 57, 58, 61, 63, 66, 69, 71, 73, 76, 81, 84, 86, 89, 94, 96, 8, 11, 16, 17, 21, 24, 28, 32, 35, 36, 37, 40, 41, 42, 44, 46, 48, 49, 51, 53, 54, 56, 58, 60, 61, 62, 65, 66, 67, 71, 74, 78, 81, 85, 86, 91, 94, 96, 8, 11, 12, 16, 19, 20, 21, 24, 28, 29, 32, 34, 36, 38, 40, 41, 42, 44, 46, 48, 50, 51, 52, 54, 56, 58, 60, 61, 62, 64, 66, 68, 69, 73, 74, 78, 81, 82, 83, 86, 90, 91, 94, 96, 7, 11, 14, 15, 16, 20, 22, 25, 27, 28, 31, 33, 35, 36, 38, 39, 41, 43, 44, 45, 46, 47, 49, 51, 53, 55, 56, 57, 58, 59, 61, 63, 64, 66, 69, 71, 74, 75, 77, 80, 82, 86, 87, 88, 91, 95, 96, 7, 11, 14, 16, 20, 23, 24, 26, 28, 31, 32, 35, 36, 38, 40, 41, 42, 43, 46, 48, 51, 54, 56, 59, 60, 61, 62, 64, 66, 69, 70, 71, 74, 76, 78, 79, 82, 86, 88, 91, 95, 96, 10, 11, 14, 16, 19, 23, 26, 28, 31, 36, 39, 41, 46, 49, 51, 53, 56, 61, 63, 66, 67, 71, 74, 76, 79, 83, 86, 88, 91, 92, 96, 6, 9, 13, 18, 21, 26, 30, 31, 34, 36, 39, 43, 46, 48, 51, 54, 56, 59, 61, 62, 65, 68, 71, 72, 76, 81, 84, 89, 93, 96, 98, 6, 10, 13, 14, 15, 18, 21, 22, 26, 28, 29, 32, 34, 37, 39, 43, 45, 46, 48, 51, 54, 56, 57, 59, 61, 62, 64, 68, 70, 73, 74, 76, 80, 81, 84, 87, 88, 89, 92, 96, 98, 5, 6, 9, 13, 16, 17, 18, 21, 24, 25, 26, 29, 33, 35, 38, 40, 41, 42, 43, 45, 46, 49, 51, 53, 56, 57, 59, 60, 61, 64, 67, 69, 73, 76, 77, 78, 81, 84, 85, 86, 89, 93, 96, 97, 98, 6, 8, 11, 13, 16, 20, 21, 24, 28, 31, 33, 34, 36, 38, 41, 45, 46, 49, 51, 53, 56, 57, 61, 64, 66, 68, 69, 71, 74, 78, 81, 82, 86, 89, 91, 94, 96, 98, 6, 9, 11, 13, 16, 21, 24, 29, 31, 35, 36, 41, 44, 46, 58, 61, 63, 66, 67, 71, 73, 78, 81, 86, 89, 91, 93, 96, 98, 6, 9, 13, 16, 21, 23, 26, 31, 34, 36, 38, 41, 44, 59, 61, 64, 66, 68, 71, 76, 79, 81, 86, 89, 93, 96, 101, 6, 8, 13, 16, 20, 21, 23, 26, 27, 31, 33, 35, 36, 39, 41, 43, 61, 63, 66, 67, 69, 71, 75, 76, 79, 81, 82, 86, 89, 94, 96, 101, 5, 7, 12, 13, 16, 20, 22, 23, 26, 30, 31, 34, 38, 42, 61, 64, 68, 71, 72, 76, 79, 80, 82, 86, 89, 90, 95, 97, 101, 4, 8, 13, 15, 16, 18, 20, 23, 25, 26, 31, 33, 38, 40, 41, 62, 64, 69, 71, 76, 77, 79, 82, 84, 86, 87, 89, 94, 98, 101, 4, 8, 13, 16, 19, 23, 26, 31, 34, 37, 41, 65, 68, 71, 76, 79, 83, 86, 89, 94, 98, 101, 4, 6, 9, 11, 12, 16, 19, 23, 26, 30, 31, 34, 36, 40, 66, 68, 71, 72, 76, 79, 83, 86, 90, 91, 93, 96, 98, 101, 4, 6, 8, 11, 12, 14, 15, 16, 18, 23, 26, 28, 29, 31, 33, 34, 36, 40, 66, 68, 69, 71, 73, 74, 76, 79, 84, 86, 87, 88, 90, 91, 94, 96, 98, 101, 4, 8, 12, 15, 17, 22, 23, 26, 29, 34, 35, 36, 38, 40, 64, 66, 67, 68, 73, 76, 79, 80, 85, 87, 90, 94, 98, 101, 4, 8, 12, 15, 18, 23, 25, 26, 28, 32, 33, 34, 36, 40, 66, 68, 69, 70, 74, 76, 77, 79, 84, 87, 90, 94, 98, 101, 4, 7, 12, 14, 18, 23, 26, 29, 34, 36, 40, 66, 68, 73, 76, 79, 84, 88, 90, 95, 98, 101};
  
  int iyTTEEHorizontal2[1386] = {4, 7, 12, 14, 18, 23, 26, 29, 34, 36, 40, 66, 68, 73, 76, 79, 84, 88, 90, 95, 98, 101, 4, 8, 12, 15, 18, 23, 25, 26, 28, 32, 33, 34, 36, 40, 66, 68, 69, 70, 74, 76, 77, 79, 84, 87, 90, 94, 98, 101, 4, 8, 12, 15, 17, 22, 23, 26, 29, 34, 35, 36, 38, 40, 64, 66, 67, 68, 73, 76, 79, 80, 85, 87, 90, 94, 98, 101, 4, 6, 8, 11, 12, 14, 15, 16, 18, 23, 26, 28, 29, 31, 33, 34, 36, 40, 66, 68, 69, 71, 73, 74, 76, 79, 84, 86, 87, 88, 90, 91, 94, 96, 98, 101, 4, 6, 9, 11, 12, 16, 19, 23, 26, 30, 31, 34, 36, 40, 66, 68, 71, 72, 76, 79, 83, 86, 90, 91, 93, 96, 98, 101, 4, 8, 13, 16, 19, 23, 26, 31, 34, 37, 41, 65, 68, 71, 76, 79, 83, 86, 89, 94, 98, 101, 4, 8, 13, 15, 16, 18, 20, 23, 25, 26, 31, 33, 38, 40, 41, 62, 64, 69, 71, 76, 77, 79, 82, 84, 86, 87, 89, 94, 98, 101, 5, 7, 12, 13, 16, 20, 22, 23, 26, 30, 31, 34, 38, 41, 42, 64, 68, 71, 72, 76, 79, 80, 82, 86, 89, 90, 95, 97, 101, 6, 8, 13, 16, 20, 21, 23, 26, 27, 31, 33, 35, 36, 39, 41, 43, 61, 63, 66, 67, 69, 71, 75, 76, 79, 81, 82, 86, 89, 94, 96, 101, 6, 9, 13, 16, 21, 23, 26, 31, 34, 36, 38, 41, 43, 44, 61, 64, 66, 68, 71, 76, 79, 81, 86, 89, 93, 96, 101, 6, 9, 11, 13, 16, 21, 24, 29, 31, 35, 36, 39, 41, 44, 46, 58, 61, 66, 67, 71, 73, 78, 81, 86, 89, 91, 93, 96, 98, 6, 8, 11, 13, 16, 20, 21, 24, 28, 31, 33, 34, 36, 38, 41, 45, 46, 49, 51, 53, 56, 57, 61, 64, 66, 68, 69, 71, 74, 78, 81, 82, 86, 89, 91, 94, 96, 98, 5, 6, 9, 13, 16, 17, 18, 21, 24, 25, 26, 29, 33, 35, 38, 41, 42, 43, 45, 46, 49, 51, 53, 56, 57, 59, 60, 61, 62, 64, 67, 69, 73, 76, 77, 78, 81, 84, 85, 86, 89, 93, 96, 97, 98, 6, 10, 13, 14, 15, 18, 21, 22, 26, 28, 29, 32, 34, 38, 40, 41, 43, 45, 46, 48, 51, 54, 56, 57, 59, 63, 65, 68, 70, 73, 74, 76, 80, 81, 84, 87, 88, 89, 92, 96, 98, 6, 9, 13, 18, 21, 26, 30, 31, 34, 37, 40, 41, 43, 46, 48, 51, 54, 56, 59, 63, 66, 68, 71, 72, 76, 81, 84, 89, 93, 96, 98, 10, 11, 14, 16, 19, 23, 26, 28, 31, 35, 36, 39, 41, 46, 49, 51, 53, 56, 61, 63, 66, 71, 74, 76, 79, 83, 86, 88, 91, 92, 96, 7, 11, 14, 16, 20, 23, 24, 26, 28, 31, 32, 33, 36, 38, 40, 41, 42, 43, 46, 48, 51, 54, 56, 59, 60, 61, 62, 64, 66, 67, 70, 71, 74, 76, 78, 79, 82, 86, 88, 91, 95, 96, 7, 11, 14, 15, 16, 20, 22, 25, 27, 28, 31, 33, 36, 38, 39, 41, 43, 44, 45, 46, 47, 49, 51, 53, 55, 56, 57, 58, 59, 61, 63, 64, 66, 67, 69, 71, 74, 75, 77, 80, 82, 86, 87, 88, 91, 95, 96, 8, 11, 12, 16, 19, 20, 21, 24, 28, 29, 33, 34, 36, 38, 40, 41, 42, 44, 46, 48, 50, 51, 52, 54, 56, 58, 60, 61, 62, 64, 66, 68, 70, 73, 74, 78, 81, 82, 83, 86, 90, 91, 94, 96, 8, 11, 16, 17, 21, 24, 28, 31, 35, 36, 37, 40, 41, 42, 44, 46, 48, 49, 51, 53, 54, 56, 58, 60, 61, 62, 65, 66, 67, 70, 74, 78, 81, 85, 86, 91, 94, 96, 8, 13, 16, 18, 21, 26, 29, 31, 33, 36, 39, 41, 44, 45, 46, 49, 51, 53, 56, 57, 58, 61, 63, 66, 69, 71, 76, 81, 84, 86, 89, 94, 96, 8, 13, 15, 19, 21, 22, 25, 28, 29, 31, 33, 36, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 66, 69, 71, 76, 77, 80, 81, 83, 87, 89, 94, 96, 9, 12, 14, 19, 23, 25, 28, 29, 31, 32, 36, 38, 39, 40, 41, 43, 45, 48, 49, 50, 51, 52, 53, 54, 57, 59, 61, 62, 63, 64, 66, 70, 71, 74, 77, 79, 83, 88, 90, 93, 96, 9, 11, 15, 18, 19, 22, 24, 27, 29, 31, 33, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 69, 71, 72, 74, 78, 80, 83, 84, 87, 91, 93, 96, 11, 15, 16, 20, 22, 25, 26, 29, 31, 34, 37, 39, 41, 42, 45, 47, 49, 51, 53, 55, 57, 60, 61, 63, 65, 68, 71, 72, 75, 77, 80, 82, 86, 87, 91, 96, 11, 14, 16, 19, 21, 24, 26, 30, 31, 34, 36, 38, 41, 45, 46, 50, 51, 52, 56, 57, 61, 64, 66, 68, 71, 72, 76, 81, 83, 86, 88, 91, 93, 11, 13, 17, 19, 22, 24, 27, 28, 31, 33, 34, 36, 39, 41, 44, 46, 49, 51, 53, 56, 58, 61, 63, 66, 68, 69, 71, 74, 75, 76, 80, 83, 85, 89, 91, 93, 10, 12, 18, 23, 28, 31, 35, 36, 38, 41, 44, 46, 49, 51, 53, 56, 58, 61, 64, 66, 67, 71, 74, 78, 79, 84, 90, 92, 93, 12, 18, 19, 23, 24, 28, 29, 31, 34, 36, 38, 41, 44, 46, 49, 51, 53, 56, 58, 61, 64, 66, 68, 71, 73, 74, 78, 80, 83, 84, 90, 93, 14, 16, 20, 21, 25, 26, 30, 31, 33, 36, 37, 41, 43, 46, 48, 51, 54, 56, 59, 61, 65, 66, 69, 71, 72, 76, 77, 80, 82, 86, 88, 93, 21, 26, 29, 32, 36, 40, 42, 46, 48, 51, 54, 56, 60, 62, 66, 70, 73, 76, 81, 83, 88, 21, 22, 26, 27, 29, 33, 35, 36, 39, 42, 45, 46, 48, 51, 54, 56, 57, 60, 63, 66, 67, 69, 73, 75, 76, 80, 83, 86, 87, 88, 15, 18, 23, 24, 28, 30, 32, 36, 39, 42, 45, 47, 48, 51, 54, 55, 57, 60, 63, 66, 70, 72, 74, 78, 79, 83, 87, 88, 16, 18, 22, 24, 27, 31, 32, 36, 38, 42, 44, 48, 49, 51, 53, 54, 58, 60, 64, 66, 70, 71, 75, 78, 80, 85, 86, 88, 16, 17, 22, 25, 27, 31, 36, 39, 42, 44, 48, 51, 54, 58, 60, 63, 66, 71, 75, 77, 80, 86, 87, 88, 18, 21, 26, 30, 33, 38, 41, 45, 47, 51, 55, 57, 61, 64, 69, 72, 76, 81, 82, 83, 84, 85, 86, 19, 21, 26, 28, 29, 34, 37, 41, 44, 48, 50, 51, 52, 54, 58, 61, 65, 68, 73, 74, 76, 81, 83, 86, 22, 25, 29, 33, 36, 38, 41, 44, 47, 51, 55, 58, 61, 64, 66, 69, 73, 77, 80, 81, 22, 24, 29, 31, 33, 36, 41, 44, 46, 47, 51, 55, 56, 58, 61, 66, 69, 71, 73, 78, 80, 81, 24, 28, 31, 32, 36, 41, 43, 46, 51, 56, 59, 61, 66, 70, 71, 74, 78, 81, 24, 26, 27, 31, 36, 39, 43, 48, 51, 54, 59, 63, 66, 71, 75, 76, 78, 81, 23, 26, 27, 31, 35, 36, 37, 38, 39, 43, 48, 51, 54, 59, 63, 64, 65, 66, 67, 71, 75, 76, 79, 81, 29, 31, 35, 39, 40, 42, 43, 46, 47, 48, 51, 54, 55, 56, 59, 60, 62, 63, 67, 71, 73, 76, 31, 33, 35, 39, 43, 44, 48, 50, 51, 52, 54, 58, 59, 63, 67, 69, 71, 76, 31, 34, 39, 43, 48, 51, 54, 59, 63, 68, 71, 76, 38, 42, 43, 46, 51, 56, 59, 60, 64, 66, 39, 42, 44, 46, 51, 56, 58, 60, 63, 66, 42, 46, 51, 56, 60, 61, 42, 46, 51, 56, 60, 61, 42, 46, 51, 56, 60};
  
  int ixTTEEVertical1[1381] = {42, 46, 51, 42, 46, 51, 42, 46, 51, 39, 42, 44, 46, 51, 38, 42, 43, 46, 51, 31, 34, 39, 43, 48, 51, 31, 33, 35, 39, 43, 44, 48, 50, 51, 29, 31, 35, 39, 40, 42, 43, 46, 47, 48, 51, 23, 26, 27, 31, 35, 36, 37, 38, 39, 43, 48, 51, 24, 26, 27, 31, 36, 39, 43, 48, 51, 24, 28, 31, 32, 36, 41, 43, 46, 51, 22, 24, 29, 31, 33, 36, 41, 44, 46, 47, 51, 22, 25, 29, 33, 36, 38, 41, 44, 47, 51, 19, 21, 26, 28, 29, 34, 37, 41, 44, 48, 50, 51, 18, 21, 26, 30, 33, 38, 41, 45, 47, 51, 16, 17, 22, 25, 27, 31, 36, 39, 42, 44, 48, 51, 16, 18, 22, 24, 27, 31, 32, 36, 38, 42, 44, 48, 49, 51, 15, 18, 23, 24, 28, 30, 32, 36, 39, 42, 45, 47, 48, 51, 21, 22, 26, 27, 29, 33, 35, 36, 39, 42, 45, 46, 48, 51, 21, 26, 29, 32, 36, 40, 42, 46, 48, 51, 14, 16, 20, 21, 25, 26, 30, 31, 33, 36, 37, 41, 43, 46, 48, 51, 12, 18, 19, 23, 24, 28, 29, 31, 34, 36, 38, 41, 44, 46, 49, 51, 10, 12, 18, 23, 28, 31, 35, 36, 38, 41, 44, 46, 49, 51, 11, 13, 17, 19, 22, 24, 27, 28, 31, 33, 34, 36, 39, 41, 44, 46, 49, 51, 11, 14, 16, 19, 21, 24, 26, 30, 31, 34, 36, 38, 41, 45, 46, 50, 51, 11, 15, 16, 20, 22, 25, 26, 29, 31, 34, 37, 39, 41, 42, 45, 47, 49, 51, 9, 11, 15, 18, 19, 22, 24, 27, 29, 31, 33, 37, 39, 41, 43, 45, 47, 49, 51, 9, 12, 14, 19, 23, 25, 28, 29, 31, 32, 36, 38, 39, 40, 41, 43, 45, 48, 49, 50, 51, 8, 13, 15, 19, 21, 22, 25, 28, 29, 31, 33, 36, 37, 39, 41, 43, 45, 47, 49, 51, 8, 13, 16, 18, 21, 26, 29, 31, 33, 36, 39, 41, 44, 45, 46, 49, 51, 8, 11, 16, 17, 21, 24, 28, 31, 35, 36, 37, 40, 41, 42, 44, 46, 48, 49, 51, 8, 11, 12, 16, 19, 20, 21, 24, 28, 29, 33, 34, 36, 38, 40, 41, 42, 44, 46, 48, 50, 51, 7, 11, 14, 15, 16, 20, 22, 25, 27, 28, 31, 33, 36, 38, 39, 41, 43, 44, 45, 46, 47, 49, 51, 7, 11, 14, 16, 20, 23, 24, 26, 28, 31, 32, 33, 36, 38, 40, 41, 42, 43, 46, 48, 51, 10, 11, 14, 16, 19, 23, 26, 28, 31, 35, 36, 39, 41, 46, 49, 51, 6, 9, 13, 18, 21, 26, 30, 31, 34, 37, 40, 41, 43, 46, 48, 51, 6, 10, 13, 14, 15, 18, 21, 22, 26, 28, 29, 32, 34, 38, 40, 41, 43, 45, 46, 48, 51, 5, 6, 9, 13, 16, 17, 18, 21, 24, 25, 26, 29, 33, 35, 38, 41, 42, 43, 45, 46, 49, 51, 6, 8, 11, 13, 16, 20, 21, 24, 28, 31, 33, 34, 36, 38, 41, 45, 46, 49, 51, 6, 9, 11, 13, 16, 21, 24, 29, 31, 35, 36, 39, 41, 44, 46, 6, 9, 13, 16, 21, 23, 26, 31, 34, 36, 38, 41, 43, 44, 6, 8, 13, 16, 20, 21, 23, 26, 27, 31, 33, 35, 36, 39, 41, 43, 5, 7, 12, 13, 16, 20, 22, 23, 26, 30, 31, 34, 38, 41, 42, 4, 8, 13, 15, 16, 18, 20, 23, 25, 26, 31, 33, 38, 40, 41, 4, 8, 13, 16, 19, 23, 26, 31, 34, 37, 41, 4, 6, 9, 11, 12, 16, 19, 23, 26, 30, 31, 34, 36, 40, 4, 6, 8, 11, 12, 14, 15, 16, 18, 23, 26, 28, 29, 31, 33, 34, 36, 40, 4, 8, 12, 15, 17, 22, 23, 26, 29, 34, 35, 36, 38, 40, 4, 8, 12, 15, 18, 23, 25, 26, 28, 32, 33, 34, 36, 40, 4, 7, 12, 14, 18, 23, 26, 29, 34, 36, 40, 4, 7, 12, 14, 18, 23, 26, 29, 34, 36, 40, 4, 8, 12, 15, 18, 23, 25, 26, 28, 32, 33, 34, 36, 40, 4, 8, 12, 15, 17, 22, 23, 26, 29, 34, 35, 36, 38, 40, 4, 6, 8, 11, 12, 14, 15, 16, 18, 23, 26, 28, 29, 31, 33, 34, 36, 40, 4, 6, 9, 11, 12, 16, 19, 23, 26, 30, 31, 34, 36, 40, 4, 8, 13, 16, 19, 23, 26, 31, 34, 37, 41, 4, 8, 13, 15, 16, 18, 20, 23, 25, 26, 31, 33, 38, 40, 41, 5, 7, 12, 13, 16, 20, 22, 23, 26, 30, 31, 34, 38, 42, 6, 8, 13, 16, 20, 21, 23, 26, 27, 31, 33, 35, 36, 39, 41, 43, 6, 9, 13, 16, 21, 23, 26, 31, 34, 36, 38, 41, 44, 6, 9, 11, 13, 16, 21, 24, 29, 31, 35, 36, 41, 44, 46, 6, 8, 11, 13, 16, 20, 21, 24, 28, 31, 33, 34, 36, 38, 41, 45, 46, 49, 51, 5, 6, 9, 13, 16, 17, 18, 21, 24, 25, 26, 29, 33, 35, 38, 40, 41, 42, 43, 45, 46, 49, 51, 6, 10, 13, 14, 15, 18, 21, 22, 26, 28, 29, 32, 34, 37, 39, 43, 45, 46, 48, 51, 6, 9, 13, 18, 21, 26, 30, 31, 34, 36, 39, 43, 46, 48, 51, 10, 11, 14, 16, 19, 23, 26, 28, 31, 36, 39, 41, 46, 49, 51, 7, 11, 14, 16, 20, 23, 24, 26, 28, 31, 32, 35, 36, 38, 40, 41, 42, 43, 46, 48, 51, 7, 11, 14, 15, 16, 20, 22, 25, 27, 28, 31, 33, 35, 36, 38, 39, 41, 43, 44, 45, 46, 47, 49, 51, 8, 11, 12, 16, 19, 20, 21, 24, 28, 29, 32, 34, 36, 38, 40, 41, 42, 44, 46, 48, 50, 51, 8, 11, 16, 17, 21, 24, 28, 32, 35, 36, 37, 40, 41, 42, 44, 46, 48, 49, 51, 8, 13, 16, 18, 21, 26, 31, 33, 36, 39, 41, 44, 45, 46, 49, 51, 8, 13, 15, 19, 21, 22, 25, 26, 31, 33, 36, 37, 39, 41, 43, 45, 47, 49, 51, 9, 12, 14, 19, 23, 25, 28, 31, 32, 36, 38, 39, 40, 41, 43, 45, 48, 49, 50, 51, 9, 11, 15, 18, 19, 22, 24, 28, 30, 31, 33, 37, 39, 41, 43, 45, 47, 49, 51, 11, 15, 16, 20, 22, 25, 27, 30, 31, 34, 37, 39, 41, 42, 45, 47, 49, 51, 11, 14, 16, 19, 21, 26, 30, 31, 34, 36, 38, 41, 45, 46, 50, 51, 11, 13, 17, 19, 22, 26, 27, 28, 31, 33, 34, 36, 39, 41, 44, 46, 49, 51, 10, 12, 18, 23, 24, 28, 31, 35, 36, 38, 41, 44, 46, 49, 51, 12, 18, 19, 22, 24, 28, 29, 31, 34, 36, 38, 41, 44, 46, 49, 51, 14, 16, 20, 22, 25, 26, 30, 31, 33, 36, 37, 41, 43, 46, 48, 51, 19, 21, 26, 29, 32, 36, 40, 42, 46, 48, 51, 19, 22, 26, 27, 29, 33, 35, 36, 39, 42, 45, 46, 48, 51, 15, 19, 23, 24, 28, 30, 32, 36, 39, 42, 45, 47, 48, 51, 16, 17, 22, 24, 27, 31, 32, 36, 38, 42, 44, 48, 49, 51, 16, 22, 25, 27, 31, 36, 39, 42, 44, 48, 51, 18, 21, 26, 30, 33, 38, 41, 45, 47, 51, 19, 21, 26, 28, 29, 34, 37, 41, 44, 48, 50, 51, 22, 25, 29, 33, 36, 38, 41, 44, 47, 51, 22, 24, 29, 31, 33, 36, 41, 44, 46, 47, 51, 24, 28, 31, 32, 36, 41, 43, 46, 51, 24, 26, 27, 31, 36, 39, 43, 48, 51, 23, 26, 27, 31, 35, 36, 37, 38, 39, 43, 48, 51, 29, 31, 35, 39, 40, 42, 43, 46, 47, 48, 51, 31, 33, 35, 39, 43, 44, 48, 50, 51, 31, 34, 39, 43, 48, 51, 38, 42, 43, 46, 51, 39, 42, 44, 46, 51, 42, 46, 51, 42, 46, 51, 42, 46, 51};

  int ixTTEEVertical2[1385] = {56, 60, 61, 56, 60, 61, 56, 60, 61, 56, 58, 60, 63, 66, 56, 59, 60, 64, 66, 54, 59, 63, 68, 71, 76, 52, 54, 58, 59, 63, 67, 69, 71, 76, 54, 55, 56, 59, 60, 62, 63, 67, 71, 73, 76, 54, 59, 63, 64, 65, 66, 67, 71, 75, 76, 79, 81, 54, 59, 63, 66, 71, 75, 76, 78, 81, 56, 59, 61, 66, 70, 71, 74, 78, 81, 55, 56, 58, 61, 66, 69, 71, 73, 78, 80, 81, 55, 58, 61, 64, 66, 69, 73, 77, 80, 81, 52, 54, 58, 61, 65, 68, 73, 74, 76, 81, 83, 86, 55, 57, 61, 64, 69, 72, 76, 81, 84, 86, 54, 58, 60, 63, 66, 71, 75, 77, 80, 86, 88, 53, 54, 58, 60, 64, 66, 70, 71, 75, 78, 80, 85, 86, 88, 54, 55, 57, 60, 63, 66, 70, 72, 74, 78, 79, 83, 87, 88, 54, 56, 57, 60, 63, 66, 67, 69, 73, 75, 76, 80, 83, 88, 54, 56, 60, 62, 66, 70, 73, 76, 81, 83, 88, 54, 56, 59, 61, 65, 66, 69, 71, 72, 76, 77, 80, 82, 86, 88, 93, 53, 56, 58, 61, 64, 66, 68, 71, 73, 74, 78, 80, 83, 84, 90, 93, 53, 56, 58, 61, 64, 66, 67, 71, 74, 78, 79, 84, 90, 92, 93, 53, 56, 58, 61, 63, 66, 68, 69, 71, 74, 75, 76, 80, 83, 85, 89, 91, 93, 52, 56, 57, 61, 64, 66, 68, 71, 72, 76, 81, 83, 86, 88, 91, 93, 53, 55, 57, 60, 61, 63, 65, 68, 71, 72, 75, 77, 80, 82, 86, 87, 91, 96, 53, 55, 57, 59, 61, 63, 65, 69, 71, 72, 74, 78, 80, 83, 84, 87, 91, 93, 96, 52, 53, 54, 57, 59, 61, 62, 63, 64, 66, 70, 71, 74, 77, 79, 83, 88, 90, 93, 96, 53, 55, 57, 59, 61, 63, 65, 66, 69, 71, 76, 77, 80, 81, 83, 87, 89, 94, 96, 53, 56, 57, 58, 61, 63, 66, 69, 71, 76, 81, 84, 86, 89, 94, 96, 53, 54, 56, 58, 60, 61, 62, 65, 66, 67, 70, 74, 78, 81, 85, 86, 91, 94, 96, 52, 54, 56, 58, 60, 61, 62, 64, 66, 68, 70, 73, 74, 78, 81, 82, 83, 86, 90, 91, 94, 96, 53, 55, 56, 57, 58, 59, 61, 63, 64, 66, 67, 69, 71, 74, 75, 77, 80, 82, 86, 87, 88, 91, 95, 96, 54, 56, 59, 60, 61, 62, 64, 66, 67, 70, 71, 74, 76, 78, 79, 82, 86, 88, 91, 95, 96, 53, 56, 61, 63, 66, 71, 74, 76, 79, 83, 86, 88, 91, 92, 96, 54, 56, 59, 63, 66, 68, 71, 72, 76, 81, 84, 89, 93, 96, 98, 54, 56, 57, 59, 63, 65, 68, 70, 73, 74, 76, 80, 81, 84, 87, 88, 89, 92, 96, 98, 53, 56, 57, 59, 60, 61, 62, 64, 67, 69, 73, 76, 77, 78, 81, 84, 85, 86, 89, 93, 96, 97, 98, 53, 56, 57, 61, 64, 66, 68, 69, 71, 74, 78, 81, 82, 86, 89, 91, 94, 96, 98, 58, 61, 66, 67, 71, 73, 78, 81, 86, 89, 91, 93, 96, 98, 61, 64, 66, 68, 71, 76, 79, 81, 86, 89, 93, 96, 101, 61, 63, 66, 67, 69, 71, 75, 76, 79, 81, 82, 86, 89, 94, 96, 101, 64, 68, 71, 72, 76, 79, 80, 82, 86, 89, 90, 95, 97, 101, 62, 64, 69, 71, 76, 77, 79, 82, 84, 86, 87, 89, 94, 98, 101, 65, 68, 71, 76, 79, 83, 86, 89, 94, 98, 101, 66, 68, 71, 72, 76, 79, 83, 86, 90, 91, 93, 96, 98, 101, 66, 68, 69, 71, 73, 74, 76, 79, 84, 86, 87, 88, 90, 91, 94, 96, 98, 101, 64, 66, 67, 68, 73, 76, 79, 80, 85, 87, 90, 94, 98, 101, 66, 68, 69, 70, 74, 76, 77, 79, 84, 87, 90, 94, 98, 101, 66, 68, 73, 76, 79, 84, 88, 90, 95, 98, 101, 66, 68, 73, 76, 79, 84, 88, 90, 95, 98, 101, 66, 68, 69, 70, 74, 76, 77, 79, 84, 87, 90, 94, 98, 101, 64, 66, 67, 68, 73, 76, 79, 80, 85, 87, 90, 94, 98, 101, 66, 68, 69, 71, 73, 74, 76, 79, 84, 86, 87, 88, 90, 91, 94, 96, 98, 101, 66, 68, 71, 72, 76, 79, 83, 86, 90, 91, 93, 96, 98, 101, 65, 68, 71, 76, 79, 83, 86, 89, 94, 98, 101, 62, 64, 69, 71, 76, 77, 79, 82, 84, 86, 87, 89, 94, 98, 101, 61, 64, 68, 71, 72, 76, 79, 80, 82, 86, 89, 90, 95, 97, 101, 61, 63, 66, 67, 69, 71, 75, 76, 79, 81, 82, 86, 89, 94, 96, 101, 59, 61, 64, 66, 68, 71, 76, 79, 81, 86, 89, 93, 96, 100, 58, 61, 63, 66, 67, 71, 73, 78, 81, 86, 89, 91, 93, 96, 98, 53, 56, 57, 61, 64, 66, 68, 69, 71, 74, 78, 81, 82, 86, 89, 91, 94, 96, 98, 53, 56, 57, 59, 60, 61, 64, 67, 69, 73, 76, 77, 78, 81, 84, 85, 86, 89, 93, 96, 97, 98, 54, 56, 57, 59, 61, 62, 64, 68, 70, 73, 74, 76, 80, 81, 84, 87, 88, 89, 92, 96, 98, 54, 56, 59, 61, 62, 65, 68, 71, 72, 76, 81, 84, 89, 93, 96, 98, 53, 56, 61, 63, 66, 67, 71, 74, 76, 79, 83, 86, 88, 91, 92, 96, 54, 56, 59, 60, 61, 62, 64, 66, 69, 70, 71, 74, 76, 78, 79, 82, 86, 88, 91, 95, 96, 53, 55, 56, 57, 58, 59, 61, 63, 64, 66, 69, 71, 74, 75, 77, 80, 82, 86, 87, 88, 91, 95, 96, 52, 54, 56, 58, 60, 61, 62, 64, 66, 68, 69, 73, 74, 78, 81, 82, 83, 86, 90, 91, 94, 96, 53, 54, 56, 58, 60, 61, 62, 65, 66, 67, 71, 74, 78, 81, 85, 86, 91, 94, 96, 53, 56, 57, 58, 61, 63, 66, 69, 71, 73, 76, 81, 84, 86, 89, 94, 96, 53, 55, 57, 59, 61, 63, 65, 66, 69, 71, 73, 74, 77, 80, 81, 83, 87, 89, 94, 96, 52, 53, 54, 57, 59, 61, 62, 63, 64, 66, 70, 71, 73, 74, 77, 79, 83, 88, 90, 93, 96, 53, 55, 57, 59, 61, 63, 65, 69, 71, 73, 75, 78, 80, 83, 84, 87, 91, 93, 96, 53, 55, 57, 60, 61, 63, 65, 68, 71, 73, 76, 77, 80, 82, 86, 87, 91, 96, 52, 56, 57, 61, 64, 66, 68, 71, 72, 76, 78, 81, 83, 86, 88, 91, 93, 53, 56, 58, 61, 63, 66, 68, 69, 71, 74, 75, 78, 80, 83, 85, 89, 91, 93, 53, 56, 58, 61, 64, 66, 67, 71, 74, 79, 84, 90, 92, 93, 53, 56, 58, 61, 64, 66, 68, 71, 73, 74, 78, 79, 83, 84, 90, 93, 54, 56, 59, 61, 65, 66, 69, 71, 72, 76, 77, 81, 82, 86, 88, 93, 54, 56, 60, 62, 66, 70, 73, 76, 81, 88, 54, 56, 57, 60, 63, 66, 67, 69, 73, 75, 76, 80, 81, 86, 87, 88, 54, 55, 57, 60, 63, 66, 70, 72, 74, 78, 79, 84, 87, 88, 53, 54, 58, 60, 64, 66, 70, 71, 75, 78, 80, 84, 86, 88, 54, 58, 60, 63, 66, 71, 75, 77, 80, 85, 87, 88, 55, 57, 61, 64, 69, 72, 76, 81, 82, 83, 84, 85, 86, 52, 54, 58, 61, 65, 68, 73, 74, 76, 81, 83, 86, 55, 58, 61, 64, 66, 69, 73, 77, 80, 81, 55, 56, 58, 61, 66, 69, 71, 73, 78, 80, 81, 56, 59, 61, 66, 70, 71, 74, 78, 81, 54, 59, 63, 66, 71, 75, 76, 78, 81, 54, 59, 63, 64, 65, 66, 67, 71, 75, 76, 79, 81, 54, 55, 56, 59, 60, 62, 63, 67, 71, 73, 76, 52, 54, 58, 59, 63, 67, 69, 71, 76, 54, 59, 63, 68, 71, 76, 56, 59, 60, 64, 66, 56, 58, 60, 63, 66, 56, 60, 61, 56, 60, 61, 56, 60};

  int iyTTEEVertical1[1381] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 90, 90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94, 94, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 99, 99, 99, 100, 100, 100};

  int iyTTEEVertical2[1385] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 90, 90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94, 94, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 99, 99, 99, 100, 100};



  line2.SetLineWidth(1);
  line2.SetLineStyle(3);

  int offset_vertical = 0;
  int offset_horizontal = 0;


  if(string(fname).find("EEMinus")!= std::string::npos){ //EE-
    offset_vertical = 102;
    offset_horizontal = 101;
  }

  
  
  //drawing horizontal TT boundaries
  
  for ( int i=0; i!=1381; i=i+1) {
    
    line2.DrawLine(abs(offset_horizontal-ixTTEEHorizontal1[i]), iyTTEEHorizontal1[i], 
		   abs(offset_horizontal-ixTTEEHorizontal1[i])+1, iyTTEEHorizontal1[i]);
    
  }
  
  for ( int i=0; i!=1386; i=i+1) {
    
    line2.DrawLine(abs(offset_horizontal-ixTTEEHorizontal2[i]), iyTTEEHorizontal2[i], 
		   abs(offset_horizontal-ixTTEEHorizontal2[i])+1, iyTTEEHorizontal2[i]);
    
  }
  
  
  // //drawing vertical TT boundaries
  
  for ( int i=0; i!=1381; i=i+1) {
    
    line2.DrawLine(abs(offset_vertical-ixTTEEVertical1[i]), iyTTEEVertical1[i], 
		   abs(offset_vertical-ixTTEEVertical1[i]), iyTTEEVertical1[i]+1);
    
  }
  
  for ( int i=0; i!=1385; i=i+1) {
    
    line2.DrawLine(abs(offset_vertical-ixTTEEVertical2[i]), iyTTEEVertical2[i], 
		   abs(offset_vertical-ixTTEEVertical2[i]), iyTTEEVertical2[i]+1);
    
  }
  

  
  //drawing TCC boundaries
  
  int ixTCCEEHorizontal[699]={1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 93, 93, 93, 94, 94, 94, 95, 95, 95, 96, 96, 96, 97, 97, 97, 98, 98, 98, 99, 99, 99, 100, 100};
  
  
  int iyTCCEEHorizontal[699]={42, 60, 61, 42, 60, 61, 42, 60, 61, 42, 60, 66, 42, 60, 66, 43, 59, 76, 43, 59, 76, 43, 59, 76, 26, 43, 59, 76, 81, 26, 43, 59, 76, 81, 28, 43, 59, 74, 81, 29, 44, 58, 73, 81, 29, 44, 58, 73, 81, 29, 44, 50, 52, 58, 73, 86, 30, 45, 47, 55, 57, 72, 86, 31, 39, 44, 58, 63, 71, 88, 32, 38, 44, 58, 64, 70, 88, 32, 36, 45, 57, 66, 70, 88, 33, 35, 46, 56, 67, 69, 88, 32, 46, 56, 70, 88, 16, 30, 33, 46, 56, 69, 72, 86, 93, 18, 29, 34, 46, 56, 68, 73, 84, 93, 18, 28, 36, 46, 56, 66, 74, 84, 93, 19, 27, 36, 46, 56, 66, 75, 83, 93, 19, 26, 36, 46, 56, 66, 76, 83, 93, 22, 25, 37, 47, 55, 65, 77, 80, 96, 22, 24, 37, 47, 55, 65, 78, 80, 96, 23, 25, 38, 48, 54, 64, 77, 79, 96, 22, 25, 39, 47, 55, 63, 77, 80, 96, 21, 26, 39, 46, 56, 63, 76, 81, 96, 21, 28, 41, 48, 54, 61, 74, 81, 96, 20, 29, 41, 48, 54, 61, 73, 82, 96, 20, 31, 41, 47, 55, 61, 71, 82, 96, 7, 20, 31, 41, 48, 54, 61, 71, 82, 95, 96, 10, 19, 31, 41, 49, 53, 61, 71, 83, 92, 96, 13, 18, 34, 43, 48, 54, 59, 68, 84, 89, 98, 13, 14, 15, 18, 34, 43, 48, 54, 59, 68, 84, 87, 88, 89, 98, 16, 17, 18, 35, 45, 49, 53, 57, 67, 84, 85, 86, 98, 16, 20, 36, 45, 49, 53, 57, 64, 82, 86, 98, 16, 21, 36, 44, 46, 58, 63, 81, 86, 98, 16, 26, 41, 44, 61, 76, 86, 101, 16, 27, 41, 43, 61, 75, 86, 101, 16, 30, 42, 61, 72, 86, 101, 16, 33, 41, 69, 86, 101, 16, 34, 41, 68, 86, 101, 16, 40, 86, 101, 15, 40, 87, 101, 15, 40, 87, 101, 15, 40, 87, 101, 14, 40, 88, 101, 14, 40, 88, 101, 15, 40, 87, 101, 15, 40, 87, 101, 15, 40, 87, 101, 16, 40, 86, 101, 16, 34, 41, 68, 86, 101, 16, 33, 41, 69, 86, 101, 16, 30, 41, 42, 72, 86, 101, 16, 27, 41, 43, 61, 75, 86, 101, 16, 26, 41, 44, 61, 76, 86, 101, 16, 21, 39, 44, 46, 58, 66, 81, 86, 98, 16, 20, 38, 45, 49, 53, 57, 66, 82, 86, 98, 16, 17, 18, 35, 45, 49, 53, 57, 67, 84, 85, 86, 98, 13, 14, 15, 18, 34, 43, 48, 54, 59, 68, 84, 87, 88, 89, 98, 13, 18, 34, 43, 48, 54, 59, 68, 84, 89, 98, 10, 19, 31, 41, 49, 53, 61, 71, 83, 92, 96, 7, 20, 31, 41, 48, 54, 61, 71, 82, 95, 96, 20, 31, 41, 47, 55, 61, 71, 82, 96, 20, 29, 41, 48, 54, 61, 73, 82, 96, 21, 28, 41, 48, 54, 61, 74, 81, 96, 21, 26, 39, 46, 56, 63, 76, 81, 96, 22, 25, 39, 47, 55, 63, 77, 80, 96, 23, 25, 38, 48, 54, 64, 77, 79, 96, 22, 24, 37, 47, 55, 65, 78, 80, 96, 22, 25, 37, 47, 55, 65, 77, 80, 96, 19, 26, 36, 46, 56, 66, 76, 83, 93, 19, 27, 36, 46, 56, 66, 75, 83, 93, 18, 28, 36, 46, 56, 66, 74, 84, 93, 18, 29, 34, 46, 56, 68, 73, 84, 93, 16, 30, 33, 46, 56, 69, 72, 86, 93, 32, 46, 56, 70, 88, 33, 35, 46, 56, 67, 69, 88, 32, 36, 45, 57, 66, 70, 88, 32, 38, 44, 58, 64, 70, 88, 31, 39, 44, 58, 63, 71, 88, 30, 45, 47, 55, 57, 72, 86, 29, 44, 50, 52, 58, 73, 86, 29, 44, 58, 73, 81, 29, 44, 58, 73, 81, 28, 43, 59, 74, 81, 26, 43, 59, 76, 81, 26, 43, 59, 76, 81, 43, 59, 76, 43, 59, 76, 43, 59, 76, 42, 60, 66, 42, 60, 66, 42, 60, 61, 42, 60, 61, 42, 60};
  
  
  
  
  
  int ixTCCEEVertical[729]={51, 61, 51, 61, 51, 61, 51, 66, 51, 66, 34, 51, 68, 76, 35, 51, 67, 76, 35, 51, 67, 76, 35, 51, 67, 81, 36, 51, 66, 81, 36, 51, 66, 81, 36, 51, 66, 81, 38, 51, 64, 81, 21, 37, 50, 51, 52, 65, 81, 86, 21, 38, 47, 51, 55, 64, 81, 86, 22, 39, 51, 63, 80, 88, 22, 38, 51, 64, 80, 88, 24, 36, 39, 51, 63, 66, 78, 88, 26, 35, 39, 51, 63, 67, 76, 88, 26, 32, 40, 51, 62, 70, 76, 88, 26, 30, 41, 51, 61, 72, 76, 93, 28, 29, 41, 51, 61, 73, 74, 93, 28, 41, 51, 61, 74, 93, 27, 28, 41, 51, 61, 74, 75, 93, 26, 30, 41, 51, 61, 72, 76, 93, 11, 25, 31, 42, 51, 60, 71, 77, 91, 96, 11, 24, 31, 43, 51, 59, 71, 78, 91, 96, 12, 23, 32, 43, 51, 59, 70, 79, 90, 96, 15, 22, 33, 43, 51, 59, 69, 80, 87, 96, 16, 21, 33, 44, 51, 58, 69, 81, 86, 96, 17, 21, 36, 44, 51, 58, 66, 81, 85, 96, 19, 20, 21, 36, 44, 51, 58, 66, 81, 82, 83, 96, 20, 22, 36, 45, 51, 57, 66, 80, 82, 96, 20, 23, 38, 46, 51, 56, 64, 79, 82, 96, 19, 23, 39, 46, 51, 56, 63, 79, 83, 96, 18, 26, 41, 46, 51, 56, 63, 76, 84, 98, 18, 28, 41, 46, 51, 56, 63, 74, 84, 98, 17, 29, 41, 46, 51, 56, 62, 73, 85, 98, 16, 31, 41, 46, 51, 56, 61, 71, 86, 98, 16, 31, 41, 46, 61, 71, 86, 98, 16, 36, 43, 44, 66, 86, 101, 6, 16, 36, 43, 66, 86, 96, 101, 12, 16, 38, 42, 64, 86, 90, 101, 15, 16, 18, 38, 40, 41, 62, 64, 84, 86, 87, 101, 16, 19, 41, 83, 86, 101, 16, 26, 30, 31, 40, 71, 72, 76, 86, 101, 15, 28, 29, 31, 33, 34, 40, 68, 69, 71, 73, 74, 87, 101, 15, 35, 36, 38, 40, 64, 66, 67, 87, 101, 15, 40, 87, 101, 14, 40, 88, 101, 14, 40, 88, 101, 15, 40, 87, 101, 15, 35, 36, 38, 40, 64, 66, 67, 87, 101, 15, 28, 29, 31, 33, 34, 40, 68, 69, 71, 73, 74, 87, 101, 16, 26, 30, 31, 40, 71, 72, 76, 86, 101, 16, 19, 41, 83, 86, 101, 15, 16, 18, 38, 40, 41, 62, 64, 84, 86, 87, 101, 12, 16, 38, 42, 64, 86, 90, 101, 6, 16, 36, 43, 66, 86, 96, 101, 16, 36, 44, 59, 66, 86, 100, 16, 31, 41, 46, 61, 71, 86, 98, 16, 31, 41, 46, 51, 56, 61, 71, 86, 98, 17, 29, 40, 46, 51, 56, 61, 73, 85, 98, 18, 28, 39, 46, 51, 56, 61, 74, 84, 98, 18, 26, 39, 46, 51, 56, 61, 76, 84, 98, 19, 23, 39, 46, 51, 56, 63, 79, 83, 96, 20, 23, 38, 46, 51, 56, 64, 79, 82, 96, 20, 22, 36, 45, 51, 57, 66, 80, 82, 96, 19, 20, 21, 36, 44, 51, 58, 66, 81, 82, 83, 96, 17, 21, 36, 44, 51, 58, 66, 81, 85, 96, 16, 21, 33, 44, 51, 58, 69, 81, 86, 96, 15, 22, 33, 43, 51, 59, 69, 80, 87, 96, 12, 23, 32, 43, 51, 59, 70, 79, 90, 96, 11, 24, 31, 43, 51, 59, 71, 78, 91, 96, 11, 25, 31, 42, 51, 60, 71, 77, 91, 96, 26, 30, 41, 51, 61, 72, 76, 93, 27, 28, 41, 51, 61, 74, 75, 93, 28, 41, 51, 61, 74, 93, 28, 29, 41, 51, 61, 73, 74, 93, 26, 30, 41, 51, 61, 72, 76, 93, 26, 32, 40, 51, 62, 70, 76, 88, 26, 35, 39, 51, 63, 67, 76, 88, 24, 36, 39, 51, 63, 66, 78, 88, 22, 38, 51, 64, 80, 88, 22, 39, 51, 63, 80, 88, 21, 38, 47, 51, 55, 64, 81, 86, 21, 37, 50, 51, 52, 65, 81, 86, 38, 51, 64, 81, 36, 51, 66, 81, 36, 51, 66, 81, 36, 51, 66, 81, 35, 51, 67, 81, 35, 51, 67, 76, 35, 51, 67, 76, 34, 51, 68, 76, 51, 66, 51, 66, 51, 61, 51, 61, 51};
  
  int iyTCCEEVertical[729]={1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 89, 89, 89, 89, 90, 90, 90, 90, 91, 91, 91, 91, 92, 92, 92, 92, 93, 93, 93, 93, 94, 94, 94, 94, 95, 95, 95, 95, 96, 96, 97, 97, 98, 98, 99, 99, 100};
  
  
  line2.SetLineWidth(1);
  line2.SetLineStyle(1);
  
  //drawing horizontal TCC boundaries
  
  for ( int i=0; i<699; i=i+1) {
    
    line2.DrawLine(abs(offset_horizontal-ixTCCEEHorizontal[i]), iyTCCEEHorizontal[i], 
	       abs(offset_horizontal-ixTCCEEHorizontal[i])+1, iyTCCEEHorizontal[i]);
    
  }
  
  //drawing vertical TCC boundaries
  
  for ( int i=0; i<729; i=i+1) {
    
    line2.DrawLine(abs(offset_vertical-ixTCCEEVertical[i]), iyTCCEEVertical[i], 
	       abs(offset_vertical-ixTCCEEVertical[i]), iyTCCEEVertical[i]+1);
    
  }
  
  
  
  //drawing sector boundaries
  
  int ixSectorsEE[202] = {61, 61, 60, 60, 59, 59, 58, 58, 57, 57, 55, 55, 45, 45, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 45, 45, 55, 55, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 0,100,100, 97, 97, 95, 95, 92, 92, 87, 87, 85, 85, 80, 80, 75, 75, 65, 65, 60, 60, 40, 40, 35, 35, 25, 25, 20, 20, 15, 15, 13, 13,  8,  8,  5,  5,  3,  3,  0,  0,  3,  3,  5,  5,  8,  8, 13, 13, 15, 15, 20, 20, 25, 25, 35, 35, 40, 40, 60, 60, 65, 65, 75, 75, 80, 80, 85, 85, 87, 87, 92, 92, 95, 95, 97, 97,100,100,  0, 61, 65, 65, 70, 70, 80, 80, 90, 90, 92,  0, 61, 65, 65, 90, 90, 97,  0, 57, 60, 60, 65, 65, 70, 70, 75, 75, 80, 80,  0, 50, 50,  0, 43, 40, 40, 35, 35, 30, 30, 25, 25, 20, 20,  0, 39, 35, 35, 10, 10,  3,  0, 39, 35, 35, 30, 30, 20, 20, 10, 10,  8,  0, 45, 45, 40, 40, 35, 35,  0, 55, 55, 60, 60, 65, 65};
  
  int iySectorsEE[202] = {50, 55, 55, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 60, 60, 59, 59, 58, 58, 57, 57, 55, 55, 45, 45, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 45, 45, 50,  0, 50, 60, 60, 65, 65, 75, 75, 80, 80, 85, 85, 87, 87, 92, 92, 95, 95, 97, 97,100,100, 97, 97, 95, 95, 92, 92, 87, 87, 85, 85, 80, 80, 75, 75, 65, 65, 60, 60, 40, 40, 35, 35, 25, 25, 20, 20, 15, 15, 13, 13,  8,  8,  5,  5,  3,  3,  0,  0,  3,  3,  5,  5,  8,  8, 13, 13, 15, 15, 20, 20, 25, 25, 35, 35, 40, 40, 50,  0, 45, 45, 40, 40, 35, 35, 30, 30, 25, 25,  0, 50, 50, 55, 55, 60, 60,  0, 60, 60, 65, 65, 70, 70, 75, 75, 85, 85, 87,  0, 61,100,  0, 60, 60, 65, 65, 70, 70, 75, 75, 85, 85, 87,  0, 50, 50, 55, 55, 60, 60,  0, 45, 45, 40, 40, 35, 35, 30, 30, 25, 25,  0, 39, 30, 30, 15, 15,  5,  0, 39, 30, 30, 15, 15,  5};
  
  line2.SetLineWidth(3);
  
  
  
  for ( int i=0; i<201; i=i+1) {
    if ( (ixSectorsEE[i]!=0 || iySectorsEE[i]!=0) && 
	 (ixSectorsEE[i+1]!=0 || iySectorsEE[i+1]!=0) ) {
      line2.DrawLine(ixSectorsEE[i]+1, iySectorsEE[i]+1, 
		 ixSectorsEE[i+1]+1, iySectorsEE[i+1]+1);
    }
  }
  
  
  //printing TT ID numbers
  
  
  int ixLabels[720]={99, 99, 97, 97, 95, 94, 92, 91, 87, 84, 79, 77, 74, 69, 64, 61, 58, 54, 47, 43, 40, 37, 32, 27, 24, 22, 17, 14, 10, 9, 7, 6, 4, 4, 2, 2, 2, 2, 4, 4, 6, 7, 9, 10, 14, 17, 22, 24, 27, 32, 37, 40, 43, 47, 54, 58, 61, 64, 69, 74, 77, 79, 84, 87, 91, 92, 94, 95, 97, 97, 99, 99, 96, 96, 94, 94, 92, 91, 89, 87, 84, 82, 78, 75, 72, 69, 65, 61, 57, 52, 49, 44, 40, 36, 32, 29, 26, 23, 19, 16, 14, 12, 10, 9, 7, 7, 5, 5, 5, 5, 7, 7, 9, 10, 12, 14, 16, 19, 23, 26, 29, 32, 36, 40, 44, 49, 52, 57, 61, 65, 69, 72, 75, 78, 82, 85, 87, 89, 91, 92, 94, 94, 96, 96, 92, 92, 91, 90, 89, 87, 85, 84, 81, 78, 76, 73, 70, 67, 64, 60, 57, 52, 49, 44, 41, 37, 34, 31, 28, 25, 23, 20, 17, 16, 14, 12, 11, 10, 9, 9, 9, 9, 10, 11, 12, 14, 16, 17, 20, 23, 25, 28, 31, 34, 37, 41, 44, 49, 52, 57, 60, 64, 67, 70, 73, 76, 78, 81, 84, 85, 87, 89, 90, 91, 92, 92, 88, 87, 87, 87, 87, 84, 82, 81, 79, 76, 74, 71, 68, 66, 62, 59, 56, 53, 48, 45, 42, 39, 35, 33, 30, 27, 25, 23, 20, 19, 17, 14, 14, 14, 14, 13, 13, 14, 14, 14, 14, 17, 19, 20, 22, 25, 27, 30, 33, 35, 39, 42, 45, 48, 53, 56, 59, 62, 66, 68, 71, 74, 76, 78, 81, 82, 84, 87, 87, 87, 87, 88, 85, 84, 83, 84, 82, 80, 79, 78, 75, 74, 72, 69, 67, 64, 61, 58, 56, 52, 49, 45, 43, 40, 37, 34, 32, 29, 28, 26, 23, 22, 21, 19, 17, 18, 17, 16, 16, 17, 18, 17, 19, 21, 22, 23, 26, 27, 29, 32, 34, 37, 40, 43, 45, 49, 52, 56, 58, 61, 64, 67, 69, 72, 73, 75, 78, 79, 80, 82, 84, 83, 84, 85, 82, 80, 80, 80, 79, 78, 77, 76, 74, 72, 69, 67, 64, 62, 59, 57, 54, 52, 49, 47, 44, 42, 39, 37, 34, 32, 29, 27, 25, 24, 23, 22, 21, 21, 21, 19, 19, 21, 21, 21, 22, 23, 24, 25, 27, 29, 32, 34, 37, 39, 42, 44, 47, 49, 52, 54, 57, 59, 62, 64, 67, 69, 72, 74, 76, 77, 78, 79, 80, 80, 80, 82, 77, 77, 77, 77, 76, 74, 74, 72, 71, 69, 67, 66, 64, 62, 59, 57, 54, 52, 49, 47, 44, 42, 39, 37, 35, 34, 32, 30, 29, 27, 27, 25, 24, 24, 24, 24, 24, 24, 24, 24, 25, 27, 27, 29, 30, 32, 34, 35, 37, 39, 42, 44, 47, 49, 52, 54, 57, 59, 62, 64, 66, 67, 69, 71, 72, 74, 74, 76, 77, 77, 77, 77, 74, 74, 74, 74, 72, 72, 71, 69, 69, 67, 65, 64, 62, 59, 58, 55, 54, 52, 49, 47, 46, 43, 42, 39, 37, 36, 34, 33, 32, 30, 29, 29, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 30, 32, 32, 34, 36, 37, 39, 42, 43, 46, 47, 49, 52, 54, 55, 58, 59, 62, 64, 65, 67, 68, 69, 71, 72, 72, 74, 74, 74, 74, 71, 71, 69, 69, 69, 69, 69, 67, 66, 64, 62, 62, 60, 59, 57, 55, 54, 52, 49, 47, 46, 44, 42, 41, 39, 39, 37, 35, 34, 32, 32, 32, 32, 32, 30, 30, 30, 30, 32, 32, 32, 32, 32, 34, 35, 37, 39, 39, 41, 42, 44, 46, 47, 49, 52, 54, 55, 57, 59, 60, 62, 62, 64, 66, 67, 69, 69, 69, 69, 69, 71, 71, 67, 67, 66, 64, 62, 60, 57, 54, 52, 49, 47, 44, 41, 39, 37, 35, 34, 34, 34, 34, 35, 37, 39, 41, 44, 47, 49, 52, 54, 57, 60, 62, 64, 66, 67, 67, 64, 63, 62, 62, 60, 59, 56, 54, 52, 49, 47, 45, 42, 42, 39, 39, 38, 37, 37, 38, 39, 39, 41, 42, 45, 47, 49, 52, 54, 56, 59, 59, 62, 62, 63, 64};
  
  int iyLabels[720]={54, 58, 61, 64, 69, 74, 77, 79, 84, 87, 91, 92, 94, 95, 97, 97, 99, 99, 99, 99, 97, 96, 94, 94, 91, 91, 86, 84, 79, 77, 74, 69, 64, 61, 57, 52, 47, 43, 40, 37, 32, 27, 24, 22, 17, 14, 10, 9, 7, 6, 4, 4, 2, 2, 2, 2, 4, 5, 7, 7, 10, 10, 15, 17, 22, 24, 27, 32, 37, 40, 44, 49, 52, 57, 61, 65, 69, 72, 75, 78, 81, 84, 87, 89, 91, 92, 94, 94, 96, 96, 96, 95, 94, 94, 92, 91, 89, 86, 85, 82, 78, 75, 72, 68, 64, 60, 57, 52, 49, 44, 40, 36, 32, 29, 26, 23, 19, 16, 14, 12, 10, 9, 7, 7, 5, 5, 5, 6, 7, 7, 9, 10, 12, 15, 16, 19, 23, 26, 29, 33, 37, 41, 44, 49, 52, 57, 60, 64, 67, 70, 73, 76, 78, 81, 84, 85, 87, 89, 90, 91, 92, 92, 91, 91, 91, 90, 89, 87, 85, 84, 81, 78, 76, 73, 70, 67, 64, 60, 57, 52, 49, 44, 41, 37, 34, 31, 28, 25, 23, 20, 17, 16, 14, 12, 11, 10, 9, 9, 10, 10, 10, 11, 12, 14, 16, 17, 20, 23, 25, 28, 31, 34, 37, 41, 44, 49, 53, 56, 59, 62, 66, 68, 71, 74, 76, 78, 81, 82, 84, 87, 87, 87, 87, 88, 88, 87, 87, 87, 86, 84, 82, 81, 78, 76, 74, 71, 67, 65, 62, 59, 56, 52, 48, 45, 42, 39, 35, 33, 30, 27, 25, 23, 20, 19, 17, 14, 14, 14, 14, 13, 13, 14, 14, 14, 15, 17, 19, 20, 23, 25, 27, 30, 34, 36, 39, 42, 45, 49, 52, 56, 58, 61, 64, 67, 69, 72, 73, 75, 78, 79, 80, 82, 84, 83, 84, 85, 85, 84, 83, 83, 82, 80, 79, 78, 75, 74, 72, 69, 67, 64, 61, 58, 55, 52, 49, 45, 43, 40, 37, 34, 32, 29, 28, 26, 23, 22, 21, 19, 17, 18, 17, 16, 16, 17, 18, 18, 19, 21, 22, 23, 26, 27, 29, 32, 34, 37, 40, 43, 46, 49, 52, 54, 57, 59, 62, 64, 67, 69, 71, 74, 76, 77, 78, 79, 80, 80, 80, 82, 81, 80, 80, 79, 79, 77, 77, 75, 73, 71, 69, 66, 64, 62, 59, 57, 54, 52, 49, 47, 44, 42, 39, 37, 34, 32, 30, 27, 25, 24, 23, 22, 21, 21, 21, 19, 20, 21, 21, 22, 22, 24, 24, 26, 28, 30, 32, 35, 37, 39, 42, 44, 47, 49, 52, 54, 57, 59, 62, 64, 66, 67, 69, 71, 72, 74, 74, 76, 77, 77, 77, 77, 77, 77, 77, 77, 75, 74, 74, 72, 70, 69, 67, 66, 63, 62, 59, 56, 54, 51, 49, 47, 44, 42, 39, 37, 35, 34, 32, 30, 29, 27, 27, 25, 24, 24, 24, 24, 24, 24, 24, 24, 26, 27, 27, 29, 31, 32, 34, 35, 38, 39, 42, 45, 47, 50, 52, 54, 55, 58, 59, 62, 64, 65, 67, 68, 69, 71, 72, 72, 74, 74, 74, 74, 74, 74, 73, 74, 72, 72, 71, 69, 69, 67, 64, 63, 61, 59, 58, 55, 53, 51, 49, 47, 46, 43, 42, 39, 37, 36, 34, 33, 32, 30, 29, 29, 27, 27, 27, 27, 27, 27, 28, 27, 29, 29, 30, 32, 32, 34, 37, 38, 40, 42, 43, 46, 48, 50, 52, 54, 55, 57, 59, 60, 61, 62, 64, 66, 67, 68, 69, 69, 69, 69, 71, 71, 71, 71, 69, 69, 69, 68, 68, 67, 65, 64, 62, 61, 60, 58, 56, 54, 54, 51, 49, 47, 46, 44, 42, 41, 40, 39, 37, 35, 34, 33, 32, 32, 32, 32, 30, 30, 30, 30, 32, 32, 32, 33, 33, 34, 36, 37, 39, 40, 41, 43, 45, 47, 47, 50, 52, 54, 57, 60, 62, 64, 66, 67, 67, 66, 66, 66, 64, 62, 59, 57, 54, 52, 49, 47, 44, 41, 39, 37, 35, 34, 34, 35, 35, 35, 37, 39, 42, 44, 47, 49, 52, 54, 56, 59, 59, 62, 62, 63, 64, 64, 63, 62, 62, 59, 59, 56, 54, 52, 49, 47, 45, 42, 42, 39, 39, 38, 37, 37, 38, 39, 39, 42, 42, 45, 47, 49};
 
  int bincontentLabels[720]={3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25};


  for(int i=0; i!= 720; ++i) label2->SetBinContent(ixLabels[i],iyLabels[i],bincontentLabels[i]);
  
  label2->Draw("text same");
  

//printing Sector numbers  
  TLatex txt2;
  if(string(fname).find("EEMinus")!= std::string::npos){ //EE-
    txt2.DrawText(27, 97, Form("-%d",1));
    txt2.DrawText(0, 77, Form("-%d",2));
    txt2.DrawText(-5, 35, Form("-%d",3));
    txt2.DrawText(12, 7, Form("-%d",4));
    txt2.DrawText(46, -5, Form("-%d",5));
    txt2.DrawText(82, 8, Form("-%d",6));
    txt2.DrawText(99, 36, Form("-%d",7));
    txt2.DrawText(94, 77, Form("-%d",8));
    txt2.DrawText(67, 97, Form("-%d",9));
  }
  else{
    txt2.DrawText(27, 97, Form("+%d",1));
    txt2.DrawText(0, 77, Form("+%d",2));
    txt2.DrawText(-5, 35, Form("+%d",3));
    txt2.DrawText(12, 7, Form("+%d",4));
    txt2.DrawText(46, -5, Form("+%d",5));
    txt2.DrawText(82, 8, Form("+%d",6));
    txt2.DrawText(99, 36, Form("+%d",7));
    txt2.DrawText(94, 77, Form("+%d",8));
    txt2.DrawText(67, 97, Form("+%d",9));
  }


  iphilabels->SetMarkerSize(0.6);
  //
  iphilabels->SetBinContent(113,64,1);
  iphilabels->SetBinContent(113,59,72);
  iphilabels->SetBinContent(113,54,71);
  //
  iphilabels->SetBinContent(113,69,2);
  iphilabels->SetBinContent(110,73,3);
  //
  iphilabels->SetBinContent(95,100,10);
  iphilabels->SetBinContent(93,102,11);
  //
  iphilabels->SetBinContent(64,113,18);
  iphilabels->SetBinContent(59,113,19);
  //
  iphilabels->SetBinContent(30,102,26);
  iphilabels->SetBinContent(28,100,27);
  //
  iphilabels->SetBinContent(13,73,34);
  iphilabels->SetBinContent(10,69,35);
  //
  iphilabels->SetBinContent(10,64,36);
  iphilabels->SetBinContent(10,59,37);
  iphilabels->SetBinContent(10,54,38);
  //
  //
  iphilabels->SetBinContent(15,39,42);
  iphilabels->SetBinContent(18,35,43);
  //
  iphilabels->SetBinContent(43,15,50);
  iphilabels->SetBinContent(48,13,51);
  //
  iphilabels->SetBinContent(75,13,58);
  iphilabels->SetBinContent(80,15,59);
  //
  iphilabels->SetBinContent(105,35,66);
  iphilabels->SetBinContent(108,39,67);
  
  iphilabels->Draw("text same");
  
  TLine l;
  l.SetLineWidth(3);
  l.DrawLine(101,51,107,51);
  TArrow * iphiArrow1 = new TArrow(107,51,107,55,0.01,"|>");
  iphiArrow1->SetLineWidth(3);
  iphiArrow1->Draw();
  
  l.DrawLine(-5,51,1,51);
  TArrow * iphiArrow2 = new TArrow(-5,51,-5,47,0.01,"|>");
  iphiArrow2->SetLineWidth(3);
  iphiArrow2->Draw();
  
  TLatex iphi;
  iphi.SetTextSize(0.03);
  iphi.DrawLatex(-7,43,"i#phi");
  iphi.DrawLatex(106,57,"i#phi");
  
  

  
  return;
  
}











void draw_EndcapOccupancy(Char_t* fname, TCanvas* c, TFile* f, int runNum, TH2I* label2, TH2C* iphilabels) 
{
  //printf("helloendcapoccupancy\n");


  c->cd();
  char runChar[50];  sprintf(runChar,", run %i",runNum);
  char hname[200];
  
  gStyle->SetOptStat(10);


  TH2F* h1 = (TH2F*)f->Get(fname);
  
  h1->Draw("colz");

  //applying draw options based on titles of histograms 

  if(string(fname).find("TPMatchEmul")!= std::string::npos){
    //int color[10]={12,10,3,4,5,6,7} ; 
    int color[10]={kGray+2,kWhite,kRed,kOrange,kGreen,kAzure,kViolet} ;
    gStyle->SetPalette(7, color) ;
    gStyle->SetOptStat(0);
    h1->GetZaxis()->SetRangeUser(-1,6) ;
  }
  else if(string(fname).find("EmulMapMaxIndex")!= std::string::npos){
    //int color[10]={12,10,3,4,5,6,7} ; 
    int color[10]={kGray+2,kWhite,kRed,kOrange,kGreen,kAzure,kViolet} ;
    gStyle->SetPalette(7, color) ;
    gStyle->SetOptStat(0);
    h1->GetZaxis()->SetRangeUser(-1,6) ;
  }
  else gStyle->SetPalette(1,0);
  
  if(string(fname).find("Fraction")!= std::string::npos){
    gStyle->SetOptStat(0);
  }

  if(string(fname).find("L1Ratio")!= std::string::npos){
    h1->SetMinimum(0);
    h1->SetMaximum(1.5);
    //if(h1->GetEntries()!=0)  c->SetLogz();
  }

  if(string(fname).find("spectrum")!= std::string::npos){
    h1->SetMinimum(0);
    h1->SetMaximum(256);
    if(h1->GetEntries()!=0)  c->SetLogz();
  }

  else if(string(fname).find("occupancy")!= std::string::npos){
    if(h1->GetEntries()!=0)  c->SetLogz();
  }
  else if(string(fname).find("TPComp")!= std::string::npos){
    if(h1->GetEntries()!=0)  c->SetLogz();
  }

  TH2F* Mask;

  if(string(fname).find("EEPlus")!= std::string::npos) Mask = (TH2F*)f->Get("MaskedTowersEEPlus");
  else if(string(fname).find("EEMinus")!= std::string::npos) Mask = (TH2F*)f->Get("MaskedTowersEEMinus");


  gStyle->SetHatchesSpacing(1.3);
  gStyle->SetHatchesLineWidth(0.05);

  for(int x=1;x!=Mask->GetNbinsX();++x){
    for(int y=1;y!=Mask->GetNbinsY();++y){
      if(Mask->GetBinContent(x,y)!=0){
	TBox b;
	b.SetFillStyle(3144);
	b.SetFillColor(1);
	b.DrawBox(x-11,y-11,x-10,y-10);
      }
    }
  }


  TH2F* MaskR;

  if(string(fname).find("EEPlus")!= std::string::npos) MaskR = (TH2F*)f->Get("MaskedReadOutEEPlus");
  else if(string(fname).find("EEMinus")!= std::string::npos) MaskR = (TH2F*)f->Get("MaskedReadOutEEMinus");

  //gStyle->SetHatchesSpacing(2.);
  //gStyle->SetHatchesLineWidth(0.2);

  for(int x=1;x!=MaskR->GetNbinsX();++x){
    for(int y=1;y!=MaskR->GetNbinsY();++y){
      if(MaskR->GetBinContent(x,y)!=0){
	TBox bR;
	bR.SetFillStyle(3109);
	bR.SetFillColor(1);
	bR.DrawBox(x-11,y-11,x-10,y-10);
      }
    }
  }



  char mytitle[100]; 
  sprintf(mytitle,"%s",h1->GetTitle()); 
  strcat(mytitle,runChar);
  h1->SetTitle(mytitle);



  TLine line2;
  //line.SetLineColor(1) ;  
  //line.SetLineStyle(1) ;  
  //line.SetLineWidth(1) ;

  

//drawing TT boundaries
  
  //note: for TTs each list is split into two because as one giant list root complains that there are too many arguments
  
  int ixTTEEHorizontal1[1381] = {1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50};
  
  int ixTTEEHorizontal2[1386] = {51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 100, 100, 100, 100, 100};
  
  
  
  int iyTTEEHorizontal1[1381] = {42, 46, 51, 56, 60, 61, 42, 46, 51, 56, 60, 61, 42, 46, 51, 56, 60, 61, 39, 42, 44, 46, 51, 56, 58, 60, 63, 66, 38, 42, 43, 46, 51, 56, 59, 60, 64, 66, 31, 34, 39, 43, 48, 51, 54, 59, 63, 68, 71, 76, 31, 33, 35, 39, 43, 44, 48, 50, 51, 52, 54, 58, 59, 63, 67, 69, 71, 76, 29, 31, 35, 39, 40, 42, 43, 46, 47, 48, 51, 54, 55, 56, 59, 60, 62, 63, 67, 71, 73, 76, 23, 26, 27, 31, 35, 36, 37, 38, 39, 43, 48, 51, 54, 59, 63, 64, 65, 66, 67, 71, 75, 76, 79, 81, 24, 26, 27, 31, 36, 39, 43, 48, 51, 54, 59, 63, 66, 71, 75, 76, 78, 81, 24, 28, 31, 32, 36, 41, 43, 46, 51, 56, 59, 61, 66, 70, 71, 74, 78, 81, 22, 24, 29, 31, 33, 36, 41, 44, 46, 47, 51, 55, 56, 58, 61, 66, 69, 71, 73, 78, 80, 81, 22, 25, 29, 33, 36, 38, 41, 44, 47, 51, 55, 58, 61, 64, 66, 69, 73, 77, 80, 81, 19, 21, 26, 28, 29, 34, 37, 41, 44, 48, 50, 51, 52, 54, 58, 61, 65, 68, 73, 74, 76, 81, 83, 86, 18, 21, 26, 30, 33, 38, 41, 45, 47, 51, 55, 57, 61, 64, 69, 72, 76, 81, 84, 86, 16, 22, 25, 27, 31, 36, 39, 42, 44, 48, 51, 54, 58, 60, 63, 66, 71, 75, 77, 80, 85, 86, 88, 16, 17, 22, 24, 27, 31, 32, 36, 38, 42, 44, 48, 49, 51, 53, 54, 58, 60, 64, 66, 70, 71, 75, 78, 80, 84, 86, 88, 15, 19, 23, 24, 28, 30, 32, 36, 39, 42, 45, 47, 48, 51, 54, 55, 57, 60, 63, 66, 70, 72, 74, 78, 79, 84, 87, 88, 19, 22, 26, 27, 29, 33, 35, 36, 39, 42, 45, 46, 48, 51, 54, 56, 57, 60, 63, 66, 67, 69, 73, 75, 76, 80, 81, 88, 19, 21, 26, 29, 32, 36, 40, 42, 46, 48, 51, 54, 56, 60, 62, 66, 70, 73, 76, 81, 88, 14, 16, 20, 22, 25, 26, 30, 31, 33, 36, 37, 41, 43, 46, 48, 51, 54, 56, 59, 61, 65, 66, 69, 71, 72, 76, 77, 81, 82, 86, 88, 93, 12, 18, 19, 22, 24, 28, 29, 31, 34, 36, 38, 41, 44, 46, 49, 51, 53, 56, 58, 61, 64, 66, 68, 71, 73, 74, 78, 79, 83, 84, 90, 93, 10, 12, 18, 23, 24, 28, 31, 35, 36, 38, 41, 44, 46, 49, 51, 53, 56, 58, 61, 64, 66, 67, 71, 74, 79, 84, 90, 92, 93, 11, 13, 17, 19, 22, 26, 27, 28, 31, 33, 34, 36, 39, 41, 44, 46, 49, 51, 53, 56, 58, 61, 63, 66, 68, 69, 71, 74, 75, 78, 80, 83, 85, 89, 91, 93, 11, 14, 16, 19, 21, 26, 30, 31, 34, 36, 38, 41, 45, 46, 50, 51, 52, 56, 57, 61, 64, 66, 68, 71, 72, 76, 78, 81, 83, 86, 88, 91, 93, 11, 15, 16, 20, 22, 25, 27, 30, 31, 34, 37, 39, 41, 42, 45, 47, 49, 51, 53, 55, 57, 60, 61, 63, 65, 68, 71, 73, 76, 77, 80, 82, 86, 87, 91, 96, 9, 11, 15, 18, 19, 22, 24, 28, 30, 31, 33, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 69, 71, 73, 75, 78, 80, 83, 84, 87, 91, 93, 96, 9, 12, 14, 19, 23, 25, 28, 31, 32, 36, 38, 39, 40, 41, 43, 45, 48, 49, 50, 51, 52, 53, 54, 57, 59, 61, 62, 63, 64, 66, 70, 71, 73, 74, 77, 79, 83, 88, 90, 93, 96, 8, 13, 15, 19, 21, 22, 25, 26, 31, 33, 36, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 66, 69, 71, 73, 74, 77, 80, 81, 83, 87, 89, 94, 96, 8, 13, 16, 18, 21, 26, 31, 33, 36, 39, 41, 44, 45, 46, 49, 51, 53, 56, 57, 58, 61, 63, 66, 69, 71, 73, 76, 81, 84, 86, 89, 94, 96, 8, 11, 16, 17, 21, 24, 28, 32, 35, 36, 37, 40, 41, 42, 44, 46, 48, 49, 51, 53, 54, 56, 58, 60, 61, 62, 65, 66, 67, 71, 74, 78, 81, 85, 86, 91, 94, 96, 8, 11, 12, 16, 19, 20, 21, 24, 28, 29, 32, 34, 36, 38, 40, 41, 42, 44, 46, 48, 50, 51, 52, 54, 56, 58, 60, 61, 62, 64, 66, 68, 69, 73, 74, 78, 81, 82, 83, 86, 90, 91, 94, 96, 7, 11, 14, 15, 16, 20, 22, 25, 27, 28, 31, 33, 35, 36, 38, 39, 41, 43, 44, 45, 46, 47, 49, 51, 53, 55, 56, 57, 58, 59, 61, 63, 64, 66, 69, 71, 74, 75, 77, 80, 82, 86, 87, 88, 91, 95, 96, 7, 11, 14, 16, 20, 23, 24, 26, 28, 31, 32, 35, 36, 38, 40, 41, 42, 43, 46, 48, 51, 54, 56, 59, 60, 61, 62, 64, 66, 69, 70, 71, 74, 76, 78, 79, 82, 86, 88, 91, 95, 96, 10, 11, 14, 16, 19, 23, 26, 28, 31, 36, 39, 41, 46, 49, 51, 53, 56, 61, 63, 66, 67, 71, 74, 76, 79, 83, 86, 88, 91, 92, 96, 6, 9, 13, 18, 21, 26, 30, 31, 34, 36, 39, 43, 46, 48, 51, 54, 56, 59, 61, 62, 65, 68, 71, 72, 76, 81, 84, 89, 93, 96, 98, 6, 10, 13, 14, 15, 18, 21, 22, 26, 28, 29, 32, 34, 37, 39, 43, 45, 46, 48, 51, 54, 56, 57, 59, 61, 62, 64, 68, 70, 73, 74, 76, 80, 81, 84, 87, 88, 89, 92, 96, 98, 5, 6, 9, 13, 16, 17, 18, 21, 24, 25, 26, 29, 33, 35, 38, 40, 41, 42, 43, 45, 46, 49, 51, 53, 56, 57, 59, 60, 61, 64, 67, 69, 73, 76, 77, 78, 81, 84, 85, 86, 89, 93, 96, 97, 98, 6, 8, 11, 13, 16, 20, 21, 24, 28, 31, 33, 34, 36, 38, 41, 45, 46, 49, 51, 53, 56, 57, 61, 64, 66, 68, 69, 71, 74, 78, 81, 82, 86, 89, 91, 94, 96, 98, 6, 9, 11, 13, 16, 21, 24, 29, 31, 35, 36, 41, 44, 46, 58, 61, 63, 66, 67, 71, 73, 78, 81, 86, 89, 91, 93, 96, 98, 6, 9, 13, 16, 21, 23, 26, 31, 34, 36, 38, 41, 44, 59, 61, 64, 66, 68, 71, 76, 79, 81, 86, 89, 93, 96, 101, 6, 8, 13, 16, 20, 21, 23, 26, 27, 31, 33, 35, 36, 39, 41, 43, 61, 63, 66, 67, 69, 71, 75, 76, 79, 81, 82, 86, 89, 94, 96, 101, 5, 7, 12, 13, 16, 20, 22, 23, 26, 30, 31, 34, 38, 42, 61, 64, 68, 71, 72, 76, 79, 80, 82, 86, 89, 90, 95, 97, 101, 4, 8, 13, 15, 16, 18, 20, 23, 25, 26, 31, 33, 38, 40, 41, 62, 64, 69, 71, 76, 77, 79, 82, 84, 86, 87, 89, 94, 98, 101, 4, 8, 13, 16, 19, 23, 26, 31, 34, 37, 41, 65, 68, 71, 76, 79, 83, 86, 89, 94, 98, 101, 4, 6, 9, 11, 12, 16, 19, 23, 26, 30, 31, 34, 36, 40, 66, 68, 71, 72, 76, 79, 83, 86, 90, 91, 93, 96, 98, 101, 4, 6, 8, 11, 12, 14, 15, 16, 18, 23, 26, 28, 29, 31, 33, 34, 36, 40, 66, 68, 69, 71, 73, 74, 76, 79, 84, 86, 87, 88, 90, 91, 94, 96, 98, 101, 4, 8, 12, 15, 17, 22, 23, 26, 29, 34, 35, 36, 38, 40, 64, 66, 67, 68, 73, 76, 79, 80, 85, 87, 90, 94, 98, 101, 4, 8, 12, 15, 18, 23, 25, 26, 28, 32, 33, 34, 36, 40, 66, 68, 69, 70, 74, 76, 77, 79, 84, 87, 90, 94, 98, 101, 4, 7, 12, 14, 18, 23, 26, 29, 34, 36, 40, 66, 68, 73, 76, 79, 84, 88, 90, 95, 98, 101};
  
  int iyTTEEHorizontal2[1386] = {4, 7, 12, 14, 18, 23, 26, 29, 34, 36, 40, 66, 68, 73, 76, 79, 84, 88, 90, 95, 98, 101, 4, 8, 12, 15, 18, 23, 25, 26, 28, 32, 33, 34, 36, 40, 66, 68, 69, 70, 74, 76, 77, 79, 84, 87, 90, 94, 98, 101, 4, 8, 12, 15, 17, 22, 23, 26, 29, 34, 35, 36, 38, 40, 64, 66, 67, 68, 73, 76, 79, 80, 85, 87, 90, 94, 98, 101, 4, 6, 8, 11, 12, 14, 15, 16, 18, 23, 26, 28, 29, 31, 33, 34, 36, 40, 66, 68, 69, 71, 73, 74, 76, 79, 84, 86, 87, 88, 90, 91, 94, 96, 98, 101, 4, 6, 9, 11, 12, 16, 19, 23, 26, 30, 31, 34, 36, 40, 66, 68, 71, 72, 76, 79, 83, 86, 90, 91, 93, 96, 98, 101, 4, 8, 13, 16, 19, 23, 26, 31, 34, 37, 41, 65, 68, 71, 76, 79, 83, 86, 89, 94, 98, 101, 4, 8, 13, 15, 16, 18, 20, 23, 25, 26, 31, 33, 38, 40, 41, 62, 64, 69, 71, 76, 77, 79, 82, 84, 86, 87, 89, 94, 98, 101, 5, 7, 12, 13, 16, 20, 22, 23, 26, 30, 31, 34, 38, 41, 42, 64, 68, 71, 72, 76, 79, 80, 82, 86, 89, 90, 95, 97, 101, 6, 8, 13, 16, 20, 21, 23, 26, 27, 31, 33, 35, 36, 39, 41, 43, 61, 63, 66, 67, 69, 71, 75, 76, 79, 81, 82, 86, 89, 94, 96, 101, 6, 9, 13, 16, 21, 23, 26, 31, 34, 36, 38, 41, 43, 44, 61, 64, 66, 68, 71, 76, 79, 81, 86, 89, 93, 96, 101, 6, 9, 11, 13, 16, 21, 24, 29, 31, 35, 36, 39, 41, 44, 46, 58, 61, 66, 67, 71, 73, 78, 81, 86, 89, 91, 93, 96, 98, 6, 8, 11, 13, 16, 20, 21, 24, 28, 31, 33, 34, 36, 38, 41, 45, 46, 49, 51, 53, 56, 57, 61, 64, 66, 68, 69, 71, 74, 78, 81, 82, 86, 89, 91, 94, 96, 98, 5, 6, 9, 13, 16, 17, 18, 21, 24, 25, 26, 29, 33, 35, 38, 41, 42, 43, 45, 46, 49, 51, 53, 56, 57, 59, 60, 61, 62, 64, 67, 69, 73, 76, 77, 78, 81, 84, 85, 86, 89, 93, 96, 97, 98, 6, 10, 13, 14, 15, 18, 21, 22, 26, 28, 29, 32, 34, 38, 40, 41, 43, 45, 46, 48, 51, 54, 56, 57, 59, 63, 65, 68, 70, 73, 74, 76, 80, 81, 84, 87, 88, 89, 92, 96, 98, 6, 9, 13, 18, 21, 26, 30, 31, 34, 37, 40, 41, 43, 46, 48, 51, 54, 56, 59, 63, 66, 68, 71, 72, 76, 81, 84, 89, 93, 96, 98, 10, 11, 14, 16, 19, 23, 26, 28, 31, 35, 36, 39, 41, 46, 49, 51, 53, 56, 61, 63, 66, 71, 74, 76, 79, 83, 86, 88, 91, 92, 96, 7, 11, 14, 16, 20, 23, 24, 26, 28, 31, 32, 33, 36, 38, 40, 41, 42, 43, 46, 48, 51, 54, 56, 59, 60, 61, 62, 64, 66, 67, 70, 71, 74, 76, 78, 79, 82, 86, 88, 91, 95, 96, 7, 11, 14, 15, 16, 20, 22, 25, 27, 28, 31, 33, 36, 38, 39, 41, 43, 44, 45, 46, 47, 49, 51, 53, 55, 56, 57, 58, 59, 61, 63, 64, 66, 67, 69, 71, 74, 75, 77, 80, 82, 86, 87, 88, 91, 95, 96, 8, 11, 12, 16, 19, 20, 21, 24, 28, 29, 33, 34, 36, 38, 40, 41, 42, 44, 46, 48, 50, 51, 52, 54, 56, 58, 60, 61, 62, 64, 66, 68, 70, 73, 74, 78, 81, 82, 83, 86, 90, 91, 94, 96, 8, 11, 16, 17, 21, 24, 28, 31, 35, 36, 37, 40, 41, 42, 44, 46, 48, 49, 51, 53, 54, 56, 58, 60, 61, 62, 65, 66, 67, 70, 74, 78, 81, 85, 86, 91, 94, 96, 8, 13, 16, 18, 21, 26, 29, 31, 33, 36, 39, 41, 44, 45, 46, 49, 51, 53, 56, 57, 58, 61, 63, 66, 69, 71, 76, 81, 84, 86, 89, 94, 96, 8, 13, 15, 19, 21, 22, 25, 28, 29, 31, 33, 36, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 66, 69, 71, 76, 77, 80, 81, 83, 87, 89, 94, 96, 9, 12, 14, 19, 23, 25, 28, 29, 31, 32, 36, 38, 39, 40, 41, 43, 45, 48, 49, 50, 51, 52, 53, 54, 57, 59, 61, 62, 63, 64, 66, 70, 71, 74, 77, 79, 83, 88, 90, 93, 96, 9, 11, 15, 18, 19, 22, 24, 27, 29, 31, 33, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 69, 71, 72, 74, 78, 80, 83, 84, 87, 91, 93, 96, 11, 15, 16, 20, 22, 25, 26, 29, 31, 34, 37, 39, 41, 42, 45, 47, 49, 51, 53, 55, 57, 60, 61, 63, 65, 68, 71, 72, 75, 77, 80, 82, 86, 87, 91, 96, 11, 14, 16, 19, 21, 24, 26, 30, 31, 34, 36, 38, 41, 45, 46, 50, 51, 52, 56, 57, 61, 64, 66, 68, 71, 72, 76, 81, 83, 86, 88, 91, 93, 11, 13, 17, 19, 22, 24, 27, 28, 31, 33, 34, 36, 39, 41, 44, 46, 49, 51, 53, 56, 58, 61, 63, 66, 68, 69, 71, 74, 75, 76, 80, 83, 85, 89, 91, 93, 10, 12, 18, 23, 28, 31, 35, 36, 38, 41, 44, 46, 49, 51, 53, 56, 58, 61, 64, 66, 67, 71, 74, 78, 79, 84, 90, 92, 93, 12, 18, 19, 23, 24, 28, 29, 31, 34, 36, 38, 41, 44, 46, 49, 51, 53, 56, 58, 61, 64, 66, 68, 71, 73, 74, 78, 80, 83, 84, 90, 93, 14, 16, 20, 21, 25, 26, 30, 31, 33, 36, 37, 41, 43, 46, 48, 51, 54, 56, 59, 61, 65, 66, 69, 71, 72, 76, 77, 80, 82, 86, 88, 93, 21, 26, 29, 32, 36, 40, 42, 46, 48, 51, 54, 56, 60, 62, 66, 70, 73, 76, 81, 83, 88, 21, 22, 26, 27, 29, 33, 35, 36, 39, 42, 45, 46, 48, 51, 54, 56, 57, 60, 63, 66, 67, 69, 73, 75, 76, 80, 83, 86, 87, 88, 15, 18, 23, 24, 28, 30, 32, 36, 39, 42, 45, 47, 48, 51, 54, 55, 57, 60, 63, 66, 70, 72, 74, 78, 79, 83, 87, 88, 16, 18, 22, 24, 27, 31, 32, 36, 38, 42, 44, 48, 49, 51, 53, 54, 58, 60, 64, 66, 70, 71, 75, 78, 80, 85, 86, 88, 16, 17, 22, 25, 27, 31, 36, 39, 42, 44, 48, 51, 54, 58, 60, 63, 66, 71, 75, 77, 80, 86, 87, 88, 18, 21, 26, 30, 33, 38, 41, 45, 47, 51, 55, 57, 61, 64, 69, 72, 76, 81, 82, 83, 84, 85, 86, 19, 21, 26, 28, 29, 34, 37, 41, 44, 48, 50, 51, 52, 54, 58, 61, 65, 68, 73, 74, 76, 81, 83, 86, 22, 25, 29, 33, 36, 38, 41, 44, 47, 51, 55, 58, 61, 64, 66, 69, 73, 77, 80, 81, 22, 24, 29, 31, 33, 36, 41, 44, 46, 47, 51, 55, 56, 58, 61, 66, 69, 71, 73, 78, 80, 81, 24, 28, 31, 32, 36, 41, 43, 46, 51, 56, 59, 61, 66, 70, 71, 74, 78, 81, 24, 26, 27, 31, 36, 39, 43, 48, 51, 54, 59, 63, 66, 71, 75, 76, 78, 81, 23, 26, 27, 31, 35, 36, 37, 38, 39, 43, 48, 51, 54, 59, 63, 64, 65, 66, 67, 71, 75, 76, 79, 81, 29, 31, 35, 39, 40, 42, 43, 46, 47, 48, 51, 54, 55, 56, 59, 60, 62, 63, 67, 71, 73, 76, 31, 33, 35, 39, 43, 44, 48, 50, 51, 52, 54, 58, 59, 63, 67, 69, 71, 76, 31, 34, 39, 43, 48, 51, 54, 59, 63, 68, 71, 76, 38, 42, 43, 46, 51, 56, 59, 60, 64, 66, 39, 42, 44, 46, 51, 56, 58, 60, 63, 66, 42, 46, 51, 56, 60, 61, 42, 46, 51, 56, 60, 61, 42, 46, 51, 56, 60};
  
  int ixTTEEVertical1[1381] = {42, 46, 51, 42, 46, 51, 42, 46, 51, 39, 42, 44, 46, 51, 38, 42, 43, 46, 51, 31, 34, 39, 43, 48, 51, 31, 33, 35, 39, 43, 44, 48, 50, 51, 29, 31, 35, 39, 40, 42, 43, 46, 47, 48, 51, 23, 26, 27, 31, 35, 36, 37, 38, 39, 43, 48, 51, 24, 26, 27, 31, 36, 39, 43, 48, 51, 24, 28, 31, 32, 36, 41, 43, 46, 51, 22, 24, 29, 31, 33, 36, 41, 44, 46, 47, 51, 22, 25, 29, 33, 36, 38, 41, 44, 47, 51, 19, 21, 26, 28, 29, 34, 37, 41, 44, 48, 50, 51, 18, 21, 26, 30, 33, 38, 41, 45, 47, 51, 16, 17, 22, 25, 27, 31, 36, 39, 42, 44, 48, 51, 16, 18, 22, 24, 27, 31, 32, 36, 38, 42, 44, 48, 49, 51, 15, 18, 23, 24, 28, 30, 32, 36, 39, 42, 45, 47, 48, 51, 21, 22, 26, 27, 29, 33, 35, 36, 39, 42, 45, 46, 48, 51, 21, 26, 29, 32, 36, 40, 42, 46, 48, 51, 14, 16, 20, 21, 25, 26, 30, 31, 33, 36, 37, 41, 43, 46, 48, 51, 12, 18, 19, 23, 24, 28, 29, 31, 34, 36, 38, 41, 44, 46, 49, 51, 10, 12, 18, 23, 28, 31, 35, 36, 38, 41, 44, 46, 49, 51, 11, 13, 17, 19, 22, 24, 27, 28, 31, 33, 34, 36, 39, 41, 44, 46, 49, 51, 11, 14, 16, 19, 21, 24, 26, 30, 31, 34, 36, 38, 41, 45, 46, 50, 51, 11, 15, 16, 20, 22, 25, 26, 29, 31, 34, 37, 39, 41, 42, 45, 47, 49, 51, 9, 11, 15, 18, 19, 22, 24, 27, 29, 31, 33, 37, 39, 41, 43, 45, 47, 49, 51, 9, 12, 14, 19, 23, 25, 28, 29, 31, 32, 36, 38, 39, 40, 41, 43, 45, 48, 49, 50, 51, 8, 13, 15, 19, 21, 22, 25, 28, 29, 31, 33, 36, 37, 39, 41, 43, 45, 47, 49, 51, 8, 13, 16, 18, 21, 26, 29, 31, 33, 36, 39, 41, 44, 45, 46, 49, 51, 8, 11, 16, 17, 21, 24, 28, 31, 35, 36, 37, 40, 41, 42, 44, 46, 48, 49, 51, 8, 11, 12, 16, 19, 20, 21, 24, 28, 29, 33, 34, 36, 38, 40, 41, 42, 44, 46, 48, 50, 51, 7, 11, 14, 15, 16, 20, 22, 25, 27, 28, 31, 33, 36, 38, 39, 41, 43, 44, 45, 46, 47, 49, 51, 7, 11, 14, 16, 20, 23, 24, 26, 28, 31, 32, 33, 36, 38, 40, 41, 42, 43, 46, 48, 51, 10, 11, 14, 16, 19, 23, 26, 28, 31, 35, 36, 39, 41, 46, 49, 51, 6, 9, 13, 18, 21, 26, 30, 31, 34, 37, 40, 41, 43, 46, 48, 51, 6, 10, 13, 14, 15, 18, 21, 22, 26, 28, 29, 32, 34, 38, 40, 41, 43, 45, 46, 48, 51, 5, 6, 9, 13, 16, 17, 18, 21, 24, 25, 26, 29, 33, 35, 38, 41, 42, 43, 45, 46, 49, 51, 6, 8, 11, 13, 16, 20, 21, 24, 28, 31, 33, 34, 36, 38, 41, 45, 46, 49, 51, 6, 9, 11, 13, 16, 21, 24, 29, 31, 35, 36, 39, 41, 44, 46, 6, 9, 13, 16, 21, 23, 26, 31, 34, 36, 38, 41, 43, 44, 6, 8, 13, 16, 20, 21, 23, 26, 27, 31, 33, 35, 36, 39, 41, 43, 5, 7, 12, 13, 16, 20, 22, 23, 26, 30, 31, 34, 38, 41, 42, 4, 8, 13, 15, 16, 18, 20, 23, 25, 26, 31, 33, 38, 40, 41, 4, 8, 13, 16, 19, 23, 26, 31, 34, 37, 41, 4, 6, 9, 11, 12, 16, 19, 23, 26, 30, 31, 34, 36, 40, 4, 6, 8, 11, 12, 14, 15, 16, 18, 23, 26, 28, 29, 31, 33, 34, 36, 40, 4, 8, 12, 15, 17, 22, 23, 26, 29, 34, 35, 36, 38, 40, 4, 8, 12, 15, 18, 23, 25, 26, 28, 32, 33, 34, 36, 40, 4, 7, 12, 14, 18, 23, 26, 29, 34, 36, 40, 4, 7, 12, 14, 18, 23, 26, 29, 34, 36, 40, 4, 8, 12, 15, 18, 23, 25, 26, 28, 32, 33, 34, 36, 40, 4, 8, 12, 15, 17, 22, 23, 26, 29, 34, 35, 36, 38, 40, 4, 6, 8, 11, 12, 14, 15, 16, 18, 23, 26, 28, 29, 31, 33, 34, 36, 40, 4, 6, 9, 11, 12, 16, 19, 23, 26, 30, 31, 34, 36, 40, 4, 8, 13, 16, 19, 23, 26, 31, 34, 37, 41, 4, 8, 13, 15, 16, 18, 20, 23, 25, 26, 31, 33, 38, 40, 41, 5, 7, 12, 13, 16, 20, 22, 23, 26, 30, 31, 34, 38, 42, 6, 8, 13, 16, 20, 21, 23, 26, 27, 31, 33, 35, 36, 39, 41, 43, 6, 9, 13, 16, 21, 23, 26, 31, 34, 36, 38, 41, 44, 6, 9, 11, 13, 16, 21, 24, 29, 31, 35, 36, 41, 44, 46, 6, 8, 11, 13, 16, 20, 21, 24, 28, 31, 33, 34, 36, 38, 41, 45, 46, 49, 51, 5, 6, 9, 13, 16, 17, 18, 21, 24, 25, 26, 29, 33, 35, 38, 40, 41, 42, 43, 45, 46, 49, 51, 6, 10, 13, 14, 15, 18, 21, 22, 26, 28, 29, 32, 34, 37, 39, 43, 45, 46, 48, 51, 6, 9, 13, 18, 21, 26, 30, 31, 34, 36, 39, 43, 46, 48, 51, 10, 11, 14, 16, 19, 23, 26, 28, 31, 36, 39, 41, 46, 49, 51, 7, 11, 14, 16, 20, 23, 24, 26, 28, 31, 32, 35, 36, 38, 40, 41, 42, 43, 46, 48, 51, 7, 11, 14, 15, 16, 20, 22, 25, 27, 28, 31, 33, 35, 36, 38, 39, 41, 43, 44, 45, 46, 47, 49, 51, 8, 11, 12, 16, 19, 20, 21, 24, 28, 29, 32, 34, 36, 38, 40, 41, 42, 44, 46, 48, 50, 51, 8, 11, 16, 17, 21, 24, 28, 32, 35, 36, 37, 40, 41, 42, 44, 46, 48, 49, 51, 8, 13, 16, 18, 21, 26, 31, 33, 36, 39, 41, 44, 45, 46, 49, 51, 8, 13, 15, 19, 21, 22, 25, 26, 31, 33, 36, 37, 39, 41, 43, 45, 47, 49, 51, 9, 12, 14, 19, 23, 25, 28, 31, 32, 36, 38, 39, 40, 41, 43, 45, 48, 49, 50, 51, 9, 11, 15, 18, 19, 22, 24, 28, 30, 31, 33, 37, 39, 41, 43, 45, 47, 49, 51, 11, 15, 16, 20, 22, 25, 27, 30, 31, 34, 37, 39, 41, 42, 45, 47, 49, 51, 11, 14, 16, 19, 21, 26, 30, 31, 34, 36, 38, 41, 45, 46, 50, 51, 11, 13, 17, 19, 22, 26, 27, 28, 31, 33, 34, 36, 39, 41, 44, 46, 49, 51, 10, 12, 18, 23, 24, 28, 31, 35, 36, 38, 41, 44, 46, 49, 51, 12, 18, 19, 22, 24, 28, 29, 31, 34, 36, 38, 41, 44, 46, 49, 51, 14, 16, 20, 22, 25, 26, 30, 31, 33, 36, 37, 41, 43, 46, 48, 51, 19, 21, 26, 29, 32, 36, 40, 42, 46, 48, 51, 19, 22, 26, 27, 29, 33, 35, 36, 39, 42, 45, 46, 48, 51, 15, 19, 23, 24, 28, 30, 32, 36, 39, 42, 45, 47, 48, 51, 16, 17, 22, 24, 27, 31, 32, 36, 38, 42, 44, 48, 49, 51, 16, 22, 25, 27, 31, 36, 39, 42, 44, 48, 51, 18, 21, 26, 30, 33, 38, 41, 45, 47, 51, 19, 21, 26, 28, 29, 34, 37, 41, 44, 48, 50, 51, 22, 25, 29, 33, 36, 38, 41, 44, 47, 51, 22, 24, 29, 31, 33, 36, 41, 44, 46, 47, 51, 24, 28, 31, 32, 36, 41, 43, 46, 51, 24, 26, 27, 31, 36, 39, 43, 48, 51, 23, 26, 27, 31, 35, 36, 37, 38, 39, 43, 48, 51, 29, 31, 35, 39, 40, 42, 43, 46, 47, 48, 51, 31, 33, 35, 39, 43, 44, 48, 50, 51, 31, 34, 39, 43, 48, 51, 38, 42, 43, 46, 51, 39, 42, 44, 46, 51, 42, 46, 51, 42, 46, 51, 42, 46, 51};

  int ixTTEEVertical2[1385] = {56, 60, 61, 56, 60, 61, 56, 60, 61, 56, 58, 60, 63, 66, 56, 59, 60, 64, 66, 54, 59, 63, 68, 71, 76, 52, 54, 58, 59, 63, 67, 69, 71, 76, 54, 55, 56, 59, 60, 62, 63, 67, 71, 73, 76, 54, 59, 63, 64, 65, 66, 67, 71, 75, 76, 79, 81, 54, 59, 63, 66, 71, 75, 76, 78, 81, 56, 59, 61, 66, 70, 71, 74, 78, 81, 55, 56, 58, 61, 66, 69, 71, 73, 78, 80, 81, 55, 58, 61, 64, 66, 69, 73, 77, 80, 81, 52, 54, 58, 61, 65, 68, 73, 74, 76, 81, 83, 86, 55, 57, 61, 64, 69, 72, 76, 81, 84, 86, 54, 58, 60, 63, 66, 71, 75, 77, 80, 86, 88, 53, 54, 58, 60, 64, 66, 70, 71, 75, 78, 80, 85, 86, 88, 54, 55, 57, 60, 63, 66, 70, 72, 74, 78, 79, 83, 87, 88, 54, 56, 57, 60, 63, 66, 67, 69, 73, 75, 76, 80, 83, 88, 54, 56, 60, 62, 66, 70, 73, 76, 81, 83, 88, 54, 56, 59, 61, 65, 66, 69, 71, 72, 76, 77, 80, 82, 86, 88, 93, 53, 56, 58, 61, 64, 66, 68, 71, 73, 74, 78, 80, 83, 84, 90, 93, 53, 56, 58, 61, 64, 66, 67, 71, 74, 78, 79, 84, 90, 92, 93, 53, 56, 58, 61, 63, 66, 68, 69, 71, 74, 75, 76, 80, 83, 85, 89, 91, 93, 52, 56, 57, 61, 64, 66, 68, 71, 72, 76, 81, 83, 86, 88, 91, 93, 53, 55, 57, 60, 61, 63, 65, 68, 71, 72, 75, 77, 80, 82, 86, 87, 91, 96, 53, 55, 57, 59, 61, 63, 65, 69, 71, 72, 74, 78, 80, 83, 84, 87, 91, 93, 96, 52, 53, 54, 57, 59, 61, 62, 63, 64, 66, 70, 71, 74, 77, 79, 83, 88, 90, 93, 96, 53, 55, 57, 59, 61, 63, 65, 66, 69, 71, 76, 77, 80, 81, 83, 87, 89, 94, 96, 53, 56, 57, 58, 61, 63, 66, 69, 71, 76, 81, 84, 86, 89, 94, 96, 53, 54, 56, 58, 60, 61, 62, 65, 66, 67, 70, 74, 78, 81, 85, 86, 91, 94, 96, 52, 54, 56, 58, 60, 61, 62, 64, 66, 68, 70, 73, 74, 78, 81, 82, 83, 86, 90, 91, 94, 96, 53, 55, 56, 57, 58, 59, 61, 63, 64, 66, 67, 69, 71, 74, 75, 77, 80, 82, 86, 87, 88, 91, 95, 96, 54, 56, 59, 60, 61, 62, 64, 66, 67, 70, 71, 74, 76, 78, 79, 82, 86, 88, 91, 95, 96, 53, 56, 61, 63, 66, 71, 74, 76, 79, 83, 86, 88, 91, 92, 96, 54, 56, 59, 63, 66, 68, 71, 72, 76, 81, 84, 89, 93, 96, 98, 54, 56, 57, 59, 63, 65, 68, 70, 73, 74, 76, 80, 81, 84, 87, 88, 89, 92, 96, 98, 53, 56, 57, 59, 60, 61, 62, 64, 67, 69, 73, 76, 77, 78, 81, 84, 85, 86, 89, 93, 96, 97, 98, 53, 56, 57, 61, 64, 66, 68, 69, 71, 74, 78, 81, 82, 86, 89, 91, 94, 96, 98, 58, 61, 66, 67, 71, 73, 78, 81, 86, 89, 91, 93, 96, 98, 61, 64, 66, 68, 71, 76, 79, 81, 86, 89, 93, 96, 101, 61, 63, 66, 67, 69, 71, 75, 76, 79, 81, 82, 86, 89, 94, 96, 101, 64, 68, 71, 72, 76, 79, 80, 82, 86, 89, 90, 95, 97, 101, 62, 64, 69, 71, 76, 77, 79, 82, 84, 86, 87, 89, 94, 98, 101, 65, 68, 71, 76, 79, 83, 86, 89, 94, 98, 101, 66, 68, 71, 72, 76, 79, 83, 86, 90, 91, 93, 96, 98, 101, 66, 68, 69, 71, 73, 74, 76, 79, 84, 86, 87, 88, 90, 91, 94, 96, 98, 101, 64, 66, 67, 68, 73, 76, 79, 80, 85, 87, 90, 94, 98, 101, 66, 68, 69, 70, 74, 76, 77, 79, 84, 87, 90, 94, 98, 101, 66, 68, 73, 76, 79, 84, 88, 90, 95, 98, 101, 66, 68, 73, 76, 79, 84, 88, 90, 95, 98, 101, 66, 68, 69, 70, 74, 76, 77, 79, 84, 87, 90, 94, 98, 101, 64, 66, 67, 68, 73, 76, 79, 80, 85, 87, 90, 94, 98, 101, 66, 68, 69, 71, 73, 74, 76, 79, 84, 86, 87, 88, 90, 91, 94, 96, 98, 101, 66, 68, 71, 72, 76, 79, 83, 86, 90, 91, 93, 96, 98, 101, 65, 68, 71, 76, 79, 83, 86, 89, 94, 98, 101, 62, 64, 69, 71, 76, 77, 79, 82, 84, 86, 87, 89, 94, 98, 101, 61, 64, 68, 71, 72, 76, 79, 80, 82, 86, 89, 90, 95, 97, 101, 61, 63, 66, 67, 69, 71, 75, 76, 79, 81, 82, 86, 89, 94, 96, 101, 59, 61, 64, 66, 68, 71, 76, 79, 81, 86, 89, 93, 96, 100, 58, 61, 63, 66, 67, 71, 73, 78, 81, 86, 89, 91, 93, 96, 98, 53, 56, 57, 61, 64, 66, 68, 69, 71, 74, 78, 81, 82, 86, 89, 91, 94, 96, 98, 53, 56, 57, 59, 60, 61, 64, 67, 69, 73, 76, 77, 78, 81, 84, 85, 86, 89, 93, 96, 97, 98, 54, 56, 57, 59, 61, 62, 64, 68, 70, 73, 74, 76, 80, 81, 84, 87, 88, 89, 92, 96, 98, 54, 56, 59, 61, 62, 65, 68, 71, 72, 76, 81, 84, 89, 93, 96, 98, 53, 56, 61, 63, 66, 67, 71, 74, 76, 79, 83, 86, 88, 91, 92, 96, 54, 56, 59, 60, 61, 62, 64, 66, 69, 70, 71, 74, 76, 78, 79, 82, 86, 88, 91, 95, 96, 53, 55, 56, 57, 58, 59, 61, 63, 64, 66, 69, 71, 74, 75, 77, 80, 82, 86, 87, 88, 91, 95, 96, 52, 54, 56, 58, 60, 61, 62, 64, 66, 68, 69, 73, 74, 78, 81, 82, 83, 86, 90, 91, 94, 96, 53, 54, 56, 58, 60, 61, 62, 65, 66, 67, 71, 74, 78, 81, 85, 86, 91, 94, 96, 53, 56, 57, 58, 61, 63, 66, 69, 71, 73, 76, 81, 84, 86, 89, 94, 96, 53, 55, 57, 59, 61, 63, 65, 66, 69, 71, 73, 74, 77, 80, 81, 83, 87, 89, 94, 96, 52, 53, 54, 57, 59, 61, 62, 63, 64, 66, 70, 71, 73, 74, 77, 79, 83, 88, 90, 93, 96, 53, 55, 57, 59, 61, 63, 65, 69, 71, 73, 75, 78, 80, 83, 84, 87, 91, 93, 96, 53, 55, 57, 60, 61, 63, 65, 68, 71, 73, 76, 77, 80, 82, 86, 87, 91, 96, 52, 56, 57, 61, 64, 66, 68, 71, 72, 76, 78, 81, 83, 86, 88, 91, 93, 53, 56, 58, 61, 63, 66, 68, 69, 71, 74, 75, 78, 80, 83, 85, 89, 91, 93, 53, 56, 58, 61, 64, 66, 67, 71, 74, 79, 84, 90, 92, 93, 53, 56, 58, 61, 64, 66, 68, 71, 73, 74, 78, 79, 83, 84, 90, 93, 54, 56, 59, 61, 65, 66, 69, 71, 72, 76, 77, 81, 82, 86, 88, 93, 54, 56, 60, 62, 66, 70, 73, 76, 81, 88, 54, 56, 57, 60, 63, 66, 67, 69, 73, 75, 76, 80, 81, 86, 87, 88, 54, 55, 57, 60, 63, 66, 70, 72, 74, 78, 79, 84, 87, 88, 53, 54, 58, 60, 64, 66, 70, 71, 75, 78, 80, 84, 86, 88, 54, 58, 60, 63, 66, 71, 75, 77, 80, 85, 87, 88, 55, 57, 61, 64, 69, 72, 76, 81, 82, 83, 84, 85, 86, 52, 54, 58, 61, 65, 68, 73, 74, 76, 81, 83, 86, 55, 58, 61, 64, 66, 69, 73, 77, 80, 81, 55, 56, 58, 61, 66, 69, 71, 73, 78, 80, 81, 56, 59, 61, 66, 70, 71, 74, 78, 81, 54, 59, 63, 66, 71, 75, 76, 78, 81, 54, 59, 63, 64, 65, 66, 67, 71, 75, 76, 79, 81, 54, 55, 56, 59, 60, 62, 63, 67, 71, 73, 76, 52, 54, 58, 59, 63, 67, 69, 71, 76, 54, 59, 63, 68, 71, 76, 56, 59, 60, 64, 66, 56, 58, 60, 63, 66, 56, 60, 61, 56, 60, 61, 56, 60};

  int iyTTEEVertical1[1381] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 90, 90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94, 94, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 99, 99, 99, 100, 100, 100};

  int iyTTEEVertical2[1385] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 52, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 90, 90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94, 94, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 99, 99, 99, 100, 100};



  line2.SetLineWidth(1);
  line2.SetLineStyle(3);

  int offset_vertical = 0;
  int offset_horizontal = 0;


  if(string(fname).find("EEMinus")!= std::string::npos){ //EE-
    offset_vertical = 102;
    offset_horizontal = 101;
  }

  
  
  //drawing horizontal TT boundaries
  
  for ( int i=0; i!=1381; i=i+1) {
    
    line2.DrawLine(abs(offset_horizontal-ixTTEEHorizontal1[i]), iyTTEEHorizontal1[i], 
		   abs(offset_horizontal-ixTTEEHorizontal1[i])+1, iyTTEEHorizontal1[i]);
    
  }
  
  for ( int i=0; i!=1386; i=i+1) {
    
    line2.DrawLine(abs(offset_horizontal-ixTTEEHorizontal2[i]), iyTTEEHorizontal2[i], 
		   abs(offset_horizontal-ixTTEEHorizontal2[i])+1, iyTTEEHorizontal2[i]);
    
  }
  
  
  // //drawing vertical TT boundaries
  
  for ( int i=0; i!=1381; i=i+1) {
    
    line2.DrawLine(abs(offset_vertical-ixTTEEVertical1[i]), iyTTEEVertical1[i], 
		   abs(offset_vertical-ixTTEEVertical1[i]), iyTTEEVertical1[i]+1);
    
  }
  
  for ( int i=0; i!=1385; i=i+1) {
    
    line2.DrawLine(abs(offset_vertical-ixTTEEVertical2[i]), iyTTEEVertical2[i], 
		   abs(offset_vertical-ixTTEEVertical2[i]), iyTTEEVertical2[i]+1);
    
  }
  

  
  //drawing TCC boundaries
  
  int ixTCCEEHorizontal[699]={1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 93, 93, 93, 94, 94, 94, 95, 95, 95, 96, 96, 96, 97, 97, 97, 98, 98, 98, 99, 99, 99, 100, 100};
  
  
  int iyTCCEEHorizontal[699]={42, 60, 61, 42, 60, 61, 42, 60, 61, 42, 60, 66, 42, 60, 66, 43, 59, 76, 43, 59, 76, 43, 59, 76, 26, 43, 59, 76, 81, 26, 43, 59, 76, 81, 28, 43, 59, 74, 81, 29, 44, 58, 73, 81, 29, 44, 58, 73, 81, 29, 44, 50, 52, 58, 73, 86, 30, 45, 47, 55, 57, 72, 86, 31, 39, 44, 58, 63, 71, 88, 32, 38, 44, 58, 64, 70, 88, 32, 36, 45, 57, 66, 70, 88, 33, 35, 46, 56, 67, 69, 88, 32, 46, 56, 70, 88, 16, 30, 33, 46, 56, 69, 72, 86, 93, 18, 29, 34, 46, 56, 68, 73, 84, 93, 18, 28, 36, 46, 56, 66, 74, 84, 93, 19, 27, 36, 46, 56, 66, 75, 83, 93, 19, 26, 36, 46, 56, 66, 76, 83, 93, 22, 25, 37, 47, 55, 65, 77, 80, 96, 22, 24, 37, 47, 55, 65, 78, 80, 96, 23, 25, 38, 48, 54, 64, 77, 79, 96, 22, 25, 39, 47, 55, 63, 77, 80, 96, 21, 26, 39, 46, 56, 63, 76, 81, 96, 21, 28, 41, 48, 54, 61, 74, 81, 96, 20, 29, 41, 48, 54, 61, 73, 82, 96, 20, 31, 41, 47, 55, 61, 71, 82, 96, 7, 20, 31, 41, 48, 54, 61, 71, 82, 95, 96, 10, 19, 31, 41, 49, 53, 61, 71, 83, 92, 96, 13, 18, 34, 43, 48, 54, 59, 68, 84, 89, 98, 13, 14, 15, 18, 34, 43, 48, 54, 59, 68, 84, 87, 88, 89, 98, 16, 17, 18, 35, 45, 49, 53, 57, 67, 84, 85, 86, 98, 16, 20, 36, 45, 49, 53, 57, 64, 82, 86, 98, 16, 21, 36, 44, 46, 58, 63, 81, 86, 98, 16, 26, 41, 44, 61, 76, 86, 101, 16, 27, 41, 43, 61, 75, 86, 101, 16, 30, 42, 61, 72, 86, 101, 16, 33, 41, 69, 86, 101, 16, 34, 41, 68, 86, 101, 16, 40, 86, 101, 15, 40, 87, 101, 15, 40, 87, 101, 15, 40, 87, 101, 14, 40, 88, 101, 14, 40, 88, 101, 15, 40, 87, 101, 15, 40, 87, 101, 15, 40, 87, 101, 16, 40, 86, 101, 16, 34, 41, 68, 86, 101, 16, 33, 41, 69, 86, 101, 16, 30, 41, 42, 72, 86, 101, 16, 27, 41, 43, 61, 75, 86, 101, 16, 26, 41, 44, 61, 76, 86, 101, 16, 21, 39, 44, 46, 58, 66, 81, 86, 98, 16, 20, 38, 45, 49, 53, 57, 66, 82, 86, 98, 16, 17, 18, 35, 45, 49, 53, 57, 67, 84, 85, 86, 98, 13, 14, 15, 18, 34, 43, 48, 54, 59, 68, 84, 87, 88, 89, 98, 13, 18, 34, 43, 48, 54, 59, 68, 84, 89, 98, 10, 19, 31, 41, 49, 53, 61, 71, 83, 92, 96, 7, 20, 31, 41, 48, 54, 61, 71, 82, 95, 96, 20, 31, 41, 47, 55, 61, 71, 82, 96, 20, 29, 41, 48, 54, 61, 73, 82, 96, 21, 28, 41, 48, 54, 61, 74, 81, 96, 21, 26, 39, 46, 56, 63, 76, 81, 96, 22, 25, 39, 47, 55, 63, 77, 80, 96, 23, 25, 38, 48, 54, 64, 77, 79, 96, 22, 24, 37, 47, 55, 65, 78, 80, 96, 22, 25, 37, 47, 55, 65, 77, 80, 96, 19, 26, 36, 46, 56, 66, 76, 83, 93, 19, 27, 36, 46, 56, 66, 75, 83, 93, 18, 28, 36, 46, 56, 66, 74, 84, 93, 18, 29, 34, 46, 56, 68, 73, 84, 93, 16, 30, 33, 46, 56, 69, 72, 86, 93, 32, 46, 56, 70, 88, 33, 35, 46, 56, 67, 69, 88, 32, 36, 45, 57, 66, 70, 88, 32, 38, 44, 58, 64, 70, 88, 31, 39, 44, 58, 63, 71, 88, 30, 45, 47, 55, 57, 72, 86, 29, 44, 50, 52, 58, 73, 86, 29, 44, 58, 73, 81, 29, 44, 58, 73, 81, 28, 43, 59, 74, 81, 26, 43, 59, 76, 81, 26, 43, 59, 76, 81, 43, 59, 76, 43, 59, 76, 43, 59, 76, 42, 60, 66, 42, 60, 66, 42, 60, 61, 42, 60, 61, 42, 60};
  
  
  
  
  
  int ixTCCEEVertical[729]={51, 61, 51, 61, 51, 61, 51, 66, 51, 66, 34, 51, 68, 76, 35, 51, 67, 76, 35, 51, 67, 76, 35, 51, 67, 81, 36, 51, 66, 81, 36, 51, 66, 81, 36, 51, 66, 81, 38, 51, 64, 81, 21, 37, 50, 51, 52, 65, 81, 86, 21, 38, 47, 51, 55, 64, 81, 86, 22, 39, 51, 63, 80, 88, 22, 38, 51, 64, 80, 88, 24, 36, 39, 51, 63, 66, 78, 88, 26, 35, 39, 51, 63, 67, 76, 88, 26, 32, 40, 51, 62, 70, 76, 88, 26, 30, 41, 51, 61, 72, 76, 93, 28, 29, 41, 51, 61, 73, 74, 93, 28, 41, 51, 61, 74, 93, 27, 28, 41, 51, 61, 74, 75, 93, 26, 30, 41, 51, 61, 72, 76, 93, 11, 25, 31, 42, 51, 60, 71, 77, 91, 96, 11, 24, 31, 43, 51, 59, 71, 78, 91, 96, 12, 23, 32, 43, 51, 59, 70, 79, 90, 96, 15, 22, 33, 43, 51, 59, 69, 80, 87, 96, 16, 21, 33, 44, 51, 58, 69, 81, 86, 96, 17, 21, 36, 44, 51, 58, 66, 81, 85, 96, 19, 20, 21, 36, 44, 51, 58, 66, 81, 82, 83, 96, 20, 22, 36, 45, 51, 57, 66, 80, 82, 96, 20, 23, 38, 46, 51, 56, 64, 79, 82, 96, 19, 23, 39, 46, 51, 56, 63, 79, 83, 96, 18, 26, 41, 46, 51, 56, 63, 76, 84, 98, 18, 28, 41, 46, 51, 56, 63, 74, 84, 98, 17, 29, 41, 46, 51, 56, 62, 73, 85, 98, 16, 31, 41, 46, 51, 56, 61, 71, 86, 98, 16, 31, 41, 46, 61, 71, 86, 98, 16, 36, 43, 44, 66, 86, 101, 6, 16, 36, 43, 66, 86, 96, 101, 12, 16, 38, 42, 64, 86, 90, 101, 15, 16, 18, 38, 40, 41, 62, 64, 84, 86, 87, 101, 16, 19, 41, 83, 86, 101, 16, 26, 30, 31, 40, 71, 72, 76, 86, 101, 15, 28, 29, 31, 33, 34, 40, 68, 69, 71, 73, 74, 87, 101, 15, 35, 36, 38, 40, 64, 66, 67, 87, 101, 15, 40, 87, 101, 14, 40, 88, 101, 14, 40, 88, 101, 15, 40, 87, 101, 15, 35, 36, 38, 40, 64, 66, 67, 87, 101, 15, 28, 29, 31, 33, 34, 40, 68, 69, 71, 73, 74, 87, 101, 16, 26, 30, 31, 40, 71, 72, 76, 86, 101, 16, 19, 41, 83, 86, 101, 15, 16, 18, 38, 40, 41, 62, 64, 84, 86, 87, 101, 12, 16, 38, 42, 64, 86, 90, 101, 6, 16, 36, 43, 66, 86, 96, 101, 16, 36, 44, 59, 66, 86, 100, 16, 31, 41, 46, 61, 71, 86, 98, 16, 31, 41, 46, 51, 56, 61, 71, 86, 98, 17, 29, 40, 46, 51, 56, 61, 73, 85, 98, 18, 28, 39, 46, 51, 56, 61, 74, 84, 98, 18, 26, 39, 46, 51, 56, 61, 76, 84, 98, 19, 23, 39, 46, 51, 56, 63, 79, 83, 96, 20, 23, 38, 46, 51, 56, 64, 79, 82, 96, 20, 22, 36, 45, 51, 57, 66, 80, 82, 96, 19, 20, 21, 36, 44, 51, 58, 66, 81, 82, 83, 96, 17, 21, 36, 44, 51, 58, 66, 81, 85, 96, 16, 21, 33, 44, 51, 58, 69, 81, 86, 96, 15, 22, 33, 43, 51, 59, 69, 80, 87, 96, 12, 23, 32, 43, 51, 59, 70, 79, 90, 96, 11, 24, 31, 43, 51, 59, 71, 78, 91, 96, 11, 25, 31, 42, 51, 60, 71, 77, 91, 96, 26, 30, 41, 51, 61, 72, 76, 93, 27, 28, 41, 51, 61, 74, 75, 93, 28, 41, 51, 61, 74, 93, 28, 29, 41, 51, 61, 73, 74, 93, 26, 30, 41, 51, 61, 72, 76, 93, 26, 32, 40, 51, 62, 70, 76, 88, 26, 35, 39, 51, 63, 67, 76, 88, 24, 36, 39, 51, 63, 66, 78, 88, 22, 38, 51, 64, 80, 88, 22, 39, 51, 63, 80, 88, 21, 38, 47, 51, 55, 64, 81, 86, 21, 37, 50, 51, 52, 65, 81, 86, 38, 51, 64, 81, 36, 51, 66, 81, 36, 51, 66, 81, 36, 51, 66, 81, 35, 51, 67, 81, 35, 51, 67, 76, 35, 51, 67, 76, 34, 51, 68, 76, 51, 66, 51, 66, 51, 61, 51, 61, 51};
  
  int iyTCCEEVertical[729]={1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 42, 42, 43, 43, 43, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 45, 45, 45, 45, 45, 45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 67, 67, 67, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 70, 70, 70, 71, 71, 71, 71, 71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 75, 75, 75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 86, 87, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 89, 89, 89, 89, 90, 90, 90, 90, 91, 91, 91, 91, 92, 92, 92, 92, 93, 93, 93, 93, 94, 94, 94, 94, 95, 95, 95, 95, 96, 96, 97, 97, 98, 98, 99, 99, 100};
  
  
  line2.SetLineWidth(1);
  line2.SetLineStyle(1);
  
  //drawing horizontal TCC boundaries
  
  for ( int i=0; i<699; i=i+1) {
    
    line2.DrawLine(abs(offset_horizontal-ixTCCEEHorizontal[i]), iyTCCEEHorizontal[i], 
	       abs(offset_horizontal-ixTCCEEHorizontal[i])+1, iyTCCEEHorizontal[i]);
    
  }
  
  //drawing vertical TCC boundaries
  
  for ( int i=0; i<729; i=i+1) {
    
    line2.DrawLine(abs(offset_vertical-ixTCCEEVertical[i]), iyTCCEEVertical[i], 
	       abs(offset_vertical-ixTCCEEVertical[i]), iyTCCEEVertical[i]+1);
    
  }
  
  
  
  //drawing sector boundaries
  
  int ixSectorsEE[202] = {61, 61, 60, 60, 59, 59, 58, 58, 57, 57, 55, 55, 45, 45, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 45, 45, 55, 55, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 0,100,100, 97, 97, 95, 95, 92, 92, 87, 87, 85, 85, 80, 80, 75, 75, 65, 65, 60, 60, 40, 40, 35, 35, 25, 25, 20, 20, 15, 15, 13, 13,  8,  8,  5,  5,  3,  3,  0,  0,  3,  3,  5,  5,  8,  8, 13, 13, 15, 15, 20, 20, 25, 25, 35, 35, 40, 40, 60, 60, 65, 65, 75, 75, 80, 80, 85, 85, 87, 87, 92, 92, 95, 95, 97, 97,100,100,  0, 61, 65, 65, 70, 70, 80, 80, 90, 90, 92,  0, 61, 65, 65, 90, 90, 97,  0, 57, 60, 60, 65, 65, 70, 70, 75, 75, 80, 80,  0, 50, 50,  0, 43, 40, 40, 35, 35, 30, 30, 25, 25, 20, 20,  0, 39, 35, 35, 10, 10,  3,  0, 39, 35, 35, 30, 30, 20, 20, 10, 10,  8,  0, 45, 45, 40, 40, 35, 35,  0, 55, 55, 60, 60, 65, 65};
  
  int iySectorsEE[202] = {50, 55, 55, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 60, 60, 59, 59, 58, 58, 57, 57, 55, 55, 45, 45, 43, 43, 42, 42, 41, 41, 40, 40, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 45, 45, 50,  0, 50, 60, 60, 65, 65, 75, 75, 80, 80, 85, 85, 87, 87, 92, 92, 95, 95, 97, 97,100,100, 97, 97, 95, 95, 92, 92, 87, 87, 85, 85, 80, 80, 75, 75, 65, 65, 60, 60, 40, 40, 35, 35, 25, 25, 20, 20, 15, 15, 13, 13,  8,  8,  5,  5,  3,  3,  0,  0,  3,  3,  5,  5,  8,  8, 13, 13, 15, 15, 20, 20, 25, 25, 35, 35, 40, 40, 50,  0, 45, 45, 40, 40, 35, 35, 30, 30, 25, 25,  0, 50, 50, 55, 55, 60, 60,  0, 60, 60, 65, 65, 70, 70, 75, 75, 85, 85, 87,  0, 61,100,  0, 60, 60, 65, 65, 70, 70, 75, 75, 85, 85, 87,  0, 50, 50, 55, 55, 60, 60,  0, 45, 45, 40, 40, 35, 35, 30, 30, 25, 25,  0, 39, 30, 30, 15, 15,  5,  0, 39, 30, 30, 15, 15,  5};
  
  line2.SetLineWidth(3);
  
  
  
  for ( int i=0; i<201; i=i+1) {
    if ( (ixSectorsEE[i]!=0 || iySectorsEE[i]!=0) && 
	 (ixSectorsEE[i+1]!=0 || iySectorsEE[i+1]!=0) ) {
      line2.DrawLine(ixSectorsEE[i]+1, iySectorsEE[i]+1, 
		 ixSectorsEE[i+1]+1, iySectorsEE[i+1]+1);
    }
  }
  
  
  //printing TT ID numbers
  
  
  int ixLabels[720]={99, 99, 97, 97, 95, 94, 92, 91, 87, 84, 79, 77, 74, 69, 64, 61, 58, 54, 47, 43, 40, 37, 32, 27, 24, 22, 17, 14, 10, 9, 7, 6, 4, 4, 2, 2, 2, 2, 4, 4, 6, 7, 9, 10, 14, 17, 22, 24, 27, 32, 37, 40, 43, 47, 54, 58, 61, 64, 69, 74, 77, 79, 84, 87, 91, 92, 94, 95, 97, 97, 99, 99, 96, 96, 94, 94, 92, 91, 89, 87, 84, 82, 78, 75, 72, 69, 65, 61, 57, 52, 49, 44, 40, 36, 32, 29, 26, 23, 19, 16, 14, 12, 10, 9, 7, 7, 5, 5, 5, 5, 7, 7, 9, 10, 12, 14, 16, 19, 23, 26, 29, 32, 36, 40, 44, 49, 52, 57, 61, 65, 69, 72, 75, 78, 82, 85, 87, 89, 91, 92, 94, 94, 96, 96, 92, 92, 91, 90, 89, 87, 85, 84, 81, 78, 76, 73, 70, 67, 64, 60, 57, 52, 49, 44, 41, 37, 34, 31, 28, 25, 23, 20, 17, 16, 14, 12, 11, 10, 9, 9, 9, 9, 10, 11, 12, 14, 16, 17, 20, 23, 25, 28, 31, 34, 37, 41, 44, 49, 52, 57, 60, 64, 67, 70, 73, 76, 78, 81, 84, 85, 87, 89, 90, 91, 92, 92, 88, 87, 87, 87, 87, 84, 82, 81, 79, 76, 74, 71, 68, 66, 62, 59, 56, 53, 48, 45, 42, 39, 35, 33, 30, 27, 25, 23, 20, 19, 17, 14, 14, 14, 14, 13, 13, 14, 14, 14, 14, 17, 19, 20, 22, 25, 27, 30, 33, 35, 39, 42, 45, 48, 53, 56, 59, 62, 66, 68, 71, 74, 76, 78, 81, 82, 84, 87, 87, 87, 87, 88, 85, 84, 83, 84, 82, 80, 79, 78, 75, 74, 72, 69, 67, 64, 61, 58, 56, 52, 49, 45, 43, 40, 37, 34, 32, 29, 28, 26, 23, 22, 21, 19, 17, 18, 17, 16, 16, 17, 18, 17, 19, 21, 22, 23, 26, 27, 29, 32, 34, 37, 40, 43, 45, 49, 52, 56, 58, 61, 64, 67, 69, 72, 73, 75, 78, 79, 80, 82, 84, 83, 84, 85, 82, 80, 80, 80, 79, 78, 77, 76, 74, 72, 69, 67, 64, 62, 59, 57, 54, 52, 49, 47, 44, 42, 39, 37, 34, 32, 29, 27, 25, 24, 23, 22, 21, 21, 21, 19, 19, 21, 21, 21, 22, 23, 24, 25, 27, 29, 32, 34, 37, 39, 42, 44, 47, 49, 52, 54, 57, 59, 62, 64, 67, 69, 72, 74, 76, 77, 78, 79, 80, 80, 80, 82, 77, 77, 77, 77, 76, 74, 74, 72, 71, 69, 67, 66, 64, 62, 59, 57, 54, 52, 49, 47, 44, 42, 39, 37, 35, 34, 32, 30, 29, 27, 27, 25, 24, 24, 24, 24, 24, 24, 24, 24, 25, 27, 27, 29, 30, 32, 34, 35, 37, 39, 42, 44, 47, 49, 52, 54, 57, 59, 62, 64, 66, 67, 69, 71, 72, 74, 74, 76, 77, 77, 77, 77, 74, 74, 74, 74, 72, 72, 71, 69, 69, 67, 65, 64, 62, 59, 58, 55, 54, 52, 49, 47, 46, 43, 42, 39, 37, 36, 34, 33, 32, 30, 29, 29, 27, 27, 27, 27, 27, 27, 27, 27, 29, 29, 30, 32, 32, 34, 36, 37, 39, 42, 43, 46, 47, 49, 52, 54, 55, 58, 59, 62, 64, 65, 67, 68, 69, 71, 72, 72, 74, 74, 74, 74, 71, 71, 69, 69, 69, 69, 69, 67, 66, 64, 62, 62, 60, 59, 57, 55, 54, 52, 49, 47, 46, 44, 42, 41, 39, 39, 37, 35, 34, 32, 32, 32, 32, 32, 30, 30, 30, 30, 32, 32, 32, 32, 32, 34, 35, 37, 39, 39, 41, 42, 44, 46, 47, 49, 52, 54, 55, 57, 59, 60, 62, 62, 64, 66, 67, 69, 69, 69, 69, 69, 71, 71, 67, 67, 66, 64, 62, 60, 57, 54, 52, 49, 47, 44, 41, 39, 37, 35, 34, 34, 34, 34, 35, 37, 39, 41, 44, 47, 49, 52, 54, 57, 60, 62, 64, 66, 67, 67, 64, 63, 62, 62, 60, 59, 56, 54, 52, 49, 47, 45, 42, 42, 39, 39, 38, 37, 37, 38, 39, 39, 41, 42, 45, 47, 49, 52, 54, 56, 59, 59, 62, 62, 63, 64};
  
  int iyLabels[720]={54, 58, 61, 64, 69, 74, 77, 79, 84, 87, 91, 92, 94, 95, 97, 97, 99, 99, 99, 99, 97, 96, 94, 94, 91, 91, 86, 84, 79, 77, 74, 69, 64, 61, 57, 52, 47, 43, 40, 37, 32, 27, 24, 22, 17, 14, 10, 9, 7, 6, 4, 4, 2, 2, 2, 2, 4, 5, 7, 7, 10, 10, 15, 17, 22, 24, 27, 32, 37, 40, 44, 49, 52, 57, 61, 65, 69, 72, 75, 78, 81, 84, 87, 89, 91, 92, 94, 94, 96, 96, 96, 95, 94, 94, 92, 91, 89, 86, 85, 82, 78, 75, 72, 68, 64, 60, 57, 52, 49, 44, 40, 36, 32, 29, 26, 23, 19, 16, 14, 12, 10, 9, 7, 7, 5, 5, 5, 6, 7, 7, 9, 10, 12, 15, 16, 19, 23, 26, 29, 33, 37, 41, 44, 49, 52, 57, 60, 64, 67, 70, 73, 76, 78, 81, 84, 85, 87, 89, 90, 91, 92, 92, 91, 91, 91, 90, 89, 87, 85, 84, 81, 78, 76, 73, 70, 67, 64, 60, 57, 52, 49, 44, 41, 37, 34, 31, 28, 25, 23, 20, 17, 16, 14, 12, 11, 10, 9, 9, 10, 10, 10, 11, 12, 14, 16, 17, 20, 23, 25, 28, 31, 34, 37, 41, 44, 49, 53, 56, 59, 62, 66, 68, 71, 74, 76, 78, 81, 82, 84, 87, 87, 87, 87, 88, 88, 87, 87, 87, 86, 84, 82, 81, 78, 76, 74, 71, 67, 65, 62, 59, 56, 52, 48, 45, 42, 39, 35, 33, 30, 27, 25, 23, 20, 19, 17, 14, 14, 14, 14, 13, 13, 14, 14, 14, 15, 17, 19, 20, 23, 25, 27, 30, 34, 36, 39, 42, 45, 49, 52, 56, 58, 61, 64, 67, 69, 72, 73, 75, 78, 79, 80, 82, 84, 83, 84, 85, 85, 84, 83, 83, 82, 80, 79, 78, 75, 74, 72, 69, 67, 64, 61, 58, 55, 52, 49, 45, 43, 40, 37, 34, 32, 29, 28, 26, 23, 22, 21, 19, 17, 18, 17, 16, 16, 17, 18, 18, 19, 21, 22, 23, 26, 27, 29, 32, 34, 37, 40, 43, 46, 49, 52, 54, 57, 59, 62, 64, 67, 69, 71, 74, 76, 77, 78, 79, 80, 80, 80, 82, 81, 80, 80, 79, 79, 77, 77, 75, 73, 71, 69, 66, 64, 62, 59, 57, 54, 52, 49, 47, 44, 42, 39, 37, 34, 32, 30, 27, 25, 24, 23, 22, 21, 21, 21, 19, 20, 21, 21, 22, 22, 24, 24, 26, 28, 30, 32, 35, 37, 39, 42, 44, 47, 49, 52, 54, 57, 59, 62, 64, 66, 67, 69, 71, 72, 74, 74, 76, 77, 77, 77, 77, 77, 77, 77, 77, 75, 74, 74, 72, 70, 69, 67, 66, 63, 62, 59, 56, 54, 51, 49, 47, 44, 42, 39, 37, 35, 34, 32, 30, 29, 27, 27, 25, 24, 24, 24, 24, 24, 24, 24, 24, 26, 27, 27, 29, 31, 32, 34, 35, 38, 39, 42, 45, 47, 50, 52, 54, 55, 58, 59, 62, 64, 65, 67, 68, 69, 71, 72, 72, 74, 74, 74, 74, 74, 74, 73, 74, 72, 72, 71, 69, 69, 67, 64, 63, 61, 59, 58, 55, 53, 51, 49, 47, 46, 43, 42, 39, 37, 36, 34, 33, 32, 30, 29, 29, 27, 27, 27, 27, 27, 27, 28, 27, 29, 29, 30, 32, 32, 34, 37, 38, 40, 42, 43, 46, 48, 50, 52, 54, 55, 57, 59, 60, 61, 62, 64, 66, 67, 68, 69, 69, 69, 69, 71, 71, 71, 71, 69, 69, 69, 68, 68, 67, 65, 64, 62, 61, 60, 58, 56, 54, 54, 51, 49, 47, 46, 44, 42, 41, 40, 39, 37, 35, 34, 33, 32, 32, 32, 32, 30, 30, 30, 30, 32, 32, 32, 33, 33, 34, 36, 37, 39, 40, 41, 43, 45, 47, 47, 50, 52, 54, 57, 60, 62, 64, 66, 67, 67, 66, 66, 66, 64, 62, 59, 57, 54, 52, 49, 47, 44, 41, 39, 37, 35, 34, 34, 35, 35, 35, 37, 39, 42, 44, 47, 49, 52, 54, 56, 59, 59, 62, 62, 63, 64, 64, 63, 62, 62, 59, 59, 56, 54, 52, 49, 47, 45, 42, 42, 39, 39, 38, 37, 37, 38, 39, 39, 42, 42, 45, 47, 49};
 
  int bincontentLabels[720]={3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 7, 8, 5, 6, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 11, 12, 9, 10, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 15, 16, 13, 14, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 19, 20, 17, 18, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 23, 21, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25, 27, 25};


  for(int i=0; i!= 720; ++i) label2->SetBinContent(ixLabels[i],iyLabels[i],bincontentLabels[i]);
  
  label2->Draw("text same");
  

//printing Sector numbers  
  TLatex txt2;
  if(string(fname).find("EEMinus")!= std::string::npos){ //EE-
    txt2.DrawText(27, 97, Form("-%d",1));
    txt2.DrawText(0, 77, Form("-%d",2));
    txt2.DrawText(-5, 35, Form("-%d",3));
    txt2.DrawText(12, 7, Form("-%d",4));
    txt2.DrawText(46, -5, Form("-%d",5));
    txt2.DrawText(82, 8, Form("-%d",6));
    txt2.DrawText(99, 36, Form("-%d",7));
    txt2.DrawText(94, 77, Form("-%d",8));
    txt2.DrawText(67, 97, Form("-%d",9));
  }
  else{
    txt2.DrawText(27, 97, Form("+%d",1));
    txt2.DrawText(0, 77, Form("+%d",2));
    txt2.DrawText(-5, 35, Form("+%d",3));
    txt2.DrawText(12, 7, Form("+%d",4));
    txt2.DrawText(46, -5, Form("+%d",5));
    txt2.DrawText(82, 8, Form("+%d",6));
    txt2.DrawText(99, 36, Form("+%d",7));
    txt2.DrawText(94, 77, Form("+%d",8));
    txt2.DrawText(67, 97, Form("+%d",9));
  }


  iphilabels->SetMarkerSize(0.6);
  //
  iphilabels->SetBinContent(113,64,1);
  iphilabels->SetBinContent(113,59,72);
  iphilabels->SetBinContent(113,54,71);
  //
  iphilabels->SetBinContent(113,69,2);
  iphilabels->SetBinContent(110,73,3);
  //
  iphilabels->SetBinContent(95,100,10);
  iphilabels->SetBinContent(93,102,11);
  //
  iphilabels->SetBinContent(64,113,18);
  iphilabels->SetBinContent(59,113,19);
  //
  iphilabels->SetBinContent(30,102,26);
  iphilabels->SetBinContent(28,100,27);
  //
  iphilabels->SetBinContent(13,73,34);
  iphilabels->SetBinContent(10,69,35);
  //
  iphilabels->SetBinContent(10,64,36);
  iphilabels->SetBinContent(10,59,37);
  iphilabels->SetBinContent(10,54,38);
  //
  //
  iphilabels->SetBinContent(15,39,42);
  iphilabels->SetBinContent(18,35,43);
  //
  iphilabels->SetBinContent(43,15,50);
  iphilabels->SetBinContent(48,13,51);
  //
  iphilabels->SetBinContent(75,13,58);
  iphilabels->SetBinContent(80,15,59);
  //
  iphilabels->SetBinContent(105,35,66);
  iphilabels->SetBinContent(108,39,67);
  
  iphilabels->Draw("text same");
  
  TLine l;
  l.SetLineWidth(3);
  l.DrawLine(101,51,107,51);
  TArrow * iphiArrow1 = new TArrow(107,51,107,55,0.01,"|>");
  iphiArrow1->SetLineWidth(3);
  iphiArrow1->Draw();
  
  l.DrawLine(-5,51,1,51);
  TArrow * iphiArrow2 = new TArrow(-5,51,-5,47,0.01,"|>");
  iphiArrow2->SetLineWidth(3);
  iphiArrow2->Draw();
  
  TLatex iphi;
  iphi.SetTextSize(0.03);
  iphi.DrawLatex(-7,43,"i#phi");
  iphi.DrawLatex(106,57,"i#phi");
  
  

  
  return;
  
}



