#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#include "uart.h"

/******************************************************************************
function:   Serial port initialization
parameter:
    UART_device : Device name
Info:
    /dev/ttyTHS*
    The default baud rate is 9600, 8-bit data, 1 stop bit, no parity
******************************************************************************/
int uvm_uart_begin(HARDWARE_UART *dev, char *UART_device)
{
    //device
    if((dev->fd = open(UART_device, O_RDWR | O_NOCTTY)) < 0)  { //打开UART 
        perror("Failed to open UART device.\n");  
        return -1; 
    }
    uvm_uart_setBaudrate(dev, 115200);
    uvm_uart_Set(dev, 8, 1, 'N');
    return 0;
}

/******************************************************************************
function:   Serial device End
parameter:
Info:
******************************************************************************/
int uvm_uart_end(HARDWARE_UART dev)
{
    if (close(dev.fd) != 0){
        perror("Failed to close UART device.\n");
        return -1;
    }
    return 0;
}

/******************************************************************************
function:   Set the serial port baud rate
parameter:
    Baudrate : Serial port baud rate
               B50          50
               B75          75
               B110         110
               B134         134
               B150         150
               B200         200
               B300         300
               B600         600
               B1200        1200
               B1800        1800
               B2400        2400
               B4800        4800
               B9600        9600
               B19200       19200
               B38400       38400
               B57600       57600
               B115200      115200
               B230400      230400
Info:
******************************************************************************/
int uvm_uart_setBaudrate(HARDWARE_UART *dev, uint32_t Baudrate)
{
    uint16_t err;
    uint32_t baud;
    tcflush(dev->fd, TCIOFLUSH);//清空数据缓冲区
    
    switch(Baudrate)        //Set the number of data bits
    {
        case B230400:
        case 230400:    baud = B230400; break;
        case B115200:   
        case 115200:    baud = B115200; break;
        case B57600:   
        case 57600:     baud = B57600; break;
        case B38400:   
        case 38400:     baud = B38400; break;
        case B19200:   
        case 19200:     baud = B19200; break;
        case B9600:   
        case 9600:  baud = B9600; break;
        case B4800:   
        case 4800:  baud = B4800; break;
        case B2400:   
        case 2400:  baud = B2400; break;
        case B1800:   
        case 1800:  baud = B1800; break;
        case B1200:   
        case 1200:  baud = B1200; break;
        case B600:   
        case 600:   baud = B600; break;
        case B300:   
        case 300:   baud = B300; break;
        case B200:   
        case 200:   baud = B200; break;
        case B150:   
        case 150:   baud = B150; break;
        case B134:   
        case 134:   baud = B134; break;
        case B110:   
        case 110:   baud = B110; break;
        case B75:   
        case 75:    baud = B75; break;
        case B50:   
        case 50:    baud = B50; break;
        default:    baud = B9600;break;

    }
    printf("Baud rate setting\r\n");
 	if(cfsetispeed(&dev->set, baud) != 0){
        printf("Baud rate setting failed 1\r\n");
        return -1;
    }
	if(cfsetospeed(&dev->set, baud) != 0){
        printf("Baud rate setting failed 2\r\n");
        return -2;
    }
    err = tcsetattr(dev->fd, TCSANOW, &dev->set);
    if(err != 0){
        perror("tcsetattr fd");
        printf("Setting the terminal baud rate failed\r\n");
        return -3;
    }
    return 0;
}

/******************************************************************************
function: Serial port sends one byte of data
parameter:
    buf :   Sent data
Info:
******************************************************************************/
int uvm_uart_writeByte(HARDWARE_UART dev, uint8_t buf)
{
    uint8_t sbuf[1] = {0};
    sbuf[0] = buf;
    return write(dev.fd, sbuf, 1);
}

/******************************************************************************
function: Serial port sends arbitrary length data
parameter:
    buf :   Sent Data buffer
    len :   Number of bytes sent
Info:
******************************************************************************/
int uvm_uart_write(HARDWARE_UART dev, const char * buf, uint32_t len)
{
    return write(dev.fd, buf, len);
}

