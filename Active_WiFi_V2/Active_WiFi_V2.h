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

	char get_status()
	{
		return status;
	}


	char* get_ssid()
	{
		return this->ssid;
	}


	char* get_password()
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

  
  void save(char * addr_ptr, int data_sz)
  { 
    for(int i = 0; i < data_sz; i++)
    {
      EEPROM.write(i, addr_ptr[i]);
      EEPROM.commit(); 
    }
  }
  
  
  void load(char * addr_ptr, int data_sz)
  {
    for(int i = 0; i < data_sz; i++)
    {
      addr_ptr[i] = EEPROM.read(i);
    }
  }


  int config()
  {
      //Select the element of the array you want to overwrite
  //Serial.print("Please enter the ");
  
  //Request the access point information
  Serial.println("Enter the SSID: ");
  this->set_ssid(serial_gets());

  Serial.println("Enter the password: ");
  this->set_password(serial_gets());

  //Check to see if the network connects
  return this->connect();

  }
  
  
  void set_ssid(char * new_ssid)
  {
    copy_str(new_ssid, this->ssid);
  }


  void set_password(char * new_password)
  {
    copy_str(new_password, this->password);
  }


  int connect()
  {
    //Disconnect before attempting to connect
    WiFi.disconnect();

    //Display information to console
    Serial.print("Connecting to network:");

    //Switch to station mode and connect to the 
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid, this->password);

    unsigned long startAttemptTime = millis();

    while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS)
    {
      Serial.print(".");
      delay(100);
    }

    Serial.println();
    char * wap_ptr = (char*)this;
    
    if (WiFi.status() == WL_CONNECTED)
    {
      //Display message and save configuration as configured
      Serial.println("Wifi connected!");
      this->status = CONFIGURED;
      this->save(wap_ptr, sizeof(*this));

      //Print out the IP address
      //Serial.println("IP Address: ");
      //Serial.println(Wifi.localIP());
      return 0;
    }
    else
    {
      //Display message and save configuration as unconfigured
      Serial.println("Could not connect to WiFi network");
      this->status = UNCONFIGURED;
      this->save(wap_ptr, sizeof(*this));
      return -1;
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
		network_list[0].load(wap_ptr, sizeof(network_list[0]));

		//Serial.println(network_list[0].status);

		if(network_list[0].get_status() == CONFIGURED)
		{
			Serial.println("Network found!");
			network_list[0].connect();
			return 0;
		}
		else
		{
			Serial.println("No configuration found. Starting setup...");
			init_wifi(&network_list[0]);
			return -1;
		}
	}

	void get_available_ssids()
	{
		//Scan wifi access points

		//Write them to a variable/array

		//display them to the serial monitor

		//return array of names
	
	}

};




#endif