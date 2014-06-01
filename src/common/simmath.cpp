/**
**  @file simmath.cpp
*/
/*
**  Copyright (c) 2014, GCBLUE PROJECT
**  All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
**
**  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
**
**  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the 
**     documentation and/or other materials provided with the distribution.
**
**  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from 
**     this software without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
**  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
**  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
**  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
**  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma warning (disable : 4996) // 'strdup' was declared deprecated

#include "simmath.h"
#include "nsNav.h"
#include "tcMapData.h"
#include "common/tcStream.h"
#include "tcGameStream.h"
#include "tcGameObject.h"
#include "tcFloatCompressor.h"
#include "common/tcObjStream.h"



float Add_dB(float x_dB, float y_dB)
{
    if (fabsf(x_dB - y_dB) > 17.0f)
    {
        return (x_dB > y_dB) ? x_dB : y_dB;
    }
    else
    {
        return 10.0f*log10f(powf(10.0f, 0.1f*x_dB) + powf(10.0f, 0.1f*y_dB));
    }
}

void ConformLonLatRad(float& lon_rad, float& lat_rad) 
{
   lon_rad += C_TWOPI * (float(lon_rad < -C_PI) - float(lon_rad >= C_PI));

   //if (lon_rad < -C_PI) {lon_rad += C_TWOPI;}
   //else if (lon_rad >= C_PI) {lon_rad -= C_TWOPI;}

   if (lat_rad > C_PIOVER2) {lat_rad = C_PIOVER2;}
   else if (lat_rad < - C_PIOVER2) {lat_rad = -C_PIOVER2;}
}

void ConformLonLatRad(double& lon_rad, double& lat_rad) 
{
   lon_rad += C_TWOPI * (double(lon_rad < -C_PI) - double(lon_rad >= C_PI));
   //if (lon_rad < -C_PI) {lon_rad += C_TWOPI;}
   //else if (lon_rad >= C_PI) {lon_rad -= C_TWOPI;}

   if (lat_rad > C_PIOVER2) {lat_rad = C_PIOVER2;}
   else if (lat_rad < - C_PIOVER2) {lat_rad = -C_PIOVER2;}
}

void ConformLonLatDeg(float& lon_deg, float& lat_deg) 
{
   lon_deg += 360.0f * (float(lon_deg < -180.0f) - float(lon_deg >= 180.0f));
   //if (lon_deg < -180.0f) {lon_deg += 360.0f;}
   //else if (lon_deg >= 180.0f) {lon_deg -= 360.0f;}

   if (lat_deg > 90.0f) {lat_deg = 90.0f;}
   else if (lat_deg < -90.0f) {lat_deg = -89.9999f;}
}

void ConformLonLatDeg(double& lon_deg, double& lat_deg) 
{
   lon_deg += 360.0 * (double(lon_deg < -180.0) - double(lon_deg >= 180.0));
   //if (lon_deg < -180.0) {lon_deg += 360.0;}
   //else if (lon_deg >= 180.0) {lon_deg -= 360.0;}

   if (lat_deg > 90.0) {lat_deg = 90.0;}
   else if (lat_deg < -90.0) {lat_deg = -89.99999;}
}

void LonLatToStringB(float afLon_deg, float afLat_deg, std::string& s) 
{
    char zBuff[128];
    float deg,min,sec;

    deg = floorf(afLat_deg);
    min = floorf(60.0f*(afLat_deg-deg));
    sec = floorf(60.0f*(60.0f*(afLat_deg-deg)-min));
    sprintf(zBuff,"%03.f:%02.f:%02.f ",deg,min,sec);
    s = zBuff;

    float abs_lon = fabsf(afLon_deg);
    float sign_lon = (afLon_deg < 0) ? -1.0f : 1.0f;

    deg = floorf(abs_lon);
    min = floorf(60.0f*(abs_lon-deg));
    sec = floorf(60.0f*(60.0f*(abs_lon-deg)-min));
    sprintf(zBuff,"%03.f:%02.f:%02.f ",sign_lon*deg,min,sec);
    s += zBuff;
}

void LonLatToString(float afLon_deg, float afLat_deg, tcString& s) 
{
    tcString stemp;
    float deg,min,sec;
    deg = floorf(afLat_deg);
    min = floorf(60.0f*(afLat_deg-deg));
    sec = floorf(60.0f*(60.0f*(afLat_deg-deg)-min));
    s.Format("%03.f:%02.f:%02.f ",deg,min,sec);

    float abs_lon = fabsf(afLon_deg);
    float sign_lon = (afLon_deg < 0) ? -1.0f : 1.0f;

    deg = floorf(abs_lon);
    min = floorf(60.0f*(abs_lon-deg));
    sec = floorf(60.0f*(60.0f*(abs_lon-deg)-min));
    stemp.Format("%03.f:%02.f:%02.f ",sign_lon*deg,min,sec);
    s += stemp;
}


// assumes lon is within [-pi,pi) and lat [-pi/2,pi/2]
int GeoWithinRegion(GeoPoint p, const tcRect *pRegion) 
{ 
   if ((p.mfLat_rad > pRegion->top)||(p.mfLat_rad < pRegion->bottom)) 
   {
       return 0;
   }

   if (pRegion->left <= pRegion->right) 
   {
      return ((p.mfLon_rad >= pRegion->left)&&(p.mfLon_rad <= pRegion->right));
   }
   else 
   {
      return ((p.mfLon_rad >= pRegion->left)||(p.mfLon_rad <= pRegion->right));
   }
}

int AngleWithinRange(float afAngle_rad, float afAngle1_rad, float afAngle2_rad) 
{
	// map angles to -180 to 180, assumes angles are in [-540,540]
	if (afAngle_rad < -C_PI) afAngle_rad += C_TWOPI;
	else if (afAngle_rad >= C_PI) afAngle_rad -= C_TWOPI;

	if (afAngle1_rad < -C_PI) afAngle1_rad += C_TWOPI;
	else if (afAngle1_rad > C_PI) afAngle1_rad -= C_TWOPI;

	if (afAngle2_rad < -C_PI) afAngle2_rad += C_TWOPI;
	else if (afAngle2_rad > C_PI) afAngle2_rad -= C_TWOPI;

	// check if region is wrapped and calc result
	if (afAngle1_rad <= afAngle2_rad) 
	{
		return ((afAngle_rad >= afAngle1_rad)&&(afAngle_rad <= afAngle2_rad));
	}
	else 
	{
		return ((afAngle_rad >= afAngle1_rad)||(afAngle_rad <= afAngle2_rad));
	}
}


/**
* operates in radian longitude, latitude, bearing
*/
bool TriangulateBearings(const tcPoint& p1, float bearing1_rad, const tcPoint& p2, float bearing2_rad,
        tcPoint& result)
{
    result.x = 0;
    result.y = 0;

    // use point 1 as origin
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y; 

	float sin_brg1 = sinf(bearing1_rad);
	float cos_brg1 = cosf(bearing1_rad);
	float sin_brg2 = sinf(bearing2_rad);
	float cos_brg2 = cosf(bearing2_rad);

    float lon_distortion1 = 1.0f / cosf(0.5f*(p1.y+p2.y));
	float lon_distortion2 = lon_distortion1;

    float bx1 = sin_brg1*lon_distortion1;
    float by1 = cos_brg1;

    float bx2 = sin_brg2*lon_distortion2;
    float by2 = cos_brg2;

    float num1 = by2*dx - bx2*dy;
    float num2 = by1*dx - bx1*dy;
    float den = bx1*by2 - bx2*by1;

    //float num2 = (dx*by1 - dy*bx1);
    //float den2 = (bx1*by2 - bx2*by1);


    if (den == 0) return false; // parallel

    float ua = num1 / den; // ua will be negative if bad triangulation (point behind p1)
    
    result.x = p1.x + ua*bx1;
    result.y = p1.y + ua*by1;

	// refine estimate with more accurate lon distortion
    lon_distortion1 = 1.0f / cosf(0.5f*(p1.y+result.y));
	lon_distortion2 = 1.0f / cosf(0.5f*(p2.y+result.y));

	bx1 = sin_brg1*lon_distortion1;
    bx2 = sin_brg2*lon_distortion2;

    num1 = by2*dx - bx2*dy;
    num2 = by1*dx - bx1*dy;
    den = bx1*by2 - bx2*by1;

	ua = num1 / den; // ua will be negative if bad triangulation (point behind p1)
    
    result.x = p1.x + ua*bx1;
    result.y = p1.y + ua*by1;

    bool valid1 = ((num1 > 0) && (den > 0)) || ((num1 < 0) && (den < 0));
    bool valid2 = ((num2 > 0) && (den > 0)) || ((num2 < 0) && (den < 0));

    return valid1 && valid2;
}

