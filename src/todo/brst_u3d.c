#include "brst_conf.h"
#include "brst_utils.h"
#include "hpdf.h"
#include "brst_u3d.h"

#include "internal/brst_objects_internal.h"
#include "internal/brst_doc_internal.h"
#include "internal/brst_streams_internal.h"
#include "internal/brst_pages_internal.h"

#include <string.h>

BRST_EXPORT(BRST_Dict)
BRST_Page_Create3DView    (BRST_Page        page,
                           BRST_U3D         u3d,
                           BRST_Annotation  annot3d,
                           const char      *name)
{
    BRST_PageAttr attr;
    BRST_Dict view;

    BRST_PTRACE((" BRST_Page_Create3DView\n"));
    BRST_UNUSED(annot3d);

    if (!BRST_Page_Validate (page))
        return NULL;

    attr = (BRST_PageAttr)page->attr;

    view = BRST_3DView_New( page->mmgr, attr->xref, u3d, name);
    if (!view) {
        BRST_CheckError (page->error);
    }
    return view;
}

BRST_U3D
BRST_U3D_LoadU3D  (BRST_MMgr        mmgr,
				   BRST_Stream      u3d_data,
				   BRST_Xref        xref);

static BRST_STATUS Get3DStreamType (BRST_Stream  stream, const char **type)
{
	static const char sign_u3d[] = "U3D";
	static const char sign_prc[] = "PRC";

	BRST_BYTE tag[4];
	BRST_UINT len;

	BRST_PTRACE ((" BRST_U3D_Get3DStreamType\n"));

	len = 4;
	if (BRST_Stream_Read (stream, tag, &len) != BRST_OK) {
		return BRST_Error_GetCode (stream->error);
	}

	if (BRST_Stream_Seek (stream, 0, BRST_SEEK_SET) != BRST_OK) {
		return BRST_Error_GetCode (stream->error);
	}

	if (BRST_MemCmp(tag, (BRST_BYTE *)sign_u3d, 4/* yes, \0 is required */) == 0) {
		*type = sign_u3d;
		return BRST_OK;
	}

	if (BRST_MemCmp(tag, (BRST_BYTE *)sign_prc, 3) == 0) {
		*type = sign_prc;
		return BRST_OK;
	}

	return BRST_INVALID_U3D_DATA;
}


BRST_EXPORT(BRST_Image)
BRST_LoadU3DFromFile  (BRST_Doc     pdf,
						const char  *filename)
{
	BRST_Stream imagedata;
	BRST_Image image;

	BRST_PTRACE ((" BRST_LoadU3DFromFile\n"));

	if (!BRST_HasDoc (pdf)) {
		return NULL;
	}

	if (pdf->pdf_version < BRST_VER_17)
		pdf->pdf_version = BRST_VER_17;

	/* create file stream */
	imagedata = BRST_FileReader_New (pdf->mmgr, filename);

	if (BRST_Stream_Validate (imagedata)) {
		image = BRST_U3D_LoadU3D (pdf->mmgr, imagedata, pdf->xref);
	} else {
		image = NULL;
	}

	/* destroy file stream */
	BRST_Stream_Free (imagedata);

	if (!image) {
		BRST_CheckError (&pdf->error);
	}
	return image;
}

BRST_EXPORT(BRST_Image)
BRST_LoadU3DFromMem (BRST_Doc pdf,
             const BRST_BYTE *buffer,
                    BRST_UINT size)
{
	BRST_Stream imagedata;
	BRST_Image image;

	BRST_PTRACE ((" BRST_LoadU3DFromMem\n"));

	if (!BRST_HasDoc (pdf)) {
		return NULL;
	}

	/* create file stream */
	imagedata = BRST_MemStream_New (pdf->mmgr, size);

	if (!BRST_Stream_Validate (imagedata)) {
		BRST_RaiseError (&pdf->error, BRST_INVALID_STREAM, 0);
		return NULL;
	}

	if (BRST_Stream_Write (imagedata, buffer, size) != BRST_OK) {
		BRST_Stream_Free (imagedata);
		return NULL;
	}

	if (BRST_Stream_Validate (imagedata)) {
		image = BRST_U3D_LoadU3D (pdf->mmgr, imagedata, pdf->xref);
	} else {
		image = NULL;
	}

	/* destroy file stream */
	BRST_Stream_Free (imagedata);

	if (!image) {
		BRST_CheckError (&pdf->error);
	}
	return image;
}

