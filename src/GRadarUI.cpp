///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GRadarUI.h"

///////////////////////////////////////////////////////////////////////////

ControlDialogBase::ControlDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* topsizer;
	topsizer = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* boxsizer;
	boxsizer = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* BoxSizerOpOpt;
	BoxSizerOpOpt = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Operational Control") ), wxVERTICAL );
	
	wxString pOperatingModeChoices[] = { _("Master Mode"), _("Slave Mode") };
	int pOperatingModeNChoices = sizeof( pOperatingModeChoices ) / sizeof( wxString );
	pOperatingMode = new wxRadioBox( BoxSizerOpOpt->GetStaticBox(), wxID_ANY, _("Operating Mode"), wxDefaultPosition, wxDefaultSize, pOperatingModeNChoices, pOperatingModeChoices, 1, wxRA_SPECIFY_COLS );
	pOperatingMode->SetSelection( 0 );
	BoxSizerOpOpt->Add( pOperatingMode, 0, wxALL, 5 );
	
	
	boxsizer->Add( BoxSizerOpOpt, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* StaticBoxSizerDisOpt;
	StaticBoxSizerDisOpt = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Display Options") ), wxVERTICAL );
	
	wxString pUpdateModeChoices[] = { _("Swept Scan Update"), _("Full Scan Update") };
	int pUpdateModeNChoices = sizeof( pUpdateModeChoices ) / sizeof( wxString );
	pUpdateMode = new wxRadioBox( StaticBoxSizerDisOpt->GetStaticBox(), wxID_ANY, _("Scan Update Method"), wxDefaultPosition, wxDefaultSize, pUpdateModeNChoices, pUpdateModeChoices, 1, wxRA_SPECIFY_COLS );
	pUpdateMode->SetSelection( 0 );
	StaticBoxSizerDisOpt->Add( pUpdateMode, 0, wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer26;
	sbSizer26 = new wxStaticBoxSizer( new wxStaticBox( StaticBoxSizerDisOpt->GetStaticBox(), wxID_ANY, _("Scan Color") ), wxVERTICAL );
	
	scancolorpicker = new wxColourPickerCtrl( sbSizer26->GetStaticBox(), wxID_ANY, wxColour( 255, 0, 0 ), wxDefaultPosition, wxSize( -1,-1 ), wxCLRP_DEFAULT_STYLE|wxCLRP_USE_TEXTCTRL );
	sbSizer26->Add( scancolorpicker, 0, wxALL, 5 );
	
	
	StaticBoxSizerDisOpt->Add( sbSizer26, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* transliderboxsizer;
	transliderboxsizer = new wxStaticBoxSizer( new wxStaticBox( StaticBoxSizerDisOpt->GetStaticBox(), wxID_ANY, _("Scan Transparency") ), wxVERTICAL );
	
	pTranSlider = new wxSlider( transliderboxsizer->GetStaticBox(), wxID_ANY, 90, 10, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	transliderboxsizer->Add( pTranSlider, 1, wxEXPAND, 5 );
	
	
	StaticBoxSizerDisOpt->Add( transliderboxsizer, 0, wxEXPAND, 5 );
	
	
	boxsizer->Add( StaticBoxSizerDisOpt, 0, wxEXPAND, 5 );
	
	pCB_Log = new wxCheckBox( this, wxID_ANY, _("Enable gradar Log"), wxDefaultPosition, wxDefaultSize, 0 );
	boxsizer->Add( pCB_Log, 0, wxALL, 5 );
	
	RangeButton = new wxButton( this, wxID_ANY, _("Range Control"), wxDefaultPosition, wxDefaultSize, 0 );
	boxsizer->Add( RangeButton, 0, wxALL, 5 );
	
	NoiseButton = new wxButton( this, wxID_ANY, _("Noise Control"), wxDefaultPosition, wxDefaultSize, 0 );
	boxsizer->Add( NoiseButton, 0, wxALL, 5 );
	
	DomeButton = new wxButton( this, wxID_ANY, _("Dome Control"), wxDefaultPosition, wxDefaultSize, 0 );
	boxsizer->Add( DomeButton, 0, wxALL, 5 );
	
	SentryButton = new wxButton( this, wxID_ANY, _("Sentry Control"), wxDefaultPosition, wxDefaultSize, 0 );
	boxsizer->Add( SentryButton, 0, wxALL, 5 );
	
	closebutton = new wxButton( this, wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	boxsizer->Add( closebutton, 0, wxALL, 5 );
	
	
	topsizer->Add( boxsizer, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( topsizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ControlDialogBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( ControlDialogBase::OnSize ) );
	pOperatingMode->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ControlDialogBase::OnOperatingModeClick ), NULL, this );
	pUpdateMode->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ControlDialogBase::OnUpdateModeClick ), NULL, this );
	scancolorpicker->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( ControlDialogBase::OnColorChanged ), NULL, this );
	pTranSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( ControlDialogBase::OnUpdateTranSlider ), NULL, this );
	pCB_Log->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ControlDialogBase::OnLogModeClicked ), NULL, this );
	RangeButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnRangeDialogClick ), NULL, this );
	NoiseButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnNoiseDialogClick ), NULL, this );
	DomeButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnDomeDialogClick ), NULL, this );
	SentryButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnSentryDialogClick ), NULL, this );
	closebutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnIdOKClick ), NULL, this );
}

