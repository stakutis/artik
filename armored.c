#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <artik_module.h>
#include <artik_sensor.h>
#include <artik_platform.h>
#include <artik_gpio.h>

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

artik_error getHumidityData(int *humidity) {
  artik_sensor_module *sensor;
  artik_sensor_handle handle_envhumid       = NULL;
  artik_sensor_humidity *sensor_envhumid = NULL;
  artik_sensor_config *config_envhumid;
  artik_error ret = S_OK;

  sensor = (artik_sensor_module *)artik_request_api_module("sensor");
  if (!sensor) return E_NOT_INITIALIZED;

  config_envhumid = sensor->get_humidity_sensor(0);
  while (1) {
    if ((void *)config_envhumid == 0) {
      ret=E_NOT_CONNECTED;
      break;
    }
    
    ret=sensor->request(config_envhumid,
			&handle_envhumid, (artik_sensor_ops *) &sensor_envhumid);
    if (ret != S_OK) break;
    sensor_envhumid->get_humidity(handle_envhumid, humidity);
    
    break;
  }
  
  if (sensor_envhumid)
    sensor_envhumid->release(handle_envhumid);
  artik_release_api_module(sensor);
  return ret;
}

artik_error getLightData(int *light) {
  artik_sensor_module *sensor;
  artik_sensor_handle handle_envlight       = NULL;
  artik_sensor_light *sensor_envlight = NULL;
  artik_sensor_config *config_envlight;
  artik_error ret = S_OK;

  sensor = (artik_sensor_module *)artik_request_api_module("sensor");
  if (!sensor) return E_NOT_INITIALIZED;

  config_envlight = sensor->get_light_sensor(0);
  while (1) {
    if ((void *)config_envlight == 0) {
      ret=E_NOT_CONNECTED;
      break;
    }
    
    ret=sensor->request(config_envlight,
			&handle_envlight, (artik_sensor_ops *) &sensor_envlight);
    if (ret != S_OK) break;
    sensor_envlight->get_intensity(handle_envlight, light);
    
    break;
  }
  
  if (sensor_envlight)
    sensor_envlight->release(handle_envlight);
  artik_release_api_module(sensor);
  return ret;
}

artik_error getPressureData(int *pressure) {
  artik_sensor_module *sensor;
  artik_sensor_handle handle_envpressure       = NULL;
  artik_sensor_pressure *sensor_envpressure = NULL;
  artik_sensor_config *config_envpressure;
  artik_error ret = S_OK;

  sensor = (artik_sensor_module *)artik_request_api_module("sensor");
  if (!sensor) return E_NOT_INITIALIZED;

  config_envpressure = sensor->get_pressure_sensor(0);
  while (1) {
    if ((void *)config_envpressure == 0) {
      ret=E_NOT_CONNECTED;
      break;
    }
    
    ret=sensor->request(config_envpressure,
			&handle_envpressure, (artik_sensor_ops *) &sensor_envpressure);
    if (ret != S_OK) break;
    sensor_envpressure->get_pressure(handle_envpressure, pressure);
    
    break;
  }
  
  if (sensor_envpressure)
    sensor_envpressure->release(handle_envpressure);
  artik_release_api_module(sensor);
  return ret;
}


artik_error getMagnetData(int *magnet) {
  artik_sensor_module *sensor;
  artik_sensor_handle handle_envmagnet       = NULL;
  artik_sensor_hall *sensor_envmagnet = NULL;
  artik_sensor_config *config_envmagnet;
  artik_error ret = S_OK;

  sensor = (artik_sensor_module *)artik_request_api_module("sensor");
  if (!sensor) return E_NOT_INITIALIZED;

  config_envmagnet = sensor->get_hall_sensor(0);
  while (1) {
    if ((void *)config_envmagnet == 0) {
      ret=E_NOT_CONNECTED;
      break;
    }
    
    ret=sensor->request(config_envmagnet,
			&handle_envmagnet, (artik_sensor_ops *) &sensor_envmagnet);
    if (ret != S_OK) break;
    sensor_envmagnet->get_detection(handle_envmagnet, magnet);
    
    break;
  }
  
  if (sensor_envmagnet)
    sensor_envmagnet->release(handle_envmagnet);
  artik_release_api_module(sensor);
  return ret;
}

artik_error getAccelerometerData(int *x, int *y, int *z) {
  artik_sensor_module *sensor;
  artik_sensor_handle handle_envacc       = NULL;
  artik_sensor_accelerometer *sensor_envacc = NULL;
  artik_sensor_config *config_envacc;
  artik_error ret = S_OK;

  sensor = (artik_sensor_module *)artik_request_api_module("sensor");
  if (!sensor) return E_NOT_INITIALIZED;

  config_envacc = sensor->get_accelerometer_sensor(0);
  while (1) {
    if ((void *)config_envacc == 0) {
      ret=E_NOT_CONNECTED;
      break;
    }
    
    ret=sensor->request(config_envacc,
			&handle_envacc, (artik_sensor_ops *) &sensor_envacc);
    if (ret != S_OK) break;
    sensor_envacc->get_speed_x(handle_envacc, x);
    sensor_envacc->get_speed_y(handle_envacc, y);
    sensor_envacc->get_speed_z(handle_envacc, z);
    
    break;
  }
  
  if (sensor_envacc)
    sensor_envacc->release(handle_envacc);
  artik_release_api_module(sensor);
  return ret;
}

