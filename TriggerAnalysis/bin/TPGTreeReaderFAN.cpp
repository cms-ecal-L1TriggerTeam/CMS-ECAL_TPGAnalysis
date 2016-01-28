#include "TPGTreeReaderFAN.h"



///////  Main program /////////
int main (int argc, char** argv)
{  
   bool debug = false;
    
   //this is the output root file of the previous analyzer EcalTPGAnalyzer.cc
   string inputfiles = "ECALTPGtree.root";
   string geomName = "data/endcapGeometry.txt";
   
   string inputdir, maskfileName  ;
   string outputRootName = "histoTPG.root" ;
   int verbose = 0 ;
   int occupancyCut = 3 ;
   
   Double_t slMinEvt = 0;
   Double_t slMaxEvt = 100000000;
   Double_t slMinOrb = 0;
   Double_t slMaxOrb = 100000000;
   Double_t slMinLS = 0;
   Double_t slMaxLS = 1000;
   Double_t slMinTime = 0;
   Double_t slMaxTime = 100;
   Long64_t firstEntry = 0;
   Long64_t lastEntry = -1;
   int GoodColl = 0;
   int eg = 2;
   string l1algo, l1algobx; 
   string bcs ; 
   string orbits ; 
   string lumi ;
   string towers ; 
   string timestamps ; 
   
   string levent ;
   string ltechtrig;
   
   
   //all the options to run this codes, these options will be used in the script makeTrigPrimPlots.sh 
   for (int i=0 ; i<argc ; i++)
   {
      if (argv[i] == string("-h") ) {
         printHelp() ;
         exit(1);
      }
      if (argv[i] == string("-i") && argc>i+1) {
         inputfiles = argv[i+1] ;
      }
      if (argv[i] == string("-d") && argc>i+1) {
         inputdir = argv[i+1] ;
         inputdir = inputdir + "/" ;
      }
      if (argv[i] == string("-o") && argc>i+1) outputRootName = argv[i+1] ;
      if (argv[i] == string("-g") && argc>i+1) geomName = argv[i+1] ;
      if (argv[i] == string("-v") && argc>i+1) verbose = atoi(argv[i+1]) ;
      if (argv[i] == string("-l1") && argc>i+1) l1algo =  string(argv[i+1]) ; //algo means algorithm 
      if (argv[i] == string("-l1bx") && argc>i+1) l1algobx =  string(argv[i+1]) ;
      if (argv[i] == string("-th1") && argc>i+1) occupancyCut= atoi(argv[i+1]) ;
      if (argv[i] == string("-m") && argc>i+1) maskfileName = argv[i+1] ;
      if (argv[i] == string("-SLMinEvt") && argc>i+1)  slMinEvt = atof(argv[i+1]) ;
      if (argv[i] == string("-SLMaxEvt") && argc>i+1)  slMaxEvt = atof(argv[i+1]) ;
      if (argv[i] == string("-SLMinOrb") && argc>i+1)  slMinOrb = atof(argv[i+1]) ;
      if (argv[i] == string("-SLMaxOrb") && argc>i+1)  slMaxOrb = atof(argv[i+1]) ;
      if (argv[i] == string("-SLMinLS") && argc>i+1) slMinLS= atof(argv[i+1]) ;
      if (argv[i] == string("-SLMaxLS") && argc>i+1) slMaxLS= atof(argv[i+1]) ;
      if (argv[i] == string("-SLMinTime") && argc>i+1) slMinTime= atof(argv[i+1]) ;
      if (argv[i] == string("-SLMaxTime") && argc>i+1) slMaxTime= atof(argv[i+1]) ;
      if (argv[i] == string("-EG") && argc>i+1) eg = atoi(argv[i+1]) ;
      
      if (argv[i] == string("-bcs") && argc>i+1) bcs= string(argv[i+1]) ;
      if (argv[i] == string("-orbits") && argc>i+1) orbits= string(argv[i+1]) ;
      if (argv[i] == string("-timestamps") && argc>i+1) timestamps= string(argv[i+1]) ;
      if (argv[i] == string("-towers") && argc>i+1) towers= string(argv[i+1]) ;
      if (argv[i] == string("-levent") && argc>i+1) levent= string(argv[i+1]) ;
      if (argv[i] == string("-techtrig") && argc>i+1) ltechtrig= string(argv[i+1]) ;
      if (argv[i] == string("-goodcoll") && argc>i+1) GoodColl = atoi(argv[i+1]) ;
      if (argv[i] == string("-lumi") && argc>i+1) lumi= string(argv[i+1]) ;
      if (argv[i] == string("-firstEntry") && argc>i+1) firstEntry= atol(argv[i+1]) ;
      if (argv[i] == string("-lastEntry") && argc>i+1) lastEntry= atol(argv[i+1]) ;
   }
   
  
   //from this, read the input arguments to the code. 
   vector<int> algobits ;
   vector<string> algos = split(l1algo,",") ;
   for (uint i=0 ; i<algos.size() ; i++) algobits.push_back(atoi(algos[i].c_str())) ; //push back the input l1 to the vector algobits
   
   vector<int> algobitsbx ;
   vector<string> algosbx = split(l1algobx,",") ;
   for (uint i=0 ; i<algosbx.size() ; i++) algobitsbx.push_back(atoi(algosbx[i].c_str())) ;
   
   //   vector<int> myevents ;
   //   vector<string> vevents = split(levent,",") ;
   //   for (uint i=0 ; i<vevents.size() ; i++) myevents.push_back(atoi(vevents[i].c_str())) ;
 
 
   //ltechtrig this not too clear,it is also the arguments of makeTrigPrimPlots.sh, but read the twiki for the command to run makeTrigPrimPlots.sh, this argument seems not used 
   vector<int> mytechtriggers ;
   vector<string> vmytechtriggers = split(ltechtrig,",") ;
   for (uint i=0 ; i<vmytechtriggers.size() ; i++) mytechtriggers.push_back(atoi(vmytechtriggers[i].c_str())) ;  
  
   
   vector<string> techTrgRangeStringVector;
   vector<int> techTrgRangeIntVector;
   vector<vector<int> > techTrgIncludeVector ;
   vector<vector<int> > techTrgExcludeVector ;
   
   vector<string> techTrgStringVector = split(ltechtrig,",") ;
   
   if(debug)
   {
      for (uint i=0 ; i<techTrgStringVector.size();i++){
         cout << "techTrgStringVector["<<i<<"] = " << techTrgStringVector[i] << endl;
      }
      cout << endl;
   }
   
   for (uint i=0 ; i<techTrgStringVector.size() ; i++)
   {
      bool exclude = false;
      
      if(techTrgStringVector[i].at(0)=='x'){
         exclude = true;
         techTrgStringVector[i].erase(0,1);
      }
      techTrgRangeStringVector = split(techTrgStringVector[i],"-") ;
      
      if(debug){
         for (uint i=0 ; i<techTrgRangeStringVector.size();i++){
            cout << "techTrgRangeStringVector["<<i<<"] = " << techTrgRangeStringVector[i] << endl;
         }    
         cout << endl;
      }
      
      techTrgRangeIntVector.clear();
      for(uint j=0; j<techTrgRangeStringVector.size();j++) {
         techTrgRangeIntVector.push_back(atoi(techTrgRangeStringVector[j].c_str()));
      }
      if(exclude) techTrgExcludeVector.push_back(techTrgRangeIntVector);
      else techTrgIncludeVector.push_back(techTrgRangeIntVector);
      
   }
   
   if(debug)
   {
      cout << "techTrgIncludeVector.size(): " << techTrgIncludeVector.size() << "\n\n";
      for (uint i=0 ; i<techTrgIncludeVector.size();i++){
         cout << "techTrgIncludeVector["<<i<<"].size(): " << techTrgIncludeVector[i].size() << "\n";
         for (uint j=0 ; j<techTrgIncludeVector[i].size();j++){
            cout << "techTrgIncludeVector["<<i<<"]["<<j<<"]: " << techTrgIncludeVector[i][j] << "\t";
         }
         cout << "\n";
      }
      
      cout << "techTrgExcludeVector.size(): " << techTrgExcludeVector.size() << "\n\n";
      for (uint i=0 ; i<techTrgExcludeVector.size();i++){
         cout << "techTrgExcludeVector["<<i<<"].size(): " << techTrgExcludeVector[i].size() << "\n";
         for (uint j=0 ; j<techTrgExcludeVector[i].size();j++){
            cout << "techTrgExcludeVector["<<i<<"]["<<j<<"]: " << techTrgExcludeVector[i][j] << "\t";
         }
         cout << "\n";
      }
   }
   
   
   //also seems not used 
   vector<string> bcRangeStringVector;
   vector<int> bcRangeIntVector;
   vector<vector<int> > bcIncludeVector ;
   vector<vector<int> > bcExcludeVector ;
   
   vector<string> bcStringVector = split(bcs,",") ;
   
   if(debug){
      for (uint i=0 ; i<bcStringVector.size();i++){
         cout << "bcStringVector["<<i<<"] = " << bcStringVector[i] << endl;
      }
      cout << endl;
   }
   
   for (uint i=0 ; i<bcStringVector.size() ; i++) {
      bool exclude = false;
      
      if(bcStringVector[i].at(0)=='x'){
         exclude = true;
         bcStringVector[i].erase(0,1);
      }
      bcRangeStringVector = split(bcStringVector[i],"-") ;
      
      if(debug){
         for (uint i=0 ; i<bcRangeStringVector.size();i++){
            cout << "bcRangeStringVector["<<i<<"] = " << bcRangeStringVector[i] << endl;
         }    
         cout << endl;
      }
      
      bcRangeIntVector.clear();
      for(uint j=0; j<bcRangeStringVector.size();j++) {
         bcRangeIntVector.push_back(atoi(bcRangeStringVector[j].c_str()));
      }
      if(exclude) bcExcludeVector.push_back(bcRangeIntVector);
      else bcIncludeVector.push_back(bcRangeIntVector);
      
   }
   
   if(debug){
      cout << "bcIncludeVector.size(): " << bcIncludeVector.size() << "\n\n";
      for (uint i=0 ; i<bcIncludeVector.size();i++){
         cout << "bcIncludeVector["<<i<<"].size(): " << bcIncludeVector[i].size() << "\n";
         for (uint j=0 ; j<bcIncludeVector[i].size();j++){
            cout << "bcIncludeVector["<<i<<"]["<<j<<"]: " << bcIncludeVector[i][j] << "\t";
         }
         cout << "\n";
      }
      
      cout << "bcExcludeVector.size(): " << bcExcludeVector.size() << "\n\n";
      for (uint i=0 ; i<bcExcludeVector.size();i++){
         cout << "bcExcludeVector["<<i<<"].size(): " << bcExcludeVector[i].size() << "\n";
         for (uint j=0 ; j<bcExcludeVector[i].size();j++){
            cout << "bcExcludeVector["<<i<<"]["<<j<<"]: " << bcExcludeVector[i][j] << "\t";
         }
         cout << "\n";
      }
   }
   
   //the same as previous one, seems not used,but it is the range for lumi 
   vector<string> lumiRangeStringVector;
   vector<double> lumiRangeIntVector;
   vector<vector<double> > lumiIncludeVector ;
   vector<vector<double> > lumiExcludeVector ;
   
   if(lumi != "-1"){
      vector<string> lumiStringVector = split(lumi,",") ;
      
      for (uint i=0 ; i<lumiStringVector.size() ; i++) {
         bool exclude = false;
         
         if(lumiStringVector[i].at(0)=='x'){
            exclude = true;
            lumiStringVector[i].erase(0,1);
         }
         lumiRangeStringVector = split(lumiStringVector[i],"-") ;
         
         lumiRangeIntVector.clear();
         for(uint j=0; j<lumiRangeStringVector.size();j++) {
            lumiRangeIntVector.push_back(atof(lumiRangeStringVector[j].c_str()));
         }
         if(exclude) lumiExcludeVector.push_back(lumiRangeIntVector);
         else lumiIncludeVector.push_back(lumiRangeIntVector);
         
      }
   }
   
   
   //this is the range for event
   vector<string> eventRangeStringVector;
   vector<ULong64_t> eventRangeIntVector;
   vector<vector<ULong64_t> > eventIncludeVector ;
   vector<vector<ULong64_t> > eventExcludeVector ;
   
   if(levent != "-1"){
      vector<string> eventStringVector = split(levent,",") ;
      
      for (uint i=0 ; i<eventStringVector.size() ; i++) {
         bool exclude = false;
         
         if(eventStringVector[i].at(0)=='x'){
            exclude = true;
            eventStringVector[i].erase(0,1);
         }
         eventRangeStringVector = split(eventStringVector[i],"-") ;
         
         eventRangeIntVector.clear();
         for(uint j=0; j<eventRangeStringVector.size();j++) {
            eventRangeIntVector.push_back(atol(eventRangeStringVector[j].c_str()));
         }
         if(exclude) eventExcludeVector.push_back(eventRangeIntVector);
         else eventIncludeVector.push_back(eventRangeIntVector);
         
      }
   }
   
   if(debug)
   {
      for(uint j=0; j<eventRangeIntVector.size();j++)
         cout << "eventRangeIntVector["<<j<<"]="<<eventRangeIntVector[j]<<endl;
   }

  
   // 
   vector<string> orbitRangeStringVector;
   vector<double> orbitRangeIntVector;
   vector<vector<double> > orbitIncludeVector ;
   vector<vector<double> > orbitExcludeVector ;
   
   vector<string> orbitStringVector = split(orbits,",") ;
   
   if(debug){
      for (uint i=0 ; i<orbitStringVector.size();i++){
         cout << "orbitStringVector["<<i<<"] = " << orbitStringVector[i] << endl;
      }
      cout << endl;
   }
   
   for (uint i=0 ; i<orbitStringVector.size() ; i++) {
      bool exclude = false;
      
      if(orbitStringVector[i].at(0)=='x'){
         exclude = true;
         orbitStringVector[i].erase(0,1);
      }
      orbitRangeStringVector = split(orbitStringVector[i],"-") ;
      
      if(debug){
         for (uint i=0 ; i<orbitRangeStringVector.size();i++){
            cout << "orbitRangeStringVector["<<i<<"] = " << orbitRangeStringVector[i] << endl;
         }    
         cout << endl;
      }
      
      orbitRangeIntVector.clear();
      for(uint j=0; j<orbitRangeStringVector.size();j++) {
         orbitRangeIntVector.push_back(atof(orbitRangeStringVector[j].c_str()));
      }
      if(exclude) orbitExcludeVector.push_back(orbitRangeIntVector);
      else orbitIncludeVector.push_back(orbitRangeIntVector);
      
   }
   
   if(debug){
      cout << "orbitIncludeVector.size(): " << orbitIncludeVector.size() << "\n\n";
      for (uint i=0 ; i<orbitIncludeVector.size();i++){
         cout << "orbitIncludeVector["<<i<<"].size(): " << orbitIncludeVector[i].size() << "\n";
         for (uint j=0 ; j<orbitIncludeVector[i].size();j++){
            cout << "orbitIncludeVector["<<i<<"]["<<j<<"]: " << orbitIncludeVector[i][j] << "\t";
         }
         cout << "\n";
      }
      
      cout << "orbitExcludeVector.size(): " << orbitExcludeVector.size() << "\n\n";
      for (uint i=0 ; i<orbitExcludeVector.size();i++){
         cout << "orbitExcludeVector["<<i<<"].size(): " << orbitExcludeVector[i].size() << "\n";
         for (uint j=0 ; j<orbitExcludeVector[i].size();j++){
            cout << "orbitExcludeVector["<<i<<"]["<<j<<"]: " << orbitExcludeVector[i][j] << "\t";
         }
         cout << "\n";
      }
   }
   
  
   //the range for time stamp;also seems not used 
   vector<string> timestampRangeStringVector;
   vector<double> timestampRangeIntVector;
   vector<vector<double> > timestampIncludeVector ;
   vector<vector<double> > timestampExcludeVector ;
   
   vector<string> timestampStringVector = split(timestamps,",") ;
   
   if(debug){
      for (uint i=0 ; i<timestampStringVector.size();i++){
         cout << "timestampStringVector["<<i<<"] = " << timestampStringVector[i] << endl;
      }
      cout << endl;
   }
   
   for (uint i=0 ; i<timestampStringVector.size() ; i++) {
      bool exclude = false;
      
      if(timestampStringVector[i].at(0)=='x'){
         exclude = true;
         timestampStringVector[i].erase(0,1);
      }
      timestampRangeStringVector = split(timestampStringVector[i],"-") ;
      
      if(debug){
         for (uint i=0 ; i<timestampRangeStringVector.size();i++){
            cout << "timestampRangeStringVector["<<i<<"] = " << timestampRangeStringVector[i] << endl;
         }    
         cout << endl;
      }
      
      timestampRangeIntVector.clear();
      for(uint j=0; j<timestampRangeStringVector.size();j++) {
         timestampRangeIntVector.push_back(atof(timestampRangeStringVector[j].c_str()));
      }
      if(exclude) timestampExcludeVector.push_back(timestampRangeIntVector);
      else timestampIncludeVector.push_back(timestampRangeIntVector);
      
   }
   
   if(debug){
      cout << "timestampIncludeVector.size(): " << timestampIncludeVector.size() << "\n\n";
      for (uint i=0 ; i<timestampIncludeVector.size();i++){
         cout << "timestampIncludeVector["<<i<<"].size(): " << timestampIncludeVector[i].size() << "\n";
         for (uint j=0 ; j<timestampIncludeVector[i].size();j++){
            cout << "timestampIncludeVector["<<i<<"]["<<j<<"]: " << timestampIncludeVector[i][j] << "\t";
         }
         cout << "\n";
      }
      
      cout << "timestampExcludeVector.size(): " << timestampExcludeVector.size() << "\n\n";
      for (uint i=0 ; i<timestampExcludeVector.size();i++){
         cout << "timestampExcludeVector["<<i<<"].size(): " << timestampExcludeVector[i].size() << "\n";
         for (uint j=0 ; j<timestampExcludeVector[i].size();j++){
            cout << "timestampExcludeVector["<<i<<"]["<<j<<"]: " << timestampExcludeVector[i][j] << "\t";
         }
         cout << "\n";
      }
   }
      
  
   //the range for tower, also an argument in makeTrigPrimPlots.sh 
   vector<string> towerRangeStringVector;
   vector<int> towerIncludeVector ;
   vector<int> towerExcludeVector ;
   
   vector<string> towerStringVector = split(towers,",") ;
   
   if(debug){
      for (uint i=0 ; i<towerStringVector.size();i++){
         cout << "towerStringVector["<<i<<"] = " << towerStringVector[i] << endl;
      }
      cout << endl;
   }
   for (uint i=0 ; i<towerStringVector.size() ; i++) {
      
      if(towerStringVector[i].at(0)=='x'){
         towerStringVector[i].erase(0,1);
         towerExcludeVector.push_back(atoi(towerStringVector[i].c_str()));
      }
      else towerIncludeVector.push_back(atoi(towerStringVector[i].c_str()));
   }
   
   if(debug){
      cout << "towerIncludeVector.size(): " << towerIncludeVector.size() << "\n\n";
      for (uint i=0 ; i<towerIncludeVector.size();i++){
         cout << "towerIncludeVector["<<i<<"]= " << towerIncludeVector[i] << "\n";
         
         cout << "\n";
      }
      cout << "towerExcludeVector.size(): " << towerExcludeVector.size() << "\n\n";
      for (uint i=0 ; i<towerExcludeVector.size();i++){
         cout << "towerExcludeVector["<<i<<"]= " << towerExcludeVector[i] << "\n";
         
         cout << "\n";
      }
   }
   //in my opinion, all these not used arguments may be only used when you want to look more detail for specific lumi ranges,event ranges or tower ranges...
   
   
   uint ref = 2 ;  //emulator array index corresponding to 3rd sample of 5.
   //this should match the real TP data (theoretically)
   
   
   ///////////////////////
   // parse geometry file
   ///////////////////////

   //now read in the input geometry file
   ifstream fin ;
   string line;
   int hashedIndex, ix, iy;
   map < int , vector< pair<int, int> > > geometry;
   
   fin.open(geomName.c_str());
   
   if (fin.is_open())
   {
      while(!fin.eof()) {
         //each line will be 3 parts, so hashedIndex part1, ix part2, iy part3
         fin >> hashedIndex >> ix >> iy;
         if(fin.eof()){
            break ; // avoid last line duplication
         }
         //put them into this map
         geometry[hashedIndex].push_back( pair<int,int>(ix,iy) ); 
      }
   }
   
   
   ///////////////////////
   // book the histograms
   ///////////////////////
   //TH1F * bx_all = new TH1F("bx_all","bx_all",3570, 0, 3570) ;

   //histo for bunch crossing information
   TH1F * bx_bit45_all = new TH1F("bx_bit45_all","bx_bit45_all",3570, 0, 3570) ;
   TH1F * bx_bit46_all = new TH1F("bx_bit46_all","bx_bit46_all",3570, 0, 3570) ;
   TH1F * bx_nTT = new TH1F("bx_nTT","bx_nTT",21, -0.5, 20.5) ;
   
   
   //TH1F * bx_all_ecal = new TH1F("bx_all_ecal","bx_all_ecal",3570, 0, 3570) ;
   //TH1F * bx_all_eb = new TH1F("bx_all_eb","bx_all_eb",3570, 0, 3570) ;
   //TH1F * bx_all_ee_m = new TH1F("bx_all_ee_m","bx_all_ee_m",3570, 0, 3570) ;
   //TH1F * bx_all_ee_p = new TH1F("bx_all_ee_p","bx_all_ee_p",3570, 0, 3570) ;
   //histo for l1 algorithm
   TH1F *  l1EGAlgos = new TH1F("L1EGAlgos","L1EGAlgos", 30, 39.5 , 69.5);
   TH2F *  l1EGAlgos2D = new TH2F("L1EGAlgos2D","L1EGAlgos2D", 30, 39.5 , 69.5, 30, 39.5 , 69.5);
   
   TH1F * techTrigCor   = new TH1F("techTrigCor","techTrigCor", 10, 39.5 , 49.5);
   TH2F * techTrigCor2D = new TH2F("techTrigCor2D","techTrigCor2D", 10, 39.5 , 49.5, 10, 39.5 , 49.5);
   
   TH2F * histoEgTrigTechTrigCor = new TH2F("histoEgTrigTechTrigCor","histoEgTrigTechTrigCor",30, 39.5 , 69.5, 10, 39.5 , 49.5); 
   
   //BARREL
   //barrel TP occupancy
   TH2F * occupancyTPEB = new TH2F("occupancyTPEB", "TP Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
   occupancyTPEB->GetYaxis()->SetTitle("eta index") ;
   occupancyTPEB->GetXaxis()->SetTitle("phi index") ;
   //barrel emulated TP occupancy
   TH2F * occupancyTPEmulEB = new TH2F("occupancyTPEmulEB", "Emulated TP Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
   occupancyTPEmulEB->GetYaxis()->SetTitle("eta index") ;
   occupancyTPEmulEB->GetXaxis()->SetTitle("phi index") ;
   //barrel TP eta
   TH1F * TPEtaEB = new TH1F("TPEtaEB", "TP: Barrel eta", 35, -17, 18) ;
   TPEtaEB->GetXaxis()->SetTitle("eta index") ;
   //barrel TP phi
   TH1F * TPPhiEB = new TH1F("TPPhiEB", "TP: Barrel phi", 72, 1, 73) ;
   TPPhiEB->GetXaxis()->SetTitle("phi index") ;
   
   
   //ENDCAPS
   //endcap TP occupancy
   TH2F * occupancyTPEEPlus = new TH2F("occupancyTPEEPlus", "TP Occupancy: E>0: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyTPEEPlus->GetYaxis()->SetTitle("y index") ;
   occupancyTPEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyTPEEMinus = new TH2F("occupancyTPEEMinus", "TP Occupancy: E>0: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyTPEEMinus->GetYaxis()->SetTitle("y index") ;
   occupancyTPEEMinus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyTPEEPlusAll = new TH2F("occupancyTPEEPlusAll", "TP Occupancy: All TPs: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyTPEEPlusAll->GetYaxis()->SetTitle("y index") ;
   occupancyTPEEPlusAll->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyTPEEMinusAll = new TH2F("occupancyTPEEMinusAll", "TP Occupancy: All TPs: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyTPEEMinusAll->GetYaxis()->SetTitle("y index") ;
   occupancyTPEEMinusAll->GetXaxis()->SetTitle("x index") ;
   
   //endcap emulated TP occupancy
   TH2F * occupancyTPEmulEEPlus = new TH2F("occupancyTPEmulEEPlus", "Emulated TP Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyTPEmulEEPlus->GetYaxis()->SetTitle("y index") ;
   occupancyTPEmulEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyTPEmulEEMinus = new TH2F("occupancyTPEmulEEMinus", "Emulated TP Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyTPEmulEEMinus->GetYaxis()->SetTitle("y index") ;
   occupancyTPEmulEEMinus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyTPEmulEEPlusALL = new TH2F("occupancyTPEmulEEPlusALL", "Occupancy of Emulated TPs: ANY emu sample > 0: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyTPEmulEEPlusALL->GetYaxis()->SetTitle("y index") ;
   occupancyTPEmulEEPlusALL->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyTPEmulEEMinusALL = new TH2F("occupancyTPEmulEEMinusALL", "Occupancy of Emulated TPs: ANY emu sample > 0: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyTPEmulEEMinusALL->GetYaxis()->SetTitle("y index") ;
   occupancyTPEmulEEMinusALL->GetXaxis()->SetTitle("x index") ;
   
   //endcap TP eta
   TH1F * TPEtaEEPlus = new TH1F("TPEtaEEPlus", "TP: Plus Endcap eta", 11, 18, 29) ;
   TPEtaEEPlus->GetXaxis()->SetTitle("eta index") ;
   TH1F * TPEtaEEMinus = new TH1F("TPEtaEEMinus", "TP: Minus Endcap eta", 11, -28, -17) ;
   TPEtaEEMinus->GetXaxis()->SetTitle("eta index") ;
   
   //endcap TP phi
   TH1F * TPPhiEEPlus = new TH1F("TPPhiEEPlus", "TP: Plus Endcap phi", 72, 1, 73) ;
   TPPhiEEPlus->GetXaxis()->SetTitle("phi index") ;
   TH1F * TPPhiEEMinus = new TH1F("TPPhiEEMinus", "TP: Minus Endcap phi", 72, 1, 73) ;
   TPPhiEEMinus->GetXaxis()->SetTitle("phi index") ;
   
   
   
   // ============================= Fill histos related to time evolution
   int timeBin = int(slMaxTime-slMinTime);
   //slMaxTime and slMinTime are the two arguments, this will compute in script makeTrigPrimPlots.sh, search for FixLimits.C, you will find the script itself will create FixLimits.C, then run it to get the slMaxTime and slMinTime. FixLimits.C will read timeStamp, orbitNb, evtNb, the branch in EcalTPGAnalyzer.cc 
   
   //cout << "time bin: " << timeBin << endl;
   TH1F * occupancyTP_vs_EvtNb = new TH1F("occupancyTP_vs_EvtNb", "TP occupancy vs. EvtNb", 1000, slMinEvt, slMaxEvt) ;
   occupancyTP_vs_EvtNb->GetXaxis()->SetTitle("EvtNb / 10^6") ;
   //occupancyTP_vs_EvtNb->SetXTitle("EvtNb / 10^6");
   occupancyTP_vs_EvtNb->GetYaxis()->SetTitle("# of TPs") ;
   //occupancyTP_vs_EvtNb->SetYTitle("# of TPs") ;
   
   //2D histo, ieta and iphi vs time 
   TH2F * iEta_vs_Time = new TH2F("iEta_vs_Time", "iEta vs. Time",timeBin, 0, slMaxTime-slMinTime, 57, -28, 29) ;
   iEta_vs_Time->GetYaxis()->SetTitle("iEta") ;
   iEta_vs_Time->GetXaxis()->SetTitle("Time (min)") ;
   TH2F * iPhi_vs_Time = new TH2F("iPhi_vs_Time", "iPhi vs. Time",timeBin, 0, slMaxTime-slMinTime, 72, 1, 73) ;
   iPhi_vs_Time->GetYaxis()->SetTitle("iPhi") ;
   iPhi_vs_Time->GetXaxis()->SetTitle("Time (min)") ;
  
   //3D time, Trigger tower vs time 
   TH3F * time3D = new TH3F("time3D", "TT vs time", 72, 1, 73, 57, -28, 29, timeBin, 0, slMaxTime-slMinTime) ;
   time3D->GetYaxis()->SetTitle("eta index") ;
   time3D->GetXaxis()->SetTitle("phi index") ;
   
  
   //seems not used 
   int LSBin = int(slMaxLS-slMinLS);
   
   TH2F * iEta_vs_LS = new TH2F("iEta_vs_LS", "iEta vs. LS",LSBin, slMinLS, slMaxLS, 57, -28, 29) ;
   iEta_vs_LS->GetYaxis()->SetTitle("iEta") ;
   iEta_vs_LS->GetXaxis()->SetTitle("Lumi Section") ;
   TH2F * iPhi_vs_LS = new TH2F("iPhi_vs_LS", "iPhi vs. LS",LSBin, slMinLS, slMaxLS, 72, 1, 73) ;
   iPhi_vs_LS->GetYaxis()->SetTitle("iPhi") ;
   iPhi_vs_LS->GetXaxis()->SetTitle("Lumi Section") ;
   
   TH3F * LS3D = new TH3F("LS3D", "TT vs lumi section", 72, 1, 73, 57, -28, 29, LSBin, slMinLS, slMaxLS) ;
   LS3D->GetYaxis()->SetTitle("eta index") ;
   LS3D->GetXaxis()->SetTitle("phi index") ;
   
  
    
   TH1F * orbit = new TH1F("orbit", "orbit number", 1000, slMinOrb, slMaxOrb) ;
   orbit->GetXaxis()->SetTitle("Orbit Number / 10^6") ;
   TH1F * eventNb = new TH1F("eventNb", "event number", 100,slMinEvt, slMaxEvt) ;
   eventNb->GetXaxis()->SetTitle("Event Number / 10^6") ;
   eventNb->GetYaxis()->SetTitle("# of Events ") ;
   //for time stamp
   TH1F * TimeStamp = new TH1F("TimeStamp", "time stamp", timeBin, 0, timeBin) ;
   TimeStamp->GetXaxis()->SetTitle("Time Stamp (min) ") ;
   
   //for lumi
   TH1F * LumiSection = new TH1F("LumiSection", "lumi section", LSBin, slMinLS, slMaxLS) ;
   LumiSection->GetXaxis()->SetTitle("Luminosity Section ") ;
   
   TH1F * triggerBit = new TH1F("triggerBit", "Active Triggers Fired", 256, 0., 128.) ;
   triggerBit->GetXaxis()->SetTitle("Trigger Bit") ;
   
   TH1F * FiredTriggers = new TH1F("FiredTriggers", "Triggers Fired (before masking)", 256, 0., 128.) ;
   FiredTriggers->GetXaxis()->SetTitle("Trigger Bit") ;
  
   //trigger primitive in EB 
   TH1F * TPEB = new TH1F("TPEB", "TP: Barrel", 256, 0., 256.) ;
   TPEB->GetXaxis()->SetTitle("TP (ADC)") ;
   //trigger primitive in EE+
   TH1F * TPEEPlus = new TH1F("TPEEPlus", "TP: EE Plus", 256, 0., 256.) ;
   TPEEPlus->GetXaxis()->SetTitle("TP (ADC)") ;
   //trigger primitive in EE-
   TH1F * TPEEMinus = new TH1F("TPEEMinus", "TP: EE Minus", 256, 0., 256.) ;
   TPEEMinus->GetXaxis()->SetTitle("TP (ADC)") ;
  
   //emulated trigger primitive in EB 
   TH1F * TPEmulEB = new TH1F("TPEmulEB", "Emulated TPs: Barrel", 256, 0., 256.) ;
   TPEmulEB->GetXaxis()->SetTitle("TP (ADC)") ;
   //emulated trigger primitive in EE+
   TH1F * TPEmulEEPlus = new TH1F("TPEmulEEPlus", "Emulated TPs: EE Plus", 256, 0., 256.) ;
   TPEmulEEPlus->GetXaxis()->SetTitle("TP (ADC)") ;
   //emulated trigger primitive in EE-
   TH1F * TPEmulEEMinus = new TH1F("TPEmulEEMinus", "Emulated TPs: EE Minus", 256, 0., 256.) ;
   TPEmulEEMinus->GetXaxis()->SetTitle("TP (ADC)") ;
  
   //the maximum emulated trigger primitive in EB 
   TH1F * TPEmulMaxEB = new TH1F("TPEmulMaxEB", "TP Emulator max: Barrel", 256, 0., 256.) ;
   TPEmulMaxEB->GetXaxis()->SetTitle("TP (ADC)") ;
   //the maximum emulated trigger primitive in EE+
   TH1F * TPEmulMaxEEPlus = new TH1F("TPEmulMaxEEPlus", "TP Emulator max: Plus Endcap", 256, 0., 256.) ;
   TPEmulMaxEEPlus->GetXaxis()->SetTitle("TP (ADC)") ;
   //the maximum emulated trigger primitive in EE-
   TH1F * TPEmulMaxEEMinus = new TH1F("TPEmulMaxEEMinus", "TP Emulator max: Minus Endcap", 256, 0., 256.) ;
   TPEmulMaxEEMinus->GetXaxis()->SetTitle("TP (ADC)") ;
  
   //max TP from Emulator in EE+ 
   TH2F * TPEmulMapMaxIndexEEPlus = new TH2F("TPEmulMapMaxIndexEEPlus", "Map Index of the max TP from Emulator: Plus Endcap",  121, -10, 111, 121, -10, 111);
   TPEmulMapMaxIndexEEPlus->GetYaxis()->SetTitle("y index") ;
   TPEmulMapMaxIndexEEPlus->GetXaxis()->SetTitle("x index") ;
   //max TP from Emulator in EE-
   TH2F * TPEmulMapMaxIndexEEMinus = new TH2F("TPEmulMapMaxIndexEEMinus", "Map Index of the max TP from Emulator: Minus Endcap",  121, -10, 111, 121, -10, 111)  ;
   TPEmulMapMaxIndexEEMinus->GetYaxis()->SetTitle("y index") ;
   TPEmulMapMaxIndexEEMinus->GetXaxis()->SetTitle("x index") ;
   //max TP from Emulator in EB
   TH2F * TPEmulMapMaxIndexEB = new TH2F("TPEmulMapMaxIndexEB", "Map Index of the max TP from Emulator: Barrel",   72, 1, 73, 38, -19, 19) ;
   TPEmulMapMaxIndexEB->GetYaxis()->SetTitle("eta index") ;
   TPEmulMapMaxIndexEB->GetXaxis()->SetTitle("phi index") ;
   
   //trigger spectrum in EB, 3D histo
   TH3F * TPspectrumMap3DEB = new TH3F("TPspectrumMap3DEB", "TP  spectrum map: Barrel", 72, 1, 73, 38, -19, 19, 256, 0., 256.) ;
   TPspectrumMap3DEB->GetYaxis()->SetTitle("eta index") ;
   TPspectrumMap3DEB->GetXaxis()->SetTitle("phi index") ;
   
   //trigger spectrum in EE+, 3D histo
   TH3F * TPspectrumMap3DEEPlus = new TH3F("TPspectrumMap3DEEPlus", "TP  spectrum map: Plus Endcap", 121, -10, 111, 121, -10, 111, 256, -0.5, 255.5) ;
   TPspectrumMap3DEEPlus->GetYaxis()->SetTitle("y index") ;
   TPspectrumMap3DEEPlus->GetXaxis()->SetTitle("x index") ;
   //trigger spectrum in EE-, 3D histo
   TH3F * TPspectrumMap3DEEMinus = new TH3F("TPspectrumMap3DEEMinus", "TP  spectrum map: Minus Endcap", 121, -10, 111, 121, -10, 111, 256, 0., 256.) ;
   TPspectrumMap3DEEMinus->GetYaxis()->SetTitle("y index") ;
   TPspectrumMap3DEEMinus->GetXaxis()->SetTitle("x index") ;
   
   //FANModi 
   TH1F * TPMatchEmulEB = new TH1F("TPMatchEmulEB", "TP data matching Emulator: Barrel", 7, -1., 6) ;
   TPMatchEmulEB->GetXaxis()->SetTitle("Emulator Index") ;
   TH1F * TPMatchEmulEEPlus = new TH1F("TPMatchEmulEEPlus", "TP data matching Emulator: Plus Endcap", 7, -1., 6) ;
   TPMatchEmulEEPlus->GetXaxis()->SetTitle("Emulator Index") ;
   TH1F * TPMatchEmulEEMinus = new TH1F("TPMatchEmulEEMinus", "TP data matching Emulator: Minus Endcap", 7, -1., 6) ;
   TPMatchEmulEEMinus->GetXaxis()->SetTitle("Emulator Index") ;
   TH1F * TPEmulMaxIndexEB = new TH1F("TPEmulMaxIndexEB", "Index of the max TP from Emulator: Barrel", 7, -1., 6) ;
   TPEmulMaxIndexEB->GetXaxis()->SetTitle("Emulator Index") ;
   TH1F * TPEmulMaxIndexEEPlus = new TH1F("TPEmulMaxIndexEEPlus", "Index of the max TP from Emulator: Plus Endcap", 7, -1., 6) ;
   TPEmulMaxIndexEEPlus->GetXaxis()->SetTitle("Emulator Index") ;
   TH1F * TPEmulMaxIndexEEMinus = new TH1F("TPEmulMaxIndexEEMinus", "Index of the max TP from Emulator: Minus Endcap", 7, -1., 6) ;
   TPEmulMaxIndexEEMinus->GetXaxis()->SetTitle("Emulator Index") ;
   TH3I * TPMatchEmul3D = new TH3I("TPMatchEmul3D", "TP data matching Emulator", 72, 1, 73, 57, -28, 29, 7, -1, 6) ;
   TPMatchEmul3D->GetYaxis()->SetTitle("eta index") ;
   TPMatchEmul3D->GetXaxis()->SetTitle("phi index") ;
   TH3I * TPEmulMax3D = new TH3I("TPEmulMax3D", "Index of max TP Emulator 3D", 72, 1, 73, 57, -28, 29, 7, -1, 6) ;
   TPEmulMax3D->GetYaxis()->SetTitle("eta index") ;
   TPEmulMax3D->GetXaxis()->SetTitle("phi index") ;
   
   TH2F * TPCompEmulEB = new TH2F("TPCompEmulEB", "Number of TP-Emulator comparisons: Barrel", 72, 1, 73, 38, -19, 19) ;
   TPCompEmulEB->GetYaxis()->SetTitle("eta index") ; 
   TPCompEmulEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * TPCompEmulEEPlus = new TH2F("TPCompEmulEEPlus", "Number of TP-Emulator comparisons: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPCompEmulEEPlus->GetYaxis()->SetTitle("y index") ; 
   TPCompEmulEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * TPCompEmulEEMinus = new TH2F("TPCompEmulEEMinus", "Number of TP-Emulator comparisons: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPCompEmulEEMinus->GetYaxis()->SetTitle("y index") ; 
   TPCompEmulEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
   
   TH2F * TPTimingEBFromEmulOK = new TH2F("TPTimingEBFromEmulOK", "Good TP Timing: Barrel", 72, 1, 73, 38, -19, 19) ;
   TPTimingEBFromEmulOK->GetYaxis()->SetTitle("eta index") ;
   TPTimingEBFromEmulOK->GetXaxis()->SetTitle("phi index") ;
   TH2F * TPTimingEBFromEmulOKAndMatch = new TH2F("TPTimingEBFromEmulOKAndMatch", "Good TP Timing and match: Barrel", 72, 1, 73, 38, -19, 19) ;
   TPTimingEBFromEmulOKAndMatch->GetYaxis()->SetTitle("eta index") ;
   TPTimingEBFromEmulOKAndMatch->GetXaxis()->SetTitle("phi index") ;
   TH2F * TPTimingEBFromEmulWrong = new TH2F("TPTimingEBFromEmulWrong", "Wrong TP Timing: Barrel", 72, 1, 73, 38, -19, 19) ;
   TPTimingEBFromEmulWrong->GetYaxis()->SetTitle("eta index") ;
   TPTimingEBFromEmulWrong->GetXaxis()->SetTitle("phi index") ;
   
   TH2F * TPTimingEEMinusFromEmulOK = new TH2F("TPTimingEEMinusFromEmulOK", "Good TP Timing: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPTimingEEMinusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
   TPTimingEEMinusFromEmulOK->GetXaxis()->SetTitle("x index") ;
   TH2F * TPTimingEEMinusFromEmulOKAndMatch= new TH2F("TPTimingEEMinusFromEmulOKAndMatch", "Good TP Timing and match: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPTimingEEMinusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
   TPTimingEEMinusFromEmulOK->GetXaxis()->SetTitle("x index") ;
   TH2F * TPTimingEEMinusFromEmulWrong = new TH2F("TPTimingEEMinusFromEmulWrong", "Wrong TP Timing: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPTimingEEMinusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
   TPTimingEEMinusFromEmulOK->GetXaxis()->SetTitle("x index") ;
   
   TH2F * TPTimingEEPlusFromEmulOK = new TH2F("TPTimingEEPlusFromEmulOK", "Good TP Timing: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPTimingEEPlusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
   TPTimingEEPlusFromEmulOK->GetXaxis()->SetTitle("x index") ;
   TH2F * TPTimingEEPlusFromEmulOKAndMatch= new TH2F("TPTimingEEPlusFromEmulOKAndMatch", "Good TP Timing and match: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPTimingEEPlusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
   TPTimingEEPlusFromEmulOK->GetXaxis()->SetTitle("x index") ;
   TH2F * TPTimingEEPlusFromEmulWrong = new TH2F("TPTimingEEPlusFromEmulWrong", "Wrong TP Timing: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPTimingEEPlusFromEmulOK->GetYaxis()->SetTitle("y index") ; 
   TPTimingEEPlusFromEmulOK->GetXaxis()->SetTitle("x index") ;
   
   
   TH2I * ttfMismatchEB = new TH2I("ttfMismatchEB", "TTF mismatch map",  72, 1, 73, 38, -19, 19) ;
   ttfMismatchEB->GetYaxis()->SetTitle("eta index") ;
   ttfMismatchEB->GetXaxis()->SetTitle("phi index") ;
   TH2I * ttfMismatchEEPlus = new TH2I("ttfMismatchEEPlus", "TTF mismatch map: Plus Endcap",  121, -10, 111, 121, -10, 111) ;
   ttfMismatchEEPlus->GetYaxis()->SetTitle("y index") ;
   ttfMismatchEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2I * ttfMismatchEEMinus = new TH2I("ttfMismatchEEMinus", "TTF mismatch map: Minus Endcap",  121, -10, 111, 121, -10, 111) ;
   ttfMismatchEEMinus->GetYaxis()->SetTitle("y index") ;
   ttfMismatchEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
   stringstream title1 ;
   if (l1algo.size()==0) title1 <<"TPEmul_vs_bx"<<" tp>"<<occupancyCut;
   else title1 <<"TPEmul_vs_bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo;
   TH2F * bx_Vs_TPEmul = new TH2F("TPEmul_vs_bx", title1.str().c_str(),3570, 0, 3570, 256, 0, 256) ;
   bx_Vs_TPEmul->GetYaxis()->SetTitle("TP Emul") ;
   bx_Vs_TPEmul->GetXaxis()->SetTitle("Bunch crossing") ;
   
   stringstream title2 ;
   if (l1algo.size()==0) title2 <<"TP_vs_bx"<<" tp>"<<occupancyCut;
   else title2 <<"TP_vs_bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo;
   TH2F * bx_Vs_TP = new TH2F("TP_vs_bx", title2.str().c_str(),3570, 0, 3570, 256, 0, 256) ;
   bx_Vs_TP->GetYaxis()->SetTitle("TP") ;
   bx_Vs_TP->GetXaxis()->SetTitle("Bunch crossing") ;
   
   stringstream title3 ;
   if (l1algo.size()==0) title3 <<"Orbit_vs_bx"<<" tp>"<<occupancyCut;
   else title3 <<"Orbit_vs_bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo;
   TH2F * bx_Vs_Orbit = new TH2F("Orbit_vs_bx", title3.str().c_str(),3570, 0, 3570, 1000, slMinOrb,slMaxOrb) ;
   bx_Vs_Orbit->GetYaxis()->SetTitle("Orbit / 10^6") ;
   bx_Vs_Orbit->GetXaxis()->SetTitle("Bunch crossing") ;
   
   stringstream title4 ;
   if (l1algo.size()==0) title4 <<"TriggerBit_vs_bx"<<" tp>"<<occupancyCut;
   else title4 <<"TriggerBit_vs_bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo;
   TH2F * bx_Vs_TriggerBit = new TH2F("TriggerBit_vs_bx", title4.str().c_str(),3570, 0, 3570, 256, 0, 64) ;
   bx_Vs_TriggerBit->GetYaxis()->SetTitle("Trigger Bit") ;
   bx_Vs_TriggerBit->GetXaxis()->SetTitle("Bunch crossing") ;
   
   stringstream title5 ;
   if (l1algo.size()==0) title5 <<"bx"<<" tp>"<<occupancyCut<<" l1bx"<<l1algobx;
   else title5 <<"bx"<<" tp>"<<occupancyCut<<" l1="<<l1algo<<" l1bx"<<l1algobx;
   TH1F * bx = new TH1F("bx", title5.str().c_str(), 3570, 0, 3570) ;
   bx->GetXaxis()->SetTitle("Bunch crossing ") ;
   
   stringstream title6 ;
   if (l1algo.size()==0) title6 <<"time"<<" tp>"<<occupancyCut<<" l1"<<l1algo;
   else title6 <<"time"<<" tp>"<<occupancyCut<<" l1="<<l1algo<<" l1"<<l1algo;
   TH1F * time = new TH1F("time", title6.str().c_str(), 3570, 0, 3570) ;
   time->GetXaxis()->SetTitle("Bunch crossing ") ;
   
   
   /////////////////////////
   //L1 candidate histograms
   /////////////////////////
   
   TH1F * nbOfL1IsoCands = new TH1F("nbOfL1IsoCands", "nbOfL1IsoCands", 5, 0., 5.) ;
   TH1F * nbOfL1NonisoCands = new TH1F("nbOfL1NonisoCands", "nbOfL1NonisoCands", 5, 0., 5.) ; 
   TH1F * L1IsoCandRank = new TH1F("L1IsoCandRank", "L1IsoCandRank", 64, 0., 64) ;
   TH1F * L1NonisoCandRank = new TH1F("L1NonisoCandRank", "L1NonisoCandRank", 64, 0., 64) ; 
   
   TH1F * nbOfL1preIsoCands = new TH1F("nbOfL1preIsoCands", "nbOfL1preIsoCands", 5, 0., 5.) ;
   TH1F * nbOfL1preNonisoCands = new TH1F("nbOfL1preNonisoCands", "nbOfL1preNonisoCands", 5, 0., 5.) ; 
   TH1F * L1preIsoCandRank = new TH1F("L1preIsoCandRank", "L1preIsoCandRank", 64, 0., 64) ;
   TH1F * L1preNonisoCandRank = new TH1F("L1preNonisoCandRank", "L1preNonisoCandRank", 64, 0., 64) ; 
   
   TH1F * nbOfL1postIsoCands = new TH1F("nbOfL1postIsoCands", "nbOfL1postIsoCands", 5, 0., 5.) ;
   TH1F * nbOfL1postNonisoCands = new TH1F("nbOfL1postNonisoCands", "nbOfL1postNonisoCands", 5, 0., 5.) ; 
   TH1F * L1postIsoCandRank = new TH1F("L1postIsoCandRank", "L1postIsoCandRank", 64, 0., 64) ;
   TH1F * L1postNonisoCandRank = new TH1F("L1postNonisoCandRank", "L1postNonisoCandRank", 64, 0., 64) ; 
   
   TH1F * L1Isotiming = new TH1F("L1Isotiming", "L1Isotiming", 5, -2., 3.) ;
   TH1F * L1Nonisotiming = new TH1F("L1Nonisotiming", "L1Nonisotiming", 5, -2., 3.) ;
   
   TH1F * L1IsotimingEB = new TH1F("L1IsotimingEB", "L1IsotimingEB", 5, -2., 3.) ;
   TH1F * L1NonisotimingEB = new TH1F("L1NonisotimingEB", "L1NonisotimingEB", 5, -2., 3.) ;
   
   TH1F * L1IsotimingEEPlus = new TH1F("L1IsotimingEEPlus", "L1IsotimingEEPlus", 5, -2., 3.) ;
   TH1F * L1NonisotimingEEPlus = new TH1F("L1NonisotimingEEPlus", "L1NonisotimingEEPlus", 5, -2., 3.) ;
   
   TH1F * L1IsotimingEEMinus = new TH1F("L1IsotimingEEMinus", "L1IsotimingEEMinus", 5, -2., 3.) ;
   TH1F * L1NonisotimingEEMinus = new TH1F("L1NonisotimingEEMinus", "L1NonisotimingEEMinus", 5, -2., 3.) ;
   
   //all ecal l1 occupancy
   TH2F * occupancyL1Iso = new TH2F("occupancyL1Iso", "Iso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
   occupancyL1Iso->GetXaxis()->SetTitle("RCT eta index") ;
   occupancyL1Iso->GetYaxis()->SetTitle("RCT phi index") ;
   TH2F * occupancyL1Noniso = new TH2F("occupancyL1Noniso", "Noniso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
   occupancyL1Noniso->GetXaxis()->SetTitle("RCT eta index") ;
   occupancyL1Noniso->GetYaxis()->SetTitle("RCT phi index") ;
   TH2F * occupancyL1preIso = new TH2F("occupancyL1preIso", "Pre-firing Iso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
   occupancyL1preIso->GetXaxis()->SetTitle("RCT eta index") ;
   occupancyL1preIso->GetYaxis()->SetTitle("RCT phi index") ;
   TH2F * occupancyL1preNoniso = new TH2F("occupancyL1preNoniso", "Pre-firing Noniso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
   occupancyL1preNoniso->GetXaxis()->SetTitle("RCT eta index") ;
   occupancyL1preNoniso->GetYaxis()->SetTitle("RCT phi index") ;
   TH2F * occupancyL1postIso = new TH2F("occupancyL1postIso", "Post-firing Iso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
   occupancyL1postIso->GetXaxis()->SetTitle("RCT eta index") ;
   occupancyL1postIso->GetYaxis()->SetTitle("RCT phi index") ;
   TH2F * occupancyL1postNoniso = new TH2F("occupancyL1postNoniso", "Post-firing Noniso L1 Occupancy", 14, 4, 18, 18, 0, 18) ;
   occupancyL1postNoniso->GetXaxis()->SetTitle("RCT eta index") ;
   occupancyL1postNoniso->GetYaxis()->SetTitle("RCT phi index") ;
   
   //barrel l1 occupancy
   TH2F * occupancyL1IsoEB = new TH2F("occupancyL1IsoEB", "L1Iso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
   occupancyL1IsoEB->GetYaxis()->SetTitle("eta index") ;
   occupancyL1IsoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * occupancyL1NonisoEB = new TH2F("occupancyL1NonisoEB", "L1Noniso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
   occupancyL1NonisoEB->GetYaxis()->SetTitle("eta index") ;
   occupancyL1NonisoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * occupancyL1preIsoEB = new TH2F("occupancyL1preIsoEB", "Pre-firing L1Iso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
   occupancyL1preIsoEB->GetYaxis()->SetTitle("eta index") ;
   occupancyL1preIsoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * occupancyL1preNonisoEB = new TH2F("occupancyL1preNonisoEB", "Pre-firing L1Noniso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
   occupancyL1preNonisoEB->GetYaxis()->SetTitle("eta index") ;
   occupancyL1preNonisoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * occupancyL1postIsoEB = new TH2F("occupancyL1postIsoEB", "Post-firing L1Iso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
   occupancyL1postIsoEB->GetYaxis()->SetTitle("eta index") ;
   occupancyL1postIsoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * occupancyL1postNonisoEB = new TH2F("occupancyL1postNonisoEB", "Post-firing L1Noniso Occupancy: Barrel", 72, 1, 73, 38, -19, 19) ;
   occupancyL1postNonisoEB->GetYaxis()->SetTitle("eta index") ;
   occupancyL1postNonisoEB->GetXaxis()->SetTitle("phi index") ;
   
   //endcap l1 occupancy
   TH2F * occupancyL1IsoEEPlus = new TH2F("occupancyL1IsoEEPlus", "L1Iso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1IsoEEPlus->GetYaxis()->SetTitle("y index") ;
   occupancyL1IsoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyL1IsoEEMinus = new TH2F("occupancyL1IsoEEMinus", "L1Iso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1IsoEEMinus->GetYaxis()->SetTitle("y index") ;
   occupancyL1IsoEEMinus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyL1NonisoEEPlus = new TH2F("occupancyL1NonisoEEPlus", "L1Noniso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1NonisoEEPlus->GetYaxis()->SetTitle("y index") ;
   occupancyL1NonisoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyL1NonisoEEMinus = new TH2F("occupancyL1NonisoEEMinus", "L1Noniso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1NonisoEEMinus->GetYaxis()->SetTitle("y index") ;
   occupancyL1NonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   TH2F * occupancyL1preIsoEEPlus = new TH2F("occupancyL1preIsoEEPlus", "Pre-firing L1Iso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1preIsoEEPlus->GetYaxis()->SetTitle("y index") ;
   occupancyL1preIsoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyL1preIsoEEMinus = new TH2F("occupancyL1preIsoEEMinus", "Pre-firing L1Iso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1preIsoEEMinus->GetYaxis()->SetTitle("y index") ;
   occupancyL1preIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyL1preNonisoEEPlus = new TH2F("occupancyL1preNonisoEEPlus", "Pre-firing L1Noniso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1preNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
   occupancyL1preNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyL1preNonisoEEMinus = new TH2F("occupancyL1preNonisoEEMinus", "Pre-firing L1Noniso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1preNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
   occupancyL1preNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   TH2F * occupancyL1postIsoEEPlus = new TH2F("occupancyL1postIsoEEPlus", "Post-firing L1Iso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1postIsoEEPlus->GetYaxis()->SetTitle("y index") ;
   occupancyL1postIsoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyL1postIsoEEMinus = new TH2F("occupancyL1postIsoEEMinus", "Post-firing L1Iso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1postIsoEEMinus->GetYaxis()->SetTitle("y index") ;
   occupancyL1postIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyL1postNonisoEEPlus = new TH2F("occupancyL1postNonisoEEPlus", "Post-firing L1Noniso Occupancy: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1postNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
   occupancyL1postNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * occupancyL1postNonisoEEMinus = new TH2F("occupancyL1postNonisoEEMinus", "Post-firing L1Noniso Occupancy: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   occupancyL1postNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
   occupancyL1postNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   //masked RCT regions
   TH2F * maskedRCT = new TH2F("maskedRCT", "Masked RCT Regions", 14, 4, 18, 18, 0, 18) ;
   maskedRCT->GetXaxis()->SetTitle("RCT eta index") ;
   maskedRCT->GetYaxis()->SetTitle("RCT phi index") ;
   
   TH2F * maskedRCTEB = new TH2F("maskedRCTEB", "Masked RCT Regions: Barrel", 72, 1, 73, 38, -19, 19) ;
   maskedRCTEB->GetXaxis()->SetTitle("eta index") ;
   maskedRCTEB->GetYaxis()->SetTitle("phi index") ;
   
   TH2F * maskedRCTEEPlus = new TH2F("maskedRCTEEPlus", "Masked RCT Regions: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   maskedRCTEEPlus->GetYaxis()->SetTitle("y index") ;
   maskedRCTEEPlus->GetXaxis()->SetTitle("x index") ;
   
   TH2F * maskedRCTEEMinus = new TH2F("maskedRCTEEMinus", "Masked RCT Regions: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   maskedRCTEEMinus->GetYaxis()->SetTitle("y index") ;
   maskedRCTEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
   //comparison with TPs 
   TH2F * L1MissingTPIso = new TH2F("L1MissingTPIso", "L1 Iso Mismatch: Missing TP", 14, 4, 18, 18, 0, 18) ;
   L1MissingTPIso->GetXaxis()->SetTitle("RCT eta index") ;
   L1MissingTPIso->GetYaxis()->SetTitle("RCT phi index") ;
   TH2F * L1MissingTPNoniso = new TH2F("L1MissingTPNoniso", "L1 Noniso Mismatch: Missing TP", 14, 4, 18, 18, 0, 18) ;
   L1MissingTPNoniso->GetXaxis()->SetTitle("RCT eta index") ;
   L1MissingTPNoniso->GetYaxis()->SetTitle("RCT phi index") ;
   
   //   TH2F * L1FractionMissingTPIso = new TH2F("L1FractionMissingTPIso", "Fraction of L1 Iso Mismatch: Missing TP", 14, 4, 18, 18, 0, 18) ;
   //   L1FractionMissingTPIso->GetXaxis()->SetTitle("RCT eta index") ;
   //   L1FractionMissingTPIso->GetYaxis()->SetTitle("RCT phi index") ;
   //   TH2F * L1FractionMissingTPNoniso = new TH2F("L1FractionMissingTPNoniso", "Fraction of L1 Noniso Mismatch: Missing TP", 14, 4, 18, 18, 0, 18) ;
   //   L1FractionMissingTPNoniso->GetXaxis()->SetTitle("RCT eta index") ;
   //   L1FractionMissingTPNoniso->GetYaxis()->SetTitle("RCT phi index") ;
   
   TH2F * L1ValueMismatchIso = new TH2F("L1ValueMismatchIso", "L1 Iso Mismatch: Value Mismatch", 14, 4, 18, 18, 0, 18) ;
   L1ValueMismatchIso->GetXaxis()->SetTitle("RCT eta index") ;
   L1ValueMismatchIso->GetYaxis()->SetTitle("RCT phi index") ;
   TH2F * L1ValueMismatchNoniso = new TH2F("L1ValueMismatchNoniso", "L1 Noniso Mismatch: Value Mismatch", 14, 4, 18, 18, 0, 18) ;
   L1ValueMismatchNoniso->GetXaxis()->SetTitle("RCT eta index") ;
   L1ValueMismatchNoniso->GetYaxis()->SetTitle("RCT phi index") ;
   
   TH1F * L1IsoRatio = new TH1F("L1IsoRatio", "iso ratio of sum of TPs to L1 rank", 1000, 0, 10.) ;
   TH1F * L1NonisoRatio = new TH1F("L1NonisoRatio", "noniso ratio of sum of TPs to L1 rank", 1000, 0, 10.) ;
   
   TH1F * L1Iso2TPSum = new TH1F("L1Iso2TPSum", "sum of two highest adjacent TPs in GCT region of L1 Iso Cand", 505, 0, 505.) ;
   TH1F * L1Noniso2TPSum = new TH1F("L1Noniso2TPSum", "sum of two highest adjacent TPs in GCT region of L1 Iso Cand", 505, 0, 505.) ;
   
   
   //barrel l1 geometric mismatch
   TH2F * L1MissingTPIsoEB = new TH2F("L1MissingTPIsoEB", "L1 Iso Mismatch: Missing TP: Barrel", 72, 1, 73, 38, -19, 19) ;
   L1MissingTPIsoEB->GetYaxis()->SetTitle("eta index") ;
   L1MissingTPIsoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * L1MissingTPNonisoEB = new TH2F("L1MissingTPNonisoEB", "L1 Noniso Mismatch: Missing TP: Barrel", 72, 1, 73, 38, -19, 19) ;
   L1MissingTPNonisoEB->GetYaxis()->SetTitle("eta index") ;
   L1MissingTPNonisoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * L1FractionMissingTPIsoEB = new TH2F("L1FractionMissingTPIsoEB", "Fraction of L1 Iso Mismatch: Missing TP: Barrel", 72, 1, 73, 38, -19, 19) ;
   L1FractionMissingTPIsoEB->GetYaxis()->SetTitle("eta index") ;
   L1FractionMissingTPIsoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * L1FractionMissingTPNonisoEB = new TH2F("L1FractionMissingTPNonisoEB", "Fraction of L1 Noniso Mismatch: Missing TP: Barrel", 72, 1, 73, 38, -19, 19) ;
   L1FractionMissingTPNonisoEB->GetYaxis()->SetTitle("eta index") ;
   L1FractionMissingTPNonisoEB->GetXaxis()->SetTitle("phi index") ;
   
   //endcap l1 geometric mismatch
   TH2F * L1MissingTPIsoEEPlus = new TH2F("L1MissingTPIsoEEPlus", "L1 Iso Mismatch: Missing TP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1MissingTPIsoEEPlus->GetYaxis()->SetTitle("y index") ;
   L1MissingTPIsoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1MissingTPIsoEEMinus = new TH2F("L1MissingTPIsoEEMinus", "L1 Iso Mismatch: Missing TP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1MissingTPIsoEEMinus->GetYaxis()->SetTitle("y index") ;
   L1MissingTPIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1MissingTPNonisoEEPlus = new TH2F("L1MissingTPNonisoEEPlus", "L1 Noniso Mismatch: Missing TP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1MissingTPNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
   L1MissingTPNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1MissingTPNonisoEEMinus = new TH2F("L1MissingTPNonisoEEMinus", "L1 Noniso Mismatch: Missing TP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1MissingTPNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
   L1MissingTPNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   TH2F * L1FractionMissingTPIsoEEPlus = new TH2F("L1FractionMissingTPIsoEEPlus", "Fraction of L1 Iso Mismatch: Missing TP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1FractionMissingTPIsoEEPlus->GetYaxis()->SetTitle("y index") ;
   L1FractionMissingTPIsoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1FractionMissingTPIsoEEMinus = new TH2F("L1FractionMissingTPIsoEEMinus", "Fraction of L1 Iso Mismatch: Missing TP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1FractionMissingTPIsoEEMinus->GetYaxis()->SetTitle("y index") ;
   L1FractionMissingTPIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1FractionMissingTPNonisoEEPlus = new TH2F("L1FractionMissingTPNonisoEEPlus", "Fraction of L1 Noniso Mismatch: Missing TP: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1FractionMissingTPNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
   L1FractionMissingTPNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1FractionMissingTPNonisoEEMinus = new TH2F("L1FractionMissingTPNonisoEEMinus", "Fraction of L1 Noniso Mismatch: Missing TP: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1FractionMissingTPNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
   L1FractionMissingTPNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   //barrel L1 TP comparisons
   TH2F * L1TPCompIsoEB = new TH2F("L1TPCompIsoEB", "L1 Iso - TP comparisons: Barrel", 72, 1, 73, 38, -19, 19) ;
   L1TPCompIsoEB->GetYaxis()->SetTitle("eta index") ;
   L1TPCompIsoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * L1TPCompNonisoEB = new TH2F("L1TPCompNonisoEB", "L1 Non Iso - TP comparisons: Barrel", 72, 1, 73, 38, -19, 19) ;
   L1TPCompNonisoEB->GetYaxis()->SetTitle("eta index") ;
   L1TPCompNonisoEB->GetXaxis()->SetTitle("phi index") ;
   
   //endcap L1 TP comparisons
   TH2F * L1TPCompIsoEEPlus = new TH2F("L1TPCompIsoEEPlus", "L1 Iso - TP comparisons: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1TPCompIsoEEPlus->GetYaxis()->SetTitle("y index") ;
   L1TPCompIsoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1TPCompIsoEEMinus = new TH2F("L1TPCompIsoEEMinus", "L1 Iso - TP comparisons: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1TPCompIsoEEMinus->GetYaxis()->SetTitle("y index") ;
   L1TPCompIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1TPCompNonisoEEPlus = new TH2F("L1TPCompNonisoEEPlus", "L1 Non Iso - TP comparisons: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1TPCompNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
   L1TPCompNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1TPCompNonisoEEMinus = new TH2F("L1TPCompNonisoEEMinus", "L1 Non Iso - TP comparisons: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1TPCompNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
   L1TPCompNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   // L1/TP ratio (ISO)
   TH3F * L1RatioTPIso3DEB = new TH3F("L1RatioTPIso3DEB", "L1 Iso: ADC Ratio L1/TP: Barrel", 72, 1, 73, 38, -19, 19, 150, 0., 1.5) ;
   L1RatioTPIso3DEB->GetYaxis()->SetTitle("eta index") ;
   L1RatioTPIso3DEB->GetXaxis()->SetTitle("phi index") ;
   
   TH3F * L1RatioTPIso3DEEPlus = new TH3F("L1RatioTPIso3DEEPlus", "L1 Iso: ADC Ratio L1/TP: Plus Endcap", 121, -10, 111, 121, -10, 111, 150, 0., 1.5) ;
   L1RatioTPIso3DEEPlus->GetYaxis()->SetTitle("y index") ;
   L1RatioTPIso3DEEPlus->GetXaxis()->SetTitle("x index") ;
   
   TH3F * L1RatioTPIso3DEEMinus = new TH3F("L1RatioTPIso3DEEMinus", "L1 Iso: ADC Ratio L1/TP: Minus Endcap", 121, -10, 111, 121, -10, 111, 150, 0., 1.5) ;
   L1RatioTPIso3DEEMinus->GetYaxis()->SetTitle("y index") ;
   L1RatioTPIso3DEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
   // L1/TP ratio (NON ISO)
   TH3F * L1RatioTPNoniso3DEB = new TH3F("L1RatioTPNoniso3DEB", "L1 Non Iso: ADC Ratio L1/TP: Barrel", 72, 1, 73, 38, -19, 19, 150, 0., 1.5) ;
   L1RatioTPNoniso3DEB->GetYaxis()->SetTitle("eta index") ;
   L1RatioTPNoniso3DEB->GetXaxis()->SetTitle("phi index") ;
   
   TH3F * L1RatioTPNoniso3DEEPlus = new TH3F("L1RatioTPNoniso3DEEPlus", "L1 Non Iso: ADC Ratio L1/TP: Plus Endcap", 121, -10, 111, 121, -10, 111, 150, 0., 1.5) ;
   L1RatioTPNoniso3DEEPlus->GetYaxis()->SetTitle("y index") ;
   L1RatioTPNoniso3DEEPlus->GetXaxis()->SetTitle("x index") ;
   
   TH3F * L1RatioTPNoniso3DEEMinus = new TH3F("L1RatioTPNoniso3DEEMinus", "L1 Non Iso: ADC Ratio L1/TP: Minus Endcap", 121, -10, 111, 121, -10, 111, 150, 0., 1.5) ;
   L1RatioTPNoniso3DEEMinus->GetYaxis()->SetTitle("y index") ;
   L1RatioTPNoniso3DEEMinus->GetXaxis()->SetTitle("x index") ;
   
   //barrel l1 value mismatch
   TH2F * L1ValueMismatchIsoEB = new TH2F("L1ValueMismatchIsoEB", "L1 Iso Mismatch: Value Mismatch: Barrel", 72, 1, 73, 38, -19, 19) ;
   L1ValueMismatchIsoEB->GetYaxis()->SetTitle("eta index") ;
   L1ValueMismatchIsoEB->GetXaxis()->SetTitle("phi index") ;
   TH2F * L1ValueMismatchNonisoEB = new TH2F("L1ValueMismatchNonisoEB", "L1 Noniso Mismatch: Value Mismatch: Barrel", 72, 1, 73, 38, -19, 19) ;
   L1ValueMismatchNonisoEB->GetYaxis()->SetTitle("eta index") ;
   L1ValueMismatchNonisoEB->GetXaxis()->SetTitle("phi index") ;
   
   //endcap l1 value mismatch
   TH2F * L1ValueMismatchIsoEEPlus = new TH2F("L1ValueMismatchIsoEEPlus", "L1 Iso Mismatch: Value Mismatch: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1ValueMismatchIsoEEPlus->GetYaxis()->SetTitle("y index") ;
   L1ValueMismatchIsoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1ValueMismatchIsoEEMinus = new TH2F("L1ValueMismatchIsoEEMinus", "L1 Iso Mismatch: Value Mismatch: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1ValueMismatchIsoEEMinus->GetYaxis()->SetTitle("y index") ;
   L1ValueMismatchIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1ValueMismatchNonisoEEPlus = new TH2F("L1ValueMismatchNonisoEEPlus", "L1 Noniso Mismatch: Value Mismatch: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1ValueMismatchNonisoEEPlus->GetYaxis()->SetTitle("y index") ;
   L1ValueMismatchNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
   TH2F * L1ValueMismatchNonisoEEMinus = new TH2F("L1ValueMismatchNonisoEEMinus", "L1 Noniso Mismatch: Value Mismatch: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   L1ValueMismatchNonisoEEMinus->GetYaxis()->SetTitle("y index") ;
   L1ValueMismatchNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
   //histos to hold the masked towers
   TH2F * MaskedTowersEB = new TH2F("MaskedTowersEB", "MaskedTowersEB", 72, 1, 73, 38, -19, 19) ;
   TH2F * MaskedTowersEEPlus = new TH2F("MaskedTowersEEPlus", "MaskedTowersEEPlus", 121, -10, 111, 121, -10, 111) ;
   TH2F * MaskedTowersEEMinus = new TH2F("MaskedTowersEEMinus", "MaskedTowersEEMinus", 121, -10, 111, 121, -10, 111) ;
   
   //histos to hold the masked towers
   TH2F * MaskedReadOutEB = new TH2F("MaskedReadOutEB", "MaskedReadOutEB", 72, 1, 73, 38, -19, 19) ;
   TH2F * MaskedReadOutEEPlus = new TH2F("MaskedReadOutEEPlus", "MaskedReadOutEEPlus", 121, -10, 111, 121, -10, 111) ;
   TH2F * MaskedReadOutEEMinus = new TH2F("MaskedReadOutEEMinus", "MaskedReadOutEEMinus", 121, -10, 111, 121, -10, 111) ;
   
   
   ///////////////////////
   // Chain the trees:
   ///////////////////////
   //from this, main analysis and filling the tree.
   //these two trees are from EcalTPGAnalyzer.cc. treeAux contains MaskedChannels information. EcalTPGAnalysis contains all the other information.
   TChain * chainAux = new TChain ("treeAux") ;
   TChain * chain = new TChain ("EcalTPGAnalysis") ;
  
   vector<string> files ;
   //if the inputfiles string has ":", but actually it will not, see from makeTrigPrimPlots.sh, it is "-i ECALTPGtree_${run}.root", directly the root name.
   if (inputfiles.find(string(":")) != string::npos) {
      vector<string> filesbase = split(inputfiles,":") ;
      if (filesbase.size() == 4) {
         int first = atoi(filesbase[1].c_str()) ;
         int last = atoi(filesbase[2].c_str()) ;
         for (int i=first ; i<=last ; i++) {
            stringstream name ;
            name<<filesbase[0]<<i<<filesbase[3] ;
            files.push_back(name.str()) ;
         }
      }
   }
   else files = split(inputfiles,",") ;
  
   //from above, the vector "files" contains all the input root files, here just cout them and Add them the chain. 
   for (uint i=0 ; i<uint(files.size()) ; i++) {
      files[i] = inputdir+files[i] ;
      cout<<"\nInput file: "<<files[i]<<endl ;
      chain->Add (files[i].c_str()) ;
      chainAux->Add (files[i].c_str()) ;
   }
   
   //here set all the adresses to the to-be-used tree variables in order to use them later. for tree EcalTPGAnalysis here.
   EcalTPGVariables treeVars ;
   setBranchAddresses (chain, treeVars) ;
  
   EcalTPGVariablesForIsoNonIso treeVarsIso; //FAN
   EcalTPGVariablesForIsoNonIso treeVarsNonIso; //FAN
   setBranchAddressesIso (chain, treeVarsIso) ;
   setBranchAddressesNonIso (chain, treeVarsNonIso) ; 


    
   //here for tree treeAux,the same as above
   EcalAux auxVars ;
   setAuxBranchAddresses (chainAux, auxVars) ;
   
   //according to the EcalTPGAnalyzer.cc, the MaskedChannels informations will only be asked for the first event, then fill them in the tree.So only one entry in the tree. here just get it! Even with only one entry, the values are not always one,because it has some arrays like iMaskedTTeta, iMaskedChannelsFromStripsX and so on. 
   chainAux->GetEntry (0) ;
   
   //cout the Masked towers in EB,EE+ and EE-
   cout << "\nMasked Towers:  " << endl;
   //here loop on all the Masked channels
   for (int nMaskCh = 0; nMaskCh < auxVars.nMaskedCh; nMaskCh++)
   {
      //store the Masked trigger tower ieta and iphi
      int ieta= auxVars.iMaskedTTeta[nMaskCh];  
      int iphi= auxVars.iMaskedTTphi[nMaskCh];
      int hashedIndex =0 ;
      if (ieta >0)
         hashedIndex = ieta * 100 + iphi ;
      else 
         hashedIndex = ieta * 100 - iphi ; 
      
      if (abs(ieta)<18) { //this is EB
         MaskedTowersEB->Fill(iphi, ieta) ; //fill this histo for EB
         cout << "   EB:  ieta=" << ieta << " iphi=" << iphi << endl;
      }
      else if(ieta<=-18){ //this EE-
         for (uint i=0; i !=geometry[hashedIndex].size();++i)
         {
            MaskedTowersEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
            cout << "   EE-:  ix=" << geometry[hashedIndex][i].first << " iy=" << geometry[hashedIndex][i].second << endl;
         }
      }
      else if(ieta>=18){ //this is EE+
         for (uint i=0; i !=geometry[hashedIndex].size();++i)
         {
            MaskedTowersEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
            cout << "   EE+:  ix=" << geometry[hashedIndex][i].first << " iy=" << geometry[hashedIndex][i].second << endl;
         }
      }
   }
  
   //cout the Masked strips in EE+ and EE- 
   cout << "\nMasked Strips in Endcaps:  " << endl;
   for (int nMaskChInStrip = 0; nMaskChInStrip < auxVars.nMaskedChannelsFromStrips; nMaskChInStrip++)
   { //loop all the masked strips
      if ( auxVars.iMaskedChannelsFromStripsZ[nMaskChInStrip] > 0 ){//see the Z-axis value to decide this is EE+
         
         MaskedTowersEEPlus->Fill(auxVars.iMaskedChannelsFromStripsX[nMaskChInStrip],auxVars.iMaskedChannelsFromStripsY[nMaskChInStrip]);
         cout << "   EE+: iStripsX=" << auxVars.iMaskedChannelsFromStripsX[nMaskChInStrip]
         << "  iStripsY" << auxVars.iMaskedChannelsFromStripsY[nMaskChInStrip] << endl;
      }
      if ( auxVars.iMaskedChannelsFromStripsZ[nMaskChInStrip] < 0 ) { //this is EE-
         MaskedTowersEEMinus->Fill(auxVars.iMaskedChannelsFromStripsX[nMaskChInStrip],auxVars.iMaskedChannelsFromStripsY[nMaskChInStrip]);
         cout << "   EE-: iStripsX=" << auxVars.iMaskedChannelsFromStripsX[nMaskChInStrip]
         << "  iStripsY=" << auxVars.iMaskedChannelsFromStripsY[nMaskChInStrip] << endl;
      }
      
   }
  
   // lastEntry is an argument here,also in the makeTrigPrimPlots.sh. I think it is also for the detail look if you want.
   if(lastEntry<0 || lastEntry>chain->GetEntries()) lastEntry = chain->GetEntries() ; //so if this argument is not specified,just cout the normal "GetEntries" of the tree EcalTPGAnalysis and give it to "lastEntry". Then later we will focus on this tree mainly.
   
   cout << "\n\nNumber of entries in rootuple: " << chain->GetEntries() <<endl;
   cout << "Entries to be processed: [" << firstEntry << "-" << lastEntry << "]\n\n";
   
   ULong64_t maxEvNb=0;
  
   
   
   ///////////////////////
   // Main loop over entries
   ///////////////////////
   
   int iRCT=0;
   for (int entry = firstEntry ; entry < lastEntry ; ++entry)//loop on all the entries and "firstEntry" has default value 0.
   {
      
      chain->GetEntry (entry) ; //for each loop, you should get entry, this is root.

     EcalTPGVariablesForIsoNonIso treeVarsIsoNonIso;  //FAN
     

     if (entry%100000==0) cout <<"------> Entry "<< entry <<" is being processed" << " <------\n" ; 
      bool keepEvent = false ;
   
 
      //compare to get the max eventID.  
      ULong64_t evNb = treeVars.evtNb; //evtNb is the event ID read from EcalTPGAnalyzer.cc
      if(evNb>maxEvNb) {
         maxEvNb=evNb;
      }
         
 

      //applying event selection
      //So here, this part is only used if you have asked for some specified event range by the argument "levent", it will only select the event with the event ID you pass to the code. But not used for now.
      if(eventIncludeVector.size()==0) keepEvent = true;
      for(uint i=0; i!=eventIncludeVector.size();++i){
         if(eventIncludeVector[i].size()==1 && evNb==eventIncludeVector[i][0]) keepEvent=true;
         else if(eventIncludeVector[i].size()==2 && (evNb>=eventIncludeVector[i][0] && evNb<=eventIncludeVector[i][1]) ) {
            keepEvent=true;
            //cout<<"include event vector"<<endl;
         }
         if(eventIncludeVector[i].size()==2 && eventIncludeVector[i][1]<eventIncludeVector[i][0] && evNb>=eventIncludeVector[i][0]) keepEvent=true;
      }
      if(!keepEvent) continue;
      
      keepEvent = true;
      for(uint i=0; i!=eventExcludeVector.size();++i){
         //cout<<"exclude event vector"<<endl;
         if(eventExcludeVector[i].size()==1 && evNb==eventExcludeVector[i][0]) keepEvent=false;
         else if(eventExcludeVector[i].size()==2 && (evNb>=eventExcludeVector[i][0] && evNb<=eventExcludeVector[i][1])) keepEvent=false;
      }
      if(!keepEvent) continue;
      if(!keepEvent) continue; //so this line is useless. 
     
 
      //applying 'GOODCOLL' selection if required
      bool keepGC = false;
      bool tech0 = false;
      bool tech40or41 = false;
      bool tech36or37or38or39 = false;
      bool tech42 = false;
      bool tech43 = false;
      for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
      { //loop on the number of ActiveTechTriggers,but not too clear about the numbers here. 
         if(treeVars.activeTechTriggers[ntrig]==0) tech0 = true;
         if(treeVars.activeTechTriggers[ntrig]==40 || treeVars.activeTechTriggers[ntrig]==41) tech40or41 = true;
         if(treeVars.activeTechTriggers[ntrig]==36 || treeVars.activeTechTriggers[ntrig]==37 || treeVars.activeTechTriggers[ntrig]==38 || treeVars.activeTechTriggers[ntrig]==39) tech36or37or38or39 = true;
         if(treeVars.activeTechTriggers[ntrig]==42) tech42 = true;
         if(treeVars.activeTechTriggers[ntrig]==43) tech43 = true;
      }
      bool tech42xor43 = false;
      if(tech42 && !tech43) tech42xor43 = true;
      if(tech43 && !tech42) tech42xor43 = true;
      if(GoodColl!=1 || (tech0 && tech40or41 && !(tech36or37or38or39) && !(tech42xor43))) keepGC = true; //check if it is worth to continue on this event.
      if (!keepGC) continue;
     
 
      //applying "techTrgs" option
      //here is to check techTrgs you pass to the code by argument "ltechtrig".If no, I think it will do nothing. If yes,it will only keep the event which has the good "ltechtrig".
      bool keep = false;
      if(techTrgIncludeVector.size()==0) keep = true;  
      for(uint i=0; i!=techTrgIncludeVector.size();++i){
         for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
         {
            if(techTrgIncludeVector[i].size()==1 && treeVars.activeTechTriggers[ntrig]==techTrgIncludeVector[i][0])
            {
               keep=true;
               //  cout << "event taken trg " <<   treeVars.activeTechTriggers[ntrig] << endl;
            }
            else if(techTrgIncludeVector[i].size()==2 && (treeVars.activeTechTriggers[ntrig]>=techTrgIncludeVector[i][0] && treeVars.activeTechTriggers[ntrig]<=techTrgIncludeVector[i][1]))
            {
               keep=true;
               // cout << "event taken trg " <<   treeVars.activeTechTriggers[ntrig] << endl;
            }
         }
      }
      if(!keep) continue;
     

      //here will check someting similar as above.  
      keep = true;
      for(uint i=0; i!=techTrgExcludeVector.size();++i){
         for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
         {
            if(techTrgExcludeVector[i].size()==1 && treeVars.activeTechTriggers[ntrig]==techTrgExcludeVector[i][0])
            {
               keep=false;
               //  cout << "event skipped trg " <<   treeVars.activeTechTriggers[ntrig] << endl;
            }
            else if(techTrgExcludeVector[i].size()==2 && (treeVars.activeTechTriggers[ntrig]>=techTrgExcludeVector[i][0] && treeVars.activeTechTriggers[ntrig]<=techTrgExcludeVector[i][1]))
            {
               keep=false;
               //  cout << "event skipped trg " <<   treeVars.activeTechTriggers[ntrig] << endl;
            }
         }
      }
      if(!keep) continue;
      
     
      //loop on all the Active Triggers.
      for(uint i=0;i!=treeVars.nbOfActiveTriggers;++i){
         //if (treeVars.activeTriggers[i]!=0) cout << treeVars.activeTriggers[i] << "\n";
         if (treeVars.activeTriggers[i]!=0) {
            triggerBit->Fill(treeVars.activeTriggers[i]) ; //fill the trigger bit.
         }
      }
      for(uint i=0;i!=128;++i){ //not clear why here 128
         int fireBX = int(treeVars.activeTriggersBX[i]/100);
         if(fireBX==1 || fireBX == 11 || fireBX == 111 || fireBX == 101)
         {//only look at on-time trigger
         FiredTriggers->Fill(i);
         }
      }
      
      int bxNb=treeVars.bxNb; //numbers of bunch crossing.
      
      //applying "bcs" option
      //here the same as above check the argument bcs if any. 
      keep = false;
      if(bcIncludeVector.size()==0) keep = true;  
      for(uint i=0; i!=bcIncludeVector.size();++i){
         if(bcIncludeVector[i].size()==1 && bxNb==bcIncludeVector[i][0]) keep=true;
         else if(bcIncludeVector[i].size()==2 && (bxNb>=bcIncludeVector[i][0] && bxNb<=bcIncludeVector[i][1])) keep=true;
      }
      if(!keep) continue;
      
      keep = true;
      for(uint i=0; i!=bcExcludeVector.size();++i){
         if(bcExcludeVector[i].size()==1 && bxNb==bcExcludeVector[i][0]) keep=false;
         else if(bcExcludeVector[i].size()==2 && (bxNb>=bcExcludeVector[i][0] && bxNb<=bcExcludeVector[i][1])) keep=false;
      }
      if(!keep) continue;
      
      
      //cout<<"event kept BX"<<endl;
      
      ULong64_t orbitNb = treeVars.orbitNb;
      
      //applying "orbits" option
      //also check the argument orbits.
      keep = false;
      if(orbitIncludeVector.size()==0) keep = true;
      for(uint i=0; i!=orbitIncludeVector.size();++i){
         if(orbitIncludeVector[i].size()==1 && (orbitNb)/1000000.==orbitIncludeVector[i][0]) keep=true;
         else if(orbitIncludeVector[i].size()==2 && ((orbitNb)/1000000.>=orbitIncludeVector[i][0] && (orbitNb)/1000000.<=orbitIncludeVector[i][1])) keep=true;
      }
      if(!keep) continue;
      
      keep = true;
      for(uint i=0; i!=orbitExcludeVector.size();++i){
         if(orbitExcludeVector[i].size()==1 && (orbitNb)/1000000.==orbitExcludeVector[i][0]) keep=false;
         else if(orbitExcludeVector[i].size()==2 && ((orbitNb)/1000000.>=orbitExcludeVector[i][0] && (orbitNb)/1000000.<=orbitExcludeVector[i][1])) keep=false;
      }
      if(!keep) continue;
      
      
      int lumiNb = treeVars.lumiBlock;
      
      //applying "lumi" option
      //the same, check the argument lumi.
      keep = false;
      if(lumiIncludeVector.size()==0) keep = true;
      for(uint i=0; i!=lumiIncludeVector.size();++i){
         if(lumiIncludeVector[i].size()==1 && lumiNb==lumiIncludeVector[i][0]) keep=true;
         else if(lumiIncludeVector[i].size()==2 && (lumiNb>=lumiIncludeVector[i][0] && lumiNb<=lumiIncludeVector[i][1])) keep=true;
      }
      if(!keep) continue;
      
      keep = true;
      for(uint i=0; i!=lumiExcludeVector.size();++i){
         if(lumiExcludeVector[i].size()==1 && lumiNb==lumiExcludeVector[i][0]) keep=false;
         else if(lumiExcludeVector[i].size()==2 && (lumiNb>=lumiExcludeVector[i][0] && lumiNb<=lumiExcludeVector[i][1])) keep=false;
      }
      if(!keep) continue;
      
      
      //cout<<"event kept lumi"<<endl;
      
      double timeStamp = treeVars.timeStamp-slMinTime;
      
      //applying "timestamps" option
      //check the timestamps.
      keep = false;
      if(timestampIncludeVector.size()==0) keep = true;
      for(uint i=0; i!=timestampIncludeVector.size();++i){
         if(timestampIncludeVector[i].size()==1 && timeStamp==timestampIncludeVector[i][0]) keep=true;
         else if(timestampIncludeVector[i].size()==2 && (timeStamp>=timestampIncludeVector[i][0] && timeStamp<=timestampIncludeVector[i][1])) keep=true;
      }
      if(!keep) continue;
      
      keep = true;
      for(uint i=0; i!=timestampExcludeVector.size();++i){
         if(timestampExcludeVector[i].size()==1 && timeStamp==timestampExcludeVector[i][0]) keep=false;
         else if(timestampExcludeVector[i].size()==2 && (timeStamp>=timestampExcludeVector[i][0] && timeStamp<=timestampExcludeVector[i][1])) keep=false;
      }
      if(!keep) continue;
      
      
      
      // trigger selection if any, the same as before, check the argument l1algo.
      keep=false ;
      if (!algobits.size()) keep = true ; // keep all events when no trigger selection
      for (uint algo = 0 ; algo<algobits.size() ; algo++)
         for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTriggers ; ntrig++)
            if (algobits[algo] == treeVars.activeTriggers[ntrig]) keep = true ;
      if (!keep) continue ;
     
 
      //not too clear, why 45 and 46 here.
      int * ibitGT45;
      ibitGT45 = unhashTr(treeVars.activeTriggersBX[45]);    
      
      int * ibitGT46;
      ibitGT46 = unhashTr(treeVars.activeTriggersBX[46]);
      
      for (int kshift = 0;kshift<5;kshift++)
      {
         if (ibitGT45[kshift]==1) bx_bit45_all->Fill(treeVars.bxNb+kshift-2);
         if (ibitGT46[kshift]==1) bx_bit46_all->Fill(treeVars.bxNb+kshift-2);
      }
      if (ibitGT45[2]==1) bx_nTT->Fill(treeVars.nbOfTowers);
      
      delete [] ibitGT46;
      delete [] ibitGT45;
      
      
      //int egbits = {40,41,42,43,44,45,46,47,48,49,50,51,52}
      TH2F l1EGAlgos2Dtest("L1EGAlgos2Dtest","L1EGAlgos2Dtest", 30, 39.5 , 69.5, 30, 39.5 , 69.5);
      
      //not too clear what is it doing. 
      for (int ibit = 40; ibit<=52;ibit++)
      {
         int * ibitGT;
         ibitGT = unhashTr(treeVars.activeTriggersBX[ibit]);
         if (ibitGT[2]==1) l1EGAlgos->Fill(ibit);
         for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
         {
            if (ibitGT[2]==1) histoEgTrigTechTrigCor->Fill(ibit,treeVars.activeTechTriggers[ntrig]);
         }
         
         
         
         for (int ibit2 = 40; ibit2<=52;ibit2++)
         {
            int * ibitGT2;   
            ibitGT2 = unhashTr(treeVars.activeTriggersBX[ibit2]);
            
            
            if (ibitGT[2]==1 && ibitGT2[2]==1)
               //       && l1EGAlgos2Dtest.GetBinContent(ibit-39,ibit2-39)>-100)
            { 
               l1EGAlgos2D->Fill(ibit,ibit2);
               l1EGAlgos2Dtest.Fill(ibit,ibit2);
               
            }
            delete [] ibitGT2;
         }
         delete [] ibitGT;
      }
     

 
      // Tech Triggers correlation plots
      
      for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTechTriggers ; ntrig++)
      { //loop on all the Active TechTriggers and fill it both 1D and 2D.
         techTrigCor->Fill(treeVars.activeTechTriggers[ntrig]);
         for (uint ntrig2 = 0 ; ntrig2 < treeVars.nbOfActiveTechTriggers ; ntrig2++)
         {
            techTrigCor2D->Fill(treeVars.activeTechTriggers[ntrig],treeVars.activeTechTriggers[ntrig2] );  //the 2D plots, you can see the correlation between each activeTechTriggers, because the X-axis is one activeTechTriggers,and the Y-axis is the other all including itself.
         }
      }
      
      // end Tech Triggers correlation plots
      
      
      
      // fill RCT masks
      if(iRCT==0) {
         for (uint iMaskRCT = 0 ; iMaskRCT < treeVars.nMaskedRCT ; iMaskRCT++) { //loop on all the Masked RCT
            int tteta = 0;
            if (treeVars.iMaskedRCTcrate[iMaskRCT]>8) tteta = treeVars.iMaskedRCTeta[iMaskRCT]+1; 
            else tteta = - treeVars.iMaskedRCTeta[iMaskRCT]-1; //get the trigger tower eta, but have differnt value in different case.
            int rcteta = getGCTRegionEta(tteta); //call the funtion to compute the RCTeta from TTeta.
            int rctphi = getGCTRegionPhi2(treeVars.iMaskedRCTcrate[iMaskRCT],treeVars.iMaskedRCTphi[iMaskRCT]); //compute the RCTphi
            vector<int>  ttphi =  getECALRegionPhi(rctphi); //compute the TTphi.
            maskedRCT->Fill(rcteta,rctphi); //Fill masked RCT in eta and phi.
            for(uint j=0;j!=ttphi.size();++j) //loop on TTphi and fill the maskedRCT in EB, EE+ and EE- seperately.
            {   
               int l1hash=0;
               if (tteta>0) l1hash= tteta * 100 + ttphi[j] ;
               else l1hash = tteta * 100 - ttphi[j] ;   
               if(abs(tteta)<18)
               { //EB
               maskedRCTEB->Fill(ttphi[j],tteta);
               }
               if (tteta>=18)
               { //EE+
               for (uint k=0; k !=geometry[l1hash].size();++k){
                  maskedRCTEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
               }
               }
               if(tteta<=-18)
               { //EE-
               for (uint k=0; k !=geometry[l1hash].size();++k){
                  maskedRCTEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
               }
               }
            }
         }
         iRCT=1;
      }
      
      
      //cout<<"event kept RCT"<<endl;
      
     //fill some L1 histograms
     TH1F *nbOfL1Cands_temp; TH1F *L1CandRank_temp; TH1F *L1timing_temp; TH1F *L1timingEB_temp; TH1F *L1timingEEPlus_temp; TH1F *L1timingEEMinus_temp;
     TH2F *occupancyL1_temp; TH2F *occupancyL1EB_temp; TH2F *occupancyL1EEPlus_temp; TH2F *occupancyL1EEMinus_temp;  
     //EcalTPGVariablesForIsoNonIso treeVarsIsoNonIso;
     for( int iloop = 0; iloop < 2; iloop++ ){ //FAN begin fill some L1 histograms,first for iso, second for noniso
         if(iloop == 0){
             treeVarsIsoNonIso = treeVarsIso;
             cout << treeVarsIsoNonIso.nbOfL1Cands << endl;
             nbOfL1Cands_temp = (TH1F*)nbOfL1IsoCands->Clone("nbOfL1IsoCands");
             occupancyL1_temp = (TH2F*)occupancyL1Iso->Clone("occupancyL1Iso");
             L1CandRank_temp = (TH1F*)L1IsoCandRank->Clone("L1IsoCandRank");
             L1timing_temp = (TH1F*)L1Isotiming->Clone("L1Isotiming");
             L1timingEB_temp = (TH1F*)L1IsotimingEB->Clone("L1IsotimingEB"); 
             L1timingEEPlus_temp = (TH1F*)L1IsotimingEEPlus->Clone("L1IsotimingEEPlus");
             L1timingEEMinus_temp = (TH1F*)L1IsotimingEEMinus->Clone("L1IsotimingEEMinus");
             occupancyL1EB_temp = (TH2F*)occupancyL1IsoEB->Clone("occupancyL1IsoEB");
             occupancyL1EEPlus_temp = (TH2F*)occupancyL1IsoEEPlus->Clone("occupancyL1IsoEEPlus");
             occupancyL1EEMinus_temp = (TH2F*)occupancyL1IsoEEMinus->Clone("occupancyL1IsoEEMinus");
         }
         else{
           
             treeVarsIsoNonIso = treeVarsNonIso;
             //setBranchAddressesNonIso (chain, treeVarsIsoNonIso) ; 
             
             nbOfL1Cands_temp = (TH1F*)nbOfL1NonisoCands->Clone("nbOfL1NonisoCands");
             occupancyL1_temp = (TH2F*)occupancyL1Noniso->Clone("occupancyL1Noniso");
             L1CandRank_temp = (TH1F*)L1NonisoCandRank->Clone("L1NonisoCandRank");
             L1timing_temp = (TH1F*)L1Nonisotiming->Clone("L1Nonisotiming");
             L1timingEB_temp = (TH1F*)L1NonisotimingEB->Clone("L1NonisotimingEB");
             L1timingEEPlus_temp = (TH1F*)L1NonisotimingEEPlus->Clone("L1NonisotimingEEPlus");
             L1timingEEMinus_temp = (TH1F*)L1NonisotimingEEMinus->Clone("L1NonisotimingEEMinus");
             occupancyL1EB_temp = (TH2F*)occupancyL1NonisoEB->Clone("occupancyL1NonisoEB");
             occupancyL1EEPlus_temp = (TH2F*)occupancyL1NonisoEEPlus->Clone("occupancyL1NonisoEEPlus");
             occupancyL1EEMinus_temp = (TH2F*)occupancyL1NonisoEEMinus->Clone("occupancyL1NonisoEEMinus");
         }
        
 
         nbOfL1Cands_temp->Fill(treeVarsIsoNonIso.nbOfL1Cands);
         for (uint l1isocand = 0 ; l1isocand < treeVarsIsoNonIso.nbOfL1Cands ; l1isocand++)
         { //loop on l1 iso candidates
            //if(treeVarsIsoNonIso.L1IsoRank[l1isocand]>=2*eg) {//require EG2 by default, EG eg in general
            if(treeVarsIsoNonIso.L1Rank[l1isocand]>=eg)
            { //require EG2 by default, EG eg in general
            occupancyL1_temp->Fill(treeVarsIsoNonIso.L1Ieta[l1isocand],treeVarsIsoNonIso.L1Iphi[l1isocand]);
            L1CandRank_temp->Fill(treeVarsIsoNonIso.L1Rank[l1isocand]);
            L1timing_temp->Fill(0);
            vector<int> tteta = getECALRegionEta(treeVarsIsoNonIso.L1Ieta[l1isocand]);
            vector<int> ttphi = getECALRegionPhi(treeVarsIsoNonIso.L1Iphi[l1isocand]);
            if(abs(tteta[0])<17){//EB
                  L1timingEB_temp->Fill(0);
            }
            if(tteta[0]>=17){//EE+
                  L1timingEEPlus_temp->Fill(0); 
            }
            if(tteta[0]<=-17){//EE-
                  L1timingEEMinus_temp->Fill(0);   
            }
            
            for(uint i=0;i!=tteta.size();++i){
               for(uint j=0;j!=ttphi.size();++j){   
                  int l1hash=0;
                  if (tteta[i]>0)
                     l1hash= tteta[i] * 100 + ttphi[j] ;
                  else 
                     l1hash = tteta[i] * 100 - ttphi[j] ;
                  
                  
                  if(abs(tteta[i])<18){//EB
                        occupancyL1EB_temp->Fill(ttphi[j],tteta[i]);
                  }
                  if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1hash].size();++k){
                           occupancyL1EEPlus_temp->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                        }
                  }
                  if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1hash].size();++k){
                           occupancyL1EEMinus_temp->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                        }
                  }
               }
            }
            }
         }

      }// FAN end fill some L1 histograms 
      

      // OLD part
      /*
      nbOfL1IsoCands->Fill(treeVars.nbOfL1IsoCands);
      for (uint l1isocand = 0 ; l1isocand < treeVars.nbOfL1IsoCands ; l1isocand++)
      { //loop on l1 iso candidates
         //if(treeVars.L1IsoRank[l1isocand]>=2*eg) {//require EG2 by default, EG eg in general
         if(treeVars.L1IsoRank[l1isocand]>=eg)
         { //require EG2 by default, EG eg in general
         occupancyL1Iso->Fill(treeVars.L1IsoIeta[l1isocand],treeVars.L1IsoIphi[l1isocand]);
         L1IsoCandRank->Fill(treeVars.L1IsoRank[l1isocand]);
         L1Isotiming->Fill(0);
         vector<int> tteta = getECALRegionEta(treeVars.L1IsoIeta[l1isocand]);
         vector<int> ttphi = getECALRegionPhi(treeVars.L1IsoIphi[l1isocand]);
         if(abs(tteta[0])<17){//EB
               L1IsotimingEB->Fill(0);
         }
         if(tteta[0]>=17){//EE+
               L1IsotimingEEPlus->Fill(0); 
         }
         if(tteta[0]<=-17){//EE-
               L1IsotimingEEMinus->Fill(0);   
         }
         
         for(uint i=0;i!=tteta.size();++i){
            for(uint j=0;j!=ttphi.size();++j){   
               int l1hash=0;
               if (tteta[i]>0)
                  l1hash= tteta[i] * 100 + ttphi[j] ;
               else 
                  l1hash = tteta[i] * 100 - ttphi[j] ;
               
               
               if(abs(tteta[i])<18){//EB
                     occupancyL1IsoEB->Fill(ttphi[j],tteta[i]);
               }
               if(tteta[i]>=18){//EE+
                     for (uint k=0; k !=geometry[l1hash].size();++k){
                        occupancyL1IsoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                     }
               }
               if(tteta[i]<=-18){//EE-
                     for (uint k=0; k !=geometry[l1hash].size();++k){
                        occupancyL1IsoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                     }
               }
            }
         }
         }
      }
      
       
      nbOfL1NonisoCands->Fill(treeVars.nbOfL1NonisoCands);
      for (uint l1nonisocand = 0 ; l1nonisocand < treeVars.nbOfL1NonisoCands ; l1nonisocand++)
      {
         if(treeVars.L1NonisoRank[l1nonisocand]>=eg)
         { //require EG2 by default, EG eg in general
         occupancyL1Noniso->Fill(treeVars.L1NonisoIeta[l1nonisocand],treeVars.L1NonisoIphi[l1nonisocand]);
         L1NonisoCandRank->Fill(treeVars.L1NonisoRank[l1nonisocand]);
         L1Nonisotiming->Fill(0);
         vector<int> tteta = getECALRegionEta(treeVars.L1NonisoIeta[l1nonisocand]);
         vector<int> ttphi = getECALRegionPhi(treeVars.L1NonisoIphi[l1nonisocand]);
         if(abs(tteta[0])<17){//EB
               L1NonisotimingEB->Fill(0);
         }
         if(tteta[0]>=17){//EE+
               L1NonisotimingEEPlus->Fill(0); 
         }
         if(tteta[0]<=-17){//EE-
               L1NonisotimingEEMinus->Fill(0);   
         }
         
         for(uint i=0;i!=tteta.size();++i){
            for(uint j=0;j!=ttphi.size();++j){   
               int l1hash=0;
               if (tteta[i]>0)
                  l1hash= tteta[i] * 100 + ttphi[j] ;
               else 
                  l1hash = tteta[i] * 100 - ttphi[j] ;
               
               if(abs(tteta[i])<18){//EB
                     occupancyL1NonisoEB->Fill(ttphi[j],tteta[i]);
               }
               if(tteta[i]>=18){//EE+
                     for (uint k=0; k !=geometry[l1hash].size();++k){
                        occupancyL1NonisoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                     }
               }
               if(tteta[i]<=-18){//EE-
                     for (uint k=0; k !=geometry[l1hash].size();++k){
                        occupancyL1NonisoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                     }
               }
            }
         }
         }
      }
      */ 

    
 
      //fill some pre-firing L1 histograms
      TH1F *nbOfL1preCands_temp; TH1F *L1preCandRank_temp; 
      TH2F *occupancyL1pre_temp; TH2F *occupancyL1preEB_temp; TH2F *occupancyL1preEEPlus_temp; TH2F *occupancyL1preEEMinus_temp; 
   
      for( int iloop = 0; iloop < 2; iloop++ ){ //FAN begin fill some L1 histograms,first for iso, second for noniso
          if(iloop == 0){
              treeVarsIsoNonIso = treeVarsIso;
              cout << treeVarsIsoNonIso.nbOfL1preCands << endl;
              nbOfL1preCands_temp = (TH1F*)nbOfL1preCands_temp->Clone("nbOfL1preIsoCands");
              L1preCandRank_temp = (TH1F*)L1preCandRank_temp->Clone("L1preIsoCandRank");
              L1timing_temp = (TH1F*)L1Isotiming->Clone("L1Isotiming");
              L1timingEB_temp = (TH1F*)L1IsotimingEB->Clone("L1IsotimingEB");
              L1timingEEPlus_temp = (TH1F*)L1IsotimingEEPlus->Clone("L1IsotimingEEPlus");
              L1timingEEMinus_temp = (TH1F*)L1IsotimingEEMinus->Clone("L1IsotimingEEMinus");
              occupancyL1pre_temp = (TH2F*)occupancyL1pre_temp->Clone("occupancyL1preIso");
              occupancyL1preEB_temp = (TH2F*)occupancyL1preEB_temp->Clone("occupancyL1preIsoEB");
              occupancyL1preEEPlus_temp = (TH2F*)occupancyL1preEEPlus_temp->Clone("occupancyL1preIsoEEPlus");
              occupancyL1preEEMinus_temp = (TH2F*)occupancyL1preEEMinus_temp->Clone("occupancyL1preIsoEEMinus");
          }
          else{
              treeVarsIsoNonIso = treeVarsNonIso;
              nbOfL1preCands_temp = (TH1F*)nbOfL1preCands_temp->Clone("nbOfL1preNonisoCands");
              L1preCandRank_temp = (TH1F*)L1preCandRank_temp->Clone("L1preNonisoCandRank");
              L1timing_temp = (TH1F*)L1Isotiming->Clone("L1Nonisotiming");
              L1timingEB_temp = (TH1F*)L1IsotimingEB->Clone("L1NonisotimingEB");
              L1timingEEPlus_temp = (TH1F*)L1IsotimingEEPlus->Clone("L1NonisotimingEEPlus");
              L1timingEEMinus_temp = (TH1F*)L1IsotimingEEMinus->Clone("L1NonisotimingEEMinus");
              occupancyL1pre_temp = (TH2F*)occupancyL1pre_temp->Clone("occupancyL1preNoniso");
              occupancyL1preEB_temp = (TH2F*)occupancyL1preEB_temp->Clone("occupancyL1preNonisoEB");
              occupancyL1preEEPlus_temp = (TH2F*)occupancyL1preEEPlus_temp->Clone("occupancyL1preNonisoEEPlus");
              occupancyL1preEEMinus_temp = (TH2F*)occupancyL1preEEMinus_temp->Clone("occupancyL1preNonisoEEMinus");

          } 
          nbOfL1preCands_temp->Fill(treeVarsIsoNonIso.nbOfL1preCands);
          for (uint l1preisocand = 0 ; l1preisocand < treeVarsIsoNonIso.nbOfL1preCands ; l1preisocand++) //loop on pre-firing L1 candidates //FAN
          {
             if(treeVarsIsoNonIso.L1preRank[l1preisocand]>=2)
             {
                if(treeVarsIsoNonIso.L1preRank[l1preisocand]>=eg)//eg is an argument, and in makeTrigPrimPlots.sh is the argument "-e", the value is 5,not too clear about this L1preIsoRank. But if the value is above the given eg, then the histo will be filled.
                { //require EG2 by default, EG eg in general
                occupancyL1pre_temp->Fill(treeVarsIsoNonIso.L1preIeta[l1preisocand],treeVarsIsoNonIso.L1preIphi[l1preisocand]); //2D plots with Ieta and Iphi.
                L1preCandRank_temp->Fill(treeVarsIsoNonIso.L1preRank[l1preisocand]);
                L1timing_temp->Fill(-1);
                vector<int> tteta = getECALRegionEta(treeVarsIsoNonIso.L1preIeta[l1preisocand]); //compute the TTeta and TTphi
                vector<int> ttphi = getECALRegionPhi(treeVarsIsoNonIso.L1preIphi[l1preisocand]);
                
                if(abs(tteta[0])<17){//EB
                      L1timingEB_temp->Fill(-1);
                }
                if(tteta[0]>=17){//EE+
                      L1timingEEPlus_temp->Fill(-1); 
                }
                if(tteta[0]<=-17){//EE-
                      L1timingEEMinus_temp->Fill(-1);   
                }
               
                //loop on TTeta to fill the similar plots in the EB, EE+ and EE-. 
                for(uint i=0;i!=tteta.size();++i){
                   for(uint j=0;j!=ttphi.size();++j){ 
                      int l1prehash=0;
                      if (tteta[i]>0)
                         l1prehash= tteta[i] * 100 + ttphi[j] ;
                      else 
                         l1prehash = tteta[i] * 100 - ttphi[j] ;
                      
                      
                      if(abs(tteta[i])<18){//EB
                            occupancyL1preEB_temp->Fill(ttphi[j],tteta[i]);
                      }
                      if(tteta[i]>=18){//EE+
                            for (uint k=0; k !=geometry[l1prehash].size();++k){
                               occupancyL1preEEPlus_temp->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                            }
                      }
                      if(tteta[i]<=-18){//EE-
                            for (uint k=0; k !=geometry[l1prehash].size();++k){
                               occupancyL1preEEMinus_temp->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                            }
                      }
                   }
                }
                }
             }
          }
        } //end fill some pre-firing L1 histograms
   
      //OLD part
      //fill some pre-firing L1 histograms
      /*
      nbOfL1preIsoCands->Fill(treeVars.nbOfL1preIsoCands);
      for (uint l1preisocand = 0 ; l1preisocand < treeVars.nbOfL1preIsoCands ; l1preisocand++) //loop on pre-firing L1 candidates //FAN
      {
         if(treeVars.L1preIsoRank[l1preisocand]>=2)
         {
            if(treeVars.L1preIsoRank[l1preisocand]>=eg)//eg is an argument, and in makeTrigPrimPlots.sh is the argument "-e", the value is 5,not too clear about this L1preIsoRank. But if the value is above the given eg, then the histo will be filled.
            { //require EG2 by default, EG eg in general
            occupancyL1preIso->Fill(treeVars.L1preIsoIeta[l1preisocand],treeVars.L1preIsoIphi[l1preisocand]); //2D plots with Ieta and Iphi.
            L1preIsoCandRank->Fill(treeVars.L1preIsoRank[l1preisocand]);
            L1Isotiming->Fill(-1);
            vector<int> tteta = getECALRegionEta(treeVars.L1preIsoIeta[l1preisocand]); //compute the TTeta and TTphi
            vector<int> ttphi = getECALRegionPhi(treeVars.L1preIsoIphi[l1preisocand]);
            
            if(abs(tteta[0])<17){//EB
                  L1IsotimingEB->Fill(-1);
            }
            if(tteta[0]>=17){//EE+
                  L1IsotimingEEPlus->Fill(-1); 
            }
            if(tteta[0]<=-17){//EE-
                  L1IsotimingEEMinus->Fill(-1);   
            }
           
            //loop on TTeta to fill the similar plots in the EB, EE+ and EE-. 
            for(uint i=0;i!=tteta.size();++i){
               for(uint j=0;j!=ttphi.size();++j){ 
                  int l1prehash=0;
                  if (tteta[i]>0)
                     l1prehash= tteta[i] * 100 + ttphi[j] ;
                  else 
                     l1prehash = tteta[i] * 100 - ttphi[j] ;
                  
                  
                  if(abs(tteta[i])<18){//EB
                        occupancyL1preIsoEB->Fill(ttphi[j],tteta[i]);
                  }
                  if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1prehash].size();++k){
                           occupancyL1preIsoEEPlus->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                        }
                  }
                  if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1prehash].size();++k){
                           occupancyL1preIsoEEMinus->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                        }
                  }
               }
            }
            }
         }
      }
      

      //now do on the non iso candidates. the structure is almost the same as the iso candidates above.
      nbOfL1preNonisoCands->Fill(treeVars.nbOfL1preNonisoCands);
      for (uint l1prenonisocand = 0 ; l1prenonisocand < treeVars.nbOfL1preNonisoCands ; l1prenonisocand++)  //loop on L1 NoISO candidates //FAN
      {
         if(treeVars.L1preNonisoRank[l1prenonisocand]>=2)
         {
            if(treeVars.L1preNonisoRank[l1prenonisocand]>=eg)
            { //require EG2 by default, EG eg in general
            occupancyL1preNoniso->Fill(treeVars.L1preNonisoIeta[l1prenonisocand],treeVars.L1preNonisoIphi[l1prenonisocand]);
            L1preNonisoCandRank->Fill(treeVars.L1preNonisoRank[l1prenonisocand]);
            L1Nonisotiming->Fill(-1);
            vector<int> tteta = getECALRegionEta(treeVars.L1preNonisoIeta[l1prenonisocand]);
            vector<int> ttphi = getECALRegionPhi(treeVars.L1preNonisoIphi[l1prenonisocand]);
            
            if(abs(tteta[0])<17){//EB
                  L1NonisotimingEB->Fill(-1);
            }
            if(tteta[0]>=17){//EE+
                  L1NonisotimingEEPlus->Fill(-1); 
            }
            if(tteta[0]<=-17){//EE-
                  L1NonisotimingEEMinus->Fill(-1);   
            }
            
            for(uint i=0;i!=tteta.size();++i){
               for(uint j=0;j!=ttphi.size();++j){ 
                  int l1prehash=0;
                  if (tteta[i]>0)
                     l1prehash= tteta[i] * 100 + ttphi[j] ;
                  else 
                     l1prehash = tteta[i] * 100 - ttphi[j] ;
                  
                  
                  if(abs(tteta[i])<18){//EB
                        occupancyL1preNonisoEB->Fill(ttphi[j],tteta[i]);
                  }
                  if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1prehash].size();++k){
                           occupancyL1preNonisoEEPlus->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                        }
                  }
                  if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1prehash].size();++k){
                           occupancyL1preNonisoEEMinus->Fill(geometry[l1prehash][k].first,geometry[l1prehash][k].second ) ;
                        }
                  }
               }
            }
            }
         }
      }
      */   



      //fill some post-firing L1 histograms
      //so here the stucture is almost the same as the pre-firing plots above. For iso and non-iso, for all and also seperately EB,EE+,EE-.
      TH1F *nbOfL1postCands_temp; TH1F *L1postCandRank_temp;
      TH2F *occupancyL1post_temp; TH2F *occupancyL1postEB_temp; TH2F *occupancyL1postEEPlus_temp; TH2F *occupancyL1postEEMinus_temp; 

      for( int iloop = 0; iloop < 2; iloop++ ){ //FAN begin fill some L1 histograms,first for iso, second for noniso
          if(iloop == 0){
              treeVarsIsoNonIso = treeVarsIso;
              cout << treeVarsIsoNonIso.nbOfL1preCands << endl;
              nbOfL1postCands_temp = (TH1F*)nbOfL1postCands_temp->Clone("nbOfL1postIsoCands");
              L1postCandRank_temp = (TH1F*)L1postCandRank_temp->Clone("L1postIsoCandRank");
              L1timing_temp = (TH1F*)L1Isotiming->Clone("L1Isotiming");
              L1timingEB_temp = (TH1F*)L1IsotimingEB->Clone("L1IsotimingEB");
              L1timingEEPlus_temp = (TH1F*)L1IsotimingEEPlus->Clone("L1IsotimingEEPlus");
              L1timingEEMinus_temp = (TH1F*)L1IsotimingEEMinus->Clone("L1IsotimingEEMinus");
              occupancyL1post_temp = (TH2F*)occupancyL1post_temp->Clone("occupancyL1postIso");
              occupancyL1postEB_temp = (TH2F*)occupancyL1postEB_temp->Clone("occupancyL1postIsoEB");
              occupancyL1postEEPlus_temp = (TH2F*)occupancyL1postEEPlus_temp->Clone("occupancyL1postIsoEEPlus");
              occupancyL1postEEMinus_temp = (TH2F*)occupancyL1postEEMinus_temp->Clone("occupancyL1postIsoEEMinus");
           }
           else{
              treeVarsIsoNonIso = treeVarsNonIso;
              nbOfL1postCands_temp = (TH1F*)nbOfL1postCands_temp->Clone("nbOfL1postNonisoCands");
              L1postCandRank_temp = (TH1F*)L1postCandRank_temp->Clone("L1postNonisoCandRank");
              L1timing_temp = (TH1F*)L1Isotiming->Clone("L1Nonisotiming");
              L1timingEB_temp = (TH1F*)L1IsotimingEB->Clone("L1NonisotimingEB");
              L1timingEEPlus_temp = (TH1F*)L1IsotimingEEPlus->Clone("L1NonisotimingEEPlus");
              L1timingEEMinus_temp = (TH1F*)L1IsotimingEEMinus->Clone("L1NonisotimingEEMinus");
              occupancyL1post_temp = (TH2F*)occupancyL1post_temp->Clone("occupancyL1postNoniso");
              occupancyL1postEB_temp = (TH2F*)occupancyL1postEB_temp->Clone("occupancyL1postNonisoEB");
              occupancyL1postEEPlus_temp = (TH2F*)occupancyL1postEEPlus_temp->Clone("occupancyL1postNonisoEEPlus");
              occupancyL1postEEMinus_temp = (TH2F*)occupancyL1postEEMinus_temp->Clone("occupancyL1postNonisoEEMinus");

           }
           
           nbOfL1postCands_temp->Fill(treeVarsIsoNonIso.nbOfL1postCands);
           for (uint l1postisocand = 0 ; l1postisocand < treeVarsIsoNonIso.nbOfL1postCands ; l1postisocand++)  //loop on post-firing L1 iso candidates //FAN
           {
              if(treeVarsIsoNonIso.L1postRank[l1postisocand]>=2)
              {
                 if(treeVarsIsoNonIso.L1postRank[l1postisocand]>=eg)
                 {
                    //require EG2 by default, EG eg in general
                    occupancyL1post_temp->Fill(treeVarsIsoNonIso.L1postIeta[l1postisocand],treeVarsIsoNonIso.L1postIphi[l1postisocand]);
                    L1postCandRank_temp->Fill(treeVarsIsoNonIso.L1postRank[l1postisocand]);
                    L1timing_temp->Fill(1);
                    vector<int> tteta = getECALRegionEta(treeVarsIsoNonIso.L1postIeta[l1postisocand]);
                    vector<int> ttphi = getECALRegionPhi(treeVarsIsoNonIso.L1postIphi[l1postisocand]);
                    
                    if(abs(tteta[0])<17){//EB
                       L1timingEB_temp->Fill(1);
                    }
                    if(tteta[0]>=17){//EE+
                       L1timingEEPlus_temp->Fill(1);  
                    }
                    if(tteta[0]<=-17){//EE-
                       L1timingEEMinus_temp->Fill(1); 
                    }
                    
                    
                    for(uint i=0;i!=tteta.size();++i){
                       for(uint j=0;j!=ttphi.size();++j){ 
                          int l1posthash=0;
                          if (tteta[i]>0)
                             l1posthash= tteta[i] * 100 + ttphi[j] ;
                          else 
                             l1posthash = tteta[i] * 100 - ttphi[j] ;
                          
                          
                          if(abs(tteta[i])<18){//EB
                             occupancyL1postEB_temp->Fill(ttphi[j],tteta[i]);
                          }
                          if(tteta[i]>=18){//EE+
                             for (uint k=0; k !=geometry[l1posthash].size();++k){
                                occupancyL1postEEPlus_temp->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                             }
                          }
                          if(tteta[i]<=-18){//EE-
                             for (uint k=0; k !=geometry[l1posthash].size();++k){
                                occupancyL1postEEMinus_temp->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                             }
                          }
                       }
                    }
                 }
              }
           }
         } //end loop post L1 



      /*OLD part 
      //fill some post-firing L1 histograms
      //so here the stucture is almost the same as the pre-firing plots above. For iso and non-iso, for all and also seperately EB,EE+,EE-.
      nbOfL1postIsoCands->Fill(treeVars.nbOfL1postIsoCands);
      for (uint l1postisocand = 0 ; l1postisocand < treeVars.nbOfL1postIsoCands ; l1postisocand++)  //loop on post-firing L1 iso candidates //FAN
      {
         if(treeVars.L1postIsoRank[l1postisocand]>=2)
         {
            if(treeVars.L1postIsoRank[l1postisocand]>=eg)
            {
               //require EG2 by default, EG eg in general
               occupancyL1postIso->Fill(treeVars.L1postIsoIeta[l1postisocand],treeVars.L1postIsoIphi[l1postisocand]);
               L1postIsoCandRank->Fill(treeVars.L1postIsoRank[l1postisocand]);
               L1Isotiming->Fill(1);
               vector<int> tteta = getECALRegionEta(treeVars.L1postIsoIeta[l1postisocand]);
               vector<int> ttphi = getECALRegionPhi(treeVars.L1postIsoIphi[l1postisocand]);
               
               if(abs(tteta[0])<17){//EB
                  L1IsotimingEB->Fill(1);
               }
               if(tteta[0]>=17){//EE+
                  L1IsotimingEEPlus->Fill(1);  
               }
               if(tteta[0]<=-17){//EE-
                  L1IsotimingEEMinus->Fill(1); 
               }
               
               
               for(uint i=0;i!=tteta.size();++i){
                  for(uint j=0;j!=ttphi.size();++j){ 
                     int l1posthash=0;
                     if (tteta[i]>0)
                        l1posthash= tteta[i] * 100 + ttphi[j] ;
                     else 
                        l1posthash = tteta[i] * 100 - ttphi[j] ;
                     
                     
                     if(abs(tteta[i])<18){//EB
                        occupancyL1postIsoEB->Fill(ttphi[j],tteta[i]);
                     }
                     if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1posthash].size();++k){
                           occupancyL1postIsoEEPlus->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                        }
                     }
                     if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1posthash].size();++k){
                           occupancyL1postIsoEEMinus->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                        }
                     }
                  }
               }
            }
         }
      }
     
      //post-firing for non iso candidates. 
      nbOfL1postNonisoCands->Fill(treeVars.nbOfL1postNonisoCands);
      for (uint l1postnonisocand = 0 ; l1postnonisocand < treeVars.nbOfL1postNonisoCands ; l1postnonisocand++) //loop on post L1 noiso candidates //FAN
      {
         if(treeVars.L1postNonisoRank[l1postnonisocand]>=2)
         {
            if(treeVars.L1postNonisoRank[l1postnonisocand]>=eg)
            {
               //require EG2 by default, EG eg in general
               occupancyL1postNoniso->Fill(treeVars.L1postNonisoIeta[l1postnonisocand],treeVars.L1postNonisoIphi[l1postnonisocand]);
               L1postNonisoCandRank->Fill(treeVars.L1postNonisoRank[l1postnonisocand]);
               L1Nonisotiming->Fill(1);
               vector<int> tteta = getECALRegionEta(treeVars.L1postNonisoIeta[l1postnonisocand]);
               vector<int> ttphi = getECALRegionPhi(treeVars.L1postNonisoIphi[l1postnonisocand]);
               if(abs(tteta[0])<17){//EB
                  L1NonisotimingEB->Fill(1);
               }
               if(tteta[0]>=17){//EE+
                  L1NonisotimingEEPlus->Fill(1);  
               }
               if(tteta[0]<=-17){//EE-
                  L1NonisotimingEEMinus->Fill(1); 
               }
               for(uint i=0;i!=tteta.size();++i){
                  for(uint j=0;j!=ttphi.size();++j){ 
                     int l1posthash=0;
                     if (tteta[i]>0)
                        l1posthash= tteta[i] * 100 + ttphi[j] ;
                     else 
                        l1posthash = tteta[i] * 100 - ttphi[j] ;
                     
                     
                     if(abs(tteta[i])<18){//EB
                        occupancyL1postNonisoEB->Fill(ttphi[j],tteta[i]);
                     }
                     if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1posthash].size();++k){
                           occupancyL1postNonisoEEPlus->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                        }
                     }
                     if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1posthash].size();++k){
                           occupancyL1postNonisoEEMinus->Fill(geometry[l1posthash][k].first,geometry[l1posthash][k].second ) ;
                        }
                     }
                  }
               }
            }
         }
      }
      */  
   

 
      
      
      //counters for filling L1 histos after looping over all the towers
      int MaxTPinIsoRegion[4];
      int MaxTPinIsoRegionIeta[4];
      int MaxTPinIsoRegionIphi[4];
      int SecondTPinIsoRegion[4];
      
      int MaxTPinNonisoRegion[4];
      int MaxTPinNonisoRegionIeta[4];
      int MaxTPinNonisoRegionIphi[4];
      int SecondTPinNonisoRegion[4];
      
      //this can be changed FAN
      for(int i=0;i<4;++i)
      {
         MaxTPinIsoRegion[i]=0;
         MaxTPinIsoRegionIeta[i]=0;
         MaxTPinIsoRegionIphi[i]=0;
         SecondTPinIsoRegion[i]=0;
         
         MaxTPinNonisoRegion[i]=0;
         MaxTPinNonisoRegionIeta[i]=0;
         MaxTPinNonisoRegionIphi[i]=0;
         SecondTPinNonisoRegion[i]=0;
      }
 
       //FAN
      //MaxTPinIsoRegion[4]={0};
      //MaxTPinIsoRegionIeta[4]={0};
      //MaxTPinIsoRegionIphi[4]={0};
      //SecondTPinIsoRegion[4]={0};
      //MaxTPinNonisoRegion[4]={0};
      //MaxTPinNonisoRegionIeta[4]={0};
      //MaxTPinNonisoRegionIphi[4]={0};
      //SecondTPinNonisoRegion[4]={0};
      

      
      bool eventBool=false;
      // loop on towers
       for (uint tower = 0 ; tower < treeVars.nbOfTowers ; tower++)
      {
         
         //cout<<"event kept, in tower loop"<<endl;
         
         int tp = getEt(treeVars.rawTPData[tower]) ; //get the Et of each trigger tower. this is data.
         
         
         int emul[5] = {getEt(treeVars.rawTPEmul1[tower]),  //get the Et of each trigger tower, this is emulated. But we have 5 emulated value.
         getEt(treeVars.rawTPEmul2[tower]),
         getEt(treeVars.rawTPEmul3[tower]),
         getEt(treeVars.rawTPEmul4[tower]),
         getEt(treeVars.rawTPEmul5[tower])} ;
         
         //cout<<"event kept, TP&emul filled"<<endl;
         
         int maxOfTPEmul = 0 ;
         int indexOfTPEmulMax = -1 ;
         for (int i=0 ; i<5 ; i++) if (emul[i]>maxOfTPEmul) //loop on the 5 emulated value find the max one and its index
         {
            maxOfTPEmul = emul[i] ; 
            indexOfTPEmulMax = i ;
         }
         int ieta = treeVars.ieta[tower] ;//get TT ieta and iphi.
         int iphi = treeVars.iphi[tower] ;
         int hashedIndex =0 ;
         if (ieta >0)
            hashedIndex = ieta * 100 + iphi ;
         else 
            hashedIndex = ieta * 100 - iphi ;
         
         //apply hashedIndex filter
         //this will do if you ask some specific trigger towers to look by using the argument "towers". but normally not used.
            keep = false;
            if(towerIncludeVector.size()==0) keep = true;
            for(uint i=0; i!=towerIncludeVector.size();++i){
               if(hashedIndex==towerIncludeVector[i]) keep=true;
            }
            if(!keep) continue;
            keep = true;
            for(uint i=0; i!=towerExcludeVector.size();++i){
               if(hashedIndex==towerExcludeVector[i]) keep=false;
            }
            if(!keep) continue;
            
            
            //do comparison with L1 objects
            for (uint l1isocand = 0 ; l1isocand < treeVars.nbOfL1IsoCands ; l1isocand++) //loop on l1 iso candidates to find the max tp and put it in MaxTPinIsoRegion.
            {
               if(treeVars.L1IsoRank[l1isocand]>=eg) //select the one above "eg"
               {
                  //require EG1 by default, EG eg in general
                  if(treeVars.L1IsoIphi[l1isocand]==getGCTRegionPhi(iphi) && treeVars.L1IsoIeta[l1isocand]==getGCTRegionEta(ieta)) //if matched do after.
                  {
                     //geometric match
                     if(tp>= MaxTPinIsoRegion[l1isocand]) //put the max tp in the MaxTPinIsoRegion and also its ieat and iphi and tp value.
                     {//we have a new maximum
                     MaxTPinIsoRegion[l1isocand]=tp;
                     MaxTPinIsoRegionIeta[l1isocand]=ieta;
                     MaxTPinIsoRegionIphi[l1isocand]=iphi;
                  }
               }
            }
      }
      
      
      for (uint l1nonisocand = 0 ; l1nonisocand < treeVars.nbOfL1NonisoCands ; l1nonisocand++) //the same as above but on the noniso l1 candidates. also compute the max tp.
      {
         if(treeVars.L1NonisoRank[l1nonisocand]>=eg)
         {
            //require EG1 by default, EG eg in general
            if(treeVars.L1NonisoIphi[l1nonisocand]==getGCTRegionPhi(iphi) && treeVars.L1NonisoIeta[l1nonisocand]==getGCTRegionEta(ieta))
            {
               //geometric match
               if(tp>= MaxTPinNonisoRegion[l1nonisocand])
               {//we have a new maximum
               MaxTPinNonisoRegion[l1nonisocand]=tp;
               MaxTPinNonisoRegionIeta[l1nonisocand]=ieta;
               MaxTPinNonisoRegionIphi[l1nonisocand]=iphi;
               }
            }
         }
      }
     
     
 
      
      if (maxOfTPEmul>occupancyCut) TPEmulMax3D->Fill(iphi, ieta, indexOfTPEmulMax+1 ); //fill the histo only if the maxEmul above the occupancyCut, occupancyCut is the value you pass to the code through argument "th1".
      //if (maxOfTPEmul==0) TPEmulMax3D->Fill(iphi, ieta, -1 );
      
      
      uint nbXtals = treeVars.nbOfXtals[tower] ; //number of crystals.
      int ttf = getTtf(treeVars.rawTPData[tower]) ; // not too clear about this funtion.
      
      //some cout 
      if (verbose>9 && (tp>0 || maxOfTPEmul>0)) {
         cout<<"(phi,eta, Nbxtals)="<<dec<<iphi<<" "<<ieta<<" "<<nbXtals<<endl ;
         cout<<"Data Et, TTF: "<<tp<<" "<<ttf<<endl ;
         cout<<"Emulator: " ;
         for (int i=0 ; i<5 ; i++) cout<<emul[i]<<" " ;
         cout<<endl ;
      }
     
      //so if this trigger primitive above the occupancyCut,fill some histo. 
      if(tp>occupancyCut) {
         occupancyTP_vs_EvtNb->Fill(treeVars.evtNb/1000000.);
         time3D->Fill(iphi,ieta,treeVars.timeStamp/60. - slMinTime);
         TimeStamp->Fill(treeVars.timeStamp/60. - slMinTime); //time stamp
         LumiSection->Fill(treeVars.lumiBlock - slMinLS); //lumi
         LS3D->Fill(iphi,ieta,treeVars.lumiBlock - slMinLS);
         iEta_vs_LS->Fill(treeVars.lumiBlock - slMinLS, ieta);
         iPhi_vs_LS->Fill(treeVars.lumiBlock - slMinLS, iphi);
         iEta_vs_Time->Fill(treeVars.timeStamp/60. - slMinTime, ieta);
         iPhi_vs_Time->Fill(treeVars.timeStamp/60. - slMinTime, iphi);
      }
      
      
      // Fill TP in EB, EE+ and EE-
      if (abs(ieta)<18)
      {
         //barrel
         if (tp>occupancyCut) TPEB->Fill(tp) ;
         if (tp>occupancyCut) TPspectrumMap3DEB->Fill(iphi, ieta, tp) ;
         if (emul[ref]>occupancyCut) TPEmulEB->Fill(emul[ref]) ;
         if (maxOfTPEmul>occupancyCut) TPEmulMaxEB->Fill(maxOfTPEmul) ;
      }
      
      if (geometry.size()>0)
      {
         
         if (ieta>=18)
         {
            // EE+
            if (tp>occupancyCut) TPEEPlus->Fill(tp) ;
            if (emul[ref]>occupancyCut) TPEmulEEPlus->Fill(emul[ref]) ;
            if (maxOfTPEmul>occupancyCut) TPEmulMaxEEPlus->Fill(maxOfTPEmul) ;
            if (tp>occupancyCut)
            {
               for (uint i=0; i !=geometry[hashedIndex].size();++i)
                  TPspectrumMap3DEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,tp) ;
            }
         }
         
         if (ieta<=-18)
         {
            //EE-
            if (tp>occupancyCut) TPEEMinus->Fill(tp) ;
            if (emul[ref]>occupancyCut) TPEmulEEMinus->Fill(emul[ref]) ;
            if (maxOfTPEmul>occupancyCut) TPEmulMaxEEMinus->Fill(maxOfTPEmul) ;
            
            if (tp>occupancyCut){   
               for (uint i=0; i !=geometry[hashedIndex].size();++i)
                  TPspectrumMap3DEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,tp) ;
            }
         }
      }
      
      
      
      // Fill BX histo  TIMING OCCUPANCY HISTOs
      if (tp>occupancyCut) bx_Vs_TP->Fill(bxNb,tp) ;
      if (emul[ref]>occupancyCut) bx_Vs_TPEmul->Fill(bxNb,emul[ref]); // only reference Tp 
      if (tp>occupancyCut)  bx_Vs_Orbit->Fill(bxNb,float(orbitNb)/1000000.);  
         
      if (tp>occupancyCut)
      {
         for (uint ntrig = 0 ; ntrig < treeVars.nbOfActiveTriggers ; ntrig++)
         { 
            if (algobitsbx.size()>0) {
               for (uint algo = 0 ; algo<algobitsbx.size() ; algo++)
                  if (algobitsbx[algo] == treeVars.activeTriggers[ntrig]) bx_Vs_TriggerBit->Fill(bxNb,treeVars.activeTriggers[ntrig]) ;
            } else {
               bx_Vs_TriggerBit->Fill(bxNb,treeVars.activeTriggers[ntrig]) ; //2D pltos bunching crossing vs trigger bits.
            }
         }
         orbit ->Fill(float(orbitNb)/1000000.);
         bx ->Fill(bxNb);
      }
      
      
      // Fill the ieta and iphi for each trigger primitive,in EB, EE+ and EE-
      if (tp>occupancyCut && abs(ieta)<18) //only data
      {
         //barrel
         occupancyTPEB->Fill(iphi, ieta) ;
         
         TPEtaEB->Fill(ieta) ; 
         TPPhiEB->Fill(iphi) ;
      }
      if (emul[ref]>occupancyCut && abs(ieta)<18) occupancyTPEmulEB->Fill(iphi, ieta) ;  //barrel //take into account also the emulated
 

      if (geometry.size()>0)
      {
         if (ieta>=18 )
         {  
            //EE+
            if(tp>occupancyCut)
            {
               TPEtaEEPlus->Fill(ieta) ; 
               TPPhiEEPlus->Fill(iphi) ;
            }
            for (uint i=0; i !=geometry[hashedIndex].size();++i)
            {
               if (tp>occupancyCut)  occupancyTPEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;       
               occupancyTPEEPlusAll->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;  
               
               if ( maxOfTPEmul>occupancyCut)
                  occupancyTPEmulEEPlusALL->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
               if (emul[ref]>occupancyCut) 
                  occupancyTPEmulEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;        
            }
         }
         
         if (ieta<=-18 )
         {
            //EE-
            if(tp>occupancyCut)
            {
               TPEtaEEMinus->Fill(ieta) ; 
               TPPhiEEMinus->Fill(iphi) ;
            }
            for (uint i=0; i !=geometry[hashedIndex].size();++i)
            {
               if (tp>occupancyCut) occupancyTPEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
               occupancyTPEEMinusAll->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
               
               if ( maxOfTPEmul>occupancyCut)
                  occupancyTPEmulEEMinusALL->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;       
               if (emul[ref]>occupancyCut) 
                  occupancyTPEmulEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;       
            }
         }
      }
      
      
      // Fill Emulator-TP matching
      // as soon as emul[ref]>0 we look to the TP. No need to check nb of crystal readout, it's more timing oriented.
      if (emul[ref]>occupancyCut) {
         if (tp>occupancyCut) {
            if (abs(ieta)<=17) {
               TPTimingEBFromEmulOK->Fill(iphi, ieta) ;
               if (emul[ref] == tp) TPTimingEBFromEmulOKAndMatch->Fill(iphi, ieta) ;
            } else if (ieta<-17) {
               for (uint i=0; i !=geometry[hashedIndex].size();++i) {
                  TPTimingEEMinusFromEmulOK->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
                  if (emul[ref] == tp) TPTimingEEMinusFromEmulOKAndMatch->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
               }
            } else if (ieta>17) {
               for (uint i=0; i !=geometry[hashedIndex].size();++i) {
                  TPTimingEEPlusFromEmulOK->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
                  if (emul[ref] == tp) TPTimingEEPlusFromEmulOKAndMatch->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
               }     
            }
         }
         else {
            if (abs(ieta)<=17)
               TPTimingEBFromEmulWrong->Fill(iphi, ieta) ;
            else if (ieta<-17) {
               for (uint i=0; i !=geometry[hashedIndex].size();++i)
                  TPTimingEEMinusFromEmulWrong->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;      
            } else if (ieta>17) {
               for (uint i=0; i !=geometry[hashedIndex].size();++i)
                  TPTimingEEPlusFromEmulWrong->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;       
            }
         }
      }
      
      // Fill TP-Emulator matching
      // comparison is meaningful when:
      //also take into account the number of crystals  
      //for barrel
      if (tp>occupancyCut && abs(ieta)<=17) {
         if (nbXtals==25) {
            TPCompEmulEB->Fill(iphi, ieta);
            bool match(false) ;
            for (int i=0 ; i<5 ; i++) {
               if (tp == emul[i]) {
                  TPMatchEmulEB->Fill(i+1) ;
                  TPMatchEmul3D->Fill(iphi, ieta, i+1) ;
                  match = true ;
               }
            }
            if (!match) {
               TPMatchEmulEB->Fill(-1) ;
               TPMatchEmul3D->Fill(iphi, ieta, -1) ;
               if (verbose>5) {
                  cout<<"MISMATCH"<<endl ;
                  cout<<"(phi,eta, Nbxtals)="<<dec<<iphi<<" "<<ieta<<" "<<nbXtals<<endl ;
                  cout<<"Data Et, TTF: "<<tp<<" "<<ttf<<endl ;
                  cout<<"Emulator: " ;
                  for (int i=0 ; i<5 ; i++) cout<<emul[i]<<" " ;
                  cout<<endl ;
               }
            }
         }
         else {
            if (ttf==1 || ttf==3) {
               MaskedReadOutEB->Fill(iphi, ieta);
            }
         }
      }
      
      //for endcaps
      else if (tp>occupancyCut && ieta>=18) {
         if(nbXtals==geometry[hashedIndex].size() ) { //read from the EE geometry input file.
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               TPCompEmulEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
            }
            bool match(false) ;
            
            for (int i=0 ; i<5 ; i++) {
               
               if (tp == emul[i]) {
                  TPMatchEmulEEPlus->Fill(i+1) ;
                  TPMatchEmul3D->Fill(iphi, ieta, i+1) ;
                  match = true ;
               }
            }
            if (!match) {
               TPMatchEmulEEPlus->Fill(-1) ;
               TPMatchEmul3D->Fill(iphi, ieta, -1) ;
               if (verbose>5) {
                  cout<<"MISMATCH"<<endl ;
                  cout<<"(phi,eta, Nbxtals)="<<dec<<iphi<<" "<<ieta<<" "<<nbXtals<<endl ;
                  cout<<"Data Et, TTF: "<<tp<<" "<<ttf<<endl ;
                  cout<<"Emulator: " ;
                  for (int i=0 ; i<5 ; i++) cout<<emul[i]<<" " ;
                  cout<<endl ;
               }
            }
         }
         
         else {
            if (ttf==1 || ttf==3){
               for (uint i=0; i !=geometry[hashedIndex].size();++i)
                  MaskedReadOutEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
            }
         }
      }
      
      //EE-
      else if (tp>occupancyCut && ieta<=-18) {
         if (nbXtals==geometry[hashedIndex].size() ) {
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               TPCompEmulEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
            }
            
            bool match(false) ;
            for (int i=0 ; i<5 ; i++) {
               if (tp == emul[i]) {
                  TPMatchEmulEEMinus->Fill(i+1) ;
                  TPMatchEmul3D->Fill(iphi, ieta, i+1) ;
                  match = true ;
               }
            }
            if (!match) {
               TPMatchEmulEEMinus->Fill(-1) ;
               TPMatchEmul3D->Fill(iphi, ieta, -1) ;
               if (verbose>5) {
                  cout<<"MISMATCH"<<endl ;
                  cout<<"(phi,eta, Nbxtals)="<<dec<<iphi<<" "<<ieta<<" "<<nbXtals<<endl ;
                  cout<<"Data Et, TTF: "<<tp<<" "<<ttf<<endl ;
                  cout<<"Emulator: " ;
                  for (int i=0 ; i<5 ; i++) cout<<emul[i]<<" " ;
                               cout<<endl ;
               }
            }
         }
         
         else {
               if (ttf==1 || ttf==3) {
                  for (uint i=0; i !=geometry[hashedIndex].size();++i)
                     MaskedReadOutEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second) ;
               }
            }
            
         }
         
         if (maxOfTPEmul>occupancyCut) { //do if the max emulated value is above occupancyCut.
            
            if(ieta<=-18)      TPEmulMaxIndexEEMinus->Fill(indexOfTPEmulMax+1) ;
            else if(ieta<18)    TPEmulMaxIndexEB->Fill(indexOfTPEmulMax+1) ;
            else if(ieta>=18)   TPEmulMaxIndexEEPlus->Fill(indexOfTPEmulMax+1) ;
         }
         
         // Fill TTF mismatch
         // not too clear about this TTF
         if (abs(ieta)<=17 && (ttf==1 || ttf==3) && nbXtals != 25) ttfMismatchEB->Fill(iphi, ieta) ; //EB
         else if (ieta>=18 && (ttf==1 || ttf==3) && nbXtals != geometry[hashedIndex].size()) { //EE+
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               ttfMismatchEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
            }
         }
         else if (ieta<=-18 && (ttf==1 || ttf==3) && nbXtals != geometry[hashedIndex].size()) { //EE-
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               ttfMismatchEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second ) ;
            }
         }
         
         if(tp>occupancyCut) eventBool=true;
         
      } // end loop towers
      
      
      if(eventBool) eventNb->Fill(treeVars.evtNb/1000000.);
      
      
     //loop over towers again to find the highest energy neighbor of the MaxTPinIsoRegion
      //both for iso and noiso candidates. 
      for (uint tower = 0 ; tower < treeVars.nbOfTowers ; tower++)
      {
         int tp = getEt(treeVars.rawTPData[tower]) ;
         int TTieta = treeVars.ieta[tower] ;
         int TTiphi = treeVars.iphi[tower] ;
         
         for (uint l1isocand = 0 ; l1isocand < treeVars.nbOfL1IsoCands ; l1isocand++) {
            if(treeVars.L1IsoRank[l1isocand]>=eg) {
               //require EG1 by default, EG eg in general
               int L1ieta = MaxTPinIsoRegionIeta[l1isocand];
               int L1iphi = MaxTPinIsoRegionIphi[l1isocand];
               
               //find neighbor towers
               
               //special cases
               if(L1iphi==1 && TTiphi==72 && L1ieta==TTieta){  
                  if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
               }
               else if(L1iphi==72 && TTiphi==1 && L1ieta==TTieta){   
                  if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
               }
               else if(L1ieta==1 && TTieta==-1 && L1iphi==TTiphi){
                  if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
               }
               else if(L1ieta==-1 && TTieta==1 && L1iphi==TTiphi){
                  if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
               }
               //normal cases
               else if(L1ieta==TTieta && abs(L1iphi-TTiphi)==1){//towers left and right
                     if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
               }
               else if(L1iphi==TTiphi && abs(L1ieta-TTieta)==1){//towers above and below
                     if(tp>=SecondTPinIsoRegion[l1isocand]) SecondTPinIsoRegion[l1isocand]=tp;
               }  
            }
         }
         
         for (uint l1nonisocand = 0 ; l1nonisocand < treeVars.nbOfL1NonisoCands ; l1nonisocand++) {
            
            if(treeVars.L1NonisoRank[l1nonisocand]>=eg) {
               //require EG1 by default, EG eg in general
               int L1ieta = MaxTPinNonisoRegionIeta[l1nonisocand];
               int L1iphi = MaxTPinNonisoRegionIphi[l1nonisocand];
               
               //find neighbor towers
               
               //special cases
               if(L1iphi==1 && TTiphi==72 && L1ieta==TTieta){  
                  if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
               }
               else if(L1iphi==72 && TTiphi==1 && L1ieta==TTieta){   
                  if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
               }
               else if(L1ieta==1 && TTieta==-1 && L1iphi==TTiphi){
                  if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
               }
               else if(L1ieta==-1 && TTieta==1 && L1iphi==TTiphi){
                  if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
               }
               else if(L1ieta==TTieta && abs(L1iphi-TTiphi)==1){//towers left and right
                     if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
               }
               else if(L1iphi==TTiphi && abs(L1ieta-TTieta)==1){//towers above and below
                     if(tp>=SecondTPinNonisoRegion[l1nonisocand]) SecondTPinNonisoRegion[l1nonisocand]=tp;
               }  
            }
         }
      }
      
      
      //look MaxTPinIsoRegion to find the missing and mismatch one for iso candidates.
      for (uint l1isocand = 0 ; l1isocand < treeVars.nbOfL1IsoCands ; l1isocand++)
      {
      
         if(treeVars.L1IsoRank[l1isocand]>=eg)
         {
            //require EG1 by default, EG eg in general
            int twoTPSum = MaxTPinIsoRegion[l1isocand]+SecondTPinIsoRegion[l1isocand];
            float ratio= twoTPSum/float(treeVars.L1IsoRank[l1isocand]);
            float ratio2= float(treeVars.L1IsoRank[l1isocand])/float(2*int(twoTPSum/2));
            
            if(l1isocand==0) 
               L1Iso2TPSum->Fill(twoTPSum);
            
            L1IsoRatio->Fill(ratio);
            
            if(ratio==0) //missing case
            {
               //missing TP
               //cout << treeVars.evtNb << ",";
               L1MissingTPIso->Fill(treeVars.L1IsoIeta[l1isocand],treeVars.L1IsoIphi[l1isocand]);
               
               vector<int> tteta = getECALRegionEta(treeVars.L1IsoIeta[l1isocand]);
               vector<int> ttphi = getECALRegionPhi(treeVars.L1IsoIphi[l1isocand]);
               
               for(uint i=0;i!=tteta.size();++i)
               {
                  for(uint j=0;j!=ttphi.size();++j)
                  {
                     int l1hash=0;
                     
                     if (tteta[i]>0)
                        l1hash= tteta[i] * 100 + ttphi[j] ;
                     else 
                        l1hash = tteta[i] * 100 - ttphi[j] ;
                     
                     if(abs(tteta[i])<18){//EB
                        L1MissingTPIsoEB->Fill(ttphi[j],tteta[i]);
                     }
                     
                     if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1hash].size();++k){
                           L1MissingTPIsoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                        }
                     }
                     if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1hash].size();++k){
                           L1MissingTPIsoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                        }
                     }
                  }
               }
            }
         
            else{ //the good one,but not sure
               if(MaxTPinIsoRegion[l1isocand] != 255 && SecondTPinIsoRegion[l1isocand] != 255 && treeVars.L1IsoRank[l1isocand] != 63)
               {
                  vector<int> tteta = getECALRegionEta(treeVars.L1IsoIeta[l1isocand]);
                  vector<int> ttphi = getECALRegionPhi(treeVars.L1IsoIphi[l1isocand]);
                  
                  for(uint i=0;i!=tteta.size();++i){
                     for(uint j=0;j!=ttphi.size();++j){
                        
                        int l1hash=0;
                        if (tteta[i]>0)
                           l1hash= tteta[i] * 100 + ttphi[j] ;
                        else 
                           l1hash = tteta[i] * 100 - ttphi[j] ;
                        
                        if(abs(tteta[i])<18){//EB
                              L1RatioTPIso3DEB->Fill(ttphi[j],tteta[i], ratio2);
                              L1TPCompIsoEB->Fill(ttphi[j],tteta[i]);
                        }
                        if(tteta[i]>=18){//EE+
                              for (uint k=0; k !=geometry[l1hash].size();++k){
                                 L1RatioTPIso3DEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second, ratio2 ) ;
                                 L1TPCompIsoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second );
                              }
                        }
                        if(tteta[i]<=-18){//EE-
                              for (uint k=0; k !=geometry[l1hash].size();++k){
                                 L1RatioTPIso3DEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second, ratio2 ) ;
                                 L1TPCompIsoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second );
                              }
                        }
                        
                     }
                  }
               }
            }
             
            //find the mismatch 
            if(ratio>4.1 || ratio<2.)
            {
               //value mismatch
               L1ValueMismatchIso->Fill(treeVars.L1IsoIeta[l1isocand],treeVars.L1IsoIphi[l1isocand]);
               
               vector<int> tteta = getECALRegionEta(treeVars.L1IsoIeta[l1isocand]);
               vector<int> ttphi = getECALRegionPhi(treeVars.L1IsoIphi[l1isocand]);
               
               for(uint i=0;i!=tteta.size();++i){
                  for(uint j=0;j!=ttphi.size();++j){
                     
                     int l1hash=0;
                     if (tteta[i]>0)
                        l1hash= tteta[i] * 100 + ttphi[j] ;
                     else 
                        l1hash = tteta[i] * 100 - ttphi[j] ;
                     
                     if(abs(tteta[i])<18){//EB
                        L1ValueMismatchIsoEB->Fill(ttphi[j],tteta[i]);
                     }
                     if(tteta[i]>=18){//EE+
                        for (uint k=0; k !=geometry[l1hash].size();++k){
                           L1ValueMismatchIsoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                        }
                     }
                     if(tteta[i]<=-18){//EE-
                        for (uint k=0; k !=geometry[l1hash].size();++k){
                           L1ValueMismatchIsoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                        }
                     }
                  }
               }
            }
         }
      }
   
   
      //the same as above but for noniso candidates.almost the same structure.
      for (uint l1nonisocand = 0 ; l1nonisocand < treeVars.nbOfL1NonisoCands ; l1nonisocand++)
      {
         
         if(treeVars.L1NonisoRank[l1nonisocand]>=eg)
         {
            //require EG1 by default, EG eg in general
            float twoTPSum = float(MaxTPinNonisoRegion[l1nonisocand]+SecondTPinNonisoRegion[l1nonisocand]);
            float ratio= float(MaxTPinNonisoRegion[l1nonisocand]+SecondTPinNonisoRegion[l1nonisocand])/float(treeVars.L1NonisoRank[l1nonisocand]);
            float ratio2= float(treeVars.L1NonisoRank[l1nonisocand])/float(2*int(twoTPSum/2));
            L1NonisoRatio->Fill(ratio);
            
            L1Noniso2TPSum->Fill(twoTPSum);
            
            if(ratio==0)
            {
               
               L1MissingTPNoniso->Fill(treeVars.L1NonisoIeta[l1nonisocand],treeVars.L1NonisoIphi[l1nonisocand]);
               
               vector<int> tteta = getECALRegionEta(treeVars.L1NonisoIeta[l1nonisocand]);
               vector<int> ttphi = getECALRegionPhi(treeVars.L1NonisoIphi[l1nonisocand]);
               
               for(uint i=0;i!=tteta.size();++i){
                  for(uint j=0;j!=ttphi.size();++j){
                     
                     int l1hash=0;
                     if (tteta[i]>0)
                        l1hash= tteta[i] * 100 + ttphi[j] ;
                     else 
                        l1hash = tteta[i] * 100 - ttphi[j] ;
                     
                     if(abs(tteta[i])<18){//EB
                           L1MissingTPNonisoEB->Fill(ttphi[j],tteta[i]);
                     }
                     if(tteta[i]>=18){//EE+
                           for (uint k=0; k !=geometry[l1hash].size();++k){
                              L1MissingTPNonisoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                           }
                     }
                     if(tteta[i]<=-18){//EE-
                           for (uint k=0; k !=geometry[l1hash].size();++k){
                              L1MissingTPNonisoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                           }
                     }
                  }
               }
            }
            
            else
            {
               if(MaxTPinNonisoRegion[l1nonisocand] != 255 && SecondTPinNonisoRegion[l1nonisocand] != 255 && treeVars.L1NonisoRank[l1nonisocand] != 63)
               {
                  
                  vector<int> tteta = getECALRegionEta(treeVars.L1NonisoIeta[l1nonisocand]);
                  vector<int> ttphi = getECALRegionPhi(treeVars.L1NonisoIphi[l1nonisocand]);
                  
                  for(uint i=0;i!=tteta.size();++i){
                     for(uint j=0;j!=ttphi.size();++j){
                        
                        int l1hash=0;
                        if (tteta[i]>0)
                           l1hash= tteta[i] * 100 + ttphi[j] ;
                        else 
                           l1hash = tteta[i] * 100 - ttphi[j] ;
                        
                        if(abs(tteta[i])<18){//EB
                              L1RatioTPNoniso3DEB->Fill(ttphi[j],tteta[i], ratio2);
                              L1TPCompNonisoEB->Fill(ttphi[j],tteta[i]);
                        }
                        if(tteta[i]>=18){//EE+
                              for (uint k=0; k !=geometry[l1hash].size();++k){
                                 L1RatioTPNoniso3DEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second, ratio2 ) ;
                                 L1TPCompNonisoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second );
                              }
                        }
                        if(tteta[i]<=-18){//EE-
                              for (uint k=0; k !=geometry[l1hash].size();++k){
                                 L1RatioTPNoniso3DEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second, ratio2 ) ;
                                 L1TPCompNonisoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second );
                              }
                        }
                     }
                  }
               }
            }
            
            if(ratio>4.1 || ratio<2.){
               
               L1ValueMismatchNoniso->Fill(treeVars.L1NonisoIeta[l1nonisocand],treeVars.L1NonisoIphi[l1nonisocand]);
               
               vector<int> tteta = getECALRegionEta(treeVars.L1NonisoIeta[l1nonisocand]);
               vector<int> ttphi = getECALRegionPhi(treeVars.L1NonisoIphi[l1nonisocand]);
               
               for(uint i=0;i!=tteta.size();++i){
                  for(uint j=0;j!=ttphi.size();++j){   
                     
                     int l1hash=0;
                     if (tteta[i]>0)
                        l1hash= tteta[i] * 100 + ttphi[j] ;
                     else 
                        l1hash = tteta[i] * 100 - ttphi[j] ;
                     
                     if(abs(tteta[i])<18){//EB
                           L1ValueMismatchNonisoEB->Fill(ttphi[j],tteta[i]);
                     }
                     if(tteta[i]>=18){//EE+
                           for (uint k=0; k !=geometry[l1hash].size();++k){
                              L1ValueMismatchNonisoEEPlus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                           }
                     }
                     if(tteta[i]<=-18){//EE-
                           for (uint k=0; k !=geometry[l1hash].size();++k){
                              L1ValueMismatchNonisoEEMinus->Fill(geometry[l1hash][k].first,geometry[l1hash][k].second ) ;
                           }
                     }
                  }
               }
            }
         }
      }
   
   } // endloop entries




   cout<<"\nMax. event number: "<<maxEvNb<<endl;
  
   //creating some fraction plots using Divide. 
   L1FractionMissingTPIsoEB->Divide(L1MissingTPIsoEB, occupancyL1IsoEB);
   L1FractionMissingTPIsoEEPlus->Divide(L1MissingTPIsoEEPlus, occupancyL1IsoEEPlus);
   L1FractionMissingTPIsoEEMinus->Divide(L1MissingTPIsoEEMinus, occupancyL1IsoEEMinus);
   
   L1FractionMissingTPNonisoEB->Divide(L1MissingTPNonisoEB, occupancyL1NonisoEB);
   L1FractionMissingTPNonisoEEPlus->Divide(L1MissingTPNonisoEEPlus, occupancyL1NonisoEEPlus);
   L1FractionMissingTPNonisoEEMinus->Divide(L1MissingTPNonisoEEMinus, occupancyL1NonisoEEMinus);
   
   
   
   ///////////////////////
   // Format & write histos
   ///////////////////////
   
    //below is to write histo,mostly is root stuff. 
   // 1. TP Spectrum  
   TProfile2D * TPspectrumMapEB = TPspectrumMap3DEB->Project3DProfile("yx") ;
   TPspectrumMapEB->SetName("TPspectrumMapEB") ;
   TPspectrumMapEB->GetYaxis()->SetTitle("eta index") ; 
   TPspectrumMapEB->GetXaxis()->SetTitle("phi index") ;
   TProfile2D * TPspectrumMapEEPlus = TPspectrumMap3DEEPlus->Project3DProfile("yx") ;
   TPspectrumMapEEPlus->SetName("TPspectrumMapEEPlus") ;
   TPspectrumMapEEPlus->GetYaxis()->SetTitle("y index") ; 
   TPspectrumMapEEPlus->GetXaxis()->SetTitle("x index") ;
   TProfile2D * TPspectrumMapEEMinus = TPspectrumMap3DEEMinus->Project3DProfile("yx") ;
   TPspectrumMapEEMinus->SetName("TPspectrumMapEEMinus") ;
   TPspectrumMapEEMinus->GetYaxis()->SetTitle("y index") ; 
   TPspectrumMapEEMinus->GetXaxis()->SetTitle("x index") ;
   
   // 2. TP Timing
   TH2F * TPMatchEmulEB2D = new TH2F("TPMatchEmulEB2D", "TP data matching Emulator: Barrel", 72, 1, 73, 38, -19, 19) ;
   TPMatchEmulEB2D->GetYaxis()->SetTitle("eta index") ; 
   TPMatchEmulEB2D->GetXaxis()->SetTitle("phi index") ;
   TPMatchEmulEB2D->GetZaxis()->SetRangeUser(-2,6) ;
   TH2F * TPMatchEmulEEPlus2D = new TH2F("TPMatchEmulEEPlus2D", "TP data matching Emulator: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPMatchEmulEEPlus2D->GetYaxis()->SetTitle("y index") ; 
   TPMatchEmulEEPlus2D->GetXaxis()->SetTitle("x index") ;
   TPMatchEmulEEPlus2D->GetZaxis()->SetRangeUser(-2,6) ;
   TH2F * TPMatchEmulEEMinus2D = new TH2F("TPMatchEmulEEMinus2D", "TP data matching Emulator: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPMatchEmulEEMinus2D->GetYaxis()->SetTitle("y index") ; 
   TPMatchEmulEEMinus2D->GetXaxis()->SetTitle("x index") ;
   TPMatchEmulEEMinus2D->GetZaxis()->SetRangeUser(-2,6) ;
   TH2F * TPMatchFractionEB2D = new TH2F("TPMatchFractionEB2D", "TP data: fraction of non-single timing: Barrel", 72, 1, 73, 38, -19, 19) ;
   TPMatchFractionEB2D->GetYaxis()->SetTitle("eta index") ; 
   TPMatchFractionEB2D->GetXaxis()->SetTitle("phi index") ;
   TH2F * TPMatchFractionEEPlus2D = new TH2F("TPMatchFractionEEPlus2D", "TP data: fraction of non-single timing: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPMatchFractionEEPlus2D->GetYaxis()->SetTitle("y index") ; 
   TPMatchFractionEEPlus2D->GetXaxis()->SetTitle("x index") ;
   TH2F * TPMatchFractionEEMinus2D = new TH2F("TPMatchFractionEEMinus2D", "TP data: fraction of non-single timing: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPMatchFractionEEMinus2D->GetYaxis()->SetTitle("y index") ; 
   TPMatchFractionEEMinus2D->GetXaxis()->SetTitle("x index") ;
   
   TH2F * TPMatchFraction2EB2D = new TH2F("TPMatchFraction2EB2D", "TP data: fraction of matching to another BX: Barrel", 72, 1, 73, 38, -19, 19) ;
   TPMatchFraction2EB2D->GetYaxis()->SetTitle("eta index") ; 
   TPMatchFraction2EB2D->GetXaxis()->SetTitle("phi index") ;
   TH2F * TPMatchFraction2EEPlus2D = new TH2F("TPMatchFraction2EEPlus2D", "TP data: fraction of matching to another BX: Plus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPMatchFraction2EEPlus2D->GetYaxis()->SetTitle("y index") ; 
   TPMatchFraction2EEPlus2D->GetXaxis()->SetTitle("x index") ;
   TH2F * TPMatchFraction2EEMinus2D = new TH2F("TPMatchFraction2EEMinus2D", "TP data: fraction of matching to another BX: Minus Endcap", 121, -10, 111, 121, -10, 111) ;
   TPMatchFraction2EEMinus2D->GetYaxis()->SetTitle("y index") ; 
   TPMatchFraction2EEMinus2D->GetXaxis()->SetTitle("x index") ;
   
   //loop on TPEmulMax3D points to find max value and index.and fill them in the EB, EE+ and EE- seperatly. 
   for (int binx=1 ; binx<=72 ; binx++) {  //looping over iphi
      for (int biny=1 ; biny<=57 ; biny++) { //looping over ieta

         int maxBinEmulz = -1 ;
         double maxEmulCell = TPEmulMax3D->GetBinContent(binx, biny, maxBinEmulz) ;
         double totalEmulCell(0) ;
         for (int binz=1; binz<=7 ; binz++) {
            double content = TPEmulMax3D->GetBinContent(binx, biny, binz) ;
            if (content>maxEmulCell) {
               maxEmulCell = content ;
               maxBinEmulz = binz ;
            }
            totalEmulCell += content ;
         }
         
         int maxBinz = 5 ;
         double maxCell = TPMatchEmul3D->GetBinContent(binx, biny, maxBinz) ;
         double totalCell(0) ;
         double totalCell2(0) ;
         
         for (int binz=1; binz<=7 ; binz++) {
            double content = TPMatchEmul3D->GetBinContent(binx, biny, binz) ;
            
            if (content>maxCell) {
               maxCell = content ;
               maxBinz = binz ;
            }
            totalCell += content ;
            if(binz>1) {
               totalCell2 += content ;
            }
         }
         if (maxCell <=0) maxBinz = 2 ; // empty cell

         if(biny<=11){ //minus endcap (ieta <=-18)
            int hashedIndex = (biny-29) * 100 - binx ;
            
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               TPMatchEmulEEMinus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,float(maxBinz)-2. ) ;
               TPEmulMapMaxIndexEEMinus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,float(maxBinEmulz)-2 ) ;
            }
            
            double fraction = 0 ;
            if (totalCell>0) fraction = 1.- maxCell/totalCell ;
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               TPMatchFractionEEMinus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,fraction ) ;         
            }
            
            double fraction2 = 0 ;
            if (maxBinz != 1 && totalCell2>0) fraction2 = 1.- maxCell/totalCell2 ;
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               TPMatchFraction2EEMinus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,fraction2 ) ;       
            }
         }
         
         else if(biny<=46 && biny!=29)
         { 
            //barrel (excluding ieta=0)
            
            TPMatchEmulEB2D->SetBinContent(binx, biny-9, float(maxBinz)-2.) ; //z must be in [-1,5] 
            TPEmulMapMaxIndexEB->SetBinContent(binx, biny-9,float(maxBinEmulz)-2 ) ;
            
            double fraction = 0 ;
            if (totalCell>0) fraction = 1.- maxCell/totalCell ;
            TPMatchFractionEB2D->SetBinContent(binx, biny-9, fraction) ;
            
            double fraction2 = 0 ;
            if (maxBinz != 1 && totalCell2>0) fraction2 = 1.- maxCell/totalCell2 ;
            TPMatchFraction2EB2D->SetBinContent(binx, biny-9, fraction2 ) ;         
         }
         
         else if(biny>=47)
         { 
            //plus endcap (ieta >=18)
            int hashedIndex = (biny-29) * 100 + binx ;
            
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               TPMatchEmulEEPlus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,float(maxBinz)-2. ) ;
               TPEmulMapMaxIndexEEPlus->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,float(maxBinEmulz)-2 ) ;
            }
            
            double fraction = 0 ;
            if (totalCell>0) fraction = 1.- maxCell/totalCell ;
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               TPMatchFractionEEPlus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,fraction ) ;       
            }
            
            double fraction2 = 0 ;
            if (maxBinz != 1 && totalCell2>0) fraction2 = 1.- maxCell/totalCell2 ;
            for (uint i=0; i !=geometry[hashedIndex].size();++i) {
               TPMatchFraction2EEPlus2D->Fill(geometry[hashedIndex][i].first,geometry[hashedIndex][i].second,fraction2 ) ;        
            }
         }
         
         
      }//end loop over ieta
      
   }//end loop over iphi
   
   
   //3. L1/TP ratio
   
   TProfile2D * L1RatioTPIsoEB = L1RatioTPIso3DEB->Project3DProfile("yx") ;
   L1RatioTPIsoEB->SetName("L1RatioTPIsoEB") ;
   L1RatioTPIsoEB->GetYaxis()->SetTitle("eta index") ; 
   L1RatioTPIsoEB->GetXaxis()->SetTitle("phi index") ;
   TProfile2D * L1RatioTPIsoEEPlus = L1RatioTPIso3DEEPlus->Project3DProfile("yx") ;
   L1RatioTPIsoEEPlus->SetName("L1RatioTPIsoEEPlus") ;
   L1RatioTPIsoEEPlus->GetYaxis()->SetTitle("y index") ; 
   L1RatioTPIsoEEPlus->GetXaxis()->SetTitle("x index") ;
   TProfile2D * L1RatioTPIsoEEMinus = L1RatioTPIso3DEEMinus->Project3DProfile("yx") ;
   L1RatioTPIsoEEMinus->SetName("L1RatioTPIsoEEMinus") ;
   L1RatioTPIsoEEMinus->GetYaxis()->SetTitle("y index") ; 
   L1RatioTPIsoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   TProfile2D * L1RatioTPNonisoEB = L1RatioTPNoniso3DEB->Project3DProfile("yx") ;
   L1RatioTPNonisoEB->SetName("L1RatioTPNonisoEB") ;
   L1RatioTPNonisoEB->GetYaxis()->SetTitle("eta index") ; 
   L1RatioTPNonisoEB->GetXaxis()->SetTitle("phi index") ;
   TProfile2D * L1RatioTPNonisoEEPlus = L1RatioTPNoniso3DEEPlus->Project3DProfile("yx") ;
   L1RatioTPNonisoEEPlus->SetName("L1RatioTPNonisoEEPlus") ;
   L1RatioTPNonisoEEPlus->GetYaxis()->SetTitle("y index") ; 
   L1RatioTPNonisoEEPlus->GetXaxis()->SetTitle("x index") ;
   TProfile2D * L1RatioTPNonisoEEMinus = L1RatioTPNoniso3DEEMinus->Project3DProfile("yx") ;
   L1RatioTPNonisoEEMinus->SetName("L1RatioTPNonisoEEMinus") ;
   L1RatioTPNonisoEEMinus->GetYaxis()->SetTitle("y index") ; 
   L1RatioTPNonisoEEMinus->GetXaxis()->SetTitle("x index") ;
   
   
   TFile saving (outputRootName.c_str (),"recreate") ;
   saving.cd () ;
   
   
  
   //write all the histo to the output root files. 
   TPEtaEB->Write() ;
   TPPhiEB->Write() ;
   TPEtaEEPlus->Write() ;
   TPPhiEEPlus->Write() ;
   TPEtaEEMinus->Write() ;
   TPPhiEEMinus->Write() ;
   
   occupancyTPEB->Write() ;
   occupancyTPEEPlus->Write() ;
   occupancyTPEEMinus->Write() ;
   occupancyTPEEPlusAll->Write() ;
   occupancyTPEEMinusAll->Write() ;
   
   occupancyTPEmulEB->Write() ;
   occupancyTPEmulEEPlus->Write() ;
   occupancyTPEmulEEPlusALL->Write() ;
   occupancyTPEmulEEMinus->Write() ;
   occupancyTPEmulEEMinusALL->Write() ;
   
   FiredTriggers->Write() ;
   
   TPEB->Write() ;
   TPEEPlus->Write() ;
   TPEEMinus->Write() ;
   TPEmulEB->Write() ;
   TPEmulEEPlus->Write() ;
   TPEmulEEMinus->Write() ;
   TPEmulMaxEB->Write() ;
   TPEmulMaxEEPlus->Write() ;
   TPEmulMaxEEMinus->Write() ;
   TPspectrumMapEB->Write() ;
   TPspectrumMap3DEB->Write() ;
   TPspectrumMapEEPlus->Write() ;
   TPspectrumMap3DEEPlus->Write() ;
   TPspectrumMapEEMinus->Write() ;
   TPspectrumMap3DEEMinus->Write() ;
   
   //L1RatioTPIso
   
   L1RatioTPIsoEB->Write() ;
   L1RatioTPIso3DEB->Write() ;
   L1RatioTPIsoEEPlus->Write() ;
   L1RatioTPIso3DEEPlus->Write() ;
   L1RatioTPIsoEEMinus->Write() ;
   L1RatioTPIso3DEEMinus->Write() ;
   
   L1RatioTPNonisoEB->Write() ;
   L1RatioTPNoniso3DEB->Write() ;
   L1RatioTPNonisoEEPlus->Write() ;
   L1RatioTPNoniso3DEEPlus->Write() ;
   L1RatioTPNonisoEEMinus->Write() ;
   L1RatioTPNoniso3DEEMinus->Write() ;
   
   L1TPCompIsoEB->Write() ;
   L1TPCompNonisoEB->Write() ;
   L1TPCompIsoEEPlus->Write() ;
   L1TPCompNonisoEEPlus->Write() ;
   L1TPCompIsoEEMinus->Write() ;
   L1TPCompNonisoEEMinus->Write() ;
   
   bx_Vs_TPEmul->Write() ;
   bx_Vs_Orbit->Write() ;
   bx_Vs_TP->Write() ;
   bx_Vs_TriggerBit->Write() ;
   bx ->Write();
   occupancyTP_vs_EvtNb->Write();
   iEta_vs_LS->Write();
   iPhi_vs_LS->Write();
   iEta_vs_Time->Write();
   iPhi_vs_Time->Write();
   orbit->Write();
   eventNb->Write();
   LumiSection->Write();
   TimeStamp->Write();
   LS3D->Write();
   time3D->Write();
   triggerBit->Write();
   
   
   TPMatchEmulEB->Write() ; 
   TPMatchEmulEEPlus->Write() ; 
   TPMatchEmulEEMinus->Write() ; 
   TPMatchEmul3D->Write() ; 
   TPEmulMaxIndexEB->Write() ;
   TPEmulMaxIndexEEPlus->Write() ;
   TPEmulMaxIndexEEMinus->Write() ;
   
   TPCompEmulEB->Write() ; 
   TPCompEmulEEPlus->Write() ; 
   TPCompEmulEEMinus->Write() ;
   
   TPMatchEmulEB2D->Write() ;
   TPMatchEmulEEPlus2D->Write() ;
   TPMatchEmulEEMinus2D->Write() ;
   
   TPMatchFractionEB2D->Write() ;
   TPMatchFractionEEPlus2D->Write() ; 
   TPMatchFractionEEMinus2D->Write() ; 
   
   TPMatchFraction2EB2D->Write() ;
   TPMatchFraction2EEPlus2D->Write() ; 
   TPMatchFraction2EEMinus2D->Write() ; 
   
   ttfMismatchEB->Write() ; 
   ttfMismatchEEPlus->Write() ; 
   ttfMismatchEEMinus->Write() ; 
   
   TPEmulMapMaxIndexEEPlus->Write() ; 
   TPEmulMapMaxIndexEEMinus->Write() ; 
   TPEmulMapMaxIndexEB->Write() ;
   TPEmulMax3D->Write() ;
   
   TPTimingEBFromEmulOK->Write() ; 
   TPTimingEBFromEmulOKAndMatch->Write() ; 
   TPTimingEBFromEmulWrong->Write() ; 
   TPTimingEEMinusFromEmulOK->Write() ; 
   TPTimingEEMinusFromEmulOKAndMatch->Write() ; 
   TPTimingEEMinusFromEmulWrong->Write() ; 
   TPTimingEEPlusFromEmulOK->Write() ; 
   TPTimingEEPlusFromEmulOKAndMatch->Write() ; 
   TPTimingEEPlusFromEmulWrong->Write() ; 
   
   occupancyL1Iso->Write();
   occupancyL1Noniso->Write();
   occupancyL1IsoEB->Write();
   occupancyL1NonisoEB->Write();
   occupancyL1IsoEEPlus->Write();
   occupancyL1IsoEEMinus->Write();
   occupancyL1NonisoEEPlus->Write();
   occupancyL1NonisoEEMinus->Write();
   
   occupancyL1preIso->Write();
   occupancyL1preNoniso->Write();
   occupancyL1preIsoEB->Write();
   occupancyL1preNonisoEB->Write();
   occupancyL1preIsoEEPlus->Write();
   occupancyL1preIsoEEMinus->Write();
   occupancyL1preNonisoEEPlus->Write();
   occupancyL1preNonisoEEMinus->Write();
   
   occupancyL1postIso->Write();
   occupancyL1postNoniso->Write();
   occupancyL1postIsoEB->Write();
   occupancyL1postNonisoEB->Write();
   occupancyL1postIsoEEPlus->Write();
   occupancyL1postIsoEEMinus->Write();
   occupancyL1postNonisoEEPlus->Write();
   occupancyL1postNonisoEEMinus->Write();
   
   nbOfL1IsoCands->Write();
   nbOfL1NonisoCands->Write();
   L1IsoCandRank->Write();
   L1NonisoCandRank->Write();
   
   nbOfL1preIsoCands->Write();
   nbOfL1preNonisoCands->Write();
   L1preIsoCandRank->Write();
   L1preNonisoCandRank->Write();
   
   nbOfL1postIsoCands->Write();
   nbOfL1postNonisoCands->Write();
   L1postIsoCandRank->Write();
   L1postNonisoCandRank->Write();
   
   L1Isotiming->Write();
   L1Nonisotiming->Write();
   L1IsotimingEB->Write();
   L1NonisotimingEB->Write();
   L1IsotimingEEPlus->Write();
   L1NonisotimingEEPlus->Write();
   L1IsotimingEEMinus->Write();
   L1NonisotimingEEMinus->Write();
   
   L1IsoRatio->Write();
   L1NonisoRatio->Write();
   
   L1MissingTPIso->Write();
   L1MissingTPNoniso->Write();
   L1MissingTPIsoEB->Write();
   L1MissingTPNonisoEB->Write();
   L1MissingTPIsoEEPlus->Write();
   L1MissingTPIsoEEMinus->Write();
   L1MissingTPNonisoEEPlus->Write();
   L1MissingTPNonisoEEMinus->Write();
   
   L1FractionMissingTPIsoEB->Write();
   L1FractionMissingTPIsoEEPlus->Write();
   L1FractionMissingTPIsoEEMinus->Write();
   
   L1FractionMissingTPNonisoEB->Write();
   L1FractionMissingTPNonisoEEPlus->Write();
   L1FractionMissingTPNonisoEEMinus->Write();
   
   L1ValueMismatchIso->Write();
   L1ValueMismatchNoniso->Write();
   L1ValueMismatchIsoEB->Write();
   L1ValueMismatchNonisoEB->Write();
   L1ValueMismatchIsoEEPlus->Write();
   L1ValueMismatchIsoEEMinus->Write();
   L1ValueMismatchNonisoEEPlus->Write();
   L1ValueMismatchNonisoEEMinus->Write();
   
   L1Iso2TPSum->Write();
   L1Noniso2TPSum->Write();
   
   maskedRCT->Write();
   maskedRCTEB->Write();
   maskedRCTEEPlus->Write();
   maskedRCTEEMinus->Write();
   
   MaskedTowersEB->Write();
   MaskedTowersEEPlus->Write();
   MaskedTowersEEMinus->Write();
   
   MaskedReadOutEB->Write();
   MaskedReadOutEEPlus->Write();
   MaskedReadOutEEMinus->Write();
   
   bx_bit45_all->Write() ;
   bx_bit46_all->Write() ;
   bx_nTT->Write() ;
   
   l1EGAlgos->Write() ;
   l1EGAlgos2D->Write() ;
   
   techTrigCor->Write() ;
   techTrigCor2D->Write() ;
   histoEgTrigTechTrigCor->Write() ;
   
   saving.Close () ;
   delete chain ;
   
   return 0 ;
   
}



