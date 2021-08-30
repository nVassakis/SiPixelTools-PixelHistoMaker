#include "custom_can_macro.C"

void Approval_plots() {
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  TFile *f; TCanvas *c; TArrow *arr; TGaxis* axis;
  
  bool save = 0;
  std::string save_dir = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2015/Approved/";
  const char* format = ".eps";
  
  // -------------------------------------------------------------
  //                 Fine Delay Scan plots
  
  //f = TFile::Open("Janos_PHM/PHM_out/StartupScans2015_Approved.root");
  f = TFile::Open("Janos_PHM/PHM_out/DelayScans2015_Final.root");
  TH1D *BPix_charge = (TH1D*)f->Get("AvgOnTrkCluChargeNorm_vs_Delay/BPix_2015Fine");
  TH1D *FPix_charge = (TH1D*)f->Get("AvgOnTrkCluChargeNorm_vs_Delay/FPix_2015Fine");
  TH1D *l1_charge   = (TH1D*)f->Get("AvgOnTrkCluChargeNorm_vs_Delay/Lay1_2015Fine");
  TH1D *l2_charge   = (TH1D*)f->Get("AvgOnTrkCluChargeNorm_vs_Delay/Lay2_2015Fine");
  TH1D *l3_charge   = (TH1D*)f->Get("AvgOnTrkCluChargeNorm_vs_Delay/Lay3_2015Fine");
  TH1D *d1_charge   = (TH1D*)f->Get("AvgOnTrkCluChargeNorm_vs_Delay/Disk1_2015Fine");
  TH1D *d2_charge   = (TH1D*)f->Get("AvgOnTrkCluChargeNorm_vs_Delay/Disk2_2015Fine");
  TH1D *BPix_eff    = (TH1D*)f->Get("HitEfficiency_vs_Delay/BPix_2015Fine")->Clone();
  TH1D *FPix_eff    = (TH1D*)f->Get("HitEfficiency_vs_Delay/FPix_2015Fine")->Clone();
  TH1D *l1_eff      = (TH1D*)f->Get("HitEfficiency_vs_Delay/Lay1_2015Fine")->Clone();
  TH1D *l2_eff      = (TH1D*)f->Get("HitEfficiency_vs_Delay/Lay2_2015Fine")->Clone();
  TH1D *l3_eff      = (TH1D*)f->Get("HitEfficiency_vs_Delay/Lay3_2015Fine")->Clone();
  TH1D *d1_eff      = (TH1D*)f->Get("HitEfficiency_vs_Delay/Disk1_2015Fine")->Clone();
  TH1D *d2_eff      = (TH1D*)f->Get("HitEfficiency_vs_Delay/Disk2_2015Fine")->Clone();
  TH1D *BPix_size   = (TH1D*)f->Get("AvgOnTrkCluSize_vs_Delay/BPix_2015Fine");
  TH1D *FPix_size   = (TH1D*)f->Get("AvgOnTrkCluSize_vs_Delay/FPix_2015Fine");
  TH1D *l1_size     = (TH1D*)f->Get("AvgOnTrkCluSize_vs_Delay/Lay1_2015Fine");
  TH1D *l2_size     = (TH1D*)f->Get("AvgOnTrkCluSize_vs_Delay/Lay2_2015Fine");
  TH1D *l3_size     = (TH1D*)f->Get("AvgOnTrkCluSize_vs_Delay/Lay3_2015Fine");
  TH1D *d1_size     = (TH1D*)f->Get("AvgOnTrkCluSize_vs_Delay/Disk1_2015Fine");
  TH1D *d2_size     = (TH1D*)f->Get("AvgOnTrkCluSize_vs_Delay/Disk2_2015Fine");
  
  BPix_charge->SetBinContent(23,0);
  BPix_charge->SetBinError(23,0);
  BPix_charge->SetMarkerColor(1);
  FPix_charge->SetBinContent(23,0); 
  FPix_charge->SetBinError(23,0);
  FPix_charge->SetMarkerColor(1);
  l1_charge->SetTitle("Layer 1");
  l1_charge->SetBinContent(23,0); 
  l1_charge->SetBinError(23,0);
  l1_charge->SetMarkerColor(1);
  l2_charge->SetTitle("Layer 2");
  l2_charge->SetBinContent(23,0); 
  l2_charge->SetBinError(23,0);
  l2_charge->SetMarkerColor(1);
  l3_charge->SetTitle("Layer 3");
  l3_charge->SetBinContent(23,0); 
  l3_charge->SetBinError(23,0);
  l3_charge->SetMarkerColor(1);
  d1_charge->SetTitle("Disk 1");
  d1_charge->SetBinContent(23,0); 
  d1_charge->SetBinError(23,0);
  d1_charge->SetMarkerColor(1);
  d2_charge->SetTitle("Disk 2");
  d2_charge->SetBinContent(23,0); 
  d2_charge->SetBinError(23,0);
  d2_charge->SetMarkerColor(1);

  BPix_size->SetBinContent(23,0); 
  BPix_size->SetBinError(23,0);
  BPix_size->SetMarkerColor(1);
  FPix_size->SetBinContent(23,0); 
  FPix_size->SetBinError(23,0);
  FPix_size->SetMarkerColor(1);
  l1_size->SetTitle("Layer 1");
  l1_size->SetBinContent(23,0); 
  l1_size->SetBinError(23,0);
  l1_size->SetMarkerColor(1);
  l2_size->SetTitle("Layer 2");
  l2_size->SetBinContent(23,0); 
  l2_size->SetBinError(23,0);
  l2_size->SetMarkerColor(1);
  l3_size->SetTitle("Layer 3");
  l3_size->SetBinContent(23,0); 
  l3_size->SetBinError(23,0);
  l3_size->SetMarkerColor(1);
  d1_size->SetTitle("Disk 1");
  d1_size->SetBinContent(23,0); 
  d1_size->SetBinError(23,0);
  d1_size->SetMarkerColor(1);
  d2_size->SetTitle("Disk 2");
  d2_size->SetBinContent(23,0); 
  d2_size->SetBinError(23,0);
  d2_size->SetMarkerColor(1);
  
  BPix_charge->SetTitle("#sqrt{s}=13 TeV (50ns)");
  c = custom_can_(BPix_charge, "OnTrkCluCharge_and_HitEfficiency_vs_Delay_BPix", 1,1, 500,500, 80,80, 45,60, 33, 0.9,0.99);
  draw_with_right_yaxis_(BPix_charge, BPix_eff, "PE1X0", "Hit Efficiency", 20,27, 36,48, 0.9,1.02, 23, 1);
  draw_lat_(23.5, 42, "BPix", 1, 0.05, 0.0, 23);
  prelim_lat_(19.5,27.5, 36,48, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
  FPix_charge->SetTitle("#sqrt{s}=13 TeV (50ns)");
  c = custom_can_(FPix_charge, "OnTrkCluCharge_and_HitEfficiency_vs_Delay_FPix", 1,1, 500,500, 80,80, 45,60, 33, 0.9,0.99);
  draw_with_right_yaxis_(FPix_charge, FPix_eff, "PE1X0", "Hit Efficiency", 20,27, 18,24, 0.9,1.02, 24, 1);
  draw_lat_(23.5, 21, "FPix", 1, 0.05, 0.0, 23);
  prelim_lat_(19.5,27.5, 18,24, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
  //c = custom_can_(l1_charge, "OnTrkCluChargeNorm_and_HitEfficiency_vs_Delay_Layer1", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(l1_charge, l1_eff, "PE1X0", "Hit Efficiency", 20,27, 37,52, 0.95,1.0, 24, 1);
  //c = custom_can_(l2_charge, "OnTrkCluChargeNorm_and_HitEfficiency_vs_Delay_Layer2", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(l2_charge, l2_eff, "PE1X0", "Hit Efficiency", 20,27, 36,46, 0.95,1.0, 24, 1);
  //c = custom_can_(l3_charge, "OnTrkCluChargeNorm_and_HitEfficiency_vs_Delay_Layer3", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(l3_charge, l3_eff, "PE1X0", "Hit Efficiency", 20,27, 30,40, 0.95,1.0, 24, 1);
  //c = custom_can_(d1_charge, "OnTrkCluChargeNorm_and_HitEfficiency_vs_Delay_Disk1", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(d1_charge, d1_eff, "PE1X0", "Hit Efficiency", 20,27, 20,23, 0.95,1.0, 24, 1);
  //c = custom_can_(d2_charge, "OnTrkCluChargeNorm_and_HitEfficiency_vs_Delay_Disk2", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(d2_charge, d2_eff, "PE1X0", "Hit Efficiency", 20,27, 20,23, 0.95,1.0, 24, 1);
  
  BPix_eff  = (TH1D*)f->Get("HitEfficiency_vs_Delay/BPix_2015Fine");
  FPix_eff  = (TH1D*)f->Get("HitEfficiency_vs_Delay/FPix_2015Fine");
  l1_eff  = (TH1D*)f->Get("HitEfficiency_vs_Delay/Lay1_2015Fine");
  l2_eff  = (TH1D*)f->Get("HitEfficiency_vs_Delay/Lay2_2015Fine");
  l3_eff  = (TH1D*)f->Get("HitEfficiency_vs_Delay/Lay3_2015Fine");
  d1_eff  = (TH1D*)f->Get("HitEfficiency_vs_Delay/Disk1_2015Fine");
  d2_eff  = (TH1D*)f->Get("HitEfficiency_vs_Delay/Disk2_2015Fine");
  
  
  BPix_size->SetTitle("#sqrt{s}=13 TeV (50ns)");
  c = custom_can_(BPix_size, "OnTrkCluSize_and_HitEfficiency_vs_Delay_BPix", 1,1, 500,500, 80,80, 45,60, 33, 0.9,0.99);
  draw_with_right_yaxis_(BPix_size, BPix_eff, "PE1X0", "Hit Efficiency", 20,27, 3.1,4.3, 0.9,1.02, 23, 1);
  draw_lat_(23.5, 3.7, "BPix", 1, 0.05, 0.0, 23);
  prelim_lat_(19.5,27.5, 3.1,4.3, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
  FPix_size->SetTitle("#sqrt{s}=13 TeV (50ns)");
  c = custom_can_(FPix_size, "OnTrkCluSize_and_HitEfficiency_vs_Delay_FPix", 1,1, 500,500, 80,80, 45,60, 33, 0.9,0.99);
  draw_with_right_yaxis_(FPix_size, FPix_eff, "PE1X0", "Hit Efficiency", 20,27, 1.5,2.1, 0.9,1.02, 24, 1);
  draw_lat_(23.5, 1.8, "FPix", 1, 0.05, 0.0, 23);
  prelim_lat_(19.5,27.5, 1.5,2.1, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
  //c = custom_can_(l1_size, "OnTrkCluSize_and_HitEfficiency_vs_Delay_Layer1", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(l1_size, l1_eff, "PE1X0", "Hit Efficiency", 20,27, 37,52, 0.95,1.0, 24, 1);
  //c = custom_can_(l2_size, "OnTrkCluSize_and_HitEfficiency_vs_Delay_Layer2", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(l2_size, l2_eff, "PE1X0", "Hit Efficiency", 20,27, 36,46, 0.95,1.0, 24, 1);
  //c = custom_can_(l3_size, "OnTrkCluSize_and_HitEfficiency_vs_Delay_Layer3", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(l3_size, l3_eff, "PE1X0", "Hit Efficiency", 20,27, 30,40, 0.95,1.0, 24, 1);
  //c = custom_can_(d1_size, "OnTrkCluSize_and_HitEfficiency_vs_Delay_Disk1", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(d1_size, d1_eff, "PE1X0", "Hit Efficiency", 20,27, 20,23, 0.95,1.0, 24, 1);
  //c = custom_can_(d2_size, "OnTrkCluSize_and_HitEfficiency_vs_Delay_Disk2", 1,1, 500,500, 80,80, 30);
  //draw_with_right_yaxis_(d2_size, d2_eff, "PE1X0", "Hit Efficiency", 20,27, 20,23, 0.95,1.0, 24, 1);
  
  
  // -------------------------------------------------------------
  //                 High Voltage Scan Plots
  
  //f = TFile::Open("Janos_PHM/PHM_out/HV18_Final.root");
  f = TFile::Open("Janos_PHM/PHM_out/StartupScans2015_Final.root");
  c = (TCanvas*)f->Get("HitEfficiency_vs_BiasVoltage/LayersDisks_HV18");
  TLegend* leg = (TLegend*)c->GetListOfPrimitives()->At(5);
  leg->SetX1(0.45);leg->SetX2(0.6);leg->SetY1(0.42);leg->SetY2(0.65);
  leg->DeleteEntry();
  TH1D* h = (TH1D*)c->GetListOfPrimitives()->At(0);
  h->GetXaxis()->SetRangeUser(0,300);
  h->SetTitle("#sqrt{s}=13 TeV (50ns)");
  gStyle->SetTitleAlign(33);
  gStyle->SetTitleX(0.985);
  gStyle->SetTitleY(0.96);
  Int_t wtopx, wtopy; UInt_t ww, wh; c->GetCanvasPar(wtopx, wtopy, ww, wh);
  gPad->SetTopMargin(double(gPad->GetTopMargin()*wh+10)/double(wh+10));
  c->SetCanvasSize(ww, wh+10);
  c->Draw();
  prelim_lat_(-2.5,302.5, 0,1, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
  //c = (TCanvas*)f->Get("NormOnTrkCluChargeMPV_vs_BiasVoltage/LayersDisks_HV18");
  //leg = (TLegend*)c->GetListOfPrimitives()->At(5);
  //leg->SetX1(0.45);leg->SetX2(0.6);leg->SetY1(0.2);leg->SetY2(0.43);
  //leg->DeleteEntry();
  //h = (TH1D*)c->GetListOfPrimitives()->At(0);
  //h->GetXaxis()->SetRangeUser(0,300);
  //h->GetYaxis()->SetRangeUser(0,25);
  //h->SetTitle("#sqrt{s}=13 TeV (50ns);Bias Votage (V);Norm. On-Trk Cluster Charge MPV (ke)");
  //gStyle->SetTitleAlign(33);
  //gStyle->SetTitleX(0.985);
  //gStyle->SetTitleY(0.96);
  //c->GetCanvasPar(wtopx, wtopy, ww, wh);
  //gPad->SetTopMargin(double(gPad->GetTopMargin()*wh+10)/double(wh+10));
  //c->SetCanvasSize(ww, wh+10);
  //c->Draw();
  //prelim_lat_(-2.5,302.5, 0,25, 0);
  //gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
  c = (TCanvas*)f->Get("NormOnTrkCluChargeMPV_vs_BiasVoltage/LayersDisks_HV18")->Clone();
  h = (TH1D*)c->GetListOfPrimitives()->At(0);
  h->GetXaxis()->SetRangeUser(0,200);
  h->GetYaxis()->SetRangeUser(0,25);
  h->SetTitle("#sqrt{s}=13 TeV (50ns);Bias Votage (V);Norm. On-Trk Cluster Charge MPV (ke)");
  gStyle->SetTitleAlign(33);
  gStyle->SetTitleX(0.985);
  gStyle->SetTitleY(0.96);
  c->GetCanvasPar(wtopx, wtopy, ww, wh);
  gPad->SetTopMargin(double(gPad->GetTopMargin()*wh+10)/double(wh+10));
  c->SetCanvasSize(ww, wh+10);
  c->Draw();
  leg = new TLegend(0.55, 0.27, 0.75, 0.42);
  leg->AddEntry((TH1D*)c->GetListOfPrimitives()->At(0), "Layer 1", "p");
  leg->AddEntry((TH1D*)c->GetListOfPrimitives()->At(1), "Layer 2", "p");
  leg->AddEntry((TH1D*)c->GetListOfPrimitives()->At(2), "Layer 3", "p");
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  gPad->GetListOfPrimitives()->Remove((TLegend*)gPad->GetPrimitive(c->GetListOfPrimitives()->At(5)->GetName())); gPad->Update();
  gPad->GetListOfPrimitives()->Remove((TH1D*)gPad->GetPrimitive(c->GetListOfPrimitives()->At(5)->GetName())); gPad->Update();
  gPad->GetListOfPrimitives()->Remove((TH1D*)gPad->GetPrimitive(c->GetListOfPrimitives()->At(4)->GetName())); gPad->Update();
  leg->Draw(); gPad->Update();
  prelim_lat_(-2.5,202.5, 0,25, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+"_BPix"+format).c_str());

  c = (TCanvas*)f->Get("NormOnTrkCluChargeMPV_vs_BiasVoltage/LayersDisks_HV18");
  h = (TH1D*)c->GetListOfPrimitives()->At(3)->Clone();
  TH1D* h2 = (TH1D*)c->GetListOfPrimitives()->At(4)->Clone();
  TH1D* h0 = (TH1D*)c->GetListOfPrimitives()->At(0)->Clone();
  h->GetXaxis()->SetTitleSize(h0->GetXaxis()->GetTitleSize());
  h->GetYaxis()->SetTitleSize(h0->GetYaxis()->GetTitleSize());
  h->GetXaxis()->SetTitleOffset(h0->GetXaxis()->GetTitleOffset());
  h->GetYaxis()->SetTitleOffset(h0->GetYaxis()->GetTitleOffset());
  h->GetXaxis()->SetRangeUser(0,300);
  h->GetYaxis()->SetRangeUser(0,20);
  h->SetTitle("#sqrt{s}=13 TeV (50ns);Bias Votage (V);Norm. On-Trk Cluster Charge MPV (ke)");
  gStyle->SetTitleAlign(33);
  gStyle->SetTitleX(0.985);
  gStyle->SetTitleY(0.96);
  c->GetCanvasPar(wtopx, wtopy, ww, wh);
  gPad->SetTopMargin(double(gPad->GetTopMargin()*wh+10)/double(wh+10));
  c->SetCanvasSize(ww, wh+10);
  c->Draw();
  h->Draw("PE1X0");
  gPad->Update();
  h2->Draw("SAMEPE1X0");
  leg = new TLegend(0.4, 0.42, 0.6, 0.53);
  leg->AddEntry(h, "Disk 1", "p");
  leg->AddEntry(h2, "Disk 2", "p");
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->Draw(); gPad->Update();
  prelim_lat_(-2.5,302.5, 0,20, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+"_FPix"+format).c_str());
  
  // -------------------------------------------------------------
  //              HitEfficiency vs Layers/Disks
  
  //f = TFile::Open("Janos_PHM/PHM_out/test.root");
  f = TFile::Open("Janos_PHM/PHM_out/Run2012B_dir0000_Final.root");
  TH1D *eff = (TH1D*)f->Get("HitEfficiency_vs_LayersDisks/Data");
  
  eff->SetTitle("#sqrt{s}=13 TeV (50ns)");
  c = custom_can_(eff, "HitEfficiency_vs_LayerDisks", 0,1, 500,500, 100,20, 45,60, 33, 0.99,0.99);
  eff->GetYaxis()->SetRangeUser(0.98,1);
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
  TGraphAsymmErrors* tgae = asym_(eff);
  for (int i=0; i<7; ++i) {
    double err_high = (eff->GetBinContent(i+1)+0.003)>1 ? 1-eff->GetBinContent(i+1) : 0.003;
    tgae->SetPointEYhigh(i,err_high); tgae->SetPointEYlow (i,0.003);
  }
  tgae->Draw("AP");
  asym_labels_(eff, tgae, 0);
  prelim_lat_(0.5,7.5, 0.98,1, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  
  // -------------------------------------------------------------
  //              Occupancy plots - Run 251561
  f = TFile::Open("Janos_PHM/PHM_out/Run251561.root");
  
  TH2D *l1 = (TH2D*)f->Get("ROCLadders_vs_ROCModules/Data_Lay1");
  TH2D *l2 = (TH2D*)f->Get("ROCLadders_vs_ROCModules/Data_Lay2");
  TH2D *l3 = (TH2D*)f->Get("ROCLadders_vs_ROCModules/Data_Lay3");
  TH2D *fpixI = (TH2D*)f->Get("ROCBladesInner_vs_ROCSideDiskPanel/Data");
  TH2D *fpixO = (TH2D*)f->Get("ROCBladesOuter_vs_ROCSideDiskPanel/Data");
  
  l1->GetYaxis()->SetRangeUser(-10,10);
  l2->GetYaxis()->SetRangeUser(-16,16);
  l1->SetTitle("#sqrt{s}=13 TeV (50ns)");
  l2->SetTitle("#sqrt{s}=13 TeV (50ns)");
  l3->SetTitle("#sqrt{s}=13 TeV (50ns)");
  fpixI->SetTitle("#sqrt{s}=13 TeV (50ns)");
  fpixO->SetTitle("#sqrt{s}=13 TeV (50ns)");
  fpixI->GetYaxis()->SetTitle("Blades in Inner Halves");
  fpixO->GetYaxis()->SetTitle("Blades in Outer Halves");
  l1->GetZaxis()->SetTitle("Cluster Occupancy- Layer 1");
  l2->GetZaxis()->SetTitle("Cluster Occupancy- Layer 2");
  l3->GetZaxis()->SetTitle("Cluster Occupancy- Layer 3");
  fpixI->GetZaxis()->SetTitle("Cluster Occupancy");
  fpixO->GetZaxis()->SetTitle("Cluster Occupancy");
  fpixI->GetXaxis()->SetBinLabel(1, "Disk-2 Pnl2");
  fpixI->GetXaxis()->SetBinLabel(9, "Disk-2 Pnl1");
  fpixI->GetXaxis()->SetBinLabel(19, "Disk-1 Pnl2");
  fpixI->GetXaxis()->SetBinLabel(27, "Disk-1 Pnl1");
  fpixI->GetXaxis()->SetBinLabel(41, "Disk+1 Pnl1");
  fpixI->GetXaxis()->SetBinLabel(49, "Disk+1 Pnl2");
  fpixI->GetXaxis()->SetBinLabel(59, "Disk+2 Pnl1");
  fpixI->GetXaxis()->SetBinLabel(67, "Disk+2 Pnl2");
  fpixI->GetXaxis()->LabelsOption("d");
  fpixO->GetXaxis()->SetBinLabel(1, "Disk-2 Pnl2");
  fpixO->GetXaxis()->SetBinLabel(9, "Disk-2 Pnl1");
  fpixO->GetXaxis()->SetBinLabel(19, "Disk-1 Pnl2");
  fpixO->GetXaxis()->SetBinLabel(27, "Disk-1 Pnl1");
  fpixO->GetXaxis()->SetBinLabel(41, "Disk+1 Pnl1");
  fpixO->GetXaxis()->SetBinLabel(49, "Disk+1 Pnl2");
  fpixO->GetXaxis()->SetBinLabel(59, "Disk+2 Pnl1");
  fpixO->GetXaxis()->SetBinLabel(67, "Disk+2 Pnl2");
  fpixO->GetXaxis()->LabelsOption("d");
  //l1->GetXaxis()->SetLabelSize(0.045);
  //l2->GetXaxis()->SetLabelSize(0.045);
  //l3->GetXaxis()->SetLabelSize(0.045);
  //fpixI->GetXaxis()->SetLabelSize(0.045);
  //fpixO->GetXaxis()->SetLabelSize(0.045);
  l2->SetBinContent(25,33,0);
  l2->SetBinContent(29,33,0);
  c = custom_can_(l1, "ROCMap_Layer1", 0,0, 500,500, 70,120, 40,60, 33, 0.9,0.99, "COLZ", 0, 0);
  arr = new TArrow(0.5, 0, 3, 0, 0.02, "|>"); arr->Draw();
  draw_lat_(0.5, 0, "z-axis (along beam)", 1, 0.025, 0.0, 13);
  arr = new TArrow(0, 5.5, 0, 0, 0.02, "|>"); arr->Draw();
  draw_lat_(-0.1, 2.5, "global #phi", 1, 0.025, 90.0, 21);
  draw_lat_(0.1, 5.5, "0", 1, 0.025, 90.0, 23);
  draw_lat_(0.1, 1, "#pi/2", 1, 0.025, 90.0, 23);

  prelim_lat_(-4.5,4.5, -10,10, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  c = custom_can_(l2, "ROCMap_Layer2", 0,0, 500,500, 70,120, 40,60, 33, 0.9,0.99, "COLZ", 0, 0);
  arr = new TArrow(0.5, 0, 3, 0, 0.02, "|>"); arr->Draw();
  draw_lat_(0.5, 0, "z-axis (along beam)", 1, 0.025, 0.0, 13);
  arr = new TArrow(0, 8.5, 0, 0, 0.02, "|>"); arr->Draw();
  draw_lat_(-0.1, 4, "global #phi", 1, 0.025, 90.0, 21);
  draw_lat_(0.1, 8.5, "0", 1, 0.025, 90.0, 23);
  draw_lat_(0.1, 1, "#pi/2", 1, 0.025, 90.0, 23);
  
  prelim_lat_(-4.5,4.5, -16,16, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  c = custom_can_(l3, "ROCMap_Layer3", 0,0, 500,500, 70,120, 40,60, 33, 0.9,0.99, "COLZ", 0, 0);
  arr = new TArrow(0.5, 0.2, 3, 0.2, 0.02, "|>"); arr->Draw();
  draw_lat_(0.5, 0.1, "z-axis (along beam)", 1, 0.025, 0.0, 13);
  arr = new TArrow(0, 11.5, 0, 0, 0.02, "|>"); arr->Draw();
  draw_lat_(-0.1, 5.5, "global #phi", 1, 0.025, 90.0, 21);
  draw_lat_(0.1, 11.5, "0", 1, 0.025, 90.0, 23);
  draw_lat_(0.1, 1, "#pi/2", 1, 0.025, 90.0, 23);
  
  prelim_lat_(-4.5,4.5, -22,22, 0);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  c = custom_can_(fpixI, "ROCMap_FPixInner", 0,0, 500,500, 70,120, 40,60, 33, 0.9,0.99, "COLZ", 0, 0);
  prelim_lat_(-4.5,4.5, 0.5,12.5, 0);
  arr = new TArrow(0, 6.5, 0, 3.5, 0.02, "|>"); arr->Draw();
  draw_lat_(-0.1, 5, "global #phi", 1, 0.025, 90.0, 21);
  draw_lat_(0.1, 6.5, "0", 1, 0.025, 90.0, 23);
  
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
  c = custom_can_(fpixO, "ROCMap_FPixOuter", 0,0, 500,500, 70,120, 40,60, 33, 0.9,0.99, "COLZ", 0, 0);
  prelim_lat_(-4.5,4.5, -12.5,-0.5, 0);
  arr = new TArrow(0, -6.5, 0, -9.5, 0.02, "|>"); arr->Draw();
  draw_lat_(-0.1, -8, "global #phi", 1, 0.025, 90.0, 21);
  draw_lat_(0.1, -6.5, "#pi", 1, 0.03, 90.0, 23);
  gPad->Update(); if (save) c->SaveAs((save_dir+std::string(c->GetName())+format).c_str());
}