/******************************************************************************
function: The serial port reads a byte
parameter:
Info: Return read data
******************************************************************************/
int uvm_uart_readByte(HARDWARE_UART dev)
{
    uint8_t buf[1] = {0};
    if (read(dev.fd, buf, 1) < 0)
    {
        return -1;
    }
    return buf[0];
}

/******************************************************************************
function: Serial port reads arbitrary byte length data
parameter:
    buf :   Read Data buffer
    len :   Number of bytes Read
Info:
******************************************************************************/
int uvm_uart_read(HARDWARE_UART dev, char* buf, uint32_t len)
{
    return read(dev.fd, buf, len);
}

int uvm_uart_data_avail(HARDWARE_UART dev)
{
  int result ;

  if (ioctl (dev.fd, FIONREAD, &result) == -1)
    return -1 ;

  return result ;
}

/******************************************************************************
function: Set serial port parameters
parameter:
    databits :   Data bit
    stopbits :   Stop bit
    parity   :   Parity bit
Info:
******************************************************************************/
int uvm_uart_Set(HARDWARE_UART *dev, int databits, int stopbits, int parity)
{
    if(tcgetattr(dev->fd, &dev->set) != 0)
    {
        perror("tcgetattr fd");
        printf("Failed to get terminal parameters\r\n");
        return 0;
    }
   dev->set.c_cflag |= (CLOCAL | CREAD);        //Generally set flag

    switch(databits)        //Set the number of data bits
    {
    case 5:
        dev->set.c_cflag &= ~CSIZE;
        dev->set.c_cflag |= CS5;
        break;
    case 6:
        dev->set.c_cflag &= ~CSIZE;
        dev->set.c_cflag |= CS6;
        break;
    case 7:
        dev->set.c_cflag &= ~CSIZE;
        dev->set.c_cflag |= CS7;
        break;
    case 8:
        dev->set.c_cflag &= ~CSIZE;
        dev->set.c_cflag |= CS8;
        break;
    default:
        fprintf(stderr, "Unsupported data size.\n");
        return 0;
    }

    switch(parity)            //Set check digit
    {
    case 'n':
    case 'N':
        dev->set.c_cflag &= ~PARENB;        //Clear check digit
        dev->set.c_iflag &= ~INPCK;         //enable parity checking
        break;
    case 'o':
    case 'O':
        dev->set.c_cflag |= PARENB;         //enable parity
        dev->set.c_cflag |= PARODD;         //Odd parity
        dev->set.c_iflag |= INPCK;          //disable parity checking
        break;
    case 'e':     
    case 'E':        
        dev->set.c_cflag |= PARENB;         //enable parity        
        dev->set.c_cflag &= ~PARODD;        //Even parity         
        dev->set.c_iflag |= INPCK;          //disable pairty checking        
        break;     
    case 's':    
    case 'S':         
        dev->set.c_cflag &= ~PARENB;        //Clear check digit         
        dev->set.c_cflag &= ~CSTOPB;
        dev->set.c_iflag |= INPCK;          //disable pairty checking        
        break;    
    default:         
        fprintf(stderr, "Unsupported parity.\n");        
        return 0;        
    }
    switch(stopbits)        //Set stop bit  1   2
    {     
        case 1:         
            dev->set.c_cflag &= ~CSTOPB;        
            break;     
        case 2:        
            dev->set.c_cflag |= CSTOPB;    
            break;   
        default:     
            fprintf(stderr, "Unsupported stopbits.\n");         
            return 0;     
    }    
    dev->set.c_cflag |= (CLOCAL | CREAD);
    dev->set.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    dev->set.c_oflag &= ~OPOST;
    dev->set.c_oflag &= ~(ONLCR | OCRNL);
    dev->set.c_iflag &= ~(ICRNL | INLCR);    
    dev->set.c_iflag &= ~(IXON | IXOFF | IXANY);
    tcflush(dev->fd, TCIFLUSH);
    dev->set.c_cc[VTIME] = 150;        //Set timeout
    dev->set.c_cc[VMIN] = 1;        //
    if(tcsetattr(dev->fd, TCSANOW, &dev->set) != 0)   //Update the UART_Set and do it now  
    {
        perror("tcsetattr fd");
        printf("Setting terminal parameters failed\r\n");
        return 0;    
    }   
    printf("Set terminal parameters successfully\r\n");
    return 1;
}
