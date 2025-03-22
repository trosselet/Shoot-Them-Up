#pragma once

//#define GC

#ifdef GC
#include "GC.h"
typedef LEWindowGC LEWindow;
typedef LETextureGC LETexture;
typedef LESpriteGC LESprite;
typedef LECircleGC LECircle;
typedef LERectGC LERect;
typedef LEFontGC LEFont;
typedef LEEventGC LEEvent;
typedef LEInputGC LEInput;
typedef LEMusicGC LEMusic;
typedef LESoundGC LESound;

#else
#include "SFML.h"
typedef SFMLWindow LEWindow;
typedef SFMLTexture LETexture;
typedef SFMLSprite LESprite;
typedef SFMLCircle LECircle;
typedef SFMLRect LERect;
typedef SFMLFont LEFont;
typedef SFMLEvent LEEvent;
typedef SFMLInput LEInput;
typedef SFMLMusic LEMusic;
typedef SFMLSound LESound;

#endif