ControlDialogBase::~ControlDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( ControlDialogBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( ControlDialogBase::OnSize ) );
	pOperatingMode->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ControlDialogBase::OnOperatingModeClick ), NULL, this );
	pUpdateMode->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( ControlDialogBase::OnUpdateModeClick ), NULL, this );
	scancolorpicker->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( ControlDialogBase::OnColorChanged ), NULL, this );
	pTranSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( ControlDialogBase::OnUpdateTranSlider ), NULL, this );
	pCB_Log->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( ControlDialogBase::OnLogModeClicked ), NULL, this );
	RangeButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnRangeDialogClick ), NULL, this );
	NoiseButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnNoiseDialogClick ), NULL, this );
	DomeButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnDomeDialogClick ), NULL, this );
	SentryButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnSentryDialogClick ), NULL, this );
	closebutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ControlDialogBase::OnIdOKClick ), NULL, this );
	
}

RangeDialogBase::RangeDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Range Setting") ), wxVERTICAL );
	
	wxString pRangeControlChoices[] = { _("Auto"), _("Manual") };
	int pRangeControlNChoices = sizeof( pRangeControlChoices ) / sizeof( wxString );
	pRangeControl = new wxRadioBox( sbSizer6->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, pRangeControlNChoices, pRangeControlChoices, 1, wxRA_SPECIFY_ROWS );
	pRangeControl->SetSelection( 0 );
	sbSizer6->Add( pRangeControl, 0, wxALL, 5 );
	
	wxString pRangeSelectChoices[] = { _(".125"), _(".25"), _(".50"), _(".75"), _("1.0"), _("1.5"), _("2"), _("3"), _("4"), _("6"), _("8"), _("12"), _("16"), _("24"), _("36"), _("48") };
	int pRangeSelectNChoices = sizeof( pRangeSelectChoices ) / sizeof( wxString );
	pRangeSelect = new wxRadioBox( sbSizer6->GetStaticBox(), wxID_ANY, _("Range Miles"), wxDefaultPosition, wxDefaultSize, pRangeSelectNChoices, pRangeSelectChoices, 2, wxRA_SPECIFY_COLS );
	pRangeSelect->SetSelection( 1 );
	sbSizer6->Add( pRangeSelect, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer4->Add( sbSizer6, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer51;
	sbSizer51 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Gain") ), wxVERTICAL );
	
	wxString GainControlSelectChoices[] = { _("Auto"), _("Manual") };
	int GainControlSelectNChoices = sizeof( GainControlSelectChoices ) / sizeof( wxString );
	GainControlSelect = new wxRadioBox( sbSizer51->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, GainControlSelectNChoices, GainControlSelectChoices, 1, wxRA_SPECIFY_ROWS );
	GainControlSelect->SetSelection( 0 );
	sbSizer51->Add( GainControlSelect, 0, wxALL, 5 );
	
	GainLevel = new wxSlider( sbSizer51->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	sbSizer51->Add( GainLevel, 0, wxEXPAND, 5 );
	
	
	bSizer4->Add( sbSizer51, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	closebutton = new wxButton( sbSizer16->GetStaticBox(), wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer16->Add( closebutton, 0, wxALL, 5 );
	
	
	bSizer4->Add( sbSizer16, 0, wxEXPAND, 5 );
	
	
	bSizer3->Add( bSizer4, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( RangeDialogBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( RangeDialogBase::OnSize ) );
	pRangeControl->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( RangeDialogBase::OnRangeControlClick ), NULL, this );
	pRangeSelect->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( RangeDialogBase::OnRangeSelectClick ), NULL, this );
	GainControlSelect->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( RangeDialogBase::OnGainModeClick ), NULL, this );
	GainLevel->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( RangeDialogBase::OnUpdateGainSlider ), NULL, this );
	closebutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( RangeDialogBase::OnRangeCloseClick ), NULL, this );
}

