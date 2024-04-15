

#pragma once

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include <wx/glcanvas.h>
#endif // precompiled headers

#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/gbsizer.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
//*)

class Dlg: public wxDialog
{
public:

  Dlg(wxWindow* parent,wxWindowID id = -1);
  virtual ~Dlg();

private:

  //(*Handlers(Dlg)
  void OnQuit(wxCommandEvent& event);
  void OnCheckBoxClick(wxCommandEvent& event);
  //*)

  //(*Identifiers(Dlg)
  static const long ID_CHECKBOX_TOP;
  static const long ID_CHECKBOX_LEFT;
  static const long ID_PANEL2;
  static const long ID_STATICTEXT1;
  static const long ID_STATICTEXT2;
  static const long ID_CHARTPANEL;
  static const long ID_CHECKBOX_RIGHT;
  static const long ID_PANEL_RIGHT;
  static const long ID_CHECKBOX_BOTTOM;
  static const long ID_STATICLINE1;
  //*)

  //(*Declarations(Dlg)
  wxCheckBox* CheckBoxBottom;
  wxCheckBox* CheckBoxLeft;
  wxCheckBox* CheckBoxRight;
  wxCheckBox* CheckBoxTop;
  wxPanel* ChartPanel;
  wxPanel* LeftPanel;
  wxPanel* RightPanel;
  wxStaticLine* StaticLine1;
  wxStaticText* StaticText1;
  wxStaticText* StaticText2;
  //*)

  DECLARE_EVENT_TABLE()
};


///////////////////////////////////////////////////////////////////////////////
/// Class printingPreferences
///////////////////////////////////////////////////////////////////////////////
class printingPreferences : public wxDialog
{
	private:

	protected:
// 		wxStdDialogButtonSizer* m_sdbSizer1;
// 		wxButton* m_sdbSizer1OK;
// 		wxButton* m_sdbSizer1Cancel;

	public:
// 		wxCheckBox* m_cbTransmitAis;
// 		wxCheckBox* m_cbAisToFile;
// 		wxTextCtrl* m_textCtrlMMSI;

		printingPreferences( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Preferences"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxRESIZE_BORDER );

		~printingPreferences();

};

