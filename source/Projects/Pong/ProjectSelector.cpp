#include "source/Pong.h"
#include "MPE/Base/EntryPoint.h"

// TODO: CREATE LAMBDA LIKE PROJECT / TEST SELECTOR

class ProjectSelector : public MPE::App
{
public:
    ProjectSelector()
    {
        PushLayer(new PONG::Pong());
    }

    ~ProjectSelector()
    {
    }
};

MPE::App *MPE::CreateApp()
{
    return new ProjectSelector();
}