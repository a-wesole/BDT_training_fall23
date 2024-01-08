//FITS THE SIGNAL AND SIGNAL+SWAP PLOTS WITH FUNCTION
# include <TFile.h>
# include <TTree.h>
# include <TBranch.h>
# include <vector>
# include <TMath.h>
# include <iostream>
# include <TF1.h>
# include <TH1F.h>
# include <TH1D.h>
# include <TCanvas.h>


int fit()
{

//TString inputfile = "/scratch/brown/awesole/output/histosout.root";
TString inputfile = "/scratch/bell/awesole/backup_from_brown/ptbinsout/massfits/pt_1_2histos.root";
TFile* inf = TFile::Open(inputfile);

TH1D *h1 = (TH1D*)inf->Get("histo_0");
TH1D *h2 = (TH1D*)inf->Get("histo_1");
TH1D *h3 = (TH1D*)inf->Get("histo_2");

double fit_range_low = 1.74;
double fit_range_high = 2.0;
double D0_mass = 1.8648;


 //TF1* f = new TF1("original function","[0]*([5]*([4]*TMath::Gaus(x,[1],[2]*(1.0 +[6]))/(sqrt(2*3.14159)*[2]*(1.0 + [6]))+(1-[4])*TMath::Gaus(x,[1],[3]*(1.0 +[6]))/(sqrt(2*3.14159)*[3]*(1.0 +[6])))+(1-[5])*TMath::Gaus(x,[8],[7]*(1.0     +[6]))/(sqrt(2*3.14159)*[7]*(1.0 +[6])))+ [9] + [10]*x + [11]*x*x + [12]*x*x*x   ", fit_range_low, fit_range_high);
 TF1* f = new TF1("original function","[0]*([4]*TMath::Gaus(x,[1],[2]*(1.0 +[6]))/(sqrt(2*3.14159)*[2]*(1.0 + [6]))+(1-[4])*TMath::Gaus(x,[1],[3]*(1.0 +[6]))/(sqrt(2*3.14159)*[3]*(1.0 +[6])))+ [7] + [8]*x + [9]*x*x + [5]*x*x*x   ", fit_range_low, fit_range_high);

f->SetLineColor(2);
f->SetLineWidth(1);

f->SetParameter(0,100.);
f->SetParameter(1,D0_mass);
f->SetParameter(2,0.03);
f->SetParameter(3,0.005);
f->SetParameter(4,0.1);

//f->FixParameter(5,1);
f->FixParameter(6,0); //always 0 in MC
//f->FixParameter(7,0.1); //does not really mater here as yield is fix to 0
//f->FixParameter(8,D0_mass);
f->FixParameter(7,0);//9
f->FixParameter(8,0);
f->FixParameter(9,0);
f->FixParameter(5,0);//12

f->SetParLimits(2,0.01,0.1);
f->SetParLimits(3,0.001,0.05);
f->SetParLimits(4,0,1);
//f->SetParLimits(5,0,1);

f->FixParameter(1,1.8648);

h1->Fit(f,"q","",fit_range_low,fit_range_high);
h1->Fit(f,"q","",fit_range_low,fit_range_high);
f->ReleaseParameter(1);
h1->Fit(f,"q","",fit_range_low,fit_range_high);
h1->Fit(f,"q","",fit_range_low,fit_range_high);
h1->Fit(f,"","",fit_range_low,fit_range_high);

f->FixParameter(1,f->GetParameter(1));
f->FixParameter(2,f->GetParameter(2));
f->FixParameter(3,f->GetParameter(3));
f->FixParameter(4,f->GetParameter(4));

f->ReleaseParameter(5);
f->ReleaseParameter(7);
f->ReleaseParameter(8);

f->SetParameter(7,0.1);
f->SetParameter(8,D0_mass);

h2->Fit(f,"L q","",fit_range_low,fit_range_high);
h2->Fit(f,"L q","",fit_range_low,fit_range_high);
h2->Fit(f,"L q","",fit_range_low,fit_range_high);
h2->Fit(f,"L q","",fit_range_low,fit_range_high);
h2->Fit(f,"L ","",fit_range_low,fit_range_high);
/*
f->FixParameter(5,f->GetParameter(5));
f->FixParameter(7,f->GetParameter(7));
f->FixParameter(8,f->GetParameter(8));

f->ReleaseParameter(7);//9
f->ReleaseParameter(8);
f->ReleaseParameter(9);
f->ReleaseParameter(5);//12

h3->Fit(f,"q","",fit_range_low,fit_range_high);
h3->Fit(f,"q","",fit_range_low,fit_range_high);
f->ReleaseParameter(1); //allow data to have different mass peak mean than MC
f->ReleaseParameter(6); //allow data to have different peak width than MC
f->SetParameter(6,0);
f->SetParLimits(6,-1,1);
h3->Fit(f,"L q","",fit_range_low,fit_range_high);
h3->Fit(f,"L q","",fit_range_low,fit_range_high);
h3->Fit(f,"L q","",fit_range_low,fit_range_high);
h3->Fit(f,"L m","",fit_range_low,fit_range_high);
*/

return 0;
}//function

