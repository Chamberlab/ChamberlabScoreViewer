//
// Created by anton on 16/12/16.
//

#ifndef CHAMBERLABSCOREVIEWER_CSVDEFAULTS_H
#define CHAMBERLABSCOREVIEWER_CSVDEFAULTS_H

#define __APP_VERSION__ "0.1.0"
#define __APP_DEFAULT_FILENAME "score.jpg"
#define __APP_DEFAULT_BPM 120
#define __APP_DEFAULT_PPS 60.0f
#define __APP_DEFAULT_BUFFER 1920.0f / 3.0f

#define __APP_DEFAULT_SHOW_INFO true
#define __APP_DEFAULT_SHOW_METRUM true
#define __APP_DEFAULT_SHOW_MENU true

#define __OSC_IP_INPUT "127.0.0.1"
#define __OSC_PORT_INPUT 4000
#define __OSC_PORT_OUTPUT 4001

#define __OSC_ADDR_CONNECT "/connected"
#define __OSC_ADDR_CLOCK_POS "/midi/clock/position"
#define __OSC_ADDR_CLOCK_START "/midi/clock/start"
#define __OSC_ADDR_CLOCK_STOP "/midi/clock/stop"
#define __OSC_ADDR_TIME "/time"
#define __OSC_ADDR_TEMPO "/tempo"

#endif //CHAMBERLABSCOREVIEWER_CSVDEFAULTS_H
