/*--------------------------------------------------------------------------------------------------------------------
| Active_Wifi.h: 
|
| Created by:     Cameron Jupp
| Date Started:   December 3, 2022
--------------------------------------------------------------------------------------------------------------------*/

#ifndef ACTIVE_WIFI_H
#define ACTIVE_WIFI_H

// -------------------------------------------------------------------------------------------------------------------- //
// --------------------------- /    \   / ___/  / ___/  /_  _/  / \  / /  / ___/  / ____/ ----------------------------- //
// -------------------------- / /_\ /  / __/   / __/     / /   / /\\/ /  / __/    \__ \  ------------------------------ //
// ------------------------- /_____/  /____/  /_/      /___/  /_/  \_/  /____/  /_____/ ------------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

#define WIFI_TIMEOUT_MS 10000
#define NETLIST_SZ      4

#define CHAR_LIM        32
#define CONFIGURED      'c'
#define UNCONFIGURED    'u'

// -------------------------------------------------------------------------------------------------------------------- //
// ----------------------------- / ___/  / /     / _\      / ____/  / ____/  / ___/  / ____/ -------------------------- //
// ---------------------------- / /__   / /__   / /_\\     \__ \    \__ \   / __/    \__ \  --------------------------- //
// --------------------------- /____/  /____/  /_/   \\  /_____/  /_____/  /____/  /_____/ ---------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

class WAP
{
// -------------------------------------------------------------------------------------------------------------------- //
// ----------------------------------------------------- PUBLIC ------------------------------------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

  public:
  
  char status = UNCONFIGURED;
  char ssid[CHAR_LIM];
  char password[CHAR_LIM];

  void copy_str(char * in_str, char * out_str);

  void save(char * addr_ptr, int data_sz);

  void load(char * addr_ptr, int data_sz);

  int config();

  void SetSSID(char * new_ssid);

  void SetPassword(char * new_password);

  int connect();
};

// -------------------------------------------------------------------------------------------------------------------- //
// -------------------------- / ___/  / /     / __  /  / _ /    / _\      / /     / ____/ ----------------------------- //
// ------------------------- / /_//  / /__   / /_/ /  / _  \   / /_\\    / /__    \__ \  ------------------------------ //
// ------------------------ /____/  /____/  /_____/  /_____/  /_/   \\  /____/  /_____/ ------------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

extern WAP network_list[NETLIST_SZ];

// -------------------------------------------------------------------------------------------------------------------- //
// -------------------  / ___/  / / //  / \  / /  / ___/ /__  __/  /_  _/  / __  /  / \  / /  / ____/ ----------------- //
// ------------------  / __/   / /_//  / /\\/ /  / /__     / /      / /   / /_/ /  / /\\/ /   \__ \ ------------------- //
// -----------------  /_/     /____/  /_/  \_/  /____/    /_/     /___/  /_____/  /_/  \_/  /_____/ ------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

void init_wifi_system();

int start_check();

void scan_waps();

void init_wifi(WAP * init_wap);

#endif