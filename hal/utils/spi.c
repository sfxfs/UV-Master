#include "log.h"
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

int uvm_spi_init(HARDWARE_SPI *spi, char *dev, uint32_t mode, uint8_t bits, uint32_t speed)
{
   int ret;
   int fd;
   spi->max_speed = speed;
   spi->bits = bits;
   fd = open(dev, O_RDWR);
   if (fd < 0)
   {
      log_error("open %s error",dev);
      return -1;
   }

   // Set SPI mode
   ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
   if (ret == -1)
   {
      log_error("SPI_IOC_RD_MODE error");
      goto fd_close;
   }
   ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
   if (ret == -1)
   {
      log_error("SPI_IOC_WR_MODE error");
      goto fd_close;
   }

   // Set the length of SPI communication
   ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
   if (ret == -1)
   {
      log_error("SPI_IOC_RD_BITS_PER_WORD error");
      goto fd_close;
   }
   ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
   if (ret == -1)
   {
      log_error("SPI_IOC_WR_BITS_PER_WORD error");
      goto fd_close;
   }

   // Set the maximum working frequency of SPI
   ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
   if (ret == -1)
   {
      log_error("SPI_IOC_WR_MAX_SPEED_HZ error");
      goto fd_close;
   }
   ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
   if (ret == -1)
   {
      log_error("SPI_IOC_RD_MAX_SPEED_HZ error");
      goto fd_close;
   }

   log_debug("spi mode: 0x%x", mode);
   log_debug("bits per word: %d", bits);
   log_debug("max speed: %d Hz (%d KHz)", speed, speed / 1000);

   spi->fd = fd;
   return fd;

fd_close:

   close(fd);
   return -1;
}

int uvm_spi_deinit(HARDWARE_SPI *spi)
{
   return close(spi->fd);
}

int uvm_spi_transfer(HARDWARE_SPI *spi, uint8_t const *tx, uint8_t const *rx, size_t len,uint16_t delay)
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
