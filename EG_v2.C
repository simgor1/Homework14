/*
In this ROOT function we generate a distribution according to sin(x)
between 0 and pi
To run do:
root
.L rootgenerate_sinx.C
rootfuncgenerate(10000)
*/
// include C++ STL headers
#include <iostream>
#include <fstream>
using namespace std;
// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h> // style object
#include <TMath.h> // math functions
#include <TCanvas.h> // canvas object

//________________________________________________________________________
void rootfuncgenerate(Int_t nEvents, Int_t nTracks, Double_t v2) {

    ofstream file("phi_dist.dat");
    
    cout << "Generating " << nEvents << " events with " << nTracks << " tracks" << endl << endl;

    // create histogram that we will fill with random values
    TH1D* hPhi = new TH1D("hPhi", "ROOT func generated distribution; x; Counts", 100, 0, TMath::Pi());

    // Define the function we want to generate
    TF1* sinFunc = new TF1("sinFunc", "1+(2*[0]*cos(2*x))", 0, TMath::Pi());
    sinFunc->SetParameter(0, v2);
    sinFunc->SetParName(0, "v2");
    
    
    
     // Loop over events
    for (Int_t ne = 0; ne < nEvents; ne++) {
        file << "Event " << ne << endl;
        file << "nTracks " << nTracks << endl;

        // Generate values for nTracks
        for (Int_t nt = 0; nt < nTracks; nt++) {
            Double_t phi = sinFunc->GetRandom();
            file << nt << " : " << phi << endl; // Write to the output file
            hPhi->Fill(phi);
        }
    }
    
    file.close();


    // Set ROOT drawing styles
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(1111);
    // create canvas for hPhi
    TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
    hPhi->SetMinimum(0);
    hPhi->Draw();
    // create 1d function that we will use to fit our generated data to ensure
    // that the generation works
    TF1* fitFunc = new TF1("fitFunc", "[0]*(1+2*[1]*cos(2*x))", 0, TMath::Pi());
    fitFunc->SetParameter(0, 10);
    fitFunc->SetParameter(1, v2);
    fitFunc->SetLineColor(kRed);
    hPhi->Fit(fitFunc);
    // Save the canvas as a picture
    c1->SaveAs("v2_rootfunc.jpg");
}
    