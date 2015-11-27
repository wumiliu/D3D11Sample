
#include "Sample/Sample.h"
#include "Sample/RenderTargetSample.h"
#include "Sample/LightSample.h"
#include "Sample/MultipleLightsSamlpe.h"
#include "Sample/FXAASample.h"

#include "Sample/DeferredLighting.h"
#include "Sample/DeferredLight.h"
#include "Sample/DeferredLightSample.h"
#include "Sample/ShadowSample.h"



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{

#if defined(DEBUG) || defined(_DEBUG)
	FILE *f(NULL);
	if (AllocConsole())
	{
		freopen_s(&f, "CONOUT$", "w", stdout);
	}
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	ShadowSample theApp(hInstance, 1024, 600);
	if (!theApp.Init())
		return 0;
	return theApp.Run();

}