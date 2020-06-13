#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H

#include <string>

namespace System
{
	/*enum SystemType
	{
		DESKTOP = 0,
		ANDROID
	};*/

	enum GLRenderMode
	{
		LetterBox = 0,
		Virtual4By3 = 1,
		Stretch
	};

	class SystemBase
	{
	public:
		virtual bool InitSystem() = 0;
		virtual void Update() = 0;
		virtual bool IsRunning() = 0;

		// TODO getsystemtype

		virtual bool LoadBinaryDataFromAssets(const std::string fileName, unsigned char*& data, off_t& length) = 0;
		virtual bool LoadStringDataFromAssets(const std::string fileName, std::string& data) = 0;

	protected:
		// rendering mode // TODO maybe move this to a global configuration source file
		GLRenderMode _RenderMode = GLRenderMode::LetterBox;
	};

	extern SystemBase* SYSTEM_PTR;
	bool InitGameEngine();
}

#endif // SYSTEM_H