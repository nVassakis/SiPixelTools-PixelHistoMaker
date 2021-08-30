#include "common_functions.h"

void Approval_plots_2018_Data() {
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  //gROOT->SetStyle("Plain");
  TFile *f; TCanvas *c; TArrow *arr; TGaxis* axis; TGraphAsymmErrors* g; TH1D* h;
  
  bool save = 1;
  int remove_prelim_label = 0;
  //std::string save_dir = "Plots/Approved_Plots/2018_May/Approved/";
  //std::string save_dir = "Plots/Approved_Plots/2018_July/PreApproval2/";
  std::string save_dir = "Plots/Approved_Plots/Papers/Pixel_Phase1/";
  std::vector<std::string> formats = { ".png", ".eps", ".root", ".C", ".pdf" };
  //std::vector<std::string> formats = { ".png" };
  
  bool efficiency      = 0;
  bool delay           = 0;
  bool filling_schemes = 0;
  bool efficiency_upd1 = 1;

  if (efficiency) {
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/Early2018FillingSchemes_10invfb.root");
    

    // -------------------------------------------------------------
    //              HitEfficiency vs InstLumi

    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi0p5/LayersDisks_2544b");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    g->GetXaxis()->SetRangeUser(0,20);
    g->GetYaxis()->SetRangeUser(0.9,1);
    c->Draw();
    rename_legend(c, "");
    prelim_lat_(0,20, 0.9,1, 0);
    era_lat_   (0,20, 0.9,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // -------------------------------------------------------------
    //              HitEfficiency vs Pile-Up

    c = (TCanvas*)f->Get("HitEfficiency_vs_Pileup/LayersDisks_2544b");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    g->GetXaxis()->SetRangeUser(8,60);
    g->GetYaxis()->SetRangeUser(0.9,1);
    c->Draw();
    rename_legend(c, "");
    prelim_lat_(8,60, 0.9,1, 0);
    era_lat_   (8,60, 0.9,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
  }

  if (delay) {
    
    // -------------------------------------------------------------
    //                        Delay Scan

    // Efficiency
    // BPix
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/Phase1_TimingScan2018_Apr19ScanResults.root");
    c = (TCanvas*)f->Get("HitEfficiency_vs_Delay/Layers_2018Apr17_Scan1and3");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    g->GetXaxis()->SetRangeUser(-15,15);
    g->GetYaxis()->SetRangeUser(0,1);
    TLegend* leg = modify_legend(c, "", 0.15,0.35, 0.55,0.85);
    remove_points(c, 1, 8,8);
    remove_points(c, 2, 8,8);
    remove_points(c, 3, 8,8);
    remove_points(c, 4, 8,8);
    c->Draw();
    // Add shaded boxes
    TPave *p = new TPave(-15,0,-4,1,0,"");
    p->SetFillColor(1);
    p->SetFillStyle(3004);
    p->Draw();
    p = new TPave(6,0,15,1,0,"");
    p->SetFillColor(1);
    p->SetFillStyle(3004);
    p->Draw();
    prelim_lat_(-15,15, 0,1, 0);
    era_lat_   (-15,15, 0,1);
    leg->AddEntry(draw_line(0.5, 0.5, 0,1, 2, 7, 634), "#color[634]{L1-2 Setting}", "l");
    leg->AddEntry(draw_line(1.5, 1.5, 0,1, 2, 7, 601), "#color[601]{L3-4 Setting}", "l");
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    // FPix
    c = (TCanvas*)f->Get("HitEfficiency_vs_Delay/Disks_2018Apr17_Scan1and3");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    g->GetXaxis()->SetRangeUser(-15,15);
    g->GetYaxis()->SetRangeUser(0,1);
    leg = modify_legend(c, "", 0.15,0.35, 0.2,0.4);
    remove_points(c, 1, 8,8);
    remove_points(c, 2, 8,8);
    remove_points(c, 3, 8,8);
    c->Draw();
    prelim_lat_(-15,15, 0,1, 0);
    era_lat_   (-15,15, 0,1);
    leg->AddEntry(draw_line(1.5, 1.5, 0,1, 2, 7, 1), "Operational Setting", "l");
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // Size
    // BPix
    c = (TCanvas*)f->Get("AvgOnTrkCluSize_vs_Delay/Layers_2018Apr17_Scan1and3");
    h = (TH1D*)c->GetListOfPrimitives()->At(1);
    h->GetXaxis()->SetRangeUser(-15,15);
    h->GetYaxis()->SetRangeUser(0,7);
    leg = modify_legend(c, "", 0.15,0.35, 0.55,0.85);
    remove_points(c, 1, 8,8);
    remove_points(c, 2, 8,8);
    remove_points(c, 3, 8,8);
    remove_points(c, 4, 8,8);
    c->Draw();
    // Add shaded boxes
    p = new TPave(-15,0,-4,7,0,"");
    p->SetFillColor(1);
    p->SetFillStyle(3004);
    p->Draw();
    p = new TPave(6,0,15,7,0,"");
    p->SetFillColor(1);
    p->SetFillStyle(3004);
    p->Draw();
    prelim_lat_(-15,15, 0,7, 0);
    era_lat_   (-15,15, 0,7);
    leg->AddEntry(draw_line(0.5, 0.5, 0,7, 2, 7, 634), "#color[634]{L1-2 Setting}", "l");
    leg->AddEntry(draw_line(1.5, 1.5, 0,7, 2, 7, 601), "#color[601]{L3-4 Setting}", "l");
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnTrkCluSize_vs_Delay/Disks_2018Apr17_Scan1and3");
    h = (TH1D*)c->GetListOfPrimitives()->At(1);
    h->GetXaxis()->SetRangeUser(-15,15);
    h->GetYaxis()->SetRangeUser(0,3);
    leg = modify_legend(c, "", 0.15,0.35, 0.2,0.4);
    remove_points(c, 1, 8,8);
    remove_points(c, 2, 8,8);
    remove_points(c, 3, 8,8);
    c->Draw();
    prelim_lat_(-15,15, 0,3, 0);
    era_lat_   (-15,15, 0,3);
    leg->AddEntry(draw_line(1.5, 1.5, 0,3, 2, 7, 1), "Operational Setting", "l");
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // Charge
    // BPix
    c = (TCanvas*)f->Get("AvgNormOnTrkCluCharge_vs_Delay/Layers_2018Apr17_Scan1and3");
    h = (TH1D*)c->GetListOfPrimitives()->At(1);
    h->GetXaxis()->SetRangeUser(-15,15);
    h->GetYaxis()->SetRangeUser(0,30);
    leg = modify_legend(c, "", 0.15,0.35, 0.1,0.4);
    remove_points(c, 1, 8,8);
    remove_points(c, 2, 8,8);
    remove_points(c, 3, 8,8);
    remove_points(c, 4, 8,8);
    c->Draw();
    // Add shaded boxes
    p = new TPave(-15,0,-4,30,0,"");
    p->SetFillColor(1);
    p->SetFillStyle(3004);
    p->Draw();
    p = new TPave(6,0,15,30,0,"");
    p->SetFillColor(1);
    p->SetFillStyle(3004);
    p->Draw();
    prelim_lat_(-15,15, 0,30, 0);
    era_lat_   (-15,15, 0,30);
    leg->AddEntry(draw_line(0.5, 0.5, 0,30, 2, 7, 634), "#color[634]{L1-2 Setting}", "l");
    leg->AddEntry(draw_line(1.5, 1.5, 0,30, 2, 7, 601), "#color[601]{L3-4 Setting}", "l");
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgNormOnTrkCluCharge_vs_Delay/Disks_2018Apr17_Scan1and3");
    h = (TH1D*)c->GetListOfPrimitives()->At(1);
    h->GetXaxis()->SetRangeUser(-15,15);
    h->GetYaxis()->SetRangeUser(0,25);
    leg = modify_legend(c, "", 0.15,0.35, 0.2,0.4);
    remove_points(c, 1, 8,8);
    remove_points(c, 2, 8,8);
    remove_points(c, 3, 8,8);
    c->Draw();
    prelim_lat_(-15,15, 0,25, 0);
    era_lat_   (-15,15, 0,25);
    leg->AddEntry(draw_line(1.5, 1.5, 0,25, 2, 7, 1), "Operational Setting", "l");
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

  }

  if (filling_schemes) {
    
    // -------------------------------------------------------------
    //                       Filling Schemes

    // Layer 1
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/History2018_22invfb.root");
    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi0p5/SelectedNBx_Lay1_2018Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    g->GetXaxis()->SetRangeUser(0,20);
    g->GetYaxis()->SetRangeUser(0.9,1);
    g->SetMarkerColor(1);
    c->Draw();
    //remove_plot(c, 9);
    remove_plot(c, 8);
    //remove_plot(c, 7);
    remove_plot(c, 6);
    //remove_plot(c, 5);
    remove_plot(c, 4);
    //remove_plot(c, 3);
    remove_plot(c, 2);
    remove_plot(c, 1);
    modify_legend(c, "Layer 1", 0.4,0.6, 0.12,0.4);
    gPad->Update();
    TLegend *leg = 0;
    for (int i=0, n=c->GetListOfPrimitives()->GetEntries(); i<n; ++i) {
      if (std::string(c->GetListOfPrimitives()->At(i)->GetName())=="TPave") 
	leg = (TLegend*)c->GetListOfPrimitives()->At(i);
    }
    TLegendEntry* entry = (TLegendEntry*)leg->GetListOfPrimitives()->At(1);
    entry->SetObject(g);
    entry->SetLabel("2b");
    prelim_lat_(0,20, 0.9,1, 0);
    era_lat_   (0,20, 0.9,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // Layer 2
    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi0p5/SelectedNBx_Lay2_2018Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    g->GetXaxis()->SetRangeUser(0,20);
    g->GetYaxis()->SetRangeUser(0.95,1);
    g->SetMarkerColor(1);
    c->Draw();
    //remove_plot(c, 9);
    remove_plot(c, 8);
    //remove_plot(c, 7);
    remove_plot(c, 6);
    //remove_plot(c, 5);
    remove_plot(c, 4);
    //remove_plot(c, 3);
    remove_plot(c, 2);
    remove_plot(c, 1);
    modify_legend(c, "Layer 2", 0.4,0.6, 0.12,0.4);
    gPad->Update();
    leg = 0;
    for (int i=0, n=c->GetListOfPrimitives()->GetEntries(); i<n; ++i) {
      if (std::string(c->GetListOfPrimitives()->At(i)->GetName())=="TPave") 
	leg = (TLegend*)c->GetListOfPrimitives()->At(i);
    }
    entry = (TLegendEntry*)leg->GetListOfPrimitives()->At(1);
    entry->SetObject(g);
    entry->SetLabel("2b");
    prelim_lat_(0,20, 0.95,1, 0);
    era_lat_   (0,20, 0.95,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // Pile-up
    // Layer 1
    c = (TCanvas*)f->Get("HitEfficiency_vs_Pileup/SelectedNBx_Lay1_2018Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    g->GetXaxis()->SetRangeUser(16,64);
    g->GetYaxis()->SetRangeUser(0.9,1);
    g->SetMarkerColor(1);
    c->Draw();
    remove_plot(c, 8);
    remove_plot(c, 6);
    remove_plot(c, 4);
    remove_plot(c, 2);
    remove_plot(c, 1);
    remove_points(c, 2, 0,4);
    remove_points(c, 3, 0,8);
    remove_points(c, 4, 0,4);
    remove_points(c, 5, 0,8);
    modify_legend(c, "Layer 1", 0.4,0.6, 0.12,0.4);
    gPad->Update();
    leg = 0;
    for (int i=0, n=c->GetListOfPrimitives()->GetEntries(); i<n; ++i) {
      if (std::string(c->GetListOfPrimitives()->At(i)->GetName())=="TPave") 
	leg = (TLegend*)c->GetListOfPrimitives()->At(i);
    }
    entry = (TLegendEntry*)leg->GetListOfPrimitives()->At(1);
    entry->SetObject(g);
    entry->SetLabel("2b");
    prelim_lat_(16,64, 0.9,1, 0);
    era_lat_   (16,64, 0.9,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    // Layer 2
    c = (TCanvas*)f->Get("HitEfficiency_vs_Pileup/SelectedNBx_Lay2_2018Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    g->GetXaxis()->SetRangeUser(16,64);
    g->GetYaxis()->SetRangeUser(0.95,1);
    g->SetMarkerColor(1);
    c->Draw();
    remove_plot(c, 8);
    remove_plot(c, 6);
    remove_plot(c, 4);
    remove_plot(c, 2);
    remove_plot(c, 1);
    remove_points(c, 2, 0,5);
    remove_points(c, 3, 0,8);
    remove_points(c, 4, 0,4);
    remove_points(c, 5, 0,8);
    modify_legend(c, "Layer 2", 0.4,0.6, 0.12,0.4);
    gPad->Update();
    leg = 0;
    for (int i=0, n=c->GetListOfPrimitives()->GetEntries(); i<n; ++i) {
      if (std::string(c->GetListOfPrimitives()->At(i)->GetName())=="TPave") 
	leg = (TLegend*)c->GetListOfPrimitives()->At(i);
    }
    entry = (TLegendEntry*)leg->GetListOfPrimitives()->At(1);
    entry->SetObject(g);
    entry->SetLabel("2b");
    prelim_lat_(16,64, 0.95,1, 0);
    era_lat_   (16,64, 0.95,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

  }


  if (efficiency_upd1) {
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/History2018_22invfb.root");

    // -------------------------------------------------------------
    //              HitEfficiency vs InstLumi

    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi0p5/LayersDisks_Data2018_MainFills");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    g->GetXaxis()->SetRangeUser(0,20);
    g->GetYaxis()->SetRangeUser(0.95,1);
    TLegend *leg = rename_legend(c, "");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(4);
    g->SetMarkerColor(418);
    g->SetLineColor(418);
    ((TLegendEntry*)leg->GetListOfPrimitives()->At(7))->SetObject(g);
    ((TLegendEntry*)leg->GetListOfPrimitives()->At(7))->SetLabel("#color[418]{Layer 4}");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(5);
    g->SetMarkerColor(1);
    g->SetLineColor(1);
    g->SetMarkerStyle(29);
    g->SetMarkerSize(1.2);
    ((TLegendEntry*)leg->GetListOfPrimitives()->At(2))->SetObject(g);
    ((TLegendEntry*)leg->GetListOfPrimitives()->At(2))->SetLabel("#color[1]{Disk 1}");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(6);
    g->SetMarkerColor(804);
    g->SetLineColor(804);
    g->SetMarkerStyle(33);
    g->SetMarkerSize(1.2);
    ((TLegendEntry*)leg->GetListOfPrimitives()->At(4))->SetObject(g);
    ((TLegendEntry*)leg->GetListOfPrimitives()->At(4))->SetLabel("#color[804]{Disk 2}");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(7);
    g->SetMarkerColor(402);
    g->SetLineColor(402);
    g->SetMarkerStyle(34);
    g->SetMarkerSize(1.2);
    ((TLegendEntry*)leg->GetListOfPrimitives()->At(6))->SetObject(g);
    ((TLegendEntry*)leg->GetListOfPrimitives()->At(6))->SetLabel("#color[402]{Disk 3}");
    c->Draw();
    TLatex *cms = prelim_lat_(0,20, 0.9,1, 0);
    TLatex *era = era_lat_   (0,20, 0.9,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    cms->SetY(1.00125);
    era->SetY(1.002);
    //c->SetName((std::string(c->GetName())+"_0p95").c_str());
    c->SetName((std::string(c->GetName())+"").c_str());
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    

    // -------------------------------------------------------------
    //              HitEfficiency vs Pile-Up

    //  c = (TCanvas*)f->Get("HitEfficiency_vs_Pileup/LayersDisks_Data2018_MainFills");
    //  g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    //  g->GetXaxis()->SetRangeUser(0,60);
    //  g->GetYaxis()->SetRangeUser(0.9,1);
    //  c->Draw();
    //  rename_legend(c, "");
    //  cms = prelim_lat_(0,60, 0.9,1, 0);
    //  era = era_lat_   (0,60, 0.9,1);
    //  if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    //  g->GetYaxis()->SetRangeUser(0.95,1);
    //  cms->SetY(1.00125);
    //  era->SetY(1.002);
    //  c->SetName((std::string(c->GetName())+"_0p95").c_str());
    //  if (save) save_plots(c, save_dir, formats, remove_prelim_label);
  }

  

}