BRST_U3D
BRST_U3D_LoadU3D   (BRST_MMgr        mmgr,
					BRST_Stream      u3d_data,
					BRST_Xref        xref)
{
	BRST_Dict u3d;
	const char *type = NULL;

	BRST_PTRACE ((" BRST_U3D_LoadU3D\n"));

	u3d = BRST_DictStream_New (mmgr, xref);
	if (!u3d) {
		return NULL;
	}

	u3d->filter = BRST_STREAM_FILTER_FLATE_DECODE;

	if (BRST_Dict_AddName (u3d, "Type", "3D") != BRST_OK) {
		BRST_Dict_Free(u3d);
		return NULL;
	}

	if (Get3DStreamType (u3d_data, &type) != BRST_OK) {
		BRST_Dict_Free(u3d);
		return NULL;
	}

	if (BRST_Dict_AddName (u3d, "Subtype", type) != BRST_OK) {
		BRST_Dict_Free(u3d);
		return NULL;
	}

	for (;;) {
		BRST_BYTE buf[BRST_STREAM_BUF_SIZ];
		BRST_UINT len = BRST_STREAM_BUF_SIZ;
		BRST_STATUS ret = BRST_Stream_Read (u3d_data, buf, &len);

		if (ret != BRST_OK) {
			if (ret == BRST_STREAM_EOF) {
				if (len > 0) {
					ret = BRST_Stream_Write (u3d->stream, buf, len);
					if (ret != BRST_OK) {
						BRST_Dict_Free(u3d);
						return NULL;
					}
				}
				break;
			} else {
				BRST_Dict_Free(u3d);
				return NULL;
			}
		}

		if (BRST_Stream_Write (u3d->stream, buf, len) != BRST_OK) {
			BRST_Dict_Free(u3d);
			return NULL;
		}
	}

	return u3d;
}

BRST_EXPORT(BRST_Dict) BRST_Create3DView(BRST_MMgr mmgr, const char *name)
{
	BRST_STATUS ret = BRST_OK;
	BRST_Dict view;

	BRST_PTRACE ((" BRST_Create3DView\n"));

	if (name == NULL || name[0] == '\0') {
		return NULL;
	}

	view = BRST_Dict_New (mmgr);
	if (!view) {
		return NULL;
	}

	ret = BRST_Dict_AddName (view, "TYPE", "3DView");
	if (ret != BRST_OK) {
		BRST_Dict_Free (view);
		return NULL;
	}

	ret = BRST_Dict_Add (view, "XN", BRST_String_New (mmgr, name, NULL));
	if (ret != BRST_OK) {
		BRST_Dict_Free (view);
		return NULL;
	}

	ret = BRST_Dict_Add (view, "IN", BRST_String_New (mmgr, name, NULL));
	if (ret != BRST_OK) {
		BRST_Dict_Free (view);
		return NULL;
	}

	return view;
}

BRST_EXPORT(BRST_STATUS) BRST_U3D_Add3DView(BRST_U3D u3d, BRST_Dict view)
{
	BRST_Array views = NULL;
	BRST_STATUS ret = BRST_OK;

	BRST_PTRACE ((" BRST_Add3DView\n"));

	if (u3d == NULL || view == NULL) {
		return BRST_INVALID_U3D_DATA;
	}

	views = (BRST_Array)BRST_Dict_GetItem (u3d, "VA", BRST_OCLASS_ARRAY);
	if (views == NULL) {
		views = BRST_Array_New (u3d->mmgr);
		if (!views) {
			return BRST_Error_GetCode (u3d->error);
		}

		ret = BRST_Dict_Add (u3d, "VA", views);
		if (ret == BRST_OK) {
			ret = BRST_Dict_AddNumber (u3d, "DV", 0);
		} else {
			BRST_Array_Free (views);
			return ret;
		}
	}

	if (ret == BRST_OK) {
		ret = BRST_Array_Add( views, view);
	}

	return ret;
}


