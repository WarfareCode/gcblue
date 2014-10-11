 //////////////////////////////////////////////////////////////////////////
// TrueVision3D 6.5 Types Declarations
// C++ headers/core header.
//////////////////////////////////////////////////////////////////////////


#ifndef TVTYPESHEADER
#define TVTYPESHEADER

#include <math.h>

#ifdef GCC
#include <stdlib.h>
#include <string.h>
#endif 

#ifdef TV3D_LIB
#ifdef GCC
	#define EXPORTCLASS __declspec(dllexport)
	#define EXPORTFUNC __declspec(dllexport)
#else
	#define EXPORTCLASS 
	#define EXPORTFUNC
#endif
#elif TV3D_EXPORT 
	#define EXPORTCLASS __declspec(dllexport)
	#define EXPORTFUNC __declspec(dllexport)
#else
	#define EXPORTCLASS __declspec(dllimport)
	#define EXPORTFUNC __declspec(dllimport)

#endif


typedef struct cTV_TEXTUREFONT_CHAR
{
	int iAsciiChar;
	float fX1;
	float fY1;
	float fX2;
	float fY2;
} cTV_TEXTUREFONT_CHAR;

typedef enum cCONST_TV_LIGHTSHADOW
{
	cTV_LIGHTSHADOW_NONE = 0,
	cTV_LIGHTSHADOW_PROJECTIVE_GLOBAL = 1,
	cTV_LIGHTSHADOW_SHADOWMAP_GLOBAL = 2,
	cTV_LIGHTSHADOW_PROJECTIVE_OBJECT = 3
};

typedef enum cCONST_TV_RENDERSURFACEFORMAT
{
	cTV_TEXTUREFORMAT_DEFAULT = 0,
	cTV_TEXTUREFORMAT_A8R8G8B8 = 21,
	cTV_TEXTUREFORMAT_X8R8G8B8 = 22,
	cTV_TEXTUREFORMAT_A4R4G4B4 = 26,
	cTV_TEXTUREFORMAT_R5G6B5 = 23,
	cTV_TEXTUREFORMAT_HDR_FLOAT16 = 113,
	cTV_TEXTUREFORMAT_HDR_FLOAT32 = 116, 
	cTV_TEXTUREFORMAT_HDR_R32F = 114,
	cTV_TEXTUREFORMAT_HDR_G32B32F = 115,
	cTV_TEXTUREFORMAT_HDR_G16B16F = 112,
	cTV_TEXTUREFORMAT_NONE = 999
} cCONST_TV_RENDERSURFACEFORMAT;

typedef enum cCONST_TV_SHADERMODEL
{
	cTV_SHADERMODEL_NOSHADER = 0,
	cTV_SHADERMODEL_1_1 = 1,
	cTV_SHADERMODEL_2_0 = 2,
	cTV_SHADERMODEL_3_0 = 3,
	cTV_SHADERMODEL_BEST = 4
} cCONST_TV_SHADERMODEL;

typedef enum cCONST_TV_NODETYPE
{
	cTV_NODETYPE_NODE = 0,
	cTV_NODETYPE_MESH = 1,
	cTV_NODETYPE_ACTOR = 2,
	cTV_NODETYPE_CAMERA = 3,
	cTV_NODETYPE_LIGHT = 4,
	cTV_NODETYPE_PARTICLEEMITTER = 5,

	cTV_NODETYPE_NONE = 99
} cCONST_TV_NODETYPE;

typedef enum cCONST_TV_ATTRACTORVELOCITYPOWER
{
	cTV_ATTRACTORPOWER_CONSTANT = 0,
	cTV_ATTRACTORPOWER_VELOCITYLINEAR = 1,
	cTV_ATTRACTORPOWER_VELOCITYQUADRATIC = 2,
	cTV_ATTRACTORPOWER_VELOCITYTHIRDORDER = 3
} cCONST_TV_ATTRACTORVELOCITYPOWER;

typedef enum cCONST_TV_SHADERPARAMETERTYPE
{
	cTV_SHADERPARAMETER_FLOAT = 0,
	cTV_SHADERPARAMETER_VECTOR = 1,
	cTV_SHADERPARAMETER_BOOL = 2,
	cTV_SHADERPARAMETER_MATRIX = 3,
	cTV_SHADERPARAMETER_TEXTURE = 4,
	cTV_SHADERPARAMETER_STRING = 5,
	cTV_SHADERPARAMETER_INTEGER = 6,
	cTV_SHADERPARAMETER_UNKNOWN = 7
} cCONST_TV_SHADERPARAMETERTYPE;



typedef struct cTV_3DQUATERNION
{
	union {
		struct { float x,y,z,w;};
		float q[4];
	};

	cTV_3DQUATERNION()
	{
		x = 0.0f;
		y = 0.0f;
		z = 1.0f;
		w = 0.0f;
	}
	cTV_3DQUATERNION(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}
} cTV_3DQUATERNION;

typedef enum cCONST_TV_PHYSICSBODY_BOUNDING
{
	cTV_BODY_BOX = 0,
	cTV_BODY_SPHERE = 1,
	cTV_BODY_CYLINDER = 2,
	cTV_BODY_NONE = 3,
	cTV_BODY_CONVEXHULL = 4
} cCONST_TV_PHYSICSBODY_BOUNDING;


typedef enum cCONST_TV_LICENSEMODE
{
	cTV_LICENSE_SHAREWARE = 1,
	cTV_LICENSE_COMMERCIAL = 2,
	cTV_LICENSE_MULTIPRODUCT = 3
} cCONST_TV_LICENSEMODE;


typedef enum cCONST_TV_WATERMARKPLACE
{
	cTV_WATERMARK_TOPLEFT = 0,
	cTV_WATERMARK_BOTTOMRIGHT = 1,
	cTV_WATERMARK_TOPRIGHT = 2,
	cTV_WATERMARK_BOTTOMLEFT = 3
} cCONST_TV_WATERMARKPLACE;

typedef enum cCONST_TV_EMITTERTYPE
{
	cTV_EMITTER_POINTSPRITE = 0,
	cTV_EMITTER_BILLBOARD = 1,
	cTV_EMITTER_MINIMESH =  2
};

typedef enum cCONST_TV_EMITTERSHAPE
{
	cTV_EMITTERSHAPE_POINT = 0,
	cTV_EMITTERSHAPE_SPHEREVOLUME = 1,
	cTV_EMITTERSHAPE_BOXVOLUME = 2,
	cTV_EMITTERSHAPE_SPHERESURFACE = 3,
	cTV_EMITTERSHAPE_BOXSURFACE = 4
};

typedef enum cCONST_TV_GAMECONTROLLERTYPE
{
 cTV_GAMECONTROLLERTYPE_DEVICE =          0x11,
 cTV_GAMECONTROLLERTYPE_MOUSE  =          0x12,
 cTV_GAMECONTROLLERTYPE_KEYBOARD =        0x13,
 cTV_GAMECONTROLLERTYPE_JOYSTICK  =       0x14,
 cTV_GAMECONTROLLERTYPE_GAMEPAD    =      0x15,
 cTV_GAMECONTROLLERTYPE_DRIVING     =     0x16,
 cTV_GAMECONTROLLERTYPE_FLIGHT       =    0x17,
 cTV_GAMECONTROLLERTYPE_1STPERSON     =   0x18,
 cTV_GAMECONTROLLERTYPE_DEVICECTRL    =   0x19,
 cTV_GAMECONTROLLERTYPE_SCREENPOINTER  =  0x1A,
 cTV_GAMECONTROLLERTYPE_REMOTE         =  0x1B,
 cTV_GAMECONTROLLERTYPE_SUPPLEMENTAL   =  0x1C
};

#define cTV_GAMECONTROLLERSUBTYPE_LIMITEDGAMESUBTYPE               1

#define cTV_GAMECONTROLLERSUBTYPE_JOYSTICK_LIMITED                  1
#define cTV_GAMECONTROLLERSUBTYPE_JOYSTICK_STANDARD                 2

#define cTV_GAMECONTROLLERSUBTYPE_GAMEPAD_LIMITED                   1
#define cTV_GAMECONTROLLERSUBTYPE_GAMEPAD_STANDARD                  2
#define cTV_GAMECONTROLLERSUBTYPE_GAMEPAD_TILT                      3

#define cTV_GAMECONTROLLERSUBTYPE_DRIVING_LIMITED                   1
#define cTV_GAMECONTROLLERSUBTYPE_DRIVING_COMBINEDPEDALS            2
#define cTV_GAMECONTROLLERSUBTYPE_DRIVING_DUALPEDALS                3
#define cTV_GAMECONTROLLERSUBTYPE_DRIVING_THREEPEDALS               4
#define cTV_GAMECONTROLLERSUBTYPE_DRIVING_HANDHELD                  5

#define cTV_GAMECONTROLLERSUBTYPE_FLIGHT_LIMITED                    1
#define cTV_GAMECONTROLLERSUBTYPE_FLIGHT_STICK                      2
#define cTV_GAMECONTROLLERSUBTYPE_FLIGHT_YOKE                       3
#define cTV_GAMECONTROLLERSUBTYPE_FLIGHT_RC                         4

