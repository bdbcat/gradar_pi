/******************************************************************************
*
* Project:  OpenCPN
* Purpose:  Garmin Radar Plugin
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
#ifdef _WINDOWS
#include "winsock2.h"
#endif

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#ifdef __WXMSW__
#include "winsock2.h"
#include "Ws2ipdef.h"
#include <iphlpapi.h>
// Link with Iphlpapi.lib
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "ws2_32.lib")
#endif

#include <wx/socket.h>
#include "wx/apptrait.h"
#include <wx/glcanvas.h>
#include "wx/sckaddr.h"
#include "wx/datetime.h"
#include <wx/fileconf.h>

#ifndef __WXMSW__
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#endif

#ifdef __WXMSW__
#include "GL/glu.h"
#endif

#ifdef __WXOSX__
#ifndef ifr_netmask
#  define ifr_netmask ifr_addr
#endif
#endif


#include "gradar_pi.h"
#include "gradardialog.h"
#include "GRadarUI.h"
#include "georef.h"

#include <wx/listimpl.cpp>
WX_DEFINE_LIST(ListOf_interface_descriptor);

#if !defined(NAN)
static const long long lNaN = 0xfff8000000000000;
#define NAN (*(double*)&lNaN)
#endif



bool              g_thread_active;

unsigned char buf[10000];           // The data buffer shared between the RX thread and the main thread

int   g_scan_meters;
int   g_scan_range;
int   g_scan_gain_level;
int   g_scan_gain_mode;
int   g_scan_sea_clutter_level;
int   g_scan_sea_clutter_mode;
int   g_scan_rain_clutter_level;
int   g_scan_dome_offset;
int   g_scan_FTC_mode;
int   g_scan_crosstalk_mode;
int   g_scan_timed_transmit_mode;
int   g_scan_timed_transmit_standby;
int   g_scan_timed_transmit_transmit;
int   g_scan_dome_speed;


double g_hdt;
double            g_current_headings[180]= {0.0};
double            g_static_headings[180] = {0.0};

int   g_scan_packets_per_tick;
int   g_prev_radar_state;
int   g_sweep_count;
int   g_radar_state;
int   g_warmup_timer;
int   g_last_warmup_timer;
int   g_scanner_state;
int   g_pseudo_tick;



int               g_max_scan_length_bytes;
int               g_current_scan_length_bytes;
unsigned char     *g_scan_buf;
double            g_selected_range;

unsigned char     *g_static_buf;
int               g_static_max_scan_length_bytes;
int               g_static_scan_length_bytes;
int               g_static_scan_meters;



double available_ranges[] = {
     0.125,
     0.25,
     0.5,
     0.75,
     1.0,
     1.5,
     2.0,
     3.0,
     4.0,
     6.0,
     8.0,
     12.0,
     16.0,
     24.0,
     36.0,
     48.0
};
int   n_ranges = 16;



int   g_updatemode;           //0:realtime,  1:full screen
wxTextCtrl        *plogtc;
wxDialog          *plogcontainer;





int   gps_watchdog_timeout_ticks = 10;

bool test(void)
{
#ifdef __WXMSW__

#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

     /* Declare and initialize variables */

     DWORD dwSize = 0;
     DWORD dwRetVal = 0;

     unsigned int i = 0;

     // Set the flags to pass to GetAdaptersAddresses
     ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

     // default to unspecified address family (both)
     ULONG family = AF_UNSPEC;

     LPVOID lpMsgBuf = NULL;

     PIP_ADAPTER_ADDRESSES pAddresses = NULL;
     ULONG outBufLen = 0;
     ULONG Iterations = 0;

     PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
     PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
     PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
     PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
     IP_ADAPTER_DNS_SERVER_ADDRESS *pDnServer = NULL;
     IP_ADAPTER_PREFIX *pPrefix = NULL;


     outBufLen = WORKING_BUFFER_SIZE;
     family = AF_INET;

     do {
          pAddresses = (IP_ADAPTER_ADDRESSES *) MALLOC(outBufLen);
          if (pAddresses == NULL) {
               printf
                    ("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
               exit(1);
          }

          dwRetVal =
               GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);

          if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
               FREE(pAddresses);
               pAddresses = NULL;
          } else {
               break;
          }

          Iterations++;

     } while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (Iterations < MAX_TRIES));

     if (dwRetVal == NO_ERROR) {
          // If successful, output some information from the data we received
          pCurrAddresses = pAddresses;
          while (pCurrAddresses) {
               printf("\tLength of the IP_ADAPTER_ADDRESS struct: %ld\n",
                    pCurrAddresses->Length);
               printf("\tIfIndex (IPv4 interface): %u\n", pCurrAddresses->IfIndex);
               printf("\tAdapter name: %s\n", pCurrAddresses->AdapterName);

               pUnicast = pCurrAddresses->FirstUnicastAddress;
               if (pUnicast != NULL) {
                    for (i = 0; pUnicast != NULL; i++){
                         SOCKET_ADDRESS sa = pUnicast->Address;
                         LPSOCKADDR pska = sa.lpSockaddr;
                         struct sockaddr_in *their_inaddr_ptr = (struct sockaddr_in *)pska;
                         char *p = inet_ntoa(their_inaddr_ptr->sin_addr);

                         pUnicast = pUnicast->Next;
                    }
                    printf("\tNumber of Unicast Addresses: %d\n", i);
               } else
                    printf("\tNo Unicast Addresses\n");


          }
     }
     //http://stackoverflow.com/questions/4139405/how-to-know-ip-address-for-interfaces-in-c

#endif
     return true;
}


int BuildInterfaceList(ListOf_interface_descriptor &list)
{

#ifdef __WXMSW__
     WSADATA WinsockData;
     if (WSAStartup(MAKEWORD(2, 2), &WinsockData) != 0){
          grLogMessage(_T("WSAStartup failed, no network interfaces detectable\n"));
          WSACleanup();
          return 1;
     }


     SOCKET sd = WSASocket(AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
     if (sd == SOCKET_ERROR) {
          grLogMessage(_T("WSASocket failed, no network interfaces detectable\n"));
          WSACleanup();
          return 2;
     }

     INTERFACE_INFO InterfaceList[20];
     unsigned long nBytesReturned;
     if (WSAIoctl(sd, SIO_GET_INTERFACE_LIST, 0, 0, &InterfaceList,
          sizeof(InterfaceList), &nBytesReturned, 0, 0) == SOCKET_ERROR) {
               grLogMessage(_T("WSAIoctl failed, no network interfaces detectable\n"));
               WSACleanup();
               return 3;
     }

     int nNumInterfaces = nBytesReturned / sizeof(INTERFACE_INFO);
     for (int i = 0; i < nNumInterfaces; ++i) {
          interface_descriptor *pid = new interface_descriptor;

          //      The unicast address
          sockaddr_in *pAddress;
          pAddress = (sockaddr_in *) & (InterfaceList[i].iiAddress);
          char *p = inet_ntoa(pAddress->sin_addr);
          pid->ip_dot = wxString(p, wxConvUTF8);
          pid->ip = inet_addr(p); //ip_addr.s_addr;


          //        pAddress = (sockaddr_in *) & (InterfaceList[i].iiBroadcastAddress);
          //        cout << " has bcast " << inet_ntoa(pAddress->sin_addr);

          //      The netmask
          pAddress = (sockaddr_in *) & (InterfaceList[i].iiNetmask);
          char *mask = inet_ntoa(pAddress->sin_addr);
          pid->netmask_dot = wxString(mask, wxConvUTF8);
          pid->netmask = inet_addr(mask);//tmp.s_addr;

          // Calculate the mask in cidr notation
          unsigned long b = inet_addr("255.255.255.255" );
          unsigned long c = pid->netmask ^ b;
          int acc = 0;
          while(c){
               acc++;
               c <<= 1;
          }
          pid->cidr = 32-acc;


          list.Append(pid);
          //        cout << " Iface is ";
          //        u_long nFlags = InterfaceList[i].iiFlags;
          //        if (nFlags & IFF_UP) cout << "up";
          //        else                 cout << "down";
          //        if (nFlags & IFF_POINTTOPOINT) cout << ", is point-to-point";
          //        if (nFlags & IFF_LOOPBACK)     cout << ", is a loopback iface";
          //        cout << ", and can do: ";
          //        if (nFlags & IFF_BROADCAST) cout << "bcast ";
          //        if (nFlags & IFF_MULTICAST) cout << "multicast ";
          //        cout << endl;
     }

     WSACleanup();
     return 0;
#endif

#ifdef __WXGTK__

#define INT_TO_ADDR(_addr) \
     (_addr & 0xFF), \
     (_addr >> 8 & 0xFF), \
     (_addr >> 16 & 0xFF), \
     (_addr >> 24 & 0xFF)

     struct ifconf ifc;
     struct ifreq ifr[20];
     int sd, ifc_num, addr, mask, i;

     /* Create a socket so we can use ioctl on the file
     * descriptor to retrieve the interface info.
     */

     sd = socket(PF_INET, SOCK_DGRAM, 0);
     if( sd <= 0)
          grLogMessage(_T("socket failed, no network interfaces detectable\n"));

     if (sd > 0)
     {
          grLogMessage(_T("ioctl test socket successful\n"));

          ifc.ifc_len = sizeof(ifr);
          ifc.ifc_ifcu.ifcu_buf = (caddr_t)ifr;

          if (ioctl(sd, SIOCGIFCONF, &ifc) == 0)
          {
               ifc_num = ifc.ifc_len / sizeof(struct ifreq);

               for (i = 0; i < ifc_num; ++i)
               {
                    if (ifr[i].ifr_addr.sa_family != AF_INET)
                    {
                         continue;
                    }

                    interface_descriptor *pid = new interface_descriptor;

                    /* display the interface name */
                    //                printf("%d) interface: %s\n", i+1, ifr[i].ifr_name);

                    /* Retrieve the IP address, broadcast address, and subnet mask. */
                    if (ioctl(sd, SIOCGIFADDR, &ifr[i]) == 0)
                    {
                         addr = ((struct sockaddr_in *)(&ifr[i].ifr_addr))->sin_addr.s_addr;
                         //                    printf("%d) address: %d.%d.%d.%d\n", i+1, INT_TO_ADDR(addr));
                         pid->ip = addr;
                         wxString dot;
                         dot.Printf(_T("%d.%d.%d.%d"), INT_TO_ADDR(addr) );
                         pid->ip_dot = dot;
                    }

                    //                if (ioctl(sd, SIOCGIFBRDADDR, &ifr[i]) == 0)
                    //                {
                    //                    bcast = ((struct sockaddr_in *)(&ifr[i].ifr_broadaddr))->sin_addr.s_addr;
                    //                    printf("%d) broadcast: %d.%d.%d.%d\n", i+1, INT_TO_ADDR(bcast));
                    //                }

                    if (ioctl(sd, SIOCGIFNETMASK, &ifr[i]) == 0)
                    {
                         mask = ((struct sockaddr_in *)(&ifr[i].ifr_netmask))->sin_addr.s_addr;
                         //                    printf("%d) netmask: %d.%d.%d.%d\n", i+1, INT_TO_ADDR(mask));
                         pid->netmask = mask;
                         wxString dot;
                         dot.Printf(_T("%d.%d.%d.%d"), INT_TO_ADDR(mask) );
                         pid->netmask_dot = dot;

                         // Calculate the mask in cidr notation
                         unsigned long b = inet_addr("255.255.255.255" );
                         unsigned long c = pid->netmask ^ b;
                         int acc = 0;
                         while(c){
                              acc++;
                              c <<= 1;
                         }
                         pid->cidr = 32-acc;
                    }

                    list.Append(pid);
               }
          }

          close(sd);
     }

     return 0;

#endif


#ifdef __WXOSX__
#define INT_TO_ADDR(_addr) \
     (_addr & 0xFF), \
     (_addr >> 8 & 0xFF), \
     (_addr >> 16 & 0xFF), \
     (_addr >> 24 & 0xFF)

     int sd;
     int addr, mask, i;

     /* Create a socket so we can use ioctl on the file
     * descriptor to retrieve the interface info.
     */

     sd = socket(PF_INET, SOCK_DGRAM, 0);
     if( sd <= 0)
          grLogMessage(_T("socket failed, no network interfaces detectable\n"));

     if (sd > 0)
     {
          grLogMessage(_T("ioctl test socket successful\n"));

          struct ifconf conf;
          char data[4096];
          struct ifreq *ifr;
          conf.ifc_len = sizeof(data);
          conf.ifc_buf = (caddr_t) data;
          if (ioctl(sd,SIOCGIFCONF,&conf) >=0) {
               i = 0;
               ifr = (struct ifreq*)data;
               while ((char*)ifr < data+conf.ifc_len) {

                    switch (ifr->ifr_addr.sa_family) {
                    case AF_INET:
                         interface_descriptor *pid = new interface_descriptor;

                         /* Retrieve the IP address, broadcast address, and subnet mask. */
                         if (ioctl(sd, SIOCGIFADDR, ifr) == 0)
                         {
                              addr = ((struct sockaddr_in *)(&ifr->ifr_addr))->sin_addr.s_addr;
                              pid->ip = addr;
                              wxString dot;
                              dot.Printf(_T("%d.%d.%d.%d"), INT_TO_ADDR(addr) );
                              pid->ip_dot = dot;
                         }

                         if (ioctl(sd, SIOCGIFNETMASK, ifr) == 0)
                         {
                              mask = ((struct sockaddr_in *)(&ifr->ifr_netmask))->sin_addr.s_addr;
                              pid->netmask = mask;
                              wxString dot;
                              dot.Printf(_T("%d.%d.%d.%d"), INT_TO_ADDR(mask) );
                              pid->netmask_dot = dot;

                              // Calculate the mask in cidr notation
                              unsigned long b = inet_addr("255.255.255.255" );
                              unsigned long c = pid->netmask ^ b;
                              int acc = 0;
                              while(c){
                                   acc++;
                                   c <<= 1;
                              }
                              pid->cidr = acc-32;//32-acc;
                         }

                         list.Append(pid);
                         break;
                    }
                    ++i;
                    ifr = (struct ifreq*)((char*)ifr +_SIZEOF_ADDR_IFREQ(*ifr));
               }
          }
          close(sd);
     }

     return 0;

#endif
}



// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
     return (opencpn_plugin *) new gradar_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
     delete p;
}


