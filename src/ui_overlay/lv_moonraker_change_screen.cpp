#include "ui/ui.h"
#include "knomi.h"
#include "moonraker.h"
#include "lv_overlay.h"

typedef enum {
    LV_MOONRAKER_STATE_IDLE = 0,
    LV_MOONRAKER_STATE_HOMING,
    LV_MOONRAKER_STATE_PROBING,
    LV_MOONRAKER_STATE_QGLING,
    LV_MOONRAKER_STATE_NOZZLE_HEATING,
    LV_MOONRAKER_STATE_BED_HEATING,
    LV_MOONRAKER_STATE_PRINTING,
    LV_MOONRAKER_STATE_TOOL_CHANGE,
    LV_SCREEN_STATE_INIT,
    LV_SCREEN_STATE_IDLE,
    LV_SCREEN_HEATED,
    LV_SCREEN_PRINT,
    LV_SCREEN_PRINT_OK,
    LV_SCREEN_PRINTED,
    LV_SCREEN_STATE_PLAYING,
    LV_SCREEN_TC_DOCKED,
    LV_SCREEN_TC_SELECTED
} lv_screen_state_t;

lv_obj_t * ui_img_main_gif;

const lv_img_dsc_t * gif_idle[] = {&gif_voron};

static char string_buffer[10];
static lv_screen_state_t lv_screen_state = LV_MOONRAKER_STATE_IDLE;
static lv_obj_t * ui_ScreenIdle = NULL;
static lv_obj_t * ui_ScreenNow = NULL;
static lv_img_dsc_t ui_tool_img = ui_img_T0_png;

static void lv_goto_busy_screen(lv_obj_t * screen, lv_screen_state_t state, const lv_img_dsc_t * gif) {
    if (lv_screen_state == state) return;

    // dont restart animation for toolchange delay
    if (lv_screen_state == LV_MOONRAKER_STATE_TOOL_CHANGE && state == LV_SCREEN_TC_DOCKED) return;
    if (lv_screen_state == LV_MOONRAKER_STATE_TOOL_CHANGE && state == LV_SCREEN_TC_SELECTED) return;

    lv_screen_state = state;

    if (gif) lv_gif_set_src(ui_img_main_gif, gif);
    lv_obj_clear_flag(ui_ScreenMainGif, LV_OBJ_FLAG_CLICKABLE);

    // backup now screen, cause lv_scr_act() is delayed updates
    if (ui_ScreenNow == NULL) ui_ScreenNow = lv_scr_act();
    if (screen && screen != ui_ScreenNow) {
        // backup screen before jump
        if (ui_ScreenIdle == NULL) ui_ScreenIdle = ui_ScreenNow;
        ui_ScreenNow = screen;
        _ui_screen_change(&screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 500, 0, NULL);
    }
}

static void lv_goto_idle_screen(void) {
    if (lv_screen_state == LV_MOONRAKER_STATE_IDLE) return;
    lv_screen_state = LV_MOONRAKER_STATE_IDLE;

    //
    lv_gif_set_src(ui_img_main_gif, gif_idle[0]);
    lv_obj_add_flag(ui_ScreenMainGif, LV_OBJ_FLAG_CLICKABLE);

    // goto the screen backed up before
    if (ui_ScreenIdle && (ui_ScreenIdle != lv_scr_act())) {
        _ui_screen_change(&ui_ScreenIdle, LV_SCR_LOAD_ANIM_MOVE_TOP, 500, 0, NULL);
    }
    ui_ScreenIdle = NULL;
    ui_ScreenNow = NULL;
}


#define TEMPERATURE_ERROR_RANGE 2

bool moonraker_nozzle_is_heating(void) {
    if (moonraker.data.heating_nozzle)
        return true;
    if (moonraker.data.nozzle_actual + TEMPERATURE_ERROR_RANGE < moonraker.data.nozzle_target)
        return true;
    if ((moonraker.data.nozzle_target != 0) && (moonraker.data.nozzle_target + TEMPERATURE_ERROR_RANGE < moonraker.data.nozzle_actual))
        return true;
    return false;
}

