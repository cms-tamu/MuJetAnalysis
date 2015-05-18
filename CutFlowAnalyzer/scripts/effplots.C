#include <iostream>
using namespace std;
#include <algorithm>    // std::max
#include <iomanip>
#include <cmath>
#include <limits>


void effplots(){
  

  TFile *f[50];
  
  TFile *f[0] = new TFile("~/Dropbox/darksusy_plots/Anal2015data/MCsamples/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_000_RAW2DIGI_L1Reco_RECO_v1.root");
  TFile *f[1] = new TFile("~/Dropbox/darksusy_plots/Anal2015data/MCsamples/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_020_RAW2DIGI_L1Reco_RECO_v1.root");
  TFile *f[2] = new TFile("~/Dropbox/darksusy_plots/Anal2015data/MCsamples/DarkSUSY_mH_125_mGammaD_0250_13TeV_cT_200_RAW2DIGI_L1Reco_RECO_v1.root");

 
  Float_t ev_all[40]={0.0};

  Float_t eps_gen[40]={0.0};
  Float_t eps_rec[40]={0.0};

  Float_t erreps_gen[40]={0.0};
  Float_t erreps_rec[40]={0.0};

  Float_t ratio[40]={0.0};
  Float_t errratio[40]={0.0};
  
  
  Bool_t is1GenMu17;
  Bool_t is2GenMu8;
  Bool_t is3GenMu8;
  Bool_t is4GenMu8;

  Bool_t is1SelMu17;
  Bool_t is2SelMu8;
  Bool_t is3SelMu8;
  Bool_t is4SelMu8;

  Bool_t is2DiMuon;
  Bool_t is2MuJets;

  Int_t diMuonC_m1_FittedVtx_hitpix;
  Int_t diMuonC_m2_FittedVtx_hitpix;
  Int_t diMuonF_m1_FittedVtx_hitpix;
  Int_t diMuonF_m2_FittedVtx_hitpix;


  Float_t ev_4gm[40]={0.0};
  Float_t ev_4gmlxylzcut[40]={0.0};

  Float_t ev_4rm[40]={0.0};

  Float_t ev_2dim[40]={0.0};
  Float_t ev_2dimvtxok[40]={0.0};
  Float_t ev_2mj[40]={0.0};
  Float_t ev_isVtxOK[40]={0.0};
  Float_t ev_is2DimDzOK[40]={0.0};
  Float_t ev_is2DimVtxOK[40]={0.0};
  Float_t ev_is2DimHLTFired[40]={0.0};
  Float_t ev_is2DimIsoTkOK[40]={0.0};
  Float_t ev_is2DimMassOK[40]={0.0};
  Float_t ev_is2DimMassOK2[40]={0.0};


  Int_t ev_is2DimHitPix[40]={0};

  Float_t ev_2dimhit[40]={0.0};
  Float_t ev_2dimhit_allcut[40]={0.0};
  Float_t ev_2dimhit_allcutrecov[40]={0.0};
  Float_t ev_2dimhit_allcutrecov2[40]={0.0};

  Float_t ev_2dim_recov[40]={0.0};
  Float_t ev_2dim_recov2[40]={0.0};

  Float_t ev_2dimhit_recov2dim[40]={0.0};
  Float_t ev_2dimhit_recovmuJetC[40]={0.0};
  Float_t ev_2dimhit_recovmuJetF[40]={0.0};

  Float_t ev_2dimhit_recov2dim2[40]={0.0};
  Float_t ev_2dimhit_recovmuJetC2[40]={0.0};
  Float_t ev_2dimhit_recovmuJetF2[40]={0.0};

  Float_t ev_2dimhitgt[40]={0.0};
  Float_t ev_2dimhitfvtx[40]={0.0};
  Float_t ev_2dimhit_fail2mujets[40]={0.0};
  Float_t ev_2dimhit_fail2mujets_recover[40]={0.0};
  Float_t ev_2dimhit_failmuJetC[40]={0.0};
  Float_t ev_2dimhit_failmuJetC_recover[40]={0.0};
  Float_t ev_2dimhit_failmuJetF[40]={0.0};
  Float_t ev_2dimhit_failmuJetF_recover[40]={0.0};


  Float_t ev_2dimhit2[40]={0.0};
  Float_t ev_2dimhit_fail2mujets2[40]={0.0};
  Float_t ev_2dimhit_fail2mujets_recover2[40]={0.0};
  Float_t ev_2dimhit_failmuJetC2[40]={0.0};
  Float_t ev_2dimhit_failmuJetC_recover2[40]={0.0};
  Float_t ev_2dimhit_failmuJetF2[40]={0.0};
  Float_t ev_2dimhit_failmuJetF_recover2[40]={0.0};


  Float_t muJetC_muon1_track_minchi2;
  Float_t muJetC_muon2_track_minchi2;
  Float_t muJetF_muon1_track_minchi2;
  Float_t muJetF_muon2_track_minchi2;

  Int_t event;
  Bool_t ev2dim;
  Bool_t ev2mj;

  Bool_t isVtxOK;
  Bool_t is2DimDzOK;
  Bool_t is2DimVtxOK;
  Bool_t is2DimHLTFired;
  Bool_t is2DimIsoTkOK;
  Bool_t is2DimMassOK;

  Int_t muJetChit[2];
  Int_t muJetFhit[2];

  Int_t muJetChitgt[2];
  Int_t muJetFhitgt[2];

  Float_t muJetC_vtx_x;
  Float_t muJetC_vtx_y;
  Float_t muJetC_vtx_z;

  Float_t muJetF_vtx_x;
  Float_t muJetF_vtx_y;
  Float_t muJetF_vtx_z;

  Float_t muJetC_mindisttrk;
  Float_t muJetF_mindisttrk;

  Bool_t muJetC_validVtx;
  Bool_t muJetC_validVtx_fitted;
  Bool_t muJetC_validVtx_mindist;

  Bool_t muJetF_validVtx;
  Bool_t muJetF_validVtx_fitted;
  Bool_t muJetF_validVtx_mindist;

  Int_t comphitmu1JetC;
  Int_t comphitmu2JetC;
  Int_t comphitmu1JetF;
  Int_t comphitmu2JetF;

  Int_t Detmu1jetC;
  Int_t Detmu2jetC;
  Int_t Detmu1jetF;
  Int_t Detmu2jetF;


  Float_t  muJetC_trackdist_1stpixel;
  Float_t  muJetF_trackdist_1stpixel;


  Float_t genA0_Lxy;
  Float_t genA1_Lxy;
  Float_t genA0_Lz;
  Float_t genA1_Lz;

  //============= Counters ===========================//
  Int_t c1genm[40]={0};
  Int_t c2genm[40]={0};
  Int_t c3genm[40]={0};
  Int_t c4genm[40]={0};

  Int_t c1recm[40]={0};
  Int_t c2recm[40]={0};
  Int_t c3recm[40]={0};
  Int_t c4recm[40]={0};

  //  for(int p=0;p<31;p++){
  for(int p=0;p<3;p++){
    
    f[p]->cd("cutFlowAnalyzer");
    
    TTree *t = (TTree*)f[p]->Get("cutFlowAnalyzer/Events");
  
    cout<<"  Events  "<<t->GetEntries()<<endl;
    
    t->SetBranchAddress("event",&event);
    t->SetBranchAddress("is2DiMuons",&ev2dim);
    t->SetBranchAddress("is2MuJets",&ev2mj);

    t->SetBranchAddress("is1GenMu17",&is1GenMu17);
    t->SetBranchAddress("is2GenMu8" ,&is2GenMu8);
    t->SetBranchAddress("is3GenMu8" ,&is3GenMu8);
    t->SetBranchAddress("is4GenMu8" ,&is4GenMu8);

    t->SetBranchAddress("is1SelMu17",&is1SelMu17);
    t->SetBranchAddress("is2SelMu8",&is2SelMu8);
    t->SetBranchAddress("is3SelMu8",&is3SelMu8);
    t->SetBranchAddress("is4SelMu8",&is4SelMu8);
    
    t->SetBranchAddress("isVertexOK",&isVtxOK);
    t->SetBranchAddress("is2DiMuonsDzOK_FittedVtx",&is2DimDzOK);
    t->SetBranchAddress("is2DiMuonsFittedVtxOK",&is2DimVtxOK);
    t->SetBranchAddress("is2DiMuonsMassOK_FittedVtx",&is2DimMassOK);
    t->SetBranchAddress("is2DiMuonsIsoTkOK_FittedVtx",&is2DimIsoTkOK);
    t->SetBranchAddress("isDiMuonHLTFired",&is2DimHLTFired);

    t->SetBranchAddress("diMuonC_m1_FittedVtx_hitpix",&diMuonC_m1_FittedVtx_hitpix);
    t->SetBranchAddress("diMuonC_m2_FittedVtx_hitpix",&diMuonC_m2_FittedVtx_hitpix);
    t->SetBranchAddress("diMuonF_m1_FittedVtx_hitpix",&diMuonF_m1_FittedVtx_hitpix);
    t->SetBranchAddress("diMuonF_m2_FittedVtx_hitpix",&diMuonF_m2_FittedVtx_hitpix);

    t->SetBranchAddress("genA0_Lxy",&genA0_Lxy);
    t->SetBranchAddress("genA1_Lxy",&genA1_Lxy);
    t->SetBranchAddress("genA0_Lz",&genA0_Lz);
    t->SetBranchAddress("genA1_Lz",&genA1_Lz);

 
    Int_t nentries = t->GetEntries();


    for(int k=0;k<nentries;k++){
      t->GetEntry(k);
      
      ev_all[p]++;

      if(is1GenMu17) c1genm[p]++;
      if(is2GenMu8)  c2genm[p]++;
      if(is3GenMu8)  c3genm[p]++;
      if(is4GenMu8)  c4genm[p]++;

      if(is1SelMu17) c1recm[p]++;
      if(is2SelMu8)  c2recm[p]++;
      if(is3SelMu8)  c3recm[p]++;
      if(is4SelMu8)  c4recm[p]++;
      
      //  ===========   GEN LEVEL FIDUCIAL CUT  ==============//

      if(is4GenMu8){
      	if(fabs(genA0_Lxy)<4.4 && fabs(genA1_Lxy)<4.4 && fabs(genA0_Lz)<34.5 && fabs(genA1_Lz)<34.5){
      	  ev_4gmlxylzcut[p]++;
      	}
      }
      
      //  =============  RECO information ====================//

      if(is4SelMu8){
    	ev_4rm[p]++;
	if(isVtxOK){
	  ev_isVtxOK[p]++;
	  //	  if(ev2mj && muJetC_validVtx_fitted && muJetF_validVtx_fitted){
	  if(ev2mj){
	    ev_2mj[p]++;
	    if(ev2dim){
	      ev_2dim[p]++;
	      if(is2DimVtxOK){
		ev_2dimvtxok[p]++;
		
		if( (diMuonC_m1_FittedVtx_hitpix==1||diMuonC_m2_FittedVtx_hitpix==1)&&(diMuonF_m1_FittedVtx_hitpix==1||diMuonF_m2_FittedVtx_hitpix==1) ){  ev_2dimhitgt[p]++;  

		  if(is2DimDzOK){
		    ev_is2DimDzOK[p]++;
		    if(is2DimMassOK){
		      ev_is2DimMassOK[p]++;
		      if(is2DimIsoTkOK){
			ev_is2DimIsoTkOK[p]++;
			ev_2dimhit_allcut[p]++;
			if(is2DimHLTFired){ 
			  ev_is2DimHLTFired[p]++;

			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }

    std::cout<<" sample          "<<p<<std::endl;
    std::cout<<" Events          "<<t->GetEntries()<<std::endl; 
    std::cout.precision(3);
    std::cout<<"  ================= GEN MUONS ========================================= "<<std::endl;
    std::cout<<" 1GenMu17        "<<c1genm[p]<<"   reff "<<c1genm[p]/(t->GetEntries()*1.0)<<" +/-  "<< sqrt(  (  (c1genm[p]/(t->GetEntries()*1.0))*(1-(c1genm[p]/(t->GetEntries()*1.0))))/(t->GetEntries()*1.0)  )<<std::endl;
    std::cout<<" 2GenMu8         "<<c2genm[p]<<"   reff  "<<c2genm[p]/(c1genm[p]*1.0)<<" +/-  "<<sqrt( ((c2genm[p]/(c1genm[p]*1.0))*(1-(c2genm[p]/(c1genm[p]*1.0))))/(c1genm[p]*1.0))  <<std::endl;
    std::cout<<" 3GenMu8         "<<c3genm[p]<<"   reff  "<<c3genm[p]/(c2genm[p]*1.0)<<" +/-  "<<sqrt( ((c3genm[p]/(c2genm[p]*1.0))*(1-(c3genm[p]/(c2genm[p]*1.0))))/(c2genm[p]*1.0))  <<std::endl;
    std::cout<<" 4GenMu8         "<<c4genm[p]<<"   reff  "<<c4genm[p]/(c3genm[p]*1.0)<<" +/-  "<<sqrt( ((c4genm[p]/(c3genm[p]*1.0))*(1-(c4genm[p]/(c3genm[p]*1.0))))/(c3genm[p]*1.0))  <<std::endl;
    std::cout<<" 4GenMu8 Lxy/Lz  "<<ev_4gmlxylzcut[p]<<"   reff   "<<ev_4gmlxylzcut[p]/(c4genm[p]*1.0)<<"  +/-  "<<sqrt( ((ev_4gmlxylzcut[p]/(c4genm[p]*1.0))*(1-(ev_4gmlxylzcut[p]/(c4genm[p]*1.0))))/(c4genm[p]*1.0))<<std::endl;
    std::cout<<"  ================= RECO MUONS ========================================= "<<std::endl;
    std::cout<<" 1RecMu17            "<<c1recm[p]<<"  reff  "<<c1recm[p]/(t->GetEntries()*1.0)<<" +/-  "<<sqrt( ((c1recm[p]/(t->GetEntries()*1.0))*(1-(c1recm[p]/(t->GetEntries()*1.0))))/(t->GetEntries()*1.0))  <<std::endl;
    std::cout<<" 2RecMu8             "<<c2recm[p]<<"  reff  "<<c2recm[p]/(c1recm[p]*1.0)<<" +/-  "<<sqrt( ((c2recm[p]/(c1recm[p]*1.0))*(1-(c2recm[p]/(c1recm[p]*1.0))))/(c1recm[p]*1.0))  <<std::endl;
    std::cout<<" 3RecMu8             "<<c3recm[p]<<"  reff  "<<c3recm[p]/(c2recm[p]*1.0)<<" +/-  "<<sqrt( ((c3recm[p]/(c2recm[p]*1.0))*(1-(c3recm[p]/(c2recm[p]*1.0))))/(c2recm[p]*1.0))  <<std::endl;
    std::cout<<" 4RecMu8             "<<c4recm[p]<<"  reff  "<<c4recm[p]/(c3recm[p]*1.0)<<" +/-  "<<sqrt( ((c4recm[p]/(c3recm[p]*1.0))*(1-(c4recm[p]/(c3recm[p]*1.0))))/(c3recm[p]*1.0))  <<std::endl;
    //    std::cout<<"  ================== EVENT variables (before HitRecovery) ================= "<<std::endl;
    std::cout<<"   VtxOK            "<<ev_isVtxOK[p]<<"    reff  "<<ev_isVtxOK[p]/ev_4rm[p]<<" +/- "<<sqrt( ( (ev_isVtxOK[p]/ev_4rm[p])*(1-(ev_isVtxOK[p]/ev_4rm[p])))/(ev_4rm[p]))<<std::endl;
    std::cout<<"   2MuJets          "<<ev_2mj[p]<<"        reff  "<<ev_2mj[p]/ev_isVtxOK[p]<<" +/- "<<sqrt( ( (ev_2mj[p]/ev_isVtxOK[p])*(1-(ev_2mj[p]/ev_isVtxOK[p])))/(ev_isVtxOK[p]))<<std::endl;
    std::cout<<"   2Dim             "<<ev_2dim[p]<<"       reff  "<<ev_2dim[p]/ev_2mj[p]<<" +/- "<<sqrt( ( (ev_2dim[p]/ev_2mj[p])*(1-(ev_2dim[p]/ev_2mj[p])))/(ev_2mj[p]))<<std::endl;
    std::cout<<"   2DimVtxOK        "<<ev_2dimvtxok[p]<<"  reff  "<<ev_2dimvtxok[p]/ev_2dim[p]<<" +/- "<<sqrt( ( (ev_2dimvtxok[p]/ev_2dim[p])*(1-(ev_2dimvtxok[p]/ev_2dim[p])))/(ev_2dim[p]))<<std::endl;
    // std::cout<<"   2DimHitPi     "<<ev_2dimhit[p]<<"    reff  "<<ev_2dimhit[p]/ev_2dimvtxok[p]<<std::endl;
    // std::cout<<"  ========================================================== "<<std::endl;
    std::cout<<"   2DimHitPix       "<<ev_2dimhitgt[p]<<"  reff  "<<ev_2dimhitgt[p]/ev_2dimvtxok[p]<<" +/- "<<sqrt( ( (ev_2dimhitgt[p]/ev_2dimvtxok[p])*(1-(ev_2dimhitgt[p]/ev_2dimvtxok[p])))/(ev_2dimvtxok[p]))<<std::endl;
    // std::cout<<"   2DimHitPix gt fitted vtx                  "<<ev_2dimhitfvtx[p]<<"  reff  "<<ev_2dimhitfvtx[p]/ev_2dimvtxok[p]<<std::endl;
    // std::cout<<"  ========================================================== "<<std::endl;
    std::cout<<"   2DimDzOK         "<<ev_is2DimDzOK[p]<<"   reff   "<<ev_is2DimDzOK[p]/ev_2dimvtxok[p]<<" +/-  "<<sqrt( ( (ev_is2DimDzOK[p]/ev_2dimvtxok[p])*(1-(ev_is2DimDzOK[p]/ev_2dimvtxok[p])) )/(ev_2dimvtxok[p]))<<endl;
    std::cout<<"   2DimMassOK       "<<ev_is2DimMassOK[p]<<"  reff   "<<ev_is2DimMassOK[p]/ev_is2DimDzOK[p]<<" +/-  "<<sqrt( ( (ev_is2DimMassOK[p]/ev_is2DimDzOK[p])*(1-(ev_is2DimMassOK[p]/ev_is2DimDzOK[p])) )/(ev_is2DimDzOK[p]))<<endl;
    std::cout<<"   2DimIsoOK        "<<ev_is2DimIsoTkOK[p]<<"   reff   "<<ev_is2DimIsoTkOK[p]/ev_is2DimMassOK[p]<<" +/-  "<<sqrt( ( (ev_is2DimIsoTkOK[p]/ev_is2DimMassOK[p])*(1-(ev_is2DimIsoTkOK[p]/ev_is2DimMassOK[p])) )/(ev_is2DimMassOK[p]))<<endl;
    std::cout<<"   2DimHLT          "<<ev_is2DimHLTFired[p]<<"   reff   "<<ev_is2DimHLTFired[p]/ev_is2DimIsoTkOK[p]<<" +/-  "<<sqrt( ( (ev_is2DimHLTFired[p]/ev_is2DimIsoTkOK[p])*(1-(ev_is2DimHLTFired[p]/ev_is2DimIsoTkOK[p])) )/(ev_is2DimIsoTkOK[p]))<<endl;

    eps_gen[p] = ev_4gmlxylzcut[p]/(1.0*t->GetEntries());
    eps_rec[p] = ev_is2DimHLTFired[p]/(1.0*t->GetEntries());
    erreps_gen[p] = sqrt( ( (ev_4gmlxylzcut[p]/(1.0*t->GetEntries()))*(1-(ev_4gmlxylzcut[p]/(1.0*t->GetEntries()))))/(1.0*t->GetEntries()));
    erreps_rec[p] = sqrt( ( ( ev_is2DimHLTFired[p]/(1.0*t->GetEntries()))*(1-( ev_is2DimHLTFired[p]/(1.0*t->GetEntries()))))/(1.0*t->GetEntries()));

    ratio[p] = eps_rec[p]/eps_gen[p];
    errratio[p] = ratio[p]*sqrt( pow(erreps_gen[p]/eps_gen[p],2)+pow(erreps_rec[p]/eps_rec[p],2));


    std::cout<<"  eps_reco                     "<<eps_rec[p]<<" +/-  "<<erreps_rec[p]<<std::endl;
    std::cout<<"  eps_gen                     "<<eps_gen[p]<<" +/-  "<<erreps_gen[p]<<std::endl;
    std::cout<<"  ratio reco/gen               "<<ratio[p]<<" +/-  "<<errratio[p]<<std::endl;
    std::cout<<"  ========================================================== "<<std::endl;

  }


  Float_t ctau[3] = {0.0,0.2,2.0};

  TGraphErrors *gr_eps_recogen = new TGraphErrors(3,ctau,ratio,0,errratio);

  TH2F *dummy = new TH2F("dummy","",100,-0.2,2.2,100,0.0,1.1);

  TLegend *leg= new TLegend(0.5,0.8,0.8,0.9);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetTextSize(0.042);
  leg->AddEntry(gr_eps_recogen,"m_{#gamma D}=0.25 GeV ","PL");

  
  TCanvas *c = new TCanvas("c","c",700,500);
  dummy->Draw();
  dummy->GetXaxis()->SetTitle("c#tau [mm]");
  dummy->GetYaxis()->SetTitle("#epsilon_{rec}/#alpha_{gen}");
  gr_eps_recogen->Draw("PLsame");
  leg->Draw("same");
  c->SaveAs("eff_epsilonvsgen.pdf","recreate");

 


}
     