int nseq;
bool b_enable_log;

//	Private logging functions
void grLogMessage(wxString s)
{
     if(b_enable_log && plogtc && plogcontainer) {
          wxString seq;
          seq.Printf(_T("%6d: "), nseq++);

          plogtc->AppendText(seq);

          plogtc->AppendText(s);
          plogcontainer->Show();
     }
}


//---------------------------------------------------------------------------------------------------------
//
//    GRadar PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"
//#include "default_pi.xpm"
#include "icons.cpp"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

gradar_pi::gradar_pi(void *ppimgr)
     :  wxTimer( this ), opencpn_plugin_18(ppimgr)
{
     // Create the PlugIn icons
     initialize_images();
     m_pdeficon = new wxBitmap(*_img_radar_blank);
}

int gradar_pi::Init(void)
{
     m_hdm = NAN;
     g_hdt = NAN;
     m_var = NAN;
     mPriHeadingM = 99;
     mPriHeadingT = 99;
     mPriVar = 99;
     mHDx_Watchdog = 2;
     mHDT_Watchdog = 2;
     mVar_Watchdog = 2;
     m_guardzone_mode= 0;
     m_partial_arc_mode = 0;
     m_guardzone_transparency = 0.8;
     m_sentry_alarm_sensitivity = 5;
     m_zonealarm = 0;

     m_inner_range = 0;
     m_outer_range = 0;
     m_arc_start_angle = 0;
     m_arc_end_angle = 0;

     m_pControlDialog = NULL;
     m_pRangeDialog = NULL;
     m_pNoiseDialog= NULL;
     m_pDomeDialog = NULL;
     m_pSentryDialog = NULL;
     m_pSentryAlarmDialog = NULL;

     m_manual_range = 0;
     g_updatemode = 0;
     g_radar_state = RADAR_OFF;
     g_warmup_timer = 1000;
     g_scanner_state = 0;
     g_scan_buf = 0;
     g_static_buf = 0;
     g_static_max_scan_length_bytes = 0;
     g_max_scan_length_bytes = 0;
     m_overlay_transparency = .50;
     g_sweep_count = 0;
     m_bmaster = true;
     m_slave_display_mode = SLAVE_DISPLAY_ON;
     m_ptemp_icon = NULL;
     m_sent_bm_id_normal = -1;
     m_sent_bm_id_rollover =  -1;

     g_prev_radar_state = -2;
     m_prev_scanner_state = -2;

     plogcontainer = new wxDialog(NULL, -1, _T("gradar_pi Log"), wxPoint(0,0), wxSize(600,400),
          wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxDIALOG_NO_PARENT | wxSTAY_ON_TOP );

     plogtc = new wxTextCtrl(plogcontainer, -1, _T(""), wxPoint(0,0), wxSize(600,400), wxTE_MULTILINE );

     grLogMessage(_T("gradar_pi log opened\n"));

     AddLocaleCatalog( _T("opencpn-gradar_pi") );

     // Set some default private member parameters
     m_Control_dialog_x = 0;
     m_Control_dialog_y= 0;
     m_Control_dialog_sx = 200;
     m_Control_dialog_sy = 200;

     ::wxDisplaySize(&m_display_width, &m_display_height);

     SetScanColor( wxColour(255, 0, 0) );

     //    Get a pointer to the opencpn configuration object
     m_pconfig = GetOCPNConfigObject();

     //    And load the configuration items
     LoadConfig();

     //  Get a list of available network interfaces and associated netmasks
     BuildInterfaceList(m_interfaces);

     if(!m_interfaces.GetCount()) {
          grLogMessage(_T("No network interfaces found.\n"));
     }

     //  Show the interfaces in the log
     for ( ListOf_interface_descriptor::Node *node = m_interfaces.GetFirst(); node; node = node->GetNext() )
     {
          interface_descriptor *current = node->GetData();

          wxString msg(_T("Found network interface: "));
          msg += current->ip_dot;
          wxString cidr;
          cidr.Printf(_T("/%d\n"), current->cidr);
          msg += cidr;
          grLogMessage(msg);
     }

     //  Determine if the standard scanner ip is accessible from this computer,
     //  using any available interface.
     //  Note:  The operating system routing table lookup will do something like this
     //         when a UDP message is to be sent.
     m_scanner_ip = _T("172.16.2.0");
     m_bscanner_accessible = CheckHostAccessible( m_scanner_ip );

     wxString msga(_T("Scanner at "));
     msga += m_scanner_ip;

     if(m_bscanner_accessible)
          msga += _T(" is accessible.\n");
     else
          msga += _T(" is <<NOT>> accessible for master control.\n");
     grLogMessage(msga);

     if(!m_bscanner_accessible)
          m_bmaster = false;

     // Get a pointer to the opencpn display canvas, to use as a parent for the UI dialog
     m_parent_window = GetOCPNCanvasWindow();

     //    This PlugIn needs a toolbar icon
     {
          m_tool_id  = InsertPlugInTool(_T(""), _img_radar_red, _img_radar_red, wxITEM_NORMAL,
               _T("GRadar"), _T(""), NULL,
               GRADAR_TOOL_POSITION, 0, this);

          CacheSetToolbarToolBitmaps( BM_ID_RED, BM_ID_BLANK);
     }

     wxIPV4address dummy;                // Do this to initialize the wxSocketBase tables

     //    Create the control socket for the Radar
     wxIPV4address addr101;;
     addr101.AnyAddress();
     addr101.Service(_T("50101"));     // does this matter?
     m_out_sock101 = new wxDatagramSocket(addr101, wxSOCKET_REUSEADDR | wxSOCKET_NOWAIT);

     //    Create the thread for Multicast radar data reception
     m_pmcrxt = new MulticastRXThread(&m_mutex, _T("239.254.2.0"),_T("50100"));
     if( m_pmcrxt->Run() != wxTHREAD_NO_ERROR ){
          delete m_pmcrxt;
          m_pmcrxt = NULL;
     }

     g_radar_state = RADAR_ACTIVATE;

     m_pmenu = new wxMenu();            // this is a dummy menu
     // required by Windows as parent to item created
     wxMenuItem *pmi = new wxMenuItem(m_pmenu, -1, _("Radar Control Garmin"));
     int miid = AddCanvasContextMenuItem(pmi, this );
     SetCanvasContextMenuItemViz(miid, true);
     m_packet_watch = 0;

     Start( 1000, wxTIMER_CONTINUOUS );

     return (WANTS_DYNAMIC_OPENGL_OVERLAY_CALLBACK |
          WANTS_OPENGL_OVERLAY_CALLBACK |
          WANTS_OVERLAY_CALLBACK     |
          WANTS_CURSOR_LATLON        |
          WANTS_TOOLBAR_CALLBACK     |
          INSTALLS_TOOLBAR_TOOL      |
          INSTALLS_CONTEXTMENU_ITEMS |
          WANTS_CONFIG               |
          WANTS_NMEA_SENTENCES       |
          WANTS_NMEA_EVENTS
          );
}

bool gradar_pi::DeInit(void)
{
     SaveConfig();

     SetTimedTransmitMode(0);
     RadarTxOff();
     {
          wxCriticalSectionLocker enter( m_pThreadCS );
          if( m_pmcrxt ) {
               if( m_pmcrxt->Delete() != wxTHREAD_NO_ERROR ){}
          }
     }
     int max_timeout = 5;
     int timeout = max_timeout;        // deadman

     while(g_thread_active && timeout > 0) {
          wxSleep(1);
          timeout--;
     }

     if(plogcontainer != NULL){
          plogcontainer->Hide();
          plogcontainer->Close();
          delete plogcontainer;
          plogcontainer = NULL;
     }

     if(m_pControlDialog != NULL){
          m_pControlDialog->Hide();
          m_pControlDialog->Close();
          delete m_pControlDialog;
          m_pControlDialog = NULL;
     }

     if(m_pRangeDialog != NULL){
          m_pRangeDialog->Hide();
          m_pRangeDialog->Close();
          delete m_pRangeDialog;
          m_pRangeDialog = NULL;
     }

     if(m_pNoiseDialog != NULL){
          m_pNoiseDialog->Hide();
          m_pNoiseDialog->Close();
          delete m_pNoiseDialog;
          m_pNoiseDialog = NULL;
     }

     if(m_pDomeDialog != NULL){
          m_pDomeDialog->Hide();
          m_pDomeDialog->Close();
          delete m_pDomeDialog;
          m_pDomeDialog = NULL;
     }

     if(m_pSentryDialog != NULL){
          m_pSentryDialog->Hide();
          m_pSentryDialog->Close();
          delete m_pSentryDialog;
          m_pSentryDialog = NULL;
     }

     if(m_pSentryAlarmDialog != NULL){
          m_pSentryAlarmDialog->Hide();
          m_pSentryAlarmDialog->Close();
          delete m_pSentryAlarmDialog;
          m_pSentryAlarmDialog = NULL;
     }

     return true;
}

