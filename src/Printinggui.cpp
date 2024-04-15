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
//*)


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

  BEGIN_EVENT_TABLE(Dlg,wxDialog)
  //(*EventTable(Dlg)
  //*)
  END_EVENT_TABLE()

  Dlg::Dlg(wxWindow* parent,wxWindowID id)
  {
    //(*Initialize(Dlg)
    wxFlexGridSizer* ChartPanelFGSizer;
    wxGridBagSizer* MainGridBagSizer;

    Create(parent, id, _("Chart Boundery"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_DIALOG_STYLE|wxCLOSE_BOX, _T("id"));
    SetClientSize(wxSize(200,200));
    MainGridBagSizer = new wxGridBagSizer(0, 0);
    CheckBoxTop = new wxCheckBox(this, ID_CHECKBOX_TOP, _("Top"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_TOP"));
    CheckBoxTop->SetValue(false);
    MainGridBagSizer->Add(CheckBoxTop, wxGBPosition(0, 1), wxGBSpan(1, 3), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxLeft = new wxCheckBox(this, ID_CHECKBOX_LEFT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_LEFT"));
    CheckBoxLeft->SetValue(false);
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
    CheckBoxRight->SetValue(false);
    MainGridBagSizer->Add(CheckBoxRight, wxGBPosition(1, 4), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    RightPanel = new wxPanel(this, ID_PANEL_RIGHT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_RIGHT"));
    MainGridBagSizer->Add(RightPanel, wxGBPosition(2, 4), wxGBSpan(2, 1), wxEXPAND, 5);
    CheckBoxBottom = new wxCheckBox(this, ID_CHECKBOX_BOTTOM, _("Bottom"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_BOTTOM"));
    CheckBoxBottom->SetValue(false);
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
  }

  ///////////////////////////////////////////////////////////////////////////////////////

  printingPreferences::printingPreferences( wxWindow* parent, wxWindowID id , const wxString& title , const wxPoint& pos , const wxSize& size, long style  ){}

  printingPreferences::~printingPreferences(){}
