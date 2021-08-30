#include "common_functions.h"

void Approval_plots_2017_Data() {
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  //gROOT->SetStyle("Plain");
  TFile *f; TCanvas *c; TArrow *arr; TGaxis* axis; TGraphAsymmErrors* g; TH1D* h;
  
  bool save = 0;
  int remove_prelim_label = 0;
  //std::string save_dir = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2017_June/PreApproval/";
  //std::string save_dir = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2017_Aug/SpokesPersonApproved/";
  std::string save_dir = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2017_Aug/Approved/";
  std::vector<std::string> formats = { ".png", ".eps", ".root", ".C", ".pdf" };
  //std::vector<std::string> formats = { ".png" };
  
  bool delay        = 0;
  bool efficiency   = 0;
  bool aug_delay    = 1;
  bool aug_clu_inst = 0;
  bool aug_clu_dist = 0;
  bool aug_eff      = 0;

  if (delay) {
    
    // -------------------------------------------------------------
    //                   HitEfficiency vs Delay

    // Case 1 Timing
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/Approval_2017_Aug_PreApproval_Jul18ScanResults.root");
    // Layer 1-2
    c = (TCanvas*)f->Get("HitEfficiency_vs_Delay/Layers_2017Jun22_dac86_prt46");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(0,18);
    g->GetYaxis()->SetRangeUser(0,1);
    modify_legend(c, "", 0.4,0.6, 0.20,0.35);
    c->Draw();
    prelim_lat_(0,18, 0,1, 0);
    era_lat_   (0,18, 0,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // Case 2 Timing
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/Approval_2017_Aug_PreApproval_Jun22ScanResults.root");
    // Layer 3-4
    c = (TCanvas*)f->Get("HitEfficiency_vs_Delay/Layers_2017Jun22_dac66_prt31");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(-7,19);
    g->GetYaxis()->SetRangeUser(0,1);
    remove_points(c, 0, 7,7);
    remove_points(c, 0, 5,5);
    remove_points(c, 1, 7,7);
    remove_points(c, 1, 5,5);
    modify_legend(c, "", 0.4,0.6, 0.20,0.35);
    c->Draw();
    prelim_lat_(-7,19, 0,1, 0);
    era_lat_   (-7,19, 0,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // Disk 1-3
    c = (TCanvas*)f->Get("HitEfficiency_vs_Delay/Disks_2017Jun22_dac66_prt31");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(-7,19);
    g->GetYaxis()->SetRangeUser(0.8,1);
    //remove_plot(c, 3);
    //remove_plot(c, 2);
    remove_points(c, 0, 7,7);
    remove_points(c, 0, 5,5);
    remove_points(c, 1, 7,7);
    remove_points(c, 1, 5,5);
    remove_points(c, 2, 7,7);
    remove_points(c, 2, 5,5);
    modify_legend(c, "", 0.4,0.6, 0.15,0.35);
    c->Draw();
    prelim_lat_(-7,19, 0.8,1, 0);
    era_lat_   (-7,19, 0.8,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    
  }

  if (efficiency) {
    //f = TFile::Open("Janos_PHM/PHM_PHASE1_out/HitEffMonitoring_StartupRuns/2_1.root");
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/Approval_2017_Aug_PreApproval.root");
    

    // -------------------------------------------------------------
    //              HitEfficiency vs Layers/Disks
  
    c = (TCanvas*)f->Get("HitEfficiency_vs_LayersDisks/HitEfficiency_vs_LayersDisks;1");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetYaxis()->SetRangeUser(0.95,1);
    h->GetYaxis()->SetNdivisions(505);
    c->Draw();
    prelim_lat_(0.5,10.5, 0.95,1, 0);
    era_lat_(0.5,10.5, 0.95,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // -------------------------------------------------------------
    //              HitEfficiency vs InstLumi

    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/LayersDisks_2017Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(6,18);
    g->GetYaxis()->SetRangeUser(0.9,1);
    c->Draw();
    modify_legend(c, "", 0.4, 0.6, 0.1, 0.45);
    prelim_lat_(6,18, 0.9,1, 0);
    era_lat_   (6,18, 0.9,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // -------------------------------------------------------------
    //              HitEfficiency vs Pile-Up

    c = (TCanvas*)f->Get("HitEfficiency_vs_Pileup/LayersDisks_2017Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(16,50);
    g->GetYaxis()->SetRangeUser(0.9,1);
    c->Draw();
    modify_legend(c, "", 0.4, 0.6, 0.1, 0.45);
    prelim_lat_(16,50, 0.9,1, 0);
    era_lat_   (16,50, 0.9,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

  }

  if (aug_delay) {
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/Approval_2017_Aug_Aug03DelayScan.root");

    //    // Hit Efficiency
    //    // Layer 1-4
    //    c = (TCanvas*)f->Get("HitEfficiency_vs_Delay/Layers_2017Aug03_dac91_prt48");
    //    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    //    g->GetXaxis()->SetRangeUser(0,15);
    //    g->GetYaxis()->SetRangeUser(0.8,1);
    //    modify_legend(c, "", 0.4,0.6, 0.10,0.35);
    //    c->Draw();
    //    //fit_sigmoid_functions_(c,0,3);
    //    TF1* fit = new TF1("l1_fit", "[0]+[1]*x+[2]/(1+exp(([3]-x)/[4]))",0,15);
    //    fit->SetParLimits(0,0,1);
    //    fit->SetParLimits(1,-1,1);
    //    fit->SetParameter(2,-1);
    //    fit->SetParameter(3,15);
    //    fit->SetParameter(4,4);
    //    fit->SetLineColor(g->GetLineColor());
    //    g->Fit("l1_fit","RM");
    //    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
    //    fit = new TF1("l2_fit", "[0]+[1]*x+[2]/(1+exp((x-[3])/[4]))",0,15);
    //    fit->SetParLimits(0,0,1);
    //    fit->SetParLimits(1,0,0.0007);
    //    fit->SetParameter(2,-0.5);
    //    fit->SetParLimits(2,-0.8,0);
    //    fit->SetParameter(3,-5);
    //    fit->SetParLimits(3,-10,-3);
    //    fit->SetParameter(4,0.5);
    //    fit->SetParLimits(4,0,1.3);
    //    fit->SetLineColor(g->GetLineColor());
    //    g->Fit("l2_fit","RM");
    //    prelim_lat_(0,15, 0.8,1, 0);
    //    era_lat_   (0,15, 0.8,1);
    //    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    //    // Disk 1-3
    //    c = (TCanvas*)f->Get("HitEfficiency_vs_Delay/Disks_2017Aug03_dac91_prt48");
    //    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    //    g->GetXaxis()->SetRangeUser(0,15);
    //    g->GetYaxis()->SetRangeUser(0.9,1);
    //    modify_legend(c, "", 0.4,0.6, 0.15,0.35);
    //    c->Draw();
    //    prelim_lat_(0,15, 0.9,1, 0);
    //    era_lat_   (0,15, 0.9,1);
    //    if (save) save_plots(c, save_dir, formats, remove_prelim_label);


    // Size
    // Layer 1-4
    c = (TCanvas*)f->Get("AvgOnTrkCluSize_vs_Delay/Layers_2017Aug03_dac91_prt48");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(0,15);
    h->GetYaxis()->SetRangeUser(0,5);
    modify_legend(c, "", 0.4,0.6, 0.10,0.35);
    c->Draw();
    draw_straight_lines_(c,0,1);
    prelim_lat_(0,15, 0,5, 0);
    era_lat_   (0,15, 0,5);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    //    // Disk 1-3
    //    c = (TCanvas*)f->Get("AvgOnTrkCluSize_vs_Delay/Disks_2017Aug03_dac91_prt48");
    //    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    //    h->GetXaxis()->SetRangeUser(0,15);
    //    h->GetYaxis()->SetRangeUser(2,2.7);
    //    modify_legend(c, "", 0.4,0.6, 0.15,0.35);
    //    c->Draw();
    //    prelim_lat_(0,15, 2,2.7, 0);
    //    era_lat_   (0,15, 2,2.7);
    //    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
  }

  if (aug_clu_inst) {
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/HitEffMonitoring_Fill6061.root");

    // InstLumi
    c = (TCanvas*)f->Get("AvgOnCluSize_vs_InstLumi/LayersDisks_2017Data");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(7,18);
    h->GetYaxis()->SetRangeUser(0,5);
    modify_legend(c, "Fill 6061", 0.4,0.6, 0.10,0.35);
    remove_plot(c, 6); remove_plot(c, 5); remove_plot(c, 4);
    c->Draw();
    prelim_lat_(7,18, 0,5, 0);
    era_lat_   (7,18, 0,5);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    c = (TCanvas*)f->Get("AvgOnCluSizeX_vs_InstLumi/LayersDisks_2017Data");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(7,18);
    h->GetYaxis()->SetRangeUser(0,3);
    modify_legend(c, "Fill 6061", 0.4,0.6, 0.10,0.35);
    remove_plot(c, 6); remove_plot(c, 5); remove_plot(c, 4);
    c->Draw();
    prelim_lat_(7,18, 0,3, 0);
    era_lat_   (7,18, 0,3);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    c = (TCanvas*)f->Get("AvgOnCluSizeY_vs_InstLumi/LayersDisks_2017Data");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(7,18);
    h->GetYaxis()->SetRangeUser(0,5);
    modify_legend(c, "Fill 6061", 0.4,0.6, 0.10,0.35);
    remove_plot(c, 6); remove_plot(c, 5); remove_plot(c, 4);
    c->Draw();
    prelim_lat_(7,18, 0,5, 0);
    era_lat_   (7,18, 0,5);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    c = (TCanvas*)f->Get("AvgOnCluChargeNorm_vs_InstLumi/LayersDisks_2017Data");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(7,18);
    h->GetYaxis()->SetRangeUser(0,30);
    modify_legend(c, "Fill 6061", 0.4,0.6, 0.10,0.35);
    remove_plot(c, 6); remove_plot(c, 5); remove_plot(c, 4);
    c->Draw();
    prelim_lat_(7,18, 0,30, 0);
    era_lat_   (7,18, 0,30);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

  }

  if (aug_clu_dist) {
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/HitEffMonitoring_Fill6061.root");

    // Distributions
    c = (TCanvas*)f->Get("OnCluSize/Layers_TBMResetBGo14");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetYaxis()->SetRangeUser(0,0.4);
    modify_legend(c, "Fill 6061", 0.5,0.7, 0.6,0.85);
    add_mean(c, 4);
    c->Draw();
    prelim_lat_(-0.5,20.5, 0,0.4, 0);
    era_lat_   (-0.5,20.5, 0,0.4);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("OnCluSize/Disks_TBMResetBGo14");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(-0.5,10.5);
    h->GetYaxis()->SetRangeUser(0,0.5);
    modify_legend(c, "Fill 6061", 0.5,0.7, 0.65,0.85);
    add_mean(c, 3);
    c->Draw();
    prelim_lat_(-0.5,10.5, 0,0.5, 0);
    era_lat_   (-0.5,10.5, 0,0.5);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    c = (TCanvas*)f->Get("OnCluSizeX/Layers_TBMResetBGo14");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(-0.5,10.5);
    h->GetYaxis()->SetRangeUser(0,0.8);
    modify_legend(c, "Fill 6061", 0.5,0.7, 0.6,0.85);
    add_mean(c, 4);
    c->Draw();
    prelim_lat_(-0.5,10.5, 0,0.8, 0);
    era_lat_   (-0.5,10.5, 0,0.8);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("OnCluSizeX/Disks_TBMResetBGo14");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(-0.5,10.5);
    h->GetYaxis()->SetRangeUser(0,0.8);
    modify_legend(c, "Fill 6061", 0.5,0.7, 0.65,0.85);
    add_mean(c, 3);
    c->Draw();
    prelim_lat_(-0.5,10.5, 0,0.8, 0);
    era_lat_   (-0.5,10.5, 0,0.8);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    c = (TCanvas*)f->Get("OnCluSizeY/Layers_TBMResetBGo14");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetYaxis()->SetRangeUser(0,0.5);
    modify_legend(c, "Fill 6061", 0.5,0.7, 0.6,0.85);
    add_mean(c, 4);
    c->Draw();
    prelim_lat_(-0.5,20.5, 0,0.5, 0);
    era_lat_   (-0.5,20.5, 0,0.5);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("OnCluSizeY/Disks_TBMResetBGo14");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(-0.5,10.5);
    h->GetYaxis()->SetRangeUser(0,0.8);
    modify_legend(c, "Fill 6061", 0.5,0.7, 0.65,0.85);
    add_mean(c, 3);
    c->Draw();
    prelim_lat_(-0.5,10.5, 0,0.8, 0);
    era_lat_   (-0.5,10.5, 0,0.8);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    c = (TCanvas*)f->Get("OnCluChargeNorm/Layers_TBMResetBGo14");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(0,100);
    h->GetYaxis()->SetRangeUser(0,0.1);
    modify_legend(c, "Fill 6061", 0.5,0.7, 0.6,0.85);
    add_mpv_fit(c, 4);
    c->Draw();
    prelim_lat_(0,100, 0,0.1, 0);
    era_lat_   (0,100, 0,0.1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("OnCluChargeNorm/Disks_TBMResetBGo14");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetXaxis()->SetRangeUser(0,100);
    h->GetYaxis()->SetRangeUser(0,0.1);
    modify_legend(c, "Fill 6061", 0.5,0.7, 0.65,0.85);
    add_mpv_fit(c, 3);
    c->Draw();
    prelim_lat_(0,100, 0,0.1, 0);
    era_lat_   (0,100, 0,0.1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

  }

  if (aug_eff) {
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/Approval_2017_Aug_PreApproval_HighLumiDataOnly.root ");

    // -------------------------------------------------------------
    //                HitEfficiency vs Layers/Disks

    c = (TCanvas*)f->Get("HitEfficiency_vs_LayersDisks/HitEfficiency_vs_LayersDisks;1");
    h = (TH1D*)c->GetListOfPrimitives()->At(0);
    h->GetYaxis()->SetRangeUser(0.95,1);
    h->GetYaxis()->SetNdivisions(505);
    c->Draw();
    TLatex* lat = new TLatex(3, 0.975, "Average inst. lumi. = 1.05 #times 10^{34} cm^{-2}s^{-1}");
    lat->SetTextSize(0.03);
    lat->Draw("SAME");
    prelim_lat_(0.5,10.5, 0.95,1, 0);
    era_lat_(0.5,10.5, 0.95,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // -------------------------------------------------------------
    //                   HitEfficiency vs InstLumi

    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/LayersDisks_2017Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(6,18);
    g->GetYaxis()->SetRangeUser(0.9,1);
    c->Draw();
    modify_legend(c, "", 0.4, 0.6, 0.1, 0.45);
    prelim_lat_(6,18, 0.9,1, 0);
    era_lat_   (6,18, 0.9,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // -------------------------------------------------------------
    //                  HitEfficiency vs Pile-Up

    c = (TCanvas*)f->Get("HitEfficiency_vs_Pileup/LayersDisks_2017Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(14,50);
    g->GetYaxis()->SetRangeUser(0.9,1);
    c->Draw();
    modify_legend(c, "", 0.4, 0.6, 0.1, 0.45);
    prelim_lat_(14,50, 0.9,1, 0);
    era_lat_   (14,50, 0.9,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // -------------------------------------------------------------
    //                     HitEfficiency vs BX

    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/HitEffMonitoring_Fill6061.root");

    c = (TCanvas*)f->Get("HitEfficiency_vs_BunchCrossing12/LayersDisks_2017Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(0,3600);
    g->GetYaxis()->SetRangeUser(0.95,1);
    g->GetYaxis()->SetTitle("Hit Efficiency / 12 Bunches");
    c->Draw();
    remove_plot(c, 6); remove_plot(c, 5); remove_plot(c, 4);
    modify_legend(c, "Fill 6061", 0.4, 0.6, 0.20, 0.45);
    prelim_lat_(0,3600, 0.95,1, 0);
    era_lat_   (0,3600, 0.95,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    c = (TCanvas*)f->Get("HitEfficiency_vs_BunchCrossing5/LayersDisks_2017Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(0,550);
    g->GetYaxis()->SetRangeUser(0.95,1);
    g->GetYaxis()->SetTitle("Hit Efficiency / 5 Bunches");
    c->Draw();
    remove_plot(c, 6); remove_plot(c, 5); remove_plot(c, 4);
    modify_legend(c, "Fill 6061", 0.4, 0.6, 0.20, 0.45);
    prelim_lat_(0,550, 0.95,1, 0);
    era_lat_   (0,550, 0.95,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    
  }
}
