///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GRADARUI_H__
#define __GRADARUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/radiobox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/spinctrl.h>

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
		wxSlider* pTranSlider;
		wxCheckBox* pCB_Log;
		wxButton* RangeButton;
		wxButton* NoiseButton;
		wxButton* DomeButton;
		wxButton* closebutton;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnOperatingModeClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateModeClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnUpdateTranSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnLogModeClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRangeDialogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNoiseDialogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDomeDialogClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIdOKClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		ControlDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Radar Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 152,428 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
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

		RangeDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Range"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 146,449 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
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

		NoiseDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Noise Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 216,400 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
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

		DomeDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Dome Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 158,218 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~DomeDialogBase();

};

#endif //__GRADARUI_H__
