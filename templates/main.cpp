#include <libLoam/c++/ArgParse.h>
#include <libLoam/c++/ObColor.h>
#include <libNoodoo/VisiDrome.h>
#include <libNoodoo/VisiFeld.h>

using namespace oblong::loam;
using namespace oblong::basement;
using namespace oblong::noodoo;

ObColor palette[3] = { { 0.7, 0.3, 0.3 },
                       { 0.3, 0.7, 0.3 },
                       { 0.3, 0.3, 0.7 } };

ObRetort Setup (VFBunch *bunch, Atmosphere *atm)
{ const int N = VisiFeld::NumAllVisiFelds ();
  for (int i = 0  ;  i < N  ;  ++i)
    { VisiFeld *vf = VisiFeld::NthOfAllVisiFelds (i);
      const size_t palette_size = sizeof(palette)/sizeof(*palette);
      vf -> SetBackgroundColor (palette [i % palette_size]);
    }
  return OB_OK;
}

int main (int argc, char **argv)
{ ArgParse ap (argc, argv);
  ap . EasyFinish (0, ArgParse::UNLIMITED);
  VisiDrome *instance = new VisiDrome ("{{ project_name }}", ap . Leftovers ());
  instance -> FindVFBunch () -> AppendPostFeldInfoHook (Setup);
  instance -> Respire ();
  instance -> Delete ();

  return 0;
}
