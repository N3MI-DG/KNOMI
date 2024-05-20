#include "../ui.h"

void ui_ScreenToolIncr_screen_init(void)
{
    ui_ScreenToolIncr = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenToolIncr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenToolIncr, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenToolIncr, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ScreenToolIncr, &ui_img_bg_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label_tool_todo = lv_label_create(ui_ScreenToolIncr);
    lv_obj_set_width(ui_label_tool_todo, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_tool_todo, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_label_tool_todo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label_tool_todo, "TODO");
    lv_obj_set_style_text_color(ui_label_tool_todo, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_tool_todo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_tool_todo, &ui_font_InterSemiBold48, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ScreenToolIncr, ui_event_ScreenToolIncr, LV_EVENT_ALL, NULL);
}
