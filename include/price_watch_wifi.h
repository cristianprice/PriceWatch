#pragma once
#include <Arduino.h>
#include <WiFi.h>

extern volatile bool wifiApConnected;
extern volatile bool wifiStaConnected;

struct WifiConfig
{
  // STA credentials
  const char *sta_ssid;
  const char *sta_password;

  // AP credentials
  const char *ap_ssid;
  const char *ap_password;

  // Mode flags
  bool start_sta;
  bool start_ap;

  WifiConfig(const char *s_ssid = "", const char *s_password = "",
             const char *a_ssid = "PriceWatch", const char *a_password = "PriceWatch123",
             bool sta = false, bool ap = true)
      : sta_ssid(s_ssid), sta_password(s_password),
        ap_ssid(a_ssid), ap_password(a_password),
        start_sta(sta), start_ap(ap) {}
};

extern WifiConfig currentWifiConfig;

void start_wifi(const WifiConfig *config);