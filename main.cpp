#include <print>

#include "OpenRGB/Client.hpp"
using orgb::ConnectStatus;
using orgb::DeviceListResult;
using orgb::RequestStatus;
using orgb::DeviceType;
using orgb::Color;
using orgb::Device;

int main()
{
	// Client creation and OpenRGB server connection.
	orgb::Client client("My OpenRGB Client");
	ConnectStatus status = client.connect ("127.0.0.1");
	if (status != ConnectStatus::Success)
	{
		// @Robustness: Terrible error handling. No error code or status message. 
		std::println("Failed to connect: {} (error code: {})", orgb::enumString(status), int(client.getLastSystemError()));
		return 0;
	}

	// Download devices.
	DeviceListResult result = client.requestDeviceList();
	if (result.status != RequestStatus::Success)
	{
		// @Robustness: Terrible error handling. No error code or status message.
		std::println("Failed to retrieve device list.");
		return 0;
	}
	// Search devices by type or name.
	const Device *keyboard = result.devices.find(DeviceType::Keyboard);
	if (!keyboard)
	{
		std::println("Device: Keyboard , not found.");
		return 0;
	}
	client.setDeviceColor(*keyboard, Color::Red);

	return 0;
}