#define cTV_GAMECONTROLLERSUBTYPE_1STPERSON_LIMITED                 1
#define cTV_GAMECONTROLLERSUBTYPE_1STPERSON_UNKNOWN                 2
#define cTV_GAMECONTROLLERSUBTYPE_1STPERSON_SIXDOF                  3
#define cTV_GAMECONTROLLERSUBTYPE_1STPERSON_SHOOTER                 4

#define cTV_GAMECONTROLLERSUBTYPE_SCREENPTR_UNKNOWN                 2
#define cTV_GAMECONTROLLERSUBTYPE_SCREENPTR_LIGHTGUN                3
#define cTV_GAMECONTROLLERSUBTYPE_SCREENPTR_LIGHTPEN                4
#define cTV_GAMECONTROLLERSUBTYPE_SCREENPTR_TOUCH                   5

#define cTV_GAMECONTROLLERSUBTYPE_REMOTE_UNKNOWN                    2

#define cTV_GAMECONTROLLERSUBTYPE_DEVICECTRL_UNKNOWN                2
#define cTV_GAMECONTROLLERSUBTYPE_DEVICECTRL_COMMSSELECTION         3
#define cTV_GAMECONTROLLERSUBTYPE_DEVICECTRL_COMMSSELECTION_HARDWIRED 4

#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_UNKNOWN              2
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_2NDHANDCONTROLLER    3
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_HEADTRACKER          4
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_HANDTRACKER          5
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_SHIFTSTICKGATE       6
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_SHIFTER              7
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_THROTTLE             8
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_SPLITTHROTTLE        9
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_COMBINEDPEDALS      10
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_DUALPEDALS          11
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_THREEPEDALS         12
#define cTV_GAMECONTROLLERSUBTYPE_SUPPLEMENTAL_RUDDERPEDALS        13

typedef enum cCONST_TV_LAYER
{
	cTV_LAYER_0 = 0,
	cTV_LAYER_1 = 1,
	cTV_LAYER_2 = 2,
	cTV_LAYER_3 = 3,
	cTV_LAYER_4 = 4,
	cTV_LAYER_5 = 5,
	cTV_LAYER_6 = 6,
	cTV_LAYER_7 = 7,
	cTV_LAYER_LIGHTMAP = 128,
	cTV_LAYER_HEIGHTMAP = 129,
	cTV_LAYER_BASETEXTURE = 130,
	cTV_LAYER_DETAILMAP = 131,
	cTV_LAYER_NORMALMAP = 132,
	cTV_LAYER_BUMPMAP = 133,
	cTV_LAYER_SPECULARMAP = 134,
	cTV_LAYER_EMISSIVE = 135
};

typedef enum cCONST_TV_LAYERMODE
{
	cTV_LAYERMODE_MODULATE = 0,
	cTV_LAYERMODE_ADD = 1,
	cTV_LAYERMODE_ADDSIGNED = 2,
	cTV_LAYERMODE_MODULATE2X = 3,
	cTV_LAYERMODE_MODULATESELECTCURRENTALPHA = 4,
	cTV_LAYERMODE_MODULATESELECTNEWALPHA = 5,
	cTV_LAYERMODE_DISABLE = 99
};

typedef enum cCONST_TV_IMAGEFORMAT
{
	cTV_IMAGE_BMP = 0,
	cTV_IMAGE_DDS = 4,
	cTV_IMAGE_JPG = 1,
	cTV_IMAGE_PNG = 3,
	cTV_IMAGE_HDR = 7,
	cTV_IMAGE_DXT1 = 10,
	cTV_IMAGE_DXT3 = 11,
	cTV_IMAGE_DXT5 = 12,
	cTV_IMAGE_TVT = 99
};


typedef enum cCONST_TV_ACTORMODE
{
	cTV_ACTORMODE_SHADER = 0,
	cTV_ACTORMODE_BLENDING = 1,
	cTV_ACTORMODE_CPU = 2,
	cTV_ACTORMODE_FASTEST = 3
} cCONST_TV_ACTORMODE;
 
typedef enum cCONST_TV_LIGHTINGMODE
{
	cTV_LIGHTING_NONE = 0,
	cTV_LIGHTING_NORMAL = 1,
	cTV_LIGHTING_MANAGED = 2,
	cTV_LIGHTING_BUMPMAPPING_TANGENTSPACE = 4,
	cTV_LIGHTING_OFFSETBUMPMAPPING_TANGENTSPACE = 5,
	cTV_LIGHTING_PERVERTEX_PRT = 6
} cCONST_TV_LIGHTINGMODE;

typedef struct cTV_SVERTEX
{
	union 
	{
		struct { float x,y,z,nx,ny,nz,tu,tv; };
		float v[8];
	};

	cTV_SVERTEX()
	{

	}
	cTV_SVERTEX(float fX, float fY, float fZ, float fNx, float fNy, float fNz, float fTu, float fTv)
	{
		x = fX;
		y = fY;
		z = fZ;
		nx = fNx;
		ny = fNy;
		nz = fNz;
		tu = fTu;
		tv = fTv;
	}
} cTV_SVERTEX;

typedef struct cTV_2DVECTOR
{
	union
	{
		struct {float x,y;};
		float v[2];
	};

	cTV_2DVECTOR()
	{
		x = 0;
		y = 0;
	}
	cTV_2DVECTOR(float fX, float fY)
	{
		x = fX;
		y = fY;
	} 


	float cTV_2DVECTOR::Dot(const cTV_2DVECTOR& v)
	{
		return x*v.x + y*v.y;
	}

	float cTV_2DVECTOR::Length()
	{
		return sqrtf(this->Dot(*this));
	}

	cTV_2DVECTOR
		cTV_2DVECTOR::operator + () const
	{
		return *this;
	}

	cTV_2DVECTOR
		cTV_2DVECTOR::operator - () const
	{
		return cTV_2DVECTOR(-x, -y);
	}

	cTV_2DVECTOR
		cTV_2DVECTOR::operator + ( const cTV_2DVECTOR& v ) const
	{
		return cTV_2DVECTOR(x + v.x, y + v.y);
	}

	cTV_2DVECTOR
		cTV_2DVECTOR::operator - ( const cTV_2DVECTOR& v ) const
	{
		return cTV_2DVECTOR(x - v.x, y - v.y);
	}

	cTV_2DVECTOR
		cTV_2DVECTOR::operator * ( float f ) const
	{
		return cTV_2DVECTOR(x * f, y * f);
	}

	cTV_2DVECTOR
		cTV_2DVECTOR::operator / ( float f ) const
	{
		float fInv = 1.0f / f;
		return cTV_2DVECTOR(x * fInv, y * fInv);
	}


	cTV_2DVECTOR& cTV_2DVECTOR::operator += ( const cTV_2DVECTOR& v)
	{
		x += v.x;
		y += v.y;
		return *this;

	}
	cTV_2DVECTOR& cTV_2DVECTOR::operator -= ( const cTV_2DVECTOR& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;

	}
	cTV_2DVECTOR& cTV_2DVECTOR::operator *= ( float f )
	{
		x *= f;
		y *= f;
		return *this;

	}
	cTV_2DVECTOR& cTV_2DVECTOR::operator /= ( float f )
	{
		float fInv = 1.0f / f;
		x *= fInv;
		y *= fInv;
		return *this;

	}

	bool cTV_2DVECTOR::operator == ( const cTV_2DVECTOR& v ) const
	{
		return x == v.x && y == v.y ;
	}

	bool cTV_2DVECTOR::operator != ( const cTV_2DVECTOR& v ) const
	{
		return x != v.x || y != v.y ;
	}


} cTV_2DVECTOR;

typedef struct cTV_CUSTOM2DVERTEX
{
	float x,y;
	unsigned int color;
	float tu, tv;
	float tu1, tv1;
	float tu2, tv2;
	float tu3, tv3;
} cTV_CUSTOM2DVERTEX;

