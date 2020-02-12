#ifndef RENDERINGFLAGS_H
#define RENDERINGFLAGS_H

enum RENDERING_FLAG
{
	RENDERINGFLAG_SPRITE,
	RENDERINGFLAG_BACKGROUND,
	RENDERINGFLAG_FOREGROUND,
    RENDERINGFLAG_STATIC_BACKGROUND,
    RENDERINGFLAG_STATIC_FOREGROUND
};

/* Desciprtion of RENDERING_FLAGS members:
 * enum RENDERINGFLAG
 *
 * RENDERINGFLAG_SPRITE
 * Flag to render a texture as a sprite. In the middle priority between
 * background and foreground.
 *
 * RENDERINGFLAG_BACKGROUND
 * Flag to render a texture as a background. The second least priority
 * rendering type behind RENDERINGFLAG_STATIC_BACKGROUND.
 *
 * RENDERINGFLAG_FOREGROUND
 * Flag to render a texture as a foreground. The second highest priority
 * rendering type behind RENDERINGFLAG_STATIC_FOREGROUND.
 *
 * RENDERINGFLAG_STATIC_BACKGROUND
 * Flag to render a background texture that fits the entire screen
 * and does not change position relative to the viewport. Like
 * background  textures, is the least priority rendering type.
 *
 * RENDERINGFLAG_STATIC_FOREGROUND
 * Flag to render a foreground texture that fits the entire screen
 * and does not change position relative to the viewport. Like
 * foregournd textures, is the most priority rendering type.
 *
 *
 * Rendering priority (high to low)
 * RENDERINGFLAG_STATIC_FOREGROUND
 * RENDERINGFLAG_FOREGROUND
 * RENDERINGFLAG_SPRITE
 * RENDERINGFLAG_BACKGROUND
 * RENDERINGFLAG_STATIC_BACKGROUND
 *
*/

#endif //RENDERINGFLAGS_H