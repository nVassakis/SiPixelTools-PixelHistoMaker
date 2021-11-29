import ROOT as r
import os


r.gROOT.SetBatch()
r.gStyle.SetOptStat(0)
r.gStyle.SetOptTitle(0)

#f = r.TFile("2021Oct_DelayScan_ZeroBiasOnlineBeamSpot_20211101_230455_plots.root")
#f = r.TFile("2021Oct_DelayScan_ZeroBiasOnlineBeamSpot_looseTrk_20211109_015538_plots.root")
#postfix = "2021Oct_Scan"
#f = r.TFile("2021Nov_DelayScan_ZeroBiasOnlineBeamSpot_MiniTimingScan_20211104_151037_plots.root")
f = r.TFile("2021Nov_DelayScan_ZeroBiasOnlineBeamSpot_MiniTimingScan_20211104_151037_plots_forLHCC.root")
postfix = "2021Nov_MiniScan"

plots = ["HitEfficiency_vs_Delay"
       , "AvgOnTrkCluSize_vs_Delay"
       , "AvgNormOnTrkCluCharge_vs_Delay"
      ]

det = ["Layers"
     , "Layers_BpI"
     , "Layers_BpO"
     , "Layers_BmI"
     , "Layers_BmO"
     , "Disks"
     , "Disks_BpI"
     , "Disks_BpO"
     , "Disks_BmI"
     , "Disks_BmO"
     ]


for p in plots:
    for d in det:
        c = f.Get(os.path.join(p,d + "_" + postfix))

        print c.GetName()

        c.cd()
        latex = r.TLatex()
        latex.SetNDC()
        latex.SetTextSize(32./float(min(c.GetWw(),c.GetWh())))
        latex.SetTextFont(42)
        latex.SetTextAlign(11)
        latex.DrawLatex(.15,.95,"#bf{CMS} #it{Preliminary}");

        c.SaveAs(c.GetName() + ".png")