int gradar_pi::GetAPIVersionMajor()
{
     return MY_API_VERSION_MAJOR;
}

int gradar_pi::GetAPIVersionMinor()
{
     return MY_API_VERSION_MINOR;
}

int gradar_pi::GetPlugInVersionMajor()
{
     return PLUGIN_VERSION_MAJOR;
}

int gradar_pi::GetPlugInVersionMinor()
{
     return PLUGIN_VERSION_MINOR;
}

wxBitmap *gradar_pi::GetPlugInBitmap()
{
     return m_pdeficon;
}

wxString gradar_pi::GetCommonName()
{
     return _T("GRadar");
}

wxString gradar_pi::GetShortDescription()
{
     return _("Garmin Radar PlugIn for OpenCPN");
}

wxString gradar_pi::GetLongDescription()
{
     return _("Garmin Radar PlugIn for OpenCPN\n");
}

bool gradar_pi::CheckHostAccessible(wxString &hostname)
{
     bool bret = false;
     long host_ip = inet_addr(hostname.mb_str());

     for ( ListOf_interface_descriptor::Node *node = m_interfaces.GetFirst(); node; node = node->GetNext() )
     {
          interface_descriptor *current = node->GetData();

          if((host_ip & current->netmask) == (current->ip & current->netmask)){
               bret = true;
               break;
          }
     }
     return bret;
}

void gradar_pi::SetDefaults(void)
{
     // If the config somehow says NOT to show the icon, override it so the user gets good feedback
     if(!m_bShowIcon) {
          m_bShowIcon = true;

          m_tool_id  = InsertPlugInTool(_T(""), _img_radar_red, _img_radar_red, wxITEM_CHECK,
               _T("GRadar"), _T(""), NULL,
               GRADAR_TOOL_POSITION, 0, this);
     }
}

int gradar_pi::GetToolbarToolCount(void)
{
     return 1;
}

void gradar_pi::OnContextMenuItemCallback(int id)
{
     if(NULL == m_pControlDialog) {
          m_pControlDialog = new ControlDialog( this, m_parent_window);
          m_pControlDialog->SetSize(m_Control_dialog_x, m_Control_dialog_y,
               m_Control_dialog_sx, m_Control_dialog_sy);
          m_pControlDialog->Hide();
     }
     if(m_pControlDialog->IsShown()) {
          m_pControlDialog->Hide();
     } else {
          m_pControlDialog->Show();
          m_pControlDialog->SetSize(m_Control_dialog_x, m_Control_dialog_y,
               m_Control_dialog_sx, m_Control_dialog_sy);
     }

     if (NULL == m_pRangeDialog) {
          m_pRangeDialog = new RangeDialog(this, m_parent_window);
          m_pRangeDialog->SetSize(m_Range_dialog_x, m_Range_dialog_y,
               m_Range_dialog_sx, m_Range_dialog_sy);
          m_pRangeDialog->Hide();
     }
     if(m_pRangeDialog->IsShown()) m_pRangeDialog->Hide();

     if (NULL == m_pNoiseDialog) {
          m_pNoiseDialog = new NoiseDialog(this, m_parent_window);
          m_pNoiseDialog->SetSize(m_Noise_dialog_x, m_Noise_dialog_y,
               m_Noise_dialog_sx, m_Noise_dialog_sy);
          m_pNoiseDialog->Hide();
     }
     if(m_pNoiseDialog->IsShown()) m_pNoiseDialog->Hide();

     if (NULL == m_pDomeDialog) {
          m_pDomeDialog = new DomeDialog(this, m_parent_window);
          m_pDomeDialog->SetSize(m_Dome_dialog_x, m_Dome_dialog_y,
               m_Dome_dialog_sx, m_Dome_dialog_sy);
          m_pDomeDialog->Hide();
     }
     if(m_pDomeDialog->IsShown()) m_pDomeDialog->Hide();

     if (NULL == m_pSentryDialog) {
          m_pSentryDialog = new SentryDialog(this, m_parent_window);
          m_pSentryDialog->SetSize(m_Sentry_dialog_x, m_Sentry_dialog_y,
               m_Sentry_dialog_sx, m_Sentry_dialog_sy);
          m_pSentryDialog->Hide();
     }
     if(m_pSentryDialog->IsShown()) m_pSentryDialog->Hide();
}

void gradar_pi::OnControlDialogClose()
{
     if(m_pControlDialog->IsShown())
          m_pControlDialog->Hide();
     SaveConfig();
}

void gradar_pi::OnRangeDialogClicked()
{
     if(m_pRangeDialog->IsShown()) {
          m_pRangeDialog->Hide();
     } else {
          m_pRangeDialog->SetSize(m_Range_dialog_x, m_Range_dialog_y,
               m_Range_dialog_sx, m_Range_dialog_sy);
          m_pRangeDialog->RangeDialogShow();
     }
}

void gradar_pi::OnRangeDialogClose()
{
     if(m_pRangeDialog->IsShown())
          m_pRangeDialog->Hide();
     SaveConfig();
}

void gradar_pi::OnNoiseDialogClicked()
{
     if(m_pNoiseDialog->IsShown()) {
          m_pNoiseDialog->Hide();
     } else {
          m_pNoiseDialog->SetSize(m_Noise_dialog_x, m_Noise_dialog_y,
               m_Noise_dialog_sx, m_Noise_dialog_sy);
          m_pNoiseDialog->NoiseDialogShow();
     }
}

void gradar_pi::OnNoiseDialogClose()
{
     if(m_pNoiseDialog->IsShown())
          m_pNoiseDialog->Hide();
     SaveConfig();
}

void gradar_pi::OnDomeDialogClicked()
{
     if(m_pDomeDialog->IsShown()) {
          m_pDomeDialog->Hide();
     } else {
          m_pDomeDialog->SetSize(m_Dome_dialog_x, m_Dome_dialog_y,
               m_Dome_dialog_sx, m_Dome_dialog_sy);
          m_pDomeDialog->DomeDialogShow();
     }
}

void gradar_pi::OnDomeDialogClose()
{
     if(m_pDomeDialog->IsShown())
          m_pDomeDialog->Hide();
     SaveConfig();
}

void gradar_pi::OnSentryDialogClicked()
{
     if(m_pSentryDialog->IsShown()) {
          m_pSentryDialog->Hide();
     } else {
          m_pSentryDialog->SetSize(m_Sentry_dialog_x, m_Sentry_dialog_y,
               m_Sentry_dialog_sx, m_Sentry_dialog_sy);
          m_pSentryDialog->SentryDialogShow();
     }
}

void gradar_pi::OnSentryDialogClose()
{
     if(m_pSentryDialog->IsShown())
          m_pSentryDialog->Hide();
     SaveConfig();
}

void gradar_pi::OnSentryAlarmDialogClose()
{
     if(m_pSentryAlarmDialog->IsShown())
          m_pSentryAlarmDialog->Hide();
     m_balarm_silence = false;
     SaveConfig();
}

void gradar_pi::OnToolbarToolCallback(int id)
{
     if(m_bmaster){
          switch(g_radar_state) {

          case RADAR_TX_ACTIVE:
               RadarTxOff();
               break;

          case RADAR_STANDBY:
               RadarTxOn();
               break;

          default:
               break;
          }
     }else{
          switch(m_slave_display_mode) {

          case SLAVE_DISPLAY_ON:
               m_slave_display_mode = SLAVE_DISPLAY_OFF;
               break;

          case SLAVE_DISPLAY_OFF:
               m_slave_display_mode = SLAVE_DISPLAY_ON;
               break;

          default:
               break;
          }
     }
}

void gradar_pi::Notify()
{
     m_packet_watch ++;
     if(m_packet_watch >= 6){

          //    If in slave mode, and no data appears to be coming in,
          //    switch to ACTIVATE mode
          if((g_scan_packets_per_tick == 0) && !m_bmaster) {

               free (g_scan_buf);        // empty the buffer
               g_scan_buf = 0;

               if( RADAR_ACTIVATE != g_radar_state )
                    grLogMessage( _("No scanner activity, reverting to search\n") );

               g_radar_state = RADAR_ACTIVATE;
          }
          g_scan_packets_per_tick = 0;
          m_packet_watch = 0;
     }

     mHDT_Watchdog--;
     if( mHDT_Watchdog <= 0 ) {
          g_hdt = 0;
          mPriHeadingT = 99;
          mHDT_Watchdog = 0;
     }

     mHDx_Watchdog--;
     if( mHDx_Watchdog <= 0 ) {
          m_hdm = NAN;
          mPriHeadingM = 99;
          mHDx_Watchdog = 0;
     }

     mVar_Watchdog--;
     if( mVar_Watchdog <= 0 ) {
          m_var = NAN;
          mPriVar = 99;
          mVar_Watchdog = 0;
     }
}

bool gradar_pi::ChangeCheck()
{
     bool change = false;

     if(m_savescan_range != g_scan_range){
          m_savescan_range = g_scan_range;
          for (int i= 0 ; i < n_ranges ; ++i) {
               if((available_ranges[i] > (g_scan_range-20)/1852.0)&&(available_ranges[i] < (g_scan_range+20)/1852.0)){
                    m_manual_range = i;
                    break;
               }
          }
          change = true;
     }
     if(m_savescan_gain_mode != g_scan_gain_mode){
          m_savescan_gain_mode = g_scan_gain_mode;
          change = true;
     }
     if(m_savescan_gain_level != g_scan_gain_level){
          m_savescan_gain_level = g_scan_gain_level;
          change = true;
     }
     if(m_savescan_sea_clutter_mode != g_scan_sea_clutter_mode){
          m_savescan_sea_clutter_mode = g_scan_sea_clutter_mode;
          change= true;
     }
     if(m_savescan_sea_clutter_level != g_scan_sea_clutter_level){
          m_savescan_sea_clutter_level = g_scan_sea_clutter_level;
          change = true;
     }
     if(m_savescan_FTC_mode != g_scan_FTC_mode){
          m_savescan_FTC_mode = g_scan_FTC_mode;
          change = true;
     }
     if(m_savescan_rain_clutter_level != g_scan_rain_clutter_level){
          m_savescan_rain_clutter_level = g_scan_rain_clutter_level;
          change = true;
     }
     if(m_savescan_dome_offset != g_scan_dome_offset){
          m_savescan_dome_offset = g_scan_dome_offset;
          change = true;
     }
     if(m_savescan_dome_speed != g_scan_dome_speed){
          m_savescan_dome_speed = g_scan_dome_speed;
          change = true;
     }
     if(m_savescan_timed_transmit_mode != g_scan_timed_transmit_mode){
          m_savescan_timed_transmit_mode = g_scan_timed_transmit_mode;
          change = true;
     }
     if(m_savescan_timed_transmit_standby != g_scan_timed_transmit_standby){
          m_savescan_timed_transmit_standby = g_scan_timed_transmit_standby;
          change = true;
     }
     if(m_savescan_timed_transmit_transmit != g_scan_timed_transmit_transmit){
          m_savescan_timed_transmit_transmit = g_scan_timed_transmit_transmit;
          change = true;
     }

     return change;
}


