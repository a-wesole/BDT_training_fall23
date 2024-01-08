//fits each plot with the function, and generates bdt scan plot for each centrality.

//add 3 lines, signal, swap and background
//canvas->save as to save all as pdfs
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


int fit_bdtscan()
{

    TString inputfile = "/scratch/bell/awesole/backup_from_brown/ptbinsout/massfits/pt_1_2histos.root";//from MC
    //TString inputfile = "/scratch/brown/awesole/ptbinsout/massfits/pt_1_2histos.root";//from MC
    //TString inputfile = "/scratch/brown/awesole/ptbinsout/massfits/pt_20_30histos.root";//from MC
//    TString inputfile = "/scratch/brown/awesole/ptbinsout/massfits/pt_6_8histos.root";//from MC
    TFile* inf = TFile::Open(inputfile);

    //TString inputfile1 = "/scratch/brown/awesole/bdt_again/hist/mergedfile.root";//data file
    //TString inputfile1 = "/scratch/brown/awesole/bdt_redo/histos/mergedfile.root";//data file
//    TString inputfile1 = "/scratch/brown/awesole/bdt_redo/histos1/mergedfile.root";//data file
TString inputfile1 = "/scratch/bell/awesole/backup_from_brown/soumikhisto/mergedfile.root";//SOUMIK ORIGINAL FILE
////   TString inputfile1 = "/scratch/bell/awesole/cutson3ddls_1127/histo/mergedfile.root";//no cuts on chi2n
   //TString inputfile1 = "/scratch/bell/awesole/log33ddls_cuts/mergedfile.root";//cuts 3ddls>0.5 data file
//   TString inputfile1 = "/scratch/bell/awesole/backup_from_brown/redobdt/mergedfile.root";//MY ORIGINAL data file
//TString inputfile1 = "/scratch/bell/awesole/newhistos/mergedfile.root";    //ONLY MASS CUTS NEW BACKGROUND TRAINING FILE

//TString inputfile1 = "/scratch/bell/awesole/3ycuts/mergedfile.root";//CUTS ON MASS AND SD
//TString inputfile1 = "/scratch/bell/awesole/dcacutsat200_11_16_histo/mergedfile.root";//CUTS ON MASS AND SD
//TString inputfile1 = "/scratch/bell/awesole/alphacuts_1126/histos/mergedfile.root";//CUTS ON ALPHA
    //TString inputfile1 = "/scratch/brown/awesole/soumikhisto/mergedfile.root";//data file
    //TString inputfile1 = "/scratch/brown/awesole/turtle/histos/mergedfile.root";//data file
//    TString inputfile1 = "/scratch/brown/awesole/ptbinsout/histos/mergedfile.root";//data file
    TFile* inf1 = TFile::Open(inputfile1);


    TH1D *h1 = (TH1D*)inf->Get("histo_0");
    h1->SetMinimum(0);
    TH1D *h2 = (TH1D*)inf->Get("histo_1");
    h2->SetMinimum(0);

    double ilist [25] = {-0.6, -0.55, -0.5, -0.45, -0.4, -0.35, -0.3, -0.25, -0.2, -0.15, -0.1, -0.05, 0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6};
    double jlist[165];
    std::vector<TH1D*> hlist;
    hlist.resize(165);


    for(int i=0; i<25; i++){
        hlist[i] = (TH1D*)inf1->Get(Form("aahisto_%d",i));//from data file
    hlist[i]->SetMinimum(0);
    hlist[i]->SetTitle(Form("BDT>%.2f", ilist[i]));
    }//for 
    for(int i=0; i<25; i++)
    {
        jlist[i]=0;
    }
    double fit_range_low = 1.74;
    double fit_range_high = 2.0;
    double D0_mass = 1.8648;

    double yield0[25];
    double error0[25];
    double yield1[17];
    double error1[17];
    double yield2[17];
    double error2[17];
    double yield3[17];
    double error3[17];
    double yield4[17];
    double error4[17];
    double yield5[17];
    double error5[17];
    double yield6[17];
    double error6[17];
    double yield7[17];
    double error7[17];
    double yield8[17];
    double error8[17];
    double yield9[17];
    double error9[17];
    double plot0[25];
    double plot1[17];
    double plot2[17];
    double plot3[17];
    double plot4[17];
    double plot5[17];
    double plot6[17];
    double plot7[17];
    double plot8[17];
    double plot9[17];

    TF1* f = new TF1("original function","[0]*([5]*([4]*TMath::Gaus(x,[1],[2]*(1.0 +[6]))/(sqrt(2*3.14159)*[2]*(1.0 + [6]))+(1-[4])*TMath::Gaus(x,[1],[3]*(1.0 +[6]))/(sqrt(2*3.14159)*[3]*(1.0 +[6])))+(1-[5])*TMath::Gaus(x,[1],[7]*(1.0 +[6]))/(sqrt(2*3.14159)*[7]*(1.0 +[6])))+ [8] + [9]*x + [10]*x*x + [11]*x*x*x   ", fit_range_low, fit_range_high);
    // TF1* f = new TF1("original function","[0]*([4]*TMath::Gaus(x,[1],[2]*(1.0 +[6]))/(sqrt(2*3.14159)*[2]*(1.0 + [6]))+(1-[4])*TMath::Gaus(x,[1],[3]*(1.0 +[6]))/(sqrt(2*3.14159)*[3]*(1.0 +[6])))+ [7] + [8]*x + [9]*x*x + [5]*x*x*x   ", fit_range_low, fit_range_high);

    //for (int i=13; i<15; i++)
  for (int i=0; i<19; i++)
    {

        //SetParNames/////////////EP//////////////////////////////////////////////////////////////////////////////
        TCanvas *c1 = new TCanvas("c1", "c1", 800,600);
        f->SetLineColor(2);
        f->SetLineWidth(2);
        f->SetParNames("signal+swap", "mean mass", "sigma 1", "sigma 2", "amplitude", "signalc", "scaling", "sigma swap", "const","x", "x*x");
        f->SetParName(11, "x*x*x");
        f->SetParameter(0,100.);//signal plus swap
        f->SetParameter(1,D0_mass);//mean mass
        f->SetParameter(2,0.03);//sigma 1
        f->SetParameter(3,0.005);//sigma 2
        f->SetParameter(4,0.1);//ratio between first and second guassian

        f->FixParameter(5,1);//fraction that is signal
        f->FixParameter(6,0); //scaling factor----------always 0 in MC
        f->FixParameter(7,0.1); //sigma of swap-------------- does not really mater here as yield is fix to 0
        //f->SetParameter(8,D0_mass);//mean of swap
        f->FixParameter(8,0);//polynomial
        f->FixParameter(9,0);//polynomial
        f->FixParameter(10,0);//polynomail
        f->FixParameter(11,0);//poly

        //f->SetParLimits(1,1.85,1.87);//sigma 1
        f->SetParLimits(2,0.01,0.1);//sigma 1
        f->SetParLimits(3,0.001,0.05);//sigma 2
        f->SetParLimits(4,0,1);//amplitude/ratio
        f->SetParLimits(5,0,1);//fraction of signal

        f->FixParameter(1,1.8648);//mean mass

        h1->Fit(f,"q","",fit_range_low,fit_range_high);
        h1->Fit(f,"q","",fit_range_low,fit_range_high);
        f->ReleaseParameter(1);//mean mass
        h1->Fit(f,"q","",fit_range_low,fit_range_high);
        h1->Fit(f,"q","",fit_range_low,fit_range_high);
        h1->Fit(f,"q","",fit_range_low,fit_range_high);
        ////h1->Fit(f,"m q","",fit_range_low,fit_range_high);
        //h1->Fit(f,"q","",fit_range_low,fit_range_high);

        f->FixParameter(1,f->GetParameter(1));//mean mass
        f->FixParameter(2,f->GetParameter(2));//sigma 1
        f->FixParameter(3,f->GetParameter(3));//sigma 2
        f->FixParameter(4,f->GetParameter(4));//ratio/amplitude

        f->ReleaseParameter(5);//fraction of signal
        f->ReleaseParameter(7);//sigma swap

        f->SetParameter(7,0.1);//sigma swap
        h2->Fit(f,"L q","",fit_range_low,fit_range_high);
        h2->Fit(f,"L q","",fit_range_low,fit_range_high);
        h2->Fit(f,"L q","",fit_range_low,fit_range_high);
        h2->Fit(f,"L q","",fit_range_low,fit_range_high);
        h2->Fit(f,"L q","",fit_range_low,fit_range_high);
        /////h2->Fit(f,"m q","",fit_range_low,fit_range_high);
        //h2->Fit(f,"L q","",fit_range_low,fit_range_high);
        double fe= f->GetParError(5);//fraction of signal

        f->FixParameter(5,f->GetParameter(5));//fraction of signal
        f->FixParameter(7,f->GetParameter(7));//sigma swap

        
        f->ReleaseParameter(8);//poly
        f->ReleaseParameter(9);//poly
        f->ReleaseParameter(10);//poly
        f->ReleaseParameter(11);//12



        hlist[i]->Fit(f,"q","",fit_range_low,fit_range_high);
        hlist[i]->Fit(f,"q","",fit_range_low,fit_range_high);

        f->ReleaseParameter(1); //mean mass ------allow data to have different mass peak mean than MC
        f->SetParLimits(1, 1.86, 1.87);

        hlist[i]->Fit(f,"L q","",fit_range_low,fit_range_high);
        hlist[i]->Fit(f,"L q","",fit_range_low,fit_range_high);

        f->ReleaseParameter(6); //mean mass ------allow data to have different mass peak mean than MC
        f->SetParLimits(6, -0.5, 0.5);
        /*
        f->ReleaseParameter(6); //ratio ------- allow data to have different peak width than MC
        f->SetParameter(6,0);//scaling factor
        f->SetParLimits(6,-1,1);//scaling factor
        */
        hlist[i]->Fit(f,"L q","",fit_range_low,fit_range_high);
        hlist[i]->Fit(f,"L q","",fit_range_low,fit_range_high);
        hlist[i]->Fit(f,"L q","",fit_range_low,fit_range_high);
        hlist[i]->Fit(f,"L q","",fit_range_low,fit_range_high);///

        hlist[i]->Fit(f,"m","",fit_range_low,fit_range_high);///



        TF1* signal = new TF1("signal","([0]*[5]*([4]*TMath::Gaus(x,[1],[2]*(1.0+[6]))/(sqrt(2*3.14159)*[2]*(1.0+[6]))+(1-[4])*TMath::Gaus(x,[1],[3]*(1.0+[6]))/(sqrt(2*3.14159)*[3]*(1.0+[6]))))",fit_range_low, fit_range_high);
        signal->FixParameter(0,f->GetParameter(0));
        signal->FixParameter(1,f->GetParameter(1));
        signal->FixParameter(2,f->GetParameter(2));
        signal->FixParameter(3,f->GetParameter(3));
        signal->FixParameter(4,f->GetParameter(4));
        signal->FixParameter(5,f->GetParameter(5));
        signal->FixParameter(6,f->GetParameter(6));

        

        TF1* swap = new TF1("swap", "[0]*((1-[5])*(TMath::Gaus(x,[1],[7]*(1.0+[6]))/(sqrt(2*3.14159)*[7]*(1.0+[6]))))", fit_range_low, fit_range_high);
        swap->FixParameter(0,f->GetParameter(0));
        swap->FixParameter(1,f->GetParameter(1));
        swap->FixParameter(5,f->GetParameter(5));
        swap->FixParameter(6,f->GetParameter(6));
        swap->FixParameter(7,f->GetParameter(7));

        TF1* background = new TF1("background", "[8] + [9]*x + [10]*x*x + [11]*x*x*x", fit_range_low, fit_range_high);
        background->FixParameter(8,f->GetParameter(8));
        background->FixParameter(9,f->GetParameter(9));
        background->FixParameter(10,f->GetParameter(10));
        background->FixParameter(11,f->GetParameter(11));

        double maxi = 1.25*(hlist[i]->GetMaximum());
        hlist[i]->SetMaximum(maxi);
        hlist[i]->Draw("EP");
        signal->SetLineColor(4);
        signal->Draw("same");
        swap->SetLineColor(8);
        swap->Draw("same");
        background->SetLineColor(1);
        background->Draw("same");
        f->SetLineColor(2);
        f->Draw("same");
        gStyle->SetOptFit(0002);
        TPaveStats *st = (TPaveStats*)hlist[i]->FindObject("stats");
        st->SetX1NDC(0.75);
        st->SetY1NDC(0.2);
        c1->Update();

        if(i<25)
        {
            if(f->GetParameter(0)>0)
            {
                yield0[i]=(f->GetParameter(0))*(f->GetParameter(5))/0.005;
                error0[i]=(f->GetParameter(5))*(f->GetParError(0))/0.005;
                plot0[i]=yield0[i]/error0[i];
            }
            else
            {
                yield0[i]=0;
                error0[i]=0;
                plot0[i]=0;
            }
            cout << "i=" << i << " yield[i]=" << yield0[i] << " error[i]=" << error0[i] << " significance[i]=" << plot0[i] << endl;
        }
        double ymax=hlist[i]->GetMaximum();
        char* str1=Form("Yield=%.0f",yield0[i]);
        char* str2=Form("+/-%.1f",error0[i]);
        TLatex *t = new TLatex(1.74,0.9*ymax, strcat(str1,str2));
        t->Draw("same");
        //TLatex *t1 = new TLatex(1.8,-2, Form("+/-%.2f",error0[i]));
        //t1->Draw("same");
        TLatex *t2 = new TLatex(1.9,0.9*ymax, Form("Significance=%.2f",plot0[i]));
        t2->Draw("same");
        if(i==0) c1->SaveAs("/home/awesole/plots/pt12/histo0.pdf");
        if(i==1) c1->SaveAs("/home/awesole/plots/pt12/histo1.pdf");
        if(i==2) c1->SaveAs("/home/awesole/plots/pt12/histo2.pdf");
        if(i==3) c1->SaveAs("/home/awesole/plots/pt12/histo3.pdf");
        if(i==4) c1->SaveAs("/home/awesole/plots/pt12/histo4.pdf");
        if(i==5) c1->SaveAs("/home/awesole/plots/pt12/histo5.pdf");
        if(i==6) c1->SaveAs("/home/awesole/plots/pt12/histo6.pdf");
        if(i==7) c1->SaveAs("/home/awesole/plots/pt12/histo7.pdf");
        if(i==8) c1->SaveAs("/home/awesole/plots/pt12/histo8.pdf");
        if(i==9) c1->SaveAs("/home/awesole/plots/pt12/histo9.pdf");
        if(i==10) c1->SaveAs("/home/awesole/plots/pt12/histo10.pdf");
        if(i==11) c1->SaveAs("/home/awesole/plots/pt12/histo11.pdf");
        if(i==12) c1->SaveAs("/home/awesole/plots/pt12/histo12.pdf");
        if(i==13) c1->SaveAs("/home/awesole/plots/pt12/histo13.pdf");
        if(i==14) c1->SaveAs("/home/awesole/plots/pt12/histo14.pdf");
        if(i==15) c1->SaveAs("/home/awesole/plots/pt12/histo15.pdf");
        if(i==16) c1->SaveAs("/home/awesole/plots/pt12/histo16.pdf");
        if(i==17) c1->SaveAs("/home/awesole/plots/pt12/histo17.pdf");
        if(i==18) c1->SaveAs("/home/awesole/plots/pt12/histo18.pdf");
        if(i==19) c1->SaveAs("/home/awesole/plots/pt12/histo19.pdf");
        if(i==20) c1->SaveAs("/home/awesole/plots/pt12/histo20.pdf");
        if(i==21) c1->SaveAs("/home/awesole/plots/pt12/histo21.pdf");
        if(i==22) c1->SaveAs("/home/awesole/plots/pt12/histo22.pdf");
        if(i==23) c1->SaveAs("/home/awesole/plots/pt12/histo23.pdf");
        if(i==24) c1->SaveAs("/home/awesole/plots/pt12/histo24.pdf");
  
      //swap->SetLineColor(3);
        //swap->Draw();
        //bin1
        //bin2
        /*
           if(i>=14 && i<29)
           {
           yield1[i-14]=(f->GetParameter("p0"))*(f->GetParameter(5));
           error1[i-14]=yield1[i-14]*sqrt(pow((ze/pz),2)+pow((fe/pf),2));
           plot1[i-14]=yield1[i-14]/error1[i-14];
           yield1[15]=0;
           yield1[16]=0;
           error1[15]=0;
           error1[16]=0;
           }
        //bin 3
        if(i>=29 && i<46)
        {
        yield2[i-29]=(f->GetParameter("p0"))*(f->GetParameter(5));
        error2[i-29]=yield2[i-29]*sqrt(pow((ze/pz),2)+pow((fe/pf),2));
        plot2[i-29]=yield2[i-29]/error2[i-29];
        }
        //bin 4
        if(i>=46 && i<63)
        {
        yield3[i-46]=(f->GetParameter("p0"))*(f->GetParameter(5));
        error3[i-46]=yield3[i-46]*sqrt(pow((ze/pz),2)+pow((fe/pf),2));
        plot3[i-46]=yield3[i-46]/error3[i-46];
        }
        //bin 5
        if(i>=63 && i<80)
        {
        yield4[i-63]=(f->GetParameter("p0"))*(f->GetParameter(5));
        error4[i-63]=yield4[i-63]*sqrt(pow((ze/pz),2)+pow((fe/pf),2));
        plot4[i-63]=yield4[i-63]/error4[i-63];
        }
        //bin 6
        if(i>=80 && i<97)
        {
        yield5[i-80]=(f->GetParameter("p0"))*(f->GetParameter(5));
        error5[i-80]=yield5[i-80]*sqrt(pow((ze/pz),2)+pow((fe/pf),2));
        plot5[i-80]=yield5[i-80]/error5[i-80];
        cout << "i=" << i-80 << " yield[i]=" << yield5[i-80] << " error[i]=" << error5[i-80] << endl;
        }
        //bin 7
        if(i>=97 && i<114)
        {
        yield6[i-97]=(f->GetParameter("p0"))*(f->GetParameter(5));
        error6[i-97]=yield6[i-97]*sqrt(pow((ze/pz),2)+pow((fe/pf),2));
        plot6[i-97]=yield6[i-97]/error6[i-97];
        }
        //bin 8
        if(i>=114 && i<131)
        {
        yield7[i-114]=(f->GetParameter("p0"))*(f->GetParameter(5));
        error7[i-114]=yield7[i-114]*sqrt(pow((ze/pz),2)+pow((fe/pf),2));
        plot7[i-114]=yield7[i-114]/error7[i-114];
        }
        //bin 9
        if(i>=131 && i<148)
        {
        yield8[i-131]=(f->GetParameter("p0"))*(f->GetParameter(5));
        error8[i-131]=yield8[i-131]*sqrt(pow((ze/pz),2)+pow((fe/pf),2));
        plot8[i-131]=yield8[i-131]/error8[i-131];
        }
        //bin 10
        if(i>=148)
        {
        yield9[i-148]=(f->GetParameter("p0"))*(f->GetParameter(5));
        error9[i-148]=yield9[i-148]*sqrt(pow((ze/pz),2)+pow((fe/pf),2));
        plot9[i-148]=yield9[i-148]/error9[i-148];
        }
        */
    }//for all histograms in vecotor


    int n=25;


    TCanvas *c2 = new TCanvas("c2", "c2",800,600 );
    auto *gr0 = new TGraph(n,ilist,plot0);
    gr0->GetYaxis()->SetTitle("Significance");
    gr0->GetXaxis()->SetTitle("BDT value");
    gr0->SetTitle("Centrality 0-10% 1<pT<2");
    //gr0->SetTitle("Centrality 10-30% 5<pT<6");
    gr0->SetMarkerColor(1);
    gr0->SetMarkerStyle(8);
    gr0->SetLineColor(2);
    gr0->SetLineWidth(4);
    gr0->SetMarkerSize(2);
    gr0->Draw("AP");
    c2->Update();
    c2->SaveAs("/home/awesole/plots/pt12/bdtscan.pdf");

    /*

       TCanvas *c3 = new TCanvas("c3", "c3");
       auto *gr1 = new TGraph(n,ilist,plot1);
       gr1->GetYaxis()->SetTitle("Significance");
       gr1->GetXaxis()->SetTitle("BDT value");
       gr1->SetTitle("Bin 2 : 2<pT<3");
       gr1->SetMarkerColor(1);
       gr1->SetMarkerStyle(8);
       gr1->SetLineColor(2);
       gr1->SetLineWidth(4);
       gr1->SetMarkerSize(2);
       gr1->Draw("AP");
       c3->Update();


       TCanvas *c4 = new TCanvas("c4", "c4");
       auto *gr2 = new TGraph(n,ilist,plot2);
       gr2->GetYaxis()->SetTitle("Significance");
       gr2->GetXaxis()->SetTitle("BDT value");
       gr2->SetTitle("Bin 3 : 3<pT<4");
       gr2->SetMarkerColor(1);
       gr2->SetMarkerStyle(8);
       gr2->SetLineColor(2);
       gr2->SetLineWidth(4);
       gr2->SetMarkerSize(2);
       gr2->Draw("AP");
       c4->Update();


       TCanvas *c5 = new TCanvas("c5", "c5");
       auto *gr3 = new TGraph(n,ilist,plot3);
       gr3->GetYaxis()->SetTitle("Significance");
       gr3->GetXaxis()->SetTitle("BDT value");
       gr3->SetTitle("Bin 4 : 4<pT<5");
       gr3->SetMarkerColor(1);
       gr3->SetMarkerStyle(8);
       gr3->SetLineColor(2);
       gr3->SetLineWidth(4);
       gr3->SetMarkerSize(2);
       gr3->Draw("AP");
       c5->Update();


       TCanvas *c6 = new TCanvas("c6", "c6");
       auto *gr4 = new TGraph(n,ilist,plot4);
       gr4->GetYaxis()->SetTitle("Significance");
       gr4->GetXaxis()->SetTitle("BDT value");
       gr4->SetTitle("Bin 5 : 5<pT<6");
       gr4->SetMarkerColor(1);
       gr4->SetMarkerStyle(8);
       gr4->SetLineColor(2);
       gr4->SetLineWidth(4);
       gr4->SetMarkerSize(2);
       gr4->Draw("AP");
       c6->Update();


       TCanvas *c7 = new TCanvas("c7", "c7");
       auto *gr5 = new TGraph(n,ilist,plot5);
       gr5->GetYaxis()->SetTitle("Significance");
       gr5->GetXaxis()->SetTitle("BDT value");
       gr5->SetTitle("Bin 6 : 6<pT<8");
       gr5->SetMarkerColor(1);
       gr5->SetMarkerStyle(8);
       gr5->SetLineColor(2);
       gr5->SetLineWidth(4);
       gr5->SetMarkerSize(2);
       gr5->Draw("AP");
       c7->Update();


    TCanvas *c8 = new TCanvas("c8", "c8");
    auto *gr6 = new TGraph(n,ilist,plot6);
    gr6->GetYaxis()->SetTitle("Significance");
    gr6->GetXaxis()->SetTitle("BDT value");
    gr6->SetTitle("Bin 7 : 8<pT<10");
    gr6->SetMarkerColor(1);
    gr6->SetMarkerStyle(8);
    gr6->SetLineColor(2);
    gr6->SetLineWidth(4);
    gr6->SetMarkerSize(2);
    gr6->Draw("AP");
    c8->Update();


    TCanvas *c9 = new TCanvas("c9", "c9");
    auto *gr7 = new TGraph(n,ilist,plot7);
    gr7->GetYaxis()->SetTitle("Significance");
    gr7->GetXaxis()->SetTitle("BDT value");
    gr7->SetTitle("Bin 8 : 10<pT<15");
    gr7->SetMarkerColor(1);
    gr7->SetMarkerStyle(8);
    gr7->SetLineColor(2);
    gr7->SetLineWidth(4);
    gr7->SetMarkerSize(2);
    gr7->Draw("AP");
    c9->Update();


    TCanvas *c10 = new TCanvas("c10", "c10");
    auto *gr8 = new TGraph(n,ilist,plot8);
    gr8->GetYaxis()->SetTitle("Significance");
    gr8->GetXaxis()->SetTitle("BDT value");
    gr8->SetTitle("Bin 9 : 15<pT<20");
    gr8->SetMarkerColor(1);
    gr8->SetMarkerStyle(8);
    gr8->SetLineColor(2);
    gr8->SetLineWidth(4);
    gr8->SetMarkerSize(2);
    gr8->Draw("AP");
    c10->Update();


    TCanvas *c11 = new TCanvas("c11", "c11");
    auto *gr9 = new TGraph(n,ilist,plot9);
    gr9->GetYaxis()->SetTitle("Significance");
    gr9->GetXaxis()->SetTitle("BDT value");
    gr9->SetTitle("Bin 10 : 20<pT<30");
    gr9->SetMarkerColor(1);
    gr9->SetMarkerStyle(8);
    gr9->SetLineColor(2);
    gr9->SetLineWidth(4);
    gr9->SetMarkerSize(2);
    gr9->Draw("AP");
    c11->Update();
    */

        return 0;
}//function

