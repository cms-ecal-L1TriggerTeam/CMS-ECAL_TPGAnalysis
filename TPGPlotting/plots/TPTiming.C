void TPTiming ()
{
  TAxis * ax = TPMatchEmul2D->GetZaxis() ;
  ax->SetRangeUser(-1,6) ;

  TCanvas* canv = new TCanvas("canv", "canv") ;
  canv->SetLogz(0) ;
  gStyle->SetOptStat(10) ;
  int color[10]={1,10,3,4,5,6,7,8,9,2} ;
  gStyle->SetPalette(7, color) ;
  TPMatchEmul2D->GetXaxis()->SetTitle("Phi index");
  TPMatchEmul2D->GetYaxis()->SetTitle("Eta index");
  TPMatchEmul2D->Draw("colz") ;
  
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
  label->Draw("same text") ; 
  
  TLatex txt;
  txt.SetTextSize(0.02);
  TLine line;
  line.SetLineColor(1) ;
  line.SetLineStyle(1) ;
  line.SetLineWidth(1) ;
  TAxis* xAxis = TPMatchEmul2D->GetXaxis();
  TAxis* yAxis = TPMatchEmul2D->GetYaxis();

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
  
}

