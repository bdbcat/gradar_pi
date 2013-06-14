
#include "gradar_pi.h"
#include "gradardialog.h"
#include "GRadarUI.h"



///////////////////////////////ControlDialog/////////////////////////


ControlDialog::ControlDialog( gradar_pi * ppi, wxWindow* parent)
    : ControlDialogBase( parent )
{
    pPlugIn = ppi;
    pParent = parent;
    this->Connect( wxEVT_MOVE, wxMoveEventHandler( ControlDialog::OnMove ) );

    Init();
}

ControlDialog::~ControlDialog( )
{
    this->Disconnect( wxEVT_MOVE, wxMoveEventHandler( ControlDialog::OnMove ) );
}

extern bool g_bmaster;
extern int g_updatemode;
extern double g_overlay_transparency;
extern bool b_enable_log;

void ControlDialog::Init( )
{
    if(g_bmaster)
        pOperatingMode->SetSelection(0);
    else
        pOperatingMode->SetSelection(1);

    if(g_updatemode)
        pUpdateMode->SetSelection(1);
    else
        pUpdateMode->SetSelection(0);

    pTranSlider->SetValue(g_overlay_transparency * 100);
    pCB_Log->SetValue(b_enable_log);
}

void ControlDialog::OnClose ( wxCloseEvent& event )
{
    pPlugIn->OnControlDialogClose();
    event.Skip();
}

void ControlDialog::OnSize ( wxSizeEvent& event )
{
    wxSize p = GetSize();
    pPlugIn->SetControlDialogSizeX(p.x);
    pPlugIn->SetControlDialogSizeY(p.y);
    event.Skip();
}
void ControlDialog::OnMove ( wxMoveEvent& event )
{
    wxPoint p =  GetPosition();
    pPlugIn->SetControlDialogX(p.x);
    pPlugIn->SetControlDialogY(p.y);
    event.Skip();
}

void ControlDialog::OnOperatingModeClick(wxCommandEvent &event)
{
    pPlugIn->SetOperatingMode(pOperatingMode->GetSelection());
}

void ControlDialog::OnUpdateModeClick(wxCommandEvent &event)
{
    pPlugIn->SetUpdateMode(pUpdateMode->GetSelection());
}

void ControlDialog::OnUpdateTranSlider(wxScrollEvent &event)
{
    g_overlay_transparency = ((double)pTranSlider->GetValue()) / 100.;
    pPlugIn->UpdateDisplayParameters();
}

void ControlDialog::OnLogModeClicked(wxCommandEvent &event)
{
    b_enable_log = pCB_Log->GetValue();
}

void ControlDialog::OnRangeDialogClick(wxCommandEvent& event)
{
    pPlugIn->OnRangeDialogClicked();
}

void ControlDialog::OnNoiseDialogClick(wxCommandEvent& event)
{
    pPlugIn->OnNoiseDialogClicked();
}

void ControlDialog::OnDomeDialogClick(wxCommandEvent& event)
{
    pPlugIn->OnDomeDialogClicked();
}

void ControlDialog::OnIdOKClick ( wxCommandEvent& event )
{
    pPlugIn->OnControlDialogClose();
    printf("IDOK\n");
}




//////////////////////////RangeDialog////////////////////////


RangeDialog::RangeDialog( gradar_pi * ppi, wxWindow* parent)
    : RangeDialogBase( parent )
{
    pPlugIn = ppi;
    pParent = parent;

    this->Connect( wxEVT_MOVE, wxMoveEventHandler( RangeDialog::OnMove ) );

    Init();
}

RangeDialog::~RangeDialog( )
{
    this->Disconnect( wxEVT_MOVE, wxMoveEventHandler( RangeDialog::OnMove ) );
}

extern int g_manual_range;
extern int g_range_control_mode;

void RangeDialog::Init()
{
    pRangeSelect->SetSelection(g_manual_range);
}

void RangeDialog::OnClose ( wxCloseEvent& event )
{
    pPlugIn->OnRangeDialogClose();
    pRangeSelect->SetSelection(g_manual_range);
    event.Skip();
}

