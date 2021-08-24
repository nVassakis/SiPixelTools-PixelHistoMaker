#include <map>

TH1D* getplot(TString fname, TString hname) {
  TFile f(fname.Data(), "READ");
  TH1D *h= (TH1D*)f.Get(hname.Data());
  TH1D *c=(TH1D*)h->Clone();
  c->SetDirectory(0);
  return c;
}

TH2D* getplot2d(TString fname, TString hname) {
  TFile f(fname.Data(), "READ");
  TH2D *h= (TH2D*)f.Get(hname.Data());
  TH2D *c=(TH2D*)h->Clone();
  c->SetDirectory(0);
  return c;
}

TH3D* getplot3d(TString fname, TString hname) {
  TFile f(fname.Data(), "READ");
  TH3D *h= (TH3D*)f.Get(hname.Data());
  TH3D *c=(TH3D*)h->Clone();
  c->SetDirectory(0);
  return c;
}

void error(TH1D* eff, TH1D* dist) {
  double z = 1; // 1 Sigma confidence
  for (int i=1; i<=eff->GetNbinsX(); i++) if (dist->GetBinContent(i)!=0) {
    double p = eff->GetBinContent(i);
    double n = dist->GetBinContent(i);
    double cen = (p+(z*z/(2*n))) / (1.0 + (z*z/n));
    double halfwidth = z*sqrt( p*(1.0-p)/n + (z*z/(4*n*n)) ) / (1.0 + (z*z/n));
    double err = halfwidth + fabs(cen-p); // Assymmetric error -> Choose larger for a conservative error estimate
    eff->SetBinError(i,err);
  }
}

void rebin_eff(TH1D* eff, TH1D* dist, int n=2) {
  eff->Multiply(dist);
  dist->Add(eff,-1);
  eff->Rebin(n);
  dist->Rebin(n);
  dist->Add(eff);
  eff->Divide(dist);
  error(eff,dist);
}

int get_online_ladder(int layer, int ladder) {
  // copied exactly from TimingStudy::getModuleData
  int on_ladder;
  if (layer==1) {
    if (ladder<=5 && ladder>=1) on_ladder = 6-ladder;
    else if (ladder<=15 && ladder>=6) on_ladder = 5-ladder;
    else if (ladder<=20 && ladder>=16) on_ladder = 26-ladder;
  } else if (layer==2) {
    if (ladder<=8 && ladder>=1) on_ladder = 9-ladder;
    else if (ladder<=24 && ladder>=9) on_ladder = 8-ladder;
    else if (ladder<=32 && ladder>=25) on_ladder = 41-ladder;
  } if (layer==3) {
    if (ladder<=11 && ladder>=1) on_ladder = 12-ladder;
    else if (ladder<=33 && ladder>=12) on_ladder = 11-ladder;
    else if (ladder<=44 && ladder>=34) on_ladder = 56-ladder;
  }
  return on_ladder;
}