/************ tcPoint ********************/
/**
* Offsets point where angle 0 is +y, angle pi/2 is +x
*/
void tcPoint::Offset(float distance, float angle_rad)
{
    x += distance * sinf(angle_rad);
    y += distance * cosf(angle_rad);
}



/******************************* tcGeoRect ********************************/

/**
* @param x longitude in radians
* @param y latitude in radians
* @return true if point (lon,lat) in radians is within
* @return region.
*/
bool tcGeoRect::ContainsPoint(float x, float y) const
{
    GeoPoint p;
    p.Set(x, y, 0);
    return GeoWithinRegion(p, this) != 0;
}

float tcGeoRect::Width() {
   if (right > left) {return right-left;}
   else {return right - left + C_TWOPI;}
}

float tcGeoRect::XCenter() {
   float fAvg;
   if (right > left) {return 0.5f*(right+left);}
   else {
      fAvg = 0.5f*(right + left + C_TWOPI);
      if (fAvg >= C_PI) {fAvg -= C_TWOPI;}
      return fAvg;
   }
}

void tcGeoRect::Offset(float dx, float dy) {
   if (top+dy > C_PIOVER2) {dy=0;}
   else if (bottom+dy <= -C_PIOVER2) {dy=0;}
   Set(left+dx,right+dx,bottom+dy,top+dy);
}

