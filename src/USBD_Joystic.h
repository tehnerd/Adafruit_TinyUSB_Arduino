#ifndef USBD_JOYSTICK_H
#define USBD_JOYSTICK_H
#include "Adafruit_USBD_HID.h"

#define DEFAULT_AXIS_MINIMUM 0
#define DEFAULT_AXIS_MAXIMUM 1023
extern "C" {

#define TUD_HID_REPORT_DESC_JOYSTICK(...) \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP     )                 ,\
  HID_USAGE      ( HID_USAGE_DESKTOP_JOYSTICK )                 ,\
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                 ,\
    /* Report ID if any */\
    __VA_ARGS__ \
    /* 8 bit X, Y, Z, Rz, Rx, Ry (min -127, max 127 ) */ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_X                    ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_Y                    ) ,\
    HID_LOGICAL_MIN_N  ( 0x0180,2                             ) ,\
    HID_LOGICAL_MAX_N  ( 0xFF7F,2                             ) ,\
    HID_REPORT_COUNT ( 2                                     ) ,\
    HID_REPORT_SIZE  ( 0x10                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
  HID_COLLECTION_END \


class Joystick: public Adafruit_USBD_HID {
public:
    explicit Joystick(uint8_t report_id);

    void setXAxisRange(int16_t minimum, int16_t maximum) {
        xAxisMinimum_ = minimum;
        xAxisMaximum_ = maximum;
    }


    void setYAxisRange(int16_t minimum, int16_t maximum) {
        yAxisMinimum_ = minimum;
        yAxisMaximum_ = maximum;
    }

    void setXAxis(int16_t value, bool send_report = false);

    void setYAxis(int16_t value, bool send_report = false);

    void generateAndSendReport();

private:
    int16_t xAxis_;
    int16_t xAxisMaximum_ = DEFAULT_AXIS_MAXIMUM;
    int16_t xAxisMinimum_ = DEFAULT_AXIS_MINIMUM;

    int16_t yAxis_;
    int16_t yAxisMaximum_ = DEFAULT_AXIS_MAXIMUM;
    int16_t yAxisMinimum_ = DEFAULT_AXIS_MINIMUM;
    bool changed_ = false;
    uint8_t report_id_;
};

}
#endif