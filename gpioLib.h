
#include <stdbool.h>

#define GPIO_EXPORT	"/sys/class/gpio/export"
#define GPIO_UNEXPORT	"/sys/class/gpio/unexport"
#define GPIO_DIR	"/sys/class/gpio/gpio%d/direction"
#define GPIO_VAL	"/sys/class/gpio/gpio%d/value"
#define GPIO_IRQ	"/sys/class/gpio/gpio%d/egde"

#define TRUE	1
#define FALSE	0
#define HIGH	1
#define LOW	0
#define IN	0
#define OUT	1

enum{
	NORMAL,
	IO_POLLED,
	EVENT_DRIVEN,
	THREAED,
};
enum{
	NONE,
	RISING,
	FALLING,
	BOTH,
};

/* gpioLib.c */
void gpioExport(int gpio);
void gpioUnexport(int gpio);
void gpioSetLevel(int gpio, bool level);
void gpioSetDir(int gpio, bool dir);
void gpioGet(int mode, int gpio, int *retVal);
void gpioEdge(int gpio, int type);
//void gpioGetIoPolled(int gpio, int *retVal);
//void gpioGetEventDriven(int gpio, int *retVal);
//void gpioGetThreaded(int gpio, int *retVal);