/**
* radian units
*/
void tcGeoRect::Set(float x1,float x2,float y1,float y2) {
   if (x1 < -C_PI) {x1 += C_TWOPI;}
   else if (x1 >= C_PI) {x1 -= C_TWOPI;}
   if (x2 < -C_PI) {x2 += C_TWOPI;}
   else if (x2 >= C_PI) {x2 -= C_TWOPI;}

   if (y1 <= -C_PIOVER2) {
      y2 = (y2-y1) - C_PIOVER2M; 
      y1 = -C_PIOVER2M;
   }
   else if (y1 > C_PIOVER2) {
      y1 = C_PIOVER2 - (y2-y1); 
      y2 = C_PIOVER2;
   }
   if (y2 <= -C_PIOVER2) {
      y2 = (y2-y1) - C_PIOVER2M; 
      y1 = -C_PIOVER2M;
   }
   else if (y2 > C_PIOVER2) {
      y1 = C_PIOVER2 - (y2-y1); 
      y2 = C_PIOVER2;
   }
   left = x1;
   right = x2;
   bottom = y1;
   top = y2;
}

/**
* accepts longitude and latitude arguments in degrees units
*/
void tcGeoRect::SetDegrees(float lon1_deg, float lon2_deg, float lat1_deg, float lat2_deg)
{
    tcGeoRect::Set(C_PIOVER180*lon1_deg, C_PIOVER180*lon2_deg, 
        C_PIOVER180*lat1_deg, C_PIOVER180*lat2_deg);
}

// forces r to be within tcGeoRect, assumes dimensions of r don't exceed tcGeoRect
// dimensions
void tcGeoRect::ApplyBounds(tcGeoRect& r) 
{
    // first handle top and bottom
    if (r.top > top) 
    {
        r.Offset(0, top - r.top); 
    }
    else if (r.bottom < bottom) 
    {
        r.Offset(0, bottom - r.bottom); 
    }   

    // left and right need to handle wrapped case

    float width = Width();
    float rWidth = r.Width();

    float xLeft = (r.left > left) ? r.left - left : r.left - left + C_TWOPI;
    if (xLeft > width)
    {
        r.left = left;
        r.right = left + rWidth;
        if (r.right >= C_PI) r.right -= C_TWOPI;
    }

    float xRight = (r.right > left) ? r.right - left : r.right - left + C_TWOPI;
    if (xRight > width)
    {
        r.right = right;
        r.left = right - rWidth;
        if (r.left < -C_PI) r.left += C_TWOPI;
    }
}



/// @returns true if any part of r is outside of this rect
bool tcGeoRect::IsOutOfBounds(tcGeoRect& r) const
{
    bool boundsAreWrapped = left > right;

    if (!boundsAreWrapped)
    {
        return (r.top > top) || (r.bottom < bottom) || (r.left < left) || (r.left > right) || (r.right > right) || (r.right < left);
    }
    else
    {
        bool leftIn = (r.left >= left)||(r.left <= right);
        bool rightIn = (r.right >= left)||(r.right <= right);

        return (r.top > top) || (r.bottom < bottom) || (!leftIn) || (!rightIn);
    }
}