RangeDialogBase::~RangeDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( RangeDialogBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( RangeDialogBase::OnSize ) );
	pRangeControl->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( RangeDialogBase::OnRangeControlClick ), NULL, this );
	pRangeSelect->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( RangeDialogBase::OnRangeSelectClick ), NULL, this );
	GainControlSelect->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( RangeDialogBase::OnGainModeClick ), NULL, this );
	GainLevel->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( RangeDialogBase::OnUpdateGainSlider ), NULL, this );
	closebutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( RangeDialogBase::OnRangeCloseClick ), NULL, this );
	
}

NoiseDialogBase::NoiseDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("SeaClutter Sensitivity Time Control") ), wxVERTICAL );
	
	wxString SeaClutterModeSelectChoices[] = { _("Man"), _("Calm"), _("Med"), _("High") };
	int SeaClutterModeSelectNChoices = sizeof( SeaClutterModeSelectChoices ) / sizeof( wxString );
	SeaClutterModeSelect = new wxRadioBox( sbSizer6->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, SeaClutterModeSelectNChoices, SeaClutterModeSelectChoices, 1, wxRA_SPECIFY_ROWS );
	SeaClutterModeSelect->SetSelection( 0 );
	sbSizer6->Add( SeaClutterModeSelect, 0, 0, 5 );
	
	SeaClutterLevel = new wxSlider( sbSizer6->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	sbSizer6->Add( SeaClutterLevel, 0, wxEXPAND, 5 );
	
	
	bSizer5->Add( sbSizer6, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("FTC Fast Time Constant") ), wxVERTICAL );
	
	wxString FTCModeSelectChoices[] = { _("Off"), _("Low"), _("Med"), _("High") };
	int FTCModeSelectNChoices = sizeof( FTCModeSelectChoices ) / sizeof( wxString );
	FTCModeSelect = new wxRadioBox( sbSizer7->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, FTCModeSelectNChoices, FTCModeSelectChoices, 1, wxRA_SPECIFY_ROWS );
	FTCModeSelect->SetSelection( 0 );
	sbSizer7->Add( FTCModeSelect, 1, wxALL, 5 );
	
	
	bSizer5->Add( sbSizer7, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("RainClutter") ), wxVERTICAL );
	
	RainClutterLevel = new wxSlider( sbSizer8->GetStaticBox(), wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	sbSizer8->Add( RainClutterLevel, 1, wxEXPAND, 5 );
	
	
	bSizer5->Add( sbSizer8, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Crosstalk") ), wxVERTICAL );
	
	wxString CrosstalkOnOffChoices[] = { _("Off"), _("On") };
	int CrosstalkOnOffNChoices = sizeof( CrosstalkOnOffChoices ) / sizeof( wxString );
	CrosstalkOnOff = new wxRadioBox( sbSizer9->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, CrosstalkOnOffNChoices, CrosstalkOnOffChoices, 1, wxRA_SPECIFY_ROWS );
	CrosstalkOnOff->SetSelection( 0 );
	sbSizer9->Add( CrosstalkOnOff, 0, wxALL, 5 );
	
	
	bSizer5->Add( sbSizer9, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer17;
	sbSizer17 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	closebutton = new wxButton( sbSizer17->GetStaticBox(), wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer17->Add( closebutton, 0, wxALL, 5 );
	
	
	bSizer5->Add( sbSizer17, 0, wxEXPAND, 5 );
	
	
	bSizer6->Add( bSizer5, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer6 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( NoiseDialogBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( NoiseDialogBase::OnSize ) );
	SeaClutterModeSelect->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( NoiseDialogBase::OnSeaClutterModeClick ), NULL, this );
	SeaClutterLevel->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( NoiseDialogBase::OnUpdateSeaClutterSlider ), NULL, this );
	FTCModeSelect->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( NoiseDialogBase::OnFTCModeclick ), NULL, this );
	RainClutterLevel->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( NoiseDialogBase::OnUpdateRainClutterSlider ), NULL, this );
	CrosstalkOnOff->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( NoiseDialogBase::OnCrosstalkModeClick ), NULL, this );
	closebutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoiseDialogBase::OnNoiseCloseClick ), NULL, this );
}

