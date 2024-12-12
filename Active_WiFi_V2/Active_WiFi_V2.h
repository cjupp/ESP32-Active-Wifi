/*--------------------------------------------------------------------------------------------------------------------
| Active_Wifi.h: 
|
| Created by:     Cameron Jupp
| Date Started:   December 3, 2022
--------------------------------------------------------------------------------------------------------------------*/
#include <Arduino.h>
#include <WiFi.h>
#include <stdio.h>
#include <EEPROM.h>
#include "Serial_Tools.h"

#ifndef ACTIVE_WIFI_H
#define ACTIVE_WIFI_H

// -------------------------------------------------------------------------------------------------------------------- //
// --------------------------- /    \   / ___/  / ___/  /_  _/  / \  / /  / ___/  / ____/ ----------------------------- //
// -------------------------- / /_\ /  / __/   / __/     / /   / /\\/ /  / __/    \__ \  ------------------------------ //
// ------------------------- /_____/  /____/  /_/      /___/  /_/  \_/  /____/  /_____/ ------------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

#define WIFI_TIMEOUT_MS		10000
#define NETLIST_SZ			4

#define SSID_CHAR_LIM		32
#define PASSWORD_CHAR_LIM	64

#define CONFIGURED			1
#define UNCONFIGURED		-1

// -------------------------------------------------------------------------------------------------------------------- //
// ----------------------------- / ___/  / /     / _\      / ____/  / ____/  / ___/  / ____/ -------------------------- //
// ---------------------------- / /__   / /__   / /_\\     \__ \    \__ \   / __/    \__ \  --------------------------- //
// --------------------------- /____/  /____/  /_/   \\  /_____/  /_____/  /____/  /_____/ ---------------------------- //
// -------------------------------------------------------------------------------------------------------------------- //

class WAP
{
	private:

	char status = UNCONFIGURED;
	char ssid[SSID_CHAR_LIM];
	char password[PASSWORD_CHAR_LIM];

	public:

	char GetStatus()
	{
		return status;
	}


	char* GetSSID()
	{
		return this->ssid;
	}


	char* GetPassword()
	{
		return this->password;
	}


  void copy_str(char * in_str, char * out_str)
  {
    int i = 0;

    do
    {
      out_str[i] = in_str[i];
    }while(in_str[i++] != '\0' && i < CHAR_LIM);
  }

  
  void SaveInEEPROM(char * addr_ptr, int data_sz)
  { 
    for(int i = 0; i < data_sz; i++)
    {
      EEPROM.write(i, addr_ptr[i]);
      EEPROM.commit(); 
    }
  }
  
  
  void LoadFromEEPROM(char * addr_ptr, int data_sz)
  {
    for(int i = 0; i < data_sz; i++)
    {
      addr_ptr[i] = EEPROM.read(i);
    }
  }
 
  
  void SetSSID(char * new_ssid)
  {
    copy_str(new_ssid, this->ssid);
  }


  void SetPassword(char * new_password)
  {
    copy_str(new_password, this->password);
  }

  char* GetIPAddress()
  {
	return Wifi.localIP();
  }

  bool WiFiConnected()
  {
	return WiFi.status() == WL_CONNECTED;
  }

  bool ConnectionTimedOut(unsigned long startTime)
  {
	return ((millis() - startTime) > WIFI_TIMEOUT_MS);
  }	

	bool Disconnect()
	{
		Wifi.disconnect();
	}

	void WaitForConnection()
	{
		unsigned long startAttemptTime = millis();

		while(!IsWiFiConnected() && !ConnectionTimedOut(startAttemptTime))
		{
			Serial.print(".");
			delay(100);
		}
	}

  bool Connect()
  {
    //Disconnect before attempting to Connect
    WiFi.disconnect();

    //Display information to console
    Serial.print("Connecting to network:");

    //Switch to station mode and Connect to the 
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid, this->password);

	WaitForConnection();


    if (WiFi.status() == WL_CONNECTED)
    {
      //Display message and SaveInEEPROM configuration as configured
      Serial.println("Wifi connected!");
      this->status = CONFIGURED;
      this->SaveInEEPROM(this, sizeof(*this));

      return true;
    }

    else
    {
      //Display message and SaveInEEPROM configuration as unconfigured
      Serial.println("Could not Connect to WiFi network");
      this->status = UNCONFIGURED;
      this->SaveInEEPROM(this, sizeof(*this));
      return false;
    }
  }
};


class Network_Manager
{
	private:

	WAP network_list[NETLIST_SZ];


	int currentWAP = 0;

	bool wapConnected = false;
	


	public:
	void Set_WAP_SSID()
	{

	}


	void Set_WAP_Password(char* password)
	{

	}


	void Add_New_WAP()
	{

	}


	int Try_All_Saved_WAPS()
	{

	}




	void init_wifi_system()
	{
		//Initialize the EEPROM memory
		EEPROM.begin(512);

		start_check();

	}

	int start_check()
	{ 
		//Display message to serial terminal
		Serial.println("Checking for previous wifi configuration...");
		
		//Create a pointer for the first access point and treat it as an array of bytes 
		char* wap_ptr = (char*)&network_list[0];
		network_list[0].LoadFromEEPROM(wap_ptr, sizeof(network_list[0]));

		//Serial.println(network_list[0].status);

		if(network_list[0].GetStatus() == CONFIGURED)
		{
			Serial.println("Network found!");
			network_list[0].Connect();
			return 0;
		}
		else
		{
			Serial.println("No configuration found. Starting setup...");
			init_wifi(&network_list[0]);
			return -1;
		}
	}

};


int RefreshAvailableSSIDs()
{
	//Get list of available connections
	int numSSID = 0;
	char SSID[32];

	WiFi.mode(WIFI_STA);
	WiFi.disconnect();

	numSSID = WiFi.scanNetworks();

	return numSSID;
}

char* GetSSIDList()
{
	int numSSID = RefreshAvailableSSIDs();

	//Make sure to delete and free up the memory after use
	char* ssidList = new char[SSID_CHAR_LIM][numSSID];

	return ssidList;

}




#endif