#include "custom_can_macro.C"

void Approval_plots_2015Nov26() {
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TFile *f; TCanvas *c; TArrow *arr; TGaxis* axis; TGraphAsymmErrors* g;
  
  bool save = 1;
  std::string save_dir = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2015_Nov/Approved/";
  std::vector<std::string> formats = { ".png", ".eps", ".root", ".C", ".pdf" };
  
  f = TFile::Open("Janos_PHM/PHM_out/Approval_2015_November.root");
  
  // -------------------------------------------------------------
  //              HitEfficiency vs Layers/Disks
  
  TH1D *eff = (TH1D*)f->Get("HitEfficiency_vs_LayersDisks/data");
  
  eff->SetTitle("");
  c = custom_can_(eff, "HitEfficiency_vs_LayerDisks", 0,1, 500,500, 100,20, 45,60, 33, 0.99,0.99);
  eff->GetYaxis()->SetRangeUser(0.98,1);
  eff->GetYaxis()->SetNdivisions(505);
  eff->GetXaxis()->SetBinLabel(1, "Layer 1");
  eff->GetXaxis()->SetBinLabel(2, "Layer 2");
  eff->GetXaxis()->SetBinLabel(3, "Layer 3");
  eff->GetXaxis()->SetBinLabel(4, "Disk -2");
  eff->GetXaxis()->SetBinLabel(5, "Disk -1");
  eff->GetXaxis()->SetBinLabel(6, "Disk +1");
  eff->GetXaxis()->SetBinLabel(7, "Disk +2");
  eff->SetMarkerColor(1);
  eff->GetXaxis()->SetLabelSize(0.05);
  //eff->Draw("PE1X0");
  g = asym_(eff);
  for (int i=0; i<7; ++i) {
    double err_high = (eff->GetBinContent(i+1)+0.003)>1 ? 1-eff->GetBinContent(i+1) : 0.003;
    g->SetPointEYhigh(i,err_high); g->SetPointEYlow (i,0.003);
  }
  g->Draw("AP");
  g->GetYaxis()->SetLabelFont(42);
  asym_labels_(eff, g, 0);
  prelim_lat_(0.5,7.5, 0.98,1, 0);
  era_lat_(0.5,7.5, 0.98,1);
  gPad->Update(); if (save) for (auto format : formats) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
  // -------------------------------------------------------------
  //           HitEfficiency vs Instantaneous Luminosity
  
  c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/LayersDisks_data");
  g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
  g->SetTitle("");
  g->SetTitle("#sqrt{s}=13 TeV (25ns)");
  g->GetXaxis()->SetRangeUser(0,5.5);
  g->GetYaxis()->SetNdivisions(505);
  c->Draw();
  prelim_lat_(0,5.5, 0.98,1, 0);
  era_lat_(0,5.5, 0.98,1);
  gPad->Update(); if (save) for (auto format : formats) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());

  // -------------------------------------------------------------
  //                   HitEfficiency vs Pile-up
  
  c = (TCanvas*)f->Get("HitEfficiency_vs_Pileup/LayersDisks_data");
  g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
  g->SetTitle("");
  g->SetTitle("#sqrt{s}=13 TeV (25ns)");
  g->GetXaxis()->SetTitle("Average Pile-up");
  g->GetXaxis()->SetRangeUser(0,25);
  g->GetYaxis()->SetNdivisions(505);
  c->Draw();
  prelim_lat_(0,25, 0.98,1, 0);
  era_lat_(0,25, 0.98,1);
  gPad->Update(); if (save) for (auto format : formats) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
}