NoiseDialogBase::~NoiseDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( NoiseDialogBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( NoiseDialogBase::OnSize ) );
	SeaClutterModeSelect->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( NoiseDialogBase::OnSeaClutterModeClick ), NULL, this );
	SeaClutterLevel->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( NoiseDialogBase::OnUpdateSeaClutterSlider ), NULL, this );
	FTCModeSelect->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( NoiseDialogBase::OnFTCModeclick ), NULL, this );
	RainClutterLevel->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( NoiseDialogBase::OnUpdateRainClutterSlider ), NULL, this );
	CrosstalkOnOff->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( NoiseDialogBase::OnCrosstalkModeClick ), NULL, this );
	closebutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NoiseDialogBase::OnNoiseCloseClick ), NULL, this );
	
}

DomeDialogBase::DomeDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer12;
	sbSizer12 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Dome Offset") ), wxVERTICAL );
	
	DomeOffsetSelect = new wxSpinCtrl( sbSizer12->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, -90, 90, 0 );
	sbSizer12->Add( DomeOffsetSelect, 0, wxALL, 5 );
	
	
	bSizer8->Add( sbSizer12, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer13;
	sbSizer13 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Dome Speed") ), wxVERTICAL );
	
	wxString DomeSpeedSelectChoices[] = { _("24"), _("30") };
	int DomeSpeedSelectNChoices = sizeof( DomeSpeedSelectChoices ) / sizeof( wxString );
	DomeSpeedSelect = new wxRadioBox( sbSizer13->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, DomeSpeedSelectNChoices, DomeSpeedSelectChoices, 1, wxRA_SPECIFY_ROWS );
	DomeSpeedSelect->SetSelection( 0 );
	sbSizer13->Add( DomeSpeedSelect, 0, wxALL, 5 );
	
	
	bSizer8->Add( sbSizer13, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer14;
	sbSizer14 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	closebutton = new wxButton( sbSizer14->GetStaticBox(), wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer14->Add( closebutton, 0, wxALL, 5 );
	
	
	bSizer8->Add( sbSizer14, 0, wxEXPAND, 5 );
	
	
	bSizer7->Add( bSizer8, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer7 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DomeDialogBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( DomeDialogBase::OnSize ) );
	DomeOffsetSelect->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( DomeDialogBase::OnUpdateOffset ), NULL, this );
	DomeSpeedSelect->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( DomeDialogBase::OnDomeSpeedClick ), NULL, this );
	closebutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DomeDialogBase::OnDomeCloseClick ), NULL, this );
}

