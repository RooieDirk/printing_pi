/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Printing Plugin
 * Author:   Mike Rossiter
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Mike Rossiter                                   *
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

#ifndef _SDR_PI_H_
#define _SDR_PI_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include <wx/glcanvas.h>
#endif // precompiled headers

#include <wx/fileconf.h>
#include <wx/datetime.h>
#include <wx/tokenzr.h>

#include "config.h"

#include "pidc.h"

#include "json/reader.h"
#include "json/writer.h"

#include "ocpn_plugin.h" //Required for OCPN plugin functions
#include "Printinggui.h"


// Define minimum and maximum versions of the grib plugin supported
#define GRIB_MAX_MAJOR 4
#define GRIB_MAX_MINOR 1
#define GRIB_MIN_MAJOR 4
#define GRIB_MIN_MINOR 1

class Dlg;

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define Printing_TOOL_POSITION                                               \
    -1 // Request default positioning of toolbar tool

class Printing_pi : public opencpn_plugin_118 {
public:
    Printing_pi(void* ppimgr);
    ~Printing_pi(void);

    //    The required PlugIn Methods
    int Init(void);
    bool DeInit(void);

    int GetAPIVersionMajor();
    int GetAPIVersionMinor();
    int GetPlugInVersionMajor();
    int GetPlugInVersionMinor();
    wxBitmap* GetPlugInBitmap();
    wxString GetCommonName();
    wxString GetShortDescription();
    wxString GetLongDescription();


    //    Optional plugin overrides
    void SetColorScheme(PI_ColorScheme cs);
    bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
    bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
    void Render(piDC &dc, PlugIn_ViewPort *vp);
    //    The override PlugIn Methods
    void OnContextMenuItemCallback(int id);



    //    Other public methods
    void OnPrintingDialogClose();


    double GetCursorLat(void) { return m_cursor_lat; }
    double GetCursorLon(void) { return m_cursor_lon; }

    void ShowPreferencesDialog(wxWindow* parent);

    double m_tr_spd;
    double m_tr_dir;

    wxString StandardPath();
    wxBitmap m_panelBitmap;




private:
    double m_cursor_lat;
    double m_cursor_lon;

    int m_position_menu_id;
    double m_GUIScaleFactor;
    void OnClose(wxCloseEvent& event);

    Printing_pi* plugin;

    Dlg* m_pDialog;

    wxFileConfig* m_pconfig;
    wxWindow* m_parent_window;
    bool LoadConfig(void);
    bool SaveConfig(void);

    int m_hr_dialog_width, m_hr_dialog_height;
    int m_hr_dialog_sx, m_hr_dialog_sy;
    int m_display_width, m_display_height;
    int m_leftclick_tool_id;
    bool m_bPrintingShowIcon;
    //bool m_bShowPrinting;

    bool m_bCopyUseAis;
    bool m_bCopyUseFile;
    wxString m_tCopyMMSI;

};

#endif
