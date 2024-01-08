//THIS PROGRAM ASSIGNS BDT VALUES FOR ONE PT RANGE
//you need to include the approprauate header file that will include the appropriate class.C from from bdt training output files
#include "header.h"
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <vector>
#include <TMath.h>
#include <iostream>
#define MAX_XB       20000
#define MAXD0CandSize 1000
using namespace std;
Bool_t istest = false;
int dataBDT(TString inputfile="", TString outfile1="", int pbpb=0, int ptMin=20, int ptMax=30, string mvatype="BDT",int cut_number=5,TString name_variable="0_1_2_3_5")
{
    //std::cout << "YOU JUST DEFINED THE FUNCTION" << endl;

    //  std::cout << "DEFINING THE MVA STRING" << endl;
    TString MVAtype = (TString)mvatype;
    //bool isPbPb = (bool)pbpb;
    //double ptmin = ptMin;
    //double ptmax = ptMax;

    //TString inputfile = "/scratch/halstead/x/xiao147/pp2015_correct_dls_agreedARC_0706_backup/add_branches/firetrigger/Dntuple_MB1_whole.root_10.root";


    //    std::cout << "IF TEST" << endl;

    if(istest)
    {
        inputfile = "/scratch/bell/mstojano/d0outputs_new/dataoutputMiniAOD/MinimumBias12/327450_327564/d0ana_PbPb2018_06.root";
        //inputfile = "/scratch/brown/mstojano/d0outputs/dataoutputMiniAOD/MinimumBias12/327450_327564/d0ana_PbPb2018_06.root";
        //inputfile = "/scratch/brown/awesole/ptbinsout/cent_0_10_pt_1_2/mcresults.root";
        //inputfile = "/scratch/brown/mstojano/d0outputs/Dfinder_prompt/miniAOD/output.root";
       //inputfile = "/scratch/brown/awesole/bbothout/smalldataresults.root";
       //inputfile = "/scratch/brown/awesole/aptout/dataresults.root";
      
        outfile1 = "/scratch/bell/awesole/garbage.root";



    }

    TFile* inf = TFile::Open(inputfile);
    //TTree *t = (TTree*)inf->Get("d0ana_mc_genmatchunswap/VertexCompositeNtuple");
    //  std::cout << "OLD TREE" << endl;
    //TTree* t = (TTree*)inf->Get("Dfinder/ntDkpi");
    //TTree *t = (TTree*)inf->Get("T");
   TTree* t = (TTree*)inf->Get("Dfinder/ntDkpi");
   //    std::cout << "TFILE" << endl;
    //                             factory->AddVariable( "dmass := mass-1.864", 'F' ); // for non-prompt D0

    //  std::cout << "DEFINE VARIABLES" << endl;
    const int max_size=30000;
    int ncent,  nDsize=0, ev=0, nDgen[max_size];
    float nmass[max_size], npT[max_size], ny[max_size], n3DDecayLengthSignificance[max_size], nVtxProb[max_size],n3DPointingAngle[max_size],nDtrk1Pt[max_size],nDtrk2Pt[max_size],nDtrk1PtErr[max_size],nDtrk2PtErr[max_size],nDtrk1Chi2n[max_size],nDtrk2Chi2n[max_size], nxyDCASigD1[max_size], nxyDCASigD2[max_size], nzDCASigD1[max_size], nzDCASigD2[max_size], log3ddls[max_size];


    int centrality,  Dsize, Dgen[max_size];
    float mass[max_size], pT[max_size], y[max_size], x3DDecayLengthSignificance[max_size], VtxProb[max_size],x3DPointingAngle[max_size],Dtrk1Pt[max_size],Dtrk2Pt[max_size],Dtrk1PtErr[max_size],Dtrk2PtErr[max_size],Dtrk1Chi2n[max_size],Dtrk2Chi2n[max_size],xyDCASignificanceDaugther1[max_size],xyDCASignificanceDaugther2[max_size],zDCASignificanceDaugther1[max_size],zDCASignificanceDaugther2[max_size];
    double MVA[max_size];
   
      /*    FOR MC FILE~~~~~~~~~~~~~~~~~~
    //   std::cout << "SET OLD BRANCHES" << endl;
    t->SetBranchAddress("nDsize", &Dsize);
   // t->SetBranchAddress("Dgen", Dgen);
    t->SetBranchAddress("nmass", mass);
    t->SetBranchAddress("ncent", &centrality);
    //    t->SetBranchAddress("event", &ev);
    t->SetBranchAddress("npT", pT);
    t->SetBranchAddress("ny", y);
    t->SetBranchAddress("nDtrk1PtErr", Dtrk1PtErr);
    t->SetBranchAddress("nDtrk2PtErr", Dtrk2PtErr);
    t->SetBranchAddress("nDtrk1Chi2n", Dtrk1Chi2n);
    t->SetBranchAddress("nDtrk2Chi2n", Dtrk2Chi2n);
    t->SetBranchAddress("n3DDecayLengthSignificance", x3DDecayLengthSignificance);
    t->SetBranchAddress("nVtxProb", VtxProb);
    t->SetBranchAddress("n3DPointingAngle", x3DPointingAngle);
    t->SetBranchAddress("nDtrk1Pt", Dtrk1Pt);
    t->SetBranchAddress("nDtrk2Pt", Dtrk2Pt);
    t->SetBranchAddress("nxyDCASigD1", xyDCASignificanceDaugther1);
    t->SetBranchAddress("nxyDCASigD2", xyDCASignificanceDaugther2);
    t->SetBranchAddress("nzDCASigD1", zDCASignificanceDaugther1);
    t->SetBranchAddress("nzDCASigD2", zDCASignificanceDaugther2);
*/


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //   std::cout << "SET OLD BRANCHES" << endl;
    t->SetBranchAddress("Dsize", &Dsize);
   // t->SetBranchAddress("Dgen", Dgen);
    t->SetBranchAddress("mass", mass);
    t->SetBranchAddress("centrality", &centrality);
    //    t->SetBranchAddress("event", &ev);
    t->SetBranchAddress("pT", pT);
    t->SetBranchAddress("y", y);
    t->SetBranchAddress("Dtrk1PtErr", Dtrk1PtErr);
    t->SetBranchAddress("Dtrk2PtErr", Dtrk2PtErr);
    t->SetBranchAddress("Dtrk1Chi2n", Dtrk1Chi2n);
    t->SetBranchAddress("Dtrk2Chi2n", Dtrk2Chi2n);
    t->SetBranchAddress("3DDecayLengthSignificance", x3DDecayLengthSignificance);
    t->SetBranchAddress("VtxProb", VtxProb);
    t->SetBranchAddress("3DPointingAngle", x3DPointingAngle);
    t->SetBranchAddress("Dtrk1Pt", Dtrk1Pt);
    t->SetBranchAddress("Dtrk2Pt", Dtrk2Pt);
    t->SetBranchAddress("xyDCASignificanceDaugther1", xyDCASignificanceDaugther1);
    t->SetBranchAddress("xyDCASignificanceDaugther2", xyDCASignificanceDaugther2);
    t->SetBranchAddress("zDCASignificanceDaugther1", zDCASignificanceDaugther1);
    t->SetBranchAddress("zDCASignificanceDaugther2", zDCASignificanceDaugther2);
    //TFile *outf = new TFile("/scratch/brown/awesole/bdtsmallsignal.root","recreate");
    //   TFile *outf = new TFile("/scratch/brown/awesole/bdtsignal.root","recreate");
    //  std::cout<<__LINE__<<std::endl;
    //    std::cout << "OUTFILE" << endl;

    TFile *outf = new TFile(outfile1,"recreate");

    //  std::cout<<__LINE__<<std::endl;
    //    std::cout<< "NEW TREE" << endl;
    TTree *mvaTree = new TTree("mvaTree","MVA");



    //  std::cout << "NEW TREE BRANCHES" << endl;
    mvaTree->Branch("nDsize",&nDsize,"nDsize/I");
    //mvaTree->Branch("nDgen", nDgen, "nDgen[nDsize]/I");
    mvaTree->Branch("nmass", nmass, "nmass[nDsize]/F");
    mvaTree->Branch("ncent", &ncent, "ncent/I");
    mvaTree->Branch("npT", npT, "npT[nDsize]/F");
    mvaTree->Branch("ny", ny, "ny[nDsize]/F");
    mvaTree->Branch("nDtrk1PtErr", nDtrk1PtErr,"nDtrk1PtErr[nDsize]/F");
    mvaTree->Branch("nDtrk2PtErr", nDtrk2PtErr,"nDtrk2PtErr[nDsize]/F");
    mvaTree->Branch("nDtrk1Chi2n", nDtrk1Chi2n,"nDtrk1Chi2n[nDsize]/F");
    mvaTree->Branch("nDtrk2Chi2n", nDtrk2Chi2n,"nDtrk2Chi2n[nDsize]/F"); 

    mvaTree->Branch("n3DDecayLengthSignificance", n3DDecayLengthSignificance, "n3DDecayLengthSignificance[nDsize]/F");
    mvaTree->Branch("log3ddls", log3ddls, "log3ddls[nDsize]/F");
    mvaTree->Branch("nVtxProb",nVtxProb , "nVtxProb[nDsize]/F");
    mvaTree->Branch("n3DPointingAngle", n3DPointingAngle,"n3DPointingAngle[nDsize]/F");
    mvaTree->Branch("nDtrk1Pt", nDtrk1Pt,"nDtrk1Pt[nDsize]/F");
    mvaTree->Branch("nDtrk2Pt", nDtrk2Pt,"nDtrk2Pt[nDsize]/F");
    mvaTree->Branch("nxyDCASigD1", nxyDCASigD1,"nxyDCASigD1[nDsize]/F");
    mvaTree->Branch("nxyDCASigD2", nxyDCASigD2,"nxyDCASigD2[nDsize]/F");
    mvaTree->Branch("nzDCASigD1", nzDCASigD1,"nzDCASigD1[nDsize]/F");
    mvaTree->Branch("nzDCASigD2", nzDCASigD2,"nzDCASigD2[nDsize]/F");

    mvaTree->Branch("BDT_weight",MVA,"BDT_weight[nDsize]/D");
    //   std::cout << "SET VARIABLE VECTOR" << endl;

std::vector<std::string> theInputVars;
    string a1="log3ddls"; 
    string a2="nVtxProb"; 
    string a3="n3DPointingAngle"; 
    string a4="nDtrk1Pt"; 
    string a5="nDtrk2Pt"; 
    string a6="nxyDCASigD1";
    string a7="nxyDCASigD2";
    string a8="nzDCASigD1";
    string a9="nzDCASigD2";

/*  
     std::vector<std::string> theInputVars;
    string a1="VtxProb"; 
    string a2="log10_3DDecayLengthSignificance"; 
    string a3="3DPointingAngle"; 
    string a4="pTD1"; 
    string a5="pTD2"; 
    string a6="xyDCASignificanceDaugther1";
    string a7="xyDCASignificanceDaugther2";
    string a8="zDCASignificanceDaugther1";
    string a9="zDCASignificanceDaugther2";

*/


    theInputVars.push_back(a1);
    theInputVars.push_back(a2);
    theInputVars.push_back(a3);
    theInputVars.push_back(a4); 
    theInputVars.push_back(a5); 
    theInputVars.push_back(a6);
    theInputVars.push_back(a7);
    theInputVars.push_back(a8);
    theInputVars.push_back(a9);



    //  std::cout << "SET VALUE VECTOR" << endl;
    std::vector<double> inputValues;
    //    std::cout << "RED BDT" << endl;
ReadBDT mva(theInputVars);
//ReadBDT_cent_0_10_pt_1_2_ mva_cent_0_10_pt_1_2_(theInputVars);
////////////////ReadBDT_pt_1_2_cen0_10 mva_pt_1_2_cen0_10(theInputVars);


  for (int i=0; i<t->GetEntries(); i++) 
  //for (int i=0; i<1000; i++)
//for (int i=0; i<2; i++)
        {
            t->GetEntry(i);
            ev = ev+1;
            ncent=centrality;
            nDsize=0;
            if (i % 10000 == 0){
                cout << i << "/" << t->GetEntries() << endl;
            }
            //    if (i % 50 == 0){
            //oniiiily copy branches where mass is in specified range   
            for (int j=0; j<Dsize; j++)
            {
            if (TMath::IsNaN(x3DDecayLengthSignificance[j])) continue;
	    if (TMath::IsNaN(nxyDCASigD2[j])) continue;
	    if (TMath::IsNaN(nzDCASigD2[j])) continue;
            //if (pT[j]>=1 && pT[j]<2 && Dtrk1Pt[j]>1.0 && Dtrk2Pt[j] >1.0 && Dtrk1Chi2n[j] < 0.18 && Dtrk2Chi2n[j] < 0.18 && centrality>0 && centrality<20 && zDCASignificanceDaugther2[j]>-200 && zDCASignificanceDaugther2[j]<200){
            if (pT[j]>=1 && pT[j]<2 && Dtrk1Pt[j]>1.0 && Dtrk2Pt[j] >1.0 && Dtrk1Chi2n[j] < 0.18 && Dtrk2Chi2n[j] < 0.18 && centrality>0 && centrality<20) 
{
            //if (centrality>=0 && centrality<20){
//cout << "DCA=" << zDCASignificanceDaugther2[j] << endl;
                    nDsize = nDsize+1;
                    nDgen[nDsize-1] = Dgen[j];
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

                inputValues.clear();
                inputValues.push_back(log10(x3DDecayLengthSignificance[j]));//00
                inputValues.push_back(VtxProb[j]);//01
                inputValues.push_back(x3DPointingAngle[j]);//02
                inputValues.push_back(Dtrk1Pt[j]);//03
                inputValues.push_back(Dtrk2Pt[j]);//04
                inputValues.push_back(xyDCASignificanceDaugther1[j]);//04
                inputValues.push_back(xyDCASignificanceDaugther2[j]);//04
                inputValues.push_back(zDCASignificanceDaugther1[j]);//04
                inputValues.push_back(zDCASignificanceDaugther2[j]);
                //MVA[nDsize-1]=mva_cent_0_10_pt_1_2_.GetMvaValue_cent_0_10_pt_1_2_(inputValues);      
                MVA[nDsize-1]=mva.GetMvaValue(inputValues);      
               ////////////MVA[nDsize-1]=mva_pt_1_2_cen0_10.GetMvaValue_pt_1_2_cen0_10(inputValues);      


                }//ifpt

            }//forDsize
            if(nDsize>0){
                mvaTree->Fill();
            }
        }//forentries
        
	    outf->cd();
    mvaTree->Write(0, TObject::kOverwrite);
    outf->Close();
    return 0;
}

int main(int argc, char *argv[])
{
    if(istest) argc=3;
    if(argc==3)
    {
        dataBDT(argv[1], argv[2]);
    }
    else
    {
        std::cout << "Usage: mergeForest <input_collection> <output_file>" << std::endl;
        return 1;
    }
    return 0;


}


