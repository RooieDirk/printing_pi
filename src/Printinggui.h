

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
#include <wx/fontpicker.h>
#include "Printing_pi.h"

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

};


///////////////////////////////////////////////////////////////////////////////
/// Class printingPreferences
///////////////////////////////////////////////////////////////////////////////
class printingPreferences : public wxDialog
{
public:

  printingPreferences(wxWindow* parent,  wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
  virtual ~printingPreferences();
  static void SetSizes();

  //(*Declarations(printingPreferences)
  wxFontPickerCtrl* FontPickerMajor;
  wxFontPickerCtrl* FontPickerMinor;
  wxStaticText* StaticText1;
  wxStaticText* StaticText2;

  wxFont MajorBckup;
  wxFont MinorBckup;
  wxWindow* Parent;

  //*)

protected:
  static const long ID_FONTPICKERMAJOR;
  static const long ID_FONTPICKERMINOR;


  //*)

private:

  //(*Handlers(printingPreferences)
  void OnFontPickerFontChanged(wxFontPickerEvent& event);
  //*)


};
