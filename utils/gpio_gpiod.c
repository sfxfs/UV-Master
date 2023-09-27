#include <stdio.h>
#include <gpiod.h>

int rov_gpiod_set_input(const char *path, unsigned int offset)
{
	int ret = -1;

	struct gpiod_chip *chip = gpiod_chip_open(path);
	if (NULL == chip)
	{
		printf("cannot open %s, please run as root\n", path);
		goto chip_error;
	}

	struct gpiod_line *line = gpiod_chip_get_line(chip, offset);
	if (NULL == chip)
	{
		printf("cannot open %s line %d\n", path, offset);
		goto line_error;
	}

	ret = gpiod_line_request_input(line, NULL);
	if (0 != ret)
	{
		printf("cannot set %s line %d to input\n", path, offset);
	}

	gpiod_line_release(line);
line_error:
	gpiod_chip_close(chip);
chip_error:
	return ret;
}

int rov_gpiod_set_output(const char *path, unsigned int offset, int initial_value)
{
	int ret = -1;

	struct gpiod_chip *chip = gpiod_chip_open(path);
	if (NULL == chip)
	{
		printf("cannot open %s, please run as root\n", path);
		goto chip_error;
	}

	struct gpiod_line *line = gpiod_chip_get_line(chip, offset);
	if (NULL == chip)
	{
		printf("cannot open %s line %d\n", path, offset);
		goto line_error;
	}

	ret = gpiod_line_request_output(line, NULL, initial_value);
	if (0 != ret)
	{
		printf("cannot set %s line %d to output\n", path, offset);
	}

	gpiod_line_release(line);
line_error:
	gpiod_chip_close(chip);
chip_error:
	return ret;
}

int rov_gpiod_set_value(const char *path, unsigned int offset, int value)
{
	int ret = -1;

	struct gpiod_chip *chip = gpiod_chip_open(path);
	if (NULL == chip)
	{
		printf("cannot open %s, please run as root\n", path);
		goto chip_error;
	}

	struct gpiod_line *line = gpiod_chip_get_line(chip, offset);
	if (NULL == chip)
	{
		printf("cannot open %s line %d\n", path, offset);
		goto line_error;
	}

	ret = gpiod_line_set_value(line, value);
	if (0 != ret)
	{
		printf("cannot set %s line %d to %d\n", path, offset, value);
	}

	gpiod_line_release(line);
line_error:
	gpiod_chip_close(chip);
chip_error:
	return ret;
}

int rov_gpiod_get_value(const char *path, unsigned int offset)
{
	int ret = -1;

	struct gpiod_chip *chip = gpiod_chip_open(path);
	if (NULL == chip)
	{
		printf("cannot open %s, please run as root\n", path);
		goto chip_error;
	}

	struct gpiod_line *line = gpiod_chip_get_line(chip, offset);
	if (NULL == chip)
	{
		printf("cannot open %s line %d\n", path, offset);
		goto line_error;
	}

	ret = gpiod_line_get_value(line);
	if (0 > ret)
	{
		printf("cannot get %s line %d value\n", path, offset);
	}

	gpiod_line_release(line);
line_error:
	gpiod_chip_close(chip);
chip_error:
	return ret;
}