bool tcGeoRect::operator==(const tcGeoRect& r)
{
    return ((left == r.left)&&(right == r.right)&&
        (top == r.top)&&(bottom == r.bottom));
}

bool tcGeoRect::operator!=(const tcGeoRect& r)
{
    return !(operator==(r));
}

/******************************* tcTerrainInfo *******************************/
void tcTerrainInfo::Clear() 
{
   mfHeight_m = 0;
   lookAheadHeight_m = 0;
   mfLatDatum = 0;
   mfLonDatum = 0;
}

void tcTerrainInfo::Serialize(tcFile& file, bool abLoad) 
{
	wxASSERT(false);
	if (abLoad) 
	{
		file.Read(&mfHeight_m,sizeof(mfHeight_m));
		file.Read(&mfLonDatum,sizeof(mfLonDatum));
		file.Read(&mfLatDatum,sizeof(mfLatDatum));
	}
	else 
	{
		file.Write(&mfHeight_m,sizeof(mfHeight_m));
		file.Write(&mfLonDatum,sizeof(mfLonDatum));
		file.Write(&mfLatDatum,sizeof(mfLatDatum));
    }
}

tcGameStream& tcTerrainInfo::operator>>(tcGameStream& stream)
{
    stream << mfHeight_m;
	stream << lookAheadHeight_m;
    stream << mfLonDatum;
    stream << mfLatDatum;

    return stream;
}

tcGameStream& tcTerrainInfo::operator<<(tcGameStream& stream)
{
    stream >> mfHeight_m;
	stream >> lookAheadHeight_m;
    stream >> mfLonDatum;
    stream >> mfLatDatum;

    return stream;
}

/********************** GeoPoint *************************************/
/**
* Load state from stream
*/
tcStream& GeoPoint::operator<<(tcStream& stream)
{
    stream >> mfLon_rad;
    stream >> mfLat_rad;
    stream >> mfAlt_m;

    return stream;
}

/**
* Save state to stream
*/
tcStream& GeoPoint::operator>>(tcStream& stream)
{
    stream << mfLon_rad;
    stream << mfLat_rad;
    stream << mfAlt_m;

    return stream;
}

const GeoPoint& GeoPoint::Offset(float distance_km, float bearing_rad)
{
    float dist_rad = C_KMTORAD * distance_km;

    mfLon_rad += dist_rad * sinf(bearing_rad) / cosf(mfLat_rad);
    mfLat_rad += dist_rad * cosf(bearing_rad);

    ConformLonLatRad(mfLon_rad, mfLat_rad);

    return *this;
}


GeoPoint::GeoPoint()
: mfLon_rad(0),
  mfLat_rad(0),
  mfAlt_m(0)
{
}


GeoPoint::GeoPoint(double lon_rad, double lat_rad, float alt_m)
: mfLon_rad(lon_rad),
  mfLat_rad(lat_rad),
  mfAlt_m(alt_m)
{
}

GeoPoint::~GeoPoint()
{
}


/******************************* tcKinematics *******************************/

/**
* Calculates closest distance that collider comes to object represented
* by tcKinematics. 
* @param dx east separation in meters in world coordinates
* @param dy north separation in meters in world coordinates
* @param dz vertical separation in meters in world coordinates
* @return time of closest distance in seconds, negative indicates past
*/
float tcKinematics::CalculateCollisionPoint(const tcKinematics& collider, float& dxi, float& dyi, float& dzi)
{
    double dlon = mfLon_rad - collider.mfLon_rad;
    double dlat = mfLat_rad - collider.mfLat_rad;
    
    float dx = C_RADTOM*cosf(mfLat_rad)*((float)dlon);
    float dy = C_RADTOM*((float)dlat);
    float dz = mfAlt_m - collider.mfAlt_m;

    float v = C_KTSTOMPS*mfSpeed_kts;
    float vc = C_KTSTOMPS*collider.mfSpeed_kts;
    float dvz = v*sinf(mfPitch_rad) - vc*sinf(collider.mfPitch_rad);
    float cospitch = cosf(mfPitch_rad);
    float cospitchc = cosf(collider.mfPitch_rad);
    float dvx = v*cospitch*sinf(mfHeading_rad) - vc*cospitchc*sinf(collider.mfHeading_rad);
    float dvy = v*cospitch*cosf(mfHeading_rad) - vc*cospitchc*cosf(collider.mfHeading_rad);

    wxASSERT(dvx*dvx + dvy*dvy + dvz*dvz != 0);

    float tclosest = -(dx*dvx + dy*dvy + dz*dvz) /
        (dvx*dvx + dvy*dvy + dvz*dvz);
    
    dxi = dx + dvx*tclosest;
    dyi = dy + dvy*tclosest;
    dzi = dz + dvz*tclosest;

    return tclosest;
}