bool gradar_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
     m_bshown_dc_message = 0;             // show message box if RenderOverlay() is called again

     UpdateState();

     if(ChangeCheck()){

          if(m_pRangeDialog)
               if(m_pRangeDialog->IsShown())m_pRangeDialog->RangeDialogShow();

          if(m_pNoiseDialog)
               if(m_pNoiseDialog->IsShown())m_pNoiseDialog->NoiseDialogShow();

          if(m_pDomeDialog)
               if(m_pDomeDialog->IsShown())m_pDomeDialog->DomeDialogShow();

          if(m_pSentryDialog)
               if(m_pSentryDialog->IsShown())m_pSentryDialog->SentryDialogShow();
     }

     if(((g_radar_state == RADAR_TX_ACTIVE)||(g_radar_state == RADAR_TT_TX_ACTIVE)) &&
         (!(!m_bmaster && (m_slave_display_mode == SLAVE_DISPLAY_OFF)))) {

          double max_distance = 0;
          wxPoint radar_center(vp->pix_width/2, vp->pix_height/2);
          if(m_bpos_set)
               GetCanvasPixLL(vp, &radar_center, m_ownship_lat, m_ownship_lon);

          double req_range;
          int range_index = 0;
          if  (m_range_control_mode == 1){
               range_index = m_manual_range;
               req_range = available_ranges[ m_manual_range ];

          }else{

               //   If ownship position is not valid, use the ViewPort center

               if(m_bpos_set) {

                    // Calculate the "optimum" radar range setting

                    // first calculate the max distance from ownship to 4 corners of the viewport
                    double lat, lon;
                    GetCanvasLLPix( vp, wxPoint(0, 0), &lat, &lon);
                    max_distance = wxMax(max_distance, DistGreatCircle(lat, lon, m_ownship_lat, m_ownship_lon));

                    GetCanvasLLPix( vp, wxPoint(0, vp->pix_height), &lat, &lon);
                    max_distance = wxMax(max_distance, DistGreatCircle(lat, lon, m_ownship_lat, m_ownship_lon));

                    GetCanvasLLPix( vp, wxPoint(vp->pix_width, vp->pix_height), &lat, &lon);
                    max_distance = wxMax(max_distance, DistGreatCircle(lat, lon, m_ownship_lat, m_ownship_lon));

                    GetCanvasLLPix( vp, wxPoint(vp->pix_width, 0), &lat, &lon);
                    max_distance = wxMax(max_distance, DistGreatCircle(lat, lon, m_ownship_lat, m_ownship_lon));
               } else {
                    double max_pix = sqrt((double)((vp->pix_width * vp->pix_width) + (vp->pix_height * vp->pix_height))) / 2;
                    max_distance = (max_pix / vp->view_scale_ppm) / 1852.0;
               }

               // now look in the list of available ranges to find the smallest range
               // that is larger than the required range

               range_index  = n_ranges-1;
               req_range = available_ranges[n_ranges-1];
               for (int i= 0 ; i < n_ranges ; i++) {
                    if(available_ranges[i] >= max_distance) {
                         req_range = available_ranges[i];
                         range_index = i;
                         break;
                    }
               }
          }

          // do we need a switch ?
          if(m_bmaster){

               if(g_selected_range != req_range) {
                    g_selected_range = req_range;
                    m_manual_range = range_index;
                    Select_Range(g_selected_range);
                    if(m_pRangeDialog)
                         if(m_pRangeDialog->IsShown())m_pRangeDialog->RangeDialogShow();
               }
          }

          //    Calculate drawing scale factor
          double ulat, llat, ulon, llon, wlat, wlon, clat, clon, brng_x, brng_y, dist_x, dist_y;

          GetCanvasLLPix( vp, wxPoint(0, (vp->pix_height)/2), &clat, &clon);
          GetCanvasLLPix( vp, wxPoint(vp->pix_width, (vp->pix_height)/2), &wlat, &wlon);
          GetCanvasLLPix( vp, wxPoint((vp->pix_width)/2, vp->pix_height), &ulat, &ulon);
          GetCanvasLLPix( vp, wxPoint((vp->pix_width)/2, 0), &llat, &llon);

          DistanceBearingMercator(clat, clon, wlat, wlon, &brng_x, &dist_x);
          DistanceBearingMercator(llat, llon, ulat, ulon, &brng_y, &dist_y);

          double h_scale_ppm = 1.0;
          double v_scale_ppm = 1.0;

          if(dist_x > 0.)
               h_scale_ppm = ((vp->pix_width))/(dist_x * 1852.);

          if(dist_y > 0.)
               v_scale_ppm = ((vp->pix_height) )/(dist_y * 1852.);

          RenderRadarOverlay(radar_center, h_scale_ppm, v_scale_ppm, vp);

          if(m_guardzone_mode == 1)
               RenderRadarGuardZone(radar_center, h_scale_ppm , v_scale_ppm, vp);

          return true;
     } else {
          return false;
     }
}

void gradar_pi::RenderRadarOverlay(wxPoint radar_center,double h_scale_ppm, double v_scale_ppm, PlugIn_ViewPort *vp)
{
     double rotation = vp->rotation * 180.0/PI;
     glPushAttrib(GL_COLOR_BUFFER_BIT | GL_LINE_BIT | GL_HINT_BIT);      //Save state
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     glPushMatrix();

     glTranslated( radar_center.x, radar_center.y, 0);

     if(g_updatemode == 0) {
          // swept scan  scaling...each scan holds 4 radials
          double bytes_per_meter = (g_current_scan_length_bytes / 4) / (double)g_scan_meters;
          double h_scale_factor = h_scale_ppm / bytes_per_meter;
          double v_scale_factor = v_scale_ppm / bytes_per_meter;
          glScaled( h_scale_factor, v_scale_factor, 1. );

          RenderRadarBuffer(g_scan_buf, g_current_scan_length_bytes, g_scan_meters, rotation, g_current_headings);

     }else{
          // full scan           scaling...each scan holds 4 radials
          double bytes_per_meter = (g_static_scan_length_bytes / 4) / (double)g_static_scan_meters;
          double h_scale_factor = h_scale_ppm / bytes_per_meter;
          double v_scale_factor = v_scale_ppm / bytes_per_meter;
          glScaled( h_scale_factor, v_scale_factor, 1. );

          RenderRadarBuffer(g_static_buf, g_static_scan_length_bytes, g_static_scan_meters, rotation, g_static_headings);
     }
     glPopMatrix();
     glPopAttrib();            // restore state
}


double sang;
double eang;

bool onearc(double ang)
{
     if ((ang >= sang) && (ang <= eang))
          return true;
     else
          return false;
}

bool twoarc(double ang)
{
     if ((ang >= sang) || (ang <= eang))
          return true;
     else
          return false;
}


void gradar_pi::RenderRadarBuffer(unsigned char *buffer, int buffer_line_length, int scan_meters, double rotation, double headings[])
{
     if(buffer == 0) return;
     m_zonealarm = 0;
     int maxrad = buffer_line_length/4;

     double mtrsperbyte = (double)scan_meters / (double)maxrad;

     bool (*checkzoneangle)(double) = onearc;

     bool zoneangle = false;
     bool checkzone = false;
     if(m_guardzone_mode == 1){
          zoneangle = true;

          if(m_partial_arc_mode == 1){
               checkzone = true;
               sang = (double)m_arc_start_angle;
               eang = (double)m_arc_end_angle;
               if ( sang < 0)
                    sang += 360;
               if ( eang < 0)
                    eang += 360;

               if (eang > sang)
                    checkzoneangle = onearc;
               else
                    checkzoneangle = twoarc;
          }
     }

     unsigned char sred = m_scan_color.Red();
     unsigned char sgrn = m_scan_color.Green();
     unsigned char sblu = m_scan_color.Blue();
     unsigned char alpha = 255 * m_overlay_transparency;
     glColor4ub(sred, sgrn, sblu, alpha);

     for(int i=0 ; i < 360 ; i += 2){
          unsigned char *packet_data = &buffer[i * buffer_line_length / 2];
          double angle = i + headings[i/2] + rotation - 90.0;
          double checkangle = i;

          for(int j=0 ; j < 4 ; j++){
               if(checkzone)
                    zoneangle = checkzoneangle(checkangle);

               double ca = cos(angle * PI / 180.);
               double sa = sin(angle * PI / 180.);

               for(int k=0 ; k < maxrad ; k++){
                    unsigned char data1 = *packet_data;
                    double rad = k;

                    if(data1 != 0){
                         if(zoneangle){
                              double zrad = double(rad + 0.5) * mtrsperbyte;
                              if((zrad >= m_inner_range) && (zrad <= m_outer_range))
                                   m_zonealarm ++;
                         }

                         double b_start = 0.0;
                         double b_end = 1.0;

                         if(data1 == 255){
                              draw_blob_gl(rad, b_start, b_end, 0.5, ca, sa);
                         }else{
                              bool start = false;
                              for (int bit_num = 0; bit_num <= 8; bit_num++){
                                   if(data1 & 0x01 ){
                                        if(!start){
                                             start = true;
                                             b_start=(double)(bit_num)/8.0;
                                        }
                                   }else{
                                        if(start){
                                             start = false;
                                             b_end = (double)(bit_num)/8.0;
                                             draw_blob_gl(rad, b_start, b_end, 0.5, ca, sa);
                                        }
                                   }
                                   data1 >>= 1;
                              }
                         }
                    }
                    packet_data++;
               }
               angle += 0.5;
               checkangle += 0.5;
          }
     }

     if(m_zonealarm > m_sentry_alarm_sensitivity) {

          if (NULL == m_pSentryAlarmDialog) {
               m_pSentryAlarmDialog = new SentryAlarmDialog(this, m_parent_window);
               m_pSentryAlarmDialog->SetSize(m_Sentry_Alarm_dialog_x, m_Sentry_Alarm_dialog_y,
                    m_Sentry_Alarm_dialog_sx, m_Sentry_Alarm_dialog_sy);
               m_pSentryAlarmDialog->Show();
          }
          m_pSentryAlarmDialog->Show();

          if (!m_alert_audio_file.IsEmpty() && !m_balarm_silence) {
              PlugInPlaySound( m_alert_audio_file );
          }
     }
}


void gradar_pi::RenderRadarGuardZone(wxPoint radar_center,double h_scale_ppm, double v_scale_ppm, PlugIn_ViewPort *vp)
{
     double rotation = vp->rotation * 180/PI;
     glPushAttrib(GL_COLOR_BUFFER_BIT | GL_LINE_BIT | GL_HINT_BIT);      //Save state
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     glPushMatrix();

     glTranslated( radar_center.x, radar_center.y, 0);
     glScaled(h_scale_ppm, v_scale_ppm, 1.0);

     RenderGuardZone(rotation);

     glPopMatrix();
     glPopAttrib();            // restore state
}

void gradar_pi::RenderGuardZone(double rotation)
{

     int start = 0;
     int stop = 360;
     int zone_size = m_outer_range - m_inner_range;
     unsigned char red = m_guardzone_color.Red();
     unsigned char green = m_guardzone_color.Green();
     unsigned char blue = m_guardzone_color.Blue();
     unsigned char alpha = 255 * m_guardzone_transparency;
     glColor4ub(red, green, blue, alpha);

     if(m_partial_arc_mode == 1)
     {
          start = m_arc_start_angle;
          stop = m_arc_end_angle;
          if((start < 0) && (stop > 0) && ((360 + start) < stop))
               start += 360;
     }

     for(int i = start; i < stop; ++i)
     {
          double angle = i + g_hdt + rotation - 90.0;
          double ca = cos( angle * PI / 180.0);
          double sa = sin( angle * PI / 180.0);

          draw_blob_gl( m_inner_range, 0.0, zone_size, 1.0, ca, sa );
     }
}


