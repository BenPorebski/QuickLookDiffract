//
//  render_osc.h
//  osc
//
//  Created by Ben on 24/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef osc_render_osc_h
#define osc_render_osc_h

void generateDiffPreview(QLPreviewRequestRef preview, CFURLRef url, CFDictionaryRef options);

void generateDiffThumbnail(QLThumbnailRequestRef thumbnail, CFURLRef url, CFDictionaryRef options);

void renderDiffImage(char *path, char *cache);

void generateCachePath(char *cache, char * path);

#endif
