#include "common_functions.h"

void Approval_plots_Run2_Phase1() {
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  //gROOT->SetStyle("Plain");
  TFile *f; TCanvas *c; TArrow *arr; TGaxis* axis; TGraphAsymmErrors* g; TH1D* h;
  
  bool save = 1;
  int remove_prelim_label = 0;
  //std::string save_dir = "Plots/Approved_Plots/2018_May/Approved/";
  //std::string save_dir = "Plots/Approved_Plots/2018_July/PreApproval2/";
  std::string save_dir = "Plots/Approved_Plots/Papers/Pixel_Phase1/Paper_PreApproval_Take2/";
  //std::vector<std::string> formats = { ".png", ".eps", ".root", ".C", ".pdf" };
  std::vector<std::string> formats = { ".png" };
  
  bool efficiency      = 1;
  bool history         = 0;

  if (efficiency) {

    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/NewEffStudy_2017_ReReco_run6.root");
    
    // BPix - 2017
    c = (TCanvas*)f->Get("NewHitEfficiency_vs_InstLumi/Layers_ALCARECOTight");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(0,16);
    g->GetYaxis()->SetRangeUser(0.8,1);
    c->Draw();
    rename_legend(c, "2017 Data");
    prelim_lat_(0,16, 0.8,1, 0);
    era2_lat_  (0,16, 0.8,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    // FPix - 2017
    //c = (TCanvas*)f->Get("NewHitEfficiency_vs_InstLumi/DisksRings_ALCARECOTight");
    //g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    //g->GetXaxis()->SetRangeUser(4,16);
    //g->GetYaxis()->SetRangeUser(0.95,1);
    //c->Draw();
    //modify_legend(c, "2017 Data",0.35,0.55,0.15,0.50);
    //prelim_lat_(4,16, 0.95,1, 0);
    //era2_lat_  (4,16, 0.95,1);
    //if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    // FPix2 - 2017
    c = (TCanvas*)f->Get("NewHitEfficiency_vs_InstLumi/FPixRadius_ALCARECOTight");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(4,16);
    g->GetYaxis()->SetRangeUser(0.95,1);
    c->Draw();
    rename_legend(c, "2017 Data");
    prelim_lat_(4,16, 0.95,1, 0);
    era2_lat_  (4,16, 0.95,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // HitEfficiency vs Eta - 2017
    c = (TCanvas*)f->Get("NewHitEfficiency_vs_TrackEta/LayersDisks_ALCARECOTight");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(-2.4,2.4);
    g->GetYaxis()->SetRangeUser(0.8,1);
    c->SetLogx(0);
    c->Draw();
    remove_points(c, 0,  0, 0);
    remove_points(c, 0, 48,48);
    remove_points(c, 1,  0, 0);
    remove_points(c, 1, 47,47);
    remove_points(c, 2,  0, 1);
    remove_points(c, 2, 39,40);
    remove_points(c, 3,  0, 0);
    remove_points(c, 3, 32,32);
    remove_points(c, 4,  0, 0);
    remove_points(c, 4, 12,16);
    remove_points(c, 4, 24,24);
    remove_points(c, 5,  0, 0);
    remove_points(c, 5, 11,13);
    remove_points(c, 6,  0, 0);
    remove_points(c, 6,  8,11);
    remove_points(c, 6, 15,15);
    rename_legend(c, "2017 Data");
    prelim_lat_(-2.5,2.5, 0.8,1, 0);
    era2_lat_   (-2.5,2.5, 0.8,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/NewEffStudy_2017_2018_ReReco_run5.root");

    // BPix - 2018
    c = (TCanvas*)f->Get("NewHitEfficiency_vs_InstLumi/Layers_2018Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(0,18);
    g->GetYaxis()->SetRangeUser(0.8,1);
    c->Draw();
    rename_legend(c, "2018 Data");
    prelim_lat_(0,18, 0.8,1, 0);
    era2_lat_  (0,18, 0.8,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    // FPix - 2018
    //c = (TCanvas*)f->Get("NewHitEfficiency_vs_InstLumi/DisksRings_2018Data");
    //g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    //g->GetXaxis()->SetRangeUser(0,18);
    //g->GetYaxis()->SetRangeUser(0.95,1);
    //c->Draw();
    //modify_legend(c, "2018 Data",0.35,0.55,0.15,0.50);
    //prelim_lat_(0,18, 0.95,1, 0);
    //era2_lat_  (0,18, 0.95,1);
    //if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    // FPix2 - 2018
    c = (TCanvas*)f->Get("NewHitEfficiency_vs_InstLumi/FPixRadius_2018Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(0,18);
    g->GetYaxis()->SetRangeUser(0.95,1);
    c->Draw();
    rename_legend(c, "2018 Data");
    prelim_lat_(0,18, 0.95,1, 0);
    era2_lat_  (0,18, 0.95,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // HitEfficiency vs Eta - 2018
    c = (TCanvas*)f->Get("NewHitEfficiency_vs_TrackEta/LayersDisks_2018Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetRangeUser(-2.4,2.4);
    g->GetYaxis()->SetRangeUser(0.8,1);
    c->SetLogx(0);
    c->Draw();
    remove_points(c, 0,  0, 0);
    remove_points(c, 0, 48,48);
    remove_points(c, 1,  0, 0);
    remove_points(c, 1, 48,48);
    remove_points(c, 2,  0, 0);
    remove_points(c, 2, 40,40);
    //remove_points(c, 3,  0, 0);
    remove_points(c, 3, 33,33);
    remove_points(c, 4, 15,19);
    //remove_points(c, 4, 14,17);
    remove_points(c, 5, 12,13);
    remove_points(c, 6, 10,13);
    rename_legend(c, "2018 Data");
    prelim_lat_(-2.5,2.5, 0.8,1, 0);
    era2_lat_   (-2.5,2.5, 0.8,1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
  }

  if (history) {
    
    f = TFile::Open("Janos_PHM/PHM_PHASE1_out/ClusterProperties_2017_2018_ALCARECO_run3.root");

    // -------------------------------------------------------------
    //             Cluster Properties History Plots

    // BPix
    c = (TCanvas*)f->Get("AvgOnCluChargeNorm_vs_IntLumi2017/Layers_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(10,32);
    modify_legend(c, "", 0.29,0.49, 0.12,0.36);
    add_labels_Phase1(c); c->Draw();
    prelim_lat_(0,120, 10,32, 0);
    era_lat_   (0,120, 10,32);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSize_vs_IntLumi2017/Layers_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(2,6);
    modify_legend(c, "", 0.29,0.49, 0.12,0.36);
    add_labels_Phase1(c); c->Draw();
    prelim_lat_(0,120, 2,6, 0);
    era_lat_   (0,120, 2,6);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSizeX_vs_IntLumi2017/Layers_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(1.0,2.6);
    modify_legend(c, "", 0.29,0.49, 0.12,0.36);
    add_labels_Phase1(c); c->Draw();
    prelim_lat_(0,120, 1.0,2.6, 0);
    era_lat_   (0,120, 1.0,2.6);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSizeY_vs_IntLumi2017/Layers_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(1,5);
    modify_legend(c, "", 0.29,0.49, 0.12,0.36);
    add_labels_Phase1(c); c->Draw();
    prelim_lat_(0,120, 1,5, 0);
    era_lat_   (0,120, 1,5);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    
    // Ring1
    c = (TCanvas*)f->Get("AvgOnCluChargeNorm_vs_IntLumi2017/Ring1Disks_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(12,28);
    remove_points(c, 0,  9, 9);
    remove_points(c, 1,  9, 9);
    remove_points(c, 2,  9, 9);
    modify_legend(c, "", 0.27,0.47, 0.18,0.36);
    add_labels_Phase1_fpix(c); c->Draw();
    prelim_lat_(0,120, 12,28, 0);
    era_lat_   (0,120, 12,28);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSize_vs_IntLumi2017/Ring1Disks_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(2,3);
    remove_points(c, 0,  9, 9);
    remove_points(c, 1,  9, 9);
    remove_points(c, 2,  9, 9);
    modify_legend(c, "", 0.27,0.47, 0.18,0.36);
    add_labels_Phase1_fpix(c); c->Draw();
    prelim_lat_(0,120, 2,3, 0);
    era_lat_   (0,120, 2,3);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSizeX_vs_IntLumi2017/Ring1Disks_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(1.4,2.1);
    remove_points(c, 0,  9, 9);
    remove_points(c, 1,  9, 9);
    remove_points(c, 2,  9, 9);
    modify_legend(c, "", 0.27,0.47, 0.18,0.36);
    add_labels_Phase1_fpix(c); c->Draw();
    prelim_lat_(0,120, 1.4,2.1, 0);
    era_lat_   (0,120, 1.4,2.1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSizeY_vs_IntLumi2017/Ring1Disks_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(1.2,2);
    remove_points(c, 0,  9, 9);
    remove_points(c, 1,  9, 9);
    remove_points(c, 2,  9, 9);
    modify_legend(c, "", 0.27,0.47, 0.18,0.36);
    add_labels_Phase1_fpix(c); c->Draw();
    prelim_lat_(0,120, 1.2,2, 0);
    era_lat_   (0,120, 1.2,2);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

    // Ring1
    c = (TCanvas*)f->Get("AvgOnCluChargeNorm_vs_IntLumi2017/Ring2Disks_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(12,28);
    remove_points(c, 0,  9, 9);
    remove_points(c, 1,  9, 9);
    remove_points(c, 2,  9, 9);
    modify_legend(c, "", 0.27,0.47, 0.18,0.36);
    add_labels_Phase1_fpix(c); c->Draw();
    prelim_lat_(0,120, 12,28, 0);
    era_lat_   (0,120, 12,28);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSize_vs_IntLumi2017/Ring2Disks_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(2,3);
    remove_points(c, 0,  9, 9);
    remove_points(c, 1,  9, 9);
    remove_points(c, 2,  9, 9);
    modify_legend(c, "", 0.27,0.47, 0.18,0.36);
    add_labels_Phase1_fpix(c); c->Draw();
    prelim_lat_(0,120, 2,3, 0);
    era_lat_   (0,120, 2,3);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSizeX_vs_IntLumi2017/Ring2Disks_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(1.4,2.1);
    remove_points(c, 0,  9, 9);
    remove_points(c, 1,  9, 9);
    remove_points(c, 2,  9, 9);
    modify_legend(c, "", 0.27,0.47, 0.18,0.36);
    add_labels_Phase1_fpix(c); c->Draw();
    prelim_lat_(0,120, 1.4,2.1, 0);
    era_lat_   (0,120, 1.4,2.1);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSizeY_vs_IntLumi2017/Ring2Disks_10to12invnbHz");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,120);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(1.2,2);
    remove_points(c, 0,  9, 9);
    remove_points(c, 1,  9, 9);
    remove_points(c, 2,  9, 9);
    modify_legend(c, "", 0.27,0.47, 0.18,0.36);
    add_labels_Phase1_fpix(c); c->Draw();
    prelim_lat_(0,120, 1.2,2, 0);
    era_lat_   (0,120, 1.2,2);
    if (save) save_plots(c, save_dir, formats, remove_prelim_label);

  }
}
