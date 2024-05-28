#ifndef MOONRAKER_H
#define MOONRAKER_H

#include <WString.h>

#define CHART_SECONDS 120
#define CHART_PADDING 2 * 100 // ℃ * 100
typedef struct {
    int16_t bed_actual;
    int16_t bed_target;
    int16_t nozzle_actual;
    int16_t nozzle_target;
    double progress;
    uint32_t file_position;
    String filename;
    double filament_used;
    double total_duration;
    double print_duration;
    float speed_factor;
    uint32_t gcode_start_byte;
    uint32_t gcode_end_byte;
    uint32_t estimated_time;
    double filament_total;
    float extruder_temp;
    float extruder_target;
    float extruder_temps[CHART_SECONDS];
    float extruder_targets[CHART_SECONDS];
    uint8_t extruder_duty;
    bool pause;
    bool printing;    // is klipper in a printing task (including printing, pausing, paused, cancelling)
    bool homing;
    bool probing;
    bool qgling;
    bool heating_nozzle;
    bool heating_bed;
    int8_t dropoff;
    int8_t pickup;
} moonraker_data_t;

#define QUEUE_LEN 5
typedef struct {
    String queue[QUEUE_LEN];
    uint8_t index_r;  // Ring buffer read position
    uint8_t index_w;  // Ring buffer write position
    uint8_t count;    // Count of commands in the queue
} post_queue_t;

class MOONRAKER {
    public:
        bool unconnected;   // is KNOMI connected to moonraker
        bool unready; // is moonraker connected to klipper
        bool data_unlock; //
        moonraker_data_t data;
        void http_get_loop(void);
        void http_post_loop(void);
        bool post_to_queue(String path);
        bool post_gcode_to_queue(String gcode);
        String send_request(const char * type, String path);

    private:
        post_queue_t post_queue;
        void get_printer_ready(void);
        void get_printer_info(void);
        void get_progress(void);
        void get_extruder(void);
        void get_status(void);
};

extern MOONRAKER moonraker;

#endif
