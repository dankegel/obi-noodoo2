/* (c)  oblong industries */

#include <libLoam/c++/ArgParse.h>
#include <libNoodoo2/VisiFeld.h>
#include <libNoodoo2/VisiDrome.h>
#include <libNoodoo2/Scene.h>
#include <libNoodoo2/MeshyThing.h>

using namespace oblong::loam;
using namespace oblong::basement;
using namespace oblong::noodoo2;


// Note: This hook assumes only one VisiFeld will be created and that this will therefore only be called once.
ObRetort VisiFeldSetupHook (VisiDrome *drome, VisiFeld *vf, Atmosphere *atm)
{
  ObRetort error;

  // Create Scene
  ObRef<Scene *> scene = new Scene (SceneMode::Flat, error);
  if (error.IsError ())
    return error;

  // Create Mesh
  ObRef<MeshyThing *> meshy = new MeshyThing (error);
  if (error.IsError ())
    return error;

  // Add data to mesh
  meshy->Geometry ().AppendPosition ({-1.0, -1.0, 0.0});
  meshy->Geometry ().AppendPosition ({1.0, -1.0, 0.0});
  meshy->Geometry ().AppendPosition ({0.0, 1.0, 0.0});

  // Specify draw mode for data
  meshy->Geometry ().SetDrawMode (VertexDrawMode::Triangles);

  // Set color of mesh
  meshy->SetColor (ObColor (1.0, 0.0, 0.0));

  // Set scale of mesh
  meshy->SetScale (Vect (50.0, 50.0, 50.0));

  // Append Scene to VisiFeld
  vf->AppendScene (~scene);

  // Attach mesh to Scene
  scene->RootShowyThing ()->AppendChild (~meshy);

  // Set Root Node pose
  scene->RootShowyThing ()->TranslateLikeFeld (vf);
  scene->RootShowyThing ()->RotateLikeFeld (vf);

  return OB_OK;
}

int main (int ac, char **av)
{
  VisiDrome *drome = new VisiDrome ();

  drome->AppendFeldSetupHook (VisiFeldSetupHook, "mesh");
  drome->Respire ();
  drome->Delete ();

  return 0;
}
