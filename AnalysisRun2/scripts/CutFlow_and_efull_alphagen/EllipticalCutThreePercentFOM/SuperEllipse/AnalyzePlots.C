TH1F* getHist(TFile* file, TString hname){
	TIter next(file->GetListOfKeys());
	TKey *key;
	while((key = (TKey*)next())){
		TDirectory* dir = file->GetDirectory(key->GetName());
		if(dir->FindKey(hname) != 0){
			TH1F *h = (TH1F*)dir->Get(hname);
			return h;
		}
	}
	cout << "hname: " << hname << endl;
	return NULL;
}


float eta_min           = 2.2;
float eta_max           = 3;
float eta_stepsize      = 0.1;

float lxy_min           = 5;
float lxy_max           = 15;
float lxy_stepsize      = 1;

float exp_min           = 1;
float exp_max           = 2;
float exp_stepsize      = 0.1;

void AnalyzePlots(TString filename){
	cout << "Running Analysis" << endl;
	//Load File
	TFile *tfile = TFile::Open(filename);

	for(double eta_cut = eta_min; eta_cut <= eta_max; eta_cut += eta_stepsize){
		for(double lxy_cut = lxy_min; lxy_cut <= lxy_max; lxy_cut += lxy_stepsize){
		for(double exp_cut = exp_min; exp_cut <= exp_max; exp_cut += exp_stepsize){

			TString histoname_num_eta = TString::Format("eta_num_lxy_%d_eta_%d_exp_%d", (int)lxy_cut, (int)(eta_cut*10), (int)(exp_cut*10));
			TString histoname_den_eta = TString::Format("eta_den_lxy_%d_eta_%d_exp_%d", (int)lxy_cut, (int)(eta_cut*10), (int)(exp_cut*10));
			TString histoname_num_lxy = TString::Format("lxy_num_lxy_%d_eta_%d_exp_%d", (int)lxy_cut, (int)(eta_cut*10), (int)(exp_cut*10));
			TString histoname_den_lxy = TString::Format("lxy_den_lxy_%d_eta_%d_exp_%d", (int)lxy_cut, (int)(eta_cut*10), (int)(exp_cut*10));

			TH1F *num_test = (TH1F*)tfile->Get(histoname_num_eta);


			TGraphAsymmErrors* eta_graph = new TGraphAsymmErrors((TH1F*)tfile->Get(histoname_num_eta), (TH1F*)tfile->Get(histoname_den_eta));
			TGraphAsymmErrors* lxy_graph = new TGraphAsymmErrors((TH1F*)tfile->Get(histoname_num_lxy), (TH1F*)tfile->Get(histoname_den_lxy));


			bool isEtaFlat = false;
			bool isLxyFlat = false;
			//Check if eta_graph is flat
			if(eta_graph->GetMean(2) > 0.50){ //2 will retrieve mean from y-axis
				Double_t ax[eta_graph->GetN()],ay[eta_graph->GetN()];
				double min = 999;
				double max = -999;
				for(int x = 0; x < eta_graph->GetN(); x++){
					eta_graph->GetPoint(x,ax[x],ay[x]);
					//cout << x << "th element of X array: " << ax[x] << endl;
					//cout << x << "th element of Y array: " << ay[x] << endl;
					if(ay[x] > max) max = ay[x];
					if(ay[x] < min) min = ay[x];
				}
				//cout << "Max and Min: " << max << ", " << min << endl;
				if(max-min <= 0.06) isEtaFlat = true;
				if(isEtaFlat){
					cout << "(Eta, Lxy) " << eta_cut << ", " << lxy_cut << " produce a flat eta efficiency plot!" << endl;
				}
			}
			//Check if lxy_graph is flat
			if(lxy_graph->GetMean(2) > 0.50){ //2 will retrieve mean from y-axis
				Double_t ax[lxy_graph->GetN()],ay[lxy_graph->GetN()];
				double min = 999;
				double max = -999;
				for(int x = 0; x < lxy_graph->GetN(); x++){
					lxy_graph->GetPoint(x,ax[x],ay[x]);
					if(ay[x] > max) max = ay[x];
					if(ay[x] < min) min = ay[x];
				}
				//cout << "Max and Min: " << max << ", " << min << endl;
				if(max-min <= 0.06) isLxyFlat = true;
				if(isLxyFlat){
					cout << "(Eta, Lxy) " << eta_cut << ", " << lxy_cut << " produce a flat Lxy efficiency plot!" << endl;
				}
			}
			if(isEtaFlat && isLxyFlat){
				cout << "Both efficiency plots are flat and have a mean > 50% for (Eta, Lxy, exp) " << eta_cut << ", " << lxy_cut << ", " << exp_cut << endl;
			}
		}
	}
	}
}
