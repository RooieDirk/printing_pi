///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Printinggui.h"

///////////////////////////////////////////////////////////////////////////

#include <wx/settings.h>
#include <wx/string.h>
#include "ocpn_plugin.h"
#include "Printing_pi.h"

//*)

extern bool g_bBorderTop;
extern bool g_bBorderLeft;
extern bool g_bBorderRight;
extern bool g_bBorderBottom;
extern wxFont g_MajorFont;
extern wxFont g_MinorFont;
extern wxSize g_MajorSize;
extern wxSize g_MinorSize;

  //(*IdInit(Dlg)
  const long Dlg::ID_CHECKBOX_TOP = wxNewId();
  const long Dlg::ID_CHECKBOX_LEFT = wxNewId();
  const long Dlg::ID_PANEL2 = wxNewId();
  const long Dlg::ID_STATICTEXT1 = wxNewId();
  const long Dlg::ID_STATICTEXT2 = wxNewId();
  const long Dlg::ID_CHARTPANEL = wxNewId();
  const long Dlg::ID_CHECKBOX_RIGHT = wxNewId();
  const long Dlg::ID_PANEL_RIGHT = wxNewId();
  const long Dlg::ID_CHECKBOX_BOTTOM = wxNewId();
  const long Dlg::ID_STATICLINE1 = wxNewId();
  //*)


  Dlg::Dlg(wxWindow* parent,wxWindowID id)
  {
    //(*Initialize(Dlg)
    wxFlexGridSizer* ChartPanelFGSizer;
    wxGridBagSizer* MainGridBagSizer;

    Create(parent, id, _("Chart Boundery"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_DIALOG_STYLE|wxCLOSE_BOX, _T("id"));
    SetClientSize(wxSize(200,200));
    MainGridBagSizer = new wxGridBagSizer(0, 0);
    CheckBoxTop = new wxCheckBox(this, ID_CHECKBOX_TOP, _("Top"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_TOP"));
    CheckBoxTop->SetValue(g_bBorderTop);
    MainGridBagSizer->Add(CheckBoxTop, wxGBPosition(0, 1), wxGBSpan(1, 3), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxLeft = new wxCheckBox(this, ID_CHECKBOX_LEFT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_LEFT"));
    CheckBoxLeft->SetValue(g_bBorderLeft);
    MainGridBagSizer->Add(CheckBoxLeft, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LeftPanel = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    MainGridBagSizer->Add(LeftPanel, wxGBPosition(1, 0), wxGBSpan(2, 1), wxEXPAND, 5);
    ChartPanel = new wxPanel(this, ID_CHARTPANEL, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE|wxBORDER_DOUBLE|wxTAB_TRAVERSAL, _T("ID_CHARTPANEL"));
    ChartPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_LISTBOX));
    ChartPanelFGSizer = new wxFlexGridSizer(2, 1, 0, 0);
    StaticText1 = new wxStaticText(ChartPanel, ID_STATICTEXT1, _("Chart"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    ChartPanelFGSizer->Add(StaticText1, 1, wxALL|wxEXPAND, 5);
    StaticText2 = new wxStaticText(ChartPanel, ID_STATICTEXT2, _("Boundary"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    ChartPanelFGSizer->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    ChartPanel->SetSizer(ChartPanelFGSizer);
    MainGridBagSizer->Add(ChartPanel, wxGBPosition(1, 1), wxGBSpan(3, 3), wxLEFT|wxEXPAND, 5);
    CheckBoxRight = new wxCheckBox(this, ID_CHECKBOX_RIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_RIGHT"));
    CheckBoxRight->SetValue(g_bBorderRight);
    MainGridBagSizer->Add(CheckBoxRight, wxGBPosition(1, 4), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RightPanel = new wxPanel(this, ID_PANEL_RIGHT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_RIGHT"));
    MainGridBagSizer->Add(RightPanel, wxGBPosition(2, 4), wxGBSpan(2, 1), wxEXPAND, 5);
    CheckBoxBottom = new wxCheckBox(this, ID_CHECKBOX_BOTTOM, _("Bottom"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_BOTTOM"));
    CheckBoxBottom->SetValue(g_bBorderBottom);
    MainGridBagSizer->Add(CheckBoxBottom, wxGBPosition(4, 1), wxGBSpan(1, 3), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(100,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    MainGridBagSizer->Add(StaticLine1, wxGBPosition(5, 0), wxGBSpan(1, 4), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(MainGridBagSizer);
    Layout();
    Center();

    Connect(ID_CHECKBOX_TOP,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Dlg::OnCheckBoxClick);
    Connect(ID_CHECKBOX_LEFT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Dlg::OnCheckBoxClick);
    Connect(ID_CHECKBOX_RIGHT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Dlg::OnCheckBoxClick);
    Connect(ID_CHECKBOX_BOTTOM,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&Dlg::OnCheckBoxClick);

    //*)
  }

  Dlg::~Dlg()
  {
    //(*Destroy(Dlg)
    //*)
  }

  void Dlg::OnQuit(wxCommandEvent& event)
  {
    Close();
  }

  void Dlg::OnCheckBoxClick(wxCommandEvent& event)
  {
    g_bBorderTop = CheckBoxTop->GetValue();
    g_bBorderLeft = CheckBoxLeft->GetValue();
    g_bBorderRight = CheckBoxRight->GetValue();
    g_bBorderBottom = CheckBoxBottom->GetValue();

  }

  ///////////////////////////////////////////////////////////////////////////////////////

  const long printingPreferences::ID_FONTPICKERMAJOR = wxNewId();
  const long printingPreferences::ID_FONTPICKERMINOR = wxNewId();

  printingPreferences::printingPreferences( wxWindow* parent, wxWindowID id , const wxPoint& pos , const wxSize& size  ){
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    wxFlexGridSizer* FlexGridSizer1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStdDialogButtonSizer* StdDialogButtonSizer1;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Borderscale Fonts"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    StaticText1 = new wxStaticText(this, wxID_ANY, _("Mainfont (Whole degrees)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FontPickerMajor = new wxFontPickerCtrl(this, ID_FONTPICKERMAJOR, g_MajorFont, wxDefaultPosition, wxDefaultSize, wxFNTP_FONTDESC_AS_LABEL|wxFNTP_USEFONT_FOR_LABEL, wxDefaultValidator, _T("ID_FONTPICKERCTRL1"));
    wxFont FontPickerMajorFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    FontPickerMajor->SetFont(FontPickerMajorFont);
    FlexGridSizer1->Add(FontPickerMajor, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, wxID_ANY, _("Minorfont (minutes)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FontPickerMinor = new wxFontPickerCtrl(this, ID_FONTPICKERMINOR, g_MinorFont, wxDefaultPosition, wxDefaultSize, wxFNTP_FONTDESC_AS_LABEL|wxFNTP_USEFONT_FOR_LABEL, wxDefaultValidator, _T("ID_FONTPICKERMINOR"));
    FlexGridSizer1->Add(FontPickerMinor, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer1->Add(FlexGridSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
    StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
    StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
    StdDialogButtonSizer1->Realize();
    StaticBoxSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxEXPAND, 5);
    SetSizer(StaticBoxSizer1);
    StaticBoxSizer1->SetSizeHints(this);

    MajorBckup = g_MajorFont;
    MinorBckup = g_MinorFont;
    Parent = parent;

    Connect(ID_FONTPICKERMAJOR,wxEVT_COMMAND_FONTPICKER_CHANGED,(wxObjectEventFunction)&printingPreferences::OnFontPickerFontChanged);
    Connect(ID_FONTPICKERMINOR,wxEVT_COMMAND_FONTPICKER_CHANGED,(wxObjectEventFunction)&printingPreferences::OnFontPickerFontChanged);
    //*)
  }
  void printingPreferences::OnFontPickerFontChanged(wxFontPickerEvent& event)
  {
    g_MajorFont = FontPickerMajor->GetSelectedFont();
    g_MinorFont = FontPickerMinor->GetSelectedFont();
    SetSizes();
    RequestRefresh(Parent);
  }
  void printingPreferences::SetSizes()
  {
    wxMemoryDC dc;
    wxString s(_("59°"));
    wxCoord w, h;
    dc.SetFont(g_MajorFont);
    dc.GetTextExtent(s, &w, &h);
    g_MajorSize.Set(w,h);
    s=_("59'");
    dc.SetFont(g_MinorFont);
    dc.GetTextExtent(s, &w, &h);
    g_MinorSize.Set(w,h);
  }

  printingPreferences::~printingPreferences(){}
