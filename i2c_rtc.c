
#include <errno.h>                  
#include <fcntl.h>                  


#include <stdio.h>
#include <string.h>                 
#include <sys/ioctl.h>              
#include <unistd.h>                 
#include <stdint.h>
#include <linux/types.h>

#include "i2c-dev.h"

#define BUS_NUM 0
#define SLAVE_ADDR 0x68


//******************************************************************************
int main(int argc, char **argv)
{
       	int fd;
    	char path[15];
    	int rtcTime[4];
	char *rtcDay[8] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	int rtcDate[4];
    	


	snprintf(path, 11, "/dev/i2c-%d", BUS_NUM);
    	printf("%s\n", path);                                       
    	fd = open(path, O_RDWR);                                    
    	if(errno)                                                   
        	printf("%s at open()\n", strerror(errno));

	
    	ioctl(fd, I2C_SLAVE_FORCE, SLAVE_ADDR);                         
    	if(errno)                                                   
        	printf("%s at ioctl()\n", strerror(errno));

	
	rtcTime[0] = i2c_smbus_read_byte_data(fd, 0x00);         
	rtcTime[1] = i2c_smbus_read_byte_data(fd, 0x01); 
	rtcTime[2] = i2c_smbus_read_byte_data(fd, 0x02); 
	rtcTime[3] = i2c_smbus_read_byte_data(fd, 0x03); 
	rtcDate[0] = i2c_smbus_read_byte_data(fd, 0x04); 
	rtcDate[1] = i2c_smbus_read_byte_data(fd, 0x05); 
	rtcDate[2] = i2c_smbus_read_byte_data(fd, 0x06); 
	

	printf("Time is HH:MM:SS %X:%X:%X\n", rtcTime[2],rtcTime[1],rtcTime[0]);
	printf("Day is %s\n", rtcDay[rtcTime[3] - 1]);  
	printf("Date is DD/MM/YY %X:%X:%X\n", rtcDate[0],rtcDate[1],rtcDate[2]);
	
	usleep(10000);

	if((rtcTime == 0) || (rtcDate == 0))                                
        	printf("Problem at read_byte_data, returned 0\n");
   	else                                                       
        	printf("success\n");
	

    return 0;
}
