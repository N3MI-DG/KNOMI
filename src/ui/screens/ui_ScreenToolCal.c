#include "../ui.h"

void ui_ScreenToolCal_screen_init(void)
{
    ui_ScreenToolCal = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenToolCal, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenToolCal, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenToolCal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ScreenToolCal, &ui_img_bg_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btn_tool_axis_minus = lv_imgbtn_create(ui_ScreenToolCal);
    lv_imgbtn_set_src(ui_btn_tool_axis_minus, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_rec_png, NULL);
    lv_obj_set_width(ui_btn_tool_axis_minus, 108);
    lv_obj_set_height(ui_btn_tool_axis_minus, 38);
    lv_obj_set_x(ui_btn_tool_axis_minus, 66);
    lv_obj_set_y(ui_btn_tool_axis_minus, 177);

    ui_img_tool_axis_minus = lv_img_create(ui_btn_tool_axis_minus);
    lv_img_set_src(ui_img_tool_axis_minus, &ui_img_down_png);
    lv_obj_set_width(ui_img_tool_axis_minus, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_img_tool_axis_minus, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_img_tool_axis_minus, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_img_tool_axis_minus, 0);
    lv_obj_set_y(ui_img_tool_axis_minus, 2);
    lv_obj_add_flag(ui_img_tool_axis_minus, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_img_tool_axis_minus, LV_OBJ_FLAG_SCROLLABLE);

    ui_btn_tool_axis_plus = lv_imgbtn_create(ui_ScreenToolCal);
    lv_imgbtn_set_src(ui_btn_tool_axis_plus, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_rec_png, NULL);
    lv_obj_set_width(ui_btn_tool_axis_plus, 108);
    lv_obj_set_height(ui_btn_tool_axis_plus, 38);
    lv_obj_set_x(ui_btn_tool_axis_plus, 66);
    lv_obj_set_y(ui_btn_tool_axis_plus, 25);

    ui_img_tool_axis_plus = lv_img_create(ui_btn_tool_axis_plus);
    lv_img_set_src(ui_img_tool_axis_plus, &ui_img_up_png);
    lv_obj_set_width(ui_img_tool_axis_plus, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_img_tool_axis_plus, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_img_tool_axis_plus, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_img_tool_axis_plus, 0);
    lv_obj_set_y(ui_img_tool_axis_plus, -2);
    lv_obj_add_flag(ui_img_tool_axis_plus, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_img_tool_axis_plus, LV_OBJ_FLAG_SCROLLABLE);

    ui_label_tool_axis = lv_label_create(ui_ScreenToolCal);
    lv_obj_set_width(ui_label_tool_axis, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_tool_axis, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_label_tool_axis, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_label_tool_axis, -80);
    lv_label_set_text(ui_label_tool_axis, "Y");
    lv_obj_set_style_text_color(ui_label_tool_axis, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_tool_axis, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_tool_axis, &ui_font_InterSeimiBold32, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label_tool_axis_text = lv_label_create(ui_ScreenToolCal);
    lv_obj_set_width(ui_label_tool_axis_text, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_tool_axis_text, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_label_tool_axis_text, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_label_tool_axis_text, -80);
    lv_obj_set_y(ui_label_tool_axis_text, 25);
    lv_label_set_text(ui_label_tool_axis_text, "AXIS");
    lv_obj_set_style_text_color(ui_label_tool_axis_text, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_tool_axis_text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_tool_axis_text, &ui_font_InterSemiBold18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label_tool_increment = lv_label_create(ui_ScreenToolCal);
    lv_obj_set_width(ui_label_tool_increment, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_tool_increment, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_label_tool_increment, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_label_tool_increment, 80);
    lv_label_set_text(ui_label_tool_increment, "10");
    lv_obj_set_style_text_color(ui_label_tool_increment, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_tool_increment, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_tool_increment, &ui_font_InterSeimiBold32, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label_tool_increment_text = lv_label_create(ui_ScreenToolCal);
    lv_obj_set_width(ui_label_tool_increment_text, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_tool_increment_text, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_label_tool_increment_text, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_label_tool_increment_text, 80);
    lv_obj_set_y(ui_label_tool_increment_text, 25);
    lv_label_set_text(ui_label_tool_increment_text, "mm");
    lv_obj_set_style_text_color(ui_label_tool_increment_text, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_tool_increment_text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_tool_increment_text, &ui_font_InterSemiBold18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btn_tool_config = lv_imgbtn_create(ui_ScreenToolCal);
    lv_imgbtn_set_src(ui_btn_tool_config, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_move_png, NULL);
    lv_obj_set_height(ui_btn_tool_config, 72);
    lv_obj_set_width(ui_btn_tool_config, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_btn_tool_config, LV_ALIGN_CENTER);

    ui_img_tool_increment = lv_img_create(ui_btn_tool_config);
    lv_img_set_src(ui_img_tool_increment, &ui_img_settings_png);
    lv_obj_set_width(ui_img_tool_increment, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_img_tool_increment, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_img_tool_increment, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_img_tool_increment, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_img_tool_increment, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_btn_tool_axis_minus, ui_event_btn_tool_axis_minus, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btn_tool_axis_plus, ui_event_btn_tool_axis_plus, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btn_tool_config, ui_event_btn_tool_config, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenToolCal, ui_event_ScreenToolCal, LV_EVENT_ALL, NULL);
}
