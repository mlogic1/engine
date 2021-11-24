#ifndef I_INPUT_RECEIVER_H
#define I_INPUT_RECEIVER_H

#include "Key.h"

namespace System
{
	class IInputReceiver
	{
		public:
			virtual void OnKeyPressed(Key key) = 0;
			virtual void OnKeyReleased(Key key) = 0;
	};
}

#endif
