#ifndef XVISUAL_INFO_H
#define XVISUAL_INFO_H

/* Visual information mask bits */

#define   VisualNoMask                0x0
#define   VisualIDMask                0x1

#define   VisualScreenMask            0x2
#define   VisualDepthMask             0x4
#define   VisualClassMask             0x8
#define   VisualRedMaskMask           0x10
#define   VisualGreenMaskMask         0x20
#define   VisualBlueMaskMask          0x40
#define   VisualColormapSizeMask      0x80
#define   VisualBitsPerRGBMask        0x100
#define   VisualAllMask               0x1FF
/* Values */

typedef struct {
    Visual *visual;
    VisualID visualid;
    int screen;
    int depth;
    int class_;
    unsigned long red_mask;
    unsigned long green_mask;
    unsigned long blue_mask;
    int colormap_size;
    int bits_per_rgb;
} XVisualInfo_Fixed;

#endif
