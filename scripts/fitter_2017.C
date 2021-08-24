void fitter_2017() {
  gStyle->SetOptTitle(0);

  //TFile *f = TFile::Open("Janos_PHM/PHM_PHASE1_out/EffLossStudy_Fill6024.root");
  //TFile *f = TFile::Open("Janos_PHM/PHM_PHASE1_out/HitEffMonitoring_Fill6026.root");
  //TFile *f = TFile::Open("Janos_PHM/PHM_PHASE1_out/HitEffMonitoring_Fill6031.root");
  //TFile *f = TFile::Open("Janos_PHM/PHM_PHASE1_out/HitEffMonitoring_Fill6046_6048_lowstat.root");
  //TFile *f = TFile::Open("Janos_PHM/PHM_PHASE1_out/HitEffMonitoring_Fill6061.root");
  TFile *f = TFile::Open("Janos_PHM/PHM_PHASE1_out/DynIneffDB_phase1_v2_test2.root"); // 6024

  TCanvas*c  = (TCanvas*)f->Get("HitEfficiency_vs_InstLumi0p5/LayersDisks_2017Data_TrkBeta0p1");
  TGraphAsymmErrors *g1 = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(0);
  TGraphAsymmErrors *g1_in  = (TGraphAsymmErrors*)((TCanvas*)f->Get("HitEfficiency_vs_InstLumi0p5/DatavsMCs2017_Lay1_InnerLadders_TrkBeta0p1"))->GetListOfPrimitives()->At(0);
  TGraphAsymmErrors *g1_out = (TGraphAsymmErrors*)((TCanvas*)f->Get("HitEfficiency_vs_InstLumi0p5/DatavsMCs2017_Lay1_OuterLadders_TrkBeta0p1"))->GetListOfPrimitives()->At(0);
  TGraphAsymmErrors *g2 = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(1);
  TGraphAsymmErrors *g3 = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(2);
  TGraphAsymmErrors *g4 = (TGraphAsymmErrors*)c->GetListOfPrimitives()->At(3);

  c->Draw();
  // Swtich L1 to Inner ladder plot
  for (int i=0; i<g1->GetN(); i++) {
    double x,y;
    g1_in->GetPoint(i,x,y);
    g1->SetPoint(i,x,y);
    g1->SetPointEXhigh(i,g1_in->GetErrorXhigh(i));
    g1->SetPointEXlow (i,g1_in->GetErrorXlow (i));
    g1->SetPointEYhigh(i,g1_in->GetErrorYhigh(i));
    g1->SetPointEYlow (i,g1_in->GetErrorYlow (i));
  }
  // Remove low lumi points
  //for (int i=5; i>0; --i) {
  //  g1->RemovePoint(i);
  //  g1_out->RemovePoint(i);
  //  g2->RemovePoint(i);
  //  g3->RemovePoint(i);
  //  g4->RemovePoint(i);
  //}
  g1_out->SetLineColor(628);
  g1_out->SetMarkerColor(628);
  g1_out->SetMarkerStyle(20);
  g1_out->Draw("SAMEP");
  g1->GetXaxis()->SetRangeUser(0,20);
  g1->GetYaxis()->SetRangeUser(0.7,1);
  g1->GetXaxis()->SetLabelSize(0.035);
  g1->GetYaxis()->SetLabelSize(0.035);
  TF1 *fit_l1_in  = new TF1("fit_l1_in", "pol3",0,20);
  TF1 *fit_l1_out = new TF1("fit_l1_out","pol3",0,20);
  TF1 *fit_l2 = new TF1("fit_l2","pol3",0,20);
  TF1 *fit_l3 = new TF1("fit_l3","pol1",0,20);
  TF1 *fit_l4 = new TF1("fit_l4","pol1",0,20);
  fit_l1_in ->FixParameter(0,1);
  fit_l1_out->FixParameter(0,1);
  fit_l2->FixParameter(0,1);
  fit_l3->FixParameter(0,1);
  fit_l4->FixParameter(0,1);
  fit_l1_in ->SetLineColor(g1->GetLineColor());
  fit_l1_out->SetLineColor(g1_out->GetLineColor());
  fit_l2->SetLineColor(g2->GetLineColor());
  fit_l3->SetLineColor(g3->GetLineColor());
  fit_l4->SetLineColor(g4->GetLineColor());
  g1->Fit("fit_l1_in","RM");
  g1_out->Fit("fit_l1_out","RM");
  g2->Fit("fit_l2","RM");
  g3->Fit("fit_l3","RM");
  g4->Fit("fit_l4","RM");
  // Get dcol efficiency
  TF1 *dcol_l1_in  = new TF1("dcol_l1_in", "pol3",0,20);
  TF1 *dcol_l1_out = new TF1("dcol_l1_out","pol3",0,20);
  TF1 *dcol_l2 = new TF1("dcol_l2","pol3",0,20);
  TF1 *dcol_l3 = new TF1("dcol_l3","pol1",0,20);
  TF1 *dcol_l4 = new TF1("dcol_l4","pol1",0,20);
  dcol_l1_in ->SetLineColor(g1->GetLineColor());
  dcol_l1_out->SetLineColor(g1_out->GetLineColor());
  dcol_l2->SetLineColor(g2->GetLineColor());
  dcol_l3->SetLineColor(g3->GetLineColor());
  dcol_l4->SetLineColor(g4->GetLineColor());
  dcol_l1_in ->SetLineStyle(7);
  dcol_l1_out->SetLineStyle(7);
  dcol_l2->SetLineStyle(7);
  dcol_l3->SetLineStyle(7);
  dcol_l4->SetLineStyle(7);
  dcol_l1_in->FixParameter(0,fit_l1_in->GetParameter(0));
  dcol_l1_out->FixParameter(0,fit_l1_out->GetParameter(0));
  dcol_l2->FixParameter(0,fit_l2->GetParameter(0));
  dcol_l3->FixParameter(0,fit_l3->GetParameter(0));
  dcol_l4->FixParameter(0,fit_l4->GetParameter(0));
  for (int i=1; i<dcol_l1_in->GetNpar();  ++i) dcol_l1_in ->FixParameter(i,fit_l1_in ->GetParameter(i)*2.7);//2.61,2.80,2.78-->2.73
  for (int i=1; i<dcol_l1_out->GetNpar(); ++i) dcol_l1_out->FixParameter(i,fit_l1_out->GetParameter(i)*2.7);//2.57,2.74,2.87-->2.73
  for (int i=1; i<dcol_l2->GetNpar(); ++i) dcol_l2->FixParameter(i,fit_l2->GetParameter(i)*1.15);
  for (int i=1; i<dcol_l3->GetNpar(); ++i) dcol_l3->FixParameter(i,fit_l3->GetParameter(i)*1.15);
  for (int i=1; i<dcol_l4->GetNpar(); ++i) dcol_l4->FixParameter(i,fit_l4->GetParameter(i)*1.15);
  dcol_l1_in ->Draw("SAME");
  dcol_l1_out->Draw("SAME");
  dcol_l2->Draw("SAME");
  dcol_l3->Draw("SAME");
  dcol_l4->Draw("SAME");
  TLegend *leg = (TLegend*)c->GetListOfPrimitives()->At(4);
  leg->Clear();
  leg->SetNColumns(2);
  leg->SetHeader("Fill 6024, #beta < 0.1");
  leg->AddEntry(g1,         "#color[633]{Layer 1 - Inner}","l");
  leg->AddEntry(dcol_l1_in, "#color[633]{ineff #times 2.7}","l");
  leg->AddEntry(g1_out,     "#color[628]{Layer 1 - Outer}","l");
  leg->AddEntry(dcol_l1_out,"#color[628]{ineff #times 2.7}","l");
  leg->AddEntry(g2,         "#color[618]{Layer 2}","l");
  leg->AddEntry(dcol_l2,    "#color[618]{ineff #times 1.15}","l");
  leg->AddEntry(g3,         "#color[601]{Layer 3}","l");
  leg->AddEntry(dcol_l3,    "#color[601]{ineff #times 1.15}","l");
  leg->AddEntry(g4,         "#color[434]{Layer 4}","l");
  leg->AddEntry(dcol_l4,    "#color[434]{ineff #times 1.15}","l");
  leg->SetX1(0.15);
  leg->SetX2(0.75);
  leg->SetY1(0.1);
  leg->SetY2(0.45);
  // Print results
  for (int lad=1; lad<=12; ++lad) {
    std::cout<<"    cms.PSet(\n        det = cms.string(\"bpix\"),"<<std::endl;
    std::cout<<"        layer = cms.uint32(1),"<<std::endl;
    std::cout<<"        ladder = cms.uint32("<<lad<<"),"<<std::endl;
    if (lad%2==0) {
      // Inner ladders
      std::cout<<"        factor = cms.vdouble("<<dcol_l1_in->GetParameter(0);
      for (int i=1; i<dcol_l1_in->GetNpar(); i++) std::cout<<", "<<dcol_l1_in->GetParameter(i);
    } else {
      // Outer ladders
      std::cout<<"        factor = cms.vdouble("<<dcol_l1_out->GetParameter(0);
      for (int i=1; i<dcol_l1_out->GetNpar(); i++) std::cout<<", "<<dcol_l1_out->GetParameter(i);
    }
    std::cout<<")\n";
    std::cout<<"    ),\n";
  }
  std::cout<<"    cms.PSet(\n        det = cms.string(\"bpix\"),"<<std::endl;
  std::cout<<"        layer = cms.uint32(2),"<<std::endl;
  std::cout<<"        factor = cms.vdouble("<<dcol_l2->GetParameter(0);
  for (int i=1; i<dcol_l2->GetNpar(); i++) std::cout<<", "<<dcol_l2->GetParameter(i);
  std::cout<<")\n";
  std::cout<<"    ),\n";
  std::cout<<"    cms.PSet(\n        det = cms.string(\"bpix\"),"<<std::endl;
  std::cout<<"        layer = cms.uint32(3),"<<std::endl;
  std::cout<<"        factor = cms.vdouble("<<dcol_l3->GetParameter(0);
  for (int i=1; i<dcol_l3->GetNpar(); i++) std::cout<<", "<<dcol_l3->GetParameter(i);
  std::cout<<")\n";
  std::cout<<"    ),\n";
  std::cout<<"    cms.PSet(\n        det = cms.string(\"bpix\"),"<<std::endl;
  std::cout<<"        layer = cms.uint32(4),"<<std::endl;
  std::cout<<"        factor = cms.vdouble("<<dcol_l4->GetParameter(0);
  for (int i=1; i<dcol_l4->GetNpar(); i++) std::cout<<", "<<dcol_l4->GetParameter(i);
  std::cout<<")\n";
  std::cout<<"    ),\n";
}