typedef struct cTV_3DVECTOR
{
	union {
		struct { float x,y,z;};
		float v[3];
	};


	cTV_3DVECTOR()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	cTV_3DVECTOR(float fx, float fy, float fz)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	float cTV_3DVECTOR::Length()
	{
		return sqrtf(this->Dot(*this));
	}



	// unary operators
	 cTV_3DVECTOR
		cTV_3DVECTOR::operator + () const
	{
		return *this;
	}

	cTV_3DVECTOR
		cTV_3DVECTOR::operator - () const
	{
		return cTV_3DVECTOR(-x, -y, -z);
	}


	// binary operators

	float cTV_3DVECTOR::Dot(const cTV_3DVECTOR& v)
	{
		return x*v.x + y*v.y + z*v.z;
	}

	cTV_3DVECTOR cTV_3DVECTOR::Cross(const cTV_3DVECTOR& v)
	{
		cTV_3DVECTOR vect;
		vect.x = y*v.z-z*v.y;
		vect.y = -(x*v.z-z*v.x);
		vect.z = x*v.y-y*v.x;
		return vect;
	}

	 cTV_3DVECTOR
		cTV_3DVECTOR::operator + ( const cTV_3DVECTOR& v ) const
	{
		return cTV_3DVECTOR(x + v.x, y + v.y, z + v.z);
	}

	cTV_3DVECTOR
		cTV_3DVECTOR::operator - ( const cTV_3DVECTOR& v ) const
	{
		return cTV_3DVECTOR(x - v.x, y - v.y, z - v.z);
	}

	 cTV_3DVECTOR
		cTV_3DVECTOR::operator * ( float f ) const
	{
		return cTV_3DVECTOR(x * f, y * f, z * f);
	}

	 cTV_3DVECTOR
		cTV_3DVECTOR::operator / ( float f ) const
	{
		float fInv = 1.0f / f;
		return cTV_3DVECTOR(x * fInv, y * fInv, z * fInv);
	}


	cTV_3DVECTOR& cTV_3DVECTOR::operator += ( const cTV_3DVECTOR& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;

	}
	cTV_3DVECTOR& cTV_3DVECTOR::operator -= ( const cTV_3DVECTOR& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	cTV_3DVECTOR& cTV_3DVECTOR::operator *= ( float f )
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	cTV_3DVECTOR& cTV_3DVECTOR::operator /= ( float f )
	{
		float fInv = 1.0f / f;
		x *= fInv;
		y *= fInv;
		z *= fInv;
		return *this;
	}

	bool cTV_3DVECTOR::operator == ( const cTV_3DVECTOR& v ) const
	{
		return x == v.x && y == v.y && z == v.z;
	}

	bool cTV_3DVECTOR::operator != ( const cTV_3DVECTOR& v ) const
	{
		return x != v.x || y != v.y || z != v.z;
	}

    /// Dewitt added
	void cTV_3DVECTOR::set(float fx, float fy, float fz)
	{
		x = fx;
		y = fy;
		z = fz;
	}

} cTV_3DVECTOR ;

typedef struct cTV_4DVECTOR
{

	union
	{
		struct { float x,y,z,w; }; // note w is after all 
		float v[4];
	};
	
	cTV_4DVECTOR()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	cTV_4DVECTOR(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}
	cTV_4DVECTOR(cTV_3DVECTOR* vVec3, float fw )
	{
		x = vVec3->x;
		y = vVec3->y;
		z = vVec3->z;
		w = fw;
	}

	

	cTV_4DVECTOR&
		cTV_4DVECTOR::operator /= ( float f )
	{
		float fInv = 1.0f / f;
		x *= fInv;
		y *= fInv;
		z *= fInv;
		w *= fInv;
		return *this;
	}


	// unary operators
	cTV_4DVECTOR
		cTV_4DVECTOR::operator + () const
	{
		return *this;
	}

	cTV_4DVECTOR
		cTV_4DVECTOR::operator - () const
	{
		return cTV_4DVECTOR(-x, -y, -z, -w);
	}


	// binary operators
	float cTV_4DVECTOR::Dot(const cTV_4DVECTOR& v)
	{
		return x*v.x + y*v.y + z*v.z + w*v.w;
	}
	float cTV_4DVECTOR::Length()
	{
		return sqrtf(this->Dot(*this));
	}
	

	cTV_4DVECTOR
		cTV_4DVECTOR::operator + ( const cTV_4DVECTOR& v ) const
	{
		return cTV_4DVECTOR(x + v.x, y + v.y, z + v.z , w + v.w);
	}

	cTV_4DVECTOR
		cTV_4DVECTOR::operator - ( const cTV_4DVECTOR& v ) const
	{
		return cTV_4DVECTOR(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	cTV_4DVECTOR
		cTV_4DVECTOR::operator * ( float f ) const
	{
		return cTV_4DVECTOR(x * f, y * f, z * f, w *f );
	}

	cTV_4DVECTOR
		cTV_4DVECTOR::operator / ( float f ) const
	{
		float fInv = 1.0f / f;
		return cTV_4DVECTOR(x * fInv, y * fInv, z * fInv, w* fInv);
	}

	cTV_4DVECTOR& cTV_4DVECTOR::operator += ( const cTV_4DVECTOR& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;

	}
	cTV_4DVECTOR& cTV_4DVECTOR::operator -= ( const cTV_4DVECTOR& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;

	}
	cTV_4DVECTOR& cTV_4DVECTOR::operator *= ( float f )
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;

	}


	bool cTV_4DVECTOR::operator == ( const cTV_4DVECTOR& v ) const
	{
		return x == v.x && y == v.y && z == v.z && w == v.w ;
	}

	bool cTV_4DVECTOR::operator != ( const cTV_4DVECTOR& v ) const
	{
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}
    
    /// Dewitt added
	void cTV_4DVECTOR::set(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}
	/// end Dewitt added 
    
} cTV_4DVECTOR ;


typedef struct cTV_3DMATRIX
{
	
	union {
		struct {
				float m11,m12,m13,m14;
				float m21,m22,m23,m24;
				float m31,m32,m33,m34;
				float m41,m42,m43,m44;		};
		float m[4][4];
	};

	cTV_3DMATRIX()
	{
		m11 = 0.0f;
		m12 = 0.0f;
		m13 = 0.0f;
		m14 = 0.0f;
		
		m21 = 0.0f;
		m22 = 0.0f;
		m23 = 0.0f;
		m24 = 0.0f;

		m31 = 0.0f;
		m32 = 0.0f;
		m33 = 0.0f;
		m34 = 0.0f;

		m41 = 0.0f;
		m42 = 0.0f;
		m43 = 0.0f;
		m44 = 0.0f;
	}
	cTV_3DMATRIX(float fm11, float fm12, float fm13, float fm14,
				float fm21, float fm22, float fm23, float fm24,
				float fm31, float fm32, float fm33, float fm34,
				float fm41, float fm42, float fm43, float fm44)
	{
		   this->m11 = fm11;
		   this->m12 = fm12;
		   this->m13 = fm13;
		   this->m14 = fm14;
		   this->m21 = fm21;
		   this->m22 = fm22;
		   this->m23 = fm23;
		   this->m24 = fm24;
		   this->m31 = fm31;
		   this->m32 = fm32;
		   this->m33 = fm33;
		   this->m34 = fm34;
		   this->m41 = fm41;
		   this->m42 = fm42;
		   this->m43 = fm43;
		   this->m44 = fm44;
	}

	cTV_3DMATRIX&
		cTV_3DMATRIX::operator += ( const cTV_3DMATRIX& mat )
	{
		m11 += mat.m11; m12 += mat.m12; m13 += mat.m13; m14 += mat.m14;
		m21 += mat.m21; m22 += mat.m22; m23 += mat.m23; m24 += mat.m24;
		m31 += mat.m31; m32 += mat.m32; m33 += mat.m33; m34 += mat.m34;
		m41 += mat.m41; m42 += mat.m42; m43 += mat.m43; m44 += mat.m44;
		return *this;
	}

	cTV_3DMATRIX&
		cTV_3DMATRIX::operator -= (cTV_3DMATRIX& mat )
	{
		m11 -= mat.m11; m12 -= mat.m12; m13 -= mat.m13; m14 -= mat.m14;
		m21 -= mat.m21; m22 -= mat.m22; m23 -= mat.m23; m24 -= mat.m24;
		m31 -= mat.m31; m32 -= mat.m32; m33 -= mat.m33; m34 -= mat.m34;
		m41 -= mat.m41; m42 -= mat.m42; m43 -= mat.m43; m44 -= mat.m44;
		return *this;
	}

	cTV_3DMATRIX&
		cTV_3DMATRIX::operator *= ( float f )
	{
		m11 *= f; m12 *= f; m13 *= f; m14 *= f;
		m21 *= f; m22 *= f; m23 *= f; m24 *= f;
		m31 *= f; m32 *= f; m33 *= f; m34 *= f;
		m41 *= f; m42 *= f; m43 *= f; m44 *= f;
		return *this;
	}

	cTV_3DMATRIX
		cTV_3DMATRIX::operator *= ( const cTV_3DMATRIX& mat ) const
	{
		return *this * mat;
	}

	cTV_3DMATRIX&
		cTV_3DMATRIX::operator /= ( float f )
	{
		float fInv = 1.0f / f;
		m11 *= fInv; m12 *= fInv; m13 *= fInv; m14 *= fInv;
		m21 *= fInv; m22 *= fInv; m23 *= fInv; m24 *= fInv;
		m31 *= fInv; m32 *= fInv; m33 *= fInv; m34 *= fInv;
		m41 *= fInv; m42 *= fInv; m43 *= fInv; m44 *= fInv;
		return *this;
	}


	// unary operators
	cTV_3DMATRIX
		cTV_3DMATRIX::operator + () const
	{
		return *this;
	}

	 cTV_3DMATRIX
		cTV_3DMATRIX::operator - () const
	{
		return cTV_3DMATRIX(-m11, -m12, -m13, -m14,
			-m21, -m22, -m23, -m24,
			-m31, -m32, -m33, -m34,
			-m41, -m42, -m43, -m44);
	}


	// binary operators
	 cTV_3DMATRIX
		cTV_3DMATRIX::operator * ( const cTV_3DMATRIX& mat ) const
	{
		  cTV_3DMATRIX res;

		  for(int i = 0; i < 4; i++)
		  {
			  for(int j = 0; j < 4; j++)
			  {
				  for(int k = 0; k < 4; k++)
				  {
						res.m[i][j] += m[i][k] * mat.m[k][j];
				  }

			  }
		  }
		  return res;
	}

	 cTV_3DMATRIX
		cTV_3DMATRIX::operator + ( const cTV_3DMATRIX& mat ) const
	{
		return cTV_3DMATRIX(m11 + mat.m11, m12 + mat.m12, m13 + mat.m13, m14 + mat.m14,
			m21 + mat.m21, m22 + mat.m22, m23 + mat.m23, m24 + mat.m24,
			m31 + mat.m31, m32 + mat.m32, m33 + mat.m33, m34 + mat.m34,
			m41 + mat.m41, m42 + mat.m42, m43 + mat.m43, m44 + mat.m44);
	}

	cTV_3DMATRIX
		cTV_3DMATRIX::operator - ( const cTV_3DMATRIX& mat ) const
	{
		return cTV_3DMATRIX(m11 - mat.m11, m12 - mat.m12, m13 - mat.m13, m14 - mat.m14,
			m21 - mat.m21, m22 - mat.m22, m23 - mat.m23, m24 - mat.m24,
			m31 - mat.m31, m32 - mat.m32, m33 - mat.m33, m34 - mat.m34,
			m41 - mat.m41, m42 - mat.m42, m43 - mat.m43, m44 - mat.m44);
	}

	cTV_3DMATRIX
		cTV_3DMATRIX::operator * ( float f ) const
	{
		return cTV_3DMATRIX(m11 * f, m12 * f, m13 * f, m14 * f,
			m21 * f, m22 * f, m23 * f, m24 * f,
			m31 * f, m32 * f, m33 * f, m34 * f,
			m41 * f, m42 * f, m43 * f, m44 * f);
	}

	cTV_3DMATRIX
		cTV_3DMATRIX::operator / ( float f ) const
	{
		float fInv = 1.0f / f;
		return cTV_3DMATRIX(m11 * fInv, m12 * fInv, m13 * fInv, m14 * fInv,
			m21 * fInv, m22 * fInv, m23 * fInv, m24 * fInv,
			m31 * fInv, m32 * fInv, m33 * fInv, m34 * fInv,
			m41 * fInv, m42 * fInv, m43 * fInv, m44 * fInv);
	}

	cTV_3DVECTOR ColVec3(int iIndex)
	{
		switch(iIndex)
		{
		case 0:
			return cTV_3DVECTOR(m11,m21,m31);
		case 1:
			return cTV_3DVECTOR(m12,m22,m32);
		case 2:
			return cTV_3DVECTOR(m13,m23,m33);
		case 3:
			return cTV_3DVECTOR(m14,m24,m34);
		default:
			return cTV_3DVECTOR(0,0,0);
		}
	}

	cTV_4DVECTOR ColVec4(int iIndex)
	{
		switch(iIndex)
		{
		case 0:
			return cTV_4DVECTOR(m11,m21,m31,m41);
		case 1:
			return cTV_4DVECTOR(m12,m22,m32,m42);
		case 2:
			return cTV_4DVECTOR(m13,m23,m33,m43);
		case 3:
			return cTV_4DVECTOR(m14,m24,m34,m44);
		default:
			return cTV_4DVECTOR(0,0,0,0);
		}
	}


	cTV_3DVECTOR RowVec3(int iIndex)
	{
		switch(iIndex)
		{
		case 0:
			return cTV_3DVECTOR(m11,m12,m13);
		case 1:
			return cTV_3DVECTOR(m21,m22,m23);
		case 2:
			return cTV_3DVECTOR(m31,m32,m33);
		case 3:
			return cTV_3DVECTOR(m41,m42,m43);
		default:
			return cTV_3DVECTOR(0,0,0);
		}
	}

	cTV_4DVECTOR RowVec4(int iIndex)
	{
		switch(iIndex)
		{
		case 0:
			return cTV_4DVECTOR(m11,m12,m13,m14);
		case 1:
			return cTV_4DVECTOR(m21,m22,m23,m24);
		case 2:
			return cTV_4DVECTOR(m31,m32,m33,m34);
		case 3:
			return cTV_4DVECTOR(m41,m42,m43,m44);
		default:
			return cTV_4DVECTOR(0,0,0,0);
		}
	}



} cTV_3DMATRIX;

typedef struct cTV_COLOR
{
	union
	{
		struct { float r, g, b ,a; } ;
		float v[4];
	};


	cTV_COLOR()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
	}

	cTV_COLOR(float fRed, float fGreen, float fBlue, float fAlpha)
	{
		r = fRed;
		g = fGreen;
		b = fBlue;
		a = fAlpha;
	}

	cTV_COLOR
		cTV_COLOR::operator + ( const cTV_COLOR& v ) const
	{
		return cTV_COLOR(r + v.r, g + v.g, b + v.b , a + v.a);
	}

	cTV_COLOR
		cTV_COLOR::operator - ( const cTV_COLOR& v ) const
	{
		return cTV_COLOR(r - v.r, g- v.g, b - v.b, a - v.a);
	}

	cTV_COLOR
		cTV_COLOR::operator * ( float f ) const
	{
		return cTV_COLOR(r * f,g * f, b * f, a *f );
	}

	cTV_COLOR
		cTV_COLOR::operator / ( float f ) const
	{
		float fInv = 1.0f / f;
		return cTV_COLOR(r * fInv, g* fInv, b * fInv, a* fInv);
	}

	cTV_COLOR& cTV_COLOR::operator += ( const cTV_COLOR& v)
	{
		r += v.r;
		g += v.g;
		b += v.b;
		a += v.a;
		return *this;

	}
	cTV_COLOR& cTV_COLOR::operator -= ( const cTV_COLOR& v)
	{
		r -= v.r;
		g -= v.g;
		b -= v.b;
		a -= v.a;
		return *this;

	}
	cTV_COLOR& cTV_COLOR::operator *= ( float f )
	{
		r *= f;
		g *= f;
		b *= f;
		a *= f;
		return *this;

	}


	bool cTV_COLOR::operator == ( const cTV_COLOR& v ) const
	{
		return r == v.r && g == v.g && b == v.b && a == v.a ;
	}

	bool cTV_COLOR::operator != ( const cTV_COLOR& v ) const
	{
		return r != v.r || g != v.g || b != v.b || a != v.a;
	}




} cTV_COLOR;




typedef enum cCONST_TV_LIGHTTYPE
{
	cTV_LIGHT_DIRECTIONAL = 3,
	cTV_LIGHT_POINT = 1,
	cTV_LIGHT_SPOT = 2,
	cTV_LIGHT_FORCE_DWORD = 0x7fffffff
} cCONST_TV_LIGHTTYPE;



typedef struct cTV_LIGHT
{
	cTV_3DVECTOR position;
	cTV_3DVECTOR direction;
	cTV_COLOR ambient;
	cTV_COLOR diffuse;
	cTV_COLOR specular;
	float range;
	float phi;
	float theta;
	cTV_3DVECTOR attenuation;
	cCONST_TV_LIGHTTYPE type;
	bool bManaged;
	float fFallOff;
} cTV_LIGHT;

typedef enum cCONST_TV_SHADERCONSTANTTYPE
{
	cTV_SHADERCONST_VECTOR4 = 1,
	cTV_SHADERCONST_MATRIX2x4 = 2,
	cTV_SHADERCONST_MATRIX3x4 = 3,
	cTV_SHADERCONST_MATRIX4x4 = 4,
	
	cTV_SHADERCONST_WORLD = 16,
	cTV_SHADERCONST_WORLDVIEW = 17,
	cTV_SHADERCONST_WORLDVIEWPROJ = 18,
	cTV_SHADERCONST_VIEWPROJ = 19,
	cTV_SHADERCONST_VIEW = 20,
	cTV_SHADERCONST_PROJ = 21,
	cTV_SHADERCONST_TIME = 22,

	cTV_SHADERCONST_OTHER = 256
} cCONST_TV_SHADERCONSTANTTYPE;



typedef enum cCONST_TV_MESHFORMAT
{
	cTV_MESHFORMAT_SIMPLE = 0,   // simple, and normal fvf  XYZ, NORMAL, TEX1
	cTV_MESHFORMAT_TEX1 = 1,     // simple also XYZ, NORMAL, TEX1
	cTV_MESHFORMAT_TEX2 = 2,	 // two sets of texcoords 
	cTV_MESHFORMAT_TEX3 = 3,	 // three sets of texcoords 
	cTV_MESHFORMAT_TEX4 = 4,	 // four sets of texcoords 
	cTV_MESHFORMAT_BUMPMAPINFO = 16, // add normal/tangent/binormal
	cTV_MESHFORMAT_DIFFUSE = 32, // diffuse color
	cTV_MESHFORMAT_SPECULAR = 64,  // specular color
	cTV_MESHFORMAT_NOLIGHTING = 128,  // disable normal.
	cTV_MESHFORMAT_NOTEX = 256,  // no texture coords.
	cTV_MESHFORMAT_BUMPMAP_VERTEX = 17, // XYZ, NORM, TANG, BIN, TEX1
	cTV_MESHFORMAT_COLORED_VERTEX = 225 // XYZ, DIFF, SPEC, TEX1


} cCONST_TV_MESHFORMAT;

typedef enum cCONST_TV_ELEMENTTYPE
{
	cTV_ELEMENT_FLOAT1 = 0 , //D3DDECLTYPE_FLOAT1 // 
	cTV_ELEMENT_FLOAT2 = 1 , //D3DDECLTYPE_FLOAT2
	cTV_ELEMENT_FLOAT3 = 2 , //D3DDECLTYPE_FLOAT3
	cTV_ELEMENT_FLOAT4 = 3 ,
	
	cTV_ELEMENT_FLOAT2_HALF = 15,// D3DDECLTYPE_FLOAT16_2  
	cTV_ELEMENT_FLOAT4_HALF = 16,// D3DDECLTYPE_FLOAT16_2  

	cTV_ELEMENT_LONGCOLOR  = 4 , // D3DDECLTYPE_D3DCOLOR
	cTV_ELEMENT_BYTE4 = 5,
	cTV_ELEMENT_SHORT2 = 6,
	cTV_ELEMENT_SHORT4 = 7,

	cTV_ELEMENT_FORCE_DWORD = 0x7fffffff

} cCONST_TV_ELEMENTTYPE;

typedef enum cCONST_TV_ELEMENTUSAGE
{
    cTV_ELEMENTUSAGE_POSITION = 0,
    cTV_ELEMENTUSAGE_NORMAL = 3,       
	cTV_ELEMENTUSAGE_DIFFUSE  = 24,       
	cTV_ELEMENTUSAGE_SPECULAR  = 25,        
	cTV_ELEMENTUSAGE_TANGENT = 6,       
    cTV_ELEMENTUSAGE_BINORMAL = 7,      

	cTV_ELEMENTUSAGE_TEXCOORD0 = 15,     
	cTV_ELEMENTUSAGE_TEXCOORD1 = 16,     
    cTV_ELEMENTUSAGE_TEXCOORD2 = 17,    
    cTV_ELEMENTUSAGE_TEXCOORD3 = 18,     
    cTV_ELEMENTUSAGE_TEXCOORD4 = 19,      
    cTV_ELEMENTUSAGE_TEXCOORD5 = 20,    
    cTV_ELEMENTUSAGE_TEXCOORD6 = 21,   
    cTV_ELEMENTUSAGE_TEXCOORD7 = 22,    

	cTV_ELEMENTUSAGE_BLENDWEIGHT = 1  , 
    cTV_ELEMENTUSAGE_BLENDINDICES = 2,  
    cTV_ELEMENTUSAGE_POINTSPRITESIZE = 4,         // 4
    cTV_ELEMENTUSAGE_TESSFACTOR = 8,   
    cTV_ELEMENTUSAGE_POSITIONT = 9,   

    cTV_ELEMENTUSAGE_FOG = 11,          
    cTV_ELEMENTUSAGE_DEPTH = 12,        
    cTV_ELEMENTUSAGE_SAMPLE = 13,

	cTV_ELEMENTUSAGE_FORCE_DWORD = 0x7fffffff
} cCONST_TV_ELEMENTUSAGE;

typedef struct cTV_VERTEXELEMENT
{
	cCONST_TV_ELEMENTTYPE element;
	cCONST_TV_ELEMENTUSAGE usage;
	int stream;  // usually 0
} cTV_VERTEXELEMENT;




    typedef enum cCONST_TV_REFRESHMODE {
        cTV_REFRESH_DISCARD = 1,
        cTV_REFRESH_FLIP = 2,
        cTV_REFRESH_COPY = 3
    } cCONST_TV_REFRESHMODE;

    typedef enum cCONST_TV_DEPTHBUFFERFORMAT {
        cTV_DEPTHBUFFER_BESTBUFFER = 0,
        cTV_DEPTHBUFFER_16BITS = 1,
        cTV_DEPTHBUFFER_24BITS = 2,
        cTV_DEPTHBUFFER_24BITS_8STENCILBITS = 3,
        cTV_DEPTHBUFFER_32BITS = 4
    } cCONST_TV_DEPTHMODEFORMAT;

    typedef enum cCONST_TV_MULTISAMPLE_TYPE {
        cTV_MULTISAMPLE_NONE = 0,
        cTV_MULTISAMPLE_2_SAMPLES = 2,
        cTV_MULTISAMPLE_3_SAMPLES = 3,
        cTV_MULTISAMPLE_4_SAMPLES = 4,
        cTV_MULTISAMPLE_5_SAMPLES = 5,
        cTV_MULTISAMPLE_6_SAMPLES = 6,
        cTV_MULTISAMPLE_7_SAMPLES = 7,
        cTV_MULTISAMPLE_8_SAMPLES = 8,
        cTV_MULTISAMPLE_9_SAMPLES = 9,
        cTV_MULTISAMPLE_10_SAMPLES = 10,
        cTV_MULTISAMPLE_11_SAMPLES = 11,
        cTV_MULTISAMPLE_12_SAMPLES = 12,
        cTV_MULTISAMPLE_13_SAMPLES = 13,
        cTV_MULTISAMPLE_14_SAMPLES = 14,
        cTV_MULTISAMPLE_15_SAMPLES = 15,
        cTV_MULTISAMPLE_16_SAMPLES = 16
    } cCONST_TV_MULTISAMPLE_TYPE;

    typedef struct cTV_RASTERSTATUS {
        bool inVBlank;
        long curScanline;
    } cTV_RASTERSTATUS;

    typedef struct cTV_MODEFORMAT {
        long Width;
        long Height;
        long Format;
    } cTV_MODEFORMAT;

    typedef struct cTV_DRIVERSETTINGS {
        char* DriverName;
        long id;
        short ModeCount;   
        cTV_MODEFORMAT* ModeFormat;
    } cTV_DRIVERSETTINGS;

    typedef enum cCONST_TV_KEY {
        cTV_KEY_0 = 11,
        cTV_KEY_1 = 2,
        cTV_KEY_2 = 3,
        cTV_KEY_3 = 4,
        cTV_KEY_4 = 5,
        cTV_KEY_5 = 6,
        cTV_KEY_6 = 7,
        cTV_KEY_7 = 8,
        cTV_KEY_8 = 9,
        cTV_KEY_9 = 10,
        cTV_KEY_A = 30,
        cTV_KEY_ABNT_C1 = 115,
        cTV_KEY_ABNT_C2 = 126,
        cTV_KEY_ADD = 78,
        cTV_KEY_APOSTROPHE = 40,
        cTV_KEY_APPS = 221,
        cTV_KEY_AT = 145,
        cTV_KEY_AX = 150,
        cTV_KEY_B = 48,
        cTV_KEY_BACKSPACE = 14,
        cTV_KEY_BACKSLASH = 43,
        cTV_KEY_C = 46,
        cTV_KEY_CALCULATOR = 161,
        cTV_KEY_CAPITAL = 58,
        cTV_KEY_CAPSLOCK = 58,
        cTV_KEY_CIRCUMFLEX = 144,
        cTV_KEY_COLON = 146,
        cTV_KEY_COMMA = 51,
        cTV_KEY_CONVERT = 121,
        cTV_KEY_D = 32,
        cTV_KEY_DECIMAL = 83,
        cTV_KEY_DELETE = 211,
        cTV_KEY_DIVIDE = 181,
        cTV_KEY_DOWN = 208,
        cTV_KEY_DOWNARROW = 208,
        cTV_KEY_E = 18,
        cTV_KEY_END = 207,
        cTV_KEY_EQUALS = 13,
        cTV_KEY_ESCAPE = 1,
        cTV_KEY_F = 33,
        cTV_KEY_F1 = 59,
        cTV_KEY_F2 = 60,
        cTV_KEY_F3 = 61,
        cTV_KEY_F4 = 62,
        cTV_KEY_F5 = 63,
        cTV_KEY_F6 = 64,
        cTV_KEY_F7 = 65,
        cTV_KEY_F8 = 66,
        cTV_KEY_F9 = 67,
        cTV_KEY_F10 = 68,
        cTV_KEY_F11 = 87,
        cTV_KEY_F12 = 88,
        cTV_KEY_F13 = 100,
        cTV_KEY_F14 = 101,
        cTV_KEY_F15 = 102,
        cTV_KEY_G = 34,
        cTV_KEY_GRAVE = 41,
        cTV_KEY_H = 35,
        cTV_KEY_HOME = 199,
        cTV_KEY_I = 23,
        cTV_KEY_INSERT = 210,
        cTV_KEY_J = 36,
        cTV_KEY_K = 37,
        cTV_KEY_KANA = 112,
        cTV_KEY_KANJI = 148,
        cTV_KEY_L = 38,
        cTV_KEY_ALT_LEFT = 56,
        cTV_KEY_LEFTBRACKET = 26,
        cTV_KEY_LEFTCONTROL = 29,
        cTV_KEY_LEFT = 203,
        cTV_KEY_LEFTARROW = 203,
        cTV_KEY_LEFTMENU = 56,
        cTV_KEY_LEFTSHIFT = 42,
        cTV_KEY_LEFTWINDOWS = 219,
        cTV_KEY_M = 50,
        cTV_KEY_MAIL = 236,
        cTV_KEY_MEDIASELECT = 237,
        cTV_KEY_MEDIASTOP = 164,
        cTV_KEY_MINUS = 12,
        cTV_KEY_MULTIPLY = 55,
        cTV_KEY_MUTE = 160,
        cTV_KEY_MYCOMPUTER = 235,
        cTV_KEY_N = 49,
        cTV_KEY_NEXT = 209,
        cTV_KEY_NEXTTRACK = 153,
        cTV_KEY_NOCONVERT = 123,
        cTV_KEY_NUMLOCK = 69,
        cTV_KEY_NUMPAD0 = 82,
        cTV_KEY_NUMPAD1 = 79,
        cTV_KEY_NUMPAD2 = 80,
        cTV_KEY_NUMPAD3 = 81,
        cTV_KEY_NUMPAD4 = 75,
        cTV_KEY_NUMPAD5 = 76,
        cTV_KEY_NUMPAD6 = 77,
        cTV_KEY_NUMPAD7 = 71,
        cTV_KEY_NUMPAD8 = 72,
        cTV_KEY_NUMPAD9 = 73,
        cTV_KEY_NUMPADCOMMA = 179,
        cTV_KEY_NUMPADENTER = 156,
        cTV_KEY_NUMPADEQUALS = 141,
        cTV_KEY_NUMPADMINUS = 74,
        cTV_KEY_NUMPADPERIOD = 83,
        cTV_KEY_NUMPADPLUS = 78,
        cTV_KEY_NUMPADSLASH = 181,
        cTV_KEY_NUMPADSTAR = 55,
        cTV_KEY_O = 24,
        cTV_KEY_OEM_102 = 86,
        cTV_KEY_P = 25,
        cTV_KEY_PAUSE = 197,
        cTV_KEY_PERIOD = 52,
        cTV_KEY_PAGEDOWN = 209,
        cTV_KEY_PAGEUP = 201,
        cTV_KEY_PLAYPAUSE = 162,
        cTV_KEY_POWER = 222,
        cTV_KEY_PREVTRACK = 144,
        cTV_KEY_PRIOR = 201,
        cTV_KEY_Q = 16,
        cTV_KEY_R = 19,
        cTV_KEY_ALT_RIGHT = 184,
        cTV_KEY_RIGHTBRACKET = 27,
        cTV_KEY_RIGHTCONTROL = 157,
        cTV_KEY_RETURN = 28,
        cTV_KEY_RIGHT = 205,
        cTV_KEY_RIGHTARROW = 205,
        cTV_KEY_RIGHTMENU = 184,
        cTV_KEY_RIGHTSHIFT = 54,
        cTV_KEY_RWIN = 220,
        cTV_KEY_S = 31,
        cTV_KEY_SCROLL = 70,
        cTV_KEY_SEMICOLON = 39,
        cTV_KEY_SLASH = 53,
        cTV_KEY_SLEEP = 223,
        cTV_KEY_SPACE = 57,
        cTV_KEY_STOP = 149,
        cTV_KEY_SUBTRACT = 74,
        cTV_KEY_SYSRQ = 183,
        cTV_KEY_T = 20,
        cTV_KEY_TAB = 15,
        cTV_KEY_U = 22,
        cTV_KEY_UNDERLINE = 147,
        cTV_KEY_UNLABELED = 151,
        cTV_KEY_UP = 200,
        cTV_KEY_UPARROW = 200,
        cTV_KEY_V = 47,
        cTV_KEY_VOLUMEDOWN = 174,
        cTV_KEY_VOLUMEUP = 176,
        cTV_KEY_W = 17,
        cTV_KEY_WAKE = 227,
        cTV_KEY_WEBBACK = 234,
        cTV_KEY_WEBFAVORITES = 230,
        cTV_KEY_WEBFORWARD = 233,
        cTV_KEY_WEBHOME = 178,
        cTV_KEY_WEBREFRESH = 231,
        cTV_KEY_WEBSEARCH = 229,
        cTV_KEY_WEBSTOP = 232,
        cTV_KEY_X = 45,
        cTV_KEY_Y = 21,
        cTV_KEY_YEN = 125, 
        cTV_KEY_Z = 44,
		cTV_FORCE_DWORD = 0x7fffffff
    } cCONST_TV_KEY; 

    typedef struct cTV_POINTAPI {      
        long x;
        long Y;
    } cTV_POINTAPI;

    typedef struct cTV_KEYDATA {        
       int Pressed;
       int Released;        
        cCONST_TV_KEY Key;
    } cTV_KEYDATA;

    typedef struct cTV_KEYBUFFER {       
        cTV_KEYDATA* Data;
    } cTV_KEYBUFFER;

    typedef enum cCONST_TV_DETAILMAP_MODE {
        cTV_DETAILMAP_ADD = 7,
        cTV_DETAILMAP_ADDSIGNED = 8,
        cTV_DETAILMAP_MODULATE = 4,
        cTV_DETAILMAP_MODULATE2X = 5,
        cTV_DETAILMAP_SUBTRACT = 10
    } cCONST_TV_DETAILMAP_MODE;

    typedef enum cCONST_TV_LANDSCAPE_AFFINE {
        cTV_AFFINE_NO = 0,
        cTV_AFFINE_LOW = 1,
        cTV_AFFINE_HIGH = 2
    } cCONST_TV_LANDSCAPE_AFFINE;

    typedef enum cCONST_TV_LANDSCAPE_HEIGHTMAP {	
		cTV_HEIGHTMAP_BLUE = 0,
		cTV_HEIGHTMAP_GREEN = 1,
		cTV_HEIGHTMAP_RED = 2,
        cTV_HEIGHTMAP_ALLRGB = 3,
		cTV_HEIGHTMAP_ALLBGR = 4
    } cCONST_TV_LANDSCAPE_HEIGHTMAP;

    typedef enum cCONST_TV_LANDSAVE {
        cTV_LANDSAVE_HEIGHT = 0,
        cTV_LANDSAVE_NORMALHEIGHT = 1,
		cTV_LANDSAVE_ALL = 2
    } cCONST_TV_LANDSAVE;

    typedef enum cCONST_TV_LANDSCAPE_PRECISION {
		cTV_PRECISION_LOWEST = 256,
        cTV_PRECISION_ULTRA_LOW = 128,
        cTV_PRECISION_VERY_LOW = 64,
        cTV_PRECISION_LOW = 32,
        cTV_PRECISION_HIGH = 8,
        cTV_PRECISION_AVERAGE = 16,
        cTV_PRECISION_BEST = 4,
		cTV_PRECISION_ULTRA = 2
    } cCONST_TV_LANDSCAPE_PRECISION;

	typedef enum cCONST_TV_LANDSCAPE_HOLETYPE {
		cTV_HOLE_NONE = 0,
		cTV_HOLE_QUAD_INVISIBLE_NO_COLLISION = 1,
		cTV_HOLE_QUAD_INVISIBLE_WITH_COLLISION = 2
	
	} cCONST_TV_LANDSCAPE_HOLETYPE;


    typedef enum cCONST_TV_SUNMODE {
        cTV_SUN_REALTIME_MOVING = 1,
        cTV_SUN_CHANGE_AMBIENT_LIGHT = 2,
        cTV_SUN_DEFAULT = 0
    } cCONST_TV_LAND_SUNMODE;

    typedef enum cCONST_TV_CLOUDMODE {
        cTV_CLOUD_MOVE = 1,
        cTV_CLOUD_DEFAULT = 0
    } cCONST_TV_CLOUDMODE;

    typedef enum cCONST_TV_LANDSCAPEMODE {
        cTV_LANDMODE_SIMPLELAND = 1,
        cTV_LANDMODE_ADVANCEDLAND = 2
    } cCONST_TV_LANDSCAPEMODE;

    typedef enum cCONST_TV_TEXGENRESOLUTION {
        cTV_TEXGEN_16x16 = 16,
        cTV_TEXGEN_32x32 = 32,
        cTV_TEXGEN_64x64 = 64,
        cTV_TEXGEN_128x128 = 128,
        cTV_TEXGEN_256x256 = 256,
        cTV_TEXGEN_512x512 = 512,
        cTV_TEXGEN_1024x1024 = 1024,
        cTV_TEXGEN_2048x2048 = 2048
    } cCONST_TV_TEXGENRESOLUTION;

    typedef enum cCONST_TV_TEXTUREMOD {
        cTV_TEXTUREMOD_USECURRENTCOORDS = 0,
        cTV_TEXTUREMOD_USECAMERAPOSITION = 1,
        cTV_TEXTUREMOD_USECAMERANORMAL = 2
    } cCONST_TV_TEXTUREMOD;

    typedef enum cCONST_TV_PRIMITIVETYPE{

		cTV_TRIANGLEFAN = 6,
        cTV_TRIANGLESTRIP = 5,
        cTV_TRIANGLELIST = 4,
        cTV_LINELIST = 2,
        cTV_LINESTRIP = 3,
        cTV_POINTLIST = 1
    } cCONST_TV_PRIMITIVETYPE;

    typedef enum cCONST_TV_VERTEXTYPE {
        cTV_COLOR_VERTEX = 530,
        cTV_NORMAL_VERTEX = 530,
        cTV_NON_LIT_VERTEX = 530
    } cCONST_TV_VERTEXTYPE;

    typedef enum cCONST_TV_MESHTYPE {
        cTV_ANIMATION_FRAME_NOMESH = 1,
        cTV_NORMAL_MESH = 0,
        cTV_MESH_AND_FRAME = 2
    } cCONST_TV_MESHTYPE;

    typedef enum cCONST_TV_BILLBOARDTYPE {
        cTV_BILLBOARD_FREEROTATION = 0,
        cTV_BILLBOARD_YAXIS = 1,
        cTV_BILLBOARD_NOROTATION = 2
    } cCONST_TV_BILLBOARDTYPE;

    typedef enum cCONST_TV_RENDERMODE {
        cTV_POINT = 1,
        cTV_LINE = 2,
        cTV_SOLID = 3
    } cCONST_TV_RENDERMODE;

    typedef enum cCONST_TV_TEXTUREFILTER {
        cTV_FILTER_NEARESTPOINT = 0,
        cTV_FILTER_BILINEAR = 1,
        cTV_FILTER_TRILINEAR = 2,
        cTV_FILTER_ANISOTROPIC = 3,
        cTV_FILTER_FLATCUBIC = 4,
        cTV_FILTER_GAUSSIANCUBIC = 5,
        cTV_FILTER_NONE = 6
    } cCONST_TV_TEXTUREFILTER;

    typedef enum cCONST_TV_TESTTYPE {
		cTV_TESTTYPE_DEFAULT = 0,
        cTV_TESTTYPE_BOUNDINGBOX = 1,
        cTV_TESTTYPE_BOUNDINGSPHERE = 2,
        cTV_TESTTYPE_ACCURATETESTING = 3,
        cTV_TESTTYPE_HITBOXES = 4
    } cCONST_TV_TESTTYPE;

	typedef enum cCONST_TV_CUBEMAPFACE
	{		
		cTV_CUBEMAP_POSITIVE_X = 0,
		cTV_CUBEMAP_NEGATIVE_X = 1,
		cTV_CUBEMAP_POSITIVE_Y = 2,
		cTV_CUBEMAP_NEGATIVE_Y = 3,
		cTV_CUBEMAP_POSITIVE_Z = 4,
		cTV_CUBEMAP_NEGATIVE_Z = 5	
	} cCONST_TV_CUBEMAPFACE;

    typedef enum cCONST_TV_COLORKEY {
        cTV_COLORKEY_NO = 0,
        cTV_COLORKEY_WHITE = 0xffffffff,
        cTV_COLORKEY_BLACK = 0xff000000,
        cTV_COLORKEY_BLUE = 0xff0000ff,
        cTV_COLORKEY_RED = 0xffff0000,
        cTV_COLORKEY_GREEN = 0xff00ff00,
        cTV_COLORKEY_YELLOW = 0xffffff00,
        cTV_COLORKEY_MAGENTA = 0xffff00ff,
        cTV_COLORKEY_CYAN = 0xff00ffff,
        cTV_COLORKEY_USE_ALPHA_CHANNEL = 0xfffaffac
    } cCONST_TV_COLORKEY;

    typedef enum cCONST_TV_BLENDINGMODE {
        cTV_BLEND_NO = 0,
        cTV_BLEND_ALPHA = 1,
        cTV_BLEND_ADD = 2,
        cTV_BLEND_COLOR = 3,
        cTV_BLEND_ADDALPHA = 4,
		cTV_BLEND_MULTIPLY = 5
    } cCONST_TV_BLENDINGMODE;

	typedef enum cCONST_TV_BLENDEX {
		cTV_BLENDEX_ONE = 2,//D3DBLEND_ONE
		cTV_BLENDEX_SRCALPHA = 5 ,//D3DBLEND_SRCALPHA	
		cTV_BLENDEX_SRCCOLOR = 3 ,//D3DBLEND_SRCCOLOR
		cTV_BLENDEX_INVSRCALPHA = 6, // D3DBLEND_INVSRCALPHA
		cTV_BLENDEX_DESTALPHA = 7,  //D3DBLEND_DESTALPHA
		cTV_BLENDEX_INVDESTALPHA = 8, // D3DBLEND_INVDESTALPHA
		cTV_BLENDEX_INVSRCCOLOR = 4, //  D3DBLEND_INVSRCCOLOR
		cTV_BLENDEX_ZERO = 1 //  D3DBLEND_ZERO
	} cCONST_TV_BLENDEX;


    typedef enum cCONST_TV_DEPTHBUFFER {
        cTV_ZBUFFER = 1,
        cTV_WBUFFER = 2
    } cCONST_TV_DEPTHBUFFER;

    typedef enum cCONST_TV_SHADEMODE {
        cTV_SHADEMODE_FLAT = 1,
        cTV_SHADEMODE_GOURAUD = 2,
        cTV_SHADEMODE_PHONG = 3
    } cCONST_TV_SHADEMODE;

	typedef enum cCONST_TV_OBJECT_TYPE {
		cTV_OBJECT_ALL = 0,
		cTV_OBJECT_MESH = 1,
		cTV_OBJECT_LANDSCAPE = 2,
		cTV_OBJECT_OCTREE = 4,
		cTV_OBJECT_ACTOR = 8,
		cTV_OBJECT_NOCOLLISION = 256,
		cTV_OBJECT_FORCE_DWORD = 0x7fffffff // to have a int enumeration (delphi)
	} cCONST_TV_OBJECT_TYPE;

	typedef enum cCONST_TV_SHADEROBJECT_TYPE {
		cTV_SHADEROBJECT_ALL = 0,
		cTV_SHADEROBJECT_MESH = 1,
		cTV_SHADEROBJECT_ACTOR = 2,
		cTV_SHADEROBJECT_LANDSCAPE = 3,
		cTV_SHADEROBJECT_MINIMESH = 4,
		cTV_SHADEROBJECT_PARTICLE = 5,
		cTV_SHADEROBJECT_ATMOSPHERE = 6,
		cTV_SHADEROBJECT_FORCE_DWORD = 0x7fffffff
	} cCONST_TV_SHADEROBJECT_TYPE;


    typedef struct cTV_COLLISIONRESULT {
       
        cTV_3DVECTOR vCollisionNormal;
        cTV_3DVECTOR vCollisionImpact;
        float fDistance;
        float fU;
        float fV;
        int iFaceindex;
        int iGroupIndex;
        bool bHasCollided;
        cCONST_TV_OBJECT_TYPE eCollidedObjectType;
        int iEntityID;
        int iMeshID;
        int iLandscapeID;
        int iBoneID;
		float fTexU;
		float fTexV;
    } cTV_COLLISIONRESULT;

    typedef enum cCONST_TV_TEXTUREMODE {
        cTV_TEXTUREMODE_16BITS = 0,
        cTV_TEXTUREMODE_32BITS = 1,
        cTV_TEXTUREMODE_COMPRESSED = 2,
        cTV_TEXTUREMODE_BETTER = 3,
        cTV_TEXTUREMODE_PALETTIZED8BITS = 4
    } cCONST_TV_TEXTUREMODE;

    typedef enum cCONST_TV_TEXTURETYPE {
        cTV_TEXTURE_DIFFUSEMAP = 0,
        cTV_TEXTURE_NORMALMAP = 1,
        cTV_TEXTURE_CUBICMAP = 2,
        cTV_TEXTURE_RENDERSURFACE = 3,
		cTV_TEXTURE_CUBERENDERSURFACE = 4,
		cTV_TEXTURE_VOLUMEMAP = 5,
		cTV_TEXTURE_DUDVMAP = 6,
		cTV_TEXTURE_BUMPMAP = 7,
		cTV_TEXTURE_FORCE_DWORD = 0x7fffffff
    } cCONST_TV_TEXTURETYPE;

    typedef struct cTV_TEXTURE {
        
        bool Active;
		char* Name;
        char* Filename;
        long Width;
        long Height;
        long Size;
        long bitdepth;
        bool colorkeyed;
		long RealWidth;
		long RealHeight;
	    cCONST_TV_TEXTURETYPE TextureType;
		long Depth;
		long RealDepth;
	} cTV_TEXTURE;

    typedef enum cCONST_TV_CULLING {
        cTV_FRONT_CULL = 2,
        cTV_BACK_CULL = 3,
        cTV_DOUBLESIDED = 1
    } cCONST_TV_CULLING;

    typedef struct cTV_PLANE {
        
        cTV_3DVECTOR Normal;
        float Dist;

		cTV_PLANE()
		{
			Normal.x = 0;
			Normal.y = 0;
			Normal.z = 0;
			Dist = 0;
		}
		cTV_PLANE(float a, float b, float c, float d)
		{
			Normal.x = a;
			Normal.y = b;
			Normal.z = c;
			Dist = d;
		}
		cTV_PLANE(cTV_3DVECTOR& vNormal, float fDist)
		{
			Normal = vNormal;
			Dist = fDist;
		}
		cTV_PLANE(cTV_3DVECTOR& v1, cTV_3DVECTOR& v2, cTV_3DVECTOR& v3)
		{
			cTV_3DVECTOR c1 = v2 - v1;
			cTV_3DVECTOR c2 = v3 - v1;
			cTV_3DVECTOR n = c1.Cross(c2);
			Normal = n / n.Length();
			// ax+by+cz+d = 0   =>  d = -ax-by-cz
			Dist = -Normal.Dot(v1);
		}
    } cTV_PLANE;

    typedef enum cCONST_TV_CURVE {
        cTV_CURVE_LOW = 0,
        cTV_CURVE_NORMAL = 1,
        cTV_CURVE_HIGH = 2
    } cCONST_TV_CURVE;

    typedef enum cCONST_TV_EMITTERMOVEMODE {
        cTV_EMITTER_LERP = 0,
        cTV_EMITTER_NOLERP = 1
    } cCONST_TV_EMITTERMOVEMODE;

    typedef enum cCONST_TV_PARTICLECHANGE {
        cTV_CHANGE_ALPHA = 1,
        cTV_CHANGE_COLOR = 2,
        cTV_CHANGE_NO = 3
    } cCONST_TV_PARTICLECHANGE;

    typedef enum cCONST_TV_PARTICLE_PRESET {
        cTV_PARTICLE_EXPLOSION = 3,
        cTV_PARTICLE_EXPLOSIONUP = 8
    } cCONST_TV_PARTICLE_PRESET;

    typedef enum cCONST_TV_GAMMATYPE {
        cTV_GAMMA_LINEAR = 1,
        cTV_GAMMA_EXPONENTIAL = 2
    } cCONST_TV_GAMMATYPE;

    typedef enum cCONST_TV_PATHTYPE {
        cTV_PATH_LINEAR = 0,
        cTV_PATH_QUADRATICBEZIER = 1,
        cTV_PATH_CUBICBEZIER = 2,
        cTV_PATH_SPLINE = 3,
		cTV_PATH_CATMULLROM = 4
    } cCONST_TV_PATHTYPE;


    typedef enum cCONST_TV_EFFECT_TYPE {
        cTV_ALL = 0,
        cTV_CONDITION = 4,
        cTV_CONSTANTFORCE = 1,
        cTV_CUSTOMFORCE = 5,
        cTV_HARDWARE = 255,
        cTV_PERIODIC = 3,
        cTV_RAMPFORCE = 2
    } cCONST_TV_EFFECT_TYPE;

	typedef struct cTV_JOYSTATE {
        long X;
		long Y;
		long Z;
        long RotationX;
        long RotationY;
        long rotationz;
        long Slider0;
        long Slider1;
        long PointOfView0;
        long PointOfView1;
        long PointOfView2;
        long PointOfView3;
    } cTV_JOYSTATE;

    typedef struct cTV_JOYSTATE2 
	{
        long X;
        long Y;
        long Z;
        long RotationX;
        long RotationY;
        long rotationz;
        long Slider0;
        long Slider1;
        long PointOfView0;
        long PointOfView1; 
        long PointOfView2;
        long PointOfView3;     
        long TorqueX;
        long TorqueY; 
        long TorqueZ;
        long ForceX;
        long ForceY;
        long ForceZ;
        long AngularVelocityX;
        long AngularVelocityY;
        long AngularVelocityZ;
        long vx;
        long vy;
		long vz;
        long vslider0;
        long vslider1;
        long fslider0;
        long fslider1;
        long ax;
        long ay;
		long az;   
        long arx;    
        long ary; 
        long arz; 
        long aslider0;
        long aslider1;
    } cTV_JOYSTATE2;

    typedef enum cCONST_TV_ENVMAPFACE {
        cTV_FACE_POSITIVEX = 1,
        cTV_FACE_NEGATIVEX = 0,
        cTV_FACE_POSITIVEY = 3,
        cTV_FACE_NEGATIVEY = 2,
        cTV_FACE_POSITIVEZ = 5,
        cTV_FACE_NEGATIVEZ = 4
    } cCONST_TV_ENVMAPFACE;

    typedef enum cCONST_TV_ROTATIONAXIS {
        cTV_ROTATION_OPENGLCOORDINATES = 0,
        cTV_ROTATION_DIRECTXCOORDINATES = 1
    } cCONST_TV_ROTATIONAXIS;

    typedef enum cCONST_TV_ANGLE {
        cTV_ANGLE_RADIAN = 0,
        cTV_ANGLE_DEGREE = 1
    } cCONST_TV_ANGLE;

    typedef enum cCONST_TV_FOG {
        cTV_FOG_LINEAR = 3,
        cTV_FOG_EXP = 1,
        cTV_FOG_EXP2 = 2
    } cCONST_TV_FOG;

    typedef enum cCONST_TV_FOGTYPE {
        cTV_FOGTYPE_PIXEL = 0,
        cTV_FOGTYPE_RANGE = 1,
        cTV_FOGTYPE_VERTEX = 2
    } cCONST_TV_FOGTYPE;

	typedef struct cTV_PARTICLE_KEYFRAME
	{
		float fKey;
		cTV_3DVECTOR fSize; 
		cTV_COLOR cColor;
		cTV_3DVECTOR vRotation;
	} cTV_PARTICLE_KEYFRAME;

	typedef enum cCONST_TV_PARTICLE_KEYUSAGE
	{
		cTV_PARTICLE_KEYUSAGE_ANGLE_XYZ = 1,
		cTV_PARTICLE_KEYUSAGE_COLOR = 2,
		cTV_PARTICLE_KEYUSAGE_SIZE = 4,
		cTV_PARTICLE_KEYUSAGE_ANGLE_Z = 8
	} cCONST_TV_PARTICLE_KEYUSAGE;

	typedef struct cTV_PARTICLEEMITTER_KEYFRAME
	{
		cTV_3DVECTOR vLocalPosition;
		cTV_3DVECTOR vMainDirection;
		cTV_3DVECTOR vGeneratorBoxSize;
		cTV_COLOR vDefaultColor;
		float fKey;
		float fSpeed;
		float fGeneratorSphereRadius;
		float fParticleLifeTime;
		float fPower;
	} cTV_PARTICLEEMITTER_KEYFRAME;


	typedef enum cCONST_TV_PARTICLEEMITTER_KEYUSAGE
	{
		cTV_EMITTER_KEYUSAGE_LOCALPOSITION = 1,
		cTV_EMITTER_KEYUSAGE_MAINDIRECTION = 2,
		cTV_EMITTER_KEYUSAGE_DEFAULTCOLOR = 4,
		cTV_EMITTER_KEYUSAGE_RADIUS = 8,
		cTV_EMITTER_KEYUSAGE_SPEED = 16,
		cTV_EMITTER_KEYUSAGE_LIFETIME = 32,
		cTV_EMITTER_KEYUSAGE_POWER = 64,
		cTV_EMITTER_KEYUSAGE_BOXSIZE = 128
	} cCONST_TV_PARTICLEEMITTER_KEYUSAGE;

	typedef enum cCONST_TV_TEXTUREPATHSTORAGE
	{
		cTV_TEXTURESTORAGE_PATHFILENAME,
		cTV_TEXTURESTORAGE_FILENAMEONLY,
		cTV_TEXTURESTORAGE_NAME
	} cCONST_TV_TEXTUREPATHSTORAGE;


	// new newton event type
	typedef struct cTV_EVENT_PHYSICSCOLLISION
	{
		cTV_3DVECTOR vNormal;
		cTV_3DVECTOR vPosition;
		float fNormalSpeed;
		float fTangentSpeed;
		float fForce;
		int iBody1;
		int iBody2;
		int iMaterial1;
		int iMaterial2;
	} cTV_EVENT_PHYSICSCOLLISION;


	typedef enum cCONST_TV_PHYSICS_SOLVER
	{
		cTV_SOLVER_EXACT = 0,
		cTV_SOLVER_ADAPTIVE = 1,
		cTV_SOLVER_LINEAR = 2,
		cTV_SOLVER_LINEAR_5PASSES = 7,
		cTV_SOLVER_LINEAR_10PASSES = 12
	} cCONST_TV_PHYSICS_SOLVER;
	 
    typedef enum cCONST_TV_PHYSICS_FRICTION
	{
		cTV_FRICTION_EXACT = 0,
		cTV_FRICTION_ADAPTIVE = 1
	} cCONST_TV_PHYSICS_FRICTION;

	typedef struct cTV_VERTEX_BUMP
	{
		float x,y,z;
		float nx,ny,nz;  // normal
		float tx,ty,tz;  // tangent
		float bx,by,bz;  // binormal
        float tu, tv;
	} cTV_VERTEX_BUMP;

	typedef struct cTV_VERTEX_COLORED
	{
		float x,y,z;
		int iDiffuseColor;
		int iSpecularColor;
		float tu,tv;
	} cTV_VERTEX_COLORED;

    // Dewitt added
    typedef cTV_2DVECTOR Vec2;
    typedef cTV_3DVECTOR Vec3;
    typedef cTV_4DVECTOR Vec4;
	// end Dewitt added
    
	//////////////////////////////////////////////////////////////////////////

#endif
