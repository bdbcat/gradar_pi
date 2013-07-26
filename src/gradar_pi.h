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
#define     PLUGIN_VERSION_MINOR    2

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    8

#ifndef PI
#define PI        3.1415926535897931160E0      /* pi */
#endif

#include "ocpn_plugin.h"
#include "wx/socket.h"


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
    unsigned int      display_meters;
    unsigned int      range_meters;
    unsigned char     gain_level[4];
    unsigned char     sea_clutter[4];
    unsigned char     rain_clutter[4];
    short             dome_offset;
    unsigned char     FTC_mode;
    unsigned char     crosstalk_onoff;
    unsigned short    fills[4];
    unsigned char     dome_speed;
    unsigned char     fillc[7];
    char              line_data;
}radar_scanline_pkt;

typedef struct {
    unsigned int      packet_type;
    unsigned int      len1;
    unsigned int      filli;
    unsigned int      range_meters;
    unsigned char     gain_level[4];
    unsigned char     sea_clutter[4];
    unsigned char     rain_clutter[4];
    short             dome_offset;
    unsigned char     FTC_mode;
    unsigned char     crosstalk_onoff;
    unsigned short    fills[4];
    unsigned char     dome_speed;
    unsigned char     fillc[7];
}radar_response_pkt;

typedef struct {
    unsigned int      packet_type;
    unsigned int      len1;
    unsigned short    parm1;
}rad_ctl_pkt;

typedef struct {
    unsigned int      packet_type;
    unsigned int      len1;
    short             parm1;
}offset_ctl_pkt;

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

typedef struct {
    unsigned int      packet_type;
    unsigned int      len1;
    unsigned char     parm1;
}onebyte_ctl_pkt;

typedef struct {
    unsigned int      packet_type;
    unsigned int      len1;
    unsigned char     parm1;
    unsigned char     parm2;
    unsigned char     parm3;
    unsigned char     parm4;
}fourbyte_ctl_pkt;


#pragma pack(pop)

class interface_descriptor
{
public:
    wxString            ip_dot;
    wxString            netmask_dot;
    long                ip;
    long                netmask;
    int                 cidr;
};

WX_DECLARE_LIST(interface_descriptor, ListOf_interface_descriptor);

//      Utility functions
void grLogMessage(wxString s);
int BuildInterfaceList(ListOf_interface_descriptor &list);

//    Forward definitions
class MulticastRXThread;
class ControlDialog;
class ControlDialogBase;
class RangeDialog;
class RangeDialogBase;
class NoiseDialog;
class NoiseDialogBase;
class DomeDialog;
class DomeDialogBase;

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define GRADAR_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class gradar_pi :  public opencpn_plugin_18
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
    void OnToolbarToolCallback(int id);

    // Other public methods

    void OnControlDialogClose();
    void OnRangeDialogClose();
    void OnRangeDialogClicked();
    void OnNoiseDialogClicked();
    void OnNoiseDialogClose();
    void OnDomeDialogClicked();
    void OnDomeDialogClose();
    void SetUpdateMode(int mode);
    void UpdateDisplayParameters(void);
    void SetOperatingMode(int mode);
    void SetRangeControlMode(int mode);
    void SetManualRange(int mode);

    void SetGainControlMode(int mode);
    void SetGainLevel(int mode);
    void SetSeaClutterMode(int mode);
    void SetSeaClutterLevel(int mode);
    void SetFTCMode(int level);
    void SetRainClutterLevel(int mode);
    void SetCrosstalkMode(int mode);
    void SetDomeOffset(int mode);
    void SetDomeSpeed(int mode);

    void SetControlDialogX(int x){ m_Control_dialog_x = x; }
    void SetControlDialogY(int y){ m_Control_dialog_y = y; }
    void SetControlDialogSizeX(int sx){ m_Control_dialog_sx = sx; }
    void SetControlDialogSizeY(int sy){ m_Control_dialog_sy = sy; }

    void SetRangeDialogX(int x){ m_Range_dialog_x = x; }
    void SetRangeDialogY(int y){ m_Range_dialog_y = y; }
    void SetRangeDialogSizeX(int sx){ m_Range_dialog_sx = sx; }
    void SetRangeDialogSizeY(int sy){ m_Range_dialog_sy = sy; }

    void SetNoiseDialogX(int x){ m_Noise_dialog_x = x; }
    void SetNoiseDialogY(int y){ m_Noise_dialog_y = y; }
    void SetNoiseDialogSizeX(int sx){ m_Noise_dialog_sx = sx; }
    void SetNoiseDialogSizeY(int sy){ m_Noise_dialog_sy = sy; }

    void SetDomeDialogX(int x){ m_Dome_dialog_x = x; }
    void SetDomeDialogY(int y){ m_Dome_dialog_y = y; }
    void SetDomeDialogSizeX(int sx){ m_Dome_dialog_sx = sx; }
    void SetDomeDialogSizeY(int sy){ m_Dome_dialog_sy = sy; }

    bool LoadConfig(void);
    bool SaveConfig(void);



