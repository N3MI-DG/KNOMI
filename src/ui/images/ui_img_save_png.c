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

#ifndef LV_ATTRIBUTE_IMG_UI_IMG_SAVE_PNG
#define LV_ATTRIBUTE_IMG_UI_IMG_SAVE_PNG
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_UI_IMG_SAVE_PNG uint8_t ui_img_save_png_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0xfe, 0xfe, 0xfe, 0xdf, 	/*Color of index 1*/

  0xff, 0xfc, 
  0xf0, 0x7e, 
  0xf0, 0xff, 
  0xff, 0xff, 
  0xff, 0xff, 
  0xff, 0xff, 
  0xff, 0xff, 
  0xff, 0xff, 
  0xf0, 0x0f, 
  0xf0, 0x0f, 
  0xf0, 0x0f, 
  0xf0, 0x0f, 
  0xf0, 0x0f, 
  0xf0, 0x0f, 
  0xf0, 0x0f, 
  0xff, 0xff, 
};

const lv_img_dsc_t ui_img_save_png = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 16,
  .header.h = 16,
  .data_size = 40,
  .data = ui_img_save_png_map,
};
