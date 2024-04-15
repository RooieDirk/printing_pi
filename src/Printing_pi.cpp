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

bool g_bBorderTop;
bool g_bBorderLeft;
bool g_bBorderRight;
bool g_bBorderBottom;
wxFont g_MajorFont;
wxFont g_MinorFont;
wxSize g_MajorSize;
wxSize g_MinorSize;
//---------------------------------------------------------------------------------------------------------
//
//    Printing PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"


Printing_pi::Printing_pi(void* ppimgr) : opencpn_plugin_118(ppimgr) {
  // Create the PlugIn icons
//   initialize_images();
//   m_panelBitmap = load_plugin("printing_panel_icon", "Printing_pi");

  //m_bShowPrinting = false;
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
//   m_hr_dialog_x = 40;
//   m_hr_dialog_y = 80;
//   m_hr_dialog_sx = 400;
//   m_hr_dialog_sy = 300;
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

  m_pDialog = NULL;

  return (WANTS_OVERLAY_CALLBACK | WANTS_OPENGL_OVERLAY_CALLBACK |
  WANTS_PREFERENCES | INSTALLS_CONTEXTMENU_ITEMS| WANTS_CONFIG);
}

bool Printing_pi::DeInit(void) {
  //    Record the dialog position
  if (NULL != m_pDialog) {
    m_pDialog->Close();
    delete m_pDialog;
    m_pDialog = NULL;
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

  if (Pref->ShowModal() != wxID_OK) {
    g_MajorFont = Pref->MajorBckup;
    g_MinorFont = Pref->MinorBckup;
  }
  SaveConfig();
  RequestRefresh(m_parent_window);  // refresh main window

  delete Pref;
  Pref = NULL;
}



bool Printing_pi::LoadConfig(void) {
  wxFileConfig* pConf = (wxFileConfig*)m_pconfig;

  if (pConf) {
    pConf->SetPath("/PlugIns/Printing_pi");
      wxString s;
        pConf->Read("MajorFont", &s);
      g_MajorFont.SetNativeFontInfo(s);
        pConf->Read("MinorFont", &s);
      g_MinorFont.SetNativeFontInfo(s);

      pConf->Read("BorderTop", &g_bBorderTop, false);
      pConf->Read("BorderLeft", &g_bBorderLeft, false);
      pConf->Read("BorderRight", &g_bBorderRight, false);
      pConf->Read("BorderBottom", &g_bBorderBottom, false);

//       m_hr_dialog_x = pConf->Read("DialogPosX", 40L);
//       m_hr_dialog_y = pConf->Read("DialogPosY", 140L);
//       m_hr_dialog_sx = pConf->Read("DialogSizeX", 330L);
// #ifdef __WXOSX__
//       m_hr_dialog_sy = pConf->Read("DialogSizeY", 250L);
// #else
//       m_hr_dialog_sy = pConf->Read("DialogSizeY", 300L);
// #endif
      printingPreferences::SetSizes();
      return true;
  } else
      return false;
}

bool Printing_pi::SaveConfig(void) {
  wxFileConfig* pConf = (wxFileConfig*)m_pconfig;

  if (pConf) {
    pConf->SetPath("/PlugIns/Printing_pi");

    pConf->Write("MajorFont", g_MajorFont.GetNativeFontInfoDesc());
    pConf->Write("MinorFont", g_MinorFont.GetNativeFontInfoDesc());
    pConf->Write("BorderTop", g_bBorderTop);
    pConf->Write("BorderLeft", g_bBorderLeft);
    pConf->Write("BorderRight", g_bBorderRight);
    pConf->Write("BorderBottom", g_bBorderBottom);

//     pConf->Write("DialogPosX", m_hr_dialog_x);
//     pConf->Write("DialogPosY", m_hr_dialog_y);
//     pConf->Write("DialogSizeX", m_hr_dialog_sx);
//     pConf->Write("DialogSizeY", m_hr_dialog_sy);

    return true;
  } else
    return false;
}

void Printing_pi::OnPrintingDialogClose() {
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
  }
}



bool Printing_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
  piDC pidc(dc);
  Render(pidc, vp);
  return true;
}

bool Printing_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
  piDC pidc;
  glEnable( GL_BLEND );
  pidc.SetVP(vp);
  Render(pidc, vp);
  glDisable( GL_BLEND );
  return true;
}

void Printing_pi::Render(piDC &dc, PlugIn_ViewPort *vp)
{
  dc.SetFont(g_MajorFont);
  dc.SetPen(wxPen(*wxWHITE,1));
  dc.SetTextForeground(*wxBLACK);
  dc.SetTextBackground(*wxWHITE);
  dc.SetBrush(*wxWHITE_BRUSH);
  wxString s("TESTtest");

//    dc.DrawText(s, 100,100);
  wxRect ChartR(0,0,vp->pix_width, vp->pix_height);
if(g_bBorderLeft){
  dc.DrawRectangle(0,0,g_MajorSize.x+10,vp->pix_height );
  ChartR=wxRect(g_MajorSize.x+10, 0, ChartR.GetWidth()-(g_MajorSize.x+10), ChartR.GetHeight() );
}
if(g_bBorderTop){
  dc.DrawRectangle(0,0,vp->pix_width, g_MajorSize.y+10 );
  ChartR=wxRect(ChartR.GetLeft(), g_MajorSize.y+10, ChartR.GetWidth(), ChartR.GetHeight()-(g_MajorSize.y+10));
}
if(g_bBorderRight){
  dc.DrawRectangle(vp->pix_width-(g_MajorSize.x+10), 0, vp->pix_width, vp->pix_height );
  ChartR=wxRect(ChartR.GetLeft(), ChartR.GetTop(), ChartR.GetWidth()-(g_MajorSize.x+10), ChartR.GetHeight());
}
if(g_bBorderBottom){
  dc.DrawRectangle(0, vp->pix_height-(g_MajorSize.y+10), vp->pix_width, g_MajorSize.y+10 );
  ChartR=wxRect(ChartR.GetLeft(), ChartR.GetTop(), ChartR.GetWidth(), ChartR.GetHeight()-(g_MajorSize.y+10));
}

dc.SetPen(wxPen(*wxBLACK,1));
dc.SetBrush(*wxTRANSPARENT_BRUSH);
dc.DrawRectangle(ChartR);
wxRect Tics(ChartR);
Tics.Inflate(4);
dc.DrawRectangle(Tics);
wxRect TicsMajor(Tics);
TicsMajor.Inflate(4);
dc.DrawRectangle(TicsMajor);
  }