/**
* Calculates the ground impact point (lon_rad, lat_rad)
* assuming constant velocity motion to impact.
* This has not been tested.
* 
* @param terrainHeight_m assumed terrain height in meters
* @param lon_rad longitude in radians of impact point
* @param lat_rad latitude in radians of impact point
* @return time of impact in seconds, negative indicates past
*/
float tcKinematics::CalculateGroundImpactPoint(float terrainHeight_m, 
											   double& lon_rad, double& lat_rad)
{

    float dz =  terrainHeight_m - mfAlt_m;
    float v = C_KTSTOMPS*mfSpeed_kts;
    float vz = v*sinf(mfPitch_rad);

	float timpact = dz / vz;

    float cospitch = cosf(mfPitch_rad);
	float k = C_MTORAD * timpact * v * cospitch;
    float dlon = k * sinf(mfHeading_rad) / cosf(mfLat_rad);
    float dlat = k * cosf(mfHeading_rad);
	
	lon_rad = mfLon_rad + dlon;
	lat_rad = mfLat_rad + dlat;

    return timpact;
}

/**
* @return range rate in m/s between this tcKinematics and k
* 3-D calculation
*/
float tcKinematics::CalculateRangeRate(const tcKinematics& k) const
{
    float speed1_mps = C_KTSTOMPS * mfSpeed_kts;
    float vz1 = sinf(mfClimbAngle_rad) * speed1_mps;
    float vxy1 = cosf(mfClimbAngle_rad) * speed1_mps;
    float vx1 = sinf(mfHeading_rad) * vxy1;
    float vy1 = cosf(mfHeading_rad) * vxy1;

    float speed2_mps = C_KTSTOMPS * k.mfSpeed_kts;
    float vz2 = sinf(k.mfClimbAngle_rad) * speed2_mps;
    float vxy2 = cosf(k.mfClimbAngle_rad) * speed2_mps;
    float vx2 = sinf(k.mfHeading_rad) * vxy2;
    float vy2 = cosf(k.mfHeading_rad) * vxy2;

    float dvx = vx1 - vx2;
    float dvy = vy1 - vy2;
    float dvz = vz1 - vz2;

    return sqrtf(dvx*dvx + dvy*dvy + dvz*dvz);
}


/**
* Extrapolates position ahead in time by dt_s (or behind if dt_s < 0)
*/
void tcKinematics::Extrapolate(float dt_s)
{
    double lon_rad;
    double lat_rad;
    float alt_m;

    PredictPosition(dt_s, lon_rad, lat_rad, alt_m);

    mfLon_rad = lon_rad;
    mfLat_rad = lat_rad;
    mfAlt_m = alt_m;
}

/**
* Predicts position ahead by dt_s seconds
*/
void tcKinematics::PredictPosition(float dt_s, 
								   double& lon_rad, double& lat_rad, float& alt_m) const
{
    float v = C_KTSTOMPS*mfSpeed_kts;

    float vz, cospitch;
    if (mfPitch_rad == 0)
    {
        vz = 0;
        cospitch = 1.0f;
    }
    else
    {
        vz = v*sinf(mfPitch_rad);
        cospitch = cosf(mfPitch_rad);
    }

	float k = C_MTORAD * dt_s * v * cospitch;
    float dlon = k * sinf(mfHeading_rad) / cosf(mfLat_rad);
    float dlat = k * cosf(mfHeading_rad);
	
	lon_rad = mfLon_rad + dlon;
	lat_rad = mfLat_rad + dlat;
	alt_m = mfAlt_m + vz * dt_s;

}

/**
* @return bearing rate to track in radians per second
* Ignores altitude difference
* @param range_km range to target
* @param bearing_rad bearing to target
* @param speet_kts target speed
* @param heading_rad target heading
*/
float tcKinematics::BearingRateTo(float range_km, float bearing_rad, float speed_kts, float heading_rad)
{
    float inv_range = 1.0f / range_km;
    float dx = sinf(bearing_rad) * inv_range;
    float dy = cosf(bearing_rad) * inv_range;

    float dvx = C_KTSTOKMPS * (sinf(heading_rad) * speed_kts - 
        sinf(mfHeading_rad) * mfSpeed_kts);
    float dvy = C_KTSTOKMPS * (cosf(heading_rad) * speed_kts - 
        cosf(mfHeading_rad) * mfSpeed_kts);

    return ((dy * dvx) - (dx * dvy));
}


