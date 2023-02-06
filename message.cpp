#include "message.h"

message::message(std::string _msg, uint64_t _ms)
{
	msg = _msg;
	ms_live = _ms;
	ms_tick = NULL;
}

message::~message()
{
}

void message::draw(HDC hDC)
{
	if (ms_tick + ms_live > std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) {
		for (int i = 0; i < msg.length(); i++) {
			printf("-");
		}
		printf("\n%s\n", msg.c_str());
		for (int i = 0; i < msg.length(); i++) {
			printf("-");
		}
		printf("\n");
	}
	
}

void message::activate()
{
	ms_tick = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
