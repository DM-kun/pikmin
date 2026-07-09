#include "App.h"
#include "sysNew.h"
#include "system.h"

#ifdef TARGET_PC
#include "sysBootup.h"
#endif

/**
 * @todo: Documentation
 */
#ifdef TARGET_PC
void game_main(void)
#else
TERNARY_BUILD_MATCHING(void, int) main(int argc, char* argv[])
#endif
{
	gsys->Initialise();
	nodeMgr = new NodeMgr();
	gsys->run(new PlugPikiApp());

	OSErrorLine(29, "End of demo");
}
