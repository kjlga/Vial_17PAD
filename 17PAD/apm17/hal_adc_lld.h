#pragma once
#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE
#include_next <hal_adc_lld.h>