void gradar_pi::draw_blob_gl( double radius, double blob_start, double blob_end, double arc_length, double ca, double sa)
{

     //    Calculate the blob size...
     double xm1 = (radius + blob_start) * ca;
     double ym1 = (radius + blob_start) * sa;
     double xm2 = (radius + blob_end) * ca;
     double ym2 = (radius + blob_end) * sa;

     double blob_width_start2 =  ((radius + blob_start) * PI * arc_length / 360);
     double blob_width_end2 =  ((radius + blob_end) * PI * arc_length / 360);

     double xa = xm1 + blob_width_start2 * sa;
     double ya = ym1 - blob_width_start2 * ca;

     double xb = xm2 + blob_width_end2 * sa;
     double yb = ym2 - blob_width_end2 * ca;

     double xc = xm1 - blob_width_start2 * sa;
     double yc = ym1 + blob_width_start2 * ca;

     double xd = xm2 - blob_width_end2 * sa;
     double yd = ym2 + blob_width_end2 * ca;


     glBegin(GL_TRIANGLES);
     glVertex2d(xa, ya);
     glVertex2d(xb, yb);
     glVertex2d(xc, yc);

     glVertex2d(xb, yb);
     glVertex2d(xc, yc);
     glVertex2d(xd, yd);
     glEnd();
}

void gradar_pi::SetCursorLatLon(double lat, double lon)
{
}

void gradar_pi::SetNMEASentence( wxString &sentence )
{
     m_NMEA0183 << sentence;

     if( m_NMEA0183.PreParse() ) {
          if( m_NMEA0183.LastSentenceIDReceived == _T("HDG") ) {
               if( m_NMEA0183.Parse() ) {
                    if( mPriVar >= 1 ) {
                         if( !wxIsNaN( m_NMEA0183.Hdg.MagneticVariationDegrees ) ){
                              mPriVar = 1;
                              if( m_NMEA0183.Hdg.MagneticVariationDirection == East )
                                   m_var =  m_NMEA0183.Hdg.MagneticVariationDegrees;
                              else if( m_NMEA0183.Hdg.MagneticVariationDirection == West )
                                   m_var = -m_NMEA0183.Hdg.MagneticVariationDegrees;
                              mVar_Watchdog = gps_watchdog_timeout_ticks;
                         }
                    }
                    if( mPriHeadingM >= 1 ) {
                         if( !wxIsNaN(m_NMEA0183.Hdg.MagneticSensorHeadingDegrees) ){
                              mPriHeadingM = 1;
                              m_hdm = m_NMEA0183.Hdg.MagneticSensorHeadingDegrees;
                              mHDx_Watchdog = gps_watchdog_timeout_ticks;
                         }
                    }
                    if( !wxIsNaN(m_NMEA0183.Hdg.MagneticSensorHeadingDegrees) ) {
                         if( !wxIsNaN( m_var )  && (mPriHeadingT >= 2) ){
                              mPriHeadingT = 2;
                              g_hdt = m_hdm + m_var;
                              mHDT_Watchdog = gps_watchdog_timeout_ticks;
                         }
                    }
               }
          }

          else if( m_NMEA0183.LastSentenceIDReceived == _T("HDM") ) {
               if( m_NMEA0183.Parse() ) {
                    if( mPriHeadingM >= 2 ) {
                         if( !wxIsNaN(m_NMEA0183.Hdm.DegreesMagnetic) ){
                              mPriHeadingM = 2;
                              m_hdm = m_NMEA0183.Hdm.DegreesMagnetic;
                              mHDx_Watchdog = gps_watchdog_timeout_ticks;
                         }
                         if( !wxIsNaN(m_NMEA0183.Hdm.DegreesMagnetic) ) {
                              if( !wxIsNaN( m_var )  && (mPriHeadingT >= 3) ){
                                   mPriHeadingT = 3;
                                   g_hdt = m_hdm + m_var;
                                   mHDT_Watchdog = gps_watchdog_timeout_ticks;
                              }
                         }
                    }
               }

               else if( m_NMEA0183.LastSentenceIDReceived == _T("HDT") ) {
                    if( m_NMEA0183.Parse() ) {
                         if( mPriHeadingT >= 1 ) {
                              if( !wxIsNaN(m_NMEA0183.Hdt.DegreesTrue) ){
                                   mPriHeadingT = 1;
                                   g_hdt = m_NMEA0183.Hdt.DegreesTrue;
                                   mHDT_Watchdog = gps_watchdog_timeout_ticks;
                              }
                         }
                    }
               }
          }
     }
}

void gradar_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
     m_ownship_lat = pfix.Lat;
     m_ownship_lon = pfix.Lon;

     if(mPriVar >= 5){
          if( !wxIsNaN( pfix.Var ) ){
               mPriVar = 5;
               m_var = pfix.Var;
               mVar_Watchdog = gps_watchdog_timeout_ticks;
          }
     }
     if(mPriHeadingM >= 5){
          if(!wxIsNaN(pfix.Hdm)){
               mPriHeadingM = 5;
               m_hdm = pfix.Hdm;
               mHDx_Watchdog = gps_watchdog_timeout_ticks;
          }
     }
     if(mPriHeadingT >= 5){
          if(!wxIsNaN(pfix.Hdt)){
               mPriHeadingT = 5;
               g_hdt = pfix.Hdt;
               mHDT_Watchdog = gps_watchdog_timeout_ticks;
          }
     }
     if(mPriHeadingT >= 6){
          if(!wxIsNaN(m_var) && !wxIsNaN(m_hdm)){
               mPriHeadingT = 6;
               g_hdt = m_var + m_hdm;
               mHDT_Watchdog = gps_watchdog_timeout_ticks;
          }
     }
     if(mPriHeadingT >= 7){
          if(!wxIsNaN(pfix.Cog)){
               mPriHeadingT = 7;
               g_hdt = pfix.Cog;
               mHDT_Watchdog = gps_watchdog_timeout_ticks;
          }
     }

     if(g_hdt != hdt_last_message) {
          wxString msg;
          msg.Printf(_T("True Heading:  %g  Mag Heading:  %g  Variation:  %g    thpri: %i  mhpri: %i  vpri: %i\n"),
               g_hdt, m_hdm, m_var, mPriHeadingT, mPriHeadingM, mPriVar);
          grLogMessage(msg);

          hdt_last_message = g_hdt;
     }

     m_bpos_set = true;
}

bool gradar_pi::LoadConfig(void)
{
     wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

     if(pConf) {
          pConf->SetPath ( _T( "/Plugins/GRadar" ) );
          pConf->Read ( _T( "GRadarOpMode" ),  &m_bmaster, 0 );
          pConf->Read ( _T( "GRadarDisplayMode" ),  &g_updatemode, 0 );
          pConf->Read ( _T( "GRadarTransparency" ),  &m_overlay_transparency, .50 );
          pConf->Read ( _T( "GRadarLog" ),  &b_enable_log, true );

          m_Control_dialog_sx = pConf->Read ( _T ( "ControlDialogSizeX" ), 155L );
          m_Control_dialog_sy = pConf->Read ( _T ( "ControlDialogSizeY" ), 467L );
          m_Control_dialog_x =  pConf->Read ( _T ( "ControlDialogPosX" ), 1L );
          m_Control_dialog_y =  pConf->Read ( _T ( "ControlDialogPosY" ), 149L );

          m_Range_dialog_sx = pConf->Read ( _T ( "RangeDialogSizeX" ), 157L );
          m_Range_dialog_sy = pConf->Read ( _T ( "RangeDialogSizeY" ), 455L );
          m_Range_dialog_x =  pConf->Read ( _T ( "RangeDialogPosX" ), 157L );
          m_Range_dialog_y =  pConf->Read ( _T ( "RangeDialogPosY" ), 157L );

          m_Noise_dialog_sx = pConf->Read ( _T ( "NoiseDialogSizeX" ), 216L );
          m_Noise_dialog_sy = pConf->Read ( _T ( "NoiseDialogSizeY" ), 453L );
          m_Noise_dialog_x =  pConf->Read ( _T ( "NoiseDialogPosX" ), 315L );
          m_Noise_dialog_y =  pConf->Read ( _T ( "NoiseDialogPosY" ), 159L );

          m_Dome_dialog_sx = pConf->Read ( _T ( "DomeDialogSizeX" ), 157L );
          m_Dome_dialog_sy = pConf->Read ( _T ( "DomeDialogSizeY" ), 232L );
          m_Dome_dialog_x =  pConf->Read ( _T ( "DomeDialogPosX" ), 161L );
          m_Dome_dialog_y =  pConf->Read ( _T ( "DomeDialogPosY" ), 254L );

          m_Sentry_dialog_sx = pConf->Read ( _T ( "SentryDialogSizeX" ), 157L );
          m_Sentry_dialog_sy = pConf->Read ( _T ( "SentryDialogSizeY" ), 232L );
          m_Sentry_dialog_x =  pConf->Read ( _T ( "SentryDialogPosX" ), 161L );
          m_Sentry_dialog_y =  pConf->Read ( _T ( "SentryDialogPosY" ), 254L );

          m_Sentry_Alarm_dialog_sx = pConf->Read ( _T ( "SentryAlarmDialogSizeX" ), 231L );
          m_Sentry_Alarm_dialog_sy = pConf->Read ( _T ( "SentryAlarmDialogSizeY" ), 174L );
          m_Sentry_Alarm_dialog_x =  pConf->Read ( _T ( "SentryAlarmDialogPosX" ), 161L );
          m_Sentry_Alarm_dialog_y =  pConf->Read ( _T ( "SentryAlarmDialogPosY" ), 254L );

          m_alert_audio_file = pConf->Read ( _T ( "AlertSoundFile" ), "" );

          return true;
     } else {
          return false;
     }
}

