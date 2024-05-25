
#include "../ui.h"

void ui_ScreenSetToolCal_screen_init(void)
{
    ui_ScreenSetToolCal = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenSetToolCal, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenSetToolCal, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenSetToolCal, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btn_set_tool_cal_save = lv_imgbtn_create(ui_ScreenSetToolCal);
    lv_imgbtn_set_src(ui_btn_set_tool_cal_save, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_dialog_png, NULL);
    lv_obj_set_width(ui_btn_set_tool_cal_save, 56);
    lv_obj_set_height(ui_btn_set_tool_cal_save, 56);
    lv_obj_set_align(ui_btn_set_tool_cal_save, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_btn_set_tool_cal_save, 0);
    lv_obj_set_y(ui_btn_set_tool_cal_save, -75);

    ui_img_set_tool_cal_save = lv_img_create(ui_btn_set_tool_cal_save);
    lv_img_set_src(ui_img_set_tool_cal_save, &ui_img_save_png);
    lv_obj_set_width(ui_img_set_tool_cal_save, 16);
    lv_obj_set_height(ui_img_set_tool_cal_save, 16);
    lv_obj_set_align(ui_img_set_tool_cal_save, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_img_set_tool_cal_save, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_img_set_tool_cal_save, LV_OBJ_FLAG_SCROLLABLE);

    ui_roller_set_axis = lv_roller_create(ui_ScreenSetToolCal);
    lv_obj_set_width(ui_roller_set_axis, 108);
    lv_obj_set_height(ui_roller_set_axis, 120);
    lv_obj_set_x(ui_roller_set_axis, 2);
    lv_obj_set_y(ui_roller_set_axis, 0);
    lv_obj_set_align(ui_roller_set_axis, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_text_color(ui_roller_set_axis, lv_color_hex(0x7F7F7F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_roller_set_axis, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_roller_set_axis, &ui_font_InterSemiBold16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_roller_set_axis, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_roller_set_axis, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_roller_set_axis, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_roller_set_axis, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_font(ui_roller_set_axis, &ui_font_InterSemiBold20, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_roller_set_axis, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_roller_set_axis, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_roller_set_axis, &ui_img_btn_rec_png, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_roller_set_increment = lv_roller_create(ui_ScreenSetToolCal);
    lv_obj_set_width(ui_roller_set_increment, 108);
    lv_obj_set_height(ui_roller_set_increment, 120);
    lv_obj_set_x(ui_roller_set_increment, -2);
    lv_obj_set_y(ui_roller_set_increment, 0);
    lv_obj_set_align(ui_roller_set_increment, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_text_color(ui_roller_set_increment, lv_color_hex(0x7F7F7F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_roller_set_increment, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_roller_set_increment, &ui_font_InterSemiBold16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_roller_set_increment, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_roller_set_increment, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_roller_set_increment, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_roller_set_increment, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_font(ui_roller_set_increment, &ui_font_InterSemiBold20, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_roller_set_increment, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_roller_set_increment, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_roller_set_increment, &ui_img_btn_rec_png, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_btn_set_tool_cal_ok = lv_imgbtn_create(ui_ScreenSetToolCal);
    lv_imgbtn_set_src(ui_btn_set_tool_cal_ok, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_dialog_png, NULL);
    lv_obj_set_width(ui_btn_set_tool_cal_ok, 56);
    lv_obj_set_height(ui_btn_set_tool_cal_ok, 56);
    lv_obj_set_x(ui_btn_set_tool_cal_ok, -45);
    lv_obj_set_y(ui_btn_set_tool_cal_ok, 165);
    lv_obj_set_align(ui_btn_set_tool_cal_ok, LV_ALIGN_TOP_MID);

    ui_img_set_tool_cal_ok = lv_img_create(ui_btn_set_tool_cal_ok);
    lv_img_set_src(ui_img_set_tool_cal_ok, &ui_img_img_ok_png);
    lv_obj_set_width(ui_img_set_tool_cal_ok, 24);
    lv_obj_set_height(ui_img_set_tool_cal_ok, 17);
    lv_obj_set_align(ui_img_set_tool_cal_ok, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_img_set_tool_cal_ok, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_img_set_tool_cal_ok, LV_OBJ_FLAG_SCROLLABLE);

    ui_btn_set_tool_cal_test = lv_imgbtn_create(ui_ScreenSetToolCal);
    lv_imgbtn_set_src(ui_btn_set_tool_cal_test, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_dialog_png, NULL);
    lv_obj_set_width(ui_btn_set_tool_cal_test, 56);
    lv_obj_set_height(ui_btn_set_tool_cal_test, 56);
    lv_obj_set_x(ui_btn_set_tool_cal_test, 45);
    lv_obj_set_y(ui_btn_set_tool_cal_test, 165);
    lv_obj_set_align(ui_btn_set_tool_cal_test, LV_ALIGN_TOP_MID);

    ui_label_set_tool_cal_test = lv_label_create(ui_btn_set_tool_cal_test);
    lv_obj_set_width(ui_label_set_tool_cal_test, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_set_tool_cal_test, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_label_set_tool_cal_test, -2);
    lv_obj_set_y(ui_label_set_tool_cal_test, -1);
    lv_obj_set_align(ui_label_set_tool_cal_test, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label_set_tool_cal_test, "Test");
    lv_obj_set_style_text_font(ui_label_set_tool_cal_test, &ui_font_InterSemiBold14, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_add_event_cb(ui_btn_set_tool_cal_test, ui_event_btn_set_tool_cal_test, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btn_set_tool_cal_ok, ui_event_btn_set_tool_cal_ok, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btn_set_tool_cal_save, ui_event_btn_set_tool_cal_save, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenSetToolCal, ui_event_ScreenSetToolCal, LV_EVENT_ALL, NULL);

}
