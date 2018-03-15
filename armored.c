#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <artik_module.h>
#include <artik_sensor.h>


static char outputString[1024]="";

static void signal_handler(int signum)
{
  printf("signal called with signum:%d!\n",signum);
  exit(-1);
}

artik_error getTemperatureData(int *celsius, int *fahrenheit) {
  artik_sensor_module *sensor;
  artik_sensor_handle handle_envtemp       = NULL;
  artik_sensor_temperature *sensor_envtemp = NULL;
  artik_sensor_config *config_envtemp;
  artik_error ret = S_OK;

  sensor = (artik_sensor_module *)artik_request_api_module("sensor");
  if (!sensor) return E_NOT_INITIALIZED;

  config_envtemp = sensor->get_temperature_sensor(0);
  while (1) {
    if ((void *)config_envtemp == 0) {
      ret=E_NOT_CONNECTED;
      break;
    }
    
    ret = sensor->request(config_envtemp,
			    &handle_envtemp, (artik_sensor_ops *)
			    &sensor_envtemp);
    if (ret != S_OK) break;

    sensor_envtemp->get_celsius(handle_envtemp, celsius);
    sensor_envtemp->get_fahrenheit(handle_envtemp, fahrenheit);
    
    break;
  }
  
  if (sensor_envtemp)
    sensor_envtemp->release(handle_envtemp);
  artik_release_api_module(sensor);
  return ret;
}

int handleGet(char *list) {
  char *token;
  artik_error error=S_OK;
  int celsius=-1, fahrenheit=-1;

  token = strtok(list,"|");
  while (token) {
    printf("Token:%s\n",token);
    if (strcmp(token,"temperature")==0) {
      error = getTemperatureData(&celsius, &fahrenheit);
      if (error == S_OK)
	sprintf(&outputString[strlen(outputString)]," \"celsius\":%d,\n \"fahrenheit\":%d,\n",celsius,fahrenheit);
    }
    else {
      printf("Unknown token:%s\n",token);
      return -1;
    }
    token = strtok(NULL,"|");
  }
  return error;
}


int main(int argc, char *argv[])
{
  int ret=0;
  int i;

  if (argc<=1) {
    printf("Syntax: armored [--get \"temperature|humidity|GPIOx...\"] [--http listen]\n");
    return -1;
  }

  sprintf(outputString,"{\n");

  i=1;
  while (i<argc){
    if (strcmp(argv[i],"--get")==0) {
      i++;
      ret = handleGet(argv[i]);
      if (ret) break;
    }
    i++;
  }

  sprintf(&outputString[strlen(outputString)]," \"resultCode\":%d,\n \"resultString\":\"%s\"\n}",ret,error_msg(ret));
  printf("outputString: \n%s\n",outputString);
  
  return ret;  
}


