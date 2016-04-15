#ifndef ConsistentVertexesCalculator_H
#define ConsistentVertexesCalculator_H
// -*- C++ -*-
//
// Package:    AnalysisTools
// Class:      ConsistentVertexesCalculator
// 
//
// Original Author:  Anthony Rose and Yuriy Pakhotin
//         Created:  Tue May 20 16:32:35 CDT 2014
//
//

// user include files
#include "TTree.h"
#include "TRandom3.h"
#include "TMath.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"

#include "MuJetAnalysis/DataFormats/interface/MultiMuon.h"
#include "MuJetAnalysis/AnalysisTools/interface/eig3.h"

//******************************************************************************
// Struct to hold relevant details from iterative vertex technique
// (should all be moved out of this file with things are stable)
//******************************************************************************
struct EventContainer
{

  double vtx_dzmj1;
  double vtx_dzmj2;
  double vtx_dxymj1;
  double vtx_dxymj2;
  double vtx_massmj1;
  double vtx_massmj2;
  math::XYZTLorentzVector vtx_mj1;
  math::XYZTLorentzVector vtx_mj2;
  Global3DPoint vtx_1;
  Global3DPoint vtx_2;
  
  GlobalPoint vtx3D_0;
  GlobalPoint vtx3D_1;
  
  math::XYZTLorentzVector vtxP4_0;
  math::XYZTLorentzVector vtxP4_1;
    
  std::vector<math::XYZTLorentzVector> vVtxP4_0;
  std::vector<math::XYZTLorentzVector> vVtxP4_1;

  EventContainer(){
    vtx_dzmj1 = 0.;
    vtx_dzmj2 = 0.;
    vtx_dxymj1 = 0.;
    vtx_dxymj2 = 0.;
    vtx_massmj1 = 0.;
    vtx_massmj2 = 0.;
    vtx_mj1 = math::XYZTLorentzVector(0.,0.,0.,0.);
    vtx_mj2 = math::XYZTLorentzVector(0.,0.,0.,0.);
    vtx_1 = Global3DPoint(0., 0., 0.);
    vtx_2 = Global3DPoint(0., 0., 0.);
  }

  void setVtx3D_0(const GlobalPoint x){
    vtx3D_0 = x;
  }
  
  GlobalPoint getVtx3D_0() {
    return vtx3D_0;
  }
  
  void setVtx3D_1(const GlobalPoint x){
    vtx3D_1 = x;
  }
  
  GlobalPoint getVtx3D_1() {
    return vtx3D_1;
  }
  
  void setVtxP4_0(const math::XYZTLorentzVector x){
    vtxP4_0 = x;
  }
  
  math::XYZTLorentzVector getVtxP4_0() {
    return vtxP4_0;
  }
  
  void setVtxP4_1(const math::XYZTLorentzVector x){
    vtxP4_1 = x;
  }
  
  math::XYZTLorentzVector getVtxP4_1() {
    return vtxP4_1;
  }
  
  void setVVtxP4_0(const std::vector<math::XYZTLorentzVector> x){
    vVtxP4_0 = x;
  }
  
  std::vector<math::XYZTLorentzVector> getVVtxP4_0 () {
    return vVtxP4_0;
  }
  
  void setVVtxP4_1(const std::vector<math::XYZTLorentzVector> x){
    vVtxP4_1 = x;
  }
  