BRST_EXPORT(BRST_STATUS) BRST_U3D_AddOnInstanciate(BRST_U3D u3d, BRST_JavaScript javascript)
{
	BRST_STATUS ret = BRST_OK;

	BRST_PTRACE ((" BRST_U3D_AddOnInstanciate\n"));

	if (u3d == NULL || javascript == NULL) {
		return BRST_INVALID_U3D_DATA;
	}

	ret = BRST_Dict_Add(u3d, "OnInstantiate", javascript);

	return ret;
}


BRST_EXPORT(BRST_STATUS) BRST_U3D_SetDefault3DView(BRST_U3D u3d, const char *name)
{
	BRST_STATUS ret = BRST_OK;

	BRST_PTRACE ((" BRST_U3D_SetDefault3DView\n"));

	if (u3d == NULL || name == NULL || name[0] == '\0') {
		return BRST_INVALID_U3D_DATA;
	}

	ret = BRST_Dict_Add (u3d, "DV", BRST_String_New (u3d->mmgr, name, NULL));
	return ret;
}

BRST_EXPORT(BRST_STATUS) BRST_3DView_AddNode(BRST_Dict view, BRST_Dict node)
{
	BRST_Array nodes = NULL;
	BRST_STATUS ret = BRST_OK;

	BRST_PTRACE ((" BRST_3DView_AddNode\n"));

	if (view == NULL) {
		return BRST_INVALID_U3D_DATA;
	}

	nodes = (BRST_Array)BRST_Dict_GetItem (view, "NA", BRST_OCLASS_ARRAY);
	if (nodes == NULL) {
		nodes = BRST_Array_New (view->mmgr);
		if (!nodes) {
			return BRST_Error_GetCode (view->error);
		}

		ret = BRST_Dict_Add (view, "NA", nodes);
		if (ret != BRST_OK) {
			BRST_Array_Free (nodes);
			return ret;
		}
	}

	ret = BRST_Array_Add(nodes, node);
	if (ret != BRST_OK) {
		BRST_Array_Free (nodes);
        return ret;
    }

    return ret;
}

BRST_EXPORT(BRST_Dict) BRST_3DView_CreateNode(BRST_Dict view, const char *name)
{
    BRST_Dict  node;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE ((" BRST_3DView_CreateNode\n"));

	node = BRST_Dict_New (view->mmgr);
	if (!node) {
        return NULL;
	}

	ret = BRST_Dict_AddName (node, "Type", "3DNode");
	if (ret != BRST_OK) {
		BRST_Dict_Free (node);
        return NULL;
	}

	ret = BRST_Dict_Add (node, "N", BRST_String_New (view->mmgr, name, NULL));
	if (ret != BRST_OK) {
		BRST_Dict_Free (node);
        return NULL;
    }

    return node;
}

BRST_EXPORT(BRST_STATUS) BRST_3DViewNode_SetOpacity(BRST_Dict node, BRST_REAL opacity)
{
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE ((" BRST_3DViewNode_SetOpacity\n"));

    if (node == NULL) {
        return BRST_INVALID_U3D_DATA;
	}

	ret = BRST_Dict_AddReal (node, "O", opacity);
		return ret;
	}

BRST_EXPORT(BRST_STATUS) BRST_3DViewNode_SetVisibility(BRST_Dict node, BRST_BOOL visible)
{
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE ((" BRST_3DViewNode_SetVisibility\n"));

    if (node == NULL) {
        return BRST_INVALID_U3D_DATA;
    }

	ret = BRST_Dict_AddBoolean (node, "V", visible);
		return ret;
	}

BRST_EXPORT(BRST_STATUS) BRST_3DViewNode_SetMatrix(BRST_Dict node, BRST_3DMatrix Mat3D)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Array array_m;

    BRST_PTRACE ((" BRST_3DViewNode_SetMatrix\n"));

    if (node == NULL) {
        return BRST_INVALID_U3D_DATA;
    }

    array_m = BRST_Array_New (node->mmgr);
    if (!array_m)
       return BRST_INVALID_U3D_DATA;

    ret = BRST_Dict_Add (node, "M", array_m);
	if (ret != BRST_OK) {
		return ret;
	}

    ret += BRST_Array_AddReal (array_m, Mat3D.a);
    ret += BRST_Array_AddReal (array_m, Mat3D.b);
    ret += BRST_Array_AddReal (array_m, Mat3D.c);

    ret += BRST_Array_AddReal (array_m, Mat3D.d);
    ret += BRST_Array_AddReal (array_m, Mat3D.e);
    ret += BRST_Array_AddReal (array_m, Mat3D.f);

    ret += BRST_Array_AddReal (array_m, Mat3D.g);
    ret += BRST_Array_AddReal (array_m, Mat3D.h);
    ret += BRST_Array_AddReal (array_m, Mat3D.i);

    ret += BRST_Array_AddReal (array_m, Mat3D.tx);
    ret += BRST_Array_AddReal (array_m, Mat3D.ty);
    ret += BRST_Array_AddReal (array_m, Mat3D.tz);

	return ret;
}

