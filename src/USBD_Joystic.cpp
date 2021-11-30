#include "USBD_Joystic.h"

struct USB_Joystick_report {
    int16_t x;
    int16_t y;
};

// hidReport_{TUD_HID_REPORT_DESC_JOYSTICK(HID_REPORT_ID(3))}
Joystick::Joystick(uint8_t report_id):report_id_(report_id) {
    //setPollInterval(2);
    //begin();
}


void Joystick::setXAxis(int16_t value, bool send_report) {
    if (xAxis_ != value) {
        xAxis_ = value;
        changed_ = true;
    }
    if (send_report) {
        generateAndSendReport();
    }
}

void Joystick::generateAndSendReport() {
    if (!changed_) {
        return;
    }
    changed_ = false;
    USB_Joystick_report report = {
        .x = xAxis_,
        .y = yAxis_,
    };
    sendReport(report_id_, &report, sizeof(report));
}

void Joystick::setYAxis(int16_t value, bool send_report) {
    if (yAxis_ != value) {
        yAxis_ = value;
        changed_ = true;
    }
    if (send_report) {
        generateAndSendReport();
    }
}