/*--------------------------------------------------------------------------------------------------------------------
| Active_Wifi.h: 
|
| Created by:     Cameron Jupp
| Date Started:   December 3, 2022
--------------------------------------------------------------------------------------------------------------------*/
#include <Arduino.h>
#include <WiFi.h>
#include <stdio.h>

#ifndef ACTIVE_WIFI_V2_H
#define ACTIVE_WIFI_V2_H

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


  void copy_str(char * source, int sourceLen, char * destination, int destinationLen)
  {
	Serial.println("Copying string");

    int i = 0;
	int charLimit = 0;

	//Choose character limit
	if(sourceLen < destinationLen)
	{
		charLimit = sourceLen;
	}
	else if(destinationLen < sourceLen)
	{
		charLimit = sourceLen;
	}

	Serial.print("Character limit: ");
	Serial.println(charLimit, DEC);


	while(i < charLimit && source[i] != '\0')
	{
		destination[i] = source[i];
		i++;		
	}

	Serial.println("Destination: ");
	Serial.println(destination);

  }

  
  
	void SetSSID(char * new_ssid, int strLen)
	{
		Serial.println("Setting SSID");
		copy_str(new_ssid, strLen, this->ssid, SSID_CHAR_LIM);
	}


	void SetPassword(char * pNewPassword, int strLen)
	{
		Serial.println("Setting password");
		copy_str(pNewPassword, strLen, this->password, PASSWORD_CHAR_LIM);
	}

  IPAddress GetIPAddress()
  {
	return WiFi.localIP();
  }

  bool IsWiFiConnected()
  {
	return WiFi.status() == WL_CONNECTED;
  }

  bool ConnectionTimedOut(unsigned long startTime)
  {
	return ((millis() - startTime) > WIFI_TIMEOUT_MS);
  }	

	bool Disconnect()
	{
		WiFi.disconnect();
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
      //Display message 
      Serial.println("Wifi connected!");
      this->status = CONFIGURED;

      return true;
    }

    else
    {
      //Display message 
      Serial.println("Could not Connect to WiFi network");
      this->status = UNCONFIGURED;
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
	void SetWapSsid()
	{

	}


	void SetWapPassword(char* password)
	{

	}


	void AddNewWap()
	{

	}


	int TryAllSavedWAPS()
	{

	}




	void Init()
	{

		StartCheck();

	}

	int StartCheck()
	{ 
		//Display message to serial terminal
		Serial.println("Checking for configured wifi configuration...");

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
			//init_wifi(&network_list[0]);
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

void GetSSIDList()
{


}

#endif