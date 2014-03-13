/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  OpenCPN Georef utility
 * Author:   David Register
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
 ***************************************************************************

 ***************************************************************************
 *  Parts of this file were adapted from source code found in              *
 *  John F. Waers (jfwaers@csn.net) public domain program MacGPS45         *
 ***************************************************************************

 */

#ifndef     __GEOREF_H__
#define     __GEOREF_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//------------------------
struct DATUM {
        const char *name;
        short ellipsoid;
        double dx;
        double dy;
        double dz;
};

struct ELLIPSOID {
        const char *name;             // name of ellipsoid
        double a;               // semi-major axis, meters
        double invf;            // 1/f
};

struct GeoRef {
  int status;
  int count;
  int order;
  double *tx;
  double *ty;
  double *lon;
  double *lat;
  double *pwx;
  double *pwy;
  double *wpx;
  double *wpy;
  int    txmax;
  int    tymax;
  int    txmin;
  int    tymin;
  double lonmax;
  double lonmin;
  double latmax;
  double latmin;

};


#ifndef PI
      #define PI        3.1415926535897931160E0      /* pi */
#endif
#define DEGREE    (PI/180.0)
#define RADIAN    (180.0/PI)

#define DATUM_INDEX_WGS84     100
#define DATUM_INDEX_UNKNOWN   -1


static const double WGS84_semimajor_axis_meters       = 6378137.0;           // WGS84 semimajor axis
static const double mercator_k0                       = 0.9996;
static const double WGSinvf                           = 298.257223563;       /* WGS84 1/f */


void datumParams(short datum, double *a, double *es);


//      Make these conversion routines useable by C or C++


#ifdef __cplusplus
extern "C" void toDMS(double a, char *bufp, int bufplen);
extern "C" void toDMM(double a, char *bufp, int bufplen);
extern "C" void todmm(int flag, double a, char *bufp, int bufplen);

extern "C" void toTM(float lat, float lon, float lat0, float lon0, double *x, double *y);
extern "C" void fromTM(double x, double y, double lat0, double lon0, double *lat, double *lon);

extern "C" void toSM(double lat, double lon, double lat0, double lon0, double *x, double *y);
extern "C" void fromSM(double x, double y, double lat0, double lon0, double *lat, double *lon);

extern "C" void toSM_ECC(double lat, double lon, double lat0, double lon0, double *x, double *y);
extern "C" void fromSM_ECC(double x, double y, double lat0, double lon0, double *lat, double *lon);

extern "C" void toPOLY(double lat, double lon, double lat0, double lon0, double *x, double *y);
extern "C" void fromPOLY(double x, double y, double lat0, double lon0, double *lat, double *lon);

/// distance in nautical miles
extern "C" void ll_gc_ll(double lat, double lon, double crs, double dist, double *dlat, double *dlon);
extern "C" void ll_gc_ll_reverse(double lat1, double lon1, double lat2, double lon2,
                                double *bearing, double *dist);


extern "C" void PositionBearingDistanceMercator(double lat, double lon, double brg, double dist,
                                                double *dlat, double *dlon);
extern "C" double DistGreatCircle(double slat, double slon, double dlat, double dlon);

extern "C" int GetDatumIndex(const char *str);
extern "C" void MolodenskyTransform (double lat, double lon, double *to_lat, double *to_lon, int from_datum_index, int to_datum_index);

extern "C" void DistanceBearingMercator(double lat0, double lon0, double lat1, double lon1, double *brg, double *dist);


#else
void toDMS(double a, char *bufp, int bufplen);
void toDMM(double a, char *bufp, int bufplen);
int GetDatumIndex(const char *str);
void MolodenskyTransform (double lat, double lon, double *to_lat, double *to_lon, int from_datum_index, int to_datum_index);

#endif





#endif
