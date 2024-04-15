/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Printing Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                *
 *   $EMAIL$                                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif  // precompiled headers

#include "Printing_pi.h"
#include "Printinggui.h"
#include "ocpn_plugin.h"

class Printing_pi;
class Dlg;


// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void* ppimgr) {
  return new Printing_pi(ppimgr);
}
extern "C" DECL_EXP int AddCanvasContextMenuItem(wxMenuItem *pitem,
                                                 opencpn_plugin *pplugin);
extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p) { delete p; }

//---------------------------------------------------------------------------------------------------------
//
//    Printing PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

/**
 * Load a icon, possibly using SVG
 * Parameters
 *  - api_name: Argument to GetPluginDataDir()
 *  - icon_name: Base name of icon living in data/ directory. When using
 *    SVG icon_name.svg is used, otherwise icon_name.png
 */

// static wxBitmap load_plugin(const char* icon_name, const char* api_name) {
//
//   wxFileName fn;
//   auto path = GetPluginDataDir(api_name);
//   fn.SetPath(path);
//   fn.AppendDir("data");
//   fn.SetName(icon_name);
// #ifdef ocpnUSE_SVG
//   wxLogDebug("Loading SVG icon");
//   fn.SetExt("svg");
//   const static int ICON_SIZE = 48;  // FIXME: Needs size from GUI
//   bitmap = GetBitmapFromSVGFile(fn.GetFullPath(), ICON_SIZE, ICON_SIZE);
// #else
//   wxLogDebug("Loading png icon");
//   fn.SetExt("png");
//   path = fn.GetFullPath();
//   if (!wxImage::CanRead(path)) {
//     wxLogDebug("Initiating image handlers.");
//     wxInitAllImageHandlers();
//   }
//   wxImage panelIcon(path);
//   bitmap = wxBitmap(panelIcon);
// #endif
//   wxLogDebug("Icon loaded, result: %s", bitmap.IsOk() ? "ok" : "fail");
//   return bitmap;
// }

Printing_pi::Printing_pi(void* ppimgr) : opencpn_plugin_118(ppimgr) {
  // Create the PlugIn icons
//   initialize_images();
//   m_panelBitmap = load_plugin("printing_panel_icon", "Printing_pi");

  m_bShowPrinting = false;
}

Printing_pi::~Printing_pi(void) {
  delete _img_PrintingIcon;

  if (m_pDialog) {
    wxFileConfig* pConf = GetOCPNConfigObject();
    ;

    if (pConf) {
      pConf->SetPath("/PlugIns/Printing_pi");
      pConf->Write("printingUseAis", m_bCopyUseAis);
      pConf->Write("printingUseFile", m_bCopyUseFile);
      pConf->Write("printingMMSI", m_tCopyMMSI);
    }
  }
}

int Printing_pi::Init(void) {
  AddLocaleCatalog("opencpn-Printing_pi");

  // Set some default private member parameters
  m_hr_dialog_x = 40;
  m_hr_dialog_y = 80;
  m_hr_dialog_sx = 400;
  m_hr_dialog_sy = 300;
  ::wxDisplaySize(&m_display_width, &m_display_height);

  //    Get a pointer to the opencpn display canvas, to use as a parent for
  //    the POI Manager dialog
  m_parent_window = GetOCPNCanvasWindow();

  //    Get a pointer to the opencpn configuration object
  m_pconfig = GetOCPNConfigObject();

  //    And load the configuration items
  LoadConfig();
  wxMenu dummy_menu;
  m_position_menu_id = AddCanvasContextMenuItem(
      new wxMenuItem(&dummy_menu, -1, _("Select Chart boundary scales")),
      this);

  //    This PlugIn needs a toolbar icon, so request its insertion


  m_pDialog = NULL;

  return (WANTS_OVERLAY_CALLBACK | WANTS_OPENGL_OVERLAY_CALLBACK |
  WANTS_PREFERENCES | INSTALLS_CONTEXTMENU_ITEMS| WANTS_CONFIG);
}

bool Printing_pi::DeInit(void) {
  //    Record the dialog position
  if (NULL != m_pDialog) {
    // Capture dialog position
    wxPoint p = m_pDialog->GetPosition();
    wxRect r = m_pDialog->GetRect();
    SetPrintingDialogX(p.x);
    SetPrintingDialogY(p.y);
    SetPrintingDialogSizeX(r.GetWidth());
    SetPrintingDialogSizeY(r.GetHeight());
    m_pDialog->Close();
    delete m_pDialog;
    m_pDialog = NULL;

    m_bShowPrinting = false;
    SetToolbarItemState(m_leftclick_tool_id, m_bShowPrinting);
  }

  SaveConfig();

  RequestRefresh(m_parent_window);  // refresh main window

  return true;
}

int Printing_pi::GetAPIVersionMajor() { return atoi(API_VERSION); }

int Printing_pi::GetAPIVersionMinor() {
  std::string v(API_VERSION);
  size_t dotpos = v.find('.');
  return atoi(v.substr(dotpos + 1).c_str());
}

int Printing_pi::GetPlugInVersionMajor() { return PLUGIN_VERSION_MAJOR; }

int Printing_pi::GetPlugInVersionMinor() { return PLUGIN_VERSION_MINOR; }

int GetPlugInVersionPatch() { return PLUGIN_VERSION_PATCH; }

int GetPlugInVersionPost() { return PLUGIN_VERSION_TWEAK; };

const char* GetPlugInVersionPre() { return PKG_PRERELEASE; }

const char* GetPlugInVersionBuild() { return PKG_BUILD_INFO; }

wxBitmap* Printing_pi::GetPlugInBitmap() { return &m_panelBitmap; }

wxString Printing_pi::GetCommonName() { return PLUGIN_API_NAME; }