bool moonraker_bed_is_heating(void) {
    if (moonraker.data.heating_bed)
        return true;
    if (moonraker.data.bed_actual + TEMPERATURE_ERROR_RANGE < moonraker.data.bed_target)
        return true;
    if ((moonraker.data.bed_target != 0) && (moonraker.data.bed_target + TEMPERATURE_ERROR_RANGE < moonraker.data.bed_actual))
        return true;
    return false;
}

// screen change according to moonraker status
void lv_loop_moonraker_change_screen(void) {
    static lv_screen_state_t screen_state = LV_SCREEN_STATE_INIT;
    if (moonraker.data.homing) {
        lv_goto_busy_screen(ui_ScreenMainGif, LV_MOONRAKER_STATE_HOMING, &gif_homing);
        return;
    }
    if (moonraker.data.probing) {
        lv_goto_busy_screen(ui_ScreenMainGif, LV_MOONRAKER_STATE_PROBING, &gif_probing);
        return;
    }
    if (moonraker.data.qgling) {
        lv_goto_busy_screen(ui_ScreenMainGif, LV_MOONRAKER_STATE_QGLING, &gif_qgling);
        return;
    }
    if (!moonraker.data.printing) {
        if (moonraker_nozzle_is_heating()) {
            lv_goto_busy_screen(ui_ScreenHeatingNozzle, LV_MOONRAKER_STATE_NOZZLE_HEATING, NULL);
            return;
        }
        if (moonraker_bed_is_heating()) {
            lv_goto_busy_screen(ui_ScreenHeatingBed, LV_MOONRAKER_STATE_BED_HEATING, NULL);
            return;
        }
    }

    if (moonraker.data.dropoff >= 0) {
        if (knomi_config.moonraker_tool[0] == char(48 + moonraker.data.dropoff)) { // Knomi tool is being docked
            lv_goto_busy_screen(ui_ScreenMainGif, LV_MOONRAKER_STATE_TOOL_CHANGE, &gif_docked);
            screen_state = LV_SCREEN_TC_DOCKED; // continue to animate for duration after moonraker data changes
            return;
        }
    }

    static uint32_t pickup_delay_ms = 0;

    if (moonraker.data.pickup >= 0) {
        // Knomi tool is being selected
        if (knomi_config.moonraker_tool[0] == char(48 + moonraker.data.pickup)) { 
            // pickup gcode triggers early, delay animation when first triggered
            if (!pickup_delay_ms) {
                pickup_delay_ms = millis() + 4000;
            }

            if (millis() > pickup_delay_ms) {
                lv_goto_busy_screen(ui_ScreenMainGif, LV_MOONRAKER_STATE_TOOL_CHANGE, &gif_print_ok);
                screen_state = LV_SCREEN_TC_SELECTED; // continue to animate for duration after moonraker data changes
                return;
            }
        }
    }

    static lv_screen_state_t playing_next_state = LV_SCREEN_STATE_INIT;
    static uint32_t playing_ms = 0;
    static lv_screen_state_t playing_state;
    static const lv_img_dsc_t * playing_img;

    switch (screen_state) {
        case LV_SCREEN_STATE_INIT:
            break;
        case LV_SCREEN_STATE_IDLE:
            if (!moonraker.data.printing) {
                screen_state = LV_SCREEN_PRINT_OK;
                return;
            }
            break;
        case LV_SCREEN_HEATED:
            playing_state = LV_SCREEN_HEATED;
            playing_img = &gif_heated;
            screen_state = LV_SCREEN_STATE_PLAYING;
            playing_next_state = LV_SCREEN_PRINT;
            playing_ms = millis() + 7000;
            return;
        case LV_SCREEN_PRINT:
            lv_goto_busy_screen(ui_ScreenMainGif, LV_SCREEN_PRINT, &gif_print);
            if (moonraker.data.progress >= 0.01 || !moonraker.data.printing)
                screen_state = LV_SCREEN_STATE_IDLE;
            return;
        case LV_SCREEN_STATE_PLAYING:
            if (playing_ms > millis()) {
                lv_goto_busy_screen(ui_ScreenMainGif, playing_state, playing_img);
                return;
            }
            screen_state = playing_next_state;
            return;
        case LV_SCREEN_PRINT_OK:
            playing_state = LV_SCREEN_PRINT_OK;
            playing_img = &gif_print_ok;
            screen_state = LV_SCREEN_STATE_PLAYING;
            playing_next_state = LV_SCREEN_PRINTED;
            playing_ms = millis() + 1600;
            return;
        case LV_SCREEN_PRINTED:
            playing_state = LV_SCREEN_PRINTED;
            playing_img = &gif_printed;
            screen_state = LV_SCREEN_STATE_PLAYING;
            playing_next_state = LV_SCREEN_STATE_INIT;
            playing_ms = millis() + 7000;
            return;
        case LV_SCREEN_TC_DOCKED:
            playing_state = LV_SCREEN_TC_DOCKED;
            playing_img = &gif_docked;
            screen_state = LV_SCREEN_STATE_PLAYING;
            if (moonraker.data.printing) {
                playing_next_state = LV_SCREEN_STATE_IDLE;
            } else {
                playing_next_state = LV_SCREEN_STATE_INIT;
            }
            playing_ms = millis() + 3000;
            return;
        case LV_SCREEN_TC_SELECTED:
            playing_state = LV_SCREEN_TC_SELECTED;
            playing_img = &gif_print_ok;
            screen_state = LV_SCREEN_STATE_PLAYING;
            if (moonraker.data.printing) {
                playing_next_state = LV_SCREEN_STATE_IDLE;
            } else {
                playing_next_state = LV_SCREEN_STATE_INIT;
            }
            playing_ms = millis() + 2000;
            pickup_delay_ms = 0;
            return;
    }

    // Printing must be lastest, the lowest priority
    // That The status screen(homing, heating, etc.) can occupy this screen
    if (moonraker.data.printing) {
        lv_goto_busy_screen(ui_ScreenPrinting, LV_MOONRAKER_STATE_PRINTING, NULL);
        return;
    }
    // back to previous screen
    lv_goto_idle_screen();

    if (lv_scr_act() == ui_ScreenMainGif) {
        static uint8_t gif_idle_index = 0;
        static uint32_t gif_idle_ms = 0;

        if (gif_idle_ms < millis()) {
            lv_gif_set_src(ui_img_main_gif, gif_idle[gif_idle_index]);
            gif_idle_index = (gif_idle_index + 1) % ACOUNT(gif_idle);
            gif_idle_ms = millis() + 4500; // 4.5s
        }
    }
}