/**
* @returns radian heading to track
*/
float tcKinematics::HeadingToTrack(const tcTrack& track) {
   return nsNav::GCHeadingApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      (float)track.mfLat_rad,(float)track.mfLon_rad);
}
/**
* @returns radian heading to (lat,lon) point
*/
float tcKinematics::HeadingToGeoRad(const GeoPoint *apGeoPoint) const
{
   return nsNav::GCHeadingApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      (float)apGeoPoint->mfLat_rad,(float)apGeoPoint->mfLon_rad);
}

/**
* @returns radian heading to (lat,lon) point
*/
float tcKinematics::HeadingToGeoRad(float lon_rad, float lat_rad) const
{
   return nsNav::GCHeadingApprox_rad((float)mfLat_rad,(float)mfLon_rad,
										lat_rad, lon_rad);
}

/**
* @returns radian heading to (lat,lon) point of kinematics object
*/
float tcKinematics::HeadingToRad(const tcKinematics& k) const
{
   return nsNav::GCHeadingApprox_rad((float)mfLat_rad,(float)mfLon_rad,
										k.mfLat_rad, k.mfLon_rad);
}

/**
* @returns range in km
*/
float tcKinematics::RangeToKm(const tcKinematics& k) const
{
   return C_RADTOKM * nsNav::GCDistanceApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      (float)k.mfLat_rad,(float)k.mfLon_rad);
}
/**
* @return range in km including range due to altitude difference
*/
float tcKinematics::RangeToKmAlt(const tcKinematics& k) const
{
   return C_RADTOKM * nsNav::GCDistanceApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      (float)k.mfLat_rad,(float)k.mfLon_rad,
      mfAlt_m,k.mfAlt_m);
}

float tcKinematics::RangeToKmAlt(const tcTrack& track) const
{
   return C_RADTOKM * nsNav::GCDistanceApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      (float)track.mfLat_rad,(float)track.mfLon_rad,
      mfAlt_m,track.mfAlt_m);
}


float tcKinematics::RangeToKmAlt(float lon_rad, float lat_rad, float alt_m) const
{
   return C_RADTOKM * nsNav::GCDistanceApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      (float)lat_rad,(float)lon_rad,
      mfAlt_m, alt_m);
}

float tcKinematics::RangeToKmAlt(const tcGameObject* obj) const
{
    wxASSERT(obj != 0);
    return RangeToKmAlt(obj->mcKin);
}


float tcKinematics::RangeToKm(const GeoPoint *apGeoPoint) const
{
   return C_RADTOKM * nsNav::GCDistanceApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      apGeoPoint->mfLat_rad,apGeoPoint->mfLon_rad);
}


/**
* @return approximate range in km, altitude difference is neglected
*/
float tcKinematics::RangeToKm(const tcTrack& track) const
{
   float lat_rad = (float)track.mfLat_rad;
   float lon_rad = (float)track.mfLon_rad;
   return C_RADTOKM * nsNav::GCDistanceApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      lat_rad,lon_rad);
}

/**
* @return approximate range in km, altitude difference is neglected
*/
float tcKinematics::RangeToKm(float lon_rad, float lat_rad) const
{
   return C_RADTOKM * nsNav::GCDistanceApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      lat_rad, lon_rad);
}

/**
* @return approximate range in m, altitude difference is neglected
*/
float tcKinematics::RangeToM(float lon_rad, float lat_rad) const
{
   return C_RADTOM * nsNav::GCDistanceApprox_rad((float)mfLat_rad,(float)mfLon_rad,
      lat_rad, lon_rad);
}


/**
* Load state from stream 
* No compression for game stream
*/
tcGameStream& tcKinematics::operator<<(tcGameStream& stream)
{
    stream >> mfLon_rad;
    stream >> mfLat_rad;
    stream >> mfAlt_m;
    stream >> mfHeading_rad;
    stream >> mfClimbAngle_rad;
    stream >> mfYaw_rad;
    stream >> mfPitch_rad;
    stream >> mfRoll_rad;
    stream >> mfSpeed_kts;

    return stream;
}

