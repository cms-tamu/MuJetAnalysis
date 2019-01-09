def getPt(Rinv):
    print "Rinv", Rinv
    if Rinv < 1:
        hwRinv = Rinv + 16384
    else:
        hwRinv = Rinv

    hwRinv = hwRinv * 1289e-11
    print "hwRinv", hwRinv
    
    


    fphi_t invPt_f1(0.719297);
    fphi_t inhwInvPt(inhwRinv*invPt_f1);
    inhwInvPt += inhwRinv*87;  // PT_CONVERSION                                                                                                                                    
    if (in.hwQ==1) inhwInvPt*=-1;



Rinv * 
