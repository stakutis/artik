#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <artik_module.h>
#include <artik_sensor.h>
#include <artik_platform.h>
#include <artik_gpio.h>

#include <netdb.h>
#include <netinet/in.h>


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
      printf("Could not map GPIOnum %d!\n",num);
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

  sprintf(outputString,"{\n");
  token = strtok(list,"|");
  while (token && error == S_OK) {
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
	char ARTIKnum[100];
	strcpy(ARTIKnum,&token[5]);
	error = getGPIO(ARTIKnum, "ARTIK", &value);
	if (error == S_OK)
	  sprintf(&outputString[strlen(outputString)]," \"%s\":%d,\n",token,value);
	else
	  break;
      }
    else {
      printf("Unknown token:%s\n",token);
      error = -1;
      break;
    }
    token = strtok(NULL,"|");
  }
  sprintf(&outputString[strlen(outputString)]," \"resultCode\":%d,\n \"resultString\":\"%s\"\n}",error,error_msg(error));
  return error;
}


int handleHTTP(char *str) {
  int sockfd, newsockfd, portno=80, clilen;
  char buffer[1000],body[1000], tempstr[100];
  struct sockaddr_in serv_addr, cli_addr;
  int n,count=0;

  printf("in handleHTTP\n");
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("sockfd:%d\n",sockfd);
  if (sockfd<0) {
    perror("ERROR opening socket");
    exit(1);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  printf("Bind now...\n");
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))<0) {
    perror("ERROR on binding");
    exit(1);
  }
  printf("Listen now...\n");
  listen(sockfd,1);
  clilen = sizeof(cli_addr);
  while (1) {
	    printf("accepting...\n");
	    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	    if (newsockfd<0) {
	      perror("Error on accept");
	      exit(1);
	    }
	    printf("newsockfd:%d\n",newsockfd);

	    bzero(buffer,sizeof(buffer));
	    n = read(newsockfd,buffer,sizeof(buffer)-1);
	    if (n<0) {
	      perror("ERROR reading fro socket");
	      exit(1);
	    }
	    printf("Here is the message (length:%d):\n%s\n",strlen(buffer),buffer);
	    if (strlen(buffer)==0) continue;
	    char *baseGet="GET /Artikd?command=read%20";
 	    if (strncmp(buffer,baseGet,strlen(baseGet))==0) {
	      char *p=&buffer[strlen(baseGet)];
	      char *space;
	      space=strchr(p,' ');
	      if (space) *space=0;
	      int ret;
	      ret = handleGet(p);
	      printf("ret got:%d str:%s\n",ret,outputString);
	      strcpy(body, outputString);
	    }
	    else {
	      printf("Didnt compare to %s\n",baseGet);
	      sprintf(body,"{\"resultCode\":-1,\"resultString\":\"Unknown HTTP request\"}");
	    }
	    
	    count++;

	    sprintf(buffer,"HTTP/1.1 200 OK\r\n");
	    strcat(buffer,"Date: Mon,  27 Jul 2018 12:28:50 GMT\r\n");
	    sprintf(tempstr,"Content-length: %d\r\n",strlen(body));
	    strcat(buffer,tempstr);
	    //	    strcat(buffer,"Content-Type: text/html\r\n");
	    strcat(buffer,"Content-Type: application/json\r\n");
	    strcat(buffer,"Connection: Closed\r\n");
	    strcat(buffer,"\r\n");
	    strcat(buffer,body);
	    printf("sending:\n%s\n",buffer);
	    n=write(newsockfd,buffer,strlen(buffer));
	    printf("n=%d\n",n);
  }
}


int processCommands(int argc, char *argv[]) {
  int ret = S_OK;
  int i;
  

  i=1;
  while (i<argc){
    if (strcmp(argv[i],"--read")==0) {
      i++;
      ret = handleGet(argv[i]);
      if (ret) break;
    }
    else
    if (strcmp(argv[i],"--http")==0) {
      i++;
      ret = handleHTTP(argv[i]);
      if (ret) break;
    }
    else {
      printf("Unknown command option: %s\n",argv[i]);
      exit(-1);
      /*
      ret = E_BAD_ARGS;
      break;
      */
    }
    i++;
  }

  return S_OK;
}

int main(int argc, char *argv[])
{int ret;

  if (argc<=1 || strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0) {
    printf("Syntax: %s [-h] [--help] [--read \"temperature|humidity|light|pressure|magnet|accelerometer|GPIOx|ARTIKx...\"] [--http listen]\n",argv[0]);
    printf("Via HTTP:  IP/Artikd?command=read and the above stuff starting with --read\n");
    printf("    Example:  http://10.0.0.227/AmoredArtikd?commmand=read temperature|humidity|ARTIK30\n");
    printf("   When specifying GPIOx the 'x' is the silk screen  GPIO value.\n");
    printf("   When specifying ARTIK the 'x' is the true Artik sysfs value;  30 is the front most button on the imposer board for example.\n");
    return -1;
  }

  ret=processCommands(argc, argv);

  printf("outputString: \n%s\n",outputString);
  
  return ret;  
}


