//CHANGE LINES 168-170
///THIS PROGRAM GENERATES BACKGROUND SAMPLE USED FOR BDT TRAINING 
//IT CAN BE USED FOR SEVERAL PT RANGES OR JUST ONE

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <vector>
#include <TMath.h>
#include<fstream>
#include<string>
#include <iostream>
using namespace std;

void multifiledataloop()
    //void multifiledataloop(int istart, int iend)
{
    const int max_size =10000;
    int abby = 1;
//DECLARE FILE INPUT LIST AND OUTOUT FILE 
   ifstream file_stream("/home/awesole/backup_brown/party/list.txt");
    TFile results("/scratch/bell/awesole/nochi2n_1127.root", "recreate"); //edit me!!!!!!!!!
    //TFile results("/scratch/brown/awesole/ptbinsout/cent_10_30_pt_5_6/dataresults.root", "recreate"); //edit me!!!!!!!!!
    //TFile results("/scratch/brown/awesole/ptbinsout/cent_30_50_pt_4_5/dataresults.root", "recreate"); //edit me!!!!!!!!!
   // TFile results("/scratch/brown/awesole/ptbinsout/cent_50_90_pt_8_30/dataresults.root", "recreate"); //edit me!!!!!!!!!
    TTree *newtree = new TTree("T" , "Background Sample");

    string filename;

    //int  nDsize=0, ev=0, tracker=0, ptmin, ptmax, cmin=0, cmax=20, tmax, ifile=0; //edit me!!!!!!!!!!!
    //int  nDsize=0, ev=0, tracker=0, ptmin, ptmax , cmin=20, cmax=60, tmax, ifile=0; //edit me!!!!!!!!!!!
    //int  nDsize=0, ev=0, tracker=0, ptmin,  ptmax , cmin=60, cmax=100, tmax, ifile=0; //edit me!!!!!!!!!!!
    int  nDsize=0,  tracker=0, ptmin, ptmax, cmin=0, cmax=20, tmax, ifile=0; //edit me!!!!!!!!!!!

    float amass, sd;
    int Dsize, centrality, ev=0, EvtNo;
    float  mass[max_size], pT[max_size], y[max_size], x3DDecayLengthSignificance[max_size],VtxProb[max_size],x3DPointingAngle[max_size],Dtrk1Pt    [max_size],Dtrk2Pt[max_size],Dtrk1PtErr[max_size],Dtrk2PtErr[max_size],Dtrk1Chi2n[max_size],Dtrk2Chi2n[max_size],xyDCASignificanceDaugther1[max_size],xyDCASignificanceDaugther2[max_size],zDCASignificanceDaugther1[max_size],zDCASignificanceDaugther2[max_size] ;
    int ncent;
    float nmass[max_size], npT[max_size], ny[max_size], n3DDecayLengthSignificance[max_size], nVtxProb[max_size], n3DPointingAngle[max_size],nDtrk1Pt[max_size], nDtrk2Pt[max_size], nDtrk1PtErr[max_size], nDtrk2PtErr[max_size], nDtrk1Chi2n[max_size], nDtrk2Chi2n[max_size], nxyDCASigD1[max_size], nxyDCASigD2[max_size], nzDCASigD1[max_size], nzDCASigD2[max_size], log3ddls[max_size];

//DECLARE BRANCHES OF NEW TREE
    newtree->Branch("nDsize",&nDsize,"nDsize/I");
    newtree->Branch("nmass", nmass, "nmass[nDsize]/F");
    newtree->Branch("ncent", &ncent, "ncent/I");
    newtree->Branch("event", ev, "ev/I");
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

//ONLY NECESSARY FOR ONE PT RANGE, SPECIFY ABBY VALUE TO ONLY INCLUDE 1 PT RAGNE
    if(abby==1) {
        ptmin=1;
        ptmax=2;}
    if(abby==2) {
        ptmin=2;
        ptmax=3;}
    if(abby==3) {
        ptmin=3;
        ptmax=4;}
    if(abby==4) 
    {ptmin=4;
        ptmax=5;}
    if(abby==5) 
    {ptmin=5;
        ptmax=6;}
    if(abby==6) 
    {ptmin=6;
        ptmax=8;}
    if(abby==8) 
    {ptmin=8;
        ptmax=10;}
    if(abby==10) {
        ptmin=10;
        ptmax=15;}
    if(abby==15) 
    {ptmin=15;
        ptmax=20;}
    if(abby==20) 
    {ptmin=20;
        ptmax=30;}
    if(abby==830) 
    {ptmin=8;
        ptmax=30;}






//DECLARE AVERAGE AND SD FOR EACH PT RANGE
//THESE VALUES COME FROM THE HISTOGRAMS OF EACH PT RANGE
//TMAX IS EQUAL TO 10X THE NUMBER OF ENTIRES IN HISTOGRAM
        if(ptmin==1 && ptmax==2)
    {
        amass=1.867;
        sd=0.01271;
        //sd=0.01075;///soumik
     tmax=55710;
        /////tmax=10;
    }

    if(ptmin==2 && ptmax==3)
    {
        amass=1.867;
        sd=0.01269;
        tmax=180710;
    }

    if(ptmin==3 && ptmax==4)
    {
        amass=1.867;
        sd=0.01237;
        tmax=216530;
    }

    if(ptmin==4 && ptmax==5)
    {
        amass=1.867;
        sd=0.0119;
        tmax=145050;
    }

    if(ptmin==5 && ptmax==6)
    {
        amass=1.866;
        sd=0.01204;
        tmax=83860;
    }

    if(ptmin==6 && ptmax==8)
    {
        amass=1.866;
        sd=0.01183;
        tmax=78340;
    }

    if(ptmin==8 && ptmax==10)
    {
        amass=1.866;
        sd=0.01168;
        tmax=177680;
    }

    if(ptmin==10 && ptmax==15)
    {
        amass=1.866;
        sd=0.01173;
        tmax=291330;
    }

    if(ptmin==15 && ptmax==20)
    {
        amass=1.866;
        sd=0.01284;
        tmax=60150;
    }

    if(ptmin==20 && ptmax==30)
    {
        amass=1.866;
        sd=0.01316;
        tmax=141500;
    }
    if(ptmin==8 && ptmax==30) //CHANGE THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {
        amass=1.866;
        sd=0.01316;
        tmax=141500;
    }