wxString Printing_pi::GetShortDescription() { return PKG_SUMMARY; }

wxString Printing_pi::GetLongDescription() { return PKG_DESCRIPTION; }


void Printing_pi::SetColorScheme(PI_ColorScheme cs) {
  if (NULL == m_pDialog) return;

  DimeWindow(m_pDialog);
}

void Printing_pi::ShowPreferencesDialog(wxWindow* parent) {
  printingPreferences* Pref = new printingPreferences(parent);

//   Pref->m_cbTransmitAis->SetValue(m_bCopyUseAis);
//   Pref->m_cbAisToFile->SetValue(m_bCopyUseFile);
//   Pref->m_textCtrlMMSI->SetValue(m_tCopyMMSI);

  if (Pref->ShowModal() == wxID_OK) {
//     bool copyAis = Pref->m_cbTransmitAis->GetValue();
//     bool copyFile = Pref->m_cbAisToFile->GetValue();
//     wxString copyMMSI = Pref->m_textCtrlMMSI->GetValue();
//
//     if (m_bCopyUseAis != copyAis || m_bCopyUseFile != copyFile ||
//         m_tCopyMMSI != copyMMSI) {
//       m_bCopyUseAis = copyAis;
//       m_bCopyUseFile = copyFile;
//       m_tCopyMMSI = copyMMSI;
    }

    if (m_pDialog) {
//       m_pDialog->m_bUseAis = m_bCopyUseAis;
//       m_pDialog->m_bUseFile = m_bCopyUseFile;
//       m_pDialog->m_tMMSI = m_tCopyMMSI;
    }

    SaveConfig();

    RequestRefresh(m_parent_window);  // refresh main window


  delete Pref;
  Pref = NULL;
}



bool Printing_pi::LoadConfig(void) {
  wxFileConfig* pConf = (wxFileConfig*)m_pconfig;

  if (pConf) {
    if (pConf->HasGroup(_T("/Settings/Printing_pi"))) {
      // Read the existing settings

      pConf->SetPath("/Settings/Printing_pi");
      pConf->Read("ShowPrintingIcon", &m_bPrintingShowIcon, 1);
      pConf->Read("printingUseAis", &m_bCopyUseAis, 0);
      pConf->Read("printingUseFile", &m_bCopyUseFile, 0);
      m_tCopyMMSI = pConf->Read("printingMMSI", "123456789");

      m_hr_dialog_x = pConf->Read("DialogPosX", 40L);
      m_hr_dialog_y = pConf->Read("DialogPosY", 140L);
      m_hr_dialog_sx = pConf->Read("DialogSizeX", 330L);
#ifdef __WXOSX__
      m_hr_dialog_sy = pConf->Read("DialogSizeY", 250L);
#else
      m_hr_dialog_sy = pConf->Read("DialogSizeY", 300L);
#endif
      pConf->DeleteGroup(_T("/Settings/Printing_pi"));
    } else {
      pConf->SetPath("/PlugIns/Printing_pi");
      pConf->Read("ShowPrintingIcon", &m_bPrintingShowIcon, 1);
      pConf->Read("printingUseAis", &m_bCopyUseAis, 0);
      pConf->Read("printingUseFile", &m_bCopyUseFile, 0);
      m_tCopyMMSI = pConf->Read("printingMMSI", "123456789");

      m_hr_dialog_x = pConf->Read("DialogPosX", 40L);
      m_hr_dialog_y = pConf->Read("DialogPosY", 140L);
      m_hr_dialog_sx = pConf->Read("DialogSizeX", 330L);
#ifdef __WXOSX__
      m_hr_dialog_sy = pConf->Read("DialogSizeY", 250L);
#else
      m_hr_dialog_sy = pConf->Read("DialogSizeY", 300L);
#endif
    }
    if ((m_hr_dialog_x < 0) || (m_hr_dialog_x > m_display_width))
      m_hr_dialog_x = 40;
    if ((m_hr_dialog_y < 0) || (m_hr_dialog_y > m_display_height))
      m_hr_dialog_y = 140;

    return true;
  } else
    return false;
}

bool Printing_pi::SaveConfig(void) {
  wxFileConfig* pConf = (wxFileConfig*)m_pconfig;

  if (pConf) {
    bool bIsDigits = m_tCopyMMSI.IsNumber();
    if (m_tCopyMMSI.length() < 9 || !bIsDigits) {
      wxMessageBox(_("MMSI must be 9 digits.\nEdit using Preferences"));
      return false;
    }

    pConf->SetPath("/PlugIns/Printing_pi");
    pConf->Write("ShowPrintingIcon", m_bPrintingShowIcon);
    pConf->Write("printingUseAis", m_bCopyUseAis);
    pConf->Write("printingUseFile", m_bCopyUseFile);
    pConf->Write("printingMMSI", m_tCopyMMSI);

    pConf->Write("DialogPosX", m_hr_dialog_x);
    pConf->Write("DialogPosY", m_hr_dialog_y);
    pConf->Write("DialogSizeX", m_hr_dialog_sx);
    pConf->Write("DialogSizeY", m_hr_dialog_sy);

    return true;
  } else
    return false;
}

void Printing_pi::OnPrintingDialogClose() {
  m_bShowPrinting = false;
  m_pDialog->Hide();
  SaveConfig();

  RequestRefresh(m_parent_window);  // refresh main window
}

void Printing_pi::OnContextMenuItemCallback(int id) {
  if(id==m_position_menu_id){
  if (!m_pDialog) m_pDialog = new Dlg(m_parent_window, -1);

  if (m_pDialog->IsShown())
    m_pDialog->Hide();
  else
    m_pDialog->Show();
  }//m_pDialog->OnContextMenu(m_cursor_lat, m_cursor_lon);
}