BRST_EXPORT(BRST_STATUS) BRST_3DView_SetLighting(BRST_Dict view, const char *scheme)
{
	BRST_STATUS ret = BRST_OK;
	BRST_Dict lighting;
	int i;
	static const char * const schemes[] =
	{ "Artwork", "None", "White", "Day", "Night", "Hard", "Primary", "Blue", "Red", "Cube", "CAD", "Headlamp" };

	BRST_PTRACE ((" BRST_3DView_SetLighting\n"));

	if (view == NULL || scheme == NULL || scheme[0] == '\0') {
		return BRST_INVALID_U3D_DATA;
	}

	for (i = 0; i < 12; i++) {
		if (!strcmp(scheme, schemes[i])) {
			break;
		}
	}

	if (i == 12) {
		return BRST_INVALID_U3D_DATA;
	}

	lighting = BRST_Dict_New (view->mmgr);
	if (!lighting) {
		return BRST_Error_GetCode (view->error);
	}

	ret = BRST_Dict_AddName (lighting, "Type", "3DLightingScheme");
	if (ret != BRST_OK) {
		BRST_Dict_Free (lighting);
		return ret;
	}

	ret = BRST_Dict_AddName (lighting, "Subtype", scheme);
	if (ret != BRST_OK) {
		BRST_Dict_Free (lighting);
		return ret;
	}

	ret = BRST_Dict_Add (view, "LS", lighting);
	if (ret != BRST_OK) {
		BRST_Dict_Free (lighting);
		return ret;
	}
	return ret;
}

BRST_EXPORT(BRST_STATUS) BRST_3DView_SetBackgroundColor(BRST_Dict view, BRST_REAL r, BRST_REAL g, BRST_REAL b)
{
	BRST_Array  color;
	BRST_STATUS ret = BRST_OK;
	BRST_Dict background;

	BRST_PTRACE ((" BRST_3DView_SetBackgroundColor\n"));

	if (view == NULL || r < 0 || r > 1 || g < 0 || g > 1 || b < 0 || b > 1) {
		return BRST_INVALID_U3D_DATA;
	}

	background = BRST_Dict_New (view->mmgr);
	if (!background) {
		return BRST_Error_GetCode (view->error);
	}

	color = BRST_Array_New (view->mmgr);
	if (!color) {
		BRST_Dict_Free (background);
		return BRST_Error_GetCode (view->error);
	}

	ret = BRST_Array_AddReal (color, r);
	if (ret != BRST_OK) {
		BRST_Array_Free (color);
		BRST_Dict_Free (background);
		return ret;
	}

	ret = BRST_Array_AddReal (color, g);
	if (ret != BRST_OK) {
		BRST_Array_Free (color);
		BRST_Dict_Free (background);
		return ret;
	}

	ret = BRST_Array_AddReal (color, b);
	if (ret != BRST_OK) {
		BRST_Array_Free (color);
		BRST_Dict_Free (background);
		return ret;
	}


	ret = BRST_Dict_AddName (background, "Type", "3DBG");
	if (ret != BRST_OK) {
		BRST_Array_Free (color);
		BRST_Dict_Free (background);
		return ret;
	}

	ret = BRST_Dict_Add (background, "C", color);
	if (ret != BRST_OK) {
		BRST_Array_Free (color);
		BRST_Dict_Free (background);
		return ret;
	}

	ret = BRST_Dict_Add (view, "BG", background);
	if (ret != BRST_OK) {
		BRST_Array_Free (color);
		BRST_Dict_Free (background);
		return ret;
	}
	return ret;
}