DomeDialogBase::~DomeDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( DomeDialogBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( DomeDialogBase::OnSize ) );
	DomeOffsetSelect->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( DomeDialogBase::OnUpdateOffset ), NULL, this );
	DomeSpeedSelect->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( DomeDialogBase::OnDomeSpeedClick ), NULL, this );
	closebutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DomeDialogBase::OnDomeCloseClick ), NULL, this );
	
}

SentryDialogBase::SentryDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer15;
	sbSizer15 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Timed Transmit") ), wxVERTICAL );
	
	wxString TimedTransmitChoices[] = { _("Off"), _("On") };
	int TimedTransmitNChoices = sizeof( TimedTransmitChoices ) / sizeof( wxString );
	TimedTransmit = new wxRadioBox( sbSizer15->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, TimedTransmitNChoices, TimedTransmitChoices, 1, wxRA_SPECIFY_ROWS );
	TimedTransmit->SetSelection( 0 );
	sbSizer15->Add( TimedTransmit, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer16;
	sbSizer16 = new wxStaticBoxSizer( new wxStaticBox( sbSizer15->GetStaticBox(), wxID_ANY, _("Standby Minutes") ), wxVERTICAL );
	
	StandbyMinutes = new wxSpinCtrl( sbSizer16->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 1, 250, 20 );
	sbSizer16->Add( StandbyMinutes, 0, wxALL, 5 );
	
	
	bSizer12->Add( sbSizer16, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer17;
	sbSizer17 = new wxStaticBoxSizer( new wxStaticBox( sbSizer15->GetStaticBox(), wxID_ANY, _("Transmit Minutes") ), wxVERTICAL );
	
	TransmitMinutes = new wxSpinCtrl( sbSizer17->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 1, 60, 2 );
	sbSizer17->Add( TransmitMinutes, 0, wxALL, 5 );
	
	
	bSizer12->Add( sbSizer17, 1, wxEXPAND, 5 );
	
	
	sbSizer15->Add( bSizer12, 1, wxEXPAND, 5 );
	
	
	bSizer10->Add( sbSizer15, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer18;
	sbSizer18 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Guard Zone") ), wxVERTICAL );
	
	wxString GuardZoneOnOffChoices[] = { _("Off"), _("On") };
	int GuardZoneOnOffNChoices = sizeof( GuardZoneOnOffChoices ) / sizeof( wxString );
	GuardZoneOnOff = new wxRadioBox( sbSizer18->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, GuardZoneOnOffNChoices, GuardZoneOnOffChoices, 1, wxRA_SPECIFY_ROWS );
	GuardZoneOnOff->SetSelection( 0 );
	sbSizer18->Add( GuardZoneOnOff, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer19;
	sbSizer19 = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, _("Outer Range Meters") ), wxVERTICAL );
	
	OuterRange = new wxSpinCtrl( sbSizer19->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 0, 20000, 0 );
	sbSizer19->Add( OuterRange, 0, wxALL, 5 );
	
	
	bSizer13->Add( sbSizer19, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer20;
	sbSizer20 = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, _("Inner Range Meters") ), wxHORIZONTAL );
	
	InnerRange = new wxSpinCtrl( sbSizer20->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, 0, 20000, 0 );
	sbSizer20->Add( InnerRange, 0, wxALL, 5 );
	
	
	bSizer13->Add( sbSizer20, 1, wxEXPAND, 5 );
	
	
	sbSizer18->Add( bSizer13, 0, wxEXPAND, 5 );
	
	wxString PartialArcNoYesChoices[] = { _("No"), _("Yes") };
	int PartialArcNoYesNChoices = sizeof( PartialArcNoYesChoices ) / sizeof( wxString );
	PartialArcNoYes = new wxRadioBox( sbSizer18->GetStaticBox(), wxID_ANY, _("Partial Arc"), wxDefaultPosition, wxDefaultSize, PartialArcNoYesNChoices, PartialArcNoYesChoices, 1, wxRA_SPECIFY_ROWS );
	PartialArcNoYes->SetSelection( 0 );
	sbSizer18->Add( PartialArcNoYes, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, _("Start Angle") ), wxVERTICAL );
	
	StartAngle = new wxSpinCtrl( sbSizer21->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, -360, 360, 0 );
	sbSizer21->Add( StartAngle, 0, wxALL, 5 );
	
	
	bSizer14->Add( sbSizer21, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer22;
	sbSizer22 = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, _("End Angle") ), wxVERTICAL );
	
	EndAngle = new wxSpinCtrl( sbSizer22->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, -360, 360, 0 );
	sbSizer22->Add( EndAngle, 0, wxALL, 5 );
	
	
	bSizer14->Add( sbSizer22, 1, wxEXPAND, 5 );
	
	
	sbSizer18->Add( bSizer14, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer24;
	sbSizer24 = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, _("Guard Zone Color") ), wxVERTICAL );
	
	m_colorpicker = new wxColourPickerCtrl( sbSizer24->GetStaticBox(), wxID_ANY, wxColour( 255, 255, 0 ), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE|wxCLRP_USE_TEXTCTRL );
	sbSizer24->Add( m_colorpicker, 0, wxALL, 5 );
	
	
	sbSizer18->Add( sbSizer24, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* gztranpsizer;
	gztranpsizer = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, _("Guard Zone Transparency") ), wxVERTICAL );
	
	pGZTranSlider = new wxSlider( gztranpsizer->GetStaticBox(), wxID_ANY, 90, 10, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	gztranpsizer->Add( pGZTranSlider, 1, wxEXPAND, 5 );
	
	
	sbSizer18->Add( gztranpsizer, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer29;
	sbSizer29 = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, _("Alarm Sensitivity") ), wxVERTICAL );
	
	AlarmSensitivitySlider = new wxSlider( sbSizer29->GetStaticBox(), wxID_ANY, 5, 1, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS );
	sbSizer29->Add( AlarmSensitivitySlider, 0, wxEXPAND, 5 );
	
	
	sbSizer18->Add( sbSizer29, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer30;
	sbSizer30 = new wxStaticBoxSizer( new wxStaticBox( sbSizer18->GetStaticBox(), wxID_ANY, _("Alarm Sound") ), wxHORIZONTAL );
	
	AlarmSelectButton = new wxButton( sbSizer30->GetStaticBox(), wxID_ANY, _("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer30->Add( AlarmSelectButton, 0, wxALL, 5 );
	
	AlarmTestButton = new wxButton( sbSizer30->GetStaticBox(), wxID_ANY, _("Test"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer30->Add( AlarmTestButton, 0, wxALL, 5 );
	
	
	sbSizer18->Add( sbSizer30, 1, wxEXPAND, 5 );
	
	
	bSizer10->Add( sbSizer18, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer23;
	sbSizer23 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	closebutton = new wxButton( sbSizer23->GetStaticBox(), wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer23->Add( closebutton, 0, wxALL, 5 );
	
	
	bSizer10->Add( sbSizer23, 1, wxEXPAND, 5 );
	
	
	bSizer9->Add( bSizer10, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer9 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SentryDialogBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( SentryDialogBase::OnSize ) );
	TimedTransmit->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( SentryDialogBase::OnTimedTransmitClick ), NULL, this );
	StandbyMinutes->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateStandbyMinutes ), NULL, this );
	TransmitMinutes->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateTransmitMinutes ), NULL, this );
	GuardZoneOnOff->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( SentryDialogBase::OnGuardZoneClick ), NULL, this );
	OuterRange->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateOuterRange ), NULL, this );
	InnerRange->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateInnerRange ), NULL, this );
	PartialArcNoYes->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( SentryDialogBase::OnPartialArcClick ), NULL, this );
	StartAngle->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateStartAngle ), NULL, this );
	EndAngle->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateEndAngle ), NULL, this );
	m_colorpicker->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SentryDialogBase::OnColorChanged ), NULL, this );
	pGZTranSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SentryDialogBase::OnUpdateTranSlider ), NULL, this );
	AlarmSensitivitySlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SentryDialogBase::OnUpdateSensitivitySlider ), NULL, this );
	AlarmSelectButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryDialogBase::OnAlarmSelect ), NULL, this );
	AlarmTestButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryDialogBase::OnAlarmTest ), NULL, this );
	closebutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryDialogBase::OnSentryCloseClick ), NULL, this );
}

