//THIS PROGRAM GENERATES SIGNAL SAMPLE FOR BDT TRAINING
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <vector>
#include <TMath.h>
#include<fstream>
#include<string>
#include <iostream>
using namespace std;

void mcloop()
{
    int  nDsize=0, ev=0, ptmin= 8, ptmax=30;
    int size=nDsize+1;
    const int max_size =10000;
    int start=0;
    int Dsize, centrality, Dgen[max_size],DgenBAncestorpdgId[max_size];
    float mass[max_size], pT[max_size], y[max_size], x3DDecayLengthSignificance[max_size],VtxProb[max_size],x3DPointingAngle[max_size],Dtrk1Pt[max_size],Dtrk2Pt[max_size],Dtrk1PtErr[max_size],Dtrk2PtErr[max_size],Dtrk1Chi2n[max_size],Dtrk2Chi2n[max_size],xyDCASignificanceDaugther1[max_size],xyDCASignificanceDaugther2[max_size],zDCASignificanceDaugther1[max_size],zDCASignificanceDaugther2[max_size] ;

    int ncent, nDgen[max_size];
    float nmass[max_size], npT[max_size], ny[max_size], n3DDecayLengthSignificance[max_size], nVtxProb[max_size],n3DPointingAngle[max_size],nDtrk1Pt[max_size],nDtrk2Pt[max_size],nDtrk1PtErr[max_size],nDtrk2PtErr[max_size],nDgenBAncestorpdgId[max_size],nDtrk1Chi2n[max_size],nDtrk2Chi2n[max_size], nxyDCASigD1[max_size], nxyDCASigD2[max_size], nzDCASigD1[max_size], nzDCASigD2[max_size], log3ddls[max_size];

    //Get input file
    //    TFile *fin = TFile::Open("/scratch/brown/mstojano/d0outputs/dataoutputMiniAOD/MinimumBias8/327250_327450/d0ana_PbPb2018_03.root");
    TFile *fin = TFile::Open("/scratch/brown/mstojano/d0outputs/Dfinder_prompt/miniAOD/output.root");
    TFile results("/scratch/brown/awesole/ptbinsout/cent_50_90_pt_8_30/mcresults.root", "recreate");

    //navigate to ntDkpi tree
    TTree* tree = (TTree*)fin->Get("Dfinder/ntDkpi");
    //for all entries in the tree
    tree->SetBranchAddress("Dsize", &Dsize);
    tree->SetBranchAddress("Dgen", Dgen);
    tree->SetBranchAddress("mass", mass);
    tree->SetBranchAddress("centrality", &centrality);
    tree->SetBranchAddress("pT", pT);
    tree->SetBranchAddress("y", y);
    tree->SetBranchAddress("3DDecayLengthSignificance", x3DDecayLengthSignificance);
    tree->SetBranchAddress("VtxProb", VtxProb);
    tree->SetBranchAddress("3DPointingAngle", x3DPointingAngle);
    tree->SetBranchAddress("Dtrk1Pt", Dtrk1Pt);
    tree->SetBranchAddress("Dtrk2Pt", Dtrk2Pt);
    tree->SetBranchAddress("Dtrk1PtErr", Dtrk1PtErr);
    tree->SetBranchAddress("Dtrk2PtErr", Dtrk2PtErr);
    tree->SetBranchAddress("Dtrk1Chi2n", Dtrk1Chi2n);
    tree->SetBranchAddress("Dtrk2Chi2n", Dtrk2Chi2n);
    tree->SetBranchAddress("xyDCASignificanceDaugther1", xyDCASignificanceDaugther1);
    tree->SetBranchAddress("xyDCASignificanceDaugther2", xyDCASignificanceDaugther2);
    tree->SetBranchAddress("zDCASignificanceDaugther1", zDCASignificanceDaugther1);
    tree->SetBranchAddress("zDCASignificanceDaugther2", zDCASignificanceDaugther2);


    float nentries = tree->GetEntries();
    //CREATE A NEW FILE AND CLONE OF TREE IN IT
    TTree *newtree = new TTree("T" , "MC Signal Sample");
    newtree->Branch("nDsize",&nDsize,"nDsize/I");
    newtree->Branch("nDgen",&nDgen,"nDgen[nDsize]/I");
    newtree->Branch("nmass", nmass, "nmass[nDsize]/F");
    newtree->Branch("ncent", &ncent, "ncent/I");
    newtree->Branch("event", &ev, "ev/I");
    newtree->Branch("npT", npT, "npT[nDsize]/F");
    newtree->Branch("ny", ny, "ny[nDsize]/F");
    newtree->Branch("n3DDecayLengthSignificance", n3DDecayLengthSignificance, "n3DDecayLengthSignificance[nDsize]/F");
    newtree->Branch("log3ddls", log3ddls, "log3ddls[nDsize]/F");
    newtree->Branch("nVtxProb",nVtxProb , "nVtxProb[nDsize]/F");
    newtree->Branch("n3DPointingAngle", n3DPointingAngle,"n3DPointingAngle[nDsize]/F");
    newtree->Branch("nDtrk1Pt", nDtrk1Pt,"nDtrk1Pt[nDsize]/F");
    newtree->Branch("nDtrk2Pt", nDtrk2Pt,"nDtrk2Pt[nDsize]/F");
    newtree->Branch("nDtrk1PtErr", nDtrk1PtErr,"nDtrk1PtErr[nDsize]/F");
    newtree->Branch("nDtrk2PtErr", nDtrk2PtErr,"nDtrk2PtErr[nDsize]/F");
    newtree->Branch("nDtrk1Chi2n", nDtrk1Chi2n,"nDtrk1Chi2n[nDsize]/F");
    newtree->Branch("nDtrk2Chi2n", nDtrk2Chi2n,"nDtrk2Chi2n[nDsize]/F");
    newtree->Branch("nxyDCASigD1", nxyDCASigD1,"nxyDCASigD1[nDsize]/F");
    newtree->Branch("nxyDCASigD2", nxyDCASigD2,"nxyDCASigD2[nDsize]/F");
    newtree->Branch("nzDCASigD1", nzDCASigD1,"nzDCASigD1[nDsize]/F");
    newtree->Branch("nzDCASigD2", nzDCASigD2,"nzDCASigD2[nDsize]/F");


    for (int i=0; i<nentries; i++)
    //for (int i=0; i<200; i++)
    {
        tree->GetEntry(i);
        ev = ev+1;
        ncent=centrality;
        nDsize=0;
        if (i % 100000 == 0){
            cout << i << "/" << nentries << endl;
        }
        //    if (i % 50 == 0){
        //oniiiily copy branches where Dgen==3   
        for (int j=0; j<Dsize; j++)
        {
            if (TMath::IsNaN(x3DDecayLengthSignificance[j])) continue;
            if (TMath::IsNaN(nxyDCASigD2[j])) continue;
            if (TMath::IsNaN(nzDCASigD2[j])) continue;
            //                if ((mass[j] > amass-6*sd && mass[j] < amass-3*sd) || (mass[j] < amass+6*sd && mass[j]>amass+3*sd)){
            if(y[j]>-1 && y[j] <1 && Dtrk1Chi2n[j] < 0.18 && Dtrk2Chi2n[j] < 0.18 && Dgen[j]==23333 && pT[j]>=ptmin && pT[j] <ptmax){
                nDsize = nDsize+1;
                nDgen[nDsize-1]= Dgen[j];
                nmass[nDsize-1] =  mass[j];
                npT[nDsize-1] =  pT[j];
                ny[nDsize-1] =  y[j];
                n3DDecayLengthSignificance[nDsize-1] =  x3DDecayLengthSignificance[j];
                log3ddls[nDsize-1] = log10(x3DDecayLengthSignificance[j]);
                nVtxProb[nDsize-1] =  VtxProb[j];
                n3DPointingAngle[nDsize-1] =  x3DPointingAngle[j];
                nDtrk1Pt[nDsize-1] =  Dtrk1Pt[j];
                nDtrk2Pt[nDsize-1] =  Dtrk2Pt[j];
                nDtrk1PtErr[nDsize-1] =  Dtrk1PtErr[j];
                nDtrk2PtErr[nDsize-1] =  Dtrk2PtErr[j];
                nDtrk1Chi2n[nDsize-1] =  Dtrk1Chi2n[j];
                nDtrk2Chi2n[nDsize-1] =  Dtrk2Chi2n[j];
                nxyDCASigD1[nDsize-1] =  xyDCASignificanceDaugther1[j];
                nxyDCASigD2[nDsize-1] =  xyDCASignificanceDaugther2[j];
                nzDCASigD1[nDsize-1] =  zDCASignificanceDaugther1[j];
                nzDCASigD2[nDsize-1] =  zDCASignificanceDaugther2[j];

            }//if dgen==23333

        }//for dsize
        if(nDsize>0){
            newtree->Fill();
        }//if dsize>0
        }//for entries
        //  }
        newtree->Write();
        results.Write();
    }//program

    int main(int argc, char *argv[])
    {
        if(argc==1)
        {
            mcloop();
        }
        else
        {
            std::cout << "Usage: mergeForest <input_collection> <output_file>" << std::endl;
            return 1;
        }
        return 0;


    }