bool gradar_pi::SaveConfig(void)
{
     wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

     if(pConf) {
          pConf->SetPath ( _T ( "/Plugins/GRadar" ) );
          pConf->Write ( _T ( "GRadarOpMode" ), m_bmaster );
          pConf->Write ( _T ( "GRadarDisplayMode" ), g_updatemode );
          pConf->Write ( _T ( "GRadarTransparency" ), m_overlay_transparency );
          pConf->Write ( _T ( "GRadarLog" ), b_enable_log );

          pConf->Write ( _T ( "ControlDialogSizeX" ),  m_Control_dialog_sx );
          pConf->Write ( _T ( "ControlDialogSizeY" ),  m_Control_dialog_sy );
          pConf->Write ( _T ( "ControlDialogPosX" ),   m_Control_dialog_x );
          pConf->Write ( _T ( "ControlDialogPosY" ),   m_Control_dialog_y );

          pConf->Write ( _T ( "RangeDialogSizeX" ),  m_Range_dialog_sx );
          pConf->Write ( _T ( "RangeDialogSizeY" ),  m_Range_dialog_sy );
          pConf->Write ( _T ( "RangeDialogPosX" ),   m_Range_dialog_x );
          pConf->Write ( _T ( "RangeDialogPosY" ),   m_Range_dialog_y );

          pConf->Write ( _T ( "NoiseDialogSizeX" ),  m_Noise_dialog_sx );
          pConf->Write ( _T ( "NoiseDialogSizeY" ),  m_Noise_dialog_sy );
          pConf->Write ( _T ( "NoiseDialogPosX" ),   m_Noise_dialog_x );
          pConf->Write ( _T ( "NoiseDialogPosY" ),   m_Noise_dialog_y );

          pConf->Write ( _T ( "DomeDialogSizeX" ),  m_Dome_dialog_sx );
          pConf->Write ( _T ( "DomeDialogSizeY" ),  m_Dome_dialog_sy );
          pConf->Write ( _T ( "DomeDialogPosX" ),   m_Dome_dialog_x );
          pConf->Write ( _T ( "DomeDialogPosY" ),   m_Dome_dialog_y );

          pConf->Write ( _T ( "SentryDialogSizeX" ),  m_Sentry_dialog_sx );
          pConf->Write ( _T ( "SentryDialogSizeY" ),  m_Sentry_dialog_sy );
          pConf->Write ( _T ( "SentryDialogPosX" ),   m_Sentry_dialog_x );
          pConf->Write ( _T ( "SentryDialogPosY" ),   m_Sentry_dialog_y );

          pConf->Write ( _T ( "SentryAlarmDialogSizeX" ),  m_Sentry_Alarm_dialog_sx );
          pConf->Write ( _T ( "SentryAlarmDialogSizeY" ),  m_Sentry_Alarm_dialog_sy );
          pConf->Write ( _T ( "SentryAlarmDialogPosX" ),   m_Sentry_Alarm_dialog_x );
          pConf->Write ( _T ( "SentryAlarmDialogPosY" ),   m_Sentry_Alarm_dialog_y );

          pConf->Write ( _T ( "AlertSoundFile" ), m_alert_audio_file );

          return true;
     } else {
          return false;
     }
}

void gradar_pi::RadarTxOff(void)
{
     if(!m_bmaster)
          return;

     rad_ctl_pkt pck;
     pck.packet_type = 0x2b2;
     pck.len1 = 2;
     pck.parm1 = 1;            // 1 (one) for "off"

     SendCommand((unsigned char *)&pck, sizeof(pck));
     grLogMessage(_T("TX Off\n"));

}

void gradar_pi::RadarTxOn(void)
{
     if(!m_bmaster)
          return;

     rad_ctl_pkt pck;
     pck.packet_type = 0x2b2;
     pck.len1 = 2;
     pck.parm1 = 2;            // 2(two) for "on"

     SendCommand((unsigned char *)&pck, sizeof(pck));
     grLogMessage(_T("TX On\n"));
}

void gradar_pi::SendCommand(unsigned char *ppkt, unsigned int n_bytes)
{
     wxIPV4address destaddr;
     destaddr.Service(_T("50101"));
     destaddr.Hostname(m_scanner_ip);
     m_out_sock101->SendTo(destaddr, ppkt, n_bytes);
}

void gradar_pi::CacheSetToolbarToolBitmaps( int bm_id_normal, int bm_id_rollover)
{
     if((bm_id_normal == m_sent_bm_id_normal) && (bm_id_rollover == m_sent_bm_id_rollover))
          return;                                                 // no change needed

     if((bm_id_normal == -1) || (bm_id_rollover == -1)) {          // don't do anything, caller's responsibility
          m_sent_bm_id_normal = bm_id_normal;
          m_sent_bm_id_rollover = bm_id_rollover;
          return;
     }

     m_sent_bm_id_normal = bm_id_normal;
     m_sent_bm_id_rollover = bm_id_rollover;

     wxBitmap *pnormal = NULL;
     wxBitmap *prollover = NULL;

     switch(bm_id_normal)
     {
     case BM_ID_RED:
          pnormal = _img_radar_red;
          break;
     case BM_ID_RED_SLAVE:
          pnormal = _img_radar_red_slave;
          break;
     case BM_ID_GREEN:
          pnormal = _img_radar_green;
          break;
     case BM_ID_GREEN_SLAVE:
          pnormal = _img_radar_green_slave;
          break;
     case BM_ID_GREEN_TT:
          pnormal = _img_radar_green_tt;
          break;
     case BM_ID_GREEN_SLAVE_TT:
          pnormal = _img_radar_green_slave_tt;
          break;
     case BM_ID_AMBER:
          pnormal = _img_radar_amber;
          break;
     case BM_ID_AMBER_SLAVE:
          pnormal = _img_radar_amber_slave;
          break;
     case BM_ID_AMBER_TT:
          pnormal = _img_radar_amber_tt;
          break;
     case BM_ID_AMBER_SLAVE_TT:
          pnormal = _img_radar_amber_slave_tt;
          break;
     case BM_ID_BLANK:
          pnormal = _img_radar_blank;
          break;
     case BM_ID_BLANK_SLAVE:
          pnormal = _img_radar_blank_slave;
          break;
     default:
          break;
     }

     switch(bm_id_rollover)
     {
     case BM_ID_RED:
          prollover = _img_radar_red;
          break;
     case BM_ID_RED_SLAVE:
          prollover = _img_radar_red_slave;
          break;
     case BM_ID_GREEN:
          prollover = _img_radar_green;
          break;
     case BM_ID_GREEN_SLAVE:
          prollover = _img_radar_green_slave;
          break;
     case BM_ID_GREEN_TT:
          prollover = _img_radar_green_tt;
          break;
     case BM_ID_GREEN_SLAVE_TT:
          prollover = _img_radar_green_slave_tt;
          break;
     case BM_ID_AMBER:
          prollover = _img_radar_amber;
          break;
     case BM_ID_AMBER_SLAVE:
          prollover = _img_radar_amber_slave;
          break;
     case BM_ID_AMBER_TT:
          prollover = _img_radar_amber_tt;
          break;
     case BM_ID_AMBER_SLAVE_TT:
          prollover = _img_radar_amber_slave_tt;
          break;
     case BM_ID_BLANK:
          prollover = _img_radar_blank;
          break;
     case BM_ID_BLANK_SLAVE:
          prollover = _img_radar_blank_slave;
          break;
     default:
          break;
     }

     if( (pnormal) && (prollover) )
          SetToolbarToolBitmaps(m_tool_id, pnormal, prollover);
}



void gradar_pi::UpdateState(void)
{
     g_pseudo_tick++;

     wxString scan_state;
     wxString plug_state;

     switch(g_scanner_state)
     {
     case 1:
          scan_state = _T("Warmup");
          break;
     case 2:
          scan_state =_T("TT Standby");
          break;
     case 3:
          scan_state = _T("Standby");
          break;
     case 4:
          scan_state = _T("TX Active");
          break;
     case 5:
          scan_state = _T("Spinup");
          break;
     case 7:
          scan_state = _T("TT TX Active");
          break;
     case 8:
          scan_state = _T("TT Spinup");
          break;
     default:
          scan_state = _T("Unknown");
          break;
     }

     switch(g_radar_state)
     {
     case 0:
          plug_state = _T("Off");
          break;
     case 1:
          plug_state = _T("Searching");
          break;
     case 2:
          plug_state = _T("Warmup");
          break;
     case 3:
          plug_state = _T("Standby");
          break;
     case 4:
          plug_state = _T("Spinup");
          break;
     case 5:
          plug_state = _T("TX Active");
          break;
     case 6:
          plug_state = _T("TT Standby");
          break;
     case 7:
          plug_state = _T("TT TX Active");
          break;
     case 8:
          plug_state = _T("TT Spinup");
          break;
     default:
          plug_state = _T("Unknown");
          break;
     }

     if((g_radar_state != g_prev_radar_state) || (g_scanner_state != m_prev_scanner_state)) {
          wxString msg(_T("UpdateState:  PluginState  "));

          if(m_bmaster)
               msg += _T("[M]  ");
          else
               msg += _T("[S]  ");

          msg += plug_state;
          wxString msg2;
          msg2.Printf(_T("  (%d)"), g_radar_state);
          msg += msg2;

          msg += _T("   Scanner state:  ");

          msg += scan_state;
          msg2.Printf(_T("  (%d)"), g_scanner_state);
          msg += msg2;

          msg += _T("\n");

          grLogMessage(msg);

          if(g_scan_packets_per_tick){
               msg.Printf(_T("Scan packets per tick: %d\n"), g_scan_packets_per_tick );
               grLogMessage( msg );
          }
     }

     g_prev_radar_state = g_radar_state;
     m_prev_scanner_state = g_scanner_state;

     //    Auto state switching is only needed in master mode
     // if(m_bmaster) {
     {
          //        int current_state = g_radar_state;

          switch (g_scanner_state)
          {
          case 1:
               g_radar_state = RADAR_IN_TIMED_WARMUP;
               break;
          case 2:
               g_radar_state = RADAR_TT_STANDBY;
               break;
          case 3:
               g_radar_state = RADAR_STANDBY;
               break;
          case 4:
               g_radar_state = RADAR_TX_ACTIVE;
               break;
          case 5:
               g_radar_state = RADAR_IN_TIMED_SPINUP;
               break;
          case 7:
               g_radar_state = RADAR_TT_TX_ACTIVE;
               break;
          case 8:
               g_radar_state = RADAR_TT_SPINUP;
               break;

          default:
               break;
          }
     }


     //    Manage icons
     switch(g_radar_state)
     {
     case RADAR_OFF:
     case RADAR_ACTIVATE:
          if(m_bmaster)
               CacheSetToolbarToolBitmaps( BM_ID_RED, BM_ID_RED);
          else
               CacheSetToolbarToolBitmaps( BM_ID_RED_SLAVE, BM_ID_RED_SLAVE);

          break;

     case RADAR_IN_TIMED_WARMUP:
          {
               if(g_warmup_timer != g_last_warmup_timer)
               {
                    g_last_warmup_timer = g_warmup_timer;

                    wxBitmap *pbmp;
                    if(g_warmup_timer & 1)
                         pbmp = _img_radar_blank;
                    else
                         pbmp = _img_radar_amber;

                    wxString str;
                    str.Printf(_T("%2d"), g_warmup_timer);

                    delete m_ptemp_icon;
                    m_ptemp_icon = new wxBitmap(pbmp->GetWidth(), pbmp->GetHeight());
                    wxMemoryDC dc(*m_ptemp_icon);
                    dc.Clear();
                    dc.DrawBitmap(*pbmp, 0, 0, true);
                    wxColour cf;
                    GetGlobalColor(_T("CHBLK"), &cf);
                    dc.SetTextForeground(cf);
                    wxFont *pFont = wxTheFontList->FindOrCreateFont(10, wxDEFAULT,
                         wxNORMAL, wxNORMAL, FALSE, wxString(_T("Eurostile Extended")));

                    dc.SetFont(*pFont);
                    wxSize s = dc.GetTextExtent(str);
                    dc.DrawText(str, (pbmp->GetWidth() - s.GetWidth()) / 2, (pbmp->GetHeight() - s.GetHeight()) / 2);
                    CacheSetToolbarToolBitmaps( -1, -1 );           // mark the cached values
                    SetToolbarToolBitmaps( m_tool_id, m_ptemp_icon, m_ptemp_icon);
               }
               break;
          }

     case RADAR_STANDBY:
          if(m_bmaster)
               CacheSetToolbarToolBitmaps( BM_ID_AMBER, BM_ID_AMBER);
          else
               CacheSetToolbarToolBitmaps( BM_ID_AMBER_SLAVE, BM_ID_AMBER_SLAVE);
          break;

     case RADAR_IN_TIMED_SPINUP:
          {
               if(g_pseudo_tick & 1) {
                    if(m_bmaster)
                         CacheSetToolbarToolBitmaps( BM_ID_BLANK, BM_ID_BLANK);
                    else
                         CacheSetToolbarToolBitmaps( BM_ID_BLANK_SLAVE, BM_ID_BLANK_SLAVE);
               }
               else {
                    if(m_bmaster)
                         CacheSetToolbarToolBitmaps( BM_ID_GREEN, BM_ID_GREEN);
                    else
                         CacheSetToolbarToolBitmaps( BM_ID_GREEN_SLAVE, BM_ID_GREEN_SLAVE);
               }
               break;
          }

     case RADAR_TX_ACTIVE:
          if(m_bmaster)
               CacheSetToolbarToolBitmaps( BM_ID_GREEN, BM_ID_GREEN);
          else
               CacheSetToolbarToolBitmaps( BM_ID_GREEN_SLAVE, BM_ID_GREEN_SLAVE);
          break;

     case RADAR_TT_STANDBY:
     case RADAR_TT_SPINUP:
          if(m_bmaster)
               CacheSetToolbarToolBitmaps(BM_ID_AMBER_TT, BM_ID_AMBER_TT);
          else
               CacheSetToolbarToolBitmaps(BM_ID_AMBER_SLAVE_TT, BM_ID_AMBER_SLAVE_TT);
          break;

     case RADAR_TT_TX_ACTIVE:
          if(m_bmaster)
               CacheSetToolbarToolBitmaps(BM_ID_GREEN_TT, BM_ID_GREEN_TT);
          else
               CacheSetToolbarToolBitmaps(BM_ID_GREEN_SLAVE_TT, BM_ID_GREEN_SLAVE_TT);
          break;

     default:
          break;
     }
}