SentryDialogBase::~SentryDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SentryDialogBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( SentryDialogBase::OnSize ) );
	TimedTransmit->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( SentryDialogBase::OnTimedTransmitClick ), NULL, this );
	StandbyMinutes->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateStandbyMinutes ), NULL, this );
	TransmitMinutes->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateTransmitMinutes ), NULL, this );
	GuardZoneOnOff->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( SentryDialogBase::OnGuardZoneClick ), NULL, this );
	OuterRange->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateOuterRange ), NULL, this );
	InnerRange->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateInnerRange ), NULL, this );
	PartialArcNoYes->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( SentryDialogBase::OnPartialArcClick ), NULL, this );
	StartAngle->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateStartAngle ), NULL, this );
	EndAngle->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SentryDialogBase::OnUpdateEndAngle ), NULL, this );
	m_colorpicker->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SentryDialogBase::OnColorChanged ), NULL, this );
	pGZTranSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SentryDialogBase::OnUpdateTranSlider ), NULL, this );
	AlarmSensitivitySlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SentryDialogBase::OnUpdateSensitivitySlider ), NULL, this );
	AlarmSelectButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryDialogBase::OnAlarmSelect ), NULL, this );
	AlarmTestButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryDialogBase::OnAlarmTest ), NULL, this );
	closebutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryDialogBase::OnSentryCloseClick ), NULL, this );
	
}