void lv_loop_moonraker_change_screen_value(void) {
    // nozzle target
    static int16_t nozzle_target;
    if (nozzle_target != moonraker.data.nozzle_target) {
        nozzle_target = moonraker.data.nozzle_target;
        snprintf(string_buffer, sizeof(string_buffer), "%d℃", nozzle_target);
        lv_label_set_text(ui_label_extruder_target, string_buffer);
        lv_label_set_text(ui_label_temp_nozzle_target, string_buffer);
        lv_label_set_text(ui_label_heating_nozzle_target, string_buffer);
    }
    // nozzle actual
    static int16_t nozzle_actual;
    if (nozzle_actual != moonraker.data.nozzle_actual) {
        nozzle_actual = moonraker.data.nozzle_actual;
        snprintf(string_buffer, sizeof(string_buffer), "%d℃", nozzle_actual);
        lv_label_set_text(ui_label_extruder_actual, string_buffer);
        lv_label_set_text(ui_label_temp_nozzle_actual, string_buffer);
        lv_label_set_text(ui_label_heating_nozzle_actual, string_buffer);
    }
    // bed target
    static int16_t bed_target;
    if (bed_target != moonraker.data.bed_target) {
        bed_target = moonraker.data.bed_target;
        snprintf(string_buffer, sizeof(string_buffer), "%d℃", bed_target);
        lv_label_set_text(ui_label_temp_bed_target, string_buffer);
        lv_label_set_text(ui_label_heating_bed_target, string_buffer);
    }
    // bed actual
    static int16_t bed_actual;
    if (bed_actual != moonraker.data.bed_actual) {
        bed_actual = moonraker.data.bed_actual;
        snprintf(string_buffer, sizeof(string_buffer), "%d℃", bed_actual);
        lv_label_set_text(ui_label_temp_bed_actual, string_buffer);
        lv_label_set_text(ui_label_heating_bed_actual, string_buffer);
    }
    // extruder
    static float extruder_temp;
    static float extruder_target;
    static int8_t extruder_duty;
    if (moonraker.data.printing) {
        extruder_temp = moonraker.data.extruder_temp;
        extruder_target = moonraker.data.extruder_target;
        extruder_duty = moonraker.data.extruder_duty;
        
        if (extruder_target > 0) {
            lv_obj_add_flag(ui_label_printing_progress, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_arc_printing_progress, LV_OBJ_FLAG_HIDDEN);

            lv_obj_clear_flag(ui_label_extruder_temp, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_label_extruder_target, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_chart_extruder, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_label_extruder_duty, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_slider_extruder_duty, LV_OBJ_FLAG_HIDDEN);

            // Update extruder temp
            snprintf(string_buffer, sizeof(string_buffer), "%.1f%℃", extruder_temp);
            lv_label_set_text(ui_label_extruder_temp, string_buffer);

            // Update target temp
            snprintf(string_buffer, sizeof(string_buffer), "%.1f%℃", extruder_target);
            lv_label_set_text(ui_label_extruder_target, string_buffer);

            // Update chart
            uint32_t chart_max = moonraker.data.extruder_targets[0] * 100;
            uint32_t chart_min = moonraker.data.extruder_targets[0] * 100;

            for(int16_t i = 0; i < CHART_SECONDS; i++) {
                uint32_t temp = moonraker.data.extruder_temps[i] * 100;
                uint32_t target = moonraker.data.extruder_targets[i] * 100;

                if (temp > chart_max) chart_max = temp;
                if (temp < chart_min) chart_min = temp;

                ui_actual_temps->y_points[i] = temp;
                ui_target_temps->y_points[i] = target;
            }

            lv_chart_set_range(ui_chart_extruder, LV_CHART_AXIS_PRIMARY_Y, chart_min+CHART_PADDING, chart_max-CHART_PADDING);
            lv_chart_set_range(ui_chart_extruder, LV_CHART_AXIS_SECONDARY_Y, chart_min+CHART_PADDING, chart_max-CHART_PADDING);
            lv_chart_refresh(ui_chart_extruder);

            // Update extruder duty
            snprintf(string_buffer, sizeof(string_buffer), "%d%%", extruder_duty);
            lv_label_set_text(ui_label_extruder_duty, string_buffer);
            lv_slider_set_value(ui_slider_extruder_duty, extruder_duty, LV_ANIM_ON);

        } else {
            lv_obj_add_flag(ui_label_extruder_temp, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_label_extruder_target, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_chart_extruder, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_label_extruder_duty, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_slider_extruder_duty, LV_OBJ_FLAG_HIDDEN);

            lv_obj_clear_flag(ui_label_printing_progress, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(ui_arc_printing_progress, LV_OBJ_FLAG_HIDDEN);

            // Match Klipperscreen's python progress algorithm
            // Credits: https://github.com/KlipperScreen/KlipperScreen/blob/7d6260d3ed41bfa4ae8c2f3d673dc715acd3f965/panels/job_status.py

            double progress, estimated, slicer_time, filament_time, file_time = 0.0;
            double print_duration = moonraker.data.print_duration;
            double total_duration = moonraker.data.total_duration;
            double speed_factor = moonraker.data.speed_factor;
            double spdcomp = sqrt(speed_factor);

            if (moonraker.data.gcode_start_byte) {
                if ((moonraker.data.file_position - moonraker.data.gcode_start_byte) > 0) {
                    progress = ((double)(moonraker.data.file_position - moonraker.data.gcode_start_byte) / 
                                (double)(moonraker.data.gcode_end_byte - moonraker.data.gcode_start_byte));
                } else {
                    progress = 0.0 / (double)(moonraker.data.gcode_end_byte - moonraker.data.gcode_start_byte);
                }
            } else {
                progress = moonraker.data.progress;
            }

            if (moonraker.data.estimated_time > 1) {
                slicer_time = (double)moonraker.data.estimated_time / spdcomp;

                if (print_duration < 1) {
                    print_duration = slicer_time * progress;
                }
            } else if (print_duration < 1) { // No extrusion
                print_duration = total_duration;
            }

            if (moonraker.data.filament_total >= moonraker.data.filament_used > 0) {
                filament_time = (print_duration / (moonraker.data.filament_used / moonraker.data.filament_total));
            }

            if (progress > 0) {
                file_time = (print_duration / progress);
            }

            if (estimated < 1) { // AUTO
                if (slicer_time > print_duration && slicer_time > 1) {
                    if (progress < 0.15) {
                        // At the begining, file and filament are innacurate
                        estimated = slicer_time;
                    } else if (filament_time > 1 && file_time > 1) {
                        // Weighted arithmetic mean (Slicer is the most accurate)
                        estimated = (slicer_time * 3 + filament_time + file_time) / 5;
                    } else if (file_time > 1) {
                        // Weighted arithmetic mean (Slicer is the most accurate)
                        estimated = (slicer_time * 2 + file_time) / 3;
                    }
                } else if (filament_time > print_duration && filament_time > 1 && file_time > 1) {
                    estimated = (filament_time + file_time) / 2;
                } else if (file_time > 1) {
                    estimated = file_time;
                }
            }

            if (estimated > 1) {
                if ((print_duration / estimated) > 0 ){
                    if ((print_duration / estimated) < 1) {
                        progress = (print_duration / estimated);
                    } else {
                        progress = 1;
                    }
                } else {
                    progress = 0;
                }
            }

            progress = progress * 100;

            lv_arc_set_value(ui_arc_printing_progress, progress);
            snprintf(string_buffer, sizeof(string_buffer), "%d%%", progress);
            lv_label_set_text(ui_label_printing_progress, string_buffer);
            
        }
    }

    if ((moonraker.data.nozzle_target != 0) && (lv_scr_act() == ui_ScreenHeatingNozzle)) {
        lv_slider_set_value(ui_slider_heating_nozzle, moonraker.data.nozzle_actual * 100 / moonraker.data.nozzle_target, LV_ANIM_ON);
    }
    if ((moonraker.data.bed_target != 0) && (lv_scr_act() == ui_ScreenHeatingBed)) {
        lv_slider_set_value(ui_slider_heating_bed, moonraker.data.bed_actual * 100 / moonraker.data.bed_target, LV_ANIM_ON);
    }

    if (lv_scr_act() == ui_ScreenTool) {
        if (knomi_config.moonraker_tool[0] == '0' && &ui_tool_img != &ui_img_T0_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T0_png);
            ui_tool_img = ui_img_T0_png;
        }
        if (knomi_config.moonraker_tool[0] == '1' && &ui_tool_img != &ui_img_T1_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T1_png);
            ui_tool_img = ui_img_T1_png;
        }
        if (knomi_config.moonraker_tool[0] == '2' && &ui_tool_img != &ui_img_T2_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T2_png);
            ui_tool_img = ui_img_T2_png;
        }
        if (knomi_config.moonraker_tool[0] == '3' && &ui_tool_img != &ui_img_T3_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T3_png);
            ui_tool_img = ui_img_T3_png;
        }
        if (knomi_config.moonraker_tool[0] == '4' && &ui_tool_img != &ui_img_T4_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T4_png);
            ui_tool_img = ui_img_T4_png;
        }
        if (knomi_config.moonraker_tool[0] == '5' && &ui_tool_img != &ui_img_T5_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T5_png);
            ui_tool_img = ui_img_T5_png;
        }
        if (knomi_config.moonraker_tool[0] == '6' && &ui_tool_img != &ui_img_T6_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T6_png);
            ui_tool_img = ui_img_T6_png;
        }
        if (knomi_config.moonraker_tool[0] == '7' && &ui_tool_img != &ui_img_T7_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T7_png);
            ui_tool_img = ui_img_T7_png;
        }
        if (knomi_config.moonraker_tool[0] == '8' && &ui_tool_img != &ui_img_T8_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T8_png);
            ui_tool_img = ui_img_T8_png;
        }
        if (knomi_config.moonraker_tool[0] == '9' && &ui_tool_img != &ui_img_T9_png) {
            lv_img_set_src(ui_img_tool_select, &ui_img_T9_png);
            ui_tool_img = ui_img_T9_png;
        }
    }

}