void gradar_pi::Select_Range(double range_nm)
{
     if(!m_bmaster)
          return;

     int range_parm_meters = (range_nm * 1852)-1;
     rad_range_pkt pck;
     pck.packet_type = 0x2b3;
     pck.len1 = 4;
     pck.parm1 = range_parm_meters;

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("SelectRange: %g nm\n"), range_nm);
     grLogMessage(msg);
}

void gradar_pi::SetUpdateMode(int mode)
{
     g_updatemode = mode;
}

void gradar_pi::SetOperatingMode(int mode)
{
     if(m_bscanner_accessible)
          m_bmaster = (mode == 0);
     else {
          ShowNoAccessMessage();
          m_bmaster = false;
     }
     if(!m_bmaster)
          m_slave_display_mode = SLAVE_DISPLAY_ON;
}

void gradar_pi::SetScanColor( wxColour col )
{
     m_scan_color = col;
}

void gradar_pi::SetRangeControlMode(int mode)
{
     if(!m_bmaster){
          m_range_control_mode = 0;
          if(m_pRangeDialog)
               if(m_pRangeDialog->IsShown())m_pRangeDialog->RangeDialogShow();
          return;
     }

     m_range_control_mode = mode;
}

void gradar_pi::SetManualRange(int mode)
{
     if(!m_bmaster){
          m_range_control_mode = 0;
          if(m_pRangeDialog)
               if(m_pRangeDialog->IsShown())m_pRangeDialog->RangeDialogShow();
          return;
     }
     if(m_range_control_mode == 1)
          m_manual_range = mode;
     if(m_pRangeDialog)
          if(m_pRangeDialog->IsShown())m_pRangeDialog->RangeDialogShow();
}


void gradar_pi::SetGainControlMode(int mode)
{
     if(!m_bmaster){
          if(m_pRangeDialog)
               if(m_pRangeDialog->IsShown())m_pRangeDialog->RangeDialogShow();
          return;
     }
     m_gain_control_mode = mode;

     rad_range_pkt pck;
     pck.packet_type = 0x2b4;
     pck.len1 = 4;

     if(mode == 0)
          pck.parm1 = 344;
     else
          pck.parm1 = m_gain_level;

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_gain_control_mode: %d \n"), m_gain_control_mode);
     grLogMessage(msg);
}


void gradar_pi::SetGainLevel(int mode)
{
     if(!m_bmaster || ( m_gain_control_mode  ==  0)){
          if(m_pRangeDialog)
               if(m_pRangeDialog->IsShown())m_pRangeDialog->RangeDialogShow();
          return;
     }
     m_gain_level = mode;

     rad_range_pkt pck;
     pck.packet_type = 0x2b4;
     pck.len1 = 4;
     pck.parm1 = m_gain_level;

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_gain_level: %d \n"), m_gain_level);
     grLogMessage(msg);
}

void gradar_pi::SetSeaClutterMode(int mode)
{
     if(!m_bmaster){
          if(m_pNoiseDialog)
               if(m_pNoiseDialog->IsShown())m_pNoiseDialog->NoiseDialogShow();
          return;
     }
     m_sea_clutter_mode = mode;

     fourbyte_ctl_pkt pck;
     pck.packet_type = 0x2b5;
     pck.len1 = 4;
     pck.parm3 = 0;
     pck.parm4 = 0;

     switch (m_sea_clutter_mode)
     {
     case 0:
          pck.parm1 = 0;
          pck.parm2 = 0;
          m_sea_clutter_level = 0;
          break;

     case 1:
          pck.parm1 = 0x21;
          pck.parm2 = 0x01;
          m_sea_clutter_level = 33;
          break;

     case 2:
          pck.parm1 = 0x43;
          pck.parm2 = 0x02;
          m_sea_clutter_level = 67;
          break;

     case 3:
          pck.parm1 = 0x64;
          pck.parm2 = 0x03;
          m_sea_clutter_level = 100;
          break;

     default:
          pck.parm1 = 0;
          pck.parm2 = 0;
          break;
     }

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_sea_clutter_mode: %d \n"), m_sea_clutter_mode);
     grLogMessage(msg);
}

void gradar_pi::SetSeaClutterLevel(int mode)
{
     if(!m_bmaster){
          if(m_pNoiseDialog)
               if(m_pNoiseDialog->IsShown())m_pNoiseDialog->NoiseDialogShow();
          return;
     }

     m_sea_clutter_level = mode;

     fourbyte_ctl_pkt pck;
     pck.packet_type = 0x2b5;
     pck.len1 = 4;
     pck.parm3 = 0;
     pck.parm4 = 0;

     pck.parm1 = m_sea_clutter_level;
     pck.parm2 = 0;

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_sea_clutter_level: %d \n"), m_sea_clutter_level);
     grLogMessage(msg);
}

void gradar_pi::SetFTCMode(int mode)
{
     if(!m_bmaster){
          if(m_pNoiseDialog)
               if(m_pNoiseDialog->IsShown())m_pNoiseDialog->NoiseDialogShow();
          return;
     }

     m_FTC_mode= mode;

     onebyte_ctl_pkt pck;
     pck.packet_type = 0x2b8;
     pck.len1 = 1;
     pck.parm1 = (unsigned char)m_FTC_mode;

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_FTC_mode: %d \n"), m_FTC_mode);
     grLogMessage(msg);
}

void gradar_pi::SetRainClutterLevel(int mode)
{
     if(!m_bmaster){
          if(m_pNoiseDialog)
               if(m_pNoiseDialog->IsShown())m_pNoiseDialog->NoiseDialogShow();
          return;
     }
     m_rain_clutter_level = mode;

     rad_range_pkt pck;
     pck.packet_type = 0x2b6;
     pck.len1 = 4;
     pck.parm1 = m_rain_clutter_level;

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_rain_clutter_level: %d \n"), m_rain_clutter_level);
     grLogMessage(msg);
}

void gradar_pi::SetCrosstalkMode(int mode)
{
     if(!m_bmaster){
          if(m_pNoiseDialog)
               if(m_pNoiseDialog->IsShown())m_pNoiseDialog->NoiseDialogShow();
          return;
     }
     m_crosstalk_mode = mode;

     onebyte_ctl_pkt pck;
     pck.packet_type = 0x2b9;
     pck.len1 = 1;

     if (m_crosstalk_mode == 0)
          pck.parm1 = 0x00;          //off
     else
          pck.parm1 = 0x01;          //on

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_crosstalk_mode: %d \n"), m_crosstalk_mode);
     grLogMessage(msg);
}

void gradar_pi::SetDomeOffset(int mode)
{
     if(!m_bmaster){
          if(m_pDomeDialog)
               if(m_pDomeDialog->IsShown())m_pDomeDialog->DomeDialogShow();
          return;
     }
     m_dome_offset = mode;

     offset_ctl_pkt pck;
     pck.packet_type = 0x2b7;
     pck.len1 = 2;
     pck.parm1 = m_dome_offset;

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_dome_offset: %d \n"), m_dome_offset);
     grLogMessage(msg);
}

void gradar_pi::SetDomeSpeed(int mode)
{
     if(!m_bmaster){
          if(m_pDomeDialog)
               if(m_pDomeDialog->IsShown())m_pDomeDialog->DomeDialogShow();
          return;
     }
     m_dome_speed = mode;

     onebyte_ctl_pkt pck;
     pck.packet_type = 0x2be;
     pck.len1 = 1;

     if (m_dome_speed == 0)
          pck.parm1 = 0x00;          //24 rpm
     else
          pck.parm1 = 0x01;          //30 rpm

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_dome_speed: %d \n"), m_dome_speed);
     grLogMessage(msg);
}

void gradar_pi::SetTimedTransmitMode(int mode)
{   if(!m_bmaster){
     if(m_pSentryDialog)
          if(m_pSentryDialog->IsShown()) m_pSentryDialog->SentryDialogShow();
     return;
}

m_timedtransmit_mode = mode;

fourbyte_ctl_pkt pck;
pck.packet_type = 0x2bb;
pck.len1 = 4;
pck.parm4 = 0;

pck.parm1 = (unsigned char)m_timedtransmit_mode;
pck.parm2 = (unsigned char)m_transmit_minutes;
pck.parm3 = (unsigned char)m_standby_minutes;

SendCommand((unsigned char *)&pck, sizeof(pck));

wxString msg;
msg.Printf(_T("m_timedtransmit_mode: %d \n"), m_timedtransmit_mode);
grLogMessage(msg);

}

void gradar_pi::SetStandbyMinutes(int mode)
{
     if(!m_bmaster || !(m_timedtransmit_mode == 0)){
          if(m_pSentryDialog)
               if(m_pSentryDialog->IsShown())m_pSentryDialog->SentryDialogShow();
          return;
     }

     m_standby_minutes = mode;

     fourbyte_ctl_pkt pck;
     pck.packet_type = 0x2bb;
     pck.len1 = 4;
     pck.parm4 = 0;

     pck.parm1 = (unsigned char)m_timedtransmit_mode;
     pck.parm2 = (unsigned char)m_transmit_minutes;
     pck.parm3 = (unsigned char)m_standby_minutes;

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_standby_minutes: %d \n"), m_standby_minutes);
     grLogMessage(msg);
}

void gradar_pi::SetTransmitMinutes(int mode)
{
     if(!m_bmaster || !(m_timedtransmit_mode == 0)){
          if(m_pSentryDialog)
               if(m_pSentryDialog->IsShown())m_pSentryDialog->SentryDialogShow();
          return;
     }

     m_transmit_minutes = mode;

     fourbyte_ctl_pkt pck;
     pck.packet_type = 0x2bb;
     pck.len1 = 4;
     pck.parm4 = 0;

     pck.parm1 = (unsigned char)m_timedtransmit_mode;
     pck.parm2 = (unsigned char)m_transmit_minutes;
     pck.parm3 = (unsigned char)m_standby_minutes;

     SendCommand((unsigned char *)&pck, sizeof(pck));

     wxString msg;
     msg.Printf(_T("m_transmit_minutes: %d \n"), m_transmit_minutes);
     grLogMessage(msg);

}

