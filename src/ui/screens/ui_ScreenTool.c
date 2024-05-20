#include "../ui.h"

void ui_ScreenTool_screen_init(void)
{
    ui_ScreenTool = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenTool, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenTool, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenTool, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ScreenTool, &ui_img_bg_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btn_tool_select = lv_imgbtn_create(ui_ScreenTool);
    lv_imgbtn_set_src(ui_btn_tool_select, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_move_png, NULL);
    lv_obj_set_height(ui_btn_tool_select, 72);
    lv_obj_set_width(ui_btn_tool_select, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_btn_tool_select, 24);
    lv_obj_set_y(ui_btn_tool_select, 45);
    lv_obj_set_style_bg_img_src(ui_btn_tool_select, &ui_img_btn_move_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_img_tool_select = lv_img_create(ui_btn_tool_select);
    // img is set depending on tool
    lv_obj_set_width(ui_img_tool_select, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_img_tool_select, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_img_tool_select, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_img_tool_select, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_img_tool_select, LV_OBJ_FLAG_SCROLLABLE);

    ui_label_tool_select = lv_label_create(ui_ScreenTool);
    lv_obj_set_width(ui_label_tool_select, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_tool_select, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_label_extruder_target, LV_ALIGN_TOP_MID);
    lv_obj_set_x(ui_label_tool_select, 35);
    lv_obj_set_y(ui_label_tool_select, 121);
    lv_label_set_text(ui_label_tool_select, "Select\n");
    lv_obj_set_style_text_font(ui_label_tool_select, &ui_font_InterSemiBold16, LV_PART_MAIN | LV_STATE_DEFAULT);



    ui_btn_tool_dock = lv_imgbtn_create(ui_ScreenTool);
    lv_imgbtn_set_src(ui_btn_tool_dock, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_move_png, NULL);
    lv_obj_set_height(ui_btn_tool_dock, 72);
    lv_obj_set_width(ui_btn_tool_dock, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_btn_tool_dock, 144);
    lv_obj_set_y(ui_btn_tool_dock, 45);

    ui_img_tool_dock = lv_img_create(ui_btn_tool_dock);
    lv_img_set_src(ui_img_tool_dock, &ui_img_dock_png);
    lv_obj_set_width(ui_img_tool_dock, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_img_tool_dock, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_img_tool_dock, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_img_tool_dock, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_img_tool_dock, LV_OBJ_FLAG_SCROLLABLE);

    ui_label_tool_dock = lv_label_create(ui_ScreenTool);
    lv_obj_set_width(ui_label_tool_dock, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_tool_dock, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_label_tool_dock, -40);
    lv_obj_set_y(ui_label_tool_dock, 121);
    lv_obj_set_align(ui_label_tool_dock, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_label_tool_dock, "Dock\n");
    lv_obj_set_style_text_font(ui_label_tool_dock, &ui_font_InterSemiBold16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btn_tool_cal = lv_imgbtn_create(ui_ScreenTool);
    lv_imgbtn_set_src(ui_btn_tool_cal, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_btn_move_png, NULL);
    lv_obj_set_height(ui_btn_tool_cal, 72);
    lv_obj_set_width(ui_btn_tool_cal, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_btn_tool_cal, 0);
    lv_obj_set_y(ui_btn_tool_cal, 134);
    lv_obj_set_align(ui_btn_tool_cal, LV_ALIGN_TOP_MID);

    ui_img_tool_cal = lv_img_create(ui_btn_tool_cal);
    lv_img_set_src(ui_img_tool_cal, &ui_img_calibrate_png);
    lv_obj_set_width(ui_img_tool_cal, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_img_tool_cal, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_img_tool_cal, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_img_tool_cal, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_img_tool_cal, LV_OBJ_FLAG_SCROLLABLE);

    ui_label_tool_cal = lv_label_create(ui_ScreenTool);
    lv_obj_set_width(ui_label_tool_cal, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_tool_cal, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_label_tool_cal, 0);
    lv_obj_set_y(ui_label_tool_cal, 8);
    lv_obj_set_align(ui_label_tool_cal, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_label_tool_cal, "Calibrate\n");
    lv_obj_set_style_text_font(ui_label_tool_cal, &ui_font_InterSemiBold16, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_add_event_cb(ui_btn_tool_select, ui_event_btn_tool_select, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btn_tool_dock, ui_event_btn_tool_dock, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_btn_tool_cal, ui_event_btn_tool_cal, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ScreenTool, ui_event_ScreenTool, LV_EVENT_ALL, NULL);
}
