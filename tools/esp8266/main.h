#ifndef __MAIN_H__
#define __MAIN_H__

#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>

#include <ESP8266HTTPUpdateServer.h>

// NTP
#include <WiFiUdp.h>
#include <TimeLib.h>

#include "eep.h"
#include "defines.h"


const byte mDnsPort = 53;

/* TIMESERVER CONFIG */
#define TIMESERVER_NAME     "pool.ntp.org"
#define TIME_LOCAL_PORT     8888
#define NTP_PACKET_SIZE     48
#define TIMEZONE            1 // Central European time +1

class Main {
    public:
        Main(void);
        virtual void setup(const char *ssid, const char *pwd, uint32_t timeout);
        virtual void loop();
        String getDateTimeStr (time_t t);


    protected:
        void showReboot(void);
        virtual void saveValues(bool webSend);

        char mStationSsid[SSID_LEN];
        char mStationPwd[PWD_LEN];
        bool mLinkLedActive;
        bool mApActive;
        ESP8266WebServer *mWeb;
        char mVersion[9];
        char mDeviceName[DEVNAME_LEN];
        eep *mEep;
        uint32_t mTimestamp;


    private:
        bool getConfig(void);
        void setupAp(const char *ssid, const char *pwd);
        bool setupStation(uint32_t timeout);

        void showNotFound(void);
        virtual void showSetup(void);
        virtual void showSave(void);
        void showUptime(void);
        void showTime(void);
        void showCss(void);
        void uptimeTicker(void);


        time_t getNtpTime(void);
        void sendNTPpacket(IPAddress& address);
        time_t offsetDayLightSaving (uint32_t local_t);

        Ticker *mUptimeTicker;
        uint32_t mUptimeSecs;

        DNSServer *mDns;
        ESP8266HTTPUpdateServer *mUpdater;

        WiFiUDP *mUdp; // for time server
};

#endif /*__MAIN_H__*/