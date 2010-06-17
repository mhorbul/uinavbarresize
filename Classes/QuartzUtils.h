/** Constants for various commonly used colors. */
extern CGColorRef kBlackColor, kWhiteColor, 
kTranslucentGrayColor, kTranslucentLightGrayColor, 
kTranslucentWhiteColor, kAlmostInvisibleWhiteColor,
kHighlightColor;

#if TARGET_OS_IPHONE
// These don't exist on iPhone, so I implement them:
CGColorRef CreateGray(CGFloat gray, CGFloat alpha);
CGColorRef CreateRGB(CGFloat red, CGFloat green, CGFloat blue, CGFloat alpha);
#else
#define CreateGray  CGColorCreateGenericGray
#define CreateRGB   CGColorCreateGenericRGB
#endif


/** Loads an image or pattern file into a CGImage or CGPattern.
 If the name begins with "/", it's interpreted as an absolute filesystem path.
 Otherwise, it's the name of a resource that's looked up in the app bundle.
 The image must exist, or an assertion-failure exception will be raised!
 Loaded images/patterns are cached in memory, so subsequent calls with the same name
 are very fast.
 The caller must NOT release the result, since it's retained in the cache. */
CGImageRef GetCGImageNamed( NSString *name );
CGColorRef GetCGPatternNamed( NSString *name );

#if ! TARGET_OS_IPHONE
/** Is it possible to read a CGImage from this pasteboard? */
BOOL CanGetCGImageFromPasteboard( NSPasteboard *pb );
/** Loads image data from the pasteboard into a CGImage. */
CGImageRef GetCGImageFromPasteboard( NSPasteboard *pb, id<NSDraggingInfo>dragInfo );
#endif

CGImageRef CreateScaledImage( CGImageRef srcImage, CGFloat scale );
CGImageRef GetScaledImageNamed( NSString *imageName, CGFloat scale );

/** Creates a CGPattern from a CGImage. Caller must release it. */
CGPatternRef CreateImagePattern( CGImageRef image );

/** Creates a CGColor that draws the given CGImage as a pattern. Caller must release it. */
CGColorRef CreatePatternColor( CGImageRef image );

/** Returns the alpha value of a single pixel in a CGImage, scaled to a particular size. */
float GetPixelAlpha( CGImageRef image, CGSize imageSize, CGPoint pt );

/** Returns the center point of a CGRect. */
static inline CGPoint GetCGRectCenter( CGRect rect ) {
    return CGPointMake(CGRectGetMidX(rect),CGRectGetMidY(rect));
}

void AddRoundRect( CGContextRef ctx, CGRect rect, CGFloat radius );