void RangeDialog::OnSize ( wxSizeEvent& event )
{
    wxSize p = GetSize();
    pPlugIn->SetRangeDialogSizeX(p.x);
    pPlugIn->SetRangeDialogSizeY(p.y);
    event.Skip();
}

void RangeDialog::OnMove ( wxMoveEvent& event )
{
    wxPoint p = GetPosition();
    pPlugIn->SetRangeDialogX(p.x);
    pPlugIn->SetRangeDialogY(p.y);
    event.Skip();
}

void RangeDialog::OnRangeControlClick(wxCommandEvent &event)
{
    pPlugIn->SetRangeControlMode(pRangeControl->GetSelection());
}

void RangeDialog::OnRangeSelectClick( wxCommandEvent& event )
{
    pPlugIn->SetManualRange( pRangeSelect->GetSelection());
}

extern int g_gain_level;
extern int g_gain_control_mode;
extern int g_scan_gain_level;
extern int g_scan_gain_mode;

void RangeDialog::OnGainModeClick( wxCommandEvent& event )
{
    pPlugIn->SetGainControlMode(GainControlSelect->GetSelection());
    if(GainControlSelect->GetSelection() == 0)
        GainLevel->SetValue(g_gain_level);
}

void RangeDialog::OnUpdateGainSlider( wxScrollEvent& event )
{
    if(GainControlSelect->GetSelection() != 0)
        pPlugIn->SetGainLevel(GainLevel->GetValue());
    else
        GainLevel->SetValue(g_gain_level);
}

void RangeDialog::OnRangeCloseClick ( wxCommandEvent& event )
{
    pRangeSelect->SetSelection(g_manual_range);
    pPlugIn->OnRangeDialogClose();
}

void RangeDialog::RangeDialogShow()
{
    pRangeControl->SetSelection(g_range_control_mode);
    pRangeSelect->SetSelection(g_manual_range);
    g_gain_level = g_scan_gain_level;

    if (g_scan_gain_mode == 1) g_gain_control_mode = 0;
    else g_gain_control_mode = 1;

    GainLevel->SetValue(g_gain_level);
    GainControlSelect->SetSelection(g_gain_control_mode);
    Show();
}




//////////////////////////NoiseDialog////////////////////////////////


NoiseDialog::NoiseDialog( gradar_pi * ppi, wxWindow* parent)
    : NoiseDialogBase( parent )
{
    pPlugIn = ppi;
    pParent = parent;

    this->Connect( wxEVT_MOVE, wxMoveEventHandler( NoiseDialog::OnMove ) );

    Init();
}

NoiseDialog::~NoiseDialog( )
{
    this->Disconnect( wxEVT_MOVE, wxMoveEventHandler( NoiseDialog::OnMove ) );
}

void NoiseDialog::Init()
{
}

void NoiseDialog::OnClose( wxCloseEvent& event )
{
    pPlugIn->OnNoiseDialogClose();
    event.Skip();
}

void NoiseDialog::OnSize( wxSizeEvent& event )
{
    wxSize p = GetSize();
    pPlugIn->SetNoiseDialogSizeX(p.x);
    pPlugIn->SetNoiseDialogSizeY(p.y);
    event.Skip();
}

void NoiseDialog::OnMove ( wxMoveEvent& event )
{
    wxPoint p = GetPosition();
    pPlugIn->SetNoiseDialogX(p.x);
    pPlugIn->SetNoiseDialogY(p.y);
    event.Skip();
}

void NoiseDialog::OnSeaClutterModeClick( wxCommandEvent& event )
{
    pPlugIn->SetSeaClutterMode(SeaClutterModeSelect->GetSelection());
}

void NoiseDialog::OnUpdateSeaClutterSlider( wxScrollEvent& event )
{
    pPlugIn->SetSeaClutterLevel(SeaClutterLevel->GetValue());
}

void NoiseDialog::OnFTCModeclick( wxCommandEvent& event )
{
    pPlugIn->SetFTCMode(FTCModeSelect->GetSelection());
}

