/* Copyright 2021 Rigado, Inc. All Rights Reserved.
 *
 * See file LICENSE.txt for full license details.
 *
 */
#include <stdint.h>

#include "board.h"
#include "mcu.h"

#define AMP_NRF_GPIO_PIN_RESET  0
#define AMP_NRF_GPIO_PIN_SET    1

static inline void amp_nrf_gpio_cfg_out(uint32_t pin_number, uint8_t pin_state)
{
    nrf_gpio_cfg_output(pin_number);
    if(pin_state == AMP_NRF_GPIO_PIN_RESET)
    {
        nrf_gpio_pin_clear(pin_number);
    }
    else
    {
        nrf_gpio_pin_set(pin_number);
    }
}

/**
 * \brief   Set up the PCB antenna for bypass mode
 */
void Board_custom_init()
{
    amp_nrf_gpio_cfg_out(PA_LNA_RX_EN_PIN,  AMP_NRF_GPIO_PIN_RESET);
    amp_nrf_gpio_cfg_out(PA_LNA_TX_EN_PIN,  AMP_NRF_GPIO_PIN_RESET);
    amp_nrf_gpio_cfg_out(PA_LNA_MODE_PIN,   AMP_NRF_GPIO_PIN_SET);
    amp_nrf_gpio_cfg_out(PA_LNA_SW_ANT_PIN, AMP_NRF_GPIO_PIN_SET);
}