  std::vector<math::XYZTLorentzVector> getVVtxP4_1 () {
    return vVtxP4_1;
  }
  
  
  void set_vtx_1(const Global3DPoint x){
    vtx_1 = x;
  }
  Global3DPoint get_vtx_1(){
    return vtx_1;
  }
  void set_vtx_2(const Global3DPoint x){
    vtx_2 = x;
  }
  Global3DPoint get_vtx_2(){
    return vtx_2;
  }
  void set_vtx_dzmj1(const double x){
    vtx_dzmj1 = x;
  }
  double get_vtx_dzmj1(){
    return vtx_dzmj1;
  }
  void set_vtx_dzmj2(const double x){
    vtx_dzmj2 = x;
  }
  double get_vtx_dzmj2(){
    return vtx_dzmj2;
  }
  void set_vtx_dxymj1(const double x){
    vtx_dxymj1 = x;
  }
  double get_vtx_dxymj1(){
    return vtx_dxymj1;
  }
  void set_vtx_dxymj2(const double x){
    vtx_dxymj2 = x;
  }
  double get_vtx_dxymj2(){
    return vtx_dxymj2;
  }
  void set_vtx_massmj1(const double x){
    vtx_massmj1 = x;
  }
  double get_vtx_massmj1(){
    return vtx_massmj1;
  }
  void set_vtx_massmj2(const double x){
    vtx_massmj2 = x;
  }
  double get_vtx_massmj2(){
    return vtx_massmj2;
  }
  void set_vtx_mj1(math::XYZTLorentzVector x){
    vtx_mj1 = x;
  }
  math::XYZTLorentzVector get_vtx_mj1(){
    return vtx_mj1;
  }
  void set_vtx_mj2(math::XYZTLorentzVector x){
    vtx_mj2 = x;
  }
  math::XYZTLorentzVector get_vtx_mj2(){
    return vtx_mj2;
  }
};

//******************************************************************************
//                Class to perform iterative vertex calculation                 
//******************************************************************************

class ConsistentVertexesCalculator {
  public:
    ConsistentVertexesCalculator(const TransientTrackBuilder *transientTrackBuilder, const GlobalPoint beamSpotPosition );
    ~ConsistentVertexesCalculator();
    
    void SetDebug(int debug = 0) { _debug = debug; }
    bool isValid() {return _resultIsValid; }
    
    void SetRandomSeed( unsigned int randomSeed = 0 ) { _randomSeed = randomSeed; }
    void SetNThrows( int nThrows = 0 ) { _nThrows = nThrows; }
        
    GlobalPoint             vertexPoint(int i)     { if (i == 0) return _vtx3D_0; else return _vtx3D_1; }
    math::XYZTLorentzVector vertexP4(int i)        { if (i == 0) return _vtxP4_0; else return _vtxP4_1; }
    GlobalVector            vertexMomentum(int i)  { math::XYZTLorentzVector v = vertexP4(i);  return GlobalVector(v.x(), v.y(), v.z()); }
    double                 vertexMass(int i)      { return vertexP4(i).mass(); }
    double                 dm()                   { return vertexMass(0) - vertexMass(1); }
    double                 dz(int i)              { if (i == 0) return _dz_0; else return _dz_1; }
    double                 dz()                   { return _dz; }
    double                 dxy(int i)             { if (i == 0) return _dxy_0; else return _dxy_1; }
    double                 chi2_sum()             { return _chi2_sum; }
    double                 chi2_dz()              { return _chi2_dz; }
    double                 chi2_dxy(int i)        { if (i == 0) return _chi2_dxy_0; else return _chi2_dxy_1; }
    
    std::vector< std::vector<double> > cholesky(std::vector<std::vector<double> > A);
    
    bool Calculate(const pat::MultiMuon *&mm_0, const pat::MultiMuon *&mm_1);

    void setBarrelPixelLayer(int barrelPixelLayer = 1) {_barrelPixelLayer = barrelPixelLayer;}
    void setEndcapPixelLayer(int endcapPixelLayer = 1) {_endcapPixelLayer = endcapPixelLayer;}
  
  private:
    
    int  _debug;
    bool _resultIsValid;
    
    unsigned int _randomSeed;
    int _nThrows;
    
    const TransientTrackBuilder *_transientTrackBuilder;
    GlobalPoint _beamSpotPosition;
    
    double _chi2_threshold;
    
    double _chi2_sum;
    double _chi2_dz;
    double _chi2_dxy_0;
    double _chi2_dxy_1;
    
    double _dz_0;
    double _dz_1;
    double _dz;
    
    double _dxy_0;
    double _dxy_1;
    
    GlobalPoint _vtx3D_0;
    GlobalPoint _vtx3D_1;
    
    math::XYZTLorentzVector _vtxP4_0;
    math::XYZTLorentzVector _vtxP4_1;
    
    std::vector<math::XYZTLorentzVector> _vVtxP4_0;
    std::vector<math::XYZTLorentzVector> _vVtxP4_1;

    int    _barrelPixelLayer;
    int    _endcapPixelLayer;
};

#endif // ConsistentVertexesCalculator_H