/**
* Save state to stream
* No compression for game stream
*/
tcGameStream& tcKinematics::operator>>(tcGameStream& stream)
{
    stream << mfLon_rad;
    stream << mfLat_rad;
    stream << mfAlt_m;
    stream << mfHeading_rad;
    stream << mfClimbAngle_rad;
    stream << mfYaw_rad;
    stream << mfPitch_rad;
    stream << mfRoll_rad;
    stream << mfSpeed_kts;

    return stream;
}

/**
* Load state from stream, compression used for update stream
*/
tcUpdateStream& tcKinematics::operator<<(tcUpdateStream& stream)
{
    stream >> mfLon_rad;
    stream >> mfLat_rad;
    stream >> mfAlt_m;
    stream >> tcAngleCompressor(mfHeading_rad);
    stream >> tcAngleCompressor(mfClimbAngle_rad);
    stream >> tcAngleCompressor(mfYaw_rad);
    stream >> tcAngleCompressor(mfPitch_rad);
    stream >> tcAngleCompressor(mfRoll_rad);
    stream >> tcIntervalCompressor(mfSpeed_kts, 0, 4000.0f);

    return stream;
}

/**
* Save state to update stream, compression used for update stream
*/
tcUpdateStream& tcKinematics::operator>>(tcUpdateStream& stream)
{
    stream << mfLon_rad;
    stream << mfLat_rad;
    stream << mfAlt_m;
    stream << tcAngleCompressor(mfHeading_rad);
    stream << tcAngleCompressor(mfClimbAngle_rad);
    stream << tcAngleCompressor(mfYaw_rad);
    stream << tcAngleCompressor(mfPitch_rad);
    stream << tcAngleCompressor(mfRoll_rad);
    stream << tcIntervalCompressor(mfSpeed_kts, 0, 4000.0f); 

    return stream;
}

void tcKinematics::Serialize(tcFile& file, bool abLoad) {
   if (abLoad) {
      file.Read(&mfLon_rad,sizeof(mfLon_rad));
      file.Read(&mfLat_rad,sizeof(mfLat_rad));
      file.Read(&mfAlt_m,sizeof(mfAlt_m));
      file.Read(&mfHeading_rad,sizeof(mfHeading_rad));          
      file.Read(&mfClimbAngle_rad,sizeof(mfClimbAngle_rad));       
      file.Read(&mfYaw_rad,sizeof(mfYaw_rad));
      file.Read(&mfPitch_rad,sizeof(mfPitch_rad));
      file.Read(&mfRoll_rad,sizeof(mfRoll_rad));
      file.Read(&mfSpeed_kts,sizeof(mfSpeed_kts));  
   }
   else {
      file.Write(&mfLon_rad,sizeof(mfLon_rad));
      file.Write(&mfLat_rad,sizeof(mfLat_rad));
      file.Write(&mfAlt_m,sizeof(mfAlt_m));
      file.Write(&mfHeading_rad,sizeof(mfHeading_rad));          
      file.Write(&mfClimbAngle_rad,sizeof(mfClimbAngle_rad));       
      file.Write(&mfYaw_rad,sizeof(mfYaw_rad));
      file.Write(&mfPitch_rad,sizeof(mfPitch_rad));
      file.Write(&mfRoll_rad,sizeof(mfRoll_rad));
      file.Write(&mfSpeed_kts,sizeof(mfSpeed_kts));  
   }
}

