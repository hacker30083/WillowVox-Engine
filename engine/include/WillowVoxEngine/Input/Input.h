#pragma once

namespace WillowVox
{
	enum Key
	{
		W,
		A,
		S,
		D
	};

	class Input
	{
		bool GetKey(Key key);
	};
}