#ifndef _GRADARDLG_H_
#define _GRADARDLG_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers



#include "GRadarUI.h"

class ControlDialog: public ControlDialogBase
{
public:
    ControlDialog(gradar_pi *ppi, wxWindow* parent);
    ~ControlDialog( );
    void Init();

private:
    void OnClose(wxCloseEvent& event);
    void OnSize( wxSizeEvent& event );
    void OnMove(wxMoveEvent& event);
    void OnOperatingModeClick(wxCommandEvent &event);
    void OnUpdateModeClick(wxCommandEvent &event);
    void OnUpdateTranSlider(wxScrollEvent &event);
    void OnLogModeClicked(wxCommandEvent &event);
    void OnRangeDialogClick(wxCommandEvent &event);
    void OnNoiseDialogClick(wxCommandEvent &event);
    void OnDomeDialogClick(wxCommandEvent &event);
    void OnIdOKClick( wxCommandEvent& event );

    wxWindow          *pParent;
    gradar_pi         *pPlugIn;
};

class RangeDialog : public RangeDialogBase
{
public:
    RangeDialog(gradar_pi *ppi, wxWindow* parent);
    ~RangeDialog();
    void Init();
    void RangeDialogShow();

private:
    void OnClose( wxCloseEvent& event );
    void OnSize( wxSizeEvent& event );
    void OnMove(wxMoveEvent& event );
    void OnRangeControlClick( wxCommandEvent& event );
    void OnRangeSelectClick( wxCommandEvent& event );
    void OnGainModeClick( wxCommandEvent& event );
    void OnUpdateGainSlider( wxScrollEvent& event );
    void OnRangeCloseClick( wxCommandEvent& event );

    wxWindow        *pParent;
    gradar_pi      *pPlugIn;
};

class NoiseDialog : public NoiseDialogBase
{
public:
    NoiseDialog(gradar_pi *ppi, wxWindow* parent);
    ~NoiseDialog();
    void Init();
    void NoiseDialogShow();

private:
    void OnClose( wxCloseEvent& event );
    void OnSize( wxSizeEvent& event );
    void OnMove( wxMoveEvent& event );
    void OnSeaClutterModeClick( wxCommandEvent& event );
    void OnUpdateSeaClutterSlider( wxScrollEvent& event );
    void OnFTCModeclick( wxCommandEvent& event );
    void OnRainClutterModeClick( wxCommandEvent& event );
    void OnUpdateRainClutterSlider( wxScrollEvent& event );
    void OnCrosstalkModeClick( wxCommandEvent& event );
    void OnNoiseCloseClick( wxCommandEvent& event );

    wxWindow        *pParent;
    gradar_pi      *pPlugIn;
};

class DomeDialog : public DomeDialogBase
{
public:
    DomeDialog(gradar_pi *ppi, wxWindow* parent);
    ~DomeDialog();
    void Init();
    void DomeDialogShow();

private:
    void OnClose( wxCloseEvent& event );
    void OnSize( wxSizeEvent& event );
    void OnMove( wxMoveEvent& event );
    void OnUpdateOffset( wxSpinEvent& event );
	void OnDomeSpeedClick( wxCommandEvent& event );
	void OnDomeCloseClick( wxCommandEvent& event );


    wxWindow        *pParent;
    gradar_pi      *pPlugIn;
};



#endif  //  _GRADARDLG_H_
