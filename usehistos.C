//GENERATES HISTOGRMAS AND WRITES THEM TO ONE FILE FOR ONE PT RANGE
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <vector>
#include <TMath.h>
#include <iostream>
# include <TF1.h>
# include <TH1F.h>
# include <TH1D.h>
# include <TCanvas.h>

using namespace std;
Bool_t istest = false;
int usehistos(TString inputfile="/scratch/bell/awesole/dcacutsat200_11_16/histo_d0ana_PbPb2018_04.root_808.root", TString outfile1="/scratch/bell/awesole/histotest.root")
{
    //    TFile *inf = TFile::Open("/scratch/brown/awesole/bdtbg.root");


    if(istest)
    {
        //inputfile="/scratch/brown/awesole/output/Dntuple_d0ana_PbPb2018_04.root_327.root";
        inputfile="/scratch/bell/awesole/dcacutsat200_11_16/histo_d0ana_PbPb2018_04.root_808.root";
        outfile1="/scratch/bell/awesole/histotest.root";
    }



    TFile* inf = TFile::Open(inputfile);
    TTree *t = (TTree*)inf->Get("mvaTree");
    t->SetMakeClass(1);
    TFile *outf = new TFile(outfile1,"recreate");

    int Dsize, centrality;
    float pT[10000], mass[10000], y[10000], nzDCASigD2[10000], n3DPointingAngle[1000], log3ddls[1000];
    double BDT_weight[10000];

    std::vector<TH1D*> alist;
    alist.resize(25);
/*
    for (int i=0; i<10; i++)
    {
        vlist[i]=new TH1D(Form("pThisto_%d",i),Form("pTBin_%d",i), 52, 1.74, 2);

    }
    cout << "vlist made" << endl;
*/

    for (int j=0; j<25; j++)
    {
        alist[j]=new TH1D(Form("aahisto_%d",j),Form("BDTBin_%d",j), 52, 1.74, 2);

    }
    
    
    for(int i=0;i<t->GetEntries();i++)
    //for(int i=0;i<1000;i++)
    {
        t->SetBranchAddress("nDsize", &Dsize); 
        t->SetBranchAddress("npT", pT);
        t->SetBranchAddress("nmass", mass);
        t->SetBranchAddress("ncent", &centrality);
        t->SetBranchAddress("BDT_weight", BDT_weight);
        t->SetBranchAddress("nmass", mass);
        t->SetBranchAddress("ny", y);
        t->SetBranchAddress("nzDCASigD2", nzDCASigD2);
        t->SetBranchAddress("n3DPointingAngle", n3DPointingAngle);
        t->SetBranchAddress("log3ddls", log3ddls);
        t->GetEntry(i);
        // cout << "Dsize= " << Dsize << endl;
/*  
      t->SetBranchAddress("Dsize", &Dsize); 
        t->SetBranchAddress("pT", pT);
        t->SetBranchAddress("mass", mass);
        t->SetBranchAddress("centrality", &centrality);
        t->SetBranchAddress("BDT_weight", BDT_weight);
        t->SetBranchAddress("y", y);
       // t->SetBranchAddress("nzDCASigD2", nzDCASigD2);
       // t->SetBranchAddress("n3DPointingAngle", n3DPointingAngle);
        t->SetBranchAddress("x3DDecayLengthSignificance", log3ddls);
        t->GetEntry(i);
        // cout << "Dsize= " << Dsize << endl;
  
*/
      if(i%100000==0) cout <<i<<" / "<<t->GetEntries()<<endl;

        if (centrality>=0 && centrality<20 )
        {
            //   for(int j=0; j<Dsize; j++)
            for(int j=0; j<Dsize; j++)
            { 
                   //if(y[j]>-1 && y[j]<1 && nzDCASigD2[j]<200 && nzDCASigD2[j]>-200 && n3DPointingAngle[j]<=0.2){
                   //if(y[j]>-1 && y[j]<1 && n3DPointingAngle[j]<=0.2){
                   if(y[j]>-1 && y[j]<1 ){
                    //cout << "j= " << j << endl;
                    //cout << "log=" << log3ddls[j] << endl;
                      //   cout << "pT[j]= " << pT[j] << endl;
                        // cout << "mass[j]= " << mass[j] << endl;
                    if(BDT_weight[j]>-0.6) alist[0]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.55) alist[1]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.5) alist[2]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.45) alist[3]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.4) alist[4]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.35) alist[5]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.3) alist[6]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.25) alist[7]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.2) alist[8]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.15) alist[9]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.1) alist[10]->Fill(mass[j]);
                    if(BDT_weight[j]>-0.05) alist[11]->Fill(mass[j]);
                    if(BDT_weight[j]>0.0) alist[12]->Fill(mass[j]);
                    if(BDT_weight[j]>0.05) alist[13]->Fill(mass[j]);
                    if(BDT_weight[j]>0.1) alist[14]->Fill(mass[j]);
                    if(BDT_weight[j]>0.15) alist[15]->Fill(mass[j]);
                    if(BDT_weight[j]>0.2) alist[16]->Fill(mass[j]);
                    if(BDT_weight[j]>0.25) alist[17]->Fill(mass[j]);
                    if(BDT_weight[j]>0.3) alist[18]->Fill(mass[j]);
                    if(BDT_weight[j]>0.35) alist[19]->Fill(mass[j]);
                    if(BDT_weight[j]>0.4) alist[20]->Fill(mass[j]);
                    if(BDT_weight[j]>0.45) alist[21]->Fill(mass[j]);
                    if(BDT_weight[j]>0.5) alist[22]->Fill(mass[j]);
                    if(BDT_weight[j]>0.55) alist[23]->Fill(mass[j]);
                    if(BDT_weight[j]>0.6) alist[24]->Fill(mass[j]);
                
            
//*******************************************************************8
//TH1F = h1("h1", "histogram", 100, -3, 3);
//TF1 f("f", "gausn(0) + pol2(3)", 0, 10);
//f.SetParameters(50, 5, 1. 0.1, 0.01);
//h1.Fit(&f,"","E");             
             
             
             
             
             
             
             
                //             t->ResetBranchAddresses();
   //             t->SetBranchAddress("nDsize", &Dsize); 
            }//if centrality
          } //ify  
       }//for nDsize
       
    }//for entries 
    outf->Write();
   outf->Close();
   return 0;
}//function 


int main(int argc, char *argv[])
{
    if(istest) argc=3;
    if(argc==3)
    {
        usehistos(argv[1], argv[2]);
    }
    else
    {
        std::cout << "Usage: mergeForest <input_collection> <output_file>" << std::endl;
        return 1;
    }
    return 0;
}