/**
* 2009 OCT 03 - Modified this to use GetInterceptData3D code with altitude difference = 0
* Something appeared wrong with previous code when checked in matlab
*/
void tcKinematics::GetInterceptData2D(const tcTrack& track, 
                                      float& rfHeading_rad, float& rfTimeToIntercept) 
{
    float dx,dy,dx2,dy2;
    float vtx,vty,vtx2,vty2; // track velocity components
    float vx,vy,v2;
    float fTrackSpeed_radps, fSpeed_radps;
    float a,b,c,det,k; // quadratic equation coefficients

    dx = (track.mfLon_rad - (float)mfLon_rad)*cosf((float)mfLat_rad);
    dy = track.mfLat_rad - (float)mfLat_rad;

    dx2 = dx*dx;
    dy2 = dy*dy;

    //rfRange_rad = sqrtf(dx2+dy2);

    fTrackSpeed_radps = track.mfSpeed_kts*C_KTSTORADPS;  

    float vtgroundspeed = fTrackSpeed_radps;
    vtx = vtgroundspeed*sinf(track.mfHeading_rad);
    vty = vtgroundspeed*cosf(track.mfHeading_rad);
    vtx2 = vtx*vtx;
    vty2 = vty*vty;

    fSpeed_radps = mfSpeed_kts*C_KTSTORADPS; // ownship speed
    v2 = fSpeed_radps*fSpeed_radps;
    a = dx2 + dy2;
    b = 2.0f*(dx*vtx + dy*vty);
    c = vtx2 + vty2 - v2;
    det = (b*b - 4.0f*a*c);
    if (det >= 0) 
    { 
        k = (-b + sqrtf(det))/(2.0f*a); // may need to check negative sol'n too

        if (k > 0)
        {
            vx = vtx + k*dx;
            vy = vty + k*dy;

            //float vground = sqrtf(vx*vx + vy*vy);
            // negative solution is evasion course

            rfHeading_rad = atan2f(vx,vy);
            //rfHeading_rad = atan2f(dx,dy);
            rfTimeToIntercept = (fabsf(dy)>=fabsf(dx)) ? dy/(vy-vty) : dx/(vx-vtx);
            return;
        }
    }

    // no intercept solution exists, just head toward target
    rfHeading_rad = atan2f(dx,dy);
    rfTimeToIntercept = 9999.0f;
    return;
     
}

void tcKinematics::GetInterceptData3D(const tcTrack& track, float& rfHeading_rad, 
                               float& rfClimbAngle_rad, float& rfTimeToIntercept, float& rfRange_rad) 
{
   float dx,dy,dz,dx2,dy2,dz2;
   float vtx,vty,vtz,vtx2,vty2,vtz2; // track velocity components
   float vx,vy,vz,v2;
   float fTrackSpeed_radps, fSpeed_radps;
   float a,b,c,det,k; // quadratic equation coefficients

   dx = (track.mfLon_rad - (float)mfLon_rad)*cosf((float)mfLat_rad);
   dy = track.mfLat_rad - (float)mfLat_rad;
   dz = (track.mfAlt_m - mfAlt_m)*C_MTORAD;
   dx2 = dx*dx;
   dy2 = dy*dy;
   dz2 = dz*dz;
   rfRange_rad = sqrtf(dx2+dy2+dz2);
   
   fTrackSpeed_radps = track.mfSpeed_kts*C_KTSTORADPS;  
   vtz = sinf(track.mfClimbAngle_rad)*fTrackSpeed_radps; 
   float vtgroundspeed = cosf(track.mfClimbAngle_rad)*fTrackSpeed_radps;
   vtx = vtgroundspeed*sinf(track.mfHeading_rad);
   vty = vtgroundspeed*cosf(track.mfHeading_rad);
   vtx2 = vtx*vtx;
   vty2 = vty*vty;
   vtz2 = vtz*vtz;
   fSpeed_radps = mfSpeed_kts*C_KTSTORADPS; // ownship speed
   v2 = fSpeed_radps*fSpeed_radps;
   a = dx2 + dy2 + dz2;
   b = 2.0f*(dx*vtx + dy*vty + dz*vtz);
   c = vtx2 + vty2 + vtz2 - v2;
   det = (b*b - 4.0f*a*c);
   if (det < 0) {
      det = b*b + 4.0f*a*0.1f*v2; // assume slightly faster
   } // no solution exists
   k = (-b + sqrtf(det))/(2.0f*a); // may need to check negative sol'n too, check for k < 0?? 3 OCT
   vx = vtx + k*dx;
   vy = vty + k*dy;
   vz = vtz + k*dz;
   float vground = sqrtf(vx*vx + vy*vy);
   // negative solution is evasion course

   rfHeading_rad = atan2f(vx,vy);
   //rfHeading_rad = atan2f(dx,dy);
   rfTimeToIntercept = (fabsf(dy)>=fabsf(dx)) ? dy/(vy-vty) : dx/(vx-vtx);
   rfClimbAngle_rad = atanf(vz/vground);
}

/**
* Set rpGeoPoint to point at afBearing_deg and afRange_km relative to
* current location of this tcKinematics object
* altitude isn't changed, has issues off of equator like everything else :<
*/
void  tcKinematics::SetRelativeGeo(GeoPoint& rpGeoPoint, float afBearing_rad, float afRange_km) {
   nsNav::OffsetApprox(mfLat_rad, mfLon_rad, rpGeoPoint.mfLat_rad, rpGeoPoint.mfLon_rad, 
      afBearing_rad,afRange_km*C_KMTORAD);
}

