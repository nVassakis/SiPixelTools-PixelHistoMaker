#include "common_functions.h"

void Approval_plots_2016_Data() {
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gROOT->SetStyle("Plain");
  TFile *f; TCanvas *c; TArrow *arr; TGaxis* axis; TGraphAsymmErrors* g; TH1D* h;
  
  bool save = 1;
  int remove_prelim_label = 0;
  std::string save_dir_march = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2016_March/PreApproval/";
  std::string save_dir_april = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2016_April/Approved/";
  std::string save_dir_july  = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2016_July/Approved/";
  std::string save_dir_2017_march  = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2017_March/PreApproval/";
  std::string save_dir_2017_may    = "/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2017_May/Approved/";
  std::vector<std::string> formats = { ".png", ".eps", ".root", ".C", ".pdf" };
  //std::vector<std::string> formats = { ".png" };
  
  bool instlumi    = 0; // 2016 March
  bool datavsmc    = 0; // 2016 April
  bool instlumiclu = 0;
  bool history     = 1; // 2016 April + 2017 May
  bool efficiency  = 0;
  bool hv          = 0; // 2016 July
  bool dyn_ineff   = 1; // 2016 July + 2017 March/May
  
  f = TFile::Open("Janos_PHM/PHM_out/2015_25ns_Data_NBunchesFixed.root"); // Old PromptReco Data plots (ReReco coming)
  
  if (instlumi) {
    // -------------------------------------------------------------
    //           HitEfficiency vs Instantaneous Luminosity
    //                      ( for Nbunches )
    
    // Layer 1
    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/SelectedNBx_Lay1_Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetTitle("Instantaneous Luminosity (#scale[0.8]{#times10^{33}cm^{-2}s^{-1}})");
    g->GetXaxis()->SetRangeUser(0,5.5);
    g->GetYaxis()->SetRangeUser(0.99,1);
    g->GetYaxis()->SetNdivisions(505);
    modify_legend(c, "Barrel Layer 1", 0.65, 0.85, 0.60, 0.85);
    remove_plot(c, 4);
    remove_points(c, 0, 0,11);
    remove_points(c, 1, 0,11);
    remove_points(c, 2, 15,15);
    remove_points(c, 2, 0,7);
    remove_points(c, 3, 4,4);
    remove_points(c, 3, 0,0);
    c->Draw();
    prelim_lat_(0,5.5, 0.99,1, 0);
    era_lat_(0,5.5, 0.99,1);
    if (save) save_plots(c, save_dir_march, formats, remove_prelim_label);
    
    // Layer 2
    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/SelectedNBx_Lay2_Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetTitle("Instantaneous Luminosity (#scale[0.8]{#times10^{33}cm^{-2}s^{-1}})");
    g->GetXaxis()->SetRangeUser(0,5.5);
    g->GetYaxis()->SetRangeUser(0.99,1);
    g->GetYaxis()->SetNdivisions(505);
    modify_legend(c, "Barrel Layer 2", 0.4, 0.6, 0.18, 0.43);
    remove_plot(c, 4);
    remove_points(c, 0, 0,11);
    remove_points(c, 1, 0,11);
    remove_points(c, 2, 15,15);
    remove_points(c, 2, 0,6);
    remove_points(c, 3, 4,4);
    remove_points(c, 3, 0,0);
    c->Draw();
    prelim_lat_(0,5.5, 0.99,1, 0);
    era_lat_(0,5.5, 0.99,1);
    if (save) save_plots(c, save_dir_march, formats, remove_prelim_label);
    
    // Layer 3
    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/SelectedNBx_Lay3_Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetTitle("Instantaneous Luminosity (#scale[0.8]{#times10^{33}cm^{-2}s^{-1}})");
    g->GetXaxis()->SetRangeUser(0,5.5);
    g->GetYaxis()->SetRangeUser(0.99,1);
    g->GetYaxis()->SetNdivisions(505);
    modify_legend(c, "Barrel Layer 3", 0.4, 0.6, 0.18, 0.43);
    remove_plot(c, 4);
    remove_points(c, 0, 0,11);
    remove_points(c, 1, 0,11);
    remove_points(c, 2, 15,15);
    remove_points(c, 2, 0,5);
    remove_points(c, 3, 4,4);
    remove_points(c, 3, 0,0);
    c->Draw();
    prelim_lat_(0,5.5, 0.99,1, 0);
    era_lat_(0,5.5, 0.99,1);
    if (save) save_plots(c, save_dir_march, formats, remove_prelim_label);
    
    // Disk 1
    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/SelectedNBx_Disk1_Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetTitle("Instantaneous Luminosity (#scale[0.8]{#times10^{33}cm^{-2}s^{-1}})");
    g->GetXaxis()->SetRangeUser(0,5.5);
    g->GetYaxis()->SetRangeUser(0.99,1);
    g->GetYaxis()->SetNdivisions(505);
    modify_legend(c, "Forward Disk 1", 0.4, 0.6, 0.18, 0.43);
    remove_plot(c, 4);
    remove_points(c, 0, 0,12);
    remove_points(c, 1, 0,8);
    remove_points(c, 2, 15,15);
    remove_points(c, 2, 0,6);
    remove_points(c, 3, 4,4);
    remove_points(c, 3, 0,0);
    c->Draw();
    prelim_lat_(0,5.5, 0.99,1, 0);
    era_lat_(0,5.5, 0.99,1);
    if (save) save_plots(c, save_dir_march, formats, remove_prelim_label);
    
    // Disk 2
    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/SelectedNBx_Disk2_Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    g->GetXaxis()->SetTitle("Instantaneous Luminosity (#scale[0.8]{#times10^{33}cm^{-2}s^{-1}})");
    g->GetXaxis()->SetRangeUser(0,5.5);
    g->GetYaxis()->SetRangeUser(0.99,1);
    g->GetYaxis()->SetNdivisions(505);
    modify_legend(c, "Forward Disk 2", 0.4, 0.6, 0.18, 0.43);
    remove_plot(c, 4);
    remove_points(c, 0, 0,12);
    remove_points(c, 1, 0,11);
    remove_points(c, 2, 15,15);
    remove_points(c, 2, 0,7);
    remove_points(c, 3, 4,4);
    remove_points(c, 3, 0,0);
    c->Draw();
    prelim_lat_(0,5.5, 0.99,1, 0);
    era_lat_(0,5.5, 0.99,1);
  }
  
  f->Close();
  f = TFile::Open("Janos_PHM/PHM_out/Approval_2016_April_PreApproval.root");
  
  if (datavsmc) {
    // -------------------------------------------------------------
    //                 Data vs MC Comparison
    
    // Norm Charge Layer 1-3
    //c = (TCanvas*)f->Get("OnCluChargeNorm/DatavsMC_Lay1");
    //c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mpv_fit(c, 3);
    //if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("OnCluChargeNorm/DatavsMC_Lay2");
    remove_plot(c, 2);
    c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mpv_fit(c, 2);
    if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    //c = (TCanvas*)f->Get("OnCluChargeNorm/DatavsMC_Lay3");
    //c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mpv_fit(c, 3);
    //if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    
    // Size Layer 1-3
    //c = (TCanvas*)f->Get("OnCluSize/DatavsMC_Lay1");
    //((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(0,0.3);
    //c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mean(c, 3);
    //if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("OnCluSize/DatavsMC_Lay2");
    remove_plot(c, 2);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,20);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetNdivisions(511);
    c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mean(c, 2);
    if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    //c = (TCanvas*)f->Get("OnCluSize/DatavsMC_Lay3");
    //c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mean(c, 3);
    //if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    
    // SizeX Layer 1-3
    //c = (TCanvas*)f->Get("OnCluSizeX/DatavsMC_Lay1");
    //c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mean(c, 3);
    //if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("OnCluSizeX/DatavsMC_Lay2");
    remove_plot(c, 2);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,10);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetNdivisions(511);
    c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mean(c, 2);
    if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    //c = (TCanvas*)f->Get("OnCluSizeX/DatavsMC_Lay3");
    //c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mean(c, 3);
    //if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    
    // SizeY Layer 1-3
    //c = (TCanvas*)f->Get("OnCluSizeY/DatavsMC_Lay1");
    //((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(0,0.3);
    //c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mean(c, 3);
    //if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    c = (TCanvas*)f->Get("OnCluSizeY/DatavsMC_Lay2");
    remove_plot(c, 2);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetNdivisions(511);
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,20);
    c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mean(c, 2);
    if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    //c = (TCanvas*)f->Get("OnCluSizeY/DatavsMC_Lay3");
    //c->Draw(); add_labels((TH1D*)c->GetListOfPrimitives()->At(0)); add_mean(c, 3);
    //if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
  }

  f->Close();
  f = TFile::Open("Janos_PHM/PHM_out/replot9_Approval_2017_April_PreApproval.root");
  
  if (instlumiclu) {
    // -------------------------------------------------------------
    //                    Instlumi Cluster Plots

    // Cluster on-track
    // Charge
    c = (TCanvas*)f->Get("OnCluChargeNormMPV_vs_InstLumi/LayersDisksOldNew_2016Data"); c->Draw();
    remove_plot(c, 7, 6); remove_plot(c, 6, 4); remove_plot(c, 5, 2); remove_plot(c, -1, 5, 1);
    rename_legend(c, ""); move_legend(c, 0.4, 0.4); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_InstLumi/", formats, remove_prelim_label);    
    // Size
    c = (TCanvas*)f->Get("AvgOnCluSize_vs_InstLumi/LayersDisksOldNew_2016Data"); c->Draw();
    remove_plot(c, 7, 6); remove_plot(c, 6, 4); remove_plot(c, 5, 2); remove_plot(c, -1, 5, 1);
    rename_legend(c, ""); move_legend(c, 0.4, 0.4); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_InstLumi/", formats, remove_prelim_label);
    // Size-X
    c = (TCanvas*)f->Get("AvgOnCluSizeX_vs_InstLumi/LayersDisksOldNew_2016Data"); c->Draw();
    remove_plot(c, 7, 6); remove_plot(c, 6, 4); remove_plot(c, 5, 2); remove_plot(c, -1, 5, 1);
    rename_legend(c, ""); move_legend(c, 0.4, 0.4); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_InstLumi/", formats, remove_prelim_label);    
    // Size-Y
    c = (TCanvas*)f->Get("AvgOnCluSizeY_vs_InstLumi/LayersDisksOldNew_2016Data"); c->Draw();
    remove_plot(c, 7, 6); remove_plot(c, 6, 4); remove_plot(c, 5, 2); remove_plot(c, -1, 5, 1);
    rename_legend(c, ""); move_legend(c, 0.4, 0.5); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_InstLumi/", formats, remove_prelim_label);

    // All clusters
    // Charge
    c = (TCanvas*)f->Get("AvgCluCharge_vs_InstLumi/LayersDisksOldNew_2016Data"); c->Draw();
    remove_plot(c, 7, 6); remove_plot(c, 6, 4); remove_plot(c, 5, 2); remove_plot(c, -1, 5, 1);
    rename_legend(c, ""); move_legend(c, 0.4, 0.4); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_InstLumi/", formats, remove_prelim_label);    
    // Size
    c = (TCanvas*)f->Get("AvgCluSize_vs_InstLumi/LayersDisksOldNew_2016Data"); c->Draw();
    remove_plot(c, 7, 6); remove_plot(c, 6, 4); remove_plot(c, 5, 2); remove_plot(c, -1, 5, 1);
    rename_legend(c, ""); move_legend(c, 0.4, 0.4); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_InstLumi/", formats, remove_prelim_label);
    // Size-X
    c = (TCanvas*)f->Get("AvgCluSizeX_vs_InstLumi/LayersDisksOldNew_2016Data"); c->Draw();
    remove_plot(c, 7, 6); remove_plot(c, 6, 4); remove_plot(c, 5, 2); remove_plot(c, -1, 5, 1);
    rename_legend(c, ""); move_legend(c, 0.4, 0.4); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_InstLumi/", formats, remove_prelim_label);    
    // Size-Y
    c = (TCanvas*)f->Get("AvgCluSizeY_vs_InstLumi/LayersDisksOldNew_2016Data"); c->Draw();
    remove_plot(c, 7, 6); remove_plot(c, 6, 4); remove_plot(c, 5, 2); remove_plot(c, -1, 5, 1);
    rename_legend(c, ""); move_legend(c, 0.4, 0.5); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_InstLumi/", formats, remove_prelim_label);
    
  }

  if (history) {
    // -------------------------------------------------------------
    //                    History Plots

    // On-track clusters
    // Old/New Modules
    c = (TCanvas*)f->Get("OnCluChargeNormMPV_vs_IntLumi/LayersDisksOld");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(8,28);
    ((TLatex*)c->GetListOfPrimitives()->At(7))->SetTitle("Run1 + Run2");
    modify_legend(c, "Old modules", 0.22, 0.42, 0.10, 0.34);
    add_years(c, 26); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    c = (TCanvas*)f->Get("OnCluChargeNormMPV_vs_IntLumiRunII/LayersNew");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(8,28);
    modify_legend(c, "New modules", 0.22, 0.42, 0.18, 0.34);
    add_year_Run2(c, 26); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);

    c = (TCanvas*)f->Get("AvgOnCluSize_vs_IntLumi/LayersDisksOld");
    ((TLatex*)c->GetListOfPrimitives()->At(7))->SetTitle("Run1 + Run2");
    modify_legend(c, "Old modules", 0.22, 0.42, 0.10, 0.34);
    add_years(c, 2.5); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSize_vs_IntLumiRunII/LayersNew");
    modify_legend(c, "New modules", 0.22, 0.42, 0.18, 0.34);
    add_year_Run2(c, 2.5); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    
    c = (TCanvas*)f->Get("AvgOnCluSizeX_vs_IntLumi/LayersDisksOld");
    ((TLatex*)c->GetListOfPrimitives()->At(7))->SetTitle("Run1 + Run2");
    modify_legend(c, "Old modules", 0.66, 0.86, 0.62, 0.86);
    add_years(c, 1.78, -0.0018); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSizeX_vs_IntLumiRunII/LayersNew");
    modify_legend(c, "New modules", 0.22, 0.42, 0.18, 0.34);
    add_year_Run2(c, 1.75, 0); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    
    c = (TCanvas*)f->Get("AvgOnCluSizeY_vs_IntLumi/LayersDisksOld");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(0,4.2);
    ((TLatex*)c->GetListOfPrimitives()->At(6))->SetY(1.025*4.2);
    ((TLatex*)c->GetListOfPrimitives()->At(7))->SetY(1.040*4.2);
    ((TLatex*)c->GetListOfPrimitives()->At(7))->SetTitle("Run1 + Run2");
    modify_legend(c, "Old modules", 0.22, 0.42, 0.10, 0.34);
    add_years(c, 2.0); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    c = (TCanvas*)f->Get("AvgOnCluSizeY_vs_IntLumiRunII/LayersNew");
    ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(0,4.2);
    ((TLatex*)c->GetListOfPrimitives()->At(4))->SetY(1.025*4.2);
    ((TLatex*)c->GetListOfPrimitives()->At(5))->SetY(1.040*4.2);
    modify_legend(c, "New modules", 0.22, 0.42, 0.18, 0.34);
    add_year_Run2(c, 2.0); c->Draw();
    if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    
    //++  // On-track clusters
    //++  c = (TCanvas*)f->Get("OnCluChargeNormMPV_vs_IntLumi/LayersDisksOldNew");
    //++  ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(8,28);
    //++  add_years(c, 26); c->Draw();
    //++  if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    //++  c = (TCanvas*)f->Get("AvgOnCluSize_vs_IntLumi/LayersDisksOldNew");
    //++  add_years(c, 2.5); c->Draw();
    //++  if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    //++  c = (TCanvas*)f->Get("AvgOnCluSizeX_vs_IntLumi/LayersDisksOldNew");
    //++  add_years(c, 1.75, -0.0009); c->Draw();
    //++  if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    //++  c = (TCanvas*)f->Get("AvgOnCluSizeY_vs_IntLumi/LayersDisksOldNew");
    //++  add_years(c, 2.0); c->Draw();
    //++  if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    //++  
    //++  // All clusters
    //++  c = (TCanvas*)f->Get("AvgCluCharge_vs_IntLumi/LayersDisksOldNew");
    //++  add_years(c, 45, -0.18); c->Draw();
    //++  if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    //++  c = (TCanvas*)f->Get("AvgCluSize_vs_IntLumi/LayersDisksOldNew");
    //++  add_years(c, 2.9); c->Draw();
    //++  if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    //++  c = (TCanvas*)f->Get("AvgCluSizeX_vs_IntLumi/LayersDisksOldNew");
    //++  ((TH1D*)c->GetListOfPrimitives()->At(0))->GetYaxis()->SetRangeUser(1.2,2.5);
    //++  add_years(c, 1.7); c->Draw();
    //++  if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    //++  c = (TCanvas*)f->Get("AvgCluSizeY_vs_IntLumi/LayersDisksOldNew");
    //++  add_years(c, 2.0); c->Draw();
    //++  if (save) save_plots(c, save_dir_2017_may+"Clu_History/", formats, remove_prelim_label);
    
  }
  
  if (efficiency) {
    // -------------------------------------------------------------
    //                    Efficiency Plots
    
    // Days
    c = (TCanvas*)f->Get("HitEfficiency_vs_Days/LayersDisks_2015Data");
    ((TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetNdivisions(505);
    add_labels((TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0), 0);
    rename_legend(c, ""); c->Draw();
    if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    
    // BunchCrossing
    // Layer 1 - PU [12,15]
    c = (TCanvas*)f->Get("HitEfficiency_vs_BunchCrossing60/SelectedNBx_pu12to15_Lay1_2015Data_ForApproval");
    rename_legend(c, "Layer 1, #LTpu#GT #subset [12,15]"); c->Draw();
    if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    // Layer 2 - PU [12,15]
    c = (TCanvas*)f->Get("HitEfficiency_vs_BunchCrossing60/SelectedNBx_pu12to15_Lay2_2015Data_ForApproval");
    rename_legend(c, "Layer 2, #LTpu#GT #subset [12,15]"); c->Draw();
    if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    //  Layer 3 - PU [12,15]
    c = (TCanvas*)f->Get("HitEfficiency_vs_BunchCrossing60/SelectedNBx_pu12to15_Lay3_2015Data_ForApproval");
    rename_legend(c, "Layer 3, #LTpu#GT #subset [12,15]"); c->Draw();
    if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    
    // Pileup (Already Approved)
    //c = (TCanvas*)f->Get("HitEfficiency_vs_Pileup/LayersDisks_Data2015");
    //g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    //g->GetXaxis()->SetRangeUser(0,25);
    //g->GetYaxis()->SetRangeUser(0.98,1);
    //c->Draw();
    //add_labels(g);
    //era_and_prelim_lat(0, 25, 0.98, 1, 1);
    //if (save) save_plots(c, save_dir_april, formats, remove_prelim_label);
    
  }

  if (hv) {
    // -------------------------------------------------------------
    //                  HV Bias Scan plots
    f = TFile::Open("Janos_PHM/PHM_out/HV20.root");

    // Full layers
    // Efficiency
    c = (TCanvas*)f->Get("HitEfficiency_vs_BiasVoltage/LayersDisks_HV20");
    c->Draw(); rename_legend(c, ""); move_legend(c, 0.5, 0.5);
    remove_plot(c, 4);
    remove_plot(c, 3);
    std::vector<TH2D*> parents;
    parents.push_back((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_Lay1"));
    parents.push_back((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_Lay2"));
    parents.push_back((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_Lay3"));
    //parents.push_back((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_Disk1"));
    //parents.push_back((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_Disk2"));
    add_turnon_fits_(c, parents);
    add_labels((TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0), 0);
    if (save) save_plots(c, save_dir_july, formats, remove_prelim_label);

    // MPV
    c = (TCanvas*)f->Get("NormOnTrkCluChargeMPV_vs_BiasVoltage/LayersDisks_HV20");
    c->Draw(); rename_legend(c, ""); move_legend(c, 0.5, 0.5); //add_mpvturnon_fits_(c, 5);
    remove_plot(c, 4);
    remove_plot(c, 3);
    add_labels((TH1D*)c->GetListOfPrimitives()->At(0), 0);
    if (save) save_plots(c, save_dir_july, formats, remove_prelim_label);

    // Size
    c = (TCanvas*)f->Get("AvgOnTrkCluSize_vs_BiasVoltage/LayersDisks_HV20");
    c->Draw(); rename_legend(c, ""); move_legend(c, 0.5, 0.5);
    remove_plot(c, 4);
    remove_plot(c, 3);
    add_labels((TH1D*)c->GetListOfPrimitives()->At(0), 0);
    if (save) save_plots(c, save_dir_july, formats, remove_prelim_label);

    //  // One HV group
    //  // Efficiency
    //  c = (TCanvas*)f->Get("HitEfficiency_vs_BiasVoltage/HVGroupsScanned_HV20");
    //  ((TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,200);
    //  c->Draw(); move_legend(c, 0.5, 0.5); rename_legend(c, "One sector");
    //  std::vector<TH2D*> parents2;
    //  parents2.push_back((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/L1OneHVGrp_HV20"));
    //  parents2.push_back((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/L3OneHVGrp_HV20"));
    //  parents2.push_back((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/D1OneHVGrp_HV20"));
    //  add_turnon_fits_(c, parents2);
    //  add_labels((TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0));
    //  if (save) save_plots(c, save_dir_july, formats, remove_prelim_label);
    //  
    //  // Turnon plot
    //  TH2D* l1_2d = (TH2D*)((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_L1OneHVGrp"))->Clone();
    //  TH2D* l2_2d = (TH2D*)((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_Lay2"))->Clone();
    //  TH2D* l3_2d = (TH2D*)((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_L3OneHVGrp"))->Clone();
    //  TH2D* d1_2d = (TH2D*)((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_D1OneHVGrp"))->Clone();
    //  TH2D* d2_2d = (TH2D*)((TH2D*)f->Get("HitEfficiency_vs_BiasVoltage/ValidHit_vs_BiasVoltage/HV20_Disk2"))->Clone();
    //  f = TFile::Open("/afs/cern.ch/user/j/jkarancs/public/Approved_Plots/2013/Other_Plot_Formats/vturnon_totlumi.root");
    //  TCanvas *c = (TCanvas*)((TCanvas*)f->Get("vturnon_totlumi"))->Clone();
    //  c->SetName("VBias1PctIneff_vs_TotalIntLumi");
    //  f->Close();
    //  TH1D* l1 = extend((TH1D*)c->GetListOfPrimitives()->At(1));
    //  TH1D* l2 = extend((TH1D*)c->GetListOfPrimitives()->At(2));
    //  TH1D* l3 = extend((TH1D*)c->GetListOfPrimitives()->At(3));
    //  TH1D* d1 = extend((TH1D*)c->GetListOfPrimitives()->At(4));
    //  TH1D* d2 = extend((TH1D*)c->GetListOfPrimitives()->At(5));
    //  TLatex* cms = (TLatex*)c->GetListOfPrimitives()->At(7);
    //  l1->GetXaxis()->SetTitle("Total Int. Luminosity - 2010-2016 (fb^{-1})");
    //  l1->GetYaxis()->SetTitle("U_{Bias, 1% Ineff} (V)");
    //  l1->GetXaxis()->SetRangeUser(0, 35);
    //  l1->SetTitle("");
    //  cms->SetTitle("CMS #scale[0.8]{#font[52]{Preliminary}}");
    //  cms->SetX(0); 
    //  cms->SetY(75+75.0/40);
    //  // Add new scan points
    //  // HV20
    //  double intlumi = 29.5 + 4.2;
    //  l1->SetBinContent(l1->FindBin(intlumi), vturnon_(fit_turnon_improved_(l1_2d)));
    //  l1->SetBinError  (l1->FindBin(intlumi), 0);
    //  l2->SetBinContent(l2->FindBin(intlumi), vturnon_(fit_turnon_improved_(l2_2d)));
    //  l2->SetBinError  (l2->FindBin(intlumi), 0);
    //  l3->SetBinContent(l3->FindBin(intlumi), vturnon_(fit_turnon_improved_(l3_2d)));
    //  l3->SetBinError  (l3->FindBin(intlumi), 0);
    //  //d1->SetBinContent(d1->FindBin(intlumi), vturnon_(fit_turnon_improved_(d1_2d)));
    //  //d1->SetBinError  (d1->FindBin(intlumi), 0);
    //  //d2->SetBinContent(d2->FindBin(intlumi), vturnon_(fit_turnon_improved_(d2_2d)));
    //  //d2->SetBinError  (d2->FindBin(intlumi), 0);
    //  TLegend *leg = (TLegend*)c->GetListOfPrimitives()->At(6);
    //  leg->SetX1(10); leg->SetX2(20);// leg->SetY1(0.65); leg->SetY2(0.85);
    //  draw_line(29.5, 29.5, 0, 75, 2, 7);
    //  draw_lat_(25, 77, "Run I",  1, 0.04, 0, 31);
    //  draw_lat_(30, 77, "Run II", 1, 0.04, 0, 11);
    //  c->Draw();
    //  if (save) save_plots(c, save_dir_july, formats, remove_prelim_label);

    f->Close();
  }

  //f->Close();
  //f = TFile::Open("Janos_PHM/PHM_out/DynamicInefficiency_Approval2016July.root");
  //f = TFile::Open("Janos_PHM/PHM_out/DynIneffDBv3_DatavsMC2016_2076or2208b.root");

  if (dyn_ineff) {
    
    // -------------------------------------------------------------
    //           HitEfficiency vs Instantaneous Luminosity
    
    // Layer 1
    c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/LayersDisks_2016Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    //g->GetXaxis()->SetTitle("Instantaneous Luminosity (#scale[0.8]{#times10^{33}cm^{-2}s^{-1}})");
    ////g->GetXaxis()->SetRangeUser(3,10); // 2016 July
    ////g->GetYaxis()->SetRangeUser(0.95,1); // 2016 July
    //g->GetXaxis()->SetRangeUser(3,15);
    //g->GetYaxis()->SetRangeUser(0.9,1);
    //g->GetYaxis()->SetNdivisions(505);
    rename_legend(c, "");
    //remove_points(c, 0, 35,35); // 2016 July
    //remove_points(c, 1, 35,35); // 2016 July
    //remove_points(c, 2, 35,35); // 2016 July
    //remove_points(c, 3, 35,35); // 2016 July
    //remove_points(c, 4, 35,35); // 2016 July
    c->Draw();
    //prelim_lat_(3,10, 0.95,1, 0); // 2016 July
    //era_lat_   (3,10, 0.95,1); // 2016 July
    //prelim_lat_(3,15, 0.9,1, 0); // 2017 March
    //era_lat_   (3,15, 0.9,1); // 2017 March
    //if (save) save_plots(c, save_dir_july, formats, remove_prelim_label);
    //if (save) save_plots(c, save_dir_2017_march, formats, remove_prelim_label);
    if (save) save_plots(c, save_dir_2017_may+"Efficiency/", formats, remove_prelim_label);

    //  // Years
    //  c = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi/DataYears_Lay1");
    //  ((TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0))->GetXaxis()->SetRangeUser(0,15);
    //  ((TLatex*)c->GetListOfPrimitives()->At(5))->SetX(0);
    //  remove_points(c, 3, 0,3); c->Draw();
    //  if (save) save_plots(c, save_dir_2017_may+"Efficiency/", formats, remove_prelim_label);

    // -------------------------------------------------------------
    //                   HitEfficiency vs Pile-up

    // Layer 1
    c = (TCanvas*)f->Get("HitEfficiency_vs_Pileup/LayersDisks_2016Data");
    g = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
    //g->GetXaxis()->SetTitle("Average Pile-up");
    ////g->GetXaxis()->SetRangeUser(10,35);
    ////g->GetYaxis()->SetRangeUser(0.95,1);
    //g->GetXaxis()->SetRangeUser(10,42);
    //g->GetYaxis()->SetRangeUser(0.9,1);
    g->GetYaxis()->SetNdivisions(505);
    rename_legend(c, "");
    //remove_points(c, 0, 14,14);
    //remove_points(c, 1, 14,14);
    //remove_points(c, 2, 14,14);
    //remove_points(c, 3, 14,14);
    //remove_points(c, 4, 14,14);
    c->Draw();
    //prelim_lat_(10,35, 0.95,1, 0);
    //era_lat_   (10,35, 0.95,1);
    //prelim_lat_(10,42, 0.9,1, 0);
    //era_lat_   (10,42, 0.9,1);
    //if (save) save_plots(c, save_dir_july, formats, remove_prelim_label);
    //if (save) save_plots(c, save_dir_2017_march, formats, remove_prelim_label);
    if (save) save_plots(c, save_dir_2017_may+"Efficiency/", formats, remove_prelim_label);

    f->Close();
  }
}
