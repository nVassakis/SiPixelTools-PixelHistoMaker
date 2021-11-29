import ROOT as r
import os
import tdrstyle


r.gROOT.SetBatch()
r.gStyle.SetOptStat(0)
r.gStyle.SetOptTitle(0)

#f = r.TFile("2021Oct_DelayScan_ZeroBiasOnlineBeamSpot_20211101_230455_plots.root")
#f = r.TFile("2021Oct_DelayScan_ZeroBiasOnlineBeamSpot_looseTrk_20211109_015538_plots.root")
#postfix = "2021Oct_Scan"
#f = r.TFile("2021Nov_DelayScan_ZeroBiasOnlineBeamSpot_MiniTimingScan_20211104_151037_plots.root")
f = r.TFile("TestBeam_2ndsettings_v2_plots/plots.root")

odir = "test/"

plots = [

"HitEfficiency_vs_LayersDisks/FedErrorEvent_2021Data",
#"HitEfficiency_vs_LayersDisks/HitEfficiency_vs_LayersDisks",
"OnCluChargeNorm/AllDisks_RECO",
"OnCluChargeNorm/Layers_RECO",
"OnCluSize/AllDisks_RECO",
"OnCluSize/Layers_RECO",
"OnCluSizeX/DisksRings_RECO",
"OnCluSizeX/Layers_RECO",
"OnCluSizeY/AllDisks_RECO",
"OnCluSizeY/Layers_RECO",
]




for p in plots:
    c = f.Get(p)

    print(c.GetName())

    c.ls()
    c.SetWindowSize(1000, 800)
    c.SetCanvasSize(1000, 800)
    c.Resize()

    r.gSystem.ProcessEvents()

    objs = list(c.GetListOfPrimitives())
    

    if("OnClu" in c.GetName()):
        o_max = 0.
        for o in objs:
            #print(o.GetName())
            if(isinstance(o, r.TH1)): o_max = max(o_max, o.GetBinContent(o.GetMaximumBin()))

        print(o_max)
        objs[0].SetMaximum(1.3*o_max)

        if("SizeX" in c.GetName() or ("Size" in c.GetName() and "Disks" in c.GetName())):
            objs[0].GetXaxis().SetRangeUser(0, 10)

    if("HitEff" in c.GetName()):
        for o in objs:
            if(isinstance(o, r.TLegend)): c.GetListOfPrimitives().Remove(o)
            if(isinstance(o, r.TGraphAsymmErrors)): 
                o.SetMarkerColor(r.kBlack)
                o.SetLineColor(r.kBlack)



    c.Modified()


    c.cd()

    tdrstyle.setTDRStyle()
    latex = r.TLatex()
    latex.SetNDC()
    latex.SetTextSize(32./float(min(c.GetWw(),c.GetWh())))
    latex.SetTextFont(42)
    latex.SetTextAlign(11)
    latex.DrawLatex(.15,.95,"#bf{CMS} #it{Preliminary}");

    c.SaveAs(odir + c.GetName() + ".png")
    c.SaveAs(odir + c.GetName() + ".png")
    if("HitEff" in c.GetName()):
        fout = r.TFile.Open(odir + "foo.root", "RECREATE")
        fout.cd()
        c.Write()
        fout.Write()
        fout.Close()

