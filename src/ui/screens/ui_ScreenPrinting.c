
#include "../ui.h"

void ui_ScreenPrinting_screen_init(void)
{
    // Background
    ui_ScreenPrinting = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenPrinting, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_ScreenPrinting, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenPrinting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Current extruder temp label
    ui_label_extruder_temp = lv_label_create(ui_ScreenPrinting);
    lv_obj_set_width(ui_label_extruder_temp, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_extruder_temp, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_label_extruder_temp, 0);
    lv_obj_set_y(ui_label_extruder_temp, 15);
    lv_obj_set_align(ui_label_extruder_temp, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_label_extruder_temp, "NULL");
    lv_obj_set_style_text_color(ui_label_extruder_temp, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_extruder_temp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_extruder_temp, &ui_font_InterSeimiBold32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Current extruder target
    ui_label_extruder_target = lv_label_create(ui_ScreenPrinting);
    lv_obj_set_width(ui_label_extruder_target, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_extruder_target, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_label_extruder_target, 0);
    lv_obj_set_y(ui_label_extruder_target, 50);
    lv_obj_set_align(ui_label_extruder_target, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_label_extruder_target, "NULL");
    lv_obj_set_style_text_color(ui_label_extruder_target, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_extruder_target, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_extruder_target, &ui_font_InterSemiBold20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Extruder chart
    ui_chart_extruder = lv_chart_create(ui_ScreenPrinting);
    lv_obj_set_size(ui_chart_extruder, 240, 70);
    lv_obj_center(ui_chart_extruder);
    lv_obj_set_y(ui_chart_extruder, -13);
    lv_obj_set_style_bg_opa(ui_chart_extruder, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_opa(ui_chart_extruder, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_size(ui_chart_extruder, 0, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(ui_chart_extruder, 3, LV_PART_ITEMS);

    lv_chart_set_type(ui_chart_extruder, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui_chart_extruder, 0, 0);
    lv_chart_set_point_count(ui_chart_extruder, 120);
    lv_chart_set_update_mode(ui_chart_extruder, LV_CHART_UPDATE_MODE_SHIFT);

    ui_target_temps = lv_chart_add_series(ui_chart_extruder, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    ui_actual_temps = lv_chart_add_series(ui_chart_extruder, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_SECONDARY_Y);

    // Extruder duty slider
    ui_slider_extruder_duty = lv_slider_create(ui_ScreenPrinting);
    lv_obj_set_width(ui_slider_extruder_duty, 122);
    lv_obj_set_height(ui_slider_extruder_duty, 125);

    lv_obj_set_y(ui_slider_extruder_duty, 22);
    lv_obj_set_align(ui_slider_extruder_duty, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_slider_extruder_duty,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);

    lv_obj_set_style_radius(ui_slider_extruder_duty, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_slider_extruder_duty, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_slider_extruder_duty, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_slider_extruder_duty, &ui_img_nozzle_gray_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_slider_extruder_duty, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_slider_extruder_duty, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_slider_extruder_duty, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_slider_extruder_duty, &ui_img_nozzle_red_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_slider_extruder_duty, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_slider_extruder_duty, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Extruder duty label
    ui_label_extruder_duty = lv_label_create(ui_ScreenPrinting);
    lv_obj_set_width(ui_label_extruder_duty, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_extruder_duty, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_label_extruder_duty, 0);
    lv_obj_set_y(ui_label_extruder_duty, 159);
    lv_obj_set_align(ui_label_extruder_duty, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_label_extruder_duty, "NULL");
    lv_obj_set_style_text_color(ui_label_extruder_duty, lv_color_hex(0xFFD164), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_extruder_duty, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_extruder_duty, &ui_font_InterSemiBold24, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Progress label
    ui_label_printing_progress = lv_label_create(ui_ScreenPrinting);
    lv_obj_set_width(ui_label_printing_progress, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_label_printing_progress, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_label_printing_progress, LV_ALIGN_CENTER);
    lv_label_set_text(ui_label_printing_progress, "NULL");
    lv_obj_set_style_text_color(ui_label_printing_progress, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_printing_progress, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_printing_progress, &ui_font_InterSemiBold48, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Progress arc
    ui_arc_printing_progress = lv_arc_create(ui_ScreenPrinting);
    lv_obj_set_width(ui_arc_printing_progress, 212);
    lv_obj_set_height(ui_arc_printing_progress, 212);
    lv_obj_set_align(ui_arc_printing_progress, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_arc_printing_progress,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_arc_set_value(ui_arc_printing_progress, 1);
    lv_arc_set_bg_angles(ui_arc_printing_progress, 0, 360);
    lv_arc_set_rotation(ui_arc_printing_progress, 270);
    lv_obj_set_style_arc_color(ui_arc_printing_progress, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_arc_printing_progress, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_arc_printing_progress, lv_color_hex(0xC02F30), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_arc_printing_progress, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_arc_printing_progress, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_arc_printing_progress, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_arc_printing_progress, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ScreenPrinting, ui_event_ScreenPrinting, LV_EVENT_ALL, NULL);

}
