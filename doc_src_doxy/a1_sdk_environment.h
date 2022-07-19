
#ifndef _SDK_ENVIRONMENT_H_
#define _SDK_ENVIRONMENT_H_

/**
@page sdk_environment SDK Environment setup

As a prerequisite for this guide, you must be able to successfully build
one of the provided application example from the SDK.

This page contains following sections:
- @subpage installation_of_sdk_environment
- @subpage checking_the_installation_validity
- @subpage flashing_guideline
- @subpage nordic_resources
- @subpage efr32_resources

@section installation_of_sdk_environment Installation of SDK Environment

This page contains following sections:
- @subpage windows_installation
- @subpage linux_installation

@subsection windows_installation  Windows installation using WSL

For Windows installation, we're using <a href="https://docs.microsoft.com/en-us/windows/wsl/about">
Windows Subsystem for Linux</a>. There are other possible options, such as <a href="https://www.cygwin.com/">Cygwin</a>
or <a href="http://www.mingw.org/">MinGW</a> but they are not covered here.

First, install Windows Subsystem for Linux according to
<a href="https://docs.microsoft.com/en-us/windows/wsl/install-win10">
installation guidelines</a>. Choose Ubuntu installation.

After done that and system is update, proceed following in bash:

Update the system:
@code
sudo apt update && sudo apt upgrade && sudo apt dist-upgrade && sudo apt autoremove
@endcode

This page contains following sections:
- @subpage wsl_compiler
- @subpage wsl_misc

@subsection wsl_compiler Compiler installation

Using <a href="https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads">
GCC Arm toolchain version 7.2.1 (7-2017-q4-major)</a> is recommended to be
used. Download the toolchain (in some directory of your own choice):
@code
wget -O gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2 https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2?revision=375265d4-e9b5-41c8-bf23-56cbe927e156?product=GNU%20Arm%20Embedded%20Toolchain,64-bit,,Linux,7-2017-q4-major
@endcode

And unpack the downloaded package:
@code
tar xjf gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2
@endcode

Now, there is a subfolder called <code>gcc-arm-none-eabi-7-2017-q4-major</code>
containing necessary tools. You may move the folder to desired location.
Modify <code>PATH</code> to contain <code>bin</code> subfolder, for example
<a href="https://smallbusiness.chron.com/modify-path-ubuntu-52030.html">here
</a>.

After that, you can verify that compiler toolchain has installed by typing:
@code
arm-none-eabi-gcc --version
@endcode

which should produce following output:
@code
arm-none-eabi-gcc (GNU Tools for Arm Embedded Processors 7-2017-q4-major) 7.2.1 20170904 (release) [ARM/embedded-7-branch revision 255204]
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
@endcode

@subsection wsl_misc Miscellaneous installation

Here are other software components that should be installed:

@code
sudo apt install build-essential python python-pip
@endcode

Install required Python libraries:
@code
sudo pip install pycryptodome
@endcode

@subsection linux_installation Installation on Ubuntu Linux

For Ubuntu-based variants, follow guideline used in @ref windows_installation
"Windows installation using WSL".

@section checking_the_installation_validity Checking the installation validity

@ref custom_app/app.c "The custom_app application" is a simple application that sends
a periodically incrementing counter value over the Wirepas network.

The application can be built with the following command:

@code
    make app_name=custom_app target_board=<target_board>
@endcode

After execution of this command, you should find the
<code>final_image_custom_app.hex</code> under <code>build/\<target_board\>/\<app_name\></code>
folder.

@section flashing_guideline Flashing devices

When using the board for the first time, the image named
<code>final_image_<*app_name*>.hex</code> generated by the build process must be
flashed. This image contains the Wirepas bootloader and a scratchpad
composed by the Wirepas Mesh stack and the application. This step must
be done on each new board.

On next boot, the stack and the application will be flashed from the
scratchpad to their dedicated flash areas.

Using the flash mechanism is a convenient way to develop the application
as long as the devices are accessible and not in high volumes. When
updating a large network, using OTAP is more practical.

This page contains following sections:
- @subpage flashing_nordic_nrf52_devices
- @subpage flashing_silabs_devices

@subsection flashing_nordic_nrf52_devices Flashing Nordic nRF52 devices

For information on how to flash Nordic nRF52xxx devices, check out <a
href="https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_nrf5x_cltools%2FUG%2Fcltools%2Fnrf5x_command_line_tools_lpage.html">
nRF5x Command Line Tools User Guide</a>

@subsection flashing_silabs_devices Flashing Silicon Labs Devices

First, install <a href="https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack">
Segger J-Link Software and Documentation Pack</a>

For information how to use Segger Jlink command-line executable (named either <code>JLink.exe
</code> or <code>Jlinkexe</code> according to your operating system), refer to
<a href="https://wiki.segger.com/J-Link_Commander">J-Link Commander</a>.

The following information should be used.

<table>
<tr><th>Device architecture</th><th>Radio profile</th><th>JLink device type</th></tr>
<tr><td>\ref efr32xg12 "EFR32xG12"</td><td>2.4 GHz/SubGhz</td><td>EFR32FG12PxxxF1024</td></tr>
</table>

Note: usually interface is SWD but it depends on the hardware design. For example:
<a href="https://www.silabs.com/support/getting-started/proprietary-wireless/flex-gecko">
Flex Gecko</a> uses SWD.

Here, couple of example <I> J-Link Commander Command files</I> that can be used
as a reference:

Programming EFR32xG12 device:
@code
device EFR32FG12PxxxF1024
if SWD
speed 1000
connect
r
loadfile <path_to_hex_file>.hex
r
g
q
@endcode

You may also need to <i>recover</i> the device when you need to:
-  Remove all the parameterization
-  Flash firmware again (with protected bootloader)

The recovery removes flash write protection mechanism and whole flash contents.
Following command for recovering is issued when using JLink commander:
@code
J-Link>unlock <enter>
Syntax: unlock <DeviceName>
---Supported devices---
  LM3Sxxx [<Auto>]
  Kinetis
  EFM32Gxxx
  LPC5460x
J-Link>unlock LM3Sxxx <enter>
Be sure that nRESET is LOW before continuing.
If you are working with an eval board,
please press the RESET button and keep it pressed.
Press enter to start unlock sequence...
Unlocking device...O.K.
Please power-cycle target hardware.
@endcode


@section nordic_resources Resources on Nordic nRF52

The nRF52 chip version supported by Wirepas Mesh has minimum 512kB of flash and
64kB of RAM.

This page contains following sections:
- @subpage flash_memory_nrf52
- @subpage ram_memory_nrf52
- @subpage peripherals_accessible_by_stack_only
- @subpage peripherals_shared_between_the_stack_and_the_application
- @subpage peripherals_available_for_the_application

@subsection flash_memory_nrf52 Flash Memory available for application on nRF52

As stated in @ref memory_partitioning "description of memory partitioning", the
available flash memory for application is limited by size of the memory area
that is used commonly for application and also scratchpad image. If application
size is too large, there is possibility that large scratchpad image will
override application image. The default maximum size of the application has been
set so that it is always safe to use scratchpad image that will contain both
firmware and application.

The _recommended_ maximum size of @ref flash_memory "flash memory" for an
application, according to processor type is following:

<table>
<tr><th>Processor</th><th>Flash memory</th></tr>
<tr><td>nRF52832</td><td>40kB</td></tr>
<tr><td>nRF52833</td><td>40kB</td></tr>
<tr><td>nRF52840</td><td>256kB</td></tr>
</table>

@subsection ram_memory_nrf52 RAM Memory available for application on nRF52

Allocated @ref ram_memory "RAM memory" for application by the processor is
following:
<table>
<tr><th>Processor</th><th>RAM memory</th></tr>
<tr><td>nRF52832</td><td>Up to 16 kB (8 kB by default)</td></tr>
<tr><td>nRF52833</td><td>72 kB</td></tr>
<tr><td>nRF52840</td><td>188 kB</td></tr>
</table>

@subsection peripherals_accessible_by_stack_only Peripherals accessible by stack only

Some peripherals are used by the Wirepas Mesh stack and cannot be
used by the application.

<table>
<tr><th>Peripheral</th><th>Associated interrupt (from file @ref mcu/nrf52/vendor/nrf52.h)</th></tr>
<tr><td>Power</td><td><code>POWER_CLOCK_IRQn</code></td></tr>
<tr><td>Radio</td><td><code>RADIO_IRQn</code></td></tr>
<tr><td>Timer0</td><td><code>TIMER0_IRQn</code></td></tr>
<tr><td>WDT</td><td><code>WDT_IRQn</code></td></tr>
<tr><td>Rtc1</td><td><code>RTC1_IRQn</code></td></tr>
<tr><td>ECB (AES)</td><td><code>ECB_IRQn</code></td></tr>
<tr><td>PPI (Channels 0, 1 and 2)</td><td><code>None</code></td></tr>
</table>

All the internal interrupt of cortex M are handled by the stack
directly (NMI, HardFault,...)

@subsection peripherals_shared_between_the_stack_and_the_application Peripherals Shared between the stack and the application

Some peripherals are used by the stack but can also be accessed by the
application. There is a @ref app_lib_hardware_t "dedicated API" to reserve these peripherals.

These peripherals must be reserved through the API before being used and
the application must initialize them each time after reserving it. In
fact, the stack may configure them differently.

It is also important to avoid long reservation of theses peripherals to
let the stack use them for its own purpose.

<table>
<tr><th>Peripheral</th><th>Reservation ID (from @ref app_lib_hardware_peripheral_e)</th></tr>
<tr><td>ADC</td><td>@ref APP_LIB_HARDWARE_PERIPHERAL_ADC</td></tr>
<tr><td>Temp</td><td>@ref APP_LIB_HARDWARE_PERIPHERAL_TEMPERATURE</td></tr>
</table>

Random Number Generator RNG (nRF52) and True Random Number Generator TRNG (EFR32)
are available for application to use within App_init function.
After App_init returns, these peripherals are reserved for Wirepas Mesh stack and
all initializations done in App_init may be overwritten.
Application may also take the control of RNG/TRNG by initializing the peripheral in
scheduled task after App_init has returned and after Wirepas Mesh stack has started.
Do note that initialization must not take place within interrupt context as interrupt
could be served before these peripherals are released from Wirepas Mesh stack usage.

@subsection peripherals_available_for_the_application Peripherals available for the application

All the other peripherals not listed above are free to be used by the application.

@section efr32_resources Resources on EFR32

Following chip variants (at 2.4 GHz only) are supported:

-   EFR32FG12P232F1024G L125/M48    [2.4 GHz only, 1024/128, BGA125/QFN48]
-   EFR32FG12P432F1024G L125/M48    [2.4 GHz only, 1024/256, BGA125/QFN48]
-   EFR32FG12P433F1024G L125/M48    [2.4 GHz & SubGHz, 1024/256, BGA125/QFN48]
-   EFR32MG12P232F1024G L125/M48    [2.4 GHz only, 1024/128, BGA125/QFN48]
-   EFR32MG12P332F1024G L125/M48    [2.4 GHz only, 1024/128, BGA125/QFN48]
-   EFR32MG12P432F1024G L125/M48    [2.4 GHz only, 1024/256, BGA125/QFN48]
-   EFR32MG12P433F1024G L125/M48    [2.4 GHz & SubGHz, 1024/256, BGA125/QFN48]
-   EFR32BG12P232F1024G L125/M48    [2.4 GHz only, 1024/128, BGA125/QFN48]
-   EFR32BG12P432F1024G L125/M48    [2.4 GHz only, 1024/256, BGA125/QFN48]
-   EFR32BG12P433F1024G L125/M48    [2.4 GHz & SubGHz, 1024/256, BGA125/QFN48]
-   EFR32BG21A010F1024IM32
-   EFR32BG21A010F512IM32
-   EFR32BG21A010F768IM32
-   EFR32BG21A020F1024IM32
-   EFR32BG21A020F512IM32
-   EFR32BG21A020F768IM32
-   EFR32BG22C224F512GM32
-   EFR32BG22C224F512GM40
-   EFR32BG22C224F512GN32
-   EFR32BG22C224F512IM32
-   EFR32BG22C224F512IM40
-   BGM220PC22HNA
-   BGM220SC22HNA

This page contains following sections:
- @subpage flash_memory_efr32
- @subpage ram_memory_efr32
- @subpage peripherals_accessible_by_stack_only2
- @subpage peripherals_shared_between_the_stack_and_the_application2
- @subpage peripherals_available_for_the_application2

@subsection flash_memory_efr32 Flash Memory available for application on EFR32

As stated in @ref memory_partitioning "description of memory partitioning", the
available flash memory for application is limited by size of the memory area
that is used commonly for application and also scratchpad image. If application
size is too large, there is possibility that large scratchpad image will
override application image. The default maximum size of the application has been
set so that it is always safe to use scratchpad image that will contain both
firmware and application.

The _recommended_ maximum size of @ref flash_memory "flash memory" for an
application, according to processor type is following:

<table>
<tr><th>Processor</th><th>Flash memory</th></tr>
<tr><td>efr32xg12pxxxf1024</td><td>256kB</td></tr>
<tr><td>efr32xg12pxxxf512</td><td>40kB</td></tr>
<tr><td>efr32xg13pxxxf512</td><td>40kB</td></tr>
<tr><td>efr32xg21xxxxf512</td><td>40kB</td></tr>
<tr><td>efr32xg21xxxxf768</td><td>40kB</td></tr>
<tr><td>efr32xg21xxxxf1024</td><td>256kB</td></tr>
<tr><td>efr32xg22xxxxf512</td><td>40kB</td></tr>
</table>


@subsection ram_memory_efr32 RAM Memory available for application on EFR32

Allocated @ref ram_memory "RAM memory" for application, by the processor is
following:
<table>
<tr><th>Processor</th><th>RAM memory</th></tr>
<tr><td>efr32xg12pxxxf1024</td><td>72kB</td></tr>
<tr><td>efr32xg12pxxxf512</td><td>8kB</td></tr>
<tr><td>efr32xg13pxxxf512</td><td>16kB</td></tr>
<tr><td>efr32xg21xxxxf512</td><td>12kB</td></tr>
<tr><td>efr32xg21xxxxf768</td><td>12kB</td></tr>
<tr><td>efr32xg21xxxxf1024</td><td>44kB</td></tr>
<tr><td>efr32xg22xxxxf512</td><td>4.5kB</td></tr>
</table>

@subsection peripherals_accessible_by_stack_only2 Peripherals accessible by stack only

Some peripherals are used by the Wirepas Mesh stack and cannot be used by the application.

<table>
<tr><th>Peripheral</th><th>Associated interrupt (from chip vendor files)</th></tr>
<tr><td><code>TIMER0</code></td><td><code>TIMER0_IRQn</code></td></tr>
<tr><td><code>RTCC</code></td><td><code>RTCC_IRQn</code></td></tr>
<tr><td><code>WDOG0</code></td><td><code>WDOG0_IRQn</code></td></tr>
<tr><td><code>CMU</code></td><td><code>CMU_IRQn</code></td></tr>
<tr><td><code>CRYPTO0</code></td><td><code>CRYPTO0_IRQn</code></td></tr>
</table>

All the internal interrupt of cortex M are handled by the stack directly (NMI, HardFault,...)

@subsection peripherals_shared_between_the_stack_and_the_application2 Peripherals Shared between the stack and the application

Some peripherals are used by the stack but can also be accessed by the application.

These peripherals must be reserved through the API before being used and the application must initialize them each time after reserving it. In fact, the stack may configure them differently.

It is also important to avoid long reservation of theses peripherals to let the stack use them for its own purpose.

<table>
<tr><th>Peripheral</th><th>Reservation ID (from @ref app_lib_hardware_peripheral_e)</th></tr>
<tr><td>ADC0</td><td>@ref APP_LIB_HARDWARE_PERIPHERAL_ADC</td></tr>
</table>

@subsection peripherals_available_for_the_application2 Peripherals available for the application

All the other peripherals not listed above are free to be used by the application.

Related Material
================

@anchor relmat3 [3] WP-RM-108 - OTAP Reference Manual

@anchor relmat4 [4] https://github.com/wirepas/wm-sdk/blob/master/source/reference_apps/dualmcu_app/api/DualMcuAPI.md

*/


#endif /* API_DOC_SDK_ENVIRONMENT_H_ */