void fitter(bool draw_fits = 1, std::string print_factors = "db") {

  if (print_factors != "cfg" && print_factors != "db") std::cout<<"Wrong argument for print_factors! it should be \"cfg\" or \"db\"."<<std::endl;

  std::string data_input_file = "anos_PHM/PHM_out/HitEff_13TeV_ZB_Run2015_50ns_full_secondrun.root";
  //std::string data_input_file = "Janos_PHM/PHM_out/HitEff_13TeV_ZB_Run2015D_25ns_2ndrun_part1and2.root";
  //std::string data_input_file = "Janos_PHM/PHM_out/HitEff_13TeV_ZB_Run2015D_25ns_2ndrun_256630-258159.root";
  //std::string data_input_file = "Janos_PHM/PHM_out/Approval_2015_November.root";
  std::string mc_input_file = "Janos_PHM/PHM_out/dcol_scan_13TeV50ns_full.root";

  const int nfile = 10;
  double dcol_eff[nfile] = { 1, 0.999, 0.996, 0.993, 0.99, 0.98, 0.97, 0.95, 0.90, 0.80 };
  
  // Data
  TH1D *data_lad_eff[3];
  TH1D *data_mod_eff[3];
  TH2D *data_mod_valid[3];
  TH1D *data_instlumi_eff[3];
  TH2D *data_instlumi_valid[3];
  TH1D *data_instlumi_den[3];
  TH1D *data_instlumi_eff_rebin[3];
  const char* layname[3] = {"_Lay1", "_Lay2","_Lay3"};
  for (int lay=0; lay<3; lay++) {
    data_lad_eff[lay]=getplot(data_input_file,(std::string("HitEfficiency_vs_Ladders/data")+layname[lay]));
    data_mod_eff[lay]=getplot(data_input_file,(std::string("HitEfficiency_vs_Modules/data")+layname[lay]));
    data_mod_valid[lay]=getplot2d(data_input_file,(std::string("HitEfficiency_vs_Modules/ValidHit_vs_Modules/data")+layname[lay]));
    data_instlumi_eff[lay]=getplot(data_input_file,(std::string("HitEfficiency_vs_InstLumi/data")+layname[lay]));
    data_instlumi_valid[lay]=getplot2d(data_input_file,(std::string("HitEfficiency_vs_InstLumi/ValidHit_vs_InstLumi/data")+layname[lay]));
  }
  
  // MC
  TH1D *mc_det_eff[nfile];
  TH1D *mc_mod_eff[3][nfile];
  TH2D *mc_mod_valid[3][nfile];
  TH3D *mc_dcol100_modmap_den[3];
  const char* dcolname[10] = {"100", "99p9", "99p6", "99p3", "99", "98", "97", "95", "90", "80"};
  for (int i=0; i<nfile; i++) {
    mc_det_eff[i] = getplot(mc_input_file,(std::string("HitEfficiency_vs_LayersDisks/Dcol")+dcolname[i]));
    for (int lay=0; lay<3; lay++) {
      mc_mod_eff[lay][i] = getplot(mc_input_file,(std::string("HitEfficiency_vs_Modules/Dcol")+dcolname[i]+layname[lay]));
      mc_mod_valid[lay][i] = getplot2d(mc_input_file,(std::string("HitEfficiency_vs_Modules/ValidHit_vs_Modules/Dcol")+dcolname[i]+layname[lay]));
      if (i==0) mc_dcol100_modmap_den[lay] = getplot3d(mc_input_file,(std::string("HitEfficiency_vs_Ladders_vs_Modules/ValidHit_vs_Ladders_vs_Modules/Dcol100")+layname[lay]));
    }
  }
 
  const char* name[3] = {"hiteff_vs_dcol_l1", "hiteff_vs_dcol_l2", "hiteff_vs_dcol_l3"};
  TF1 *avg_fit[3];
  TH1D *hiteff_vs_dcol[3];
  const char* ringname[4] = {"_ring1", "_ring2", "_ring3", "_ring4"};
  TF1 *ring_fit[3][4];
  TH1D *hiteff_vs_dcol_ring[3][4];
  TF1 *instlumi_fit[3];
  TH1D *instlumi_scale[3];
  TCanvas * c; 
  if (draw_fits) {
    gStyle->SetOptStat(0);
    c = new TCanvas("c", "c",800,800);
    c->Divide(2,2);
  }
  // Scale factor arrays
  std::vector<double> mc_ladder_on_dcol[3];
  std::vector<double> mc_ladder_off_dcol[3];
  double data_ring_eff[3][4];
  double data_ring_dcol[3][4];
  double mc_ring_eff[3][4];
  double mc_ring_dcol[3][4];
  double mc_ring_scale[3][4];
  double mc_lay_eff[3];
  double mc_lay_dcol[3];

  std::map<int,int> on_to_off_map[3];
  
  for (int lay=0; lay<3; lay++) {
    // Hit Eff vs Dcol Eff Fitting
    const char* axis_title = ";DCol Efficiency;Hit Efficiency";
    hiteff_vs_dcol[lay] = new TH1D(name[lay],axis_title,251,0.7495,1.0005);
    for (int ring=0; ring<4; ring++)
      hiteff_vs_dcol_ring[lay][ring] = new TH1D((std::string(name[lay])+ringname[ring]).c_str(),axis_title,251,0.7495,1.0005);
    for (int i=0; i<nfile; i++) {
      hiteff_vs_dcol[lay]->Fill(dcol_eff[i],mc_det_eff[i]->GetBinContent(lay+1));
      for (int ring=0; ring<4; ring++) {
	double mc_val = 0, mc_mis = 0;
	double data_val = 0, data_mis = 0;
	for (int side=0; side<=1; side++) {
	  mc_val += mc_mod_valid[lay][i]->GetBinContent(side?4-ring:6+ring,2);
	  mc_mis += mc_mod_valid[lay][i]->GetBinContent(side?4-ring:6+ring,1);
	  if (i==0) {
      data_val += data_mod_valid[lay]->GetBinContent(side?4-ring:6+ring,2);
      data_mis += data_mod_valid[lay]->GetBinContent(side?4-ring:6+ring,1);
	  }
	}
	hiteff_vs_dcol_ring[lay][ring]->Fill(dcol_eff[i],mc_val/(mc_val+mc_mis));
	if (i==0) data_ring_eff[lay][ring] = data_val/(data_val+data_mis);
      }
    }
    avg_fit[lay] = new TF1(name[lay],"pol2",0.75,1);
    hiteff_vs_dcol[lay]->Fit(name[lay],"RQ0");
    for (int ring=0; ring<4; ring++) {
      ring_fit[lay][ring] = new TF1((std::string(name[lay])+ringname[ring]).c_str(),"pol2",0.75,1);
      hiteff_vs_dcol_ring[lay][ring]->Fit((std::string(name[lay])+ringname[ring]).c_str(),"RQ0");
    }
    if (draw_fits) {
      c->cd(1);
      hiteff_vs_dcol[lay]->SetAxisRange(0.8, 1.05, "Y");
      hiteff_vs_dcol[lay]->SetMarkerColor(1+lay);
      hiteff_vs_dcol[lay]->SetMarkerStyle(20+lay);
      hiteff_vs_dcol[lay]->Draw(lay?"PSAME":"P");
      avg_fit[lay]->SetLineColor(lay+1);
      avg_fit[lay]->Draw("SAME");
      c->cd(2+lay);
      hiteff_vs_dcol_ring[lay][0]->SetAxisRange(0.8, 1.05, "Y");
      for (int ring=0; ring<4; ring++) {
	int color = (ring==0) ? 2 : ((ring==1) ? 6 : ((ring==2) ? 4 : 7));
	hiteff_vs_dcol_ring[lay][ring]->SetMarkerColor(color);
	hiteff_vs_dcol_ring[lay][ring]->SetMarkerStyle(20+ring);
	hiteff_vs_dcol_ring[lay][ring]->Draw(ring?"PSAME":"P");
	ring_fit[lay][ring]->SetLineColor(color);
	ring_fit[lay][ring]->Draw("SAME");
      }
    }
    // Ladder factors
    int nlad = (lay==0) ? 20 : (lay==1 ? 32 : 44);
    for (int ladder=1; ladder<=nlad; ladder++) {
      int on_ladder = get_online_ladder(lay+1,ladder);
      on_to_off_map[lay][on_ladder] = ladder;
      //std::cout<<"offline ladder "<<ladder<<" is online ladder "<<on_ladder<<std::endl;
      //std::cout<<"online ladder "<<on_ladder<<" is offline ladder "<<on_to_off_map[lay][on_ladder]<<std::endl;
    }
    mc_ladder_off_dcol[lay].resize(nlad);
    mc_ladder_on_dcol[lay].resize(nlad+1);
    for (int on_ladder=-nlad/2; on_ladder<=nlad/2; on_ladder++) {
      // Online scale factors
      if (on_ladder!=0) {
	double hit_eff = data_lad_eff[lay]->GetBinContent(on_ladder+23);
	double dcol_factor = avg_fit[lay]->GetX(hit_eff);
	int off_ladder = on_to_off_map[lay][on_ladder];
	mc_ladder_off_dcol[lay][off_ladder-1] = dcol_factor; // Offline module dcol efficiency factors
	mc_ladder_on_dcol[lay][on_ladder+nlad/2] = dcol_factor; // Online module dcol efficiency factors
      }
    }
    if (print_factors == "cfg") {
      std::cout<<"    theLadderEfficiency_BPix"<<(lay+1)<<" = cms.vdouble(\n";
      for (int off_ladder=1; off_ladder<=nlad; off_ladder++) std::cout<<"        "<<mc_ladder_off_dcol[lay][off_ladder-1]<<",\n";
      std::cout<<"        )\n";
    }
    if (print_factors=="db"){
      std::cout<<"    theColGeomFactors = cms.untracked.VPSet(\n";
      for (int off_ladder=1; off_ladder<=nlad; off_ladder++) {
        std::cout<<"      cms.PSet(\n        det = cms.string(\"bpix\"),"<<std::endl;
        std::cout<<"        layer = cms.uint32("<<lay+1<<"),"<<std::endl;
        std::cout<<"        ladder = cms.uint32("<<off_ladder<<"),"<<std::endl;
        std::cout<<"        factor = cms.double("<<mc_ladder_off_dcol[lay][off_ladder-1]<<")\n        ),\n";
      }
    }
    
    // Module and Instlumi factors
    mc_lay_eff[lay] = 0;
    double lay_den = 0;
    for (int ring=0; ring<4; ring++) {
      double ring_den = 0;
      mc_ring_eff[lay][ring] = 0;
      for (int side=0; side<=1; side++) {
	for (int ilad=0; ilad<=nlad; ilad++) if (ilad!=nlad/2) {
	  double module_val = mc_dcol100_modmap_den[lay]->GetBinContent(side?4-ring:6+ring, ilad+1, 2);
	  double module_mis = mc_dcol100_modmap_den[lay]->GetBinContent(side?4-ring:6+ring, ilad+1, 1);
	  ring_den += module_val + module_mis;
	  if (ring == 3) mc_ring_eff[lay][ring] += (module_val+module_mis) * ring_fit[lay][ring-1]->Eval(mc_ladder_on_dcol[lay][ilad]);
	  else mc_ring_eff[lay][ring] += (module_val+module_mis) * ring_fit[lay][ring]->Eval(mc_ladder_on_dcol[lay][ilad]);
        }
      }
      mc_ring_eff[lay][ring] /= ring_den;
      mc_ring_dcol[lay][ring] = ring_fit[lay][ring]->GetX(mc_ring_eff[lay][ring]);
      data_ring_dcol[lay][ring] = ring_fit[lay][ring]->GetX(data_ring_eff[lay][ring]);
      mc_ring_scale[lay][ring] = data_ring_dcol[lay][ring] / mc_ring_dcol[lay][ring];
      //std::cout<<"Layer "<<(lay+1)<<" Ring "<<(ring+1)<<" average Data hit eff: "<<data_ring_eff[lay][ring]<<std::endl;
      //std::cout<<"Layer "<<(lay+1)<<" Ring "<<(ring+1)<<" average Data dcol eff: "<<data_ring_dcol[lay][ring]<<std::endl;
      //std::cout<<"Layer "<<(lay+1)<<" Ring "<<(ring+1)<<" average MC dcol eff: "<<mc_ring_dcol[lay][ring]<<std::endl;
      //std::cout<<"Layer "<<(lay+1)<<" Ring "<<(ring+1)<<" Scale factor: "<<mc_ring_scale[lay][ring]<<std::endl;
      for (int side=0; side<=1; side++) {
	for (int ilad=0; ilad<=nlad; ilad++) if (ilad!=nlad/2) {
	  double module_val = mc_dcol100_modmap_den[lay]->GetBinContent(side?4-ring:6+ring, ilad+1, 2);
	  double module_mis = mc_dcol100_modmap_den[lay]->GetBinContent(side?4-ring:6+ring, ilad+1, 1);
	  lay_den += module_val + module_mis;
	  mc_lay_eff[lay] += (module_val+module_mis) * ring_fit[lay][ring]->Eval(mc_ladder_on_dcol[lay][ilad]*mc_ring_scale[lay][ring]);
        }
      }
    }
    if (print_factors=="cfg") {
      std::cout<<"    theModuleEfficiency_BPix"<<(lay+1)<<" = cms.vdouble("<<std::endl;
      for (int ring=0; ring<4; ring++) std::cout<<"        "<<mc_ring_scale[lay][ring]<<",\n";
      std::cout<<"        )\n";
    }
    if (print_factors=="db"){
      for (int ring=1; ring<=8; ring++) {
        int module;
        if (ring<=4) module=5-ring;
        else module=ring-4;
        std::cout<<"      cms.PSet(\n        det = cms.string(\"bpix\"),"<<std::endl;
        std::cout<<"        layer = cms.uint32("<<lay+1<<"),"<<std::endl;
        std::cout<<"        module = cms.uint32("<<ring<<"),"<<std::endl;
        std::cout<<"        factor = cms.double("<<mc_ring_scale[lay][module-1]<<")\n        ),\n";
      }
      std::cout<<"      ),\n";
    }
    
    mc_lay_eff[lay] /= lay_den;
    mc_lay_dcol[lay] = avg_fit[lay]->GetX(mc_lay_eff[lay]);

    data_instlumi_den[lay] = data_instlumi_valid[lay]->ProjectionX();
    int n_rebin = 1;
    data_instlumi_eff_rebin[lay]=(TH1D*)data_instlumi_eff[lay]->Clone();
    rebin_eff(data_instlumi_eff_rebin[lay],data_instlumi_den[lay], n_rebin);
    
    instlumi_scale[lay]=(TH1D*)data_instlumi_eff_rebin[lay]->Clone();
    
    //instlumi scaling
    for (int i=1; i<=instlumi_scale[0]->GetNbinsX(); i++) {
      double data_instlumi_lay_eff = data_instlumi_eff_rebin[lay]->GetBinContent(i);
      double data_instlumi_lay_dcol = avg_fit[lay]->GetX(data_instlumi_lay_eff);
      double instlumi_scale_factor = (data_instlumi_lay_eff>0) ? data_instlumi_lay_dcol/mc_lay_dcol[lay] : 0;
      instlumi_scale[lay]->SetBinContent(i,instlumi_scale_factor);
    }
    instlumi_fit[lay] = new TF1((std::string("instlumi_fit")+layname[lay]).c_str(),"pol1",0, 1.4);
    instlumi_scale[lay]->Fit((std::string("instlumi_fit")+layname[lay]).c_str(), "RQ0");
    //instlumi_fit[lay]->Print();
    if (print_factors=="cfg") {
      std::cout<<"    thePUEfficiency_BPix"<<(lay+1)<<" = cms.vdouble("<<std::endl;
      for (int par=0; par<3; par++) std::cout<<"        "<<instlumi_fit[lay]->GetParameter(par)<<",\n";
      std::cout<<"        )\n\n";
    }
    if (print_factors=="db"){
      std::cout<<"    theColPUEfficiency = cms.untracked.VPSet(\n";
      std::cout<<"      cms.PSet(\n        det = cms.string(\"bpix\"),"<<std::endl;
      std::cout<<"        layer = cms.uint32("<<lay+1<<"),"<<std::endl;
      std::cout<<"        factor = cms.vdouble(\n";
      for (int par=0; par<3; par++) std::cout<<"          "<<instlumi_fit[lay]->GetParameter(par)<<",\n";
      std::cout<<"          ),\n        ),\n";
    }
  }
  TCanvas * proba = new TCanvas("proba", "proba",600,600);
  proba->cd();
  instlumi_scale[0]->Draw("P");
  instlumi_fit[0]->Draw("SAME");

  TCanvas* dcol= new TCanvas("Hiteff_vs_Dcol","Hiteff_vs_Dcol",600,600);
  hiteff_vs_dcol[0]->SetAxisRange(0.8, 1.05, "Y");
  hiteff_vs_dcol[0]->SetMarkerColor(1);
  hiteff_vs_dcol[0]->SetMarkerStyle(20);
  hiteff_vs_dcol[0]->Draw("P");
  hiteff_vs_dcol[1]->SetMarkerColor(2);
  hiteff_vs_dcol[1]->SetMarkerStyle(21);
  hiteff_vs_dcol[1]->Draw("SAMEP");
  hiteff_vs_dcol[2]->SetMarkerColor(8);
  hiteff_vs_dcol[2]->SetMarkerStyle(22);
  hiteff_vs_dcol[2]->Draw("SAMEP");
  avg_fit[0]->SetLineColor(1);
  avg_fit[1]->SetLineColor(2);
  avg_fit[2]->SetLineColor(8);
  avg_fit[0]->Draw("SAME");
  avg_fit[1]->Draw("SAME");
  avg_fit[2]->Draw("SAME");
  TLegend *leg3 = new TLegend(0.45,0.25,0.25,0.35,"");
  leg3->AddEntry(hiteff_vs_dcol[0],   "Layer 1", "P");
  leg3->AddEntry(hiteff_vs_dcol[1],   "Layer 2", "P");
  leg3->AddEntry(hiteff_vs_dcol[2],   "Layer 3", "P");
  leg3->SetFillColor(0);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.04);
  leg3->Draw("SAMEP1");
}
