///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GRADARUI_H__
#define __GRADARUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/radiobox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/clrpicker.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ControlDialogBase
///////////////////////////////////////////////////////////////////////////////
class ControlDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxRadioBox* pOperatingMode;
		wxRadioBox* pUpdateMode;
		wxColourPickerCtrl* scancolorpicker;
		wxSlider* pTranSlider;
		wxCheckBox* pCB_Log;
		wxButton* RangeButton;
		wxButton* NoiseButton;
		wxButton* DomeButton;
		wxButton* SentryButton;
		wxButton* closebutton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnOperatingModeClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateModeClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnColorChanged( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnUpdateTranSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnLogModeClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRangeDialogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNoiseDialogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDomeDialogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSentryDialogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIdOKClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		ControlDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Radar Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 163,535 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~ControlDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class RangeDialogBase
///////////////////////////////////////////////////////////////////////////////
class RangeDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxRadioBox* pRangeControl;
		wxRadioBox* pRangeSelect;
		wxRadioBox* GainControlSelect;
		wxSlider* GainLevel;
		wxButton* closebutton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnRangeControlClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRangeSelectClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGainModeClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateGainSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnRangeCloseClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		RangeDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Range"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 146,449 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~RangeDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class NoiseDialogBase
///////////////////////////////////////////////////////////////////////////////
class NoiseDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxRadioBox* SeaClutterModeSelect;
		wxSlider* SeaClutterLevel;
		wxRadioBox* FTCModeSelect;
		wxSlider* RainClutterLevel;
		wxRadioBox* CrosstalkOnOff;
		wxButton* closebutton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnSeaClutterModeClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateSeaClutterSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnFTCModeclick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateRainClutterSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnCrosstalkModeClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNoiseCloseClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		NoiseDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Noise Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 216,395 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~NoiseDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DomeDialogBase
///////////////////////////////////////////////////////////////////////////////
class DomeDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxSpinCtrl* DomeOffsetSelect;
		wxRadioBox* DomeSpeedSelect;
		wxButton* closebutton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnUpdateOffset( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnDomeSpeedClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDomeCloseClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DomeDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Dome Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 158,218 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~DomeDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SentryDialogBase
///////////////////////////////////////////////////////////////////////////////
class SentryDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxRadioBox* TimedTransmit;
		wxSpinCtrl* StandbyMinutes;
		wxSpinCtrl* TransmitMinutes;
		wxRadioBox* GuardZoneOnOff;
		wxSpinCtrl* OuterRange;
		wxSpinCtrl* InnerRange;
		wxRadioBox* PartialArcNoYes;
		wxSpinCtrl* StartAngle;
		wxSpinCtrl* EndAngle;
		wxColourPickerCtrl* m_colorpicker;
		wxSlider* pGZTranSlider;
		wxSlider* AlarmSensitivitySlider;
		wxButton* AlarmSelectButton;
		wxButton* AlarmTestButton;
		wxButton* closebutton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnTimedTransmitClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateStandbyMinutes( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnUpdateTransmitMinutes( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnGuardZoneClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateOuterRange( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnUpdateInnerRange( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnPartialArcClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateStartAngle( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnUpdateEndAngle( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnColorChanged( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnUpdateTranSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnUpdateSensitivitySlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnAlarmSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAlarmTest( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSentryCloseClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SentryDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Sentry Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 241,754 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~SentryDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SentryAlarmDialogBase
///////////////////////////////////////////////////////////////////////////////
class SentryAlarmDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxButton* SilenceButton;
		wxButton* closebutton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnAlarmSilenceClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAlarmCloseClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SentryAlarmDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("RadarSentryAlarm"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 281,166 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~SentryAlarmDialogBase();
	
};

#endif //__GRADARUI_H__
