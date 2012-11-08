//
//  redner_osc.c
//  osc
//
//  Created by Ben on 24/11/11.
//  Copyright 2011 Monash University. All rights reserved.
//

#include <main.h>



void generateDiffPreview(QLPreviewRequestRef preview, CFURLRef url, CFDictionaryRef options){
	
	CFStringRef UrlToPath;
	char path[1024], cache[1024];
	struct CGSize previewSize;
	struct stat pathStat, cacheStat;
	
	previewSize.width = 1024;
	previewSize.height = 1024;
	
	struct CGRect cgRect;
	struct CGPoint cgPoint;
	cgRect.size.width = previewSize.width;
	cgRect.size.height = previewSize.height;
	cgPoint.x = 0;
	cgPoint.y = 0;
	cgRect.origin = cgPoint;
	
	
	//Create a Cstring for the path of our file of interest.
	UrlToPath = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
	CFStringGetCString(UrlToPath, path, sizeof(path), kCFStringEncodingUTF8);
	
	//Cache stuff
	generateCachePath(cache, path);	//Generate the path where we are going to save our cache files.
	
	//Retrieve info on both cache img and structure file
	stat(path, &pathStat);
	int isCache = stat(cache, &cacheStat);
	
	
	
	//Image rendering function
	
	//Check to see if the cache image exists or if the cache image is older than the structure file.
	if(isCache == -1 || pathStat.st_mtime > cacheStat.st_mtime){
		//If case(s) matched, lets render a new image.
		renderDiffImage(path, cache);
	}
	
	
	//Create graphics contexts and start to load up the preview image.
	CGContextRef image = QLPreviewRequestCreateContext(preview, previewSize, false, options);
	
	CGDataProviderRef myProvider = CGDataProviderCreateWithFilename(cache);
    if (myProvider == NULL) {
		printf("Error: Could not load file\n");
		return;
	}
    
    CGImageRef pngimg = CGImageCreateWithJPEGDataProvider(myProvider, NULL, false, kCGRenderingIntentDefault);
	CGContextDrawImage(image, cgRect, pngimg);	//Draw the image to the context
	QLPreviewRequestFlushContext(preview, image);	//Flush the context to the screen.
}


void generateDiffThumbnail(QLThumbnailRequestRef thumbnail, CFURLRef url, CFDictionaryRef options){
	
	CFStringRef UrlToPath;
	char path[1024], cache[1024];
	struct CGSize thumbnailSize;
	struct stat pathStat, cacheStat;
	
	thumbnailSize.width = 1024;
	thumbnailSize.height = 1024;
	
	struct CGRect cgRect;
	struct CGPoint cgPoint;
	cgRect.size.width = thumbnailSize.width;
	cgRect.size.height = thumbnailSize.height;
	cgPoint.x = 0;
	cgPoint.y = 0;
	cgRect.origin = cgPoint;
	
	
	//Create a Cstring for the path of our file of interest.
	UrlToPath = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
	CFStringGetCString(UrlToPath, path, sizeof(path), kCFStringEncodingUTF8);
	
	//Cache stuff
	generateCachePath(cache, path);	//Generate the path where we are going to save our cache files.
	
	//Retrieve info on both cache img and structure file
	stat(path, &pathStat);
	int isCache = stat(cache, &cacheStat);
	
	
	
	//Image rendering function
	
	//Check to see if the cache image exists or if the cache image is older than the structure file.
	if(isCache == -1 || pathStat.st_mtime > cacheStat.st_mtime){
		//If case(s) matched, lets render a new image.
		//renderDiffImage(path, cache);
        return;
	}
	
	
	//Create graphics contexts and start to load up the thumbnail image.
	CGContextRef image = QLThumbnailRequestCreateContext(thumbnail, thumbnailSize, false, options);
	
	CGDataProviderRef myProvider = CGDataProviderCreateWithFilename(cache);
    if (myProvider == NULL) {
		printf("Error: Could not load file\n");
		return;
	}
    
    CGImageRef pngimg = CGImageCreateWithJPEGDataProvider(myProvider, NULL, false, kCGRenderingIntentDefault);
	CGContextDrawImage(image, cgRect, pngimg);	//Draw the image to the context
	QLThumbnailRequestFlushContext(thumbnail, image);	//Flush the context to the screen.
}




// Calls the custom diff2jpeg application
//
void renderDiffImage(char *path, char *cache){
	
	char cmd[1024], creatediffPath[1024];
	
	CFBundleRef Bundle = CFBundleGetBundleWithIdentifier(CFSTR(__BUNDLE_IDENTIFIER__));
	CFURLRef BundleURL = CFBundleCopyBundleURL(Bundle);
	CFStringRef cfStringRef = CFURLCopyFileSystemPath( BundleURL, kCFURLPOSIXPathStyle);
	assert(cfStringRef);
	
	CFStringGetCString(cfStringRef, creatediffPath, 1024, kCFStringEncodingASCII);
    
	
	strcpy(cmd, creatediffPath);
	strcat(cmd, "/Contents/Resources/creatediff ");
    strcat(cmd, "\"");
	strcat(cmd, path);
    strcat(cmd, "\"");
	strcat(cmd, " ");
    strcat(cmd, "\"");
	strcat(cmd, cache);
    strcat(cmd, "\"");
    
    printf("cmd: %s\n", cmd);
	
	int execute = system(cmd);
    
    if (execute != 0) {
        return;
    }
}



void generateCachePath(char *cache, char * path){
	
	char cachePath[1024];
	strcpy(cachePath, path);
	
	for(int i=0; i < sizeof(cachePath); i++){
		if(cachePath[i] == '/'){
			cachePath[i] = '.';
		}
	}
	
		sprintf(cache, "%s/diffpreview%s.jpg", __CACHE_LOCATION__, cachePath);
	
	
}