//WHILE LOOP FOR ALL FILES    
while(true) {

        if(tracker>tmax) break;
        file_stream >> filename;
        if(file_stream.eof()) break;
        /*
        if(ifile < istart) {
            ifile++;
            continue;
        }

        if(ifile >= iend)
            break;
            */
        cout << "ifile=" << ifile << endl;
        TFile *fin = TFile::Open(filename.c_str());
        if(fin->IsZombie() || fin->Get("Dfinder/ntDkpi")==nullptr) {
            ifile ++;
            continue;
        }
        TDirectory* dir = (TDirectory*)fin->Get("Dfinder");
        TTree *tree = (TTree*)dir->Get(Form("ntDkpi"));


        //for all entries in the tree
	tree->SetBranchAddress("EvtNo",&EvtNo);
        tree->SetBranchAddress("Dsize", &Dsize);
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
        for (int i=0; i<nentries; i++)
        //     for (int i=0; i<200; i++)
        {
            tree->GetEntry(i);
            ncent=centrality;
	    ev = ev+1;
            nDsize=0;
            if (i % 100000 == 0){
                cout << i << "/" << nentries << endl;
            }
            //   if (i % 3 == 0){
            //oniiiily copy branches where mass is in specified range   
            if(tracker>tmax) break;

            if(centrality>=cmin && centrality<cmax)
            {
                for (int j=0; j<Dsize; j++)
                {
                    if (TMath::IsNaN(x3DDecayLengthSignificance[j])) continue;
                    if (TMath::IsNaN(nxyDCASigD2[j])) continue;
                    if (TMath::IsNaN(nzDCASigD2[j])) continue;

                    //if (((mass[j] > amass-6*sd && mass[j] < amass-3*sd) || (mass[j] < amass+6*sd && mass[j]>amass+3*sd)) && pT[j]>=ptmin && pT[j] <ptmax && y[j]>-1 && y[j] <1 && Dtrk1Chi2n[j] < 0.18 && Dtrk2Chi2n[j] < 0.18 && x3DPointingAngle[j]<0.2)  //for alpha cuts only
                    if (((mass[j] > amass-6*sd && mass[j] < amass-3*sd) || (mass[j] < amass+6*sd && mass[j]>amass+3*sd)) && pT[j]>=ptmin && pT[j] <ptmax && y[j]>-1 && y[j] <1 && Dtrk1Chi2n[j] < 0.18 && Dtrk2Chi2n[j] < 0.18) //Original
                    //if (((mass[j] > amass-6*sd && mass[j] < amass-3*sd) || (mass[j] < amass+6*sd && mass[j]>amass+3*sd)) && pT[j]>=ptmin && pT[j] <ptmax  && y[j]>-1 && y[j] <1) //Original
                    //if (((mass[j] > amass-6*sd && mass[j] < amass-3*sd) || (mass[j] < amass+6*sd && mass[j]>amass+3*sd)) && pT[j]>=ptmin && pT[j] <ptmax && y[j]>-1 && y[j] <1 && Dtrk1Chi2n[j] < 0.18 && Dtrk2Chi2n[j] < 0.18 && zDCASignificanceDaugther2[j]<200 && zDCASignificanceDaugther2[j]>-200) //cuts on DCAsignificance D2
                            {
                        tracker = tracker+1;
                        nDsize = nDsize+1;
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

//cout << "dsize=" << nDsize << "evt=" << ev  << "mass=" << mass[j] << endl;
                    }//if in side bands

                }//for dsize
                if(nDsize>0){
                    newtree->Fill();
                }
            }//if centrality
            //         }//if i%2
        }//for entries
        cout << "tracker=" << tracker << endl;
        ifile++;
        fin->Close();
    }//while
        results.cd();
        newtree->Write();
        results.Write();
        results.Close();
}//program

int main(int argc, char *argv[])
{
    /*
    if(argc==3)
    {
        multifiledataloop(argv[1], argv[2]);
    }    
   */
    if(argc==1)
    {
        multifiledataloop();
    }    
    else
    {
        std::cout << "Usage: mergeForest <input_collection> <output_file>" << std::endl;
        return 1;
    }
    return 0;


}