BRST_EXPORT(BRST_STATUS) BRST_3DView_SetPerspectiveProjection(BRST_Dict view, BRST_REAL fov)
{
	BRST_STATUS ret = BRST_OK;
	BRST_Dict projection;

	BRST_PTRACE ((" BRST_3DView_SetPerspectiveProjection\n"));

	if (view == NULL || fov < 0 || fov > 180) {
		return BRST_INVALID_U3D_DATA;
	}

	projection = BRST_Dict_New (view->mmgr);
	if (!projection) {
		return BRST_Error_GetCode (view->error);
	}

	ret = BRST_Dict_AddName (projection, "Subtype", "P");
	if (ret != BRST_OK) {
		BRST_Dict_Free (projection);
		return ret;
	}

	ret = BRST_Dict_AddName (projection, "PS", "Min");
	if (ret != BRST_OK) {
		BRST_Dict_Free (projection);
		return ret;
	}

	ret = BRST_Dict_AddReal (projection, "FOV", fov);
	if (ret != BRST_OK) {
		BRST_Dict_Free (projection);
		return ret;
	}

	ret = BRST_Dict_Add (view, "P", projection);
	if (ret != BRST_OK) {
		BRST_Dict_Free (projection);
		return ret;
	}
	return ret;
}

BRST_EXPORT(BRST_STATUS) BRST_3DView_SetOrthogonalProjection(BRST_Dict view, BRST_REAL mag)
{
	BRST_STATUS ret = BRST_OK;
	BRST_Dict projection;

	BRST_PTRACE ((" BRST_3DView_SetOrthogonalProjection\n"));

	if (view == NULL || mag <= 0) {
		return BRST_INVALID_U3D_DATA;
	}

	projection = BRST_Dict_New (view->mmgr);
	if (!projection) {
		return BRST_Error_GetCode (view->error);
	}

	ret = BRST_Dict_AddName (projection, "Subtype", "O");
	if (ret != BRST_OK) {
		BRST_Dict_Free (projection);
		return ret;
	}

	ret = BRST_Dict_AddReal (projection, "OS", mag);
	if (ret != BRST_OK) {
		BRST_Dict_Free (projection);
		return ret;
	}

	ret = BRST_Dict_Add (view, "P", projection);
	if (ret != BRST_OK) {
		BRST_Dict_Free (projection);
		return ret;
	}
	return ret;
}

#define normalize(x, y, z)		\
{					\
	BRST_REAL modulo;			\
	modulo = (float)sqrt((float)(x*x) + (float)(y*y) + (float)(z*z));	\
	if (modulo != 0.0)			\
	{					\
		x = x/modulo;			\
		y = y/modulo;			\
		z = z/modulo;			\
	}					\
}

/* building the transformation matrix*/
/* #1,#2,#3 centre of orbit coordinates (coo)*/
/* #4,#5,#6 centre of orbit to camera direction vector (c2c)*/
/* #7 orbital radius (roo)*/
/* #8 camera roll (roll)*/

