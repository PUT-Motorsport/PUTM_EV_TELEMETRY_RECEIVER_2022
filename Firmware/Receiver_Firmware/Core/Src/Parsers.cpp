/*
 * Parsers.c
 *
 *  Created on: 11 May 2022
 *      Author: Adam Wasilewski
 */
#include <Parsers.hpp>
#include <cstdlib>
#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <fmt/format-inl.h>
#include "usbd_cdc_if.h"

//extern UART_HandleTypeDef hlpuart1;

uint8_t buffer[34]{0};

void Pass(uint8_t RxData[])
{
	memcpy(buffer, RxData, 32);
	for(size_t i = 1; i < 31; i++)
	{
		buffer[i] = i;
	}
	buffer[31] = RxData[0];
	buffer[32] = '\r';
	buffer[33] = '\n';
	//HAL_UART_Transmit(&hlpuart1, buffer , 66, 100);
	CDC_Transmit_FS((uint8_t*)buffer, sizeof(buffer));
	HAL_Delay(1);
}
/*
void Update_Terminal2()
{
	auto out = fmt::memory_buffer();
	format_to(std::back_inserter(out),"APPS:{} LVV:{} LV SoC{} HVV:{} HV SoC:{} HV T:{} HV Curr:{} BP Front:{} Speed:{} Motor curr:{} Engine V:{} Inverter T:{}\n\r",
			ms65.Pedal_Position,ms65.LV_Voltage,ms65.LV_Soc,ms65.HV_Voltage, ms65.HV_SoC, ms65.HV_Temps, ms65.HV_Current,ms66.brake_pressure_front,ms67.vehicle_speed,ms67.motor_current, ms67.engine_speed, ms68.inverter_temp);

	auto data = out.data(); // pointer to the formatted data
	auto size = out.size(); // size of the formatted data

	HAL_UART_Transmit(&hlpuart1, (uint8_t*)(data), size, 1000);

	HAL_Delay(10);
}
*/
