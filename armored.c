#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <artik_module.h>
#include <artik_sensor.h>


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

int main(int argc, char *argv[])
{
  int celsius=-1, fahrenheit=-1;
  artik_error error;
  char *token;

  printf("hi\n");
  token = strtok(argv[1],"|");
  while (token) {
    printf("Token:%s\n",token);
    if (strcmp(token,"temperature")==0) {
      error = getTemperatureData(&celsius, &fahrenheit);
      printf("Error: %d ErrStr:%s c:%d f:%d\n",error, error_msg(error), celsius, fahrenheit);
    }
    else {
      printf("Unknown token:%s\n",token);
      return -1;
    }
    token = strtok(NULL,"|");
  }

  return 0;  
}


