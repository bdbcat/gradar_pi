/******************************************************************************
 * $Id: gradar_pi.h,v 1.8 2010/06/21 01:54:37 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  GRIB Plugin
 * Author:   David Register
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
 *   bdbcat@yahoo.com   *
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

#ifndef _GRADARPI_H_
#define _GRADARPI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#define     PLUGIN_VERSION_MAJOR    1
#define     PLUGIN_VERSION_MINOR    0

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    8

#ifndef PI
      #define PI        3.1415926535897931160E0      /* pi */
#endif

#ifdef __WXGTK__
//#include "/home/dsr/Projects/opencpn_sf/opencpn/include/ocpn_plugin.h"
#endif

#ifdef __WXMSW__
//#include "../../opencpn_sf/opencpn/include/ocpn_plugin.h"
#endif

#include "ocpn_plugin.h"

enum {
        ID_TEXTCTRL1 =            10000,
        ID_OK,
        ID_DORADIOBOX,
        ID_TRANSLIDER,
        ID_OMRADIOBOX,
        ID_LOGENABLE

};

enum {
        BM_ID_RED,
        BM_ID_RED_SLAVE,
        BM_ID_GREEN,
        BM_ID_GREEN_SLAVE,
        BM_ID_AMBER,
        BM_ID_AMBER_SLAVE,
        BM_ID_BLANK,
        BM_ID_BLANK_SLAVE

};

double piDistGreatCircle(double slat, double slon, double dlat, double dlon);

enum {
      RADAR_OFF,
      RADAR_ACTIVATE,
      RADAR_IN_TIMED_WARMUP,
      RADAR_STANDBY,
      RADAR_TX_ACTIVATE,
      RADAR_IN_TIMED_SPINUP,
      RADAR_TX_ACTIVE
      };


#pragma pack(push,1)

typedef struct {
      unsigned short    packet_type;
}packet_type_pkt;

typedef struct {
      unsigned int      packet_type;
      unsigned int      len1;
      unsigned short    angle;
      unsigned short    scan_length_bytes;
      unsigned short    scan_length_bytes_1;
      unsigned short    e;
      unsigned short    range_meters;
      unsigned short    fill[17];
      char              line_data;
}radar_scanline_pkt;

typedef struct {
      unsigned int      packet_type;
      unsigned int      len1;
      unsigned short    parm1;
}rad_ctl_pkt;

typedef struct {
      unsigned int      packet_type;
      unsigned int      len1;
      unsigned int      parm1;
}rad_range_pkt;


typedef struct {
      unsigned int      packet_type;
      unsigned int      len1;
      unsigned short    parm1;
      unsigned short    parm2;
      unsigned int      parm3;
      unsigned int      parm4;
}rad_status_pkt;

#pragma pack(pop)


//    Forward definitions
class MulticastRXThread;
class GRadarDialog;

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define GRADAR_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class gradar_pi : public opencpn_plugin_18
{
public:
      gradar_pi(void *ppimgr);

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

//    The required override PlugIn Methods
      bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
      bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
      void SetCursorLatLon(double lat, double lon);
      void SetPositionFix(PlugIn_Position_Fix &pfix);
      void SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);
      void OnContextMenuItemCallback(int id);

      void SetDefaults(void);

      int GetToolbarToolCount(void);

      void ShowPreferencesDialog( wxWindow* parent );

      void OnToolbarToolCallback(int id);


// Other public methods


      void OnDialogClose();

      void OnGRadarDialogClose();         // Control dialog
      void SetUpdateMode(int mode);
      void UpdateDisplayParameters(void);
      void SetOperatingMode(int mode);

      void SetGRadarDialogX(int x){ m_GRadar_dialog_x = x; }
      void SetGRadarDialogY(int y){ m_GRadar_dialog_y = y; }
      void SetGRadarDialogSizeX(int sx){ m_GRadar_dialog_sx = sx; }
      void SetGRadarDialogSizeY(int sy){ m_GRadar_dialog_sy = sy; }

