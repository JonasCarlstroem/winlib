#pragma once

namespace nat
{
	class event_observer
	{
	public:
		virtual void handle(const event& ev) const = 0;
	};
}