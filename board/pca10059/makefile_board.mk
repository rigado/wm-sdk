# Add board specific sources here, if any
SRCS += board/$(target_board)/board_custom_init.c
CFLAGS += -DUSB_PID=$(usb_pid)