private:
    bool CheckHostAccessible(wxString &hostname);
    void ShowNoAccessMessage(void);

   void SendCommand(unsigned char *ppkt, unsigned int n_bytes);

    void RadarTxOff(void);
    void RadarTxOn(void);
    void UpdateState(void);
    void DoTick(void);
    bool ChangeCheck(void);

    void Select_Range(double range);
    void RenderRadarBufferDirect(PlugIn_ViewPort *vp);
    void RenderRadarOverlaySwept(wxPoint radar_center, double v_scale_ppm, PlugIn_ViewPort *vp);
    void RenderRadarOverlayFull(wxPoint radar_center, double v_scale_ppm, PlugIn_ViewPort *vp);

    void RenderRadarBuffer(unsigned char *buffer, int buffer_line_length, wxDC *pdc,
        int width, int height);
    void draw_blob_dc(wxDC &dc, double angle, double radius, double blob_r, double arc_length,
        double scale, int xoff, int yoff, double ca, double sa);
    void draw_blob_gl(double angle, double radius, double blob_start, double blob_end, double arc_length, double ca, double sa);

    void CacheSetToolbarToolBitmaps(int bm_id_normal, int bm_id_rollover);

    wxString         m_scanner_ip;
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
    wxCriticalSection       m_pThreadCS;

    wxDatagramSocket   *m_out_sock101;
    wxDateTime         m_dt_last_render;

    int               m_sent_bm_id_normal;
    int               m_sent_bm_id_rollover;

    wxBitmap           *m_ptemp_icon;
    wxLogWindow	*m_plogwin;

    int                m_Control_dialog_sx, m_Control_dialog_sy ;
    int                m_Control_dialog_x, m_Control_dialog_y ;

    int                 m_Range_dialog_sx, m_Range_dialog_sy;
    int                 m_Range_dialog_x, m_Range_dialog_y;

    int                 m_Noise_dialog_sx, m_Noise_dialog_sy;
    int                 m_Noise_dialog_x, m_Noise_dialog_y;

    int                 m_Dome_dialog_sx, m_Dome_dialog_sy;
    int                 m_Dome_dialog_x, m_Dome_dialog_y;

    ControlDialog        *m_pControlDialog;
    RangeDialog         *m_pRangeDialog;
    NoiseDialog         *m_pNoiseDialog;
    DomeDialog          *m_pDomeDialog;

    ListOf_interface_descriptor         m_interfaces;
    bool                                m_bscanner_accessible;

};

class MulticastRXThread: public wxThread
{
public:

    MulticastRXThread(wxMutex *pMutex, const wxString &IP_addr, const wxString &service_port);
    ~MulticastRXThread(void);
    virtual ExitCode Entry();

    void OnExit(void);

private:
    void process_buffer(void);

    wxMutex     *m_pShareMutex;

    wxString m_ip;
    wxString m_service_port;
    wxDatagramSocket  *m_sock;
    wxIPV4address     m_myaddr;

};



#endif



