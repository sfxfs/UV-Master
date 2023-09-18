#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/spi/spidev.h>

#include "spi.h"

int rov_spi_init(HARDWARE_SPI *spi, char *dev, uint32_t mode, uint8_t bits, uint32_t speed)
{
   int ret;
   int fd;
   spi->max_speed = speed;
   spi->bits = bits;
   fd = open(dev, O_RDWR);
   if (fd < 0)
   {
      printf("open %s error......\r\n",dev);
      return -1;
   }

   // Set SPI mode
   ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
   if (ret == -1)
   {
      printf("SPI_IOC_RD_MODE error......\n ");
      goto fd_close;
   }
   ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
   if (ret == -1)
   {
      printf("SPI_IOC_WR_MODE error......\n ");
      goto fd_close;
   }

   // Set the length of SPI communication
   ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
   if (ret == -1)
   {
      printf("SPI_IOC_RD_BITS_PER_WORD error......\n ");
      goto fd_close;
   }
   ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
   if (ret == -1)
   {
      printf("SPI_IOC_WR_BITS_PER_WORD error......\n ");
      goto fd_close;
   }

   // Set the maximum working frequency of SPI
   ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
   if (ret == -1)
   {
      printf("SPI_IOC_WR_MAX_SPEED_HZ error......\n ");
      goto fd_close;
   }
   ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
   if (ret == -1)
   {
      printf("SPI_IOC_RD_MAX_SPEED_HZ error......\n ");
      goto fd_close;
   }

   printf("spi mode: 0x%x\n", mode);
   printf("bits per word: %d\n", bits);
   printf("max speed: %d Hz (%d KHz)\n", speed, speed / 1000);

   spi->fd = fd;
   return fd;

fd_close:

   close(fd);
   return -1;
}

int rov_spi_deinit(HARDWARE_SPI *spi)
{
   return close(spi->fd);
}

int rov_spi_transfer(HARDWARE_SPI *spi, uint8_t const *tx, uint8_t const *rx, size_t len,uint16_t delay)
{
   int ret;

   struct spi_ioc_transfer tr = {
       .tx_buf = (unsigned long)tx,
       .rx_buf = (unsigned long)rx,
       .len = len,
       .delay_usecs = delay,
       .speed_hz = spi->max_speed,
       .bits_per_word = spi->bits,
   };

   ret = ioctl(spi->fd, SPI_IOC_MESSAGE(1), &tr);
   if (ret == -1)
   {
      return -1;
   }

   return 0;
}