void gradar_pi::SetGuardZoneMode(int mode)
{
     m_guardzone_mode = mode;
}

void gradar_pi::SetOuterRange(int mode)
{
     m_outer_range = mode;
}

void gradar_pi::SetInnerRange(int mode)
{
     m_inner_range = mode;
}

void gradar_pi::SetPartialArcMode(int mode)
{
     m_partial_arc_mode = mode;
}

void gradar_pi::SetStartAngle(int mode)
{
     m_arc_start_angle = mode;
}

void gradar_pi::SetEndAngle(int mode)
{
     m_arc_end_angle = mode;
}

void gradar_pi::SetGuardZoneColor( wxColour col )
{
     m_guardzone_color = col;
}

void gradar_pi::UpdateDisplayParameters(void)
{
     RequestRefresh(GetOCPNCanvasWindow());
}

bool gradar_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
     if(0 == m_bshown_dc_message) {
          wxString message(_("The Radar Overlay PlugIn requires OpenGL mode to be activated in Toolbox->Settings"));
          //        ::wxMessageBox(message, _T("gradar_pi message"), wxICON_INFORMATION | wxOK, GetOCPNCanvasWindow());

          m_bshown_dc_message = 1;

          wxMessageDialog dlg(GetOCPNCanvasWindow(),  message, _T("gradar_pi message"), wxOK);
          dlg.ShowModal();
     }
     return false;
}

void gradar_pi::ShowNoAccessMessage(void)
{
     wxString message(_("The Radar Overlay PlugIn is unable to\ndirectly control the radar scanner.\n\n"));
     message += _("Scanner is located at ip address: ");
     message += m_scanner_ip;
     message += _T("\n\n");
     message += _("Interfaces available on this computer are:\n");
     for ( ListOf_interface_descriptor::Node *node = m_interfaces.GetFirst(); node; node = node->GetNext() )
     {
          interface_descriptor *current = node->GetData();
          message += current->ip_dot;
          wxString cidr;
          cidr.Printf(_T("/%d\n"), current->cidr);
          message += cidr;
     }

     wxMessageDialog dlg(GetOCPNCanvasWindow(),  message, _T("gradar_pi message"), wxOK);
     dlg.ShowModal();
}


MulticastRXThread::MulticastRXThread( wxMutex *pMutex, const wxString &IP_addr, const wxString &service_port)
     :wxThread()
{
     //      m_pTarget = MessageTarget;

     m_pShareMutex = pMutex;

     m_ip = IP_addr;
     m_service_port = service_port;
     m_sock = 0;

     Create();
}

MulticastRXThread::~MulticastRXThread()
{
     delete m_sock;
}

void MulticastRXThread::OnExit()
{
}

void* MulticastRXThread::Entry()
{
     g_thread_active = true;
     //    Create a datagram socket for input
     m_myaddr.AnyAddress();             // equivalent to localhost
     m_myaddr.Service(m_service_port);     // the port must align with the expected multicast address


     m_sock = new wxDatagramSocket(m_myaddr, wxSOCKET_REUSEADDR);
     m_sock->SetFlags(wxSOCKET_BLOCK);

     //    Subscribe to a multicast group
     unsigned int a = 0;
#ifdef __WXGTK__
/*     GAddress gaddress;
     _GAddress_Init_INET(&gaddress);
     GAddress_INET_SetHostName(&gaddress, m_ip.mb_str());
     //       struct in_addr *iaddr;
     //       iaddr = &(((struct sockaddr_in *)gaddress.m_addr)->sin_addr);
     //       iaddr->s_addr = inet_addr(m_ip.mb_str());

     struct in_addr *addr;
     addr = &(((struct sockaddr_in *)gaddress.m_addr)->sin_addr);
     a = addr->s_addr;
 */
     a = inet_addr(m_ip.mb_str());

#endif

#ifdef __WXMSW__
     a = inet_addr(m_ip.mb_str());
#endif

#ifdef __WXOSX__
     a = inet_addr(m_ip.mb_str());
#endif

     struct ip_mreq mreq;
     mreq.imr_multiaddr.s_addr = a;
     //mreq.imr_interface.s_addr = inet_addr("172.16.1.1");
     mreq.imr_interface.s_addr= INADDR_ANY;    // this should be the RX interface
     // gotten like inet_addr("192.168.37.99");

     bool bam = m_sock->SetOption(IPPROTO_IP, IP_ADD_MEMBERSHIP, (const void *)&mreq, sizeof(mreq));

     //http://ho.runcode.us/q/how-to-set-up-a-socket-for-udp-multicast-with-2-network-cards-present
     wxString msg;
     if(bam) {
          msg = _T("Successfully added to multicast group ");
     }
     else {
          msg = _T("Failed to add to multicast group ");
     }

     msg.Append(m_ip);
     msg.Append(_T("\n"));
     grLogMessage(msg);

     //      tmp = s->buffer_size;
     //      if (setsockopt(udp_fd, SOL_SOCKET, SO_RCVBUF, &tmp, sizeof(tmp)) < 0) {

     wxIPV4address rx_addr;
     rx_addr.Hostname(_T("0.0.0.0"));          // any address will do here,
     // just so long as it looks like an IP

     //  In the case that the scanner is not powered up, there will be no packets from it.
     //  In this case, the time-out value of 5 seconds delays the smooth shutdown of the thread,
     //  for no good purpose.

     //  To avoid this annoyance, poll the socket at 1 second timout until something is heard.
     //  Then switch to a longer timout

     bool not_done = true;
     int n_rx_once = 0;
     m_sock->SetTimeout(1);
     while(0 == n_rx_once)
     {
          if(TestDestroy())
          {
               goto thread_exit;
          }

          m_sock->RecvFrom(rx_addr, buf, sizeof(buf));
          //       printf(" bytes read %d\n", m_sock->LastCount());

          if(m_sock->LastCount()) {
               grLogMessage(_T("->gradar_pi: First Packet Rx"));
               n_rx_once++;

               process_buffer();
          }
     }

     //    The big while....
     m_sock->SetTimeout(5);
     while((not_done))
     {
          if(TestDestroy())
          {
               not_done = false;                               // smooth exit
               goto thread_exit;
          }

          m_sock->RecvFrom(rx_addr, buf, sizeof(buf));
          //       printf(" bytes read %d\n", m_sock->LastCount());

          if(m_sock->LastCount()) {
               process_buffer();
          }
     }

thread_exit:
     g_thread_active = false;
     return 0;
}

void MulticastRXThread::process_buffer(void)
{
     //  printf("process_buffer\n");
     //      unsigned short packet_type = *(unsigned short *)(&buf[0]);

     packet_type_pkt packet;
     memcpy(&packet, buf, sizeof(packet_type_pkt));
     unsigned short packet_type = packet.packet_type;

     switch(packet_type)
     {
     case 0x2a3:
          {
               g_scan_packets_per_tick++;

               if((g_radar_state == RADAR_TX_ACTIVE)||(g_radar_state == RADAR_TT_TX_ACTIVE)) {
                    radar_scanline_pkt packet;
                    memcpy(&packet, buf, sizeof(radar_scanline_pkt));

                    if((packet.scan_length_bytes > g_max_scan_length_bytes) || (g_scan_buf == 0)) {
                         free (g_scan_buf);
                         g_scan_buf = (unsigned char *)calloc(180 * packet.scan_length_bytes, 1);

                         g_max_scan_length_bytes = packet.scan_length_bytes;
                    }

                    // Range change?
                    if((unsigned int) g_scan_range != packet.range_meters + 1)
                    {

                         if(g_scan_buf)
                              memset(g_scan_buf, 0, g_max_scan_length_bytes * 180);
                         g_sweep_count = 0;
                    }

                    g_scan_meters = packet.display_meters + 1;
                    g_scan_range = packet.range_meters + 1;
                    g_scan_gain_level = packet.gain_level[0];
                    g_scan_gain_mode = packet.gain_level[1];
                    g_scan_sea_clutter_level = packet.sea_clutter[0];
                    g_scan_sea_clutter_mode = packet.sea_clutter[1];
                    g_scan_rain_clutter_level = packet.rain_clutter[0];
                    g_scan_dome_offset = packet.dome_offset;
                    g_scan_FTC_mode = packet.FTC_mode;
                    g_scan_crosstalk_mode = packet.crosstalk_onoff;
                    g_scan_timed_transmit_mode = packet.timed_transmit[0];
                    g_scan_timed_transmit_transmit = packet.timed_transmit[1];
                    g_scan_timed_transmit_standby = packet.timed_transmit[2];
                    g_scan_dome_speed = packet.dome_speed;

                    if(packet.angle == 358)
                         g_sweep_count++;

                    g_current_scan_length_bytes = packet.scan_length_bytes;

                    unsigned char *packet_data = buf + sizeof(radar_scanline_pkt) - 1;
                    unsigned char *dest_data = &g_scan_buf[packet.scan_length_bytes * packet.angle / 2];
                    memcpy(dest_data, packet_data, packet.scan_length_bytes);

                    g_current_headings[packet.angle/2] = g_hdt;

                    // if in full screen mode, take a snapshot of the scan data on last radial (358 deg)
                    if((g_updatemode == 1) && (packet.angle == 358) && (g_sweep_count >= 2)) {
                         if(packet.scan_length_bytes > g_static_max_scan_length_bytes) {
                              free(g_static_buf);
                              g_static_buf = (unsigned char *)calloc(180 * packet.scan_length_bytes, 1);
                              g_static_max_scan_length_bytes = packet.scan_length_bytes;
                         }

                         memcpy(g_static_buf, g_scan_buf, packet.scan_length_bytes * 180);
                         g_static_scan_length_bytes = g_current_scan_length_bytes;
                         g_static_scan_meters = g_scan_meters;

                         for(int i=0; i<180; ++i)
                              g_static_headings[i] = g_current_headings[i];
                    }
               }
               break;
          }

     case 0x2a5:
          {
               g_scan_packets_per_tick++;

               rad_status_pkt packet;
               memcpy(&packet, buf, sizeof(rad_status_pkt));
               g_scanner_state = packet.parm1;
               g_warmup_timer = packet.parm2;

               break;
          }

     case 0x2a7:
          {
               g_scan_packets_per_tick++;

               radar_response_pkt packet;
               memcpy(&packet, buf, sizeof(radar_response_pkt));
               g_scan_range = packet.range_meters+1;
               g_scan_gain_level  = packet.gain_level[0];
               g_scan_gain_mode = packet.gain_level[1];
               g_scan_sea_clutter_level = packet.sea_clutter[0];
               g_scan_sea_clutter_mode = packet.sea_clutter[1];
               g_scan_rain_clutter_level = packet.rain_clutter[0];
               g_scan_dome_offset = packet.dome_offset;
               g_scan_FTC_mode = packet.FTC_mode;
               g_scan_crosstalk_mode = packet.crosstalk_onoff;
               g_scan_timed_transmit_mode = packet.timed_transmit[0];
               g_scan_timed_transmit_transmit = packet.timed_transmit[1];
               g_scan_timed_transmit_standby = packet.timed_transmit[2];
               g_scan_dome_speed = packet.dome_speed;
               break;
          }

     default:
          break;
     }
}