private:
      bool LoadConfig(void);
      bool SaveConfig(void);

      void RadarTxOff(void);
      void RadarTxOn(void);
      void UpdateState(void);
      void DoTick(void);

      void Select_Range(double range);
      void RenderRadarBufferDirect(PlugIn_ViewPort *vp);
      void RenderRadarOverlaySwept(wxPoint radar_center, double v_scale_ppm, PlugIn_ViewPort *vp);
      void RenderRadarOverlayFull(wxPoint radar_center, double v_scale_ppm, PlugIn_ViewPort *vp);

      void RenderRadarBuffer(unsigned char *buffer, int buffer_line_length, wxDC *pdc,
                              int width, int height);
      void draw_blob_dc(wxDC &dc, double angle, double radius, double blob_r, double arc_length,
                               double scale, int xoff, int yoff);
      void draw_blob_gl(double angle, double radius, double blob_r, double arc_length);

      void CacheSetToolbarToolBitmaps(int bm_id_normal, int bm_id_rollover);

      wxFileConfig     *m_pconfig;
      wxWindow         *m_parent_window;
      wxMenu           *m_pmenu;

      int              m_display_width, m_display_height;
      int              m_tool_id;
      bool              m_bShowIcon;
      wxBitmap          *m_pdeficon;

      //    Controls added to Preferences panel
      wxCheckBox              *m_pShowIcon;

      wxMutex                 m_mutex;
      MulticastRXThread       *m_pmcrxt;

      wxDatagramSocket   *m_out_sock101;
      wxDateTime         m_dt_last_render;

      GRadarDialog       *m_pControlDialog;

      int                m_GRadar_dialog_sx, m_GRadar_dialog_sy ;
      int                m_GRadar_dialog_x, m_GRadar_dialog_y ;

      wxBitmap           *m_ptemp_icon;
      wxLogWindow	*m_plogwin;
      int               m_sent_bm_id_normal;
      int               m_sent_bm_id_rollover;

};



class MulticastRXThread: public wxThread
{

      public:

            MulticastRXThread(wxMutex *pMutex, const wxString &IP_addr, const wxString &service_port);
            ~MulticastRXThread(void);
            void *Entry(void);

            void OnExit(void);

      private:
            void process_buffer(void);


            wxMutex     *m_pShareMutex;

            wxString m_ip;
            wxString m_service_port;

            wxDatagramSocket  *m_sock;
            wxIPV4address     m_myaddr;

};


//----------------------------------------------------------------------------------------------------------
//    GRadar Control Dialog Specification
//----------------------------------------------------------------------------------------------------------
class GRadarDialog: public wxDialog
{
      DECLARE_CLASS( GRadarDialog )
                  DECLARE_EVENT_TABLE()
      public:

           GRadarDialog( );

            ~GRadarDialog( );
            void Init();

            bool Create(  wxWindow *parent, gradar_pi *ppi, wxWindowID id = wxID_ANY,
                         const wxString& caption = _("Radar Control"),
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxDefaultSize,
                         long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU );

           void CreateControls();


      private:
            void OnClose(wxCloseEvent& event);
            void OnIdOKClick( wxCommandEvent& event );
            void OnMove( wxMoveEvent& event );
            void OnSize( wxSizeEvent& event );
            void OnUpdateModeClick(wxCommandEvent &event);
            void OnUpdateTransSlider(wxCommandEvent &event);
            void OnOperatingModeClick(wxCommandEvent &event);
            void OnLogModeClick(wxCommandEvent &event);

            wxWindow          *pParent;
            gradar_pi         *pPlugIn;

            // Controls
            wxRadioBox        *pUpdateMode;
            wxSlider          *pTranSlider;
            wxRadioBox        *pOperatingMode;
            wxCheckBox        *pCB_log;
};

#endif