SentryAlarmDialogBase::SentryAlarmDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer27;
	sbSizer27 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );
	
	m_staticText1 = new wxStaticText( sbSizer27->GetStaticBox(), wxID_ANY, _("Radar Sentry Alarm"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( 15, 70, 90, 90, false, wxEmptyString ) );
	
	sbSizer27->Add( m_staticText1, 1, wxALIGN_CENTER|wxALL, 5 );
	
	SilenceButton = new wxButton( sbSizer27->GetStaticBox(), wxID_ANY, _("Silence"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer27->Add( SilenceButton, 0, wxALIGN_CENTER|wxALL|wxTOP, 5 );
	
	
	bSizer14->Add( sbSizer27, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer28;
	sbSizer28 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxHORIZONTAL );
	
	closebutton = new wxButton( sbSizer28->GetStaticBox(), wxID_ANY, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer28->Add( closebutton, 0, wxALL, 5 );
	
	
	bSizer14->Add( sbSizer28, 0, wxALIGN_RIGHT|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer14 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SentryAlarmDialogBase::OnClose ) );
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( SentryAlarmDialogBase::OnSize ) );
	SilenceButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryAlarmDialogBase::OnAlarmSilenceClick ), NULL, this );
	closebutton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryAlarmDialogBase::OnAlarmCloseClick ), NULL, this );
}

SentryAlarmDialogBase::~SentryAlarmDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( SentryAlarmDialogBase::OnClose ) );
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( SentryAlarmDialogBase::OnSize ) );
	SilenceButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryAlarmDialogBase::OnAlarmSilenceClick ), NULL, this );
	closebutton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SentryAlarmDialogBase::OnAlarmCloseClick ), NULL, this );
	
}
