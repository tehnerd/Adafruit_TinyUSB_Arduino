#include "USBD_Joystick.h"

struct USB_Joystick_report {
    int16_t x;
    int16_t y;
    // hardcode lol
    uint8_t buttons[16];
};

// hidReport_{TUD_HID_REPORT_DESC_JOYSTICK(HID_REPORT_ID(3))}
Joystick::Joystick(uint8_t report_id, uint8_t buttons):report_id_(report_id), buttons_(buttons) {
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
    uint8_t report_size = 4 + buttons_/8;
    uint8_t report[report_size];
    report[0] = (uint8_t)(xAxis_ & 0xFF);
    report[1] = (uint8_t)(xAxis_ >> 8);
    report[2] = (uint8_t)(yAxis_ & 0xFF);
    report[3] = (uint8_t)(yAxis_ >> 8);
    for (int i = 0; i < buttons_/8; i++) {
        report[4+i] = (uint8_t)((buttonsState_ >> (8 * i)) & 0xFF);
    }
    sendReport(report_id_, report, report_size);
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

void Joystick::setButtons(uint8_t value, uint8_t offset) {
    uint32_t old_state = buttonsState_;
    if (offset > 3) {
        return;
    }
    value = ~value;
    uint32_t mask = 0xFFFFFFFF ^ (0xFF << (8 * offset));
    buttonsState_ &= mask;
    buttonsState_ |= (value << (8 * offset));
    if (buttonsState_ != old_state) {
        changed_ = true;
    }
}