int getGPIO(char *GPIOstring, char *valueType /* GPIO, ARTIK */,int *value) {
  artik_error ret=S_OK;
  int num=atoi(GPIOstring);
  artik_gpio_module *gpio;
  artik_gpio_config config;
  artik_gpio_handle handle=NULL;

  gpio = (artik_gpio_module *)artik_request_api_module("gpio");
  if (!gpio) return E_NOT_INITIALIZED;

  if (strcmp(valueType,"GPIO")==0)
    switch (num) {
    case 0:
      config.id = ARTIK_A710_GPIO0; 
      break;
    case 1:
      config.id = ARTIK_A710_GPIO1; 
      break;
    case 2:
      config.id = ARTIK_A710_GPIO2; 
      break;
    case 3:
      config.id = ARTIK_A710_GPIO3; 
      break;
    // WE COULD ADD MORE HERE AS NEEDED
    default:
      printf("Could not map GPIOnum %d!\n",GPIOnum);
      return E_BAD_ARGS;
    }
  else config.id = num;

  printf("Using id of %d\n",config.id);
  config.name = "button";
  config.edge = GPIO_EDGE_BOTH; 
  config.dir = GPIO_IN;
  config.initial_value = 0;
  *value = -1;
  
  while (1) {
    ret = gpio->request(&handle, &config);
    printf("ret of request:%d\n",ret);
    if (ret) break;
    *value = gpio->read(handle);
    printf("got value %d\n",*value);
    break;
  }


  if (handle != NULL) gpio->release(handle);
  if (gpio)
    artik_release_api_module(gpio);
  return ret;
}


int handleGet(char *list) {
  char *token;
  artik_error error=S_OK;

  token = strtok(list,"|");
  while (token) {
    if (strcmp(token,"temperature")==0) {
      int celsius=-1, fahrenheit=-1;
      error = getTemperatureData(&celsius, &fahrenheit);
      if (error == S_OK)
	sprintf(&outputString[strlen(outputString)]," \"celsius\":%d,\n \"fahrenheit\":%d,\n",celsius,fahrenheit);
      else
	break;
    }
    else
    if (strcmp(token,"humidity")==0) {
      int humidity;
      error = getHumidityData(&humidity);
      if (error == S_OK)
	sprintf(&outputString[strlen(outputString)]," \"humidity\":%d,\n",humidity);
      else
	break;
    }
    else
    if (strcmp(token,"light")==0) {
      int light;
      error = getLightData(&light);
      if (error == S_OK)
	sprintf(&outputString[strlen(outputString)]," \"light\":%d,\n",light);
      else
	break;
    }
    else
    if (strcmp(token,"pressure")==0) {
      int pressure;
      error = getPressureData(&pressure);
      if (error == S_OK)
	sprintf(&outputString[strlen(outputString)]," \"pressure\":%d,\n",pressure);
      else
	break;
    }
    else
    if (strcmp(token,"magnet")==0) {
      int magnet;
      error = getMagnetData(&magnet);
      if (error == S_OK)
	sprintf(&outputString[strlen(outputString)]," \"magnet\":%d,\n",magnet);
      else
	break;
    }
    else
    if (strcmp(token,"accelerometer")==0) {
      int x,y,z;
      error = getAccelerometerData(&x,&y,&z);
      if (error == S_OK)
	sprintf(&outputString[strlen(outputString)]," \"speed_x\":%d,\n \"speed_y\":%d,\n \"speed_z\":%d,\n",x,y,z);
      else
	break;
    }
    else
      if (strncmp(token,"GPIO",4)==0) {
	int value;
	char GPIOnum[100];
	strcpy(GPIOnum,&token[4]);
	error = getGPIO(GPIOnum, "GPIO", &value);
	if (error == S_OK)
	  sprintf(&outputString[strlen(outputString)]," \"%s\":%d,\n",token,value);
	else
	  break;
      }
    else
      if (strncmp(token,"ARTIK",5)==0) {
	int value;
	char GPIOnum[100];
	strcpy(GPIOnum,&token[5]);
	error = getGPIO(GPIOnum, "ARTIK", &value);
	if (error == S_OK)
	  sprintf(&outputString[strlen(outputString)]," \"%s\":%d,\n",token,value);
	else
	  break;
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
    printf("Syntax: armored [--get \"temperature|humidity|light|pressure|magnet|accelerometer|GPIOx|ARTIKx...\"] [--http listen]\n");
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


