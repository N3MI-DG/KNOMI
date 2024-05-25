#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_UI_IMG_UP_PNG
#define LV_ATTRIBUTE_IMG_UI_IMG_UP_PNG
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_UI_IMG_UP_PNG uint8_t ui_img_up_png_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0xff, 0xff, 0xff, 0x9f, 	/*Color of index 1*/

  0x00, 0x00, 0x7e, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0xc0, 0x00, 
  0x00, 0x0f, 0xff, 0xf0, 0x00, 
  0x00, 0x3f, 0xc3, 0xfc, 0x00, 
  0x01, 0xff, 0x00, 0xff, 0x80, 
  0x07, 0xf8, 0x00, 0x1f, 0xe0, 
  0x3f, 0xe0, 0x00, 0x07, 0xfc, 
  0xff, 0x00, 0x00, 0x00, 0xff, 
  0xfc, 0x00, 0x00, 0x00, 0x3f, 
  0xf0, 0x00, 0x00, 0x00, 0x0f, 
};

const lv_img_dsc_t ui_img_up_png = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 40,
  .header.h = 10,
  .data_size = 58,
  .data = ui_img_up_png_map,
};