BRST_EXPORT(BRST_STATUS) BRST_3DView_SetCamera(BRST_Dict view, BRST_REAL coox, BRST_REAL cooy, BRST_REAL cooz, BRST_REAL c2cx, BRST_REAL c2cy, BRST_REAL c2cz, BRST_REAL roo, BRST_REAL roll)
{
	BRST_REAL viewx, viewy, viewz;
	BRST_REAL leftx, lefty, leftz;
	BRST_REAL upx, upy, upz;
	BRST_REAL transx, transy, transz;

	BRST_Array  matrix;
	BRST_STATUS ret = BRST_OK;

	BRST_PTRACE ((" BRST_3DView_SetCamera\n"));

	if (view == NULL) {
		return BRST_INVALID_U3D_DATA;
	}

	/* view vector (opposite to c2c) */
	viewx = -c2cx;
	viewy = -c2cy;
	viewz = -c2cz;

	/* c2c = (0, -1, 0) by default */
	if (viewx == 0.0 && viewy == 0.0 && viewz == 0.0) {
		viewy = 1.0;
	}
	/* normalize view vector */
	normalize(viewx, viewy, viewz);

	/* rotation matrix */

	/* top and bottom views */
	leftx = -1.0f;
	lefty =  0.0f;
	leftz =  0.0f;

	/* up-vector */
	if (viewz < 0.0) /* top view*/
	{
		upx = 0.0f;
		upy = 1.0f;
		upz = 0.0f;
	}
	else /* bottom view*/
	{
		upx = 0.0f;
		upy =-1.0f;
		upz = 0.0f;
	}

	if ( fabs(viewx) + fabs(viewy) != 0.0f) /* other views than top and bottom*/
	{
		/* up-vector = up_world - (up_world dot view) view*/
		upx = -viewz*viewx;
		upy = -viewz*viewy;
		upz = -viewz*viewz + 1.0f;
		/* normalize up-vector*/
		normalize(upx, upy, upz);
		/* left vector = up x view*/
		leftx = viewz*upy - viewy*upz;
		lefty = viewx*upz - viewz*upx;
		leftz = viewy*upx - viewx*upy;
		/* normalize left vector*/
		normalize(leftx, lefty, leftz);
	}
	/* apply camera roll*/
	{
		BRST_REAL leftxprime, leftyprime, leftzprime;
		BRST_REAL upxprime, upyprime, upzprime;
		BRST_REAL sinroll, cosroll;

		sinroll =  (BRST_REAL)sin((roll/180.0f)*BRST_PI);
		cosroll =  (BRST_REAL)cos((roll/180.0f)*BRST_PI);
		leftxprime = leftx*cosroll + upx*sinroll;
		leftyprime = lefty*cosroll + upy*sinroll;
		leftzprime = leftz*cosroll + upz*sinroll;
		upxprime = upx*cosroll + leftx*sinroll;
		upyprime = upy*cosroll + lefty*sinroll;
		upzprime = upz*cosroll + leftz*sinroll;
		leftx = leftxprime;
		lefty = leftyprime;
		leftz = leftzprime;
		upx = upxprime;
		upy = upyprime;
		upz = upzprime;
	}

	/* translation vector*/
	roo = (BRST_REAL)fabs(roo);
	if (roo == 0.0) {
		roo = (BRST_REAL)0.000000000000000001;
	}
	transx = coox - roo*viewx;
	transy = cooy - roo*viewy;
	transz = cooz - roo*viewz;

	/* transformation matrix*/
	matrix = BRST_Array_New (view->mmgr);
	if (!matrix) {
		return BRST_Error_GetCode (view->error);
	}

	ret = BRST_Array_AddReal (matrix, leftx);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, lefty);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, leftz);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, upx);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, upy);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, upz);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, viewx);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, viewy);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, viewz);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, transx);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, transy);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, transz);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Dict_AddName (view, "MS", "M");
	if (ret != BRST_OK) goto failed;

	ret = BRST_Dict_Add (view, "C2W", matrix);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Dict_AddReal (view, "CO", roo);

failed:
	if (ret != BRST_OK) {
		BRST_Array_Free (matrix);
		return ret;
	}
	return ret;
}

BRST_EXPORT(BRST_STATUS) BRST_3DView_SetCameraByMatrix(BRST_Dict view, BRST_3DMatrix Mat3D, BRST_REAL co)
{
	BRST_Array  matrix;
	BRST_STATUS ret = BRST_OK;

	BRST_PTRACE ((" BRST_3DView_SetCameraByMatrix\n"));

	if (view == NULL) {
		return BRST_INVALID_U3D_DATA;
	}

	/* transformation matrix*/
	matrix = BRST_Array_New (view->mmgr);
	if (!matrix) {
		return BRST_Error_GetCode (view->error);
	}

	ret = BRST_Array_AddReal (matrix, Mat3D.a);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.b);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.c);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.d);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.e);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.f);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.g);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.h);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.i);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.tx);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.ty);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Array_AddReal (matrix, Mat3D.tz);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Dict_AddName (view, "MS", "M");
	if (ret != BRST_OK) goto failed;

	ret = BRST_Dict_Add (view, "C2W", matrix);
	if (ret != BRST_OK) goto failed;

	ret = BRST_Dict_AddReal (view, "CO", co);
	if (ret != BRST_OK) goto failed;

failed:
	if (ret != BRST_OK) {
		BRST_Array_Free (matrix);
		return ret;
	}
	return ret;
}

