
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




extern bool b_enable_log;
extern int g_updatemode;

void ControlDialog::Init( )
{
    if(pPlugIn->m_bmaster)
        pOperatingMode->SetSelection(0);
    else
        pOperatingMode->SetSelection(1);

    if(g_updatemode)
        pUpdateMode->SetSelection(1);
    else
        pUpdateMode->SetSelection(0);

    pTranSlider->SetValue(pPlugIn->m_overlay_transparency * 100);
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

    //  The PlugIn may override the selection and prevent Master Mode
    if(pPlugIn->m_bmaster)
        pOperatingMode->SetSelection(0);
    else
        pOperatingMode->SetSelection(1);

}

void ControlDialog::OnUpdateModeClick(wxCommandEvent &event)
{
    pPlugIn->SetUpdateMode(pUpdateMode->GetSelection());
}

void ControlDialog::OnUpdateTranSlider(wxScrollEvent &event)
{
    pPlugIn->m_overlay_transparency = ((double)pTranSlider->GetValue()) / 100.;
    pPlugIn->UpdateDisplayParameters();
}

void ControlDialog::OnColorChanged( wxColourPickerEvent& event )
{
    pPlugIn->SetScanColor( scancolorpicker->GetColour());
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

void ControlDialog::OnSentryDialogClick(wxCommandEvent& event)
{
    pPlugIn->OnSentryDialogClicked();
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

void RangeDialog::Init()
{
    pRangeSelect->SetSelection(pPlugIn->m_manual_range);
}

void RangeDialog::OnClose ( wxCloseEvent& event )
{
    pPlugIn->OnRangeDialogClose();
    pRangeSelect->SetSelection(pPlugIn->m_manual_range);
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



extern int g_scan_gain_level;
extern int g_scan_gain_mode;

void RangeDialog::OnGainModeClick( wxCommandEvent& event )
{
    pPlugIn->SetGainControlMode(GainControlSelect->GetSelection());
    if(GainControlSelect->GetSelection() == 0)
        GainLevel->SetValue(pPlugIn->m_gain_level);
}

void RangeDialog::OnUpdateGainSlider( wxScrollEvent& event )
{
    if(GainControlSelect->GetSelection() != 0)
        pPlugIn->SetGainLevel(GainLevel->GetValue());
    else
        GainLevel->SetValue(pPlugIn->m_gain_level);
}

void RangeDialog::OnRangeCloseClick ( wxCommandEvent& event )
{
    pRangeSelect->SetSelection(pPlugIn->m_manual_range);
    pPlugIn->OnRangeDialogClose();
}

void RangeDialog::RangeDialogShow()
{
    pRangeControl->SetSelection(pPlugIn->m_range_control_mode);
    pRangeSelect->SetSelection(pPlugIn->m_manual_range);
    pPlugIn->m_gain_level = g_scan_gain_level;

    if (g_scan_gain_mode == 1) pPlugIn->m_gain_control_mode = 0;
    else pPlugIn->m_gain_control_mode = 1;

    GainLevel->SetValue(pPlugIn->m_gain_level);
    GainControlSelect->SetSelection(pPlugIn->m_gain_control_mode);
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


extern int g_scan_sea_clutter_mode;
extern int g_scan_sea_clutter_level;
extern int g_scan_rain_clutter_level;
extern int g_scan_FTC_mode;
extern int g_scan_crosstalk_mode;

void NoiseDialog::NoiseDialogShow()
{
    pPlugIn->m_sea_clutter_mode = g_scan_sea_clutter_mode;
    SeaClutterModeSelect->SetSelection(pPlugIn->m_sea_clutter_mode);
    pPlugIn->m_sea_clutter_level = g_scan_sea_clutter_level;
    SeaClutterLevel->SetValue(pPlugIn->m_sea_clutter_level);
    pPlugIn->m_FTC_mode = g_scan_FTC_mode;
    FTCModeSelect->SetSelection(pPlugIn->m_FTC_mode);
    pPlugIn->m_rain_clutter_level = g_scan_rain_clutter_level;
    RainClutterLevel->SetValue(pPlugIn->m_rain_clutter_level);
    pPlugIn->m_crosstalk_mode = g_scan_crosstalk_mode;
    CrosstalkOnOff->SetSelection(pPlugIn->m_crosstalk_mode);

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


extern int g_scan_dome_offset;
extern int g_scan_dome_speed;

void DomeDialog::DomeDialogShow()
{
    pPlugIn->m_dome_offset = g_scan_dome_offset;
    DomeOffsetSelect->SetValue(pPlugIn->m_dome_offset);

    if (g_scan_dome_speed == 0) pPlugIn->m_dome_speed = 0;
    else pPlugIn->m_dome_speed = 1;
    DomeSpeedSelect->SetSelection(pPlugIn->m_dome_speed);

    Show();
}



//////////////////////////SentryDialog////////////////////////////////


SentryDialog::SentryDialog( gradar_pi * ppi, wxWindow* parent)
    : SentryDialogBase( parent )
{
    pPlugIn = ppi;
    pParent = parent;

    this->Connect( wxEVT_MOVE, wxMoveEventHandler( SentryDialog::OnMove ) );

    Init();
}


SentryDialog::~SentryDialog( )
{
    this->Disconnect( wxEVT_MOVE, wxMoveEventHandler( SentryDialog::OnMove ) );
}

void SentryDialog::Init()
{
     pGZTranSlider->SetValue(pPlugIn->m_guardzone_transparency * 100);
     AlarmSensitivitySlider->SetValue(pPlugIn->m_sentry_alarm_sensitivity);
}

void SentryDialog::OnClose( wxCloseEvent& event )
{
    pPlugIn->OnSentryDialogClose();
    event.Skip();
}

void SentryDialog::OnSize( wxSizeEvent& event )
{
    wxSize p = GetSize();
    pPlugIn->SetSentryDialogSizeX(p.x);
    pPlugIn->SetSentryDialogSizeY(p.y);
    event.Skip();
}

void SentryDialog::OnMove ( wxMoveEvent& event )
{
    wxPoint p = GetPosition();
    pPlugIn->SetSentryDialogX(p.x);
    pPlugIn->SetSentryDialogY(p.y);
    event.Skip();
}

void SentryDialog::OnTimedTransmitClick( wxCommandEvent& event )
{
    pPlugIn->SetTimedTransmitMode(TimedTransmit->GetSelection());
}

void SentryDialog::OnUpdateStandbyMinutes( wxSpinEvent& event )
{
    pPlugIn->SetStandbyMinutes(StandbyMinutes->GetValue());
}

void SentryDialog::OnUpdateTransmitMinutes( wxSpinEvent& event )
{
    pPlugIn->SetTransmitMinutes(TransmitMinutes->GetValue());
}

void SentryDialog::OnGuardZoneClick( wxCommandEvent& event )
{
    pPlugIn->SetGuardZoneMode(GuardZoneOnOff->GetSelection());
    pPlugIn->SetGuardZoneColor( m_colorpicker->GetColour());
}

void SentryDialog::OnUpdateOuterRange( wxSpinEvent& event )
{
    int iran = InnerRange->GetValue();
    int oran = OuterRange->GetValue();
    if (oran < iran)
        oran = iran;
    OuterRange->SetValue(oran);
    pPlugIn->SetOuterRange(oran);
}


void SentryDialog::OnUpdateInnerRange( wxSpinEvent& event )
{
    int iran = InnerRange->GetValue();
    int oran = OuterRange->GetValue();
    if (iran > oran)
        iran = oran;
    InnerRange->SetValue(iran);
    pPlugIn->SetInnerRange(iran);
}


void SentryDialog::OnPartialArcClick( wxCommandEvent& event )
{
    pPlugIn->SetPartialArcMode(PartialArcNoYes->GetSelection());
}


void SentryDialog::OnUpdateStartAngle( wxSpinEvent& event )
{
    int vale = EndAngle->GetValue();
    int vals = StartAngle->GetValue();
    if (vale < vals)
        vals = vale;
    if ((vale - vals)>360)
        vals = vale - 360;
    StartAngle->SetValue(vals);

    pPlugIn->SetStartAngle(vals);    
}


void SentryDialog::OnUpdateEndAngle( wxSpinEvent& event )
{
    int vale = EndAngle->GetValue();
    int vals = StartAngle->GetValue();
    if (vale < vals)
        vale = vals;
    if ((vale - vals)>360)
        vale = 360 + vals;
    EndAngle->SetValue(vale);

    pPlugIn->SetEndAngle(vale);
}


void SentryDialog::OnColorChanged( wxColourPickerEvent& event )
{
    pPlugIn->SetGuardZoneColor( m_colorpicker->GetColour());
}

void SentryDialog::OnUpdateTranSlider(wxScrollEvent &event)
{
    pPlugIn->m_guardzone_transparency = ((double)pGZTranSlider->GetValue()) / 100.;
    pPlugIn->UpdateDisplayParameters();
}

void SentryDialog::OnUpdateSensitivitySlider(wxScrollEvent &event)
{
    pPlugIn->m_sentry_alarm_sensitivity = AlarmSensitivitySlider->GetValue();
}


void SentryDialog::OnSentryCloseClick( wxCommandEvent& event )
{
    pPlugIn->OnSentryDialogClose();
}

extern int g_scan_timed_transmit_mode;
extern int g_scan_timed_transmit_standby;
extern int g_scan_timed_transmit_transmit;

void SentryDialog::SentryDialogShow()
{
    pPlugIn->m_timedtransmit_mode = g_scan_timed_transmit_mode;
    TimedTransmit->SetSelection(pPlugIn->m_timedtransmit_mode);
    pPlugIn->m_standby_minutes = g_scan_timed_transmit_standby;
    StandbyMinutes->SetValue(pPlugIn->m_standby_minutes);
    pPlugIn->m_transmit_minutes = g_scan_timed_transmit_transmit;
    TransmitMinutes->SetValue(pPlugIn->m_transmit_minutes);

    Show();
}


//////////////////////////SentryAlarmDialog////////////////////////////////


SentryAlarmDialog::SentryAlarmDialog( gradar_pi * ppi, wxWindow* parent)
    : SentryAlarmDialogBase( parent )
{
    pPlugIn = ppi;
    pParent = parent;

    this->Connect( wxEVT_MOVE, wxMoveEventHandler( SentryAlarmDialog::OnMove ) );

    Init();
}

SentryAlarmDialog::~SentryAlarmDialog( )
{
    this->Disconnect( wxEVT_MOVE, wxMoveEventHandler( SentryAlarmDialog::OnMove ) );
}

void SentryAlarmDialog::Init()
{
}

void SentryAlarmDialog::OnClose( wxCloseEvent& event )
{
    pPlugIn->OnSentryAlarmDialogClose();
    event.Skip();
}

void SentryAlarmDialog::OnSize( wxSizeEvent& event )
{
    wxSize p = GetSize();
    pPlugIn->SetSentryAlarmDialogSizeX(p.x);
    pPlugIn->SetSentryAlarmDialogSizeY(p.y);
    event.Skip();
}

void SentryAlarmDialog::OnMove ( wxMoveEvent& event )
{
    wxPoint p = GetPosition();
    pPlugIn->SetSentryAlarmDialogX(p.x);
    pPlugIn->SetSentryAlarmDialogY(p.y);
    event.Skip();
}

void SentryAlarmDialog::OnAlarmCloseClick( wxCommandEvent& event )
{
    pPlugIn->OnSentryAlarmDialogClose();
}

void SentryAlarmDialog::SentryAlarmDialogShow()
{
    Show();
}













