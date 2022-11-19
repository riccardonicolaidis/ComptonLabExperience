#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "../include/myglobals.hh"

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "THStack.h"
#include "TF1.h"
#include "TLegend.h"


using namespace std;


int DataAnalysis()
{

    // Open the file DetectorAngles.csv

    ifstream DetectorAnglesFile;
    DetectorAnglesFile.open("../DetectorAngles.csv");

    // Read the file DetectorAngles.csv
    int DetectorID[NDetectors];
    double DetectorAngle[NDetectors]; // in degrees
    double DetectorAngleRad[NDetectors]; // in radians

    for (int i = 0; i < NDetectors; i++)
    {
        DetectorAnglesFile >> DetectorID[i] >> DetectorAngle[i];
        DetectorAngleRad[i] = DetectorAngle[i] * M_PI / 180.0;
    }

    // Close the file DetectorAngles.csv
    DetectorAnglesFile.close();

    // Print all the data in the arrays
    for (int i = 0; i < NDetectors; i++)
    {
        cout << DetectorID[i] << " " << DetectorAngle[i] << " " << DetectorAngleRad[i] << endl;
    }

    TFile *file = new TFile("../DST/Photon1MeV.root");
    TTree *tree = (TTree*)file->Get("Edep");

    double Emean[NDetectors];
    double EmeanError[NDetectors];

    // Create the histograms
    TH1D *hEdep[NDetectors];
    
    for (int i = 0; i < NDetectors; i++)
    {
        hEdep[i] = new TH1D(Form("hEdep%d", i), Form("hEdep%d", i), 300, 0.001, 1.1);
        tree -> Draw(Form("Ed_%d>>hEdep%d", i, i), Form("(EdTarget > 0) && (1 - EdTarget - Ed_%d) < 0.05",i), "");
        cout << hEdep[i] -> GetBinCenter(hEdep[i] -> GetMaximumBin()) << endl;
        
        double center = hEdep[i] -> GetBinCenter(hEdep[i] -> GetMaximumBin());
        double sigma = 0.1;
        

        hEdep[i] = new TH1D(Form("hEdep%d", i), Form("hEdep%d", i), 100, center-sigma, center+sigma);
        tree -> Draw(Form("Ed_%d>>hEdep%d", i, i), Form("(EdTarget > 0) && (1 - EdTarget - Ed_%d) < 0.05",i), "");
        hEdep[i] -> SetLineColor(i+1);


        Emean[i] = hEdep[i] -> GetMean();
        EmeanError[i] = hEdep[i] -> GetRMS(1) / sqrt(hEdep[i] -> GetEntries());

    }

    TCanvas *c1 = new TCanvas("c1", "c1", 1200, 600);
    // Stacked histograms
    THStack *hs = new THStack("hs", "hs");

    


    for (int i = 0; i < NDetectors; i++)
    {
        hs -> Add(hEdep[i], "e1");
    }
    hs -> Draw("nostack");
    hs -> GetXaxis() -> SetTitle("Edep [MeV]");
    hs -> GetYaxis() -> SetTitle("Counts");
    gPad -> SetLogy();

    c1 -> SaveAs("Histograms.pdf");
    c1 -> SaveAs("Histograms.png");


    // Create the TGraphErrors
    TGraphErrors *gEdep = new TGraphErrors(NDetectors, DetectorAngle, Emean, 0, EmeanError);
    gEdep -> SetTitle("Edep vs. Angle");
    gEdep -> GetXaxis() -> SetTitle("Angle [rad]");
    gEdep -> GetYaxis() -> SetTitle("Edep [MeV]");
    gEdep -> SetMarkerStyle(20);
    gEdep -> SetMarkerColor(4);
    gEdep -> SetLineColor(4);

    // Compton Scattering formula


    TF1 *fModel = new TF1("fModel", "1/(1 + (1/0.511)*(1 - TMath::Cos(x*3.14/180)))", -180, 180);
    fModel -> SetLineColor(2);

    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    gEdep -> Draw("AP");
    fModel -> Draw("same");

    TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg -> AddEntry(gEdep, "Data", "lep");
    leg -> AddEntry(fModel, "Model", "l");

    leg -> Draw();

    c2 -> SaveAs("Edep_vs_Angle.pdf");
    c2 -> SaveAs("Edep_vs_Angle.png");
    

    return 0;
}