#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CHAN_CONFIG_SINGLE   8
#define CHAN_CONFIG_DIFF     0

static int myFd;

void loadSpiDriver()
{
    printf("before gpio load spi...\n");
    if (system("/usr/local/bin/gpio load spi") == -1)
    {
        fprintf(stderr, "can't load the SPI driver: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("after gpio load spi...\n");
}

void spiSetup(int spiChannel)
{
    if ((myFd = wiringPiSPISetup(spiChannel, 1000000)) < 0)
    {
        fprintf(stderr, "can't open the SPI bus: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

/*
 myAnalogRead(): it return 0:0v ~ 1023:3.3v
*/
int myAnalogRead(int spiChannel, int channelConfig, int analogChannel)
{
    if (analogChannel < 0 || analogChannel > 7)
        return -1;
    unsigned char buffer[3] = {1}; //start bit
    buffer[1] = (channelConfig+analogChannel) << 4;
    wiringPiSPIDataRW(spiChannel, buffer, 3);
    return((buffer[1] & 3) << 8) + buffer[2]; //get last 10 bits
}

/*
int main()
{
    int analogChannel = 0;
    int spiChannel = 0;
    int channelConfig = CHAN_CONFIG_SINGLE;

    loadSpiDriver();
    wiringPiSetup();
    spiSetup(spiChannel);

    printf("MCP3008 got: %d\n", myAnalogRead(spiChannel, channelConfig, analogChannel));

    close(myFd);
    return 0;
}
 
*/



 