BRST_EXPORT(BRST_STATUS) BRST_3DView_SetCrossSectionOn  (BRST_Dict      view,
                                                         BRST_Point3D   center,
                                                         BRST_REAL      Roll,
                                                         BRST_REAL      Pitch,
                                                         BRST_REAL      opacity,
                                                         BRST_BOOL      showintersection)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Array array_b;
    BRST_Array array_sa;
    BRST_Dict crosssection;

    BRST_PTRACE ((" BRST_3DView_SetCrossSectionOn\n"));

    if (view == NULL) {
        return BRST_INVALID_U3D_DATA;
    }

    crosssection = BRST_Dict_New (view->mmgr);
    if (!crosssection) {
        return BRST_Error_GetCode (view->error);
    }

    ret = BRST_Dict_AddName (crosssection, "Type", "3DCrossSection");
    if (ret != BRST_OK) {
        BRST_Dict_Free (crosssection);
        return ret;
    }

    array_b = BRST_Array_New (view->mmgr);
    if (!array_b){
        BRST_Dict_Free (crosssection);
        return BRST_Error_GetCode (view->error);
    }

    if (BRST_Dict_Add (crosssection, "C", array_b) != BRST_OK)
    {
        BRST_Dict_Free (crosssection);
        return BRST_INVALID_U3D_DATA;
    }

    ret += BRST_Array_AddReal (array_b, center.x);
    ret += BRST_Array_AddReal (array_b, center.y);
    ret += BRST_Array_AddReal (array_b, center.z);

    array_b = BRST_Array_New (view->mmgr);
    if (!array_b){
        BRST_Dict_Free (crosssection);
        return BRST_Error_GetCode (view->error);
    }

    if (BRST_Dict_Add (crosssection, "O", array_b) != BRST_OK)
    {
        BRST_Dict_Free (crosssection);
        return BRST_INVALID_U3D_DATA;
    }

    ret += BRST_Array_AddNull (array_b);
    ret += BRST_Array_AddReal (array_b, Roll);
    ret += BRST_Array_AddReal (array_b, Pitch);

    ret += BRST_Dict_AddReal(crosssection, "PO", opacity);

    ret += BRST_Dict_AddBoolean(crosssection, "IV", showintersection);

    array_b = BRST_Array_New (view->mmgr);
    if (!array_b){
        BRST_Dict_Free (crosssection);
        return BRST_Error_GetCode (view->error);
    }
    if (BRST_Dict_Add (crosssection, "IC", array_b) != BRST_OK)
    {
        BRST_Dict_Free (crosssection);
        return BRST_INVALID_U3D_DATA;
    }
    ret += BRST_Array_AddName (array_b, "DeviceRGB");
    ret += BRST_Array_AddReal (array_b, 1.0);
    ret += BRST_Array_AddReal (array_b, 0.0);
    ret += BRST_Array_AddReal (array_b, 0.0);

    array_sa = BRST_Array_New (view->mmgr);
    if (!array_sa){
        BRST_Dict_Free (crosssection);
        return BRST_Error_GetCode (view->error);
    }

    if (BRST_Dict_Add (view, "SA", array_sa) != BRST_OK)
    {
        BRST_Dict_Free (crosssection);
        return BRST_INVALID_U3D_DATA;
    }

    if (BRST_Array_Add(array_sa, crosssection) != BRST_OK)
    {
        BRST_Dict_Free (crosssection);
        return BRST_INVALID_U3D_DATA;
    }

    return ret;
}

BRST_EXPORT(BRST_STATUS) BRST_3DView_SetCrossSectionOff(BRST_Dict view)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Array array_sa;

    BRST_PTRACE ((" BRST_3DView_SetCrossSectionOff\n"));

    if (view == NULL) {
        return BRST_INVALID_U3D_DATA;
    }

    array_sa = BRST_Array_New (view->mmgr);
    if (!array_sa){
        return BRST_Error_GetCode (view->error);
    }

    if (BRST_Dict_Add (view, "SA", array_sa) != BRST_OK)
    {
        return BRST_INVALID_U3D_DATA;
    }

    return ret;
}

