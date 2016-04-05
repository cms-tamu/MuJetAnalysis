if(MatchRECOtoGENdimuons(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_phi, diMuonF_FittedVtx_eta, diMuonF_FittedVtx_phi, genA0_eta, genA0_phi, genA1_eta, genA0_phi) == 0){ //diMuonC -> A0, diMuonF -> A1
	if(fabs(genA0_Lxy)>=5.0 || fabs(genA0_Lz)>=34.5){ //A0 is the fake and has match diMuonC
		if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
	}
	if(fabs(genA1_Lxy)>=5.0 || fabs(genA1_Lz)>=34.5){ //A1 is the fake and has match diMuonF
		if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);

	}
}else{ //diMuonC -> A1, diMuonF -> A0
	if(fabs(genA0_Lxy)>=5.0 || fabs(genA0_Lz)>=34.5){ //A0 is the fake and has match diMuonF
		if(diMuonF_FittedVtx_eta > -800 && diMuonF_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonF_FittedVtx_eta, diMuonF_FittedVtx_Lxy);
	}
	if(fabs(genA1_Lxy)>=5.0 || fabs(genA1_Lz)>=34.5){ //A1 is the fake and has match diMuonC
		if(diMuonC_FittedVtx_eta > -800 && diMuonC_FittedVtx_Lxy > -800) Fake_Reco_Eta_vs_Lxy->Fill(diMuonC_FittedVtx_eta, diMuonC_FittedVtx_Lxy);
	}
}
