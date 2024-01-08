//GENERATES HISTO GRAM FOR SIGNAL AND SIGNAL+SWAP FOR EACH PT RANGE.
//THE FIELS ARE NEEDED FOR FITTING
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
Bool_t istest =true;
int histos(TString inputfile="", TString outfile1="")
{
    //    TFile *inf = TFile::Open("/scratch/brown/awesole/bdtbg.root");

    if(istest)
    {
        //inputfile="/scratch/brown/awesole/output/Dntuple_d0ana_PbPb2018_04.root_327.root";
        inputfile="/scratch/brown/mstojano/d0outputs/Dfinder_prompt/miniAOD/output.root";
//        outfile1="/scratch/brown/awesole/ptbinsout/massfits/pt_1_2histos.root";
    }

    int ptmin, ptmax;
    for (int range=0; range<10; range++)
    {
        if(range==0)
        {
        ptmin =1;
        ptmax=2;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_1_2histos.root";
        }
         if(range==1)
        {
        ptmin =2;
        ptmax=3;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_2_3histos.root";
        }
         if(range==2)
        {
        ptmin =3;
        ptmax=4;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_3_4histos.root";
        }
         if(range==3)
        {
        ptmin =4;
        ptmax=5;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_4_5histos.root";
        }
         if(range==4)
        {
        ptmin =5;
        ptmax=6;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_5_6histos.root";
        }
         if(range==5)
        {
        ptmin =6;
        ptmax=8;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_6_8histos.root";
        }
         if(range==6)
        {
        ptmin =8;
        ptmax=10;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_8_10histos.root";
        }
         if(range==7)
        {
        ptmin =10;
        ptmax=15;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_10_15histos.root";
        }
         if(range==8)
        {
        ptmin =15;
        ptmax=20;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_15_20histos.root";
        }
         if(range==9)
        {
        ptmin =20;
        ptmax=30;
        outfile1="/scratch/brown/awesole/ptbinsout/massfits/updatept_20_30histos.root";
        }
 
     
        TFile* inf = TFile::Open(inputfile);
    //TTree *t = (TTree*)inf->Get("mvaTree");
    TTree *t = (TTree*)inf->Get("Dfinder/ntDkpi");
    t->SetMakeClass(1);
    TFile *outf = new TFile(outfile1,"recreate");

    int Dsize, Dgen[10000], centrality;
    float pT[10000], mass[10000], y[10000], Dtrk1Chi2n[10000], Dtrk2Chi2n[10000];

    std::vector<TH1D*> vlist;
    //vlist.resize(10);
    vlist.resize(3);
    std::vector<float> massdata;


    //for (int i=0; i<10; i++)
    for (int i=0; i<2; i++)
    {
        vlist[i]=new TH1D(Form("histo_%d",i),Form("histo_%d",i), 52, 1.74, 2);

    }
        t->SetBranchAddress("Dsize", &Dsize); 
        t->SetBranchAddress("centrality", &centrality);
        t->SetBranchAddress("pT", pT);
        t->SetBranchAddress("mass", mass);
        t->SetBranchAddress("Dgen", Dgen);
        t->SetBranchAddress("y", y);
        t->SetBranchAddress("Dtrk1Chi2n", Dtrk1Chi2n);
        t->SetBranchAddress("Dtrk2Chi2n", Dtrk2Chi2n);
    for(int i=0;i<t->GetEntries();i++)
    //   for(int i=0;i<10000;i++)
    {
        t->GetEntry(i);

        if(i%100000==0) cout <<i<<" / "<<t->GetEntries()<<endl;
        if(centrality<0 || centrality>=20) continue;
        //   for(int j=0; j<Dsize; j++)
        for(int j=0; j<Dsize; j++)
        {
            //    cout << "j= " << j << endl;
            //         cout << "pT[j]= " << pT[j] << endl;
            //         cout << "mass[j]= " << mass[j] << endl;
            if(pT[j]>=ptmin && pT[j]<ptmax && y[j]>-1 && y[j] <1 && Dtrk1Chi2n[j] < 0.18 && Dtrk2Chi2n[j]<0.18)
            {
                if(Dgen[j]==23333)
                {
                    vlist[0]->Fill(mass[j]);
                }//if dgen ==23333

                if(Dgen[j]==23333 || Dgen[j]==23344)
                {
                    vlist[1]->Fill(mass[j]);
                }//if dgen==23333||23344
            }
            /*
               if(pT[j]<4  || Dgen[j]==23333 || Dgen[j]==23344)
               {
               vlist[2]->Fill(mass[j]);
               }//if pT

*/
            /*
               if (pT[j]>1 && pT[j]<2){
               vlist[0]->Fill(mass[j]);
               }//if pT
               if (pT[j]>2 && pT[j]<3){
               vlist[1]->Fill(mass[j]);
               }//if pT
               if (pT[j]>3 && pT[j]<4){
               vlist[2]->Fill(mass[j]);
               }//if pT
               if (pT[j]>4 && pT[j]<5){
               vlist[3]->Fill(mass[j]);
               }//if pT
               if (pT[j]>5 && pT[j]<6){
               vlist[4]->Fill(mass[j]);
               }//if pT
               if (pT[j]>6 && pT[j]<8){
               vlist[5]->Fill(mass[j]);
               }//if pT
               if (pT[j]>8 && pT[j]<10){
               vlist[6]->Fill(mass[j]);
               }//if pT
               if (pT[j]>10 && pT[j]<15){
               vlist[7]->Fill(mass[j]);
               }//if pT
               if (pT[j]>15 && pT[j]<20){
               vlist[8]->Fill(mass[j]);
               }//if pT
               if (pT[j]>20 && pT[j]<30){
               vlist[9]->Fill(mass[j]);
               }//if pT
               */
            //  cout << "END OF FOR DSIZE LOOP" << endl;
            //           t->ResetBranchAddresses();
            //           t->SetBranchAddress("nDsize", &Dsize); 
        }//for nDsizpe
        //cout << "END OF ENTRIES LOOP" << endl;
        //      cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }//for entries 
    outf->Write();
    outf->Close();
    }//fot pt ranges
    return 0;
    }//function 


int main(int argc, char *argv[])
{
    if(istest) argc=3;
    if(argc==3)
    {
        histos(argv[1], argv[2]);
    }
    else
    {
        std::cout << "Usage: mergeForest <input_collection> <output_file>" << std::endl;
        return 1;
    }
    return 0;
}
