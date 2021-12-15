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
    /* 16 bit X, Y */ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_DESKTOP                 ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_X                    ) ,\
    HID_USAGE        ( HID_USAGE_DESKTOP_Y                    ) ,\
    HID_LOGICAL_MIN_N  ( 0x0180,2                             ) ,\
    HID_LOGICAL_MAX_N  ( 0xFF7F,2                             ) ,\
    HID_REPORT_COUNT ( 2                                     ) ,\
    HID_REPORT_SIZE  ( 0x10                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
    /* 16 bit Button Map */ \
    HID_USAGE_PAGE   ( HID_USAGE_PAGE_BUTTON                  ) ,\
    HID_USAGE_MIN    ( 1                                      ) ,\
    HID_USAGE_MAX    ( 16                                     ) ,\
    HID_LOGICAL_MIN  ( 0                                      ) ,\
    HID_LOGICAL_MAX  ( 1                                      ) ,\
    HID_REPORT_COUNT ( 16                                     ) ,\
    HID_REPORT_SIZE  ( 1                                      ) ,\
    HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE ) ,\
  HID_COLLECTION_END \


class Joystick: public Adafruit_USBD_HID {
public:
    Joystick(uint8_t report_id, uint8_t buttons = 16);

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
    // used to set 8 buttons at once. when receive state from PISO shift register
    void setButtons(uint8_t value, uint8_t offset);

    void generateAndSendReport();

private:
    uint8_t buttons_;
    uint32_t buttonsState_ = 0;
    int16_t xAxis_ = 0;
    int16_t xAxisMaximum_ = DEFAULT_AXIS_MAXIMUM;
    int16_t xAxisMinimum_ = DEFAULT_AXIS_MINIMUM;

    int16_t yAxis_ = 0;
    int16_t yAxisMaximum_ = DEFAULT_AXIS_MAXIMUM;
    int16_t yAxisMinimum_ = DEFAULT_AXIS_MINIMUM;
    bool changed_ = false;
    uint8_t report_id_;
};

}
#endif