BRST_Dict BRST_3DView_New( BRST_MMgr  mmgr, BRST_Xref  xref, BRST_U3D u3d, const char *name)
{
	BRST_STATUS ret = BRST_OK;
	BRST_Dict view;

	BRST_PTRACE ((" BRST_3DView_New\n"));

	if (name == NULL || name[0] == '\0') {
		return NULL;
	}

	view = BRST_Dict_New (mmgr);
	if (!view) {
		return NULL;
	}

	if (BRST_Xref_Add (xref, view) != BRST_OK)
        return NULL;

	ret = BRST_Dict_AddName (view, "TYPE", "3DView");
	if (ret != BRST_OK) {
		BRST_Dict_Free (view);
		return NULL;
	}

	ret = BRST_Dict_Add (view, "XN", BRST_String_New (mmgr, name, NULL));
	if (ret != BRST_OK) {
		BRST_Dict_Free (view);
		return NULL;
	}

	ret = BRST_Dict_Add (view, "IN", BRST_String_New (mmgr, name, NULL));
	if (ret != BRST_OK) {
		BRST_Dict_Free (view);
		return NULL;
	}

	ret = BRST_U3D_Add3DView( u3d, view);
	if (ret != BRST_OK) {
		BRST_Dict_Free (view);
		return NULL;
	}

	return view;
}


BRST_EXPORT(BRST_STATUS)
BRST_3DView_Add3DC3DMeasure(BRST_Dict       view,
							BRST_3DMeasure measure)
{

	BRST_STATUS ret = BRST_OK;
	BRST_Array array;
	void* a;

	a = BRST_Dict_GetItem (view, "MA", BRST_OCLASS_ARRAY);

	if ( a )
	{
		array = (BRST_Array)a;
	}
	else
	{
		array = BRST_Array_New (view->mmgr);
		if (!array)
			return 0;

		if (BRST_Dict_Add (view, "MA", array) != BRST_OK)
			return 0;
	}

	ret = BRST_Array_Add(array, measure);

	return ret;
}


BRST_EXPORT(BRST_JavaScript) BRST_CreateJavaScript( BRST_Doc pdf, const char *code )
{
	BRST_JavaScript javaScript;
	BRST_UINT len ;

	BRST_PTRACE ((" BRST_CreateJavaScript\n"));

	javaScript = (BRST_JavaScript) BRST_DictStream_New(pdf->mmgr, pdf->xref);
	if (!javaScript) {
		return NULL;
	}

	javaScript->filter = BRST_STREAM_FILTER_FLATE_DECODE;

	len = (BRST_UINT)strlen(code);
	if (BRST_Stream_Write (javaScript->stream, (BRST_BYTE *)code, len) != BRST_OK) {
		BRST_Dict_Free(javaScript);
		return NULL;
	}

	return javaScript;
}

BRST_EXPORT(BRST_JavaScript) BRST_LoadJSFromFile  (BRST_Doc pdf, const char *filename)
{
	BRST_Stream js_data;
	BRST_JavaScript js = NULL;

	BRST_PTRACE ((" BRST_LoadJSFromFile\n"));

	if (!BRST_HasDoc (pdf)) {
		return NULL;
	}

	/* create file stream */
	js_data = BRST_FileReader_New (pdf->mmgr, filename);

	if (!BRST_Stream_Validate (js_data)) {
		BRST_Stream_Free (js_data);
		return NULL;
	}

	js = (BRST_JavaScript) BRST_DictStream_New(pdf->mmgr, pdf->xref);
	if (!js) {
		BRST_Stream_Free (js_data);
		return NULL;
	}

	js->filter = BRST_STREAM_FILTER_FLATE_DECODE; // or BRST_STREAM_FILTER_NONE

	for (;;) {
		BRST_BYTE buf[BRST_STREAM_BUF_SIZ];
		BRST_UINT len = BRST_STREAM_BUF_SIZ;
		BRST_STATUS ret = BRST_Stream_Read (js_data, buf, &len);

		if (ret != BRST_OK) {
			if (ret == BRST_STREAM_EOF) {
				if (len > 0) {
					ret = BRST_Stream_Write (js->stream, buf, len);
					if (ret != BRST_OK) {
						BRST_Stream_Free (js_data);
						BRST_Dict_Free(js);
						return NULL;
					}
				}
				break;
			} else {
				BRST_Stream_Free (js_data);
				BRST_Dict_Free(js);
				return NULL;
			}
		}

		if (BRST_Stream_Write (js->stream, buf, len) != BRST_OK) {
			BRST_Stream_Free (js_data);
			BRST_Dict_Free(js);
			return NULL;
		}
	}

	/* destroy file stream */
	BRST_Stream_Free (js_data);

	return js;
}

#undef normalize
