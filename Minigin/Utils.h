#pragma once

namespace
{

	//INTERNAL USE ONLY
	template <int length> struct SdbmHash
	{
		consteval static unsigned int _calculate(const char* const text, unsigned int& value)
		{
			const unsigned int character = SdbmHash<length - 1>::_calculate(text, value);
			value = character + (value << 6) + (value << 16) - value;
			return text[length - 1];
		}

		consteval static unsigned int calculate(const char* const text)
		{
			unsigned int value{ 0 };
			const auto character = _calculate(text, value);
			return character + (value << 6) + (value << 16) - value;
		}
	};

	//INTERNAL USE ONLY
	template <> struct SdbmHash<1>
	{
		consteval static int _calculate(const char* const text, unsigned int&) { return text[0]; }
	};

}

namespace dae
{

	namespace utils
	{

		template <size_t N> consteval unsigned int MakeSdbmHash(const char(&text)[N])
		{
			return SdbmHash<N - 1>::calculate(text);
		}

		//Rect with origin in the top left corner
		struct SrcDstRect
		{
			int x{};
			int y{};
			int width{};
			int height{};
		};
	}
}