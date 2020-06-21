#ifndef I_INPUT_RECEIVER_H
#define I_INPUT_RECEIVER_H

#include "Key.h"

namespace System
{
	class IInputReceiver
	{
		public:
			virtual void ReceiveKeyInput(Key key) = 0;
	};
}

#endif
