#ifndef RENDERINGFLAGS_H
#define RENDERINGFLAGS_H

enum CREVRenderingFlag
{
	RENDERINGFLAG_SPRITE,
	RENDERINGFLAG_BACKGROUND,
	RENDERINGFLAG_FOREGROUND
};

/*Desciprtion of CREVRenderingFlag members:
 *enum CREVRenderingFlag
 *
 *CRE_V_TEXTURE_SPRITE
 * Flag to render a texture as a sprite. In the middle priority between
 * background and foreground.
 *
 *CRE_V_TEXTURE_BACKGROUND
 * Flag to render a texture as a background. The least priority
 * rendering type
 *
 *CRE_V_TEXTURE_FOREGROUND
 * Flag to render a texture as a foreground. The most priority
 * rendering type
 *
*/

#endif //RENDERINGFLAGS_H