void NoiseDialog::OnUpdateRainClutterSlider( wxScrollEvent& event )
{
    pPlugIn->SetRainClutterLevel(RainClutterLevel->GetValue());
}

void NoiseDialog::OnCrosstalkModeClick( wxCommandEvent& event )
{
    pPlugIn->SetCrosstalkMode(CrosstalkOnOff->GetSelection());
}

void NoiseDialog::OnNoiseCloseClick( wxCommandEvent& event )
{
    pPlugIn->OnNoiseDialogClose();
}

extern int g_sea_clutter_mode;
extern int g_sea_clutter_level;
extern int g_rain_clutter_level;
extern int g_FTC_mode;
extern int g_crosstalk_mode;
extern int g_scan_sea_clutter_mode;
extern int g_scan_sea_clutter_level;
extern int g_scan_rain_clutter_level;
extern int g_scan_FTC_mode;
extern int g_scan_crosstalk_mode;

void NoiseDialog::NoiseDialogShow()
{
    g_sea_clutter_mode = g_scan_sea_clutter_mode;
    SeaClutterModeSelect->SetSelection(g_sea_clutter_mode);
    g_sea_clutter_level = g_scan_sea_clutter_level;
    SeaClutterLevel->SetValue(g_sea_clutter_level);
    g_FTC_mode = g_scan_FTC_mode;
    FTCModeSelect->SetSelection(g_FTC_mode);
    g_rain_clutter_level = g_scan_rain_clutter_level;
    RainClutterLevel->SetValue(g_rain_clutter_level);
    g_crosstalk_mode = g_scan_crosstalk_mode;
    CrosstalkOnOff->SetSelection(g_crosstalk_mode);

    Show();
}




//////////////////////////DomeDialog////////////////////////////////


DomeDialog::DomeDialog( gradar_pi * ppi, wxWindow* parent)
    : DomeDialogBase( parent )
{
    pPlugIn = ppi;
    pParent = parent;

    this->Connect( wxEVT_MOVE, wxMoveEventHandler( DomeDialog::OnMove ) );

    Init();
}

DomeDialog::~DomeDialog( )
{
    this->Disconnect( wxEVT_MOVE, wxMoveEventHandler( DomeDialog::OnMove ) );
}

void DomeDialog::Init()
{
}

void DomeDialog::OnClose( wxCloseEvent& event )
{
    pPlugIn->OnDomeDialogClose();
    event.Skip();
}

void DomeDialog::OnSize( wxSizeEvent& event )
{
    wxSize p = GetSize();
    pPlugIn->SetDomeDialogSizeX(p.x);
    pPlugIn->SetDomeDialogSizeY(p.y);
    event.Skip();
}

void DomeDialog::OnMove ( wxMoveEvent& event )
{
    wxPoint p = GetPosition();
    pPlugIn->SetDomeDialogX(p.x);
    pPlugIn->SetDomeDialogY(p.y);
    event.Skip();
}

void DomeDialog::OnUpdateOffset( wxSpinEvent& event )
{
    pPlugIn->SetDomeOffset(DomeOffsetSelect->GetValue());
}

void DomeDialog::OnDomeSpeedClick( wxCommandEvent& event )
{
    pPlugIn->SetDomeSpeed(DomeSpeedSelect->GetSelection());
}

void DomeDialog::OnDomeCloseClick( wxCommandEvent& event )
{
    pPlugIn->OnDomeDialogClose();
}

extern int g_dome_offset;
extern int g_scan_dome_offset;
extern int g_dome_speed;
extern int g_scan_dome_speed;

void DomeDialog::DomeDialogShow()
{
    g_dome_offset = g_scan_dome_offset;
    DomeOffsetSelect->SetValue(g_dome_offset);

    if (g_scan_dome_speed == 0) g_dome_speed = 0;
    else g_dome_speed = 1;
    DomeSpeedSelect->SetSelection(g_dome_speed);

    Show